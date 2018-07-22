/** @file

  Copyright (c) 2012, Apple Inc. All rights reserved.<BR>
  Copyright (c) 2013 Linaro.org
  Copyright (c), Microsoft Corporation. All rights reserved.

  This program and the accompanying materials
  are licensed and made available under the terms and conditions of the BSD License
  which accompanies this distribution.  The full text of the license may be found at
  http://opensource.org/licenses/bsd-license.php

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

  Static SMBIOS Table for the SolidRun HummingBoard-Edge iMX6 Quad platform
  Derived from EmulatorPkg package

  Note SMBIOS 2.7.1 Required structures:
    BIOS Information (Type 0)
    System Information (Type 1)
    Board Information (Type 2)
    System Enclosure (Type 3)
    Processor Information (Type 4) - CPU Driver
    Cache Information (Type 7) - For cache that is external to processor
    System Slots (Type 9) - If system has slots
    Physical Memory Array (Type 16)
    Memory Device (Type 17) - For each socketed system-memory Device
    Memory Array Mapped Address (Type 19) - One per contiguous block per Physical Memroy Array
    System Boot Information (Type 32)

**/

#include <Protocol/Smbios.h>
#include <IndustryStandard/SmBios.h>
#include <Guid/SmBios.h>
#include <Library/DebugLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/IoLib.h>

SMBIOS_TABLE_TYPE0 mBIOSInfoType0 = {
  { EFI_SMBIOS_TYPE_BIOS_INFORMATION, sizeof (SMBIOS_TABLE_TYPE0), 0 },
  1,                    // Vendor String
  2,                    // BiosVersion String
  0xE000,               // BiosSegment
  3,                    // BiosReleaseDate String
  0x7F,                 // BiosSize
  {                     // BiosCharacteristics
    0,    //  Reserved                          :2;
    0,    //  Unknown                           :1;
    0,    //  BiosCharacteristicsNotSupported   :1;
    0,    //  IsaIsSupported                    :1;
    0,    //  McaIsSupported                    :1;
    0,    //  EisaIsSupported                   :1;
    0,    //  PciIsSupported                    :1;
    0,    //  PcmciaIsSupported                 :1;
    0,    //  PlugAndPlayIsSupported            :1;
    0,    //  ApmIsSupported                    :1;
    1,    //  BiosIsUpgradable                  :1;
    1,    //  BiosShadowingAllowed              :1;
    0,    //  VlVesaIsSupported                 :1;
    0,    //  EscdSupportIsAvailable            :1;
    0,    //  BootFromCdIsSupported             :1;
    1,    //  SelectableBootIsSupported         :1;
    0,    //  RomBiosIsSocketed                 :1;
    0,    //  BootFromPcmciaIsSupported         :1;
    0,    //  EDDSpecificationIsSupported       :1;
    0,    //  JapaneseNecFloppyIsSupported      :1;
    0,    //  JapaneseToshibaFloppyIsSupported  :1;
    0,    //  Floppy525_360IsSupported          :1;
    0,    //  Floppy525_12IsSupported           :1;
    0,    //  Floppy35_720IsSupported           :1;
    0,    //  Floppy35_288IsSupported           :1;
    0,    //  PrintScreenIsSupported            :1;
    0,    //  Keyboard8042IsSupported           :1;
    0,    //  SerialIsSupported                 :1;
    0,    //  PrinterIsSupported                :1;
    0,    //  CgaMonoIsSupported                :1;
    0,    //  NecPc98                           :1;
    0     //  ReservedForVendor                 :32;
  },
  {       // BIOSCharacteristicsExtensionBytes[]
    0x81, //  AcpiIsSupported                   :1;
          //  UsbLegacyIsSupported              :1;
          //  AgpIsSupported                    :1;
          //  I2OBootIsSupported                :1;
          //  Ls120BootIsSupported              :1;
          //  AtapiZipDriveBootIsSupported      :1;
          //  Boot1394IsSupported               :1;
          //  SmartBatteryIsSupported           :1;
    0x0e, //  BiosBootSpecIsSupported           :1;
          //  FunctionKeyNetworkBootIsSupported :1;
          //  TargetContentDistributionEnabled  :1;
          //  UefiSpecificationSupported        :1;
          //  VirtualMachineSupported           :1;
          //  ExtensionByte2Reserved            :3;
  },
  0x00,                    // SystemBiosMajorRelease
  0x01,                    // SystemBiosMinorRelease
  0xFF,                    // EmbeddedControllerFirmwareMajorRelease
  0xFF,                    // EmbeddedControllerFirmwareMinorRelease
};

