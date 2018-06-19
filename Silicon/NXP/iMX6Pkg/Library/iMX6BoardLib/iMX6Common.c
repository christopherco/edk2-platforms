/** @file
*
*  Copyright (c), Microsoft Corporation. All rights reserved.
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
#include <Library/IoLib.h>
#include <Library/ArmPlatformLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/PrintLib.h>
#include <Library/PcdLib.h>
#include <Library/SerialPortLib.h>
#include <Library/TimerLib.h>
#include <Library/iMX6BoardLib.h>
#include <Library/PcdLib.h>
#include <IndustryStandard/Tpm20.h>
#include <IndustryStandard/Tpm2Acpi.h>
#include <iMX6.h>

void __DoNothing() {}
VOID SdhcInit () __attribute__ ((weak, alias ("__DoNothing")));
VOID EhciInit () __attribute__ ((weak, alias ("__DoNothing")));
VOID EnetInit () __attribute__ ((weak, alias ("__DoNothing")));
VOID I2cInit () __attribute__ ((weak, alias ("__DoNothing")));
VOID SpiInit () __attribute__ ((weak, alias ("__DoNothing")));
VOID PcieInit () __attribute__ ((weak, alias ("__DoNothing")));
VOID SetupAudio () __attribute__ ((weak, alias ("__DoNothing")));

RETURN_STATUS
EFIAPI
TimerConstructor (
  VOID
  );

/**
    Initialize the TPM2 control area.

Note:
    This is temporary, and is normally done in TPM2 OPTEE device lib,
    which will take place as soon as the TreeDxe driver is enabled.
**/
VOID
Tpm2AcpiControlAreaInit ()
{
  EFI_PHYSICAL_ADDRESS BaseAddress;
  UINT32 BufferSize;
  EFI_TPM2_ACPI_CONTROL_AREA *ControlArea;
 
  BaseAddress = PcdGet64 (PcdTpm2AcpiBufferBase);
  BufferSize = PcdGet32 (PcdTpm2AcpiBufferSize);

  if ((BaseAddress == 0) || (BufferSize == 0)) {
    //
    // TPM not enabled
    //
    return;
  }

  ASSERT (BufferSize >= EFI_PAGE_SIZE * 3);

  ControlArea = (EFI_TPM2_ACPI_CONTROL_AREA *)((UINTN)BaseAddress);
  ZeroMem(ControlArea, sizeof(EFI_TPM2_ACPI_CONTROL_AREA));
  BufferSize = EFI_PAGE_SIZE;
  ControlArea->Command = (UINT64)((UINTN)(ControlArea + 1));
  ControlArea->CommandSize = BufferSize;
  ControlArea->Response = ControlArea->Command + BufferSize;
  ControlArea->ResponseSize = BufferSize;
}

/**
  Initialize controllers that must setup at the early stage
**/
RETURN_STATUS
ArmPlatformInitialize (
  IN  UINTN                     MpId
  )
{
  if (!ArmPlatformIsPrimaryCore (MpId)) {
    return RETURN_SUCCESS;
  }

  ImxClkPwrInit ();

  // initialize default UEFI debug port early so we can use its debug output
  SerialPortInitialize ();
  SerialPortWrite (
   (UINT8 *)SERIAL_DEBUG_PORT_INIT_MSG,
   (UINTN)sizeof(SERIAL_DEBUG_PORT_INIT_MSG));

  // Initialize timer early on because the following init path will be calling
  // delay functions. PrePi.c calls ArmPlatformInitialize before it calls
  // TimerConstructor to initialize the timer.
  TimerConstructor ();

  SdhcInit ();
  EhciInit ();
  EnetInit ();
  I2cInit ();
  SpiInit ();
  PcieInit ();
  SetupAudio ();

  Tpm2AcpiControlAreaInit ();
  
  return RETURN_SUCCESS;
}

/**
  Return the current Boot Mode

  This function returns the boot reason on the platform

**/
EFI_BOOT_MODE
ArmPlatformGetBootMode (
  VOID
  )
{
  return BOOT_WITH_FULL_CONFIGURATION;
}
