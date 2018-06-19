/*

Copyright (c) 2012-2014, ARM Limited. All rights reserved.
Copyright (c) Microsoft Corporation. All rights reserved.

This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

File name:

    EnetRecv.c

Abstract:

    implements Ethernet MAC (ENET) SNP receive function.

*/

#include "EnetDxe.h"
#include <iMX6.h>
#include <iMX6ClkPwr.h>
#include <Library/TimerLib.h>
#include <Library/CacheMaintenanceLib.h>

/*
This function retrieves one packet from the receive queue of a network interface. If there are no
packets on the receive queue, then EFI_NOT_READY will be returned. If there is a packet on the
receive queue, and the size of the packet is smaller than BufferSize, then the contents of the
packet will be placed in Buffer, and BufferSize will be updated with the actual size of the
packet. 
In addition, if SrcAddr, DestAddr, and Protocol are not NULL, then these values will
be extracted from the media header and returned. EFI_SUCCESS will be returned if a packet was
successfully received. If BufferSize is smaller than the received packet, then the size of the
receive packet will be placed in BufferSize and EFI_BUFFER_TOO_SMALL will be returned.
If the driver has not been initialized, EFI_DEVICE_ERROR will be returned.

Arguments:

This        A pointer to the EFI_SIMPLE_NETWORK_PROTOCOL instance.
HeaderSize  The size, in bytes, of the media header received on the network interface. If this parameter is NULL, then the media header size will not be returned.
BufferSize  On entry, the size, in bytes, of Buffer. On exit, the size, in bytes, of the packet that was received on the network interface.
Buffer      A pointer to the data buffer to receive both the media header and the data.
SrcAddr     The source HW MAC address. If this parameter is NULL, the HW MAC source address will not be extracted from the media header.
DestAddr    The destination HW MAC address. If this parameter is NULL, the HW MAC destination address will not be extracted from the media header.
Protocol    The media header type. If this parameter is NULL, then the protocol will not be extracted from the media header. See RFC 1700 section “Ether Types” for examples.

Retrun values:

    EFI_SUCCESS             The received data was stored in Buffer, and BufferSize has been updated to the number of bytes received.
    EFI_NOT_STARTED         The network interface has not been started.
    EFI_NOT_READY           No packets have been received on the network interface.
    EFI_BUFFER_TOO_SMALL    BufferSize is too small for the received packets. BufferSize has been updated to the required size. 
    EFI_INVALID_PARAMETER   One or more of the following conditions is TRUE:
                                The This parameter is NULL
                                The This parameter does not point to a valid EFI_SIMPLE_NETWORK_PROTOCOL structure.
                                The BufferSize parameter is NULL
                                The Buffer parameter is NULL
    EFI_DEVICE_ERROR        The command could not be sent to the network interface.
 */
