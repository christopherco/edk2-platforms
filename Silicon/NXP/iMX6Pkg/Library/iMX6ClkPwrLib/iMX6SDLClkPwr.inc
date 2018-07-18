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

#ifndef CPU_IMX6SDL
#error iMX6SDLClkPwr.inc should not be compiled for non iMX6 SDL platform.
#endif

/**
  Get the CCGR register index and gate number for a clock gate.
**/

IMX_CCGR_INDEX ImxpCcgrIndexFromClkGate (IMX_CLK_GATE ClockGate)
{
  static const IMX_CCGR_INDEX ImxpCcgrIndexMap[] = {
    {0, 0},  // MX6_AIPS_TZ1_CLK_ENABLE
    {0, 1},  // MX6_AIPS_TZ2_CLK_ENABLE
    {0, 2},  // MX6_APBHDMA_HCLK_ENABLE
    {0, 3},  // MX6_ASRC_CLK_ENABLE
    {0, 4},  // MX6_CAAM_SECURE_MEM_CLK_ENABLE
    {0, 5},  // MX6_CAAM_WRAPPER_ACLK_ENABLE
    {0, 6},  // MX6_CAAM_WRAPPER_IPG_ENABLE
    {0, 7},  // MX6_CAN1_CLK_ENABLE
    {0, 8},  // MX6_CAN1_SERIAL_CLK_ENABLE
    {0, 9},  // MX6_CAN2_CLK_ENABLE
    {0, 10}, // MX6_CAN2_SERIAL_CLK_ENABLE
    {0, 11}, // MX6_ARM_DBG_CLK_ENABLE
    {0, 12}, // MX6_DCIC1_CLK_ENABLE
    {0, 13}, // MX6_DCIC2_CLK_ENABLE
    {0, 14}, // MX6_DTCP_CLK_ENABLE
    {1, 0},  // MX6_ECSPI1_CLK_ENABLE
    {1, 1},  // MX6_ECSPI2_CLK_ENABLE
    {1, 2},  // MX6_ECSPI3_CLK_ENABLE
    {1, 3},  // MX6_ECSPI4_CLK_ENABLE
    {1, 4},  // MX6_ECSPI5_CLK_ENABLE
    {1, 5},  // MX6_ENET_CLK_ENABLE
    {1, 6},  // MX6_EPIT1_CLK_ENABLE
    {1, 7},  // MX6_EPIT2_CLK_ENABLE
    {1, 8},  // MX6_ESAI_CLK_ENABLE
    {1, 10}, // MX6_GPT_CLK_ENABLE
    {1, 11}, // MX6_GPT_SERIAL_CLK_ENABLE
    {1, 12}, // MX6_GPU2D_CLK_ENABLE
    {1, 13}, // MX6_GPU3D_CLK_ENABLE
    {2, 0},  // MX6_HDMI_TX_ENABLE
    {2, 2},  // MX6_HDMI_TX_ISFRCLK_ENABLE
    {2, 3},  // MX6_I2C1_SERIAL_CLK_ENABLE
    {2, 4},  // MX6_I2C2_SERIAL_CLK_ENABLE
    {2, 5},  // MX6_I2C3_SERIAL_CLK_ENABLE
    {2, 6},  // MX6_IIM_CLK_ENABLE
    {2, 7},  // MX6_IOMUX_IPT_CLK_IO_ENABLE
    {2, 8},  // MX6_IPMUX1_CLK_ENABLE
    {2, 9},  // MX6_IPMUX2_CLK_ENABLE
    {2, 10}, // MX6_IPMUX3_CLK_ENABLE
    {2, 11}, // MX6_IPSYNC_IP2APB_TZASC1_IPG_MASTER_CLK_ENABLE
    {2, 12}, // MX6_IPSYNC_IP2APB_TZASC2_IPG_MASTER_CLK_ENABLE
    {2, 13}, // MX6_IPSYNC_VDOA_IPG_MASTER_CLK_ENABLE
    {3, 0},  // MX6_IPU1_IPU_CLK_ENABLE
    {3, 1},  // MX6_IPU1_IPU_DI0_CLK_ENABLE
    {3, 2},  // MX6_IPU1_IPU_DI1_CLK_ENABLE
    {3, 3},  // MX6_IPU2_IPU_CLK_ENABLE
    {3, 4},  // MX6_IPU2_IPU_DI0_CLK_ENABLE
    {3, 5},  // MX6_IPU2_IPU_DI1_CLK_ENABLE
    {3, 6},  // MX6_LDB_DI0_CLK_ENABLE
    {3, 7},  // MX6_LDB_DI1_CLK_ENABLE
    {3, 8},  // MX6_MIPI_CORE_CFG_CLK_ENABLE
    {3, 9},  // MX6_MLB_CLK_ENABLE
    {3, 10}, // MX6_MMDC_CORE_ACLK_FAST_CORE_P0_ENABLE
    {3, 12}, // MX6_MMDC_CORE_IPG_CLK_P0_ENABLE
    {3, 14}, // MX6_OCRAM_CLK_ENABLE
    {3, 15}, // MX6_OPENVGAXICLK_CLK_ROOT_ENABLE
    {4, 0},  // MX6_PCIE_ROOT_ENABLE
    {4, 4},  // MX6_PL301_MX6QFAST1_S133CLK_ENABLE
    {4, 6},  // MX6_PL301_MX6QPER1_BCHCLK_ENABLE
    {4, 7},  // MX6_PL301_MX6QPER2_MAINCLK_ENABLE
    {4, 8},  // MX6_PWM1_CLK_ENABLE
    {4, 9},  // MX6_PWM2_CLK_ENABLE
    {4, 10}, // MX6_PWM3_CLK_ENABLE
    {4, 11}, // MX6_PWM4_CLK_ENABLE
    {4, 12}, // MX6_RAWNAND_U_BCH_INPUT_APB_CLK_ENABLE
    {4, 13}, // MX6_RAWNAND_U_GPMI_BCH_INPUT_BCH_CLK_ENABLE
    {4, 14}, // MX6_RAWNAND_U_GPMI_BCH_INPUT_GPMI_IO_CLK_ENABLE
    {4, 15}, // MX6_RAWNAND_U_GPMI_INPUT_APB_CLK_ENABLE
    {5, 0},  // MX6_ROM_CLK_ENABLE
    {5, 2},  // MX6_SATA_CLK_ENABLE
    {5, 3},  // MX6_SDMA_CLK_ENABLE
    {5, 6},  // MX6_SPBA_CLK_ENABLE
    {5, 7},  // MX6_SPDIF_CLK_ENABLE
    {5, 9},  // MX6_SSI1_CLK_ENABLE
    {5, 10}, // MX6_SSI2_CLK_ENABLE
    {5, 11}, // MX6_SSI3_CLK_ENABLE
    {5, 12}, // MX6_UART_CLK_ENABLE
    {5, 13}, // MX6_UART_SERIAL_CLK_ENABLE
    {6, 0},  // MX6_USBOH3_CLK_ENABLE
    {6, 1},  // MX6_USDHC1_CLK_ENABLE
    {6, 2},  // MX6_USDHC2_CLK_ENABLE
    {6, 3},  // MX6_USDHC3_CLK_ENABLE
    {6, 4},  // MX6_USDHC4_CLK_ENABLE
    {6, 5},  // MX6_EIM_SLOW_CLK_ENABLE
    {6, 6},  // MX6_VDOAXICLK_CLK_ENABLE
    {6, 7},  // MX6_VPU_CLK_ENABLE
  };

  return ImxpCcgrIndexMap[ClockGate];
}

