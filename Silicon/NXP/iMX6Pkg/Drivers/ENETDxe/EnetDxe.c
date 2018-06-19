/*

Copyright (c) 2012-2014, ARM Limited. All rights reserved.
Copyright (c) Microsoft Corporation. All rights reserved.

This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
*/

/*
  EnetDxe.c

Abstract:

    Implements the Simple Network Protocol is as follows:

Add global variable for the EFI_SIMPLE_NETWORK_PROTOCOL instance to SimpleNetworkProtocol.
Create child handle in Driver Binding Protocol Start() and install the Simple Network Protocol and the Device Path Protocol. 
Also allocate and initialize an EFI_SIMPLE_NETWORK_MODE structure in the Simple Network Protocol.
Implement the Simple Network Protocol services.
Create an Exit Boot Services Event to disable DMA when packets are received.
*/

#include "EnetDxe.h"
#include <iMX6.h>
#include <iMX6ClkPwr.h>
#include <Library/TimerLib.h>

LANENET_DEVICE_PATH LANENETPathTemplate =  
{
    {
        {
            MESSAGING_DEVICE_PATH, MSG_MAC_ADDR_DP,
            { (UINT8) (sizeof(MAC_ADDR_DEVICE_PATH)), (UINT8) ((sizeof(MAC_ADDR_DEVICE_PATH)) >> 8) }
        },
        {
            { 0 } 
        }, 0 
    },
    {
        END_DEVICE_PATH_TYPE,
        END_ENTIRE_DEVICE_PATH_SUBTYPE,
        { sizeof(EFI_DEVICE_PATH_PROTOCOL), 0 }
    }
};

