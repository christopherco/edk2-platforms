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
#include <iMX6.h>
#include <common_macros.h>
#include <common_epit.h>

#include <PiDxe.h>

#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>

#include <Protocol/Timer.h>
#include <Protocol/HardwareInterrupt.h>

// The notification function to call on every timer interrupt.
volatile EFI_TIMER_NOTIFY mTimerNotifyFunction = (EFI_TIMER_NOTIFY) NULL;
EFI_EVENT EfiExitBootServicesEvent = (EFI_EVENT) NULL;

// Cached copy of the Hardware Interrupt protocol instance
EFI_HARDWARE_INTERRUPT_PROTOCOL *gInterrupt = NULL;

// Cached interrupt vector
volatile UINTN  mVector;
UINT64 mCurrentTimerPeriod;

EFI_STATUS
EFIAPI
TimerDriverRegisterHandler (
  IN EFI_TIMER_ARCH_PROTOCOL  *This,
  IN EFI_TIMER_NOTIFY         NotifyFunction
  )
{
  DEBUG ((DEBUG_VERBOSE, "++TimerDriverRegisterHandler()\n"));
  if ((NotifyFunction == NULL) && (mTimerNotifyFunction == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  if ((NotifyFunction != NULL) && (mTimerNotifyFunction != NULL)) {
    return EFI_ALREADY_STARTED;
  }

  mTimerNotifyFunction = NotifyFunction;
  DEBUG ((DEBUG_VERBOSE, "--TimerDriverRegisterHandler()=ok\n"));
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
TimerDriverSetTimerPeriod (
  IN EFI_TIMER_ARCH_PROTOCOL  *This,
  IN UINT64                   TimerPeriod
  )
{
  EFI_STATUS  Status;
  UINT32      TimerCount;
  UINT16      epitPreScalar;

  DEBUG ((DEBUG_VERBOSE, "++TimerDriverSetTimerPeriod(%d)\n", TimerPeriod));

  PCSP_EPIT_REG g_pEPIT = (PCSP_EPIT_REG) CSP_BASE_REG_PA_EPIT1;

  DEBUG ((DEBUG_VERBOSE, "TimerDriverSetTimerPeriod() disable timer. EPIT_REG adr=%p\n", g_pEPIT));

  // First stop the timer.
  INSREG32BF(&g_pEPIT->CR,EPIT_CR_EN,EPIT_CR_EN_DISABLE);

  if (TimerPeriod == 0) {
    Status = gInterrupt->DisableInterruptSource(gInterrupt, mVector);
    mCurrentTimerPeriod = 0;
    DEBUG ((DEBUG_VERBOSE, "--TimerDriverSetTimerPeriod() Timer Disabled\n"));
    return Status;
  } 

  // configure EPIT to be sourced from iMX6 24 MHz crystal oscialltor per
  // i.MX 6Dual/6Quad Applications Processor Reference Manual, Rev. 3, 07/2015
  // aim to have UEFI tick counting at 1 MHz clock or another frequency as set in pcd value

  // NOTE: prescalar computed per iMX6 spec for EPIT in 24.6.1 seems to provide inaccurate tick frequency 
  // on Hummingboard corrected divider is 68 (prescalar+1)
  
  epitPreScalar = 68;
  DEBUG((DEBUG_VERBOSE, "TimerDriverSetTimerPeriod() using corrected EPIT prescalar=%d\n", epitPreScalar));

  OUTREG32(&g_pEPIT->CR,
      CSP_BITFVAL(EPIT_CR_ENMOD, EPIT_CR_ENMOD_LOAD) |
      CSP_BITFVAL(EPIT_CR_OCIEN, EPIT_CR_OCIEN_ENABLE) |
      CSP_BITFVAL(EPIT_CR_RLD, EPIT_CR_RLD_RELOAD) |
      CSP_BITFVAL(EPIT_CR_PRESCALAR, (epitPreScalar-1)) |  // bits 4-15, 000 to FFF.
      CSP_BITFVAL(EPIT_CR_SWR, EPIT_CR_SWR_NORESET) |
      CSP_BITFVAL(EPIT_CR_IOVW, EPIT_CR_IOVW_OVR) |
      CSP_BITFVAL(EPIT_CR_DBGEN, EPIT_CR_DBGEN_ACTIVE) |
      CSP_BITFVAL(EPIT_CR_WAITEN, EPIT_CR_WAITEN_ENABLE) |
      CSP_BITFVAL(EPIT_CR_DOZEN, EPIT_CR_DOZEN_ENABLE) |
      CSP_BITFVAL(EPIT_CR_STOPEN, EPIT_CR_STOPEN_ENABLE) |
      CSP_BITFVAL(EPIT_CR_OM, EPIT_CR_OM_DICONNECT) |
      CSP_BITFVAL(EPIT_CR_CLKSRC, EPIT_CR_CLKSRC_IPGCLK)); // source is crystal clock source (24 MHz)

  // Clear timer compare interrupt flag (write-1-clear)
  OUTREG32(&g_pEPIT->SR, CSP_BITFMASK(EPIT_SR_OCIF));
    // Set the new compare value
  TimerCount = (UINT32)(TimerPeriod / 10);

  if((UINT64)TimerCount > (UINT64)0xffffffff)
    TimerCount = 0xffffffff;

  mCurrentTimerPeriod = TimerPeriod;

  OUTREG32(&g_pEPIT->CMPR, TimerCount);
  OUTREG32(&g_pEPIT->LR, TimerCount);
  
  Status = gInterrupt->EnableInterruptSource(gInterrupt, mVector);
  // turn the timer on
  INSREG32BF(&g_pEPIT->CR,EPIT_CR_EN,EPIT_CR_EN_ENABLE);

  DEBUG ((DEBUG_VERBOSE, "--TimerDriverSetTimerPeriod(%d)=%Xh\n", TimerPeriod,Status));
  return Status;
}

EFI_STATUS
EFIAPI
TimerDriverGetTimerPeriod (
  IN EFI_TIMER_ARCH_PROTOCOL   *This,
  OUT UINT64                   *TimerPeriod
  )
{
  *TimerPeriod = mCurrentTimerPeriod;
  DEBUG ((DEBUG_VERBOSE, "+-TimerDriverGetTimerPeriod(%d)=ok\n", mCurrentTimerPeriod));
  return EFI_SUCCESS;
}

VOID
EFIAPI
TimerInterruptHandler (
  IN  HARDWARE_INTERRUPT_SOURCE   Source,
  IN  EFI_SYSTEM_CONTEXT          SystemContext       
  )
{
  EFI_TPL OriginalTPL;
  PCSP_EPIT_REG g_pEPIT = (PCSP_EPIT_REG) CSP_BASE_REG_PA_EPIT1;

  //
  // DXE core uses this callback for the EFI timer tick. The DXE core uses locks
  // that raise to TPL_HIGH and then restore back to current level. Thus we need
  // to make sure TPL level is set to TPL_HIGH while we are handling the timer tick.
  //
  OriginalTPL = gBS->RaiseTPL (TPL_HIGH_LEVEL);

  // Check if the timer interrupt is active
  if (INREG32 (&g_pEPIT->SR) != 0) {
    // Acknowledge the EPIT interrupt
    OUTREG32 (&g_pEPIT->SR, 0x1);

    // Signal end of interrupt early to help avoid losing subsequent ticks from long duration handlers
    gInterrupt->EndOfInterrupt (gInterrupt, Source);

    if (mTimerNotifyFunction) {
      mTimerNotifyFunction (mCurrentTimerPeriod);
    }
  }

  gBS->RestoreTPL (OriginalTPL);
//  DEBUG ((EFI_D_ERROR, "+-TimerInterruptHandler()\n"));
}


EFI_STATUS
EFIAPI
TimerDriverGenerateSoftInterrupt (
  IN EFI_TIMER_ARCH_PROTOCOL  *This
  )
{
  return EFI_UNSUPPORTED;
}

EFI_TIMER_ARCH_PROTOCOL   gTimer = {
  TimerDriverRegisterHandler,
  TimerDriverSetTimerPeriod,
  TimerDriverGetTimerPeriod,
  TimerDriverGenerateSoftInterrupt
};

VOID
EFIAPI
ExitBootServicesEvent (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  EFI_STATUS  Status;

  DEBUG ((DEBUG_INFO, "Disabling EPIT timer on ExitBootServicesEvent"));

  // Disable the timer
  Status = TimerDriverSetTimerPeriod(&gTimer, 0);
  ASSERT_EFI_ERROR (Status);
}

EFI_STATUS
EFIAPI
TimerInitialize (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_HANDLE  Handle = NULL;
  EFI_STATUS  Status;
  DEBUG ((DEBUG_VERBOSE, "++TimerInitialize()\n"));

  mVector = IRQ_EPIT1;

  // Find the interrupt controller protocol.  ASSERT if not found.
  Status = gBS->LocateProtocol (
                  &gHardwareInterruptProtocolGuid,
                  NULL,
                  (VOID **) &gInterrupt);

  ASSERT_EFI_ERROR (Status);

  // Disable the timer
  Status = TimerDriverSetTimerPeriod (&gTimer, 0);
  ASSERT_EFI_ERROR (Status);

  // Install interrupt handler
  Status = gInterrupt->RegisterInterruptSource (gInterrupt, mVector, TimerInterruptHandler);
  ASSERT_EFI_ERROR (Status);

  // Set up default timer
  Status = TimerDriverSetTimerPeriod (&gTimer, FixedPcdGet32 (PcdTimerPeriod));
  ASSERT_EFI_ERROR (Status);

  DEBUG ((
    DEBUG_VERBOSE,
    "EPIT Timer initialized to default period %d x 100ns ~ %dms\n",
    FixedPcdGet32(PcdTimerPeriod),
    FixedPcdGet32(PcdTimerPeriod) / 10000));

  // Install the Timer Architectural Protocol onto a new handle
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &gEfiTimerArchProtocolGuid,
                  &gTimer,
                  NULL);

  ASSERT_EFI_ERROR(Status);

  // Register for an ExitBootServicesEvent
  Status = gBS->CreateEvent (
                  EVT_SIGNAL_EXIT_BOOT_SERVICES,
                  TPL_NOTIFY,
                  ExitBootServicesEvent,
                  NULL,
                  &EfiExitBootServicesEvent);

  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_VERBOSE, "--TimerInitialize()\n"));
  return Status;
}