CONST CHAR16 *StringFromImxClk (IMX_CLK Value)
{
  switch (Value) {
  case IMX_CLK_NONE: return L"(none)";
  case IMX_OSC_CLK: return L"OSC_CLK";
  case IMX_PLL1_MAIN_CLK: return L"PLL1_MAIN_CLK";
  case IMX_PLL2_MAIN_CLK: return L"PLL2_MAIN_CLK";
  case IMX_PLL2_PFD0: return L"PLL2_PFD0";
  case IMX_PLL2_PFD1: return L"PLL2_PFD1";
  case IMX_PLL2_PFD2: return L"PLL2_PFD2";
  case IMX_PLL3_MAIN_CLK: return L"PLL3_MAIN_CLK";
  case IMX_PLL3_PFD0: return L"PLL3_PFD0";
  case IMX_PLL3_PFD1: return L"PLL3_PFD1";
  case IMX_PLL3_PFD2: return L"PLL3_PFD2";
  case IMX_PLL3_PFD3: return L"PLL3_PFD3";
  case IMX_PLL4_MAIN_CLK: return L"PLL4_MAIN_CLK";
  case IMX_PLL5_MAIN_CLK: return L"PLL5_MAIN_CLK";
  case IMX_CLK1: return L"CLK1";
  case IMX_CLK2: return L"CLK2";
  case IMX_PLL1_SW_CLK: return L"PLL1_SW_CLK";
  case IMX_STEP_CLK: return L"STEP_CLK";
  case IMX_PLL3_SW_CLK: return L"PLL3_SW_CLK";
  case IMX_AXI_ALT: return L"AXI_ALT";
  case IMX_AXI_CLK_ROOT: return L"AXI_CLK_ROOT";
  case IMX_PERIPH_CLK2: return L"PERIPH_CLK2";
  case IMX_PERIPH_CLK: return L"PERIPH_CLK";
  case IMX_PRE_PERIPH_CLK: return L"PRE_PERIPH_CLK";
  case IMX_PRE_PERIPH2_CLK: return L"PRE_PERIPH2_CLK";
  case IMX_PERIPH2_CLK: return L"PERIPH2_CLK";
  case IMX_ARM_CLK_ROOT: return L"ARM_CLK_ROOT";
  case IMX_MMDC_CH0_CLK_ROOT: return L"MMDC_CH0_CLK_ROOT";
  case IMX_MMDC_CH1_CLK_ROOT: return L"MMDC_CH1_CLK_ROOT";
  case IMX_AHB_CLK_ROOT: return L"AHB_CLK_ROOT";
  case IMX_IPG_CLK_ROOT: return L"IPG_CLK_ROOT";
  case IMX_PERCLK_CLK_ROOT: return L"PERCLK_CLK_ROOT";
  case IMX_USDHC1_CLK_ROOT: return L"USDHC1_CLK_ROOT";
  case IMX_USDHC2_CLK_ROOT: return L"USDHC2_CLK_ROOT";
  case IMX_USDHC3_CLK_ROOT: return L"USDHC3_CLK_ROOT";
  case IMX_USDHC4_CLK_ROOT: return L"USDHC4_CLK_ROOT";
  case IMX_SSI1_CLK_ROOT: return L"SSI1_CLK_ROOT";
  case IMX_SSI2_CLK_ROOT: return L"SSI2_CLK_ROOT";
  case IMX_SSI3_CLK_ROOT: return L"SSI3_CLK_ROOT";
  case IMX_GPU2D_AXI_CLK_ROOT: return L"GPU2D_AXI_CLK_ROOT";
  case IMX_GPU3D_AXI_CLK_ROOT: return L"GPU3D_AXI_CLK_ROOT";
  case IMX_PCIE_AXI_CLK_ROOT: return L"PCIE_AXI_CLK_ROOT";
  case IMX_VDO_AXI_CLK_ROOT: return L"VDO_AXI_CLK_ROOT";
  case IMX_IPU1_HSP_CLK_ROOT: return L"IPU1_HSP_CLK_ROOT";
  case IMX_GPU2D_CORE_CLK_ROOT: return L"GPU2D_CORE_CLK_ROOT";
  case IMX_ACLK_EIM_SLOW_CLK_ROOT: return L"ACLK_EIM_SLOW_CLK_ROOT";
  case IMX_ACLK_CLK_ROOT: return L"ACLK_CLK_ROOT";
  case IMX_ENFC_CLK_ROOT: return L"ENFC_CLK_ROOT";
  case IMX_GPU3D_CORE_CLK_ROOT: return L"GPU3D_CORE_CLK_ROOT";
  case IMX_GPU3D_SHADER_CLK_ROOT: return L"GPU3D_SHADER_CLK_ROOT";
  case IMX_VPU_AXI_CLK_ROOT: return L"VPU_AXI_CLK_ROOT";
  case IMX_IPU1_DI0_CLK_ROOT: return L"IPU1_DI0_CLK_ROOT";
  case IMX_IPU1_DI1_CLK_ROOT: return L"IPU1_DI1_CLK_ROOT";
  case IMX_LDB_DI0_SERIAL_CLK_ROOT: return L"LDB_DI0_SERIAL_CLK_ROOT";
  case IMX_LDB_DI0_IPU: return L"LDB_DI0_IPU";
  case IMX_LDB_DI1_SERIAL_CLK_ROOT: return L"LDB_DI1_SERIAL_CLK_ROOT";
  case IMX_LDB_DI1_IPU: return L"LDB_DI1_IPU";
  case IMX_SPDIF0_CLK_ROOT: return L"SPDIF0_CLK_ROOT";
  case IMX_SPDIF1_CLK_ROOT: return L"SPDIF1_CLK_ROOT";
  case IMX_ESAI_CLK_ROOT: return L"ESAI_CLK_ROOT";
  case IMX_HSI_TX_CLK_ROOT: return L"HSI_TX_CLK_ROOT";
  case IMX_CAN_CLK_ROOT: return L"CAN_CLK_ROOT";
  case IMX_ECSPI_CLK_ROOT: return L"ECSPI_CLK_ROOT";
  case IMX_UART_CLK_ROOT: return L"UART_CLK_ROOT";
  case IMX_VIDEO_27M_CLK_ROOT: return L"VIDEO_27M_CLK_ROOT";
  default:
    ASSERT (FALSE);
    return L"[invalid IMX_CLK value]";
  }
}

IMX_CLK ImxpClkFromBypassClkSource (IMX_PLL_BYPASS_CLK_SRC BypassClockSource)
{
  switch (BypassClockSource) {
  case IMX_PLL_BYPASS_CLK_SRC_REF_CLK_24M:
    return IMX_OSC_CLK;
  case IMX_PLL_BYPASS_CLK_SRC_CLK1:
    return IMX_CLK1;
  case IMX_PLL_BYPASS_CLK_SRC_CLK2:
    return IMX_CLK2;
  case IMX_PLL_BYPASS_CLK_SRC_XOR:
  default:
    ASSERT (FALSE);
    return IMX_CLK_NONE;
  }
}

