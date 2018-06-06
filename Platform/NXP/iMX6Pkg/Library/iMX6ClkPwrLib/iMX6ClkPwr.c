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

#include <PiDxe.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/TimerLib.h>
#include <Library/BaseMemoryLib.h>

#include <iMX6.h>
#include <iMX6ClkPwr.h>
#include "iMX6ClkPwr_private.h"

// Let GCC know it's OK to compare enum values
#if defined (__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wenum-compare"
#endif

C_ASSERT(IMX_CLOCK_GATE_STATE_OFF == IMX_CCM_CCGR_OFF);
C_ASSERT(IMX_CLOCK_GATE_STATE_ON_RUN == IMX_CCM_CCGR_ON_RUN);
C_ASSERT(IMX_CLOCK_GATE_STATE_ON == IMX_CCM_CCGR_ON);

#if defined (__GNUC__)
#pragma GCC diagnostic pop // -Wenum-compare
#endif

/**
  Caches clock values, since clocks towards the root of the tree are
  requested frequently.
**/
static IMX_CLOCK_TREE_CACHE ImxpClockPwrCache;

#if defined(CPU_IMX6DQ)
#include "iMX6DQClkPwr.inc"
#elif defined(CPU_IMX6SX)
#include "iMX6SXClkPwr.inc"
#elif defined(CPU_IMX6SDL)
#include "iMX6SDLClkPwr.inc"
#else
#error CPU Preprocessor Flag Not Defined
#endif

//
// Common private functions
//

/**
  Reset (invalidate) the clock tree cache. The clock tree cache must be
  invalidated whenever the clock tree is modified, e.g. when changing
  PLL configuration, clock mux, or divider.
**/
VOID ImxpClkPwrCacheReset ()
{
  SetMem (&ImxpClockPwrCache.Valid, sizeof(ImxpClockPwrCache.Valid), 0);
}

/**
  Configure clock gating for the specified clock signal.
**/
VOID ImxClkPwrSetClockGate (IMX_CLK_GATE ClockGate, IMX_CLOCK_GATE_STATE State)
{
  volatile IMX_CCM_REGISTERS *ccmRegisters = (IMX_CCM_REGISTERS *) IMX_CCM_BASE;

  // Extract register index
  const IMX_CCGR_INDEX index = ImxpCcgrIndexFromClkGate(ClockGate);
  const UINTN startBit = index.GateNumber * 2;
  const UINTN endBit = startBit + 1;

  MmioBitFieldWrite32 (
    (UINTN) &ccmRegisters->CCGR[index.RegisterIndex],
    startBit,
    endBit,
    State);
}

/**
  Determine if gating TZASC1_IPG_MASTER_CLK should be skipped.
 **/
BOOLEAN ImxClkPwrShouldSkipTZASC1 ()
{
    BOOLEAN Skip = FALSE;

#if defined(CPU_IMX6DQ)
    IMX_IOMUXC_GPR_REGISTERS *IoMuxMmioBasePtr = 
        (IMX_IOMUXC_GPR_REGISTERS *)IOMUXC_GPR_BASE_ADDRESS;

    UINTN IomuxGPR9 = MmioRead32 ((UINTN) &IoMuxMmioBasePtr->GPR9);
        
    if (IomuxGPR9 & IMX_IOMUXC_TZASC1_BYP) {
        // TZASC-1 is active.
        Skip = TRUE;
    }
#endif

    return Skip;
}

/**
  Determine if a clock gate should be skipped
 **/
BOOLEAN ImxClkPwrShouldSkipGate (IMX_CLK_GATE ClockGate)
{
    switch(ClockGate) {
    case IMX_IPSYNC_IP2APB_TZASC1_IPG_MASTER_CLK_ENABLE:
        return ImxClkPwrShouldSkipTZASC1 ();

    default:
        return FALSE;
    }
}

/**
  Set multiple clock gates to a given state efficiently.
**/
VOID ImxClkPwrSetClockGates (
  const IMX_CLK_GATE *ClockGateList,
  UINTN ClockGateCount,
  IMX_CLOCK_GATE_STATE State
  )
{
  volatile IMX_CCM_REGISTERS *ccmRegisters = (IMX_CCM_REGISTERS *) IMX_CCM_BASE;

  UINTN i;

  // Read all CCGR registers to local copy
  UINT32 ccgrRegisters[ARRAYSIZE (ccmRegisters->CCGR)];
  for (i = 0; i < ARRAYSIZE (ccgrRegisters); ++i) {
    ccgrRegisters[i] = MmioRead32 ((UINTN) &ccmRegisters->CCGR[i]);
  }

  // Compute new CCGR register values
  for (i = 0; i < ClockGateCount; ++i) {
    if (ImxClkPwrShouldSkipGate(ClockGateList[i])) {
        continue;
    }

    IMX_CCGR_INDEX index = ImxpCcgrIndexFromClkGate (ClockGateList[i]);
    ccgrRegisters[index.RegisterIndex] =
      (ccgrRegisters[index.RegisterIndex] & ~(0x3 << (2 * index.GateNumber))) |
      (State << (2 * index.GateNumber));
  }

  // Write back to registers
  for (i = 0; i < ARRAYSIZE (ccgrRegisters); ++i) {
    MmioWrite32 ((UINTN) &ccmRegisters->CCGR[i], ccgrRegisters[i]);
  }
}