CHAR8 *mBIOSInfoType0Strings[] = {
  "To be filled by O.E.M.", // Vendor String
  "0.1",                    // BiosVersion String
  __DATE__,                 // BiosReleaseDate String
  NULL
};

SMBIOS_TABLE_TYPE1 mSysInfoType1 = {
  { EFI_SMBIOS_TYPE_SYSTEM_INFORMATION, sizeof (SMBIOS_TABLE_TYPE1), 0 },
  1,    // Manufacturer String
  2,    // ProductName String
  3,    // Version String
  4,    // SerialNumber String
  { 0x25EF0280, 0xEC82, 0x42B0, { 0x8F, 0xB6, 0x10, 0xAD, 0xCC, 0xC6, 0x7C, 0x02 } },
  SystemWakeupTypePowerSwitch,
  5,    // SKUNumber String
  6,    // Family String
};
CHAR8  *mSysInfoType1Strings[] = {
  "SolidRun",
  "HummingBoard-Edge i4Pro",
  "2.0",
  "System Serial#",
  "hb04w-e-110-00-004-0",
  "edk2",
  NULL
};

SMBIOS_TABLE_TYPE2  mBoardInfoType2 = {
  { EFI_SMBIOS_TYPE_BASEBOARD_INFORMATION, sizeof (SMBIOS_TABLE_TYPE2), 0 },
  1,    // Manufacturer String
  2,    // ProductName String
  3,    // Version String
  4,    // SerialNumber String
  5,    // AssetTag String
  {     // FeatureFlag
    1,    //  Motherboard           :1;
    0,    //  RequiresDaughterCard  :1;
    0,    //  Removable             :1;
    0,    //  Replaceable           :1;
    0,    //  HotSwappable          :1;
    0,    //  Reserved              :3;
  },
  6,                        // LocationInChassis String
  0,                        // ChassisHandle;
  BaseBoardTypeMotherBoard, // BoardType;
  0,                        // NumberOfContainedObjectHandles;
  { 0 }                     // ContainedObjectHandles[1];
};
CHAR8  *mBoardInfoType2Strings[] = {
  "SolidRun",
  "HummingBoard-Edge i4Pro",
  "2.0",
  "Base Board Serial#",
  "Base Board Asset Tag#",
  "hb04w-e-110-00-004-0",
  NULL
};

SMBIOS_TABLE_TYPE3  mEnclosureInfoType3 = {
  { EFI_SMBIOS_TYPE_SYSTEM_ENCLOSURE, sizeof (SMBIOS_TABLE_TYPE3), 0 },
  1,                          // Manufacturer String
  MiscChassisTypeOther,       // Type;
  2,                          // Version String
  3,                          // SerialNumber String
  4,                          // AssetTag String
  ChassisStateSafe,           // BootupState;
  ChassisStateSafe,           // PowerSupplyState;
  ChassisStateSafe,           // ThermalState;
  ChassisSecurityStatusNone,  // SecurityStatus;
  { 0, 0, 0, 0 },             // OemDefined[4];
  0,                          // Height;
  0,                          // NumberofPowerCords;
  0,                          // ContainedElementCount;
  0,                          // ContainedElementRecordLength;
  { { 0 } },                  // ContainedElements[1];
};
CHAR8  *mEnclosureInfoType3Strings[] = {
  "SolidRun",
  "2.0",
  "Chassis Board Serial#",
  "Chassis Board Asset Tag#",
  NULL
};