/**
  Configure the GPU clock tree so that GPU2D and GPU3D are clocked from
  the AXI clock root and are within the allowed frequency range.

  The GPU must be powered down, and GPU clocks must be gated when this
  function is called.
**/
VOID ImxCcmConfigureGpuClockTree ()
{
  volatile IMX_CCM_REGISTERS *ccmRegisters = (IMX_CCM_REGISTERS *) IMX_CCM_BASE;

  IMX_CCM_CBCMR_REG cbcmrReg ; cbcmrReg.AsUint32 = MmioRead32 ((UINTN) &ccmRegisters->CBCMR);

  cbcmrReg.gpu2d_axi_clk_sel = IMX_CCM_GPU2D_AXI_CLK_SEL_AXI;
  cbcmrReg.gpu3d_axi_clk_sel = IMX_CCM_GPU3D_AXI_CLK_SEL_AXI;

  cbcmrReg.gpu2d_core_clk_sel = IMX_CCM_GPU2D_CORE_CLK_SEL_PLL2_PFD0;
  cbcmrReg.gpu3d_core_clk_sel = IMX_CCM_GPU3D_CORE_CLK_SEL_MMDC_CH0_AXI;
  cbcmrReg.gpu3d_shader_clk_sel = IMX_CCM_GPU3D_SHADER_CLK_SEL_MMDC_CH0_AXI;

  cbcmrReg.gpu2d_core_clk_podf = 0;
  cbcmrReg.gpu3d_core_podf = 0;
  cbcmrReg.gpu3d_shader_podf = 0;

  ImxpClkPwrCacheReset ();
  MmioWrite32 ((UINTN) &ccmRegisters->CBCMR, cbcmrReg.AsUint32);
}

/**
    Configure all of DIx clock tree for IPU1. For flexibility
    purpose use PLL5 (PLL Video) as main reference clock. PLL 5 has flexible
    divider making it easily configurable. Muxing and clock programming needs
    when to be updated when supporting multiple display.
**/
VOID ImxCcmConfigureIPUDIxClockTree ()
{
    volatile IMX_CCM_REGISTERS* ccmRegisters = (IMX_CCM_REGISTERS*) IMX_CCM_BASE;
    IMX_CCM_CHSCCDR_REG chscddrReg;

    chscddrReg.AsUint32 = MmioRead32((UINTN)&ccmRegisters->CHSCCDR);    // CCM HSC Clock Divider Register

    // Setup muxing to pre-mux
    chscddrReg.ipu1_di0_clk_sel = IMX_CHSCCDR_IPU1_DI0_CLK_SEL_PREMUX;          // 0 - derive clock from mmdc_ch0 clock
    chscddrReg.ipu1_di1_clk_sel = IMX_CHSCCDR_IPU1_DI1_CLK_SEL_PREMUX;          // 0 - derive clock from divided pre-muxed ipu1 di1 clock
    chscddrReg.ipu1_di0_podf = IMX_CHSCCDR_IPU1_DI0_PODF_DIV_1;                 // 0 - divide by 1
    chscddrReg.ipu1_di1_podf = IMX_CHSCCDR_IPU1_DI1_PODF_DIV_1;                 // 0 - divide by 1
    chscddrReg.ipu1_di0_pre_clk_sel = IMX_CHSCCDR_IPU1_DI0_PRE_CLK_SEL_PLL5;    // 2 - derive clock from pll5
    chscddrReg.ipu1_di1_pre_clk_sel = IMX_CHSCCDR_IPU1_DI1_PRE_CLK_SEL_PLL5;    // 2 - derive clock from pll5

    MmioWrite32 ((UINTN)&ccmRegisters->CHSCCDR, chscddrReg.AsUint32);
}

/**
    Configure PLL 5 clock rate to the desired clock rate
**/
VOID ImxSetClockRatePLL5 (
    UINT32 ClockRate,
    IMX_CCM_PLL_VIDEO_CTRL_POST_DIV_SELECT PostDivSelect
    )
{
    // Use clock rate as denom for simple fractional calculation
    UINT32 denom = IMX_REF_CLK_24M_FREQ;
    UINT32 divSelect = ClockRate / IMX_REF_CLK_24M_FREQ; // Signed value
    UINT32 numerator = ClockRate % IMX_REF_CLK_24M_FREQ;
    volatile IMX_CCM_ANALOG_REGISTERS *ccmAnalogRegisters =
        (IMX_CCM_ANALOG_REGISTERS *)IMX_CCM_ANALOG_BASE;
    IMX_CCM_PLL_VIDEO_CTRL_REG pllVideoCtrlReg; pllVideoCtrlReg.AsUint32 =
        MmioRead32 ((UINTN)&ccmAnalogRegisters->PLL_VIDEO);

    ASSERT (numerator < denom);
    ASSERT ((divSelect >= 27) && (divSelect <= 54));

    // PLL output frequency = Fref * (DIV_SELECT + NUM / DENOM)
    // Use the clock rate as denomitor to make fractional calulation simple
    pllVideoCtrlReg.DIV_SELECT = divSelect;
    pllVideoCtrlReg.POST_DIV_SELECT = PostDivSelect;

    MmioWrite32(
        (UINTN)&ccmAnalogRegisters->PLL_VIDEO, pllVideoCtrlReg.AsUint32);
    MmioWrite32(
        (UINTN)&ccmAnalogRegisters->PLL_VIDEO_NUM, numerator);
    MmioWrite32(
        (UINTN)&ccmAnalogRegisters->PLL_VIDEO_DENOM, denom);

    pllVideoCtrlReg.AsUint32 = MmioRead32(
        (UINTN)&ccmAnalogRegisters->PLL_VIDEO);

    // Check to see if pll is locked, if not attempt to enable it
    if (pllVideoCtrlReg.LOCK == 0) {
        UINT32 counter = 10000;
        {
            IMX_CCM_PLL_VIDEO_CTRL_REG pllVideoCtrlClearReg = { 0 };
            pllVideoCtrlClearReg.POWERDOWN = 1;
            MmioWrite32(
                (UINTN)&ccmAnalogRegisters->PLL_VIDEO_CLR,
                pllVideoCtrlClearReg.AsUint32);
        }
        pllVideoCtrlReg.AsUint32 = MmioRead32(
            (UINTN)&ccmAnalogRegisters->PLL_VIDEO);
        {
            IMX_CCM_PLL_VIDEO_CTRL_REG pllVideoCtrlSetReg = { 0 };
            pllVideoCtrlSetReg.ENABLE = 1;
            MmioWrite32(
                (UINTN)&ccmAnalogRegisters->PLL_VIDEO_SET,
                pllVideoCtrlSetReg.AsUint32);
        }
        pllVideoCtrlReg.AsUint32 = MmioRead32(
            (UINTN)&ccmAnalogRegisters->PLL_VIDEO);
        {
            IMX_CCM_PLL_VIDEO_CTRL_REG pllVideoCtrlClearReg = { 0 };
            pllVideoCtrlClearReg.BYPASS = 1;
            MmioWrite32(
                (UINTN)&ccmAnalogRegisters->PLL_VIDEO_CLR,
                pllVideoCtrlClearReg.AsUint32);
        }
        pllVideoCtrlReg.AsUint32 = MmioRead32(
            (UINTN)&ccmAnalogRegisters->PLL_VIDEO);
        do {
            pllVideoCtrlReg.AsUint32 = MmioRead32(
                (UINTN)&ccmAnalogRegisters->PLL_VIDEO);
            --counter;
        } while ((pllVideoCtrlReg.LOCK == 0) && (counter > 0));
        ASSERT (counter > 0);
    }
}