/**
  Get the current clock gating setting for the specified clock gate.
**/
IMX_CLOCK_GATE_STATE ImxClkPwrGetClockGate (IMX_CLK_GATE ClockGate)
{
  volatile IMX_CCM_REGISTERS *ccmRegisters = (IMX_CCM_REGISTERS *) IMX_CCM_BASE;

  const IMX_CCGR_INDEX index = ImxpCcgrIndexFromClkGate(ClockGate);
  const UINTN startBit = index.GateNumber * 2;
  const UINTN endBit = startBit + 1;

  UINT32 value = MmioBitFieldRead32 (
                    (UINTN) &ccmRegisters->CCGR[index.RegisterIndex],
                    startBit,
                    endBit);

  switch (value) {
  case IMX_CCM_CCGR_OFF:
  case IMX_CCM_CCGR_ON_RUN:
  case IMX_CCM_CCGR_ON:
    break;
  default:
    ASSERT (FALSE);
  }

  return (IMX_CLOCK_GATE_STATE) value;
}

EFI_STATUS
ImxpGetPll3MainClkInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  )
{
  volatile IMX_CCM_ANALOG_REGISTERS *ccmAnalogRegisters =
      (IMX_CCM_ANALOG_REGISTERS *) IMX_CCM_ANALOG_BASE;

  IMX_CCM_ANALOG_PLL_USB1_REG pllUsb1Reg; pllUsb1Reg.AsUint32 =
      MmioRead32((UINTN)&ccmAnalogRegisters->PLL_USB1);

  const IMX_CLK parent = ImxpClkFromBypassClkSource (pllUsb1Reg.BYPASS_CLK_SRC);

  IMX_CLOCK_INFO parentInfo;
  EFI_STATUS status = ImxpGetClockInfo (Cache, parent, &parentInfo);
  if (EFI_ERROR (status)) {
    return status;
  }

  if (pllUsb1Reg.DIV_SELECT == 0) {
    ClockInfo->Frequency = parentInfo.Frequency * 20;
  } else {
    ClockInfo->Frequency = parentInfo.Frequency * 22;
  }

  ClockInfo->Parent = parent;

  return EFI_SUCCESS;
}

EFI_STATUS
ImxpGetPll3PfdClkInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  IMX_PLL_PFD PfdIndex,
  OUT IMX_CLOCK_INFO *ClockInfo
  )
{
  volatile IMX_CCM_ANALOG_REGISTERS *ccmAnalogRegisters =
      (IMX_CCM_ANALOG_REGISTERS *) IMX_CCM_ANALOG_BASE;

  IMX_CCM_PFD_480_REG pfd480Reg;pfd480Reg.AsUint32 =
      MmioRead32 ((UINTN) &ccmAnalogRegisters->PFD_480);

  UINT32 pfdFrac;
  switch (PfdIndex) {
  case IMX_PLL_PFD0:
    pfdFrac = pfd480Reg.PFD0_FRAC;
    break;
  case IMX_PLL_PFD1:
    pfdFrac = pfd480Reg.PFD1_FRAC;
    break;
  case IMX_PLL_PFD2:
    pfdFrac = pfd480Reg.PFD2_FRAC;
    break;
  case IMX_PLL_PFD3:
    pfdFrac = pfd480Reg.PFD3_FRAC;
    break;
  default:
    ASSERT (FALSE);
    return EFI_INVALID_PARAMETER;
  }

  IMX_CLOCK_INFO parentInfo;
  EFI_STATUS status = ImxpGetClockInfo (Cache, IMX_PLL3_MAIN_CLK, &parentInfo);
  if (EFI_ERROR (status)) {
    return status;
  }

  // The resulting frequency shall be 480*18/PFDn_FRAC
  // where PFD0_FRAC is in the range 12-35.
  ASSERT ((pfdFrac >= 12) && (pfdFrac <= 35));
  ClockInfo->Frequency = (UINT32) ((UINT64) parentInfo.Frequency * 18 / pfdFrac);
  ClockInfo->Parent = IMX_PLL3_MAIN_CLK;

  return EFI_SUCCESS;
}