SMBIOS_TABLE_TYPE4 mProcessorInfoType4 = {
  { EFI_SMBIOS_TYPE_PROCESSOR_INFORMATION, sizeof (SMBIOS_TABLE_TYPE4), 0},
  1,                                // Socket String;
  CentralProcessor,                 // ProcessorType;
  ProcessorFamilyIndicatorFamily2,  // ProcessorFamily;
  2,                                // ProcessorManufacture String;
  {                                 // ProcessorId;
    {     // PROCESSOR_SIGNATURE
      0,  //  ProcessorSteppingId:4;
      0,  //  ProcessorModel:     4;
      0,  //  ProcessorFamily:    4;
      0,  //  ProcessorType:      2;
      0,  //  ProcessorReserved1: 2;
      0,  //  ProcessorXModel:    4;
      0,  //  ProcessorXFamily:   8;
      0,  //  ProcessorReserved2: 4;
    },
    {     // PROCESSOR_FEATURE_FLAGS
      0,  //  ProcessorFpu       :1;
      0,  //  ProcessorVme       :1;
      0,  //  ProcessorDe        :1;
      0,  //  ProcessorPse       :1;
      0,  //  ProcessorTsc       :1;
      0,  //  ProcessorMsr       :1;
      0,  //  ProcessorPae       :1;
      0,  //  ProcessorMce       :1;
      0,  //  ProcessorCx8       :1;
      0,  //  ProcessorApic      :1;
      0,  //  ProcessorReserved1 :1;
      0,  //  ProcessorSep       :1;
      0,  //  ProcessorMtrr      :1;
      0,  //  ProcessorPge       :1;
      0,  //  ProcessorMca       :1;
      0,  //  ProcessorCmov      :1;
      0,  //  ProcessorPat       :1;
      0,  //  ProcessorPse36     :1;
      0,  //  ProcessorPsn       :1;
      0,  //  ProcessorClfsh     :1;
      0,  //  ProcessorReserved2 :1;
      0,  //  ProcessorDs        :1;
      0,  //  ProcessorAcpi      :1;
      0,  //  ProcessorMmx       :1;
      0,  //  ProcessorFxsr      :1;
      0,  //  ProcessorSse       :1;
      0,  //  ProcessorSse2      :1;
      0,  //  ProcessorSs        :1;
      0,  //  ProcessorReserved3 :1;
      0,  //  ProcessorTm        :1;
      0,  //  ProcessorReserved4 :2;
    }
  },
  3,    // ProcessorVersion String;
  {     // Voltage;
    1,  // ProcessorVoltageCapability5V        :1;
    1,  // ProcessorVoltageCapability3_3V      :1;
    1,  // ProcessorVoltageCapability2_9V      :1;
    0,  // ProcessorVoltageCapabilityReserved  :1;
    0,  // ProcessorVoltageReserved            :3;
    0   // ProcessorVoltageIndicateLegacy      :1;
  },
  0,                      // ExternalClock;
  1200,                   // MaxSpeed;
  792,                    // CurrentSpeed;
  0x41,                   // Status;
  ProcessorUpgradeOther,  // ProcessorUpgrade;
  0,                      // L1CacheHandle;
  0,                      // L2CacheHandle;
  0,                      // L3CacheHandle;
  4,                      // SerialNumber;
  5,                      // AssetTag;
  6,                      // PartNumber;
  0,                      // CoreCount;
  0,                      // EnabledCoreCount;
  0,                      // ThreadCount;
  0,                      // ProcessorCharacteristics;
  ProcessorFamilyARMv7,   // ProcessorFamily2;
};

CHAR8 *mProcessorInfoType4Strings[] = {
  "SoM",
  "NXP",
  "i.MX 6Quad",
  "1.0",
  "1.0",
  "1.0",
  NULL
};

