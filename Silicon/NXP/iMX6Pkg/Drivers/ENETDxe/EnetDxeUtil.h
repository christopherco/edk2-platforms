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


#ifndef __IMX6ENET_DXE_UTIL_H__
#define __IMX6ENET_DXE_UTIL_H__

// iMX6 data cache alignment for ENET buffers. 
#define IMX6_CACHE_ALIGN_SIZE 128 // in bits

typedef struct _LANENET_DEVICE_PATH
{
    MAC_ADDR_DEVICE_PATH LANENET;
    EFI_DEVICE_PATH_PROTOCOL End;
} LANENET_DEVICE_PATH;

// PHY Registers Access functions

// Read from MII register (PHY Access)
EFI_STATUS PHYRead32(IN LANENET_DRIVER* LanDriverPtr, UINT32 Index, UINT32* ResultPtr);

// Write to the MII register (PHY Access)
EFI_STATUS PHYWrite32(IN LANENET_DRIVER* LanDriverPtr, UINT32 Index, UINT32 Value);

// General Operations

UINT8 GenerateHash(IN EFI_MAC_ADDRESS* Mac);
VOID DumpPHYRegs(IN LANENET_DRIVER* LanDriverPtr);
VOID DumpEnetRegs(IN LANENET_DRIVER* LanDriverPtr);

VOID EnetSetMacAddress(IN LANENET_DRIVER* LanDriverPtr, IN EFI_MAC_ADDRESS* MacPtr);
VOID EnetGetMacAddressFromFuses(IN EFI_SIMPLE_NETWORK_PROTOCOL* SnpPtr, OUT EFI_MAC_ADDRESS* MacPtr);

EFI_STATUS AllocAdapterMemory(IN EFI_SIMPLE_NETWORK_PROTOCOL* SnpPtr);
EFI_STATUS ReleaseAdapterMemory(IN EFI_SIMPLE_NETWORK_PROTOCOL* SnpPtr);

// intialize and set up Enet controller - fully prepare for use but leave it disabled
EFI_STATUS InitializeAndSetupEnetController(IN EFI_SIMPLE_NETWORK_PROTOCOL* SnpPtr);
// perform re/init steps and enable controller
EFI_STATUS RestartEnetController(IN EFI_SIMPLE_NETWORK_PROTOCOL* SnpPtr);

#define MMI_DATA_MASK 0xFFFF

// Check the Link Status and take appropriate action
EFI_STATUS CheckLinkStatus(IN EFI_SIMPLE_NETWORK_PROTOCOL* Snp);

EFI_STATUS DisableEnetController(IN LANENET_DRIVER* LanDriverPtr);
EFI_STATUS EnableEnetController(IN LANENET_DRIVER* LanDriverPtr);

EFI_STATUS StartReceiver(IN LANENET_DRIVER* LanDriverPtr);
EFI_STATUS StopReceiver(IN LANENET_DRIVER* LanDriverPtr);
EFI_STATUS StartTransmitter(IN LANENET_DRIVER* LanDriverPtr);
EFI_STATUS StopTransmitter(IN LANENET_DRIVER* LanDriverPtr);

// Ethernet packet length definitions
#define ETHER_FRAME_MAX_PAYLOAD_LENGTH   1500  // Maximal Ethernet frame data payload size
#define ETHER_FRAME_MIN_PAYLOAD_LENGTH     46  // Minimal Ethernet frame data payload size
#define ETHER_FRAME_CRC_LENGTH              4  // Size of Ethernet frame CRC
#define ETHER_FRAME_MAX_LENGTH           1536  // Maximal Ethernet frame size (sum of header, payload and CRC)
#define ETHER_FRAME_MIN_LENGTH             64  // Minimal Ethernet frame size (sum of header, payload and CRC)

#endif // __IMX6ENET_DXE_UTIL_H__