/*
  Entry point for the iMX6 ENET UEFI driver

Arguments:
    Handle          The firmware allocated handle for the UEFI image.
    SystemTable     A pointer to the EFI System Table.

Returns:
    EFI_SUCCESS           The operation completed successfully.
    EFI_OUT_OF_RESOURCES  The request could not be completed due to a lack of resources.

*/
EFI_STATUS EnetDxeEntry(IN EFI_HANDLE Handle, IN EFI_SYSTEM_TABLE* SystemTable)
{
    EFI_STATUS Status;
    LANENET_DRIVER* LanDriver;
    EFI_SIMPLE_NETWORK_PROTOCOL* Snp;
    EFI_SIMPLE_NETWORK_MODE* SnpMode;
    LANENET_DEVICE_PATH* LANENETPath;
    EFI_HANDLE ControllerHandle;
    ENET_INFO("+EnetDxeEntry()\r\n");

    // Allocate Resources

    LanDriver = AllocateZeroPool(sizeof(LANENET_DRIVER));
    if (LanDriver == NULL) 
    {
        ENET_ERROR("--EnetDxeEntry()=no res1\r\n");
        return EFI_OUT_OF_RESOURCES;
    }

    LANENETPath = (LANENET_DEVICE_PATH*)AllocateCopyPool(sizeof(LANENET_DEVICE_PATH), &LANENETPathTemplate);

    if(LANENETPath == NULL)
    {
        FreePool(LanDriver);
        ENET_ERROR("--EnetDxeEntry()=no res2\r\n");
        return EFI_OUT_OF_RESOURCES;
    }

    // Initialize pointers

    LanDriver->enetRegisters = (IMX6_ENET_REGISTERS*)IMX_ENET_BASE;
    Snp = &(LanDriver->Snp);
    SnpMode = &(LanDriver->SnpMode);
    Snp->Mode = SnpMode;

    // Set the signature of the LAN Driver structure

    LanDriver->Signature = LANENET_SIGNATURE;

    // allocate circular buffers for descriptors and individual buffers linked to them

    Status = AllocAdapterMemory(Snp);
    if(Status != EFI_SUCCESS) 
    {
        ENET_ERROR("EnetDxeEntry: Error out of memory in EnetAllocAdapterMemory\r\n");
        return EFI_OUT_OF_RESOURCES;
    }

    // Assign fields and function pointers

    Snp->Revision = EFI_SIMPLE_NETWORK_PROTOCOL_REVISION;
    Snp->WaitForPacket = NULL;              // blocking call - not supported
    Snp->Initialize = SnpInitialize;
    Snp->Start = SnpStart;
    Snp->Stop = SnpStop;
    Snp->Reset = SnpReset;
    Snp->Shutdown = SnpShutdown;
    Snp->ReceiveFilters = SnpReceiveFilters;
    Snp->StationAddress = SnpStationAddress;
    Snp->Statistics = SnpStatistics;
    Snp->MCastIpToMac = SnpMcastIptoMac;
    Snp->NvData = SnpNvData;                // not supported - return from function
    Snp->GetStatus = SnpGetStatus;
    Snp->Transmit = SnpTransmit;
    Snp->Receive = SnpReceive;

    // Start completing simple network mode structure

    SnpMode->State = EfiSimpleNetworkStopped;
    SnpMode->HwAddressSize = NET_ETHER_ADDR_LEN;    // HW address is 6 bytes
    SnpMode->MediaHeaderSize = sizeof(ETHER_HEAD);  //
    SnpMode->MaxPacketSize = EFI_PAGE_SIZE;         // Preamble + SOF + Ether Frame (with VLAN tag + 4bytes)
    SnpMode->NvRamSize = 0;                         // No NVRAM with this device
    SnpMode->NvRamAccessSize = 0;                   // No NVRAM with this device

    // Claim that all receive filter settings are supported, though the MULTICAST mode
    // is not completely supported. The LANENET Ethernet controller is only able to
    // do a "hash filtering" and not a perfect filtering on multicast addresses. The
    // controller does not filter the multicast addresses directly but a hash value
    // of them. The hash value of a multicast address is derived from its CRC and
    // ranges from 0 to 63 included.
    // We claim that the perfect MULTICAST filtering mode is supported because
    // we do not want the user to switch directly to the PROMISCOUS_MULTICAST mode
    // and thus not being able to take advantage of the hash filtering.

    SnpMode->ReceiveFilterMask = EFI_SIMPLE_NETWORK_RECEIVE_UNICAST |
                                EFI_SIMPLE_NETWORK_RECEIVE_MULTICAST |
                                EFI_SIMPLE_NETWORK_RECEIVE_BROADCAST |
                                EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS |
                                EFI_SIMPLE_NETWORK_RECEIVE_PROMISCUOUS_MULTICAST;

    // We do not intend to receive anything for the time being.

    SnpMode->ReceiveFilterSetting = 0;

    // LANENET has 64bit hash table, can filter 64 MCast MAC Addresses

    SnpMode->MaxMCastFilterCount = MAX_MCAST_FILTER_CNT;
    SnpMode->MCastFilterCount = 0;
    ZeroMem(&SnpMode->MCastFilter, MAX_MCAST_FILTER_CNT * sizeof(EFI_MAC_ADDRESS));

    // Set the interface type (1: Ethernet or 6: IEEE 802 Networks)

    SnpMode->IfType = NET_IFTYPE_ETHERNET;

    // Mac address is changeable as it is loaded from erasable memory

    SnpMode->MacAddressChangeable = TRUE;

    // Can only transmit one packet at a time

    SnpMode->MultipleTxSupported = FALSE;

    // MediaPresent checks for cable connection and partner link

    SnpMode->MediaPresentSupported = TRUE;
    SnpMode->MediaPresent = FALSE;

    // Set broadcast address

    SetMem(&SnpMode->BroadcastAddress, sizeof(EFI_MAC_ADDRESS), 0xFF);

    // Assign fields for device path

    CopyMem(&LANENETPath->LANENET.MacAddress, &Snp->Mode->CurrentAddress, NET_ETHER_ADDR_LEN);
    LANENETPath->LANENET.IfType = Snp->Mode->IfType;

    Status = InitializeAndSetupEnetController(Snp);

    if(EFI_ERROR(Status)) 
    {
        ENET_ERROR("--EnetDxeEntry: Error initialising NIC hardware\r\n");
        return EFI_DEVICE_ERROR;
    }

    // Initialize snp protocol

    ControllerHandle = NULL;

    Status = gBS->InstallMultipleProtocolInterfaces(&ControllerHandle,
                    &gEfiSimpleNetworkProtocolGuid, 
                    Snp,
                    &gEfiDevicePathProtocolGuid, 
                    LANENETPath,
                    NULL);

    // Say what the status of loading the protocol structure is

    if(EFI_ERROR(Status)) 
    {
        ENET_ERROR(" EnetDxeEntry() InstallMultipleProtocolInterfaces failed! Err=%Xh\r\n", Status);
        FreePool(LanDriver);
    }
    else 
    {
        LanDriver->ControllerHandle = ControllerHandle;
    }

    ENET_INFO( "--EnetDxeEntry()=%Xh\r\n", Status);
    return Status;
}