SMBIOS_TABLE_TYPE7  mCacheInfoType7I1 = {
  { EFI_SMBIOS_TYPE_CACHE_INFORMATION, sizeof (SMBIOS_TABLE_TYPE7), 0 },
  1,      // SocketDesignation String
  0x018A, // Cache Configuration
  0x0020, // Maximum Size 32k
  0x0020, // Install Size 32k
  {       // Supported SRAM Type
    0,    //Other             :1
    0,    //Unknown           :1
    0,    //NonBurst          :1
    1,    //Burst             :1
    0,    //PiplelineBurst    :1
    1,    //Synchronous       :1
    0,    //Asynchronous      :1
    0     //Reserved          :9
  },
  {       // Current SRAM Type
    0,    //Other             :1
    0,    //Unknown           :1
    0,    //NonBurst          :1
    1,    //Burst             :1
    0,    //PiplelineBurst    :1
    1,    //Synchronous       :1
    0,    //Asynchronous      :1
    0     //Reserved          :9
  },
  0,                      // Cache Speed unknown
  CacheErrorMultiBit,     // Error Correction Multi
  CacheTypeInstruction,   // System Cache Type
  CacheAssociativity2Way  // Associativity
};
CHAR8  *mCacheInfoType7I1Strings[] = {
  "L1 ICache",
  NULL
};

SMBIOS_TABLE_TYPE7  mCacheInfoType7D1 = {
  { EFI_SMBIOS_TYPE_CACHE_INFORMATION, sizeof (SMBIOS_TABLE_TYPE7), 0 },
  1,      // SocketDesignation String
  0x018A, // Cache Configuration
  0x0020, // Maximum Size 32k
  0x0020, // Install Size 32k
  {       // Supported SRAM Type
    0,    //Other             :1
    0,    //Unknown           :1
    0,    //NonBurst          :1
    1,    //Burst             :1
    0,    //PiplelineBurst    :1
    1,    //Synchronous       :1
    0,    //Asynchronous      :1
    0     //Reserved          :9
  },
  {       // Current SRAM Type
    0,    //Other             :1
    0,    //Unknown           :1
    0,    //NonBurst          :1
    1,    //Burst             :1
    0,    //PiplelineBurst    :1
    1,    //Synchronous       :1
    0,    //Asynchronous      :1
    0     //Reserved          :9
  },
  0,                      // Cache Speed unknown
  CacheErrorMultiBit,     // Error Correction Multi
  CacheTypeData,          // System Cache Type
  CacheAssociativity2Way  // Associativity
};
CHAR8  *mCacheInfoType7D1Strings[] = {
  "L1 DCache",
  NULL
};

SMBIOS_TABLE_TYPE7  mCacheInfoType7U2 = {
  { EFI_SMBIOS_TYPE_CACHE_INFORMATION, sizeof (SMBIOS_TABLE_TYPE7), 0 },
  1,      // SocketDesignation String
  0x018A, // Cache Configuration
  0x0400, // Maximum Size 1M
  0x0400, // Install Size 1M
  {       // Supported SRAM Type
    0,    //Other             :1
    0,    //Unknown           :1
    0,    //NonBurst          :1
    1,    //Burst             :1
    0,    //PiplelineBurst    :1
    1,    //Synchronous       :1
    0,    //Asynchronous      :1
    0     //Reserved          :9
  },
  {       // Current SRAM Type
    0,    //Other             :1
    0,    //Unknown           :1
    0,    //NonBurst          :1
    1,    //Burst             :1
    0,    //PiplelineBurst    :1
    1,    //Synchronous       :1
    0,    //Asynchronous      :1
    0     //Reserved          :9
  },
  0,                      // Cache Speed unknown
  CacheErrorMultiBit,     // Error Correction Multi
  CacheTypeUnified,       // System Cache Type
  CacheAssociativity2Way  // Associativity
};
CHAR8  *mCacheInfoType7U2Strings[] = {
  "L2 UCache (PL310)",
  NULL
};

