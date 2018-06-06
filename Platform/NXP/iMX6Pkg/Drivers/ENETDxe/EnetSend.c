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

    Enet_send.c

Abstract:

    implements Ethernet MAC (ENET) SNP send function.

*/

#include "EnetDxe.h"
#include <iMX6.h>
#include <iMX6ClkPwr.h>
#include <Library/TimerLib.h>
#include <Library/CacheMaintenanceLib.h>

/*
This function places the packet specified by Header and Buffer on the transmit queue.

The SnpTransmit() function performs nonblocking I/O. A caller who wants to perform blocking I/O,
should call SnpTransmit(), and then SnpGetStatus() until the transmitted buffer shows up in the
recycled transmit buffer.
If the driver has not been initialized, EFI_DEVICE_ERROR will be returned

Arguments:

SnpPtr      A pointer to the EFI_SIMPLE_NETWORK_PROTOCOL instance.
HdrSize     The size, in bytes, of the media header to be filled in by the Transmit() function. 
            If HeaderSize is nonzero, then it must be equal to This->Mode->MediaHeaderSize and the DestAddr and Protocol parameters must not be NULL.
BuffSize    The size, in bytes, of the entire packet (media header and data) to be transmitted through the network interface.
DataPtr     A pointer to the packet (media header followed by data) to be transmitted. This parameter cannot be NULL. 
            If HeaderSize is zero, then the media header in Buffer must already be filled in by the caller. 
            If HeaderSize is nonzero, then the media header will be filled in by the Transmit() function.
SrcAddr     The source HW MAC address. If HeaderSize is zero, then this parameter is ignored. 
            If HeaderSize is nonzero and SrcAddr is NULL, then This->Mode->CurrentAddress is used for the source HW MAC address.
DestAddr    The destination HW MAC address. If HeaderSize is zero, then this parameter is ignored.
ProtocolPtr The type of header to build. 
            If HeaderSize is zero, then this parameter is ignored. See RFC 3232, section “Ether Types,” for examples.

Status Codes Returned:

    EFI_SUCCESS             The packet was placed on the transmit queue.
    EFI_NOT_STARTED         The network interface has not been started.
    EFI_NOT_READY           The network interface is too busy to accept this transmit request.
    EFI_BUFFER_TOO_SMALL    The BufferSize parameter is too small.
    EFI_INVALID_PARAMETER   One or more of the parameters has an unsupported value.
    EFI_DEVICE_ERROR        The command could not be sent to the network interface.
    EFI_UNSUPPORTED         This function is not supported by the network interface.
 */
