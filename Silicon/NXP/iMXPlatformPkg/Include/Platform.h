/** @file
*
*  Copyright (c) Microsoft Corporation. All rights reserved.
*
*  This program and the accompanying materials
*  are licensed and made available under the terms and conditions of the BSD License
*  which accompanies this distribution.  The full text of the license may be found at
*  http://opensource.org/licenses/bsd-license.php
*
*  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
*  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
*
**/
//
//  Freescale i.MX Platform specific defines for constructing ACPI tables
//

#ifndef _PLATFORM_IMX_H_
#define _PLATFORM_IMX_H_

#include <IndustryStandard/Acpi50.h>

#define EFI_ACPI_OEM_ID                         {'M','C','R','S','F','T'}   // OEMID 6 bytes long

#define EFI_ACPI_VENDOR_ID                      SIGNATURE_32('M','S','F','T')
#define EFI_ACPI_CSRT_REVISION                  0x00000005

#define EFI_ACPI_5_0_CSRT_REVISION              0x00000000

//
// Resource Descriptor Types
//

#define EFI_ACPI_CSRT_RD_TYPE_INTERRUPT 1
#define EFI_ACPI_CSRT_RD_TYPE_TIMER 2
#define EFI_ACPI_CSRT_RD_TYPE_DMA 3
#define EFI_ACPI_CSRT_RD_TYPE_CACHE 4

//
// Resource Descriptor Subtypes
//

#define EFI_ACPI_CSRT_RD_SUBTYPE_INTERRUPT_LINES 0
#define EFI_ACPI_CSRT_RD_SUBTYPE_INTERRUPT_CONTROLLER 1
#define EFI_ACPI_CSRT_RD_SUBTYPE_TIMER 0
#define EFI_ACPI_CSRT_RD_SUBTYPE_DMA_CHANNEL 0
#define EFI_ACPI_CSRT_RD_SUBTYPE_DMA_CONTROLLER 1
#define EFI_ACPI_CSRT_RD_SUBTYPE_CACHE 0

//
// Fixed device IDs
//

#define EFI_ACPI_CSRT_DEVICE_ID_DMA 0x00000009

#pragma pack(push, 1)

//------------------------------------------------------------------------
// CSRT Resource Group header 24 bytes long
//------------------------------------------------------------------------
typedef struct
{
   UINT32 Length;           // Length
   UINT32 VendorID;         // 4 bytes
   UINT32 SubVendorId;         // 4 bytes
   UINT16 DeviceId;         // 2 bytes
   UINT16 SubdeviceId;         // 2 bytes
   UINT16 Revision;         // 2 bytes
   UINT16 Reserved;         // 2 bytes
   UINT32 SharedInfoLength;   // 4 bytes
} EFI_ACPI_5_0_CSRT_RESOURCE_GROUP_HEADER;

//------------------------------------------------------------------------
// CSRT Resource Descriptor 12 bytes total
//------------------------------------------------------------------------
typedef struct
{
   UINT32 Length;       // 4 bytes
   UINT16 ResourceType; // 2 bytes
   UINT16 ResourceSubType; // 2 bytes
   UINT32 UID;          // 4 bytes
} EFI_ACPI_5_0_CSRT_RESOURCE_DESCRIPTOR_HEADER;

#pragma pack (pop)

#endif // !_PLATFORM_IMX_H_