EFI_STATUS
ImxpGetPll3SwClkInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  )
{
  volatile IMX_CCM_REGISTERS *ccmRegisters = (IMX_CCM_REGISTERS *) IMX_CCM_BASE;

  IMX_CCM_CCSR_REG ccsrReg; ccsrReg.AsUint32 =
      MmioRead32 ((UINTN) &ccmRegisters->CCSR);

  IMX_CLK parent;
  if (ccsrReg.pll3_sw_clk_sel == IMX_CCM_PLL3_SW_CLK_SEL_PLL3_MAIN_CLK) {
    parent = IMX_PLL3_MAIN_CLK;
  } else {
    ASSERT (ccsrReg.pll3_sw_clk_sel == IMX_CCM_PLL3_SW_CLK_SEL_PLL3_BYPASS_CLK);

    ASSERT (!"Not implemented");
    return EFI_UNSUPPORTED;
  }

  IMX_CLOCK_INFO parentInfo;
  EFI_STATUS status = ImxpGetClockInfo (Cache, parent, &parentInfo);
  if (EFI_ERROR (status)) {
    return status;
  }

  ClockInfo->Frequency = parentInfo.Frequency;
  ClockInfo->Parent = parent;

  return EFI_SUCCESS;
}


EFI_STATUS
ImxpGetPll1MainClkInfo  (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  )
{
  volatile IMX_CCM_ANALOG_REGISTERS *ccmAnalogRegisters =
      (IMX_CCM_ANALOG_REGISTERS *) IMX_CCM_ANALOG_BASE;

  IMX_CCM_ANALOG_PLL_ARM_REG pllArmReg;pllArmReg.AsUint32 =
      MmioRead32 ((UINTN) &ccmAnalogRegisters->PLL_ARM);

  const IMX_CLK parent = ImxpClkFromBypassClkSource (pllArmReg.BYPASS_CLK_SRC);

  IMX_CLOCK_INFO parentInfo;
  EFI_STATUS status = ImxpGetClockInfo (Cache, parent, &parentInfo);
  if (EFI_ERROR (status)) {
    return status;
  }

  if (pllArmReg.BYPASS != 0) {
    ClockInfo->Frequency = parentInfo.Frequency;
    ClockInfo->Parent = parent;
    return EFI_SUCCESS;
  }

  ClockInfo->Frequency =
    (UINT32) ((UINT64) parentInfo.Frequency * pllArmReg.DIV_SELECT / 2);

  ClockInfo->Parent = parent;

  return EFI_SUCCESS;
}

EFI_STATUS
ImxpGetPll2MainClkInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  )
{
  volatile IMX_CCM_ANALOG_REGISTERS *ccmAnalogRegisters =
      (IMX_CCM_ANALOG_REGISTERS *) IMX_CCM_ANALOG_BASE;

  IMX_CCM_ANALOG_PLL_SYS_REG pllSysReg; pllSysReg.AsUint32 =
      MmioRead32 ((UINTN) &ccmAnalogRegisters->PLL_SYS);

  // Determine the reference clock source
  const IMX_CLK parent = ImxpClkFromBypassClkSource (pllSysReg.BYPASS_CLK_SRC);

  IMX_CLOCK_INFO parentInfo;
  EFI_STATUS status = ImxpGetClockInfo (Cache, parent, &parentInfo);
  if (EFI_ERROR (status)) {
    return status;
  }

  if (pllSysReg.BYPASS != 0) {
    ClockInfo->Frequency = parentInfo.Frequency;
    ClockInfo->Parent = parent;
    return EFI_SUCCESS;
  }

  if (pllSysReg.DIV_SELECT == 0) {
    ClockInfo->Frequency = parentInfo.Frequency * 20;
  } else {
    ASSERT (pllSysReg.DIV_SELECT == 1);
    ClockInfo->Frequency = parentInfo.Frequency * 22;
  }

  ClockInfo->Parent = parent;

  return EFI_SUCCESS;
}