EFI_STATUS EFIAPI SnpTransmit(IN  EFI_SIMPLE_NETWORK_PROTOCOL* SnpPtr,
                            IN UINTN HdrSize,
                            IN UINTN BuffSize,
                            IN VOID* DataPtr,
                            IN EFI_MAC_ADDRESS* SrcAddr OPTIONAL,
                            IN EFI_MAC_ADDRESS* DstAddr OPTIONAL,
                            IN UINT16* ProtocolPtr OPTIONAL)
{
    EFI_STATUS Status = 0;
    LANENET_DRIVER* LanDriverPtr;
    INT32 timeout = 999;
    EFI_TPL SavedTpl;
    INT32 k = 0;
    UINT16 DefaultProtocol = (UINT16)0x0806;
    volatile ENET_BD* TxBDPtr = NULL;
    volatile UINT8* TxBufferPtr = NULL;
    volatile UINT8* ByteMemPtr = NULL;
    volatile UINT8* TempByteMemPtr = NULL;

    ENET_INFO("++SnpTransmit(size=%d, DataPtr=%08Xh)\r\n", BuffSize,DataPtr);

    // Check preliminaries

    if((SnpPtr == NULL) || (DataPtr == NULL))
    {
        ENET_ERROR("--SnpTransmit() null ptr(s)\r\n");
        return EFI_INVALID_PARAMETER;
    }

    SavedTpl = gBS->RaiseTPL(ENETIMX6_TPL);
    LanDriverPtr = INSTANCE_FROM_SNP_THIS(SnpPtr);
    TxBDPtr = LanDriverPtr->SendBDBPtrs[LanDriverPtr->tbd_index];
    TxBufferPtr = LanDriverPtr->TxBuffersPtr[LanDriverPtr->tbd_index];

    // Check that driver was started and initialised

    if(SnpPtr->Mode->State == EfiSimpleNetworkStarted) 
    {
        ENET_ERROR("TX - Warning: LANENET Driver not initialized\n");
        Status = EFI_DEVICE_ERROR;
        goto SnpSendDone;
    }
    else if(SnpPtr->Mode->State == EfiSimpleNetworkStopped)
    {
        ENET_ERROR("TX - Warning: LANENET Driver in stopped state\n");
        Status = EFI_NOT_STARTED;
        goto SnpSendDone;
    }

    // Check validity of BufferSize

    if(BuffSize < SnpPtr->Mode->MediaHeaderSize)
    {
        ENET_ERROR("SnpTransmit(size=%d) buffer too small for data\r\n", BuffSize);
        Status = EFI_BUFFER_TOO_SMALL;
        goto SnpSendDone;
    }

    // Before transmitting check the link Status

    if(CheckLinkStatus(SnpPtr) != EFI_SUCCESS)
    {
        ENET_ERROR("SnpTransmit() cannot send - NO Link \r\n");
        Status = EFI_NOT_READY;
        goto SnpSendDone;
    }

    // check vald length of data

    if(BuffSize > ETHER_FRAME_MAX_LENGTH || BuffSize <= 0)
    {
        ENET_ERROR("SnpTransmit() cannot send - packet too small or too big \r\n");
        Status = EFI_INVALID_PARAMETER;        
        goto SnpSendDone;
    }

    ByteMemPtr=(volatile UINT8*)(TxBufferPtr);

    ENET_INFO("SnpTransmit() Tx buffer ptr=%08Xh for TxBD[%d]\r\n",TxBufferPtr,LanDriverPtr->tbd_index);

    // Ensure header is correct size if non-zero

    if(HdrSize != 0) 
    {
        if (HdrSize != SnpPtr->Mode->MediaHeaderSize)
        {
            ENET_ERROR("SnpTransmit(ERR) incorrect header size\r\n");
            Status = EFI_INVALID_PARAMETER;
            goto SnpSendDone;
        }

        // destination address and protocol must be provided

        if ((DstAddr == NULL) || (ProtocolPtr == NULL))
        {
            ENET_ERROR("SnpTransmit(ERR) ivalid destination address or protocol\r\n");
            Status = EFI_INVALID_PARAMETER;
            goto SnpSendDone;
        }

        ENET_INFO(" SnpTransmit() header size=%d\r\n", HdrSize);

        // ***  we need to populate all header fields ****

        // Write the destination address

        CopyMem((UINT8*)ByteMemPtr, DstAddr, NET_ETHER_ADDR_LEN); // 0-5; is not sizeof(EFI_MAC_ADDRESS))
        ByteMemPtr += NET_ETHER_ADDR_LEN;

        // source address may or may not be provided.
        // NOTE: If HeaderSize is nonzero and SrcAddr is NULL, then SnpPtr->Mode->CurrentAddress is used for the source HW MAC address.

        if(SrcAddr == NULL) 
        {        
            SrcAddr = (EFI_MAC_ADDRESS*)&SnpPtr->Mode->CurrentAddress;
            ENET_INFO("SnpTransmit() no src addr given, use current\r\n");
        }

        // Write the Source Address

        CopyMem((UINT8*)ByteMemPtr, SrcAddr, NET_ETHER_ADDR_LEN); // 6-11
        ByteMemPtr += NET_ETHER_ADDR_LEN;

        // Write the Protocol

        UINT16 Prot=HTONS(*ProtocolPtr);
        CopyMem((UINT8*)ByteMemPtr, &Prot, sizeof(UINT16)); // 12-13
        
        ENET_INFO("SnpSend - copied caller's prot %04Xh\r\n", *(UINT16*)ByteMemPtr);
        
        ByteMemPtr += sizeof(UINT16); 

        // Next is the payload - copy from Data

        CopyMem((UINT8*)ByteMemPtr,(UINT8*)((UINT32)DataPtr+HdrSize), BuffSize-HdrSize);
    }
    else
    {
        ENET_INFO(" SnpTransmit() header size=0\r\n");

        // just write entire Data buffer as given into ethernet frame

        // src - arbitrary unaligned buffer  
        // dest - cache-aligned buffer. 

        CopyMem((UINT8*)ByteMemPtr, (UINT8*)DataPtr, BuffSize);

        ByteMemPtr += NET_ETHER_ADDR_LEN;
        SrcAddr = (EFI_MAC_ADDRESS*)ByteMemPtr;

        if(*ByteMemPtr == 0x0 && *(ByteMemPtr+1) == 0x0 && *(ByteMemPtr+2) == 0x0 && *(ByteMemPtr+3) == 0x0 && 
                *(ByteMemPtr+4) == 0x0 && *(ByteMemPtr+5) == 0x0 )
        {
            ENET_INFO("SnpSend - caller gave unconfigured MAC address, use current instead\r\n");
            SrcAddr = (EFI_MAC_ADDRESS*)&SnpPtr->Mode->CurrentAddress;
            CopyMem((UINT8*)ByteMemPtr, SrcAddr, NET_ETHER_ADDR_LEN); // 6-11
        }
    }

    // ethernet frame is now prepared for sending out
    // print frame properties for debug

    DstAddr = (EFI_MAC_ADDRESS*)TxBufferPtr;

    SrcAddr = (EFI_MAC_ADDRESS*)((UINT32)TxBufferPtr + NET_ETHER_ADDR_LEN);

    ProtocolPtr = (UINT16*)((UINT32)TxBufferPtr + 2 * NET_ETHER_ADDR_LEN);

    // Check for the nature of the frame

    if((DstAddr->Addr[0] & 0x1) == 1)
    {
        LanDriverPtr->Stats.TxMulticastFrames += 1;
    }
    else
    {
        LanDriverPtr->Stats.TxUnicastFrames += 1;
    }

    // Check if broadcast

    if(DstAddr->Addr[0] == 0xFF)
    {
        LanDriverPtr->Stats.TxBroadcastFrames += 1;
    }

    // set new values into current TxBD - data length of frame to send

    TxBDPtr->DataLen = (UINT16)BuffSize;

    ENET_SEND(" SEND {%02X:%02X:%02X:%02X:%02X:%02X}->{%02X:%02X:%02X:%02X:%02X:%02X} prot=%d len=%d\r\n",
                                SrcAddr->Addr[0],SrcAddr->Addr[1],SrcAddr->Addr[2], SrcAddr->Addr[3],SrcAddr->Addr[4],SrcAddr->Addr[5],
                                DstAddr->Addr[0],DstAddr->Addr[1],DstAddr->Addr[2], DstAddr->Addr[3],DstAddr->Addr[4],DstAddr->Addr[5],
                                *ProtocolPtr, TxBDPtr->DataLen);

    // set control Status flags:
    // this TxBD is last in chain always
    // and should transmit CRC

    TxBDPtr->ControlStatus &=  BD_ENET_TX_WRAP;
    TxBDPtr->ControlStatus |= (BD_ENET_TX_LAST | BD_ENET_TX_TC | BD_ENET_TX_READY);

    // note from u-boot
    // perform dumb read from TxBD so that write operations complete before sDMA starts

    Status = *(UINT32*)((UINT32)TxBDPtr + sizeof(ENET_BD) - 4);

    // NOTE from NXP
    // execute dsb SY before setting TDAR bit 

    asm volatile("dsb sy");

    // now mark this block descriptor as ready for transmission by uDMA

    MmioWrite32((UINT32)&LanDriverPtr->enetRegisters->TDAR, BIT24);

    // wait until uDMA will get over it
    // option - to improve performance perform this check in SnpGetStatus()

    while(timeout != 0)
    {
        // This bit is cleared by the MAC device when no additional ready descriptors remain in the transmit ring.

        if( (MmioRead32((UINT32)&LanDriverPtr->enetRegisters->TDAR) & BIT24) == 0)
        {
            ENET_INFO("SnpTransmit() frame sent.\r\n");
            break;
        }
        MicroSecondDelay(10);
        timeout -= 1;
    }

    if(timeout == 0)
    {
        Status = EFI_TIMEOUT;
        ENET_ERROR("SnpTransmit() - timeout\r\n");
    }
    else
    {
        // check for completion - sDMA must clear BD_ENET_TX_READY flag in current TxBD

        if((TxBDPtr->ControlStatus & BD_ENET_TX_READY) == 0)
        {
            Status = EFI_SUCCESS;
            LanDriverPtr->Stats.TxGoodFrames += 1;

            // Save the address of the submitted packet so we can notify the consumer that
            // it has been sent in GetStatus. When the packet tag appears in the Tx Status
            // Fifo, we will return Buffer in the TxBuff parameter of GetStatus.

            LanDriverPtr->TxBuffCallerPtrs[LanDriverPtr->tbd_index] = (UINT8*)DataPtr;
            ENET_INFO("SnpTransmit() TxBD[%d] has caller buffer at %08Xh\r\n",LanDriverPtr->tbd_index, 
                    LanDriverPtr->TxBuffCallerPtrs[LanDriverPtr->tbd_index]);
        }
        else
        {
            // something did work
            // check for send errors wil be done in SnpCheckStatus()

            ENET_ERROR("SnpTransmit(ERR) failed, TX_READY flag Not cleared! sts=%04Xh after send\r\n", TxBDPtr->ControlStatus);
            Status = EFI_DEVICE_ERROR;
        }        
    }
    
    // clear current TxBD descriptor
    // for the next transmission use the other buffer

    if(LanDriverPtr->tbd_index != 0)
    {
        CleanOneBlockDescriptor_Tx(TxBDPtr,TRUE);
        LanDriverPtr->tbd_index = 0;
    }
    else
    {
        CleanOneBlockDescriptor_Tx(TxBDPtr,FALSE);
        LanDriverPtr->tbd_index = 1;
    }

SnpSendDone:
    gBS->RestoreTPL(SavedTpl);
    ENET_INFO("--SnpTransmit(TxBD idx=%d)=%Xh\r\n", LanDriverPtr->tbd_index,Status);
    return Status;
}