SMBIOS_TABLE_TYPE9  mSysSlotInfoType9 = {
  { EFI_SMBIOS_TYPE_SYSTEM_SLOTS, sizeof (SMBIOS_TABLE_TYPE9), 0 },
  1,                      // SlotDesignation String
  SlotTypeOther,          // SlotType;
  SlotDataBusWidthOther,  // SlotDataBusWidth;
  SlotUsageAvailable,     // CurrentUsage;
  SlotLengthOther,        // SlotLength;
  0,    // SlotID;
  {     // SlotCharacteristics1;
    1,  // CharacteristicsUnknown  :1;
    0,  // Provides50Volts         :1;
    0,  // Provides33Volts         :1;
    0,  // SharedSlot              :1;
    0,  // PcCard16Supported       :1;
    0,  // CardBusSupported        :1;
    0,  // ZoomVideoSupported      :1;
    0,  // ModemRingResumeSupported:1;
  },
  {     // SlotCharacteristics2;
    0,  // PmeSignalSupported      :1;
    0,  // HotPlugDevicesSupported :1;
    0,  // SmbusSignalSupported    :1;
    0,  // Reserved                :5;
  },
  0,    // SegmentGroupNum;
  0,    // BusNum;
  0,    // DevFuncNum;
};
CHAR8  *mSysSlotInfoType9Strings[] = {
  "SD Card",
  NULL
};

SMBIOS_TABLE_TYPE16 mPhyMemArrayInfoType16 = {
  { EFI_SMBIOS_TYPE_PHYSICAL_MEMORY_ARRAY, sizeof (SMBIOS_TABLE_TYPE16), 0 },
  MemoryArrayLocationSystemBoard, // Location;
  MemoryArrayUseSystemMemory,     // Use;
  MemoryErrorCorrectionUnknown,   // MemoryErrorCorrection;
  0x80000000,                     // MaximumCapacity (2 GB);
  0xFFFE,                         // MemoryErrorInformationHandle;
  1,                              // NumberOfMemoryDevices;
  0x80000000ULL,                  // ExtendedMaximumCapacity (2 GB)
};
CHAR8 *mPhyMemArrayInfoType16Strings[] = {
  NULL
};

SMBIOS_TABLE_TYPE17 mMemDevInfoType17 = {
  { EFI_SMBIOS_TYPE_MEMORY_DEVICE, sizeof (SMBIOS_TABLE_TYPE17), 0 },
  0,          // MemoryArrayHandle; Matches SMBIOS_TABLE_TYPE16.Handle, see PhyMemArrayInfoUpdateSmbiosType16()
  0xFFFE,     // MemoryErrorInformationHandle;
  0xFFFF,     // TotalWidth;
  0xFFFF,     // DataWidth;
  0x0800,     // Size; // When bit 15 is 0: Size in MB
                       // When bit 15 is 1: Size in KB, and continues in ExtendedSize
  MemoryFormFactorUnknown,  // FormFactor;
  0xff,                     // DeviceSet;
  1,                        // DeviceLocator String
  2,                        // BankLocator String
  MemoryTypeDram,           // MemoryType;
  {     // TypeDetail;
    0,  // Reserved        :1;
    0,  // Other           :1;
    1,  // Unknown         :1;
    0,  // FastPaged       :1;
    0,  // StaticColumn    :1;
    0,  // PseudoStatic    :1;
    0,  // Rambus          :1;
    0,  // Synchronous     :1;
    0,  // Cmos            :1;
    0,  // Edo             :1;
    0,  // WindowDram      :1;
    0,  // CacheDram       :1;
    0,  // Nonvolatile     :1;
    0,  // Registered      :1;
    0,  // Unbuffered      :1;
    0,  // Reserved1       :1;
  },
  0,          // Speed;
  3,          // Manufacturer String
  0,          // SerialNumber String
  0,          // AssetTag String
  0,          // PartNumber String
  0,          // Attributes;
  0,          // ExtendedSize;
  0,          // ConfiguredMemoryClockSpeed;
};
CHAR8 *mMemDevInfoType17Strings[] = {
  "OS Virtual Memory",
  "malloc",
  "OSV",
  NULL
};