EFI_STATUS EFIAPI SnpReceive(IN EFI_SIMPLE_NETWORK_PROTOCOL* SnpPtr,
                            OUT UINTN* HdrSizePtr OPTIONAL,
                            IN OUT UINTN* BuffSizePtr,
                            OUT VOID* DataPtr,
                            OUT EFI_MAC_ADDRESS* SrcAddrPtr OPTIONAL,
                            OUT EFI_MAC_ADDRESS* DstAddrPtr OPTIONAL,
                            OUT UINT16* ProtocolPtr OPTIONAL)
{
    EFI_STATUS Status = 0;
    LANENET_DRIVER* LanDriverPtr;
    UINT32 FrameLen;
    EFI_MAC_ADDRESS Dst;
    EFI_MAC_ADDRESS Src;
    UINTN DroppedFrames;
    UINT32 TempReg = 0;
    UINT32 CurrPacIndex = 0;
    UINT16 TempReg16 = 0;
    INT32 k = 0;
    EFI_TPL SavedTpl;
    volatile ENET_BD* RxBDPtr = NULL;
    volatile UINT8* RxBufferPtr = NULL;
    UINT8* DataBytePtr = NULL;

    ENET_INFO("++SnpReceive(*bufsiz=%d)\r\n", *BuffSizePtr);

    // Check preliminaries

    if((SnpPtr == NULL) || (DataPtr == NULL) || (BuffSizePtr == NULL)) 
    {
        ENET_ERROR("SnpReceive() Error - null pointer(s)\r\n");
        return EFI_INVALID_PARAMETER;
    }

    SavedTpl = gBS->RaiseTPL(ENETIMX6_TPL);

    LanDriverPtr = INSTANCE_FROM_SNP_THIS(SnpPtr);

    RxBDPtr = LanDriverPtr->RecvBDPtrs[LanDriverPtr->Rbd_index];
    RxBufferPtr = LanDriverPtr->RxBuffersPtr[LanDriverPtr->Rbd_index];

    // Check that driver was started and initialised

    if(SnpPtr->Mode->State == EfiSimpleNetworkStarted) 
    {
        ENET_WARNING("Warning: Efi network not initialized\r\n");
        Status=EFI_DEVICE_ERROR;
        goto EndReceive;
    } 
    else if(SnpPtr->Mode->State == EfiSimpleNetworkStopped) 
    {
        ENET_WARNING("Warning: Efi network Driver in stopped state\r\n");
        Status=EFI_NOT_STARTED;
        goto EndReceive;
    }

    // receiver should be active when this function runs
    // if sDMA disabled receiver then we ran out of free buffers
    if(LanDriverPtr->ReceiverActivated == TRUE)
    {
        if((MmioRead32((UINTN)&LanDriverPtr->enetRegisters->RDAR) & ENET_RDAR_ACTIVE_ACTIVE) == 0x0)
        {
            AsciiPrint("ALL Reveiver buffers are full!!\r\n");
        }
    }

    // Count dropped frames

    DroppedFrames = MmioRead32((UINTN)&LanDriverPtr->enetRegisters->IEEE_R_DROP); 
    if(DroppedFrames != 0)
    {
        LanDriverPtr->Stats.RxDroppedFrames += DroppedFrames;
        ENET_INFO("SnpReceive dropped frames=%d\r\n", DroppedFrames);
    }

    // check receiver status in EIR for errors
    // use recv_index and control status to check for received frames

    TempReg = MmioRead32((UINTN)&LanDriverPtr->enetRegisters->EIR);
    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->EIR, TempReg);

    if(TempReg & EIR_BIT30_BABERR)
    {
        ENET_ERROR(" Babbling Receive Error. Need to restart.\r\n");
        Status = EFI_DEVICE_ERROR;
        goto EndReceive;
    }

    if(TempReg & EIR_BIT22_EBERR)
    {
        ENET_ERROR(" Ethernet Bus Error. Need to restart.\r\n");
        Status = EFI_DEVICE_ERROR;
        goto EndReceive;
    }

    if(TempReg & EIR_BIT28_GRASTOP) // Graceful Stop Complete
    {
        ENET_ERROR(" Receiver is stopped. Cannot receive.\r\n");
        Status = EFI_DEVICE_ERROR;
        goto EndReceive;
    }

    // so we have new packet(s) now
    
    TempReg16 = RxBDPtr->ControlStatus;

    if((TempReg16 & BD_ENET_RX_EMPTY) == 0) // packet is not empty
    {
        // print frame diagnostics

        ENET_INFO("recv frame [%d] bufferAddrPA=%08Xh VA=%08Xh, ctl_sts=%04Xh length=%d\r\n", 
                LanDriverPtr->Rbd_index, RxBufferPtr, RxBDPtr->BufferAddressPA, RxBDPtr->ControlStatus, RxBDPtr->DataLen);

        if((TempReg16 & BD_ENET_RX_ERRORS) == 0x0)
        {
            if((TempReg16 & BD_ENET_RX_LAST) != 0x0)
            {
                FrameLen = RxBDPtr->DataLen - 4;  // don't count tail 
                ENET_INFO(" Recv datalen=%d\r\n", FrameLen);

                if(FrameLen > 14)
                {                
                    // copy buffer and pass it to upper layers
                    // return it to UEFI if enough space is provided by caller

                    if(FrameLen <= *BuffSizePtr)
                    {
                        *BuffSizePtr = FrameLen;

                        // Read Rx Packet data. Data is aligned but length may be or not multiple of 2
                        // memcopy does not works reliably here due to cahce limitation while sDMA is running

                        DataBytePtr = (UINT8*)DataPtr;

                        CopyMem(DataBytePtr, (VOID*)(UINT32)RxBufferPtr, FrameLen);

                        // Get the received packet length

                        LanDriverPtr->Stats.RxTotalBytes += FrameLen;

                        if(HdrSizePtr != NULL)
                        {
                            *HdrSizePtr = SnpPtr->Mode->MediaHeaderSize;
                        }

                        DataBytePtr = (UINT8*)DataPtr;

                        // Get the destination MAC address - 6 bytes

                        Dst.Addr[0] = *(DataBytePtr);
                        Dst.Addr[1] = *(DataBytePtr + 1);
                        Dst.Addr[2] = *(DataBytePtr + 2);
                        Dst.Addr[3] = *(DataBytePtr + 3);
                        Dst.Addr[4] = *(DataBytePtr + 4);
                        Dst.Addr[5] = *(DataBytePtr + 5);

                        if(DstAddrPtr != NULL) 
                        {
                            CopyMem(DstAddrPtr, &Dst, sizeof(EFI_MAC_ADDRESS));
                        }

                        // Get the source MAC address - 6 bytes

                        Src.Addr[0] = *(DataBytePtr + 6);
                        Src.Addr[1] = *(DataBytePtr + 7);
                        Src.Addr[2] = *(DataBytePtr + 8);
                        Src.Addr[3] = *(DataBytePtr + 9);
                        Src.Addr[4] = *(DataBytePtr + 10);
                        Src.Addr[5] = *(DataBytePtr + 11);

                        if(SrcAddrPtr != NULL) 
                        {
                            CopyMem(SrcAddrPtr, &Src, sizeof(EFI_MAC_ADDRESS));
                        }

                        // skip optional 802.1q tag

                        // Get the protocol - 2 bytes

                        UINT16 ProtocolRead =  *(UINT16*)(DataBytePtr + 12);
                        if(ProtocolPtr != NULL) 
                        {
                            *ProtocolPtr = NTOHS(ProtocolRead);
                        }

                        Status=EFI_SUCCESS;
                        LanDriverPtr->Stats.RxGoodFrames += 1;

                        ENET_RECV(" RECV[%d] {%02X:%02X:%02X:%02X:%02X:%02X}->{%02X:%02X:%02X:%02X:%02X:%02X} prt=%04X len=%d\r\n",
                                    LanDriverPtr->Rbd_index,
                                    Src.Addr[0], Src.Addr[1], Src.Addr[2], Src.Addr[3], Src.Addr[4], Src.Addr[5],
                                    Dst.Addr[0], Dst.Addr[1], Dst.Addr[2], Dst.Addr[3], Dst.Addr[4], Dst.Addr[5],
                                    NTOHS(ProtocolRead), FrameLen);
                    }
                    else
                    {
                        // this typically happens when receiving jumbo frames - 4k 

                        ENET_ERROR("SnpReceive buffer too small! %d given but have %d bytes\r\n", *BuffSizePtr, RxBDPtr->DataLen);
                        *BuffSizePtr = RxBDPtr->DataLen;
                        Status = EFI_BUFFER_TOO_SMALL;
                    }
                }
                else
                {
                    // packet corrupt or too short

                    ENET_ERROR("     Packet too short! len=%d\r\n", FrameLen);
                    *BuffSizePtr = 0;
                    Status=EFI_DEVICE_ERROR;
                }
            }
            else
            {
                // split packet ? Last bit not set
                ENET_ERROR("     Split Packet ?\r\n");
            }
        }
        else
        {
            // error bits are set in packet, discard
            // no need to tell UEFI that we discarded bad packet

            ENET_INFO("    corrupt packet {%08Xh} at %d, discard\r\n", TempReg16, LanDriverPtr->Rbd_index);
            *BuffSizePtr = 0;
            Status = EFI_NOT_READY;
        }

        // mark current buffer as free in RxBD

        CleanOneBlockDescriptor_Rx(RxBDPtr, LanDriverPtr->Rbd_index == LANENET_RX_RING_NUM_ENTRIES-1 ? TRUE : FALSE);

        // move forward to next rx buffer

        LanDriverPtr->Rbd_index = (LanDriverPtr->Rbd_index + 1) % LANENET_RX_RING_NUM_ENTRIES;

        // restart rx engine 

        StartReceiver(LanDriverPtr);          
    }
    else // no packet yet. Just carry on
    {
        *BuffSizePtr = 0;
        Status = EFI_NOT_READY;
    }

EndReceive:
    gBS->RestoreTPL(SavedTpl);
    ENET_INFO("--SnpReceive(RxBD idx=%d)=%Xh\r\n", LanDriverPtr->Rbd_index,Status);
    return Status;
}
