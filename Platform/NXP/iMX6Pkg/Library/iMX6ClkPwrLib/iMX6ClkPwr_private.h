/** @file
*
*  Internal declarations for the IMX6 Clock and Power module
*
*  Copyright (c), Microsoft Corporation. All rights reserved.
*  Copyright 2018 NXP
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
#ifndef _IMX6_CLK_PWR_PRIVATE_H_
#define _IMX6_CLK_PWR_PRIVATE_H_


#ifndef ARRAYSIZE
#define ARRAYSIZE(a) (sizeof(a) / sizeof(a[0]))
#endif // ARRAYSIZE

#ifndef C_ASSERT
#define C_ASSERT(e) typedef char __C_ASSERT__[(e)?1:-1]
#endif // C_ASSERT

typedef enum {
  IMX_PLL_PFD0,
  IMX_PLL_PFD1,
  IMX_PLL_PFD2,
  IMX_PLL_PFD3,
} IMX_PLL_PFD;

typedef struct {
  UINT16 RegisterIndex;   // Register index (0-6)
  UINT16 GateNumber;      // Gate number within register (0-15)
} IMX_CCGR_INDEX;

IMX_CCGR_INDEX ImxpCcgrIndexFromClkGate (IMX_CLK_GATE ClockGate);

#define _BITS_PER_UINTN (8 * sizeof(UINTN))

typedef struct {
  UINTN Valid[(IMX_CLK_MAX + _BITS_PER_UINTN) / _BITS_PER_UINTN];
  IMX_CLOCK_INFO Table[IMX_CLK_MAX];
} IMX_CLOCK_TREE_CACHE;

VOID ImxpClkPwrCacheReset ();

IMX_CLK ImxpClkFromBypassClkSource (IMX_PLL_BYPASS_CLK_SRC BypassClockSource);

VOID ImxCcmConfigureGpuClockTree ();

VOID ImxCcmConfigureIPUDIxClockTree ();

VOID ImxCcmConfigureIPULDBxClockTree ();

#if (defined(CPU_IMX6DQ) || defined(CPU_IMX6SDL))
VOID ImxSetClockRatePLL5 (UINT32 ClockRate, IMX_CCM_PLL_VIDEO_CTRL_POST_DIV_SELECT PostDivSelect);
#elif defined(CPU_IMX6SX)
VOID ImxSetClockRatePLL5 (UINT32 TargetClockRate, UINT32 PreDividerLcdif1Val, UINT32 PostDividerLcdif1Val);
#else
#error iMX6 CPU Type Not Defined! 
#endif

//
// Clock Info functions
//

EFI_STATUS
ImxpGetClockInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  IN IMX_CLK ClockId,
  OUT IMX_CLOCK_INFO *ClockInfo
  );

VOID ImxpGetOsc24ClkInfo (OUT IMX_CLOCK_INFO *ClockInfo);

EFI_STATUS
ImxpGetPll1MainClkInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  );

EFI_STATUS
ImxpGetPll2MainClkInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  );

EFI_STATUS
ImxpGetPll2PfdClkInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  IMX_PLL_PFD PfdIndex,
  OUT IMX_CLOCK_INFO *ClockInfo
  );

EFI_STATUS
ImxpGetPll3MainClkInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  );

EFI_STATUS
ImxpGetPll3PfdClkInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  IMX_PLL_PFD PfdIndex,
  OUT IMX_CLOCK_INFO *ClockInfo
  );

EFI_STATUS
ImxpGetPll3SwClkInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  );

EFI_STATUS
ImxpGetAxiClkRootInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  );

EFI_STATUS
ImxpGetPeriphClkInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  );

EFI_STATUS
ImxpGetPrePeriphClkInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  );

EFI_STATUS
ImxpGetPeriphClk2Info (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  );

EFI_STATUS
ImxpGetArmClkRootInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  );

EFI_STATUS
ImxpGetMmdcCh0ClkRootInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  );

EFI_STATUS
ImxpGetAhbClkRootInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  );

EFI_STATUS
ImxpGetIpgClkRootInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  );

EFI_STATUS
ImxpGetGpu2dAxiClkRootInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  );

EFI_STATUS
ImxpGetGpu3dAxiClkRootInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  );

EFI_STATUS
ImxpGetGpu2dCoreClkInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  );

EFI_STATUS
ImxpGetGpu3dCoreClkInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  );

EFI_STATUS
ImxpGetGpu3dShaderClkInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  );

//
// Power functions
//

VOID ImxEnableGpuVpuPowerDomain ();

VOID ImxDisableGpuVpuPowerDomain ();

#endif // _IMX6_CLK_PWR_PRIVATE_H_