SMBIOS_TABLE_TYPE19 mMemArrMapInfoType19 = {
  { EFI_SMBIOS_TYPE_MEMORY_ARRAY_MAPPED_ADDRESS, sizeof (SMBIOS_TABLE_TYPE19), 0 },
  0x10000000, // StartingAddress;
  0x8fffffff, // EndingAddress;
  0,          // MemoryArrayHandle;
  1,          // PartitionWidth;
  0,          // ExtendedStartingAddress;
  0,          // ExtendedEndingAddress;
};
CHAR8 *mMemArrMapInfoType19Strings[] = {
  NULL
};

SMBIOS_TABLE_TYPE32 mBootInfoType32 = {
  { EFI_SMBIOS_TYPE_SYSTEM_BOOT_INFORMATION, sizeof (SMBIOS_TABLE_TYPE32), 0 },
  { 0, 0, 0, 0, 0, 0 },         // Reserved[6];
  BootInformationStatusNoError  // BootStatus
};

CHAR8 *mBootInfoType32Strings[] = {
  NULL
};

/**

  Create SMBIOS record.

  Converts a fixed SMBIOS structure and an array of pointers to strings into
  an SMBIOS record where the strings are cat'ed on the end of the fixed record
  and terminated via a double NULL and add to SMBIOS table.

  @param  Template    Fixed SMBIOS structure, required.
  @param  StringPack  Array of strings to convert to an SMBIOS string pack.
                      NULL is OK.
  @param  DataSmbiosHandle  The new SMBIOS record handle .
                      NULL is OK.
**/
EFI_STATUS
EFIAPI
LogSmbiosData (
  IN  EFI_SMBIOS_TABLE_HEADER *Template,
  IN  CHAR8                   **StringPack,
  OUT EFI_SMBIOS_HANDLE       *DataSmbiosHandle
  )
{
  EFI_STATUS                Status;
  EFI_SMBIOS_PROTOCOL       *Smbios;
  EFI_SMBIOS_HANDLE         SmbiosHandle;
  EFI_SMBIOS_TABLE_HEADER   *Record;
  UINTN                     Index;
  UINTN                     StringSize;
  UINTN                     Size;
  CHAR8                     *Str;

  Status = gBS->LocateProtocol (&gEfiSmbiosProtocolGuid, NULL, (VOID **)&Smbios);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  // Calculate the size of the fixed record and optional string pack
  Size = Template->Length;
  if (StringPack == NULL) {
    // At least a double null is required
    Size += 2;
  } else {
    for (Index = 0; StringPack[Index] != NULL; Index++) {
      StringSize = AsciiStrSize (StringPack[Index]);
      Size += StringSize;
    }
  if (StringPack[0] == NULL) {
    // At least a double null is required
    Size += 1;
    }

    // Don't forget the terminating double null
    Size += 1;
  }

  // Copy over Template
  Record = (EFI_SMBIOS_TABLE_HEADER *)AllocateZeroPool (Size);
  if (Record == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  CopyMem (Record, Template, Template->Length);

  // Append string pack
  Str = ((CHAR8 *)Record) + Record->Length;

  for (Index = 0; StringPack[Index] != NULL; Index++) {
    StringSize = AsciiStrSize (StringPack[Index]);
    CopyMem (Str, StringPack[Index], StringSize);
    Str += StringSize;
  }

  *Str = 0;
  SmbiosHandle = SMBIOS_HANDLE_PI_RESERVED;
  Status = Smbios->Add (
                     Smbios,
                     gImageHandle,
                     &SmbiosHandle,
                     Record
                     );
  if ((Status == EFI_SUCCESS) && (DataSmbiosHandle != NULL)) {
      *DataSmbiosHandle = SmbiosHandle;
  }

  ASSERT_EFI_ERROR (Status);
  FreePool (Record);
  return Status;
}

VOID
BIOSInfoUpdateSmbiosType0 (
  VOID
  )
{
  LogSmbiosData ((EFI_SMBIOS_TABLE_HEADER *)&mBIOSInfoType0, mBIOSInfoType0Strings, NULL);
}

VOID
I64ToHexString(
    IN OUT CHAR8* TargetStringSz,
    IN UINT32 TargetStringSize,
    IN UINT64 Value
    )
{
    static CHAR8 ItoH[] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
    UINT8 StringInx;
    INT8 NibbleInx;

    ZeroMem((void*)TargetStringSz, TargetStringSize);

    //
    // Convert each nibble to hex string, starting from
    // the highest non-zero nibble.
    //
    StringInx = 0;
    for (NibbleInx = sizeof(UINT64) * 2; NibbleInx > 0; --NibbleInx) {
        UINT64 NibbleMask = (((UINT64)0xF) << ((NibbleInx - 1) * 4));
        UINT8 Nibble = (UINT8)((Value & NibbleMask) >> ((NibbleInx - 1) * 4));

        ASSERT(Nibble <= 0xF);

        if (StringInx < (TargetStringSize-1)) {
            TargetStringSz[StringInx++] = ItoH[Nibble];
        } else {
            break;
        }
    }
}

UINT64 ObtainPlatformId(VOID)
{
   UINT64 BoardSerial=(UINT64)0;

   // see iMX6 reference manual section 46.5.10 for OTP CFG registers description
   const UINT32 RegOCOTP_CFG0Addr=0x021BC410; // OTP Bank0 Word1 contains lower 32 bits of the Unique ID and SJC_CHALLENGE field
   const UINT32 RegOCOTP_CFG1Addr=0x021BC420; // OTP Bank0 Word2 contains upper 32 bits of the Unique ID and SJC_CHALLENGE field
   BoardSerial = ((UINT64)(MmioRead32(RegOCOTP_CFG1Addr))) << 32;
   BoardSerial = BoardSerial | ((UINT64)(MmioRead32(RegOCOTP_CFG0Addr)));

   DEBUG((DEBUG_INFO, "Hummingboard Edge ser no %08X%08Xh \r\n", (UINT32)(BoardSerial>>32), (UINT32)BoardSerial));
   return BoardSerial;
}

VOID
SysInfoUpdateSmbiosType1 (
  VOID
  )
{
   UINT64 BoardSerial=(UINT64)0;
   UINT32 Bank0Word3=0;
   static CHAR8 BoardSerialString[sizeof(BoardSerial) * 2 + 1]={0x00};
   int k=0;

   const UINT32 RegOCOTP_CFG2Addr=0x021BC430;
   BoardSerial = ObtainPlatformId();

   // Update the Smbios Type1 information with the board serial string
   I64ToHexString(&BoardSerialString[0], sizeof(BoardSerialString), BoardSerial);
   mSysInfoType1Strings[mSysInfoType1.SerialNumber - 1] = &BoardSerialString[0];

   Bank0Word3 = MmioRead32(RegOCOTP_CFG2Addr);
   // Construct string to make UUID: fixed prefix + board serial number printed in hex
   mSysInfoType1.Uuid.Data1=((UINT32)'H'<<24) | ((UINT32)'M'<<16) | ((UINT32)'B'<<8) | (UINT32)'E' ;
   mSysInfoType1.Uuid.Data2=(UINT16)Bank0Word3;
   mSysInfoType1.Uuid.Data3=(UINT16)(Bank0Word3>>16);

   for(k=7; k>=0; k--) {
      mSysInfoType1.Uuid.Data4[7-k]=(UINT8)(BoardSerial>>(k*8));
   }

   LogSmbiosData ((EFI_SMBIOS_TABLE_HEADER*)&mSysInfoType1, mSysInfoType1Strings, NULL);

}

VOID
BoardInfoUpdateSmbiosType2 (
  VOID
  )
{
  LogSmbiosData ((EFI_SMBIOS_TABLE_HEADER *)&mBoardInfoType2, mBoardInfoType2Strings, NULL);
}

VOID
EnclosureInfoUpdateSmbiosType3 (
  VOID
  )
{
  UINT8 ChassisSerialNo=0xFF;
  static CHAR8 ChassisBoardSerialString[sizeof(ChassisSerialNo) * 2 + 1]={0x00};

  // Generate chassis number from same platform id.
  ChassisSerialNo = (UINT8)(ObtainPlatformId() >> 40);
  DEBUG((DEBUG_INFO, "Chassis Board Serial %02Xh \r\n", ChassisSerialNo));

  I64ToHexString(&ChassisBoardSerialString[0], sizeof(ChassisBoardSerialString), ChassisSerialNo);
  mEnclosureInfoType3Strings[mEnclosureInfoType3.SerialNumber - 1] = &ChassisBoardSerialString[0];

  LogSmbiosData ((EFI_SMBIOS_TABLE_HEADER *)&mEnclosureInfoType3, mEnclosureInfoType3Strings, NULL);
}

VOID
ProcessorInfoUpdateSmbiosType4 (
  IN UINTN MaxCpus
  )
{
  mProcessorInfoType4.CoreCount        = (UINT8) MaxCpus;
  mProcessorInfoType4.EnabledCoreCount = (UINT8) MaxCpus;
  mProcessorInfoType4.ThreadCount      = (UINT8) MaxCpus;

  LogSmbiosData ((EFI_SMBIOS_TABLE_HEADER *)&mProcessorInfoType4, mProcessorInfoType4Strings, NULL);
}

VOID
CacheInfoUpdateSmbiosType7 (
  VOID
  )
{
  LogSmbiosData ((EFI_SMBIOS_TABLE_HEADER *)&mCacheInfoType7I1, mCacheInfoType7I1Strings, NULL);
  LogSmbiosData ((EFI_SMBIOS_TABLE_HEADER *)&mCacheInfoType7D1, mCacheInfoType7D1Strings, NULL);
  LogSmbiosData ((EFI_SMBIOS_TABLE_HEADER *)&mCacheInfoType7U2, mCacheInfoType7U2Strings, NULL);
}

VOID
SysSlotInfoUpdateSmbiosType9 (
  VOID
  )
{
  LogSmbiosData ((EFI_SMBIOS_TABLE_HEADER *)&mSysSlotInfoType9, mSysSlotInfoType9Strings, NULL);
}

VOID
PhyMemArrayInfoUpdateSmbiosType16 (
  VOID
  )
{
  EFI_SMBIOS_HANDLE MemArraySmbiosHandle;
  LogSmbiosData ((EFI_SMBIOS_TABLE_HEADER *)&mPhyMemArrayInfoType16, mPhyMemArrayInfoType16Strings, &MemArraySmbiosHandle);

  // Update the memory device information
  mMemDevInfoType17.MemoryArrayHandle = MemArraySmbiosHandle;
}

VOID
MemDevInfoUpdateSmbiosType17 (
  VOID
  )
{
  LogSmbiosData ((EFI_SMBIOS_TABLE_HEADER *)&mMemDevInfoType17, mMemDevInfoType17Strings, NULL);
}

VOID
MemArrMapInfoUpdateSmbiosType19 (
  VOID
  )
{
  LogSmbiosData ((EFI_SMBIOS_TABLE_HEADER *)&mMemArrMapInfoType19, mMemArrMapInfoType19Strings, NULL);
}

VOID
BootInfoUpdateSmbiosType32 (
  VOID
  )
{
  LogSmbiosData ((EFI_SMBIOS_TABLE_HEADER *)&mBootInfoType32, mBootInfoType32Strings, NULL);
}

EFI_STATUS
EFIAPI
PlatformSmbiosDriverEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  BIOSInfoUpdateSmbiosType0();

  SysInfoUpdateSmbiosType1();

  BoardInfoUpdateSmbiosType2();

  EnclosureInfoUpdateSmbiosType3();

  ProcessorInfoUpdateSmbiosType4 (FixedPcdGet32(PcdCoreCount));

  CacheInfoUpdateSmbiosType7();

  SysSlotInfoUpdateSmbiosType9();

  PhyMemArrayInfoUpdateSmbiosType16();

  MemDevInfoUpdateSmbiosType17();

  MemArrMapInfoUpdateSmbiosType19();

  BootInfoUpdateSmbiosType32();

  return EFI_SUCCESS;
}