EFI_STATUS
ImxpGetPll2PfdClkInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  IMX_PLL_PFD PfdIndex,
  OUT IMX_CLOCK_INFO *ClockInfo
  )
{
  volatile IMX_CCM_ANALOG_REGISTERS *ccmAnalogRegisters =
      (IMX_CCM_ANALOG_REGISTERS *) IMX_CCM_ANALOG_BASE;

  IMX_CCM_PFD_528_REG pfd528Reg; pfd528Reg.AsUint32 =
      MmioRead32 ((UINTN) &ccmAnalogRegisters->PFD_528);

  UINT32 pfdFrac;
  switch (PfdIndex) {
  case IMX_PLL_PFD0:
    pfdFrac = pfd528Reg.PFD0_FRAC;
    break;
  case IMX_PLL_PFD1:
    pfdFrac = pfd528Reg.PFD1_FRAC;
    break;
  case IMX_PLL_PFD2:
    pfdFrac = pfd528Reg.PFD2_FRAC;
    break;
  default:
    ASSERT (FALSE);
    return EFI_INVALID_PARAMETER;
  }

  IMX_CLOCK_INFO parentInfo;
  EFI_STATUS status = ImxpGetClockInfo (Cache, IMX_PLL2_MAIN_CLK, &parentInfo);
  if (EFI_ERROR (status)) {
    return status;
  }

  // The resulting frequency shall be 528*18/PFDn_FRAC
  // where PFD0_FRAC is in the range 12-35.
  ASSERT ((pfdFrac >= 12) && (pfdFrac <= 35));
  ClockInfo->Frequency = (UINT32) ((UINT64) parentInfo.Frequency * 18 / pfdFrac);
  ClockInfo->Parent = IMX_PLL2_MAIN_CLK;

  return EFI_SUCCESS;
}

EFI_STATUS
ImxpGetAxiClkRootInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  )
{
  volatile IMX_CCM_REGISTERS *ccmRegisters = (IMX_CCM_REGISTERS *) IMX_CCM_BASE;

  IMX_CCM_CBCDR_REG cbcdrReg; cbcdrReg.AsUint32 =
      MmioRead32 ((UINTN) &ccmRegisters->CBCDR);

  IMX_CLK parent;
  if (cbcdrReg.axi_sel == IMX_CCM_AXI_SEL_PERIPH_CLK) {
    parent = IMX_PERIPH_CLK;
  } else {
    ASSERT (cbcdrReg.axi_sel == IMX_CCM_AXI_SEL_AXI_ALT);
    parent = IMX_AXI_ALT;
  }

  IMX_CLOCK_INFO parentInfo;
  EFI_STATUS status = ImxpGetClockInfo (Cache, parent, &parentInfo);
  if (EFI_ERROR (status)) {
    return status;
  }

  ClockInfo->Frequency = parentInfo.Frequency / (1 + cbcdrReg.axi_podf);
  ClockInfo->Parent = parent;

  return EFI_SUCCESS;
}

EFI_STATUS
ImxpGetGpu2dCoreClkInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  )
{
  volatile IMX_CCM_REGISTERS *ccmRegisters = (IMX_CCM_REGISTERS *) IMX_CCM_BASE;

  IMX_CCM_CBCMR_REG cbcmrReg ; cbcmrReg.AsUint32 = MmioRead32 ((UINTN) &ccmRegisters->CBCMR);

  IMX_CLK parent;
  switch (cbcmrReg.gpu2d_core_clk_sel) {
  case IMX_CCM_GPU2D_CORE_CLK_SEL_AXI:
    parent = IMX_AXI_CLK_ROOT;
    break;
  case IMX_CCM_GPU2D_CORE_CLK_SEL_PLL3_SW:
    parent = IMX_PLL3_SW_CLK;
    break;
  case IMX_CCM_GPU2D_CORE_CLK_SEL_PLL2_PFD0:
    parent = IMX_PLL2_PFD0;
    break;
  case IMX_CCM_GPU2D_CORE_CLK_SEL_PLL2_PFD2:
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

  ClockInfo->Frequency =
      parentInfo.Frequency / (1 + cbcmrReg.gpu2d_core_clk_podf);
  ClockInfo->Parent = parent;

  if (ClockInfo->Frequency > IMX_GPU2D_CORE_CLK_MAX) {
    DEBUG ((
      DEBUG_WARN,
      "GPU2D_CORE_CLK exceeds maximum. (Value = %d, Max = %d)\r\n",
      ClockInfo->Frequency,
      IMX_GPU2D_CORE_CLK_MAX));
  }

  return EFI_SUCCESS;
}

EFI_STATUS
ImxpGetGpu3dCoreClkInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  )
{
  volatile IMX_CCM_REGISTERS *ccmRegisters = (IMX_CCM_REGISTERS *) IMX_CCM_BASE;

  IMX_CCM_CBCMR_REG cbcmrReg ; cbcmrReg.AsUint32 = MmioRead32 ((UINTN) &ccmRegisters->CBCMR);

  IMX_CLK parent;
  switch (cbcmrReg.gpu3d_core_clk_sel) {
  case IMX_CCM_GPU3D_CORE_CLK_SEL_MMDC_CH0_AXI:
    parent = IMX_MMDC_CH0_CLK_ROOT;
    break;
  case IMX_CCM_GPU3D_CORE_CLK_SEL_PLL3_SW:
    parent = IMX_PLL3_SW_CLK;
    break;
  case IMX_CCM_GPU3D_CORE_CLK_SEL_PLL2_PFD1:
    parent = IMX_PLL2_PFD1;
    break;
  case IMX_CCM_GPU3D_CORE_CLK_SEL_PLL2_PFD2:
    parent = IMX_PLL2_PFD2;
    break;
  default:
    ASSERT (FALSE);
    return EFI_UNSUPPORTED;
  }

  IMX_CLOCK_INFO parentInfo;
  EFI_STATUS status = ImxpGetClockInfo (Cache, parent, &parentInfo);
  if (EFI_ERROR (status)) {
    return status;
  }

  ClockInfo->Frequency = parentInfo.Frequency / (1 + cbcmrReg.gpu3d_core_podf);
  ClockInfo->Parent = parent;

  if (ClockInfo->Frequency > IMX_GPU3D_CORE_CLK_MAX) {
    DEBUG ((
      DEBUG_WARN,
      "GPU3D_CORE_CLK exceeds maximum. (Value = %d, Max = %d)\r\n",
      ClockInfo->Frequency,
      IMX_GPU3D_CORE_CLK_MAX));
  }

  return EFI_SUCCESS;
}

