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

    Enet_filters.c

Abstract:

    implements Ethernet MAC (ENET) MAC filter related functions
*/

#include "EnetDxe.h"
#include <iMX6.h>
#include <iMX6ClkPwr.h>
#include <Library/TimerLib.h>

/*
    SnpReceiveFilters
    
This function is used enable and disable the hardware and software receive filters for the underlying
network device.
The receive filter change is broken down into three steps:
    The filter mask bits that are set (ON) in the Enable parameter are added to the current receive filter settings.
    The filter mask bits that are set (ON) in the Disable parameter are subtracted from the updated receive filter settings.
    If the resulting receive filter setting is not supported by the hardware a more liberal setting is selected.

Arguments:

    SnpPtr           A pointer to the EFI_SIMPLE_NETWORK_PROTOCOLinstance.
    Enable           A bit mask of receive filters to enable.
    Disable          A bit mask of receive filters to disable.
    ResetMCastFilter Set to TRUE to reset the contents of the multicast
                                receive filters on the network interface to
                                their default values.
    MCastFilterCnt    Number of multicast HW MAC addresses in the new
                                MCastFilter list. This value must be less than or
                                equal to the MCastFilterCnt field of
                                EFI_SIMPLE_NETWORK_MODE. This field is optional if
                                ResetMCastFilter is TRUE.
    MCastFilter       A pointer to a list of new multicast receive
                                filter HW MAC addresses. This list will replace
                                any existing multicast HW MAC address list. This
                                field is optional if ResetMCastFilter is TRUE.
return values

    EFI_SUCCESS            The receive filters of the LANENET were updated.
    EFI_NOT_STARTED        The ENET has not been started.
    EFI_INVALID_PARAMETER  One or more of the following conditions is TRUE :
                                  . This is NULL
                                  . Multicast is being enabled (the EFI_SIMPLE_NETWORK_RECEIVE_MULTICAST bit is set in
                                        Enable, it is not set in Disable, and ResetMCastFilter
                                        is FALSE) and MCastFilterCount is zero.
                                  . Multicast is being enabled and MCastFilterCount is greater than Snp->Mode->MaxMCastFilterCount.
                                  . Multicast is being enabled and MCastFilter is NULL
                                  . Multicast is being enabled and one or more of the addresses in the MCastFilter list are not valid
                                        multicast MAC addresses.
    EFI_DEVICE_ERROR       The ENET has been started but not initialized.

*/
EFI_STATUS EFIAPI SnpReceiveFilters(IN  EFI_SIMPLE_NETWORK_PROTOCOL* SnpPtr,
                                    IN  UINT32 Enable,
                                    IN  UINT32 Disable,
                                    IN  BOOLEAN ResetMCastFilter,
                                    IN  UINTN MCastFilterCnt OPTIONAL,
                                    IN  EFI_MAC_ADDRESS* MCastFilterPtr OPTIONAL)
{
    EFI_SIMPLE_NETWORK_MODE* Mode;
    UINT32 Count;
    UINT32 Crc;
    LANENET_DRIVER* LanDriverPtr;
    UINT32 ReceiveFilterSetting;
    EFI_MAC_ADDRESS* Mac;
    EFI_MAC_ADDRESS ZeroMac;
    EFI_TPL SavedTpl;
    EFI_STATUS Status = 0;
    UINT8 UnicastHashValue = 0;
    UINT8 MulticastHashValue = 0;

    ENET_INFO("++SnpReceiveFilters(en=%08Xh dis=%08Xh resetMCst=%d MCstFltCnt=%d MCastFltPtr=%p)\r\n",Enable,Disable,ResetMCastFilter,MCastFilterCnt,MCastFilterPtr);

    // Check Snp Instance

    if(SnpPtr == NULL)
    {
        ENET_ERROR("--SnpReceiveFilters() invalid parameter\r\n");
        return EFI_INVALID_PARAMETER;
    }

    SavedTpl = gBS->RaiseTPL(ENETIMX6_TPL);
    Mode = SnpPtr->Mode;
    LanDriverPtr = INSTANCE_FROM_SNP_THIS(SnpPtr);

    // Check that driver was started and initialised

    if(Mode->State == EfiSimpleNetworkStarted)
    {
        ENET_ERROR(" Error SnpReceiveFilters Driver not initialized\r\n");
        Status = EFI_DEVICE_ERROR;
        goto SnpRecvFltrDone;
    }
    else if(Mode->State == EfiSimpleNetworkStopped)
    {
        ENET_ERROR(" Error SnpReceiveFilters Driver in stopped state\r\n");
        Status = EFI_NOT_STARTED;
        goto SnpRecvFltrDone;
    }

    if((Enable  & (~Mode->ReceiveFilterMask)) || (Disable & (~Mode->ReceiveFilterMask))  )
    {
        ENET_ERROR(" Error SnpReceiveFilters invalid parameter Enable or Disable\r\n");
        Status = EFI_INVALID_PARAMETER;
        goto SnpRecvFltrDone;
    }

    // Before to change anything, stop the reception of packets.

    StopReceiver(LanDriverPtr);

    // erase MAC filter first if they have reset flag set

    if(ResetMCastFilter == TRUE)
    {
        ENET_MAC(" SnpReceiveFilters Resetting Multicast filter\r\n");
        Mode->MCastFilterCount = 0;
        MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->GAUR, 0);
        MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->GALR, 0);
        ENET_INFO(" SnpReceiveFilters Multicast wrote hash 000 000 to GA*R regs\r\n");
    }

    // Check the validity of the multicast setting and compute the
    // hash values of the multicast mac addresses to listen to.

    if(((Disable & EFI_SIMPLE_NETWORK_RECEIVE_MULTICAST) == 0) && 
        ((Enable  & EFI_SIMPLE_NETWORK_RECEIVE_MULTICAST) != 0) )
    {
        if((MCastFilterCnt == 0) || (MCastFilterCnt > Mode->MaxMCastFilterCount) || (MCastFilterPtr == NULL))
        {
            ENET_ERROR(" Error SnpReceiveFilters invalid parameter MCastFilterCnt and MCastFilterPtr is nul\r\n");
            Status = EFI_INVALID_PARAMETER;
            goto SnpRecvFltrDone;
        }

        // Check the validity of all multicast addresses before to change anything.

        for(Count = 0; Count < MCastFilterCnt; Count++)
        {
            if ((MCastFilterPtr[Count].Addr[0] & 1) == 0)
            {
                ENET_ERROR(" Error SnpReceiveFilters found invalid multicast address[%d]\r\n", Count);
                Status = EFI_INVALID_PARAMETER;
                goto SnpRecvFltrDone;
            }
        }

        ZeroMem(&Mode->MCastFilter[0], sizeof(EFI_MAC_ADDRESS) * MCastFilterCnt);

        // Go through each filter address and set appropriate bits on multicast hash registers

        for(Count = 0; Count < MCastFilterCnt; Count++)
        {
            Mac = &(MCastFilterPtr[Count]);
            ENET_MAC(" SnpReceiveFilters  adding MCast address[%d]=%02X-%02X-%02X-%02X-%02X-%02X to filter\r\n", Count,
                        Mac->Addr[0],Mac->Addr[1],Mac->Addr[2],Mac->Addr[3],Mac->Addr[4],Mac->Addr[5]);
            CopyMem(&Mode->MCastFilter[Count], Mac, sizeof(EFI_MAC_ADDRESS));

            MulticastHashValue = GenerateHash(Mac);

            // GAUR contains the upper 32 bits of the 64-bit hash table used in the address recognition
            // process for receive frames with a multicast address. You must initialize this register.
        
            if(MulticastHashValue > 31)
            {
                MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->GAUR, (1 << (MulticastHashValue - 32)) |
                            MmioRead32((UINTN)&LanDriverPtr->enetRegisters->GAUR) );
            }
            else
            {
                MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->GALR, (1 << MulticastHashValue) | 
                            MmioRead32((UINTN)&LanDriverPtr->enetRegisters->GALR) );    
            }
        }

        Mode->MCastFilterCount = MCastFilterCnt;
        ENET_INFO(" SnpReceiveFilters Multicast writing hash %04Xh to ENET regs\r\n", MulticastHashValue);

    }

    ENET_INFO(" SnpReceiveFilters Multicast read hash %08X %08Xh from GA*R regs\r\n",
                MmioRead32((UINTN)&LanDriverPtr->enetRegisters->GAUR),
                MmioRead32((UINTN)&LanDriverPtr->enetRegisters->GALR));

    // Write the mask of the selected hash values for the multicast filtering.
    // The two masks are set to zero if the multicast filtering is not enabled.

    ReceiveFilterSetting = (Mode->ReceiveFilterSetting | Enable) & (~Disable);
 
    if(ReceiveFilterSetting & EFI_SIMPLE_NETWORK_RECEIVE_UNICAST)
    {
        ENET_MAC(" SnpReceiveFilters Allowing Unicast Frame Reception - use current MAC address\r\n");
        CopyMem(&Mode->CurrentAddress, &mZeroMac, NET_ETHER_ADDR_LEN);
        EnetSetMacAddress(LanDriverPtr, &Mode->CurrentAddress);
        ENET_MAC(" SnpReceiveFilters Allowing Unicast Frame Reception - set hash into IA*R\r\n");

        // Add Enet MAC address and set appropriate bits on unicast hash table

        Mac = (EFI_MAC_ADDRESS*)&(mZeroMac[0]);
        ENET_MAC(" SnpReceiveFilters  adding UniCast address=%02X-%02X-%02X-%02X-%02X-%02X to filter\r\n",
                    Mac->Addr[0],Mac->Addr[1],Mac->Addr[2],Mac->Addr[3],Mac->Addr[4],Mac->Addr[5]);

        // The most significant 6 bits of the MAC address CRC constitute the hash
        // value of the MAC address.

        UnicastHashValue = GenerateHash(Mac);

        if(UnicastHashValue > 31)
        {
            MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->IAUR,  (0x1 << (UnicastHashValue - 32)) );
        }
        else
        {
             MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->IALR, (0x1 << UnicastHashValue) );
        }

        ENET_MAC(" SnpReceiveFilters wrote hash %08Xh %08Xh to IA*R regs\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->IAUR),
                    MmioRead32((UINTN)&LanDriverPtr->enetRegisters->IALR) );
    } 
    else
    {
        ENET_MAC(" SnpReceiveFilters Not allow Unicast Frame Reception - set 0000000 as MAC address\r\n");

        // The Unicast packets do not have to be listen to, set the MAC
        // address of the LANENET to be the "not configured" all zeroes
        // ethernet MAC address.

        ZeroMem(&Mode->CurrentAddress, NET_ETHER_ADDR_LEN);
        EnetSetMacAddress(LanDriverPtr, &Mode->CurrentAddress);
        ENET_INFO(" SnpReceiveFilters Not allow Unicast Frame Reception - set IA*R regs to 0000000\r\n");
        MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->IAUR, 0);
        MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->IALR, 0);
    }

    if(ReceiveFilterSetting & EFI_SIMPLE_NETWORK_RECEIVE_MULTICAST)
    {
        ENET_MAC(" SnpReceiveFilters Allowing Multicast Frame Reception\r\n");
    }
    else
    {
        ENET_MAC(" SnpReceiveFilters Not allowing Multicast Frame Reception\r\n");
    }

    if(ReceiveFilterSetting & EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS_MULTICAST)
    {
        ENET_MAC(" SnpReceiveFilters Enabling Promiscuous Multicast Mode\r\n");
    }
    else
    {
        ENET_MAC(" SnpReceiveFilters Disabling Promiscuous Multicast Mode\r\n");
    }

    if((ReceiveFilterSetting & EFI_SIMPLE_NETWORK_RECEIVE_BROADCAST) == 0)
    {
         ENET_MAC(" SnpReceiveFilters Not allowing Broadcast Frame Reception\r\n");
    }
    else
    {
        ENET_MAC(" SnpReceiveFilters Allowing Broadcast Frame Reception\r\n");
    }

    if(ReceiveFilterSetting & EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS) 
    {
        ENET_MAC(" SnpReceiveFilters Enabling Promiscuous Receive Mode\r\n");
    }
    else
    {
        ENET_MAC(" SnpReceiveFilters Disabling Promiscuous Receive Mode\r\n");
    }

    StartReceiver(LanDriverPtr);

    Status = EFI_SUCCESS;

SnpRecvFltrDone:
    gBS->RestoreTPL(SavedTpl);
    ENET_INFO("--SnpReceiveFilters()=%Xh\r\n", Status);
    return Status;
}