EFI_STATUS
ImxpGetArmClkRootInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  )
{
  volatile IMX_CCM_REGISTERS *ccmRegisters = (IMX_CCM_REGISTERS *) IMX_CCM_BASE;

  IMX_CLOCK_INFO pll1Info;
  EFI_STATUS status = ImxpGetClockInfo (Cache, IMX_PLL1_MAIN_CLK, &pll1Info);
  if (EFI_ERROR(status)) {
    return status;
  }

  IMX_CCM_CACRR_REG cacrrReg;cacrrReg.AsUint32 =
      MmioRead32 ((UINTN) &ccmRegisters->CACRR);

  ClockInfo->Frequency = pll1Info.Frequency / (1 + cacrrReg.arm_podf);
  ClockInfo->Parent = IMX_PLL1_MAIN_CLK;

  return EFI_SUCCESS;
}

EFI_STATUS
ImxpGetPrePeriphClkInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  )
{
  volatile IMX_CCM_REGISTERS *ccmRegisters = (IMX_CCM_REGISTERS *) IMX_CCM_BASE;

  IMX_CCM_CBCMR_REG cbcmrReg ; cbcmrReg.AsUint32 = MmioRead32 ((UINTN) &ccmRegisters->CBCMR);

  IMX_CLK parent;
  switch (cbcmrReg.pre_periph_clk_sel) {
  case IMX_CCM_PRE_PERIPH_CLK_SEL_PLL2:
    parent = IMX_PLL2_MAIN_CLK;
    break;
  case IMX_CCM_PRE_PERIPH_CLK_SEL_PLL2_PFD2:
    parent = IMX_PLL2_PFD2;
    break;
  case IMX_CCM_PRE_PERIPH_CLK_SEL_PLL2_PFD0:
    parent = IMX_PLL2_PFD0;
    break;
  case IMX_CCM_PRE_PERIPH_CLK_SEL_PLL2_PFD2_DIV2:
    parent = IMX_PLL2_PFD2;
    break;
  default:
    ASSERT (FALSE);
    return EFI_INVALID_PARAMETER;
  }

  IMX_CLOCK_INFO parentInfo;
  EFI_STATUS status = ImxpGetClockInfo (Cache, parent, &parentInfo);
  if (EFI_ERROR (status)) {
    return status;
  }

  if (cbcmrReg.pre_periph_clk_sel == IMX_CCM_PRE_PERIPH_CLK_SEL_PLL2_PFD2_DIV2) {
    ClockInfo->Frequency = parentInfo.Frequency / 2;
  } else {
    ClockInfo->Frequency = parentInfo.Frequency;
  }

  ClockInfo->Parent = parent;

  return EFI_SUCCESS;
}

VOID ImxpGetOsc24ClkInfo (OUT IMX_CLOCK_INFO *ClockInfo)
{
  ClockInfo->Frequency = IMX_REF_CLK_24M_FREQ;
  ClockInfo->Parent = IMX_CLK_NONE;
}

EFI_STATUS
ImxpGetAhbClkRootInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  )
{
   volatile IMX_CCM_REGISTERS *ccmRegisters = (IMX_CCM_REGISTERS *) IMX_CCM_BASE;

  IMX_CLOCK_INFO parentInfo;
  EFI_STATUS status = ImxpGetClockInfo (Cache, IMX_PERIPH_CLK, &parentInfo);
  if (EFI_ERROR (status)) {
    return status;
  }

  IMX_CCM_CBCDR_REG cbcdrReg; cbcdrReg.AsUint32 =
      MmioRead32 ((UINTN) &ccmRegisters->CBCDR);

  ClockInfo->Frequency = parentInfo.Frequency / (1 + cbcdrReg.ahb_podf);
  ClockInfo->Parent = IMX_PERIPH_CLK;

  return EFI_SUCCESS;
}

EFI_STATUS
ImxpGetIpgClkRootInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  )
{
  volatile IMX_CCM_REGISTERS *ccmRegisters = (IMX_CCM_REGISTERS *) IMX_CCM_BASE;

  IMX_CLOCK_INFO parentInfo;
  EFI_STATUS status = ImxpGetClockInfo (Cache, IMX_AHB_CLK_ROOT, &parentInfo);
  if (EFI_ERROR (status)) {
    return status;
  }

  IMX_CCM_CBCDR_REG cbcdrReg; cbcdrReg.AsUint32 =
      MmioRead32 ((UINTN) &ccmRegisters->CBCDR);

  ClockInfo->Frequency = parentInfo.Frequency / (1 + cbcdrReg.ipg_podf);
  ClockInfo->Parent = IMX_AHB_CLK_ROOT;

  return EFI_SUCCESS;
}

//
// Public functions
//

EFI_STATUS
ImxClkPwrGetClockInfo (
  IMX_CLK ClockId,
  OUT IMX_CLOCK_INFO *ClockInfo
  )
{
  return ImxpGetClockInfo (&ImxpClockPwrCache, ClockId, ClockInfo);
}