EFI_STATUS
ImxpGetGpu3dShaderClkInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  )
{
  volatile IMX_CCM_REGISTERS *ccmRegisters = (IMX_CCM_REGISTERS *) IMX_CCM_BASE;

  IMX_CCM_CBCMR_REG cbcmrReg ; cbcmrReg.AsUint32 = MmioRead32 ((UINTN) &ccmRegisters->CBCMR);

  IMX_CLK parent;
  switch (cbcmrReg.gpu3d_shader_clk_sel) {
  case IMX_CCM_GPU3D_SHADER_CLK_SEL_MMDC_CH0_AXI:
    parent = IMX_MMDC_CH0_CLK_ROOT;
    break;
  case IMX_CCM_GPU3D_SHADER_CLK_SEL_PLL3_SW:
    parent = IMX_PLL3_SW_CLK;
    break;
  case IMX_CCM_GPU3D_SHADER_CLK_SEL_PLL2_PFD1:
    parent = IMX_PLL2_PFD1;
    break;
  case IMX_CCM_GPU3D_SHADER_CLK_SEL_PLL3_PFD0:
    parent = IMX_PLL3_PFD0;
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

  ClockInfo->Frequency =
      parentInfo.Frequency / (1 + cbcmrReg.gpu3d_shader_podf);

  ClockInfo->Parent = parent;

  return EFI_SUCCESS;
}

EFI_STATUS
ImxpGetPeriphClk2Info (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  )
{
  volatile IMX_CCM_REGISTERS *ccmRegisters = (IMX_CCM_REGISTERS *) IMX_CCM_BASE;

  IMX_CCM_CBCMR_REG cbcmrReg; cbcmrReg.AsUint32 =
      MmioRead32 ((UINTN) &ccmRegisters->CBCMR);

  IMX_CLK parent;
  switch (cbcmrReg.periph_clk2_sel) {
  case IMX_CCM_PERIPH_CLK2_SEL_PLL3_SW_CLK:
    parent = IMX_PLL3_SW_CLK;
    break;
  case IMX_CCM_PERIPH_CLK2_SEL_OSC_CLK:
    parent = IMX_OSC_CLK;
    break;
  case IMX_CCM_PERIPH_CLK2_SEL_PLL2:
    parent = IMX_PLL2_MAIN_CLK;
    break;
  default:
    ASSERT (FALSE);
    return EFI_INVALID_PARAMETER;
  }

  IMX_CCM_CBCDR_REG cbcdrReg; cbcdrReg.AsUint32 =
      MmioRead32 ((UINTN) &ccmRegisters->CBCDR);

  IMX_CLOCK_INFO parentInfo;
  EFI_STATUS status = ImxpGetClockInfo (Cache, parent, &parentInfo);
  if (EFI_ERROR (status)) {
    return status;
  }

  ClockInfo->Frequency = parentInfo.Frequency / (1 + cbcdrReg.periph_clk2_podf);
  ClockInfo->Parent = parent;

  return EFI_SUCCESS;
}

EFI_STATUS
ImxpGetPeriphClkInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  )
{
  volatile IMX_CCM_REGISTERS *ccmRegisters = (IMX_CCM_REGISTERS *) IMX_CCM_BASE;

  IMX_CCM_CBCDR_REG cbcdrReg; cbcdrReg.AsUint32 =
      MmioRead32 ((UINTN) &ccmRegisters->CBCDR);

  IMX_CLK parent;

  // NOTE: periph_clk_sel is OR'd with PLL_bypass_en2 (from jtag) to
  //       produce the input value to the MUX. We assume PLL_bypass_en2 is 0.
  if (cbcdrReg.periph_clk_sel == 0) {
    parent = IMX_PRE_PERIPH_CLK;
  } else {
    ASSERT (cbcdrReg.periph_clk_sel == 1);
    parent = IMX_PERIPH_CLK2;
  }

  IMX_CLOCK_INFO parentInfo;
  EFI_STATUS status = ImxpGetClockInfo (Cache, parent, &parentInfo);
  if (EFI_ERROR (status)) {
    return status;
  }

  ClockInfo->Frequency = parentInfo.Frequency / (1 + cbcdrReg.mmdc_ch0_axi_podf);
  ClockInfo->Parent = parent;

  return EFI_SUCCESS;
}

EFI_STATUS
ImxpGetMmdcCh0ClkRootInfo (
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

  ClockInfo->Frequency =
      parentInfo.Frequency / (1 + cbcdrReg.mmdc_ch0_axi_podf);
  ClockInfo->Parent = IMX_PERIPH_CLK;

  return EFI_SUCCESS;
}

