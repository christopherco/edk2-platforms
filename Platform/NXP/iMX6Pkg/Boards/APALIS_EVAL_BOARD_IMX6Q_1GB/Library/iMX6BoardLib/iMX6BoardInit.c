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

#include <Library/IoLib.h>
#include <Library/ArmPlatformLib.h>
#include <Library/DebugLib.h>
#include <Library/PrintLib.h>
#include <Library/PcdLib.h>
#include <Library/SerialPortLib.h>
#include <Library/TimerLib.h>

#include <iMX6.h>
#include <iMX6ClkPwr.h>
#include <iMX6IoMux.h>

typedef enum {
    IMX_USDHC_GPIO_INPUT_PAD_CTL = _IMX_MAKE_PAD_CTL(
                              IMX_SRE_FAST,
                              IMX_DSE_50_OHM,
                              IMX_SPEED_LOW,
                              IMX_ODE_DISABLE,
                              IMX_PKE_DISABLE,
                              IMX_PUE_PULL,
                              IMX_PUS_22K_OHM_PU,
                              IMX_HYS_ENABLED),

    IMX_PAD_CFG_NANDF_CS1_GPIO6_IO14 = _IMX_MAKE_PADCFG2(
                              IMX_USDHC_GPIO_INPUT_PAD_CTL,
                              IMX_SION_DISABLED,
                              IMX_IOMUXC_NANDF_CS1_ALT5_GPIO6_IO14),
} IMX_USDHC_PADCFG;

typedef enum {
    IMX_PAD_CFG_EIM_DATA19_GPIO3_IO19 = _IMX_MAKE_PADCFG(
                              IMX_SRE_SLOW,
                              IMX_DSE_40_OHM,
                              IMX_SPEED_MEDIUM,
                              IMX_ODE_DISABLE,
                              IMX_PKE_ENABLE,
                              IMX_PUE_PULL,
                              IMX_PUS_100K_OHM_PU,
                              IMX_HYS_ENABLED,
                              IMX_SION_DISABLED,
                              IMX_IOMUXC_EIM_D19_ALT5_GPIO3_IO19),

    IMX_PAD_CFG_GPIO17_GPIO7_IO12 = _IMX_MAKE_PADCFG(
                              IMX_SRE_SLOW,
                              IMX_DSE_40_OHM,
                              IMX_SPEED_MEDIUM,
                              IMX_ODE_DISABLE,
                              IMX_PKE_ENABLE,
                              IMX_PUE_PULL,
                              IMX_PUS_100K_OHM_PU,
                              IMX_HYS_ENABLED,
                              IMX_SION_DISABLED,
                              IMX_IOMUXC_GPIO_17_ALT5_GPIO7_IO12),
} IMX_PCIE_PADCFG;


/**
  Turn on required clocks, that are not handled by the PEP. 
**/
static VOID UngateRequiredClocks ()
{
    static const IMX_CLK_GATE gatesToTurnOn[] = {
        IMX_SDMA_CLK_ENABLE,
        IMX_SPBA_CLK_ENABLE,
    };

    ImxClkPwrSetClockGates(
        gatesToTurnOn,
        sizeof(gatesToTurnOn) / sizeof(gatesToTurnOn[0]),
        IMX_CLOCK_GATE_STATE_ON);
}

/**
  Initialize clock and power for modules on the SOC
**/
VOID ImxClkPwrInit ()
{
  EFI_STATUS status;

  if (FeaturePcdGet (PcdGpuEnable)) {
    status = ImxClkPwrGpuEnable ();
    ASSERT_EFI_ERROR (status);
  }

  status = ImxClkPwrIpuDIxEnable();
  ASSERT_EFI_ERROR (status);

  //
  // Ensure GPT_SERIAL_CLK is ungated
  //
  ImxClkPwrSetClockGate(IMX_GPT_SERIAL_CLK_ENABLE, IMX_CLOCK_GATE_STATE_ON);

  ASSERT_EFI_ERROR (ImxClkPwrValidateClocks ());
}

/**
  Initialize SDHC modules on the SOC and perform required pin-muxing
**/
VOID SdhcInit ()
{
  //
  // CardDetect signal CD_B is routed to NANDF_CS1 pad GPIO6_IO14 signal
  //
  ImxPadConfig (IMX_PAD_NANDF_CS1, IMX_PAD_CFG_NANDF_CS1_GPIO6_IO14);
  ImxGpioDirection (IMX_GPIO_BANK2, 0, IMX_GPIO_DIR_INPUT);
}

/**
  Initialize I2C modules on the SOC and perform required pin-muxing
**/
VOID I2cInit ()
{
}

/**
  Initialize SPI modules on the SOC and perform required pin-muxing
**/
VOID SpiInit ()
{
    UINT32 RegValue;

    //
    // On Apalis only ESPI1,2 are exposed.
    // Configure the return path for ECSPI1_MISO, ECSPI2_MISO
    //

    RegValue = MmioRead32(IOMUXC_ECSPI1_MISO_SELECT_INPUT);
    RegValue &= ~3;
    RegValue |= (IMX_IOMUXC_ECSPI1_MISO_CSI0_DATA06_ALT2 << 0);
    MmioWrite32(IOMUXC_ECSPI1_MISO_SELECT_INPUT, RegValue);

    RegValue = MmioRead32(IOMUXC_ECSPI2_MISO_SELECT_INPUT);
    RegValue &= ~3;
    RegValue |= (IMX_IOMUXC_ECSPI2_MISO_EIM_OE_B_ALT2 << 0);
    MmioWrite32(IOMUXC_ECSPI2_MISO_SELECT_INPUT, RegValue);

    //
    // ECSPI3 is available on the Apalis but PADs are shared with SD/MMC.
    // Currently ECSPI3 is not exposed.
    // If needed  Configure the return path for ECSPI3_MISO.
    //
}

/**
  Initialize PCI Express module on the SOC and perform required pin-muxing
**/
VOID PcieInit ()
{
    //
    // PCIe GPIO Power
    //
    ImxPadConfig(IMX_PAD_EIM_D19, IMX_PAD_CFG_EIM_DATA19_GPIO3_IO19);
    ImxGpioDirection(IMX_GPIO_BANK3, 19, IMX_GPIO_DIR_OUTPUT);

    //
    // PCIe GPIO Reset
    //
    ImxPadConfig(IMX_PAD_GPIO_17, IMX_PAD_CFG_GPIO17_GPIO7_IO12);
    ImxGpioDirection(IMX_GPIO_BANK7, 12, IMX_GPIO_DIR_OUTPUT);
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

  ImxClkPwrInit();
  UngateRequiredClocks();

  SerialPortInitialize ();
  SerialPortWrite (
   (UINT8 *)SERIAL_PORT_INIT_MSG,
   (UINTN)sizeof(SERIAL_PORT_INIT_MSG));

  SdhcInit ();
  I2cInit ();
  SpiInit ();
  PcieInit ();

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

/**
    UART initialization for function that is called from SEC.
    Nothing to initialize as we are dependent on primary boot loader to setup
    UART.
**/
VOID UartInit ()
{

  return;
}