EFI_STATUS
ImxpGetGpu2dAxiClkRootInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  )
{
  volatile IMX_CCM_REGISTERS *ccmRegisters = (IMX_CCM_REGISTERS *) IMX_CCM_BASE;

  IMX_CCM_CBCMR_REG cbcmrReg ; cbcmrReg.AsUint32 = MmioRead32 ((UINTN) &ccmRegisters->CBCMR);

  IMX_CLK parent;
  if (cbcmrReg.gpu2d_axi_clk_sel == IMX_CCM_GPU2D_AXI_CLK_SEL_AXI) {
    parent = IMX_AXI_CLK_ROOT;
  } else {
    ASSERT (cbcmrReg.gpu2d_axi_clk_sel == IMX_CCM_GPU2D_AXI_CLK_SEL_AHB);
    parent = IMX_AHB_CLK_ROOT;
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
ImxpGetGpu3dAxiClkRootInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  OUT IMX_CLOCK_INFO *ClockInfo
  )
{
  volatile IMX_CCM_REGISTERS *ccmRegisters = (IMX_CCM_REGISTERS *) IMX_CCM_BASE;

  IMX_CCM_CBCMR_REG cbcmrReg ; cbcmrReg.AsUint32 = MmioRead32 ((UINTN) &ccmRegisters->CBCMR);

  IMX_CLK parent;
  if (cbcmrReg.gpu3d_axi_clk_sel == IMX_CCM_GPU3D_AXI_CLK_SEL_AXI) {
    parent = IMX_AXI_CLK_ROOT;
  } else {
    ASSERT (cbcmrReg.gpu3d_axi_clk_sel == IMX_CCM_GPU3D_AXI_CLK_SEL_AHB);
    parent = IMX_AHB_CLK_ROOT;
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

VOID ImxEnableGpuVpuPowerDomain ()
{
  volatile IMX_CCM_ANALOG_REGISTERS *analogRegisters =
    (IMX_CCM_ANALOG_REGISTERS *) IMX_CCM_ANALOG_BASE;

  volatile IMX_GPC_REGISTERS *gpcRegisters = (IMX_GPC_REGISTERS *) IMX_GPC_BASE;
  volatile IMX_GPC_PGC_REGISTERS *gpuPgcRegisters = &gpcRegisters->PGC_GPU;

  // Configure GPC/PGC PUPSCR Register SW2ISO bits
  {
      IMX_GPC_PGC_PUPSCR_REG pupscrReg; pupscrReg.AsUint32 =
        MmioRead32 ((UINTN) &gpuPgcRegisters->PUPSCR);

    pupscrReg.SW = IMX_GPC_PGC_PUPSCR_SW_DEFAULT;
    pupscrReg.SW2ISO = IMX_GPC_PGC_PUPSCR_SW2ISO_DEFAULT;

    MmioWrite32 ((UINTN) &gpuPgcRegisters->PUPSCR, pupscrReg.AsUint32);
  }

  // Turn on LDO_PU to 1.250V
  {
    IMX_PMU_REG_CORE_REG pmuCoreReg = {0};
    pmuCoreReg.REG1_TARG = 0x1f;

    MmioWrite32 ((UINTN) &analogRegisters->PMU_REG_CORE_CLR, pmuCoreReg.AsUint32);

    pmuCoreReg.REG1_TARG = 22;
    MmioWrite32 ((UINTN) &analogRegisters->PMU_REG_CORE_SET, pmuCoreReg.AsUint32);

    MicroSecondDelay (100);
  }

  // Assert power up request
  IMX_GPC_CNTR_REG gpcCntrReg; gpcCntrReg.AsUint32 =
      MmioRead32 ((UINTN) &gpcRegisters->CNTR);

  gpcCntrReg.gpu_vpu_pdn_req = 0;
  gpcCntrReg.gpu_vpu_pup_req = 1;

  MmioWrite32 ((UINTN) &gpcRegisters->CNTR, gpcCntrReg.AsUint32);

  // Wait for power up request to complete
  do {
    gpcCntrReg.AsUint32 = MmioRead32 ((UINTN) &gpcRegisters->CNTR);
  } while (gpcCntrReg.gpu_vpu_pup_req != 0);
}

VOID ImxDisableGpuVpuPowerDomain ()
{
  volatile IMX_GPC_REGISTERS *gpcRegisters = (IMX_GPC_REGISTERS *) IMX_GPC_BASE;
  volatile IMX_GPC_PGC_REGISTERS *gpuPgcRegisters = &gpcRegisters->PGC_GPU;

  // Configure GPC/PGC PDNSCR Register ISO bits
  {
      IMX_GPC_PGC_PDNSCR_REG pdnscrReg; pdnscrReg.AsUint32 =
        MmioRead32 ((UINTN) &gpuPgcRegisters->PDNSCR);

    pdnscrReg.ISO = IMX_GPC_PGC_PDNSCR_ISO_DEFAULT;
    pdnscrReg.ISO2SW = IMX_GPC_PGC_PDNSCR_ISO2SW_DEFAULT;

    MmioWrite32 ((UINTN) &gpuPgcRegisters->PDNSCR, pdnscrReg.AsUint32);
  }

  // Configure GPC/PGC CTRL[PCR] bit to allow power down of the blocks
  {
      IMX_GPC_PGC_PGCR_REG ctrlReg; ctrlReg.AsUint32 =
        MmioRead32 ((UINTN) &gpuPgcRegisters->CTRL);

    ctrlReg.PCR = 1;    // enable powering down of the blocks

    MmioWrite32 ((UINTN) &gpuPgcRegisters->CTRL, ctrlReg.AsUint32);
  }

  // Assert power down request
  {
      IMX_GPC_CNTR_REG gpcCntrReg; gpcCntrReg.AsUint32 =
        MmioRead32 ((UINTN) &gpcRegisters->CNTR);

    gpcCntrReg.gpu_vpu_pdn_req = 1;
    gpcCntrReg.gpu_vpu_pup_req = 0;

    MmioWrite32 ((UINTN) &gpcRegisters->CNTR, gpcCntrReg.AsUint32);

    // Wait for power down request to complete
    do {
      gpcCntrReg.AsUint32 = MmioRead32 ((UINTN) &gpcRegisters->CNTR);
    } while (gpcCntrReg.gpu_vpu_pdn_req != 0);
  }
}

EFI_STATUS
ImxpGetClockInfo (
  IN OUT IMX_CLOCK_TREE_CACHE *Cache,
  IN IMX_CLK ClockId,
  OUT IMX_CLOCK_INFO *ClockInfo
  )
{
  ASSERT (ClockId < ARRAYSIZE(Cache->Table));

  // First try to satisfy from cache
  {
    UINTN cacheValidBits = Cache->Valid[ClockId / _BITS_PER_UINTN];
    if (cacheValidBits & (1 << (ClockId % _BITS_PER_UINTN))) {
      *ClockInfo = Cache->Table[ClockId];
      return EFI_SUCCESS;
    }
  }

  EFI_STATUS status;
  switch (ClockId) {
  case IMX_OSC_CLK:
    ImxpGetOsc24ClkInfo (ClockInfo);
    status = EFI_SUCCESS;
    break;
  case IMX_PLL1_MAIN_CLK:
    status = ImxpGetPll1MainClkInfo (Cache, ClockInfo);
    break;
  case IMX_PLL2_MAIN_CLK:
    status = ImxpGetPll2MainClkInfo (Cache, ClockInfo);
    break;
  case IMX_PLL2_PFD0:
    status = ImxpGetPll2PfdClkInfo (Cache, IMX_PLL_PFD0, ClockInfo);
    break;
  case IMX_PLL2_PFD1:
    status = ImxpGetPll2PfdClkInfo (Cache, IMX_PLL_PFD1, ClockInfo);
    break;
  case IMX_PLL2_PFD2:
    status = ImxpGetPll2PfdClkInfo (Cache, IMX_PLL_PFD2, ClockInfo);
    break;
  case IMX_PLL3_MAIN_CLK:
    status = ImxpGetPll3MainClkInfo (Cache, ClockInfo);
    break;
  case IMX_PLL3_PFD0:
    status = ImxpGetPll3PfdClkInfo (Cache, IMX_PLL_PFD0, ClockInfo);
    break;
  case IMX_PLL3_PFD1:
    status = ImxpGetPll3PfdClkInfo (Cache, IMX_PLL_PFD1, ClockInfo);
    break;
  case IMX_PLL3_PFD2:
    status = ImxpGetPll3PfdClkInfo (Cache, IMX_PLL_PFD2, ClockInfo);
    break;
  case IMX_PLL3_PFD3:
    status = ImxpGetPll3PfdClkInfo (Cache, IMX_PLL_PFD3, ClockInfo);
    break;
  case IMX_PLL3_SW_CLK:
    status = ImxpGetPll3SwClkInfo (Cache, ClockInfo);
    break;
  case IMX_AXI_CLK_ROOT:
    status = ImxpGetAxiClkRootInfo (Cache, ClockInfo);
    break;
  case IMX_PERIPH_CLK2:
    status = ImxpGetPeriphClk2Info (Cache, ClockInfo);
    break;
  case IMX_PERIPH_CLK:
    status = ImxpGetPeriphClkInfo (Cache, ClockInfo);
    break;
  case IMX_PRE_PERIPH_CLK:
    status = ImxpGetPrePeriphClkInfo (Cache, ClockInfo);
    break;
  case IMX_ARM_CLK_ROOT:
    status = ImxpGetArmClkRootInfo (Cache, ClockInfo);
    break;
  case IMX_MMDC_CH0_CLK_ROOT:
    status = ImxpGetMmdcCh0ClkRootInfo (Cache, ClockInfo);
    break;
  case IMX_AHB_CLK_ROOT:
    status = ImxpGetAhbClkRootInfo (Cache, ClockInfo);
    break;
  case IMX_IPG_CLK_ROOT:
    status = ImxpGetIpgClkRootInfo (Cache, ClockInfo);
    break;
  case IMX_GPU2D_AXI_CLK_ROOT:
    status = ImxpGetGpu2dAxiClkRootInfo (Cache, ClockInfo);
    break;
  case IMX_GPU3D_AXI_CLK_ROOT:
    status = ImxpGetGpu3dAxiClkRootInfo (Cache, ClockInfo);
    break;
  case IMX_GPU2D_CORE_CLK_ROOT:
    status = ImxpGetGpu2dCoreClkInfo (Cache, ClockInfo);
    break;
  case IMX_GPU3D_CORE_CLK_ROOT:
    status = ImxpGetGpu3dCoreClkInfo (Cache, ClockInfo);
    break;
  case IMX_GPU3D_SHADER_CLK_ROOT:
    status = ImxpGetGpu3dShaderClkInfo (Cache, ClockInfo);
    break;
  default:
    return EFI_UNSUPPORTED;
  }

  if (EFI_ERROR (status)) {
    return status;
  }

  // Update the cache
  Cache->Table[ClockId] = *ClockInfo;
  Cache->Valid[ClockId / _BITS_PER_UINTN] |= (1 << (ClockId % _BITS_PER_UINTN));

  return EFI_SUCCESS;
}

/**
  Power on and clock the GPU2D/GPU3D blocks.

  Follow the datasheet recommended sequence for clocking and powering:
    Gate clocks -> unpower module ->
    configure muxes/dividers -> power module -> Ungate clocks
**/
EFI_STATUS ImxClkPwrGpuEnable ()
{
    //EFI_STATUS status;

#if !defined(MDEPKG_NDEBUG)

  //
  // Precondition: clock and power should be disabled
  //
  {
    ASSERT (ImxClkPwrGetClockGate (IMX_GPU3D_CLK_ENABLE) == IMX_CLOCK_GATE_STATE_OFF);
    ASSERT (ImxClkPwrGetClockGate (IMX_GPU2D_CLK_ENABLE) == IMX_CLOCK_GATE_STATE_OFF);
    ASSERT (ImxClkPwrGetClockGate (IMX_OPENVGAXICLK_CLK_ROOT_ENABLE) == IMX_CLOCK_GATE_STATE_OFF);
  }

#endif

  // Ensure clocks are gated
  ImxClkPwrSetClockGate (IMX_GPU3D_CLK_ENABLE, IMX_CLOCK_GATE_STATE_OFF);
  ImxClkPwrSetClockGate (IMX_GPU2D_CLK_ENABLE, IMX_CLOCK_GATE_STATE_OFF);
  ImxClkPwrSetClockGate (IMX_OPENVGAXICLK_CLK_ROOT_ENABLE, IMX_CLOCK_GATE_STATE_OFF);

  // Ensure GPU powered down (GPU should be powered down anyway)
  ImxDisableGpuVpuPowerDomain ();

  // Configure clock muxes and dividers for GPU3D, GPU2D, and OpenVG
  ImxCcmConfigureGpuClockTree ();

  // Power on the GPU
  ImxEnableGpuVpuPowerDomain ();

  // Ungate the GPU clocks
  ImxClkPwrSetClockGate (IMX_GPU3D_CLK_ENABLE, IMX_CLOCK_GATE_STATE_ON);
  ImxClkPwrSetClockGate (IMX_GPU2D_CLK_ENABLE, IMX_CLOCK_GATE_STATE_ON);
  ImxClkPwrSetClockGate (IMX_OPENVGAXICLK_CLK_ROOT_ENABLE, IMX_CLOCK_GATE_STATE_ON);

  return EFI_SUCCESS;
}


/**
    Setup the clock tree for Display Interface (DI) for DuaLite and Solo
        Gate clocks -> Configure mux/div -> Ungate clocks -> Setup PLL
**/
EFI_STATUS ImxClkPwrIpuDIxEnable ()
{
    ImxClkPwrSetClockGate(IMX_IPU1_DI0_CLK_ENABLE, IMX_CCM_CCGR_OFF);
    ImxClkPwrSetClockGate(IMX_IPU1_DI1_CLK_ENABLE, IMX_CCM_CCGR_OFF);

    ImxCcmConfigureIPUDIxClockTree();

    ImxClkPwrSetClockGate(IMX_IPU1_DI0_CLK_ENABLE, IMX_CCM_CCGR_ON);

    // Setup PLL to 65MHz as expected from UBOOT although transition
    // might be so fast that UBOOT screen would not be displayed
    ImxSetPll5ReferenceRate(65000000);

    return EFI_SUCCESS;
}

/**
    Configure PLL5 to the desired clock rate for all Display Interface (DI).
    Currently only support one display to IPU1 DI0.
**/
EFI_STATUS ImxSetPll5ReferenceRate (
    UINT32 ClockRate
    )
{
    BOOLEAN foundConfig = FALSE;
    UINT32 dxPodfDivider;
    UINT32 targetFreq;
    UINT32 postDivSelectCount;
    UINT32 postDivSelectValue[3] = { 1, 2, 4 };
    IMX_CCM_PLL_VIDEO_CTRL_POST_DIV_SELECT postDivSelect[3] = {
        IMX_POST_DIV_SELECT_DIVIDE_1,
        IMX_POST_DIV_SELECT_DIVIDE_2,
        IMX_POST_DIV_SELECT_DIVIDE_4 };

    for (postDivSelectCount = 0;
        postDivSelectCount < ARRAYSIZE (postDivSelectValue);
        ++postDivSelectCount) {

        for (dxPodfDivider = 1; dxPodfDivider < 9; ++dxPodfDivider) {

            targetFreq =
                dxPodfDivider *
                ClockRate *
                postDivSelectValue[postDivSelectCount];

            // The valid range for PPL loop divider is 27-54 so we
            // need to target freq need to fit within the valid range.
            if ((targetFreq >= PLL5_MIN_FREQ) &&
                (targetFreq <= PLL5_MAX_FREQ)) {
                foundConfig = TRUE;
                break;
            }
        }

        if (foundConfig == TRUE) {
            break;
        }
    }

    if (foundConfig == FALSE) {
        DEBUG((DEBUG_ERROR, "ClockRate %d\n", ClockRate));
        ASSERT(FALSE);
        return EFI_INVALID_PARAMETER;
    }

    DEBUG ((
        DEBUG_INFO,
        "PLL 5 setting (%d) Target Freq %d Divider %d PostDiv %d\n",
        ClockRate,
        targetFreq,
        dxPodfDivider,
        postDivSelectValue[postDivSelectCount]
        ));

    {
        volatile IMX_CCM_REGISTERS *ccmRegisters =
            (IMX_CCM_REGISTERS *)IMX_CCM_BASE;
        IMX_CCM_CHSCCDR_REG chscddrReg; chscddrReg.AsUint32 =
             MmioRead32 ((UINTN)&ccmRegisters->CHSCCDR) ;

        ImxClkPwrSetClockGate(IMX_IPU1_DI0_CLK_ENABLE, IMX_CCM_CCGR_OFF);
        ImxClkPwrSetClockGate(IMX_IPU1_DI1_CLK_ENABLE, IMX_CCM_CCGR_OFF);

        chscddrReg.ipu1_di0_podf = dxPodfDivider - 1;
        chscddrReg.ipu1_di1_podf = dxPodfDivider - 1;

        MmioWrite32 ((UINTN)&ccmRegisters->CHSCCDR, chscddrReg.AsUint32);

        ImxClkPwrSetClockGate(IMX_IPU1_DI0_CLK_ENABLE, IMX_CCM_CCGR_ON);
    }

    ImxSetClockRatePLL5(targetFreq, postDivSelect[postDivSelectCount]);

    return EFI_SUCCESS;
}

EFI_STATUS ImxClkPwrClkOut1Enable (IMX_CLK Clock, UINT32 Divider)
{
  volatile IMX_CCM_REGISTERS *ccmRegisters = (IMX_CCM_REGISTERS *) IMX_CCM_BASE;

  if ((Divider < 1) || (Divider > 8)) {
    return EFI_INVALID_PARAMETER;
  }

  IMX_CCM_CCOSR_REG ccosrReg; ccosrReg.AsUint32 =
      MmioRead32 ((UINTN) &ccmRegisters->CCOSR);

  switch (Clock) {
  case IMX_OSC_CLK:
    ccosrReg.CLKO2_SEL = IMX_CCM_CLKO2_SEL_OSC_CLK;
    ccosrReg.CLKO2_DIV = Divider - 1;
    ccosrReg.CLKO2_EN = 1;
    ccosrReg.CLK_OUT_SEL = IMX_CCM_CLK_OUT_SEL_CCM_CLKO2;
    break;

  case IMX_PLL2_MAIN_CLK:
    ccosrReg.CLKO1_SEL = IMX_CCM_CLKO1_SEL_PLL2_MAIN_CLK_2;
    ccosrReg.CLKO1_DIV = Divider - 1;
    ccosrReg.CLKO1_EN = 1;
    ccosrReg.CLK_OUT_SEL = IMX_CCM_CLK_OUT_SEL_CCM_CLKO1;
    break;

  case IMX_AXI_CLK_ROOT:
    ccosrReg.CLKO1_SEL = IMX_CCM_CLKO1_SEL_AXI_CLK_ROOT;
    ccosrReg.CLKO1_DIV = Divider - 1;
    ccosrReg.CLKO1_EN = 1;
    ccosrReg.CLK_OUT_SEL = IMX_CCM_CLK_OUT_SEL_CCM_CLKO1;
    break;

  case IMX_IPG_CLK_ROOT:
    ccosrReg.CLKO1_SEL = IMX_CCM_CLKO1_SEL_IPG_CLK_ROOT;
    ccosrReg.CLKO1_DIV = Divider - 1;
    ccosrReg.CLKO1_EN = 1;
    ccosrReg.CLK_OUT_SEL = IMX_CCM_CLK_OUT_SEL_CCM_CLKO1;
    break;

  case IMX_GPU2D_AXI_CLK_ROOT:
    ccosrReg.CLKO2_SEL = IMX_CCM_CLKO2_SEL_GPU2D_AXI_CLK_ROOT;
    ccosrReg.CLKO2_DIV = Divider - 1;
    ccosrReg.CLKO2_EN = 1;
    ccosrReg.CLK_OUT_SEL = IMX_CCM_CLK_OUT_SEL_CCM_CLKO2;
    break;

  case IMX_GPU3D_AXI_CLK_ROOT:
    ccosrReg.CLKO2_SEL = IMX_CCM_CLKO2_SEL_GPU3D_AXI_CLK_ROOT;
    ccosrReg.CLKO2_DIV = Divider - 1;
    ccosrReg.CLKO2_EN = 1;
    ccosrReg.CLK_OUT_SEL = IMX_CCM_CLK_OUT_SEL_CCM_CLKO2;
    break;

  case IMX_GPU2D_CORE_CLK_ROOT:
    ccosrReg.CLKO2_SEL = IMX_CCM_CLKO2_SEL_GPU2D_CORE_CLK_ROOT;
    ccosrReg.CLKO2_DIV = Divider - 1;
    ccosrReg.CLKO2_EN = 1;
    ccosrReg.CLK_OUT_SEL = IMX_CCM_CLK_OUT_SEL_CCM_CLKO2;
    break;

  case IMX_GPU3D_CORE_CLK_ROOT:
    ccosrReg.CLKO2_SEL = IMX_CCM_CLKO2_SEL_GPU3D_CORE_CLK_ROOT;
    ccosrReg.CLKO2_DIV = Divider - 1;
    ccosrReg.CLKO2_EN = 1;
    ccosrReg.CLK_OUT_SEL = IMX_CCM_CLK_OUT_SEL_CCM_CLKO2;
    break;

  case IMX_GPU3D_SHADER_CLK_ROOT:
    ccosrReg.CLKO2_SEL = IMX_CCM_CLKO2_SEL_GPU3D_SHADER_CLK_ROOT;
    ccosrReg.CLKO2_DIV = Divider - 1;
    ccosrReg.CLKO2_EN = 1;
    ccosrReg.CLK_OUT_SEL = IMX_CCM_CLK_OUT_SEL_CCM_CLKO2;
    break;

  case IMX_UART_CLK_ROOT:
    ccosrReg.CLKO2_SEL = IMX_CCM_CLKO2_SEL_UART_CLK_ROOT;
    ccosrReg.CLKO2_DIV = Divider - 1;
    ccosrReg.CLKO2_EN = 1;
    ccosrReg.CLK_OUT_SEL = IMX_CCM_CLK_OUT_SEL_CCM_CLKO2;
    break;

  default:
    return EFI_UNSUPPORTED;
  }

  MmioWrite32 ((UINTN) &ccmRegisters->CCOSR, ccosrReg.AsUint32);

  return EFI_SUCCESS;
}

VOID ImxClkPwrClkOut1Disable ()
{
  volatile IMX_CCM_REGISTERS *ccmRegisters = (IMX_CCM_REGISTERS *) IMX_CCM_BASE;

  IMX_CCM_CCOSR_REG ccosrReg; ccosrReg.AsUint32 =
      MmioRead32 ((UINTN) &ccmRegisters->CCOSR);

  ccosrReg.CLKO1_EN = 0;
  ccosrReg.CLKO2_EN = 0;

  MmioWrite32 ((UINTN) &ccmRegisters->CCOSR, ccosrReg.AsUint32);
}

EFI_STATUS ImxClkPwrValidateClocks ()
{
  struct {
    IMX_CLK Clock;
    IMX_CLOCK_INFO Info;
  } expectedClocks[] = {
    // Clock, Frequency, Parent
    {IMX_OSC_CLK, {24000000, IMX_CLK_NONE}},
    {IMX_PLL1_MAIN_CLK, {792000000, IMX_OSC_CLK}},
    {IMX_PLL2_MAIN_CLK, {528000000, IMX_OSC_CLK}},
    {IMX_PLL2_PFD0, {306580645, IMX_PLL2_MAIN_CLK}},
    {IMX_PLL2_PFD1,{528000000, IMX_PLL2_MAIN_CLK}},
    {IMX_PLL2_PFD2, {396000000, IMX_PLL2_MAIN_CLK}},
    {IMX_PLL3_MAIN_CLK, {480000000, IMX_OSC_CLK}},
    {IMX_PLL3_PFD0, {720000000, IMX_PLL3_MAIN_CLK}},
    {IMX_PLL3_PFD1, {540000000, IMX_PLL3_MAIN_CLK}},
    {IMX_PLL3_PFD2, {508235294, IMX_PLL3_MAIN_CLK}},
    {IMX_PLL3_PFD3, {454736842, IMX_PLL3_MAIN_CLK}},
    {IMX_AXI_CLK_ROOT, {198000000, IMX_PERIPH_CLK}},
    {IMX_MMDC_CH0_CLK_ROOT, {396000000, IMX_PERIPH_CLK}},
  };

  BOOLEAN invalid = FALSE;

  int i;
  for (i = 0; i < ARRAYSIZE (expectedClocks); ++i) {
    DEBUG ((
      DEBUG_INFO,
      "Validating clock %s. Expecting: Frequency = %d (%d Mhz), Parent = %s\r\n",
      StringFromImxClk (expectedClocks[i].Clock),
      expectedClocks[i].Info.Frequency,
      expectedClocks[i].Info.Frequency / 1000000,
      StringFromImxClk (expectedClocks[i].Info.Parent)
      ));

    IMX_CLOCK_INFO actualInfo;
    EFI_STATUS status = ImxClkPwrGetClockInfo (
        expectedClocks[i].Clock,
        &actualInfo);

    if (EFI_ERROR (status)) {
      DEBUG ((
        DEBUG_ERROR,
        "Failed to get clock info. (Clock = %s, status = 0x%x)\r\n",
        StringFromImxClk (expectedClocks[i].Clock),
        status
        ));

      return status;
    }

    if ((actualInfo.Frequency != expectedClocks[i].Info.Frequency) ||
        (actualInfo.Parent != expectedClocks[i].Info.Parent)) {

        DEBUG ((
          DEBUG_ERROR,
          "SDL Clock settings do not match expected! Clock = %s (Expected, Actual) "
          "Frequency: %d, %d. Parent: %s, %s\r\n",
          StringFromImxClk (expectedClocks[i].Clock),
          expectedClocks[i].Info.Frequency,
          actualInfo.Frequency,
          StringFromImxClk (expectedClocks[i].Info.Parent),
          StringFromImxClk (actualInfo.Parent)
          ));

        invalid = TRUE;
    }
  }

  return invalid ? EFI_DEVICE_ERROR : EFI_SUCCESS;
}
