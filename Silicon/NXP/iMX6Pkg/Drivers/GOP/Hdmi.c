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

#include "Osal.h"

#include "Display.h"
#include "Hdmi.h"
#include "Edid.h"

PLL_MPLL_CONFIG PllMpllGenericConfigSetting[] = {
    { 13500000,2,8,{ { 3,0,3,3,0,0,0,0, } }, { { 4,3,4,4,0, } }, { { 0,0,0, } },  },
    { 13500000,2,10,{ { 1,4,3,3,0,0,1,0, } }, { { 4,3,4,4,0, } }, { { 0,0,0, } },  },
    { 13500000,2,12,{ { 2,4,3,3,0,0,2,0, } }, { { 4,3,3,3,0, } }, { { 0,0,0, } },  },
    { 13500000,2,16,{ { 3,1,3,2,0,0,3,0, } }, { { 4,3,4,4,0, } }, { { 1,0,0, } },  },
    { 13500000,4,8,{ { 3,1,3,2,0,0,0,0, } }, { { 4,3,4,4,0, } }, { { 1,0,0, } },  },
    { 13500000,4,10,{ { 1,5,3,2,0,0,1,0, } }, { { 4,3,4,4,0, } }, { { 1,0,0, } },  },
    { 13500000,4,12,{ { 2,5,3,2,0,0,2,0, } }, { { 4,3,3,3,0, } }, { { 1,0,0, } },  },
    { 13500000,4,16,{ { 3,2,3,1,0,0,3,0, } }, { { 4,3,4,4,0, } }, { { 2,0,0, } },  },
    { 18000000,3,8,{ { 2,1,3,2,0,0,0,0, } }, { { 4,3,4,4,0, } }, { { 1,0,0, } },  },
    { 18000000,3,16,{ { 2,2,3,1,0,0,3,0, } }, { { 4,3,4,4,0, } }, { { 2,0,0, } },  },
    { 24175000,1,8,{ { 0,0,3,3,0,0,0,0, } }, { { 4,3,4,4,0, } }, { { 0,0,0, } },  },
    { 24175000,1,10,{ { 1,0,3,3,0,0,1,0, } }, { { 4,3,4,4,0, } }, { { 0,0,0, } },  },
    { 24175000,1,12,{ { 2,0,3,3,0,0,2,0, } }, { { 4,3,3,3,0, } }, { { 0,0,0, } },  },
    { 24175000,1,16,{ { 3,0,2,2,0,0,3,0, } }, { { 4,3,4,4,0, } }, { { 1,1,0, } },  },
    { 27000000,1,8,{ { 0,0,3,3,0,0,0,0, } }, { { 4,3,4,4,0, } }, { { 0,0,0, } },  },
    { 27000000,1,10,{ { 1,0,3,3,0,0,1,0, } }, { { 4,3,4,4,0, } }, { { 0,0,0, } },  },
    { 27000000,1,12,{ { 2,0,3,3,0,0,2,0, } }, { { 4,3,3,3,0, } }, { { 0,0,0, } },  },
    { 27000000,1,16,{ { 3,0,2,2,0,0,3,0, } }, { { 4,3,5,4,0, } }, { { 1,0,0, } },  },
    { 27000000,2,8,{ { 3,0,2,2,0,0,0,0, } }, { { 4,3,4,4,0, } }, { { 1,1,0, } },  },
    { 27000000,2,10,{ { 1,1,3,2,0,0,1,0, } }, { { 4,3,4,4,0, } }, { { 1,0,0, } },  },
    { 27000000,2,12,{ { 2,1,3,2,0,0,2,0, } }, { { 4,3,3,3,0, } }, { { 1,0,0, } },  },
    { 27000000,2,16,{ { 3,1,2,1,0,0,3,0, } }, { { 4,3,4,4,0, } }, { { 2,1,0, } },  },
    { 27000000,4,8,{ { 3,1,2,1,0,0,0,0, } }, { { 4,3,4,4,0, } }, { { 2,1,0, } },  },
    { 27000000,4,10,{ { 1,2,3,1,0,0,1,0, } }, { { 4,3,4,4,0, } }, { { 2,0,0, } },  },
    { 27000000,4,12,{ { 2,2,3,1,0,0,2,0, } }, { { 4,3,3,3,0, } }, { { 2,0,0, } },  },
    { 27000000,4,16,{ { 3,2,2,0,0,0,3,0, } }, { { 4,3,4,4,0, } }, { { 3,1,0, } },  },
    { 36000000,1,8,{ { 0,0,3,3,0,0,0,0, } }, { { 4,3,4,4,0, } }, { { 0,0,0, } },  },
    { 36000000,1,16,{ { 3,0,2,2,0,0,3,0, } }, { { 4,3,4,4,0, } }, { { 1,1,0, } },  },
    { 50350000,1,8,{ { 0,0,2,2,0,0,0,0, } }, { { 4,3,4,4,0, } }, { { 1,1,0, } },  },
    { 50350000,1,10,{ { 1,0,2,2,0,0,1,0, } }, { { 4,3,4,4,0, } }, { { 1,1,0, } },  },
    { 50350000,1,12,{ { 2,0,2,2,0,0,2,0, } }, { { 4,3,3,3,0, } }, { { 1,1,0, } },  },
    { 50350000,1,16,{ { 3,0,1,1,0,0,3,0, } }, { { 4,3,4,4,0, } }, { { 2,2,0, } },  },
    { 50350000,2,8,{ { 3,0,1,1,0,0,0,0, } }, { { 4,3,4,4,0, } }, { { 2,2,0, } },  },
    { 50350000,2,10,{ { 1,1,2,1,0,0,1,0, } }, { { 4,3,4,4,0, } }, { { 2,1,0, } },  },
    { 50350000,2,12,{ { 2,1,2,1,0,0,2,0, } }, { { 4,3,3,3,0, } }, { { 2,1,0, } },  },
    { 50350000,2,16,{ { 3,1,1,0,0,0,3,0, } }, { { 4,3,4,4,0, } }, { { 3,2,0, } },  },
    { 54000000,1,8,{ { 0,0,2,2,0,0,0,0, } }, { { 4,3,4,4,0, } }, { { 1,1,0, } },  },
    { 54000000,1,10,{ { 1,0,2,2,0,0,1,0, } }, { { 4,3,4,4,0, } }, { { 1,1,0, } },  },
    { 54000000,1,12,{ { 2,0,2,2,0,0,2,0, } }, { { 4,3,3,3,0, } }, { { 1,1,0, } },  },
    { 54000000,1,16,{ { 3,0,1,1,0,0,3,0, } }, { { 4,3,4,4,0, } }, { { 2,2,0, } },  },
    { 54000000,2,8,{ { 3,0,1,1,0,0,0,0, } }, { { 4,3,4,4,0, } }, { { 2,2,0, } },  },
    { 54000000,2,10,{ { 1,1,2,1,0,0,1,0, } }, { { 4,3,4,4,0, } }, { { 2,1,0, } },  },
    { 54000000,2,12,{ { 2,1,2,1,0,0,2,0, } }, { { 4,3,3,3,0, } }, { { 2,1,0, } },  },
    { 54000000,2,16,{ { 3,1,1,0,0,0,3,0, } }, { { 4,3,4,4,0, } }, { { 3,2,0, } },  },
    { 58400000,1,8,{ { 0,0,2,2,0,0,0,0, } }, { { 4,3,4,4,0, } }, { { 1,1,0, } },  },
    { 58400000,1,10,{ { 1,0,2,2,0,0,1,0, } }, { { 4,3,3,3,0, } }, { { 1,1,0, } },  },
    { 58400000,1,12,{ { 2,0,2,2,0,0,2,0, } }, { { 4,3,3,3,0, } }, { { 1,1,0, } },  },
    { 58400000,1,16,{ { 3,0,1,1,0,0,3,0, } }, { { 4,3,4,4,0, } }, { { 2,2,0, } },  },
    { 72000000,1,8,{ { 0,0,2,2,0,0,0,0, } }, { { 4,3,3,3,0, } }, { { 1,1,0, } },  },
    { 72000000,1,10,{ { 1,0,2,2,0,0,1,0, } }, { { 4,3,3,3,0, } }, { { 1,1,0, } },  },
    { 72000000,1,12,{ { 2,0,1,1,0,0,2,0, } }, { { 4,3,4,4,0, } }, { { 2,2,0, } },  },
    { 72000000,1,16,{ { 3,0,1,1,0,0,3,0, } }, { { 4,3,3,3,0, } }, { { 2,2,0, } },  },
    { 74250000,1,8,{ { 0,0,2,2,0,0,0,0, } }, { { 4,3,3,3,0, } }, { { 1,1,0, } },  },
    { 74250000,1,10,{ { 1,0,1,1,0,0,1,0, } }, { { 4,3,5,5,0, } }, { { 2,2,0, } },  },
    { 74250000,1,12,{ { 2,0,1,1,0,0,2,0, } }, { { 4,3,4,4,0, } }, { { 2,2,0, } },  },
    { 74250000,1,16,{ { 3,0,1,1,0,0,3,0, } }, { { 4,3,3,3,0, } }, { { 2,2,0, } },  },
    { 108000000,1,8,{ { 0,0,1,1,0,0,0,0, } }, { { 4,3,4,4,0, } }, { { 2,2,0, } },  },
    { 108000000,1,10,{ { 1,0,1,1,0,0,1,0, } }, { { 4,3,4,4,0, } }, { { 2,2,0, } },  },
    { 108000000,1,12,{ { 2,0,1,1,0,0,2,0, } }, { { 4,3,3,3,0, } }, { { 2,2,0, } },  },
    { 108000000,1,16,{ { 3,0,0,0,0,0,3,0, } }, { { 4,3,4,4,0, } }, { { 3,3,0, } },  },
    { 118800000,1,8,{ { 0,0,1,1,0,0,0,0, } }, { { 4,3,4,4,0, } }, { { 2,2,0, } },  },
    { 118800000,1,10,{ { 1,0,1,1,0,0,1,0, } }, { { 4,3,4,4,0, } }, { { 2,2,0, } },  },
    { 118800000,1,12,{ { 2,0,1,1,0,0,2,0, } }, { { 4,3,3,3,0, } }, { { 2,2,0, } },  },
    { 118800000,1,16,{ { 3,0,0,0,0,0,3,0, } }, { { 4,3,4,4,0, } }, { { 3,3,0, } },  },
    { 144000000,1,8,{ { 0,0,1,1,0,0,0,0, } }, { { 4,3,3,3,0, } }, { { 2,2,0, } },  },
    { 144000000,1,10,{ { 1,0,0,0,0,0,1,0, } }, { { 4,3,5,5,0, } }, { { 3,3,0, } },  },
    { 144000000,1,12,{ { 2,0,0,0,0,0,2,0, } }, { { 4,3,4,4,0, } }, { { 3,3,0, } },  },
    { 144000000,1,16,{ { 3,0,0,0,0,0,3,0, } }, { { 4,3,3,3,0, } }, { { 3,3,0, } },  },
    { 148500000,1,8,{ { 0,0,1,1,0,0,0,0, } }, { { 4,3,3,3,0, } }, { { 2,2,0, } },  },
    { 148500000,1,10,{ { 1,0,0,0,0,0,1,0, } }, { { 4,3,5,5,0, } }, { { 3,3,0, } },  },
    { 148500000,1,12,{ { 2,0,0,0,0,0,2,0, } }, { { 4,3,4,4,0, } }, { { 3,3,0, } },  },
    { 148500000,1,16,{ { 3,0,0,0,0,0,3,0, } }, { { 4,3,3,3,0, } }, { { 3,3,0, } },  },
    { 216000000,1,8,{ { 0,0,1,1,0,0,0,0, } }, { { 4,3,3,3,0, } }, { { 2,2,0, } },  },
    { 216000000,1,10,{ { 1,0,0,0,0,0,1,0, } }, { { 4,3,5,5,0, } }, { { 3,3,0, } },  },
    { 216000000,1,12,{ { 2,0,0,0,0,0,2,0, } }, { { 4,3,4,4,0, } }, { { 3,3,0, } },  },
    // Fallback
    { 65000000,1,8,{ { 0,0,1,1,0,0,0,0, } },{ { 4,3,3,3,0, } },{ { 2,2,0, } }, },
};

BOOLEAN HDMIPhyPollI2CDone (
    DISPLAY_INTERFACE_CONTEXT* HdmiDisplayContextPtr,
    UINT32 TimeOut
    )
{
    BOOLEAN waitResult = FALSE;
    HDMI_IH_I2CMPHY_STAT0_REG I2cMPhyStat0Reg;

    do {
        I2cMPhyStat0Reg.Reg = HDMIRead8(HDMI_IH_I2CMPHY_STAT0);
        if (I2cMPhyStat0Reg.i2cmphydone)
        {
            waitResult = TRUE;
            break;
        }

        if (--TimeOut == 0)
        {
            break;
        }

        OS_SLEEP(1);
    } while (I2cMPhyStat0Reg.i2cmphydone == 0);

#if DBG
    if ((TimeOut == 0) || (I2cMPhyStat0Reg.i2cmphyerror == 1)) {
        OS_ERROR(
            "HDMI I2C failed value %x time out %d\n",
            I2cMPhyStat0Reg.Reg,
            TimeOut));
    }
#endif

    return waitResult;
}

BOOLEAN HDMIPhyI2cRead (
    DISPLAY_INTERFACE_CONTEXT* HdmiDisplayContextPtr,
    UINT8 Addr,
    UINT16* DataPtr
    )
{
    BOOLEAN readStatus;
    UINT16 data0, data1;
    HDMI_IH_I2CMPHY_STAT0_REG I2cmPhyStat0Reg = { { 1, 1, 0 } };

    HDMIWrite8(HDMI_IH_I2CMPHY_STAT0, I2cmPhyStat0Reg.Reg);
    HDMIWrite8(HDMI_PHY_I2CM_ADDRESS_ADDR, Addr);

    {
        HDMI_PHY_I2CM_OPERATION_ADDR_REG I2cmOperationReg;

        I2cmOperationReg.Reg = HDMIRead8(HDMI_PHY_I2CM_OPERATION_ADDR);
        I2cmOperationReg.read = 1;
        HDMIWrite8(HDMI_PHY_I2CM_OPERATION_ADDR, I2cmOperationReg.Reg);
    }

    readStatus = HDMIPhyPollI2CDone(HdmiDisplayContextPtr, 1000);
    if (!readStatus) {
        OS_ERROR("Fail to read I2c HDMI Phy\n");
        goto Exit;
    }

    data0 = HDMIRead8(HDMI_PHY_I2CM_DATAI_0_ADDR);
    data1 = HDMIRead8(HDMI_PHY_I2CM_DATAI_1_ADDR);

    *DataPtr = data0 | (data1 << 8);

Exit:
    return readStatus;
}

BOOLEAN HDMIPhyI2cWrite (
    DISPLAY_INTERFACE_CONTEXT* HdmiDisplayContextPtr,
    UINT8 Addr,
    UINT16 Data
    )
{
    UINT8 data1 = (Data >> 8);
    UINT8 data0 = (Data & 0x00FF);
    HDMI_IH_I2CMPHY_STAT0_REG I2cmPhyStat0Reg = { { 1, 1, 0 } };

    HDMIWrite8(HDMI_IH_I2CMPHY_STAT0, I2cmPhyStat0Reg.Reg);
    HDMIWrite8(HDMI_PHY_I2CM_ADDRESS_ADDR, Addr);
    HDMIWrite8(HDMI_PHY_I2CM_DATAO_0_ADDR, data0);
    HDMIWrite8(HDMI_PHY_I2CM_DATAO_1_ADDR, data1);

    {
        HDMI_PHY_I2CM_OPERATION_ADDR_REG I2cmOperationReg = { { 0, 0, 0, 0 } };

        I2cmOperationReg.write = 1;
        HDMIWrite8(HDMI_PHY_I2CM_OPERATION_ADDR, I2cmOperationReg.Reg);
    }

    return HDMIPhyPollI2CDone(HdmiDisplayContextPtr, 1000);
}

BOOLEAN GetGenericConfigSetting (
    DISPLAY_TIMING* DisplayTimingPtr,
    PLL_MPLL_CONFIG** ConfigGenericSettingPPtr
    )
{
    BOOLEAN foundConfig = FALSE;
    UINT32 settingIndex;

    for (settingIndex = 0;
         settingIndex < ARRAYSIZE(PllMpllGenericConfigSetting);
        ++settingIndex) {

        if ((DisplayTimingPtr->PixelClock ==
                PllMpllGenericConfigSetting[settingIndex].PixelClock) &&
            (DisplayTimingPtr->PixelRepetition ==
                PllMpllGenericConfigSetting[settingIndex].PixelRepetition) &&
            (GetColorDepth(DisplayTimingPtr->PixelFormat) ==
                PllMpllGenericConfigSetting[settingIndex].ColorDepth)) {

            foundConfig = TRUE;
            *ConfigGenericSettingPPtr = &PllMpllGenericConfigSetting[settingIndex];
            break;
        }
    }

    // Use the fallback value the last index if no configuration is found
    if (foundConfig == FALSE) {
        *ConfigGenericSettingPPtr =
            &PllMpllGenericConfigSetting[ARRAYSIZE(PllMpllGenericConfigSetting)];
        foundConfig = TRUE;
    }

    return foundConfig;
}

OS_STATUS InitHDMI (
    DISPLAY_CONTEXT* DisplayContextPtr
    )
{
    DISPLAY_INTERFACE_CONTEXT* HdmiDisplayContextPtr =
        &DisplayContextPtr->DIContext[HDMI_DISPLAY];
    OS_STATUS status = 0;

    OS_ZERO_MEM(HdmiDisplayContextPtr, sizeof(*HdmiDisplayContextPtr));

    HdmiDisplayContextPtr->MmioBasePtr = (VOID*)OS_MMIO_MAP(HDMI_BASE);
    if (HdmiDisplayContextPtr->MmioBasePtr == NULL) {
        OS_ERROR("Fail to map HDMI register\n");
        goto Exit;
    }

    // Setup HDMI DDC muxing
    OS_WRITE32(IOMUXC_SW_MUX_CTL_PAD_KEY_COL3, 0x00000012);
    OS_WRITE32(IOMUXC_SW_MUX_CTL_PAD_KEY_ROW3, 0x00000012);
    OS_WRITE32(IOMUXC_HDMI_II2C_CLKIN_SELECT_INPUT, 0x00000001);
    OS_WRITE32(IOMUXC_HDMI_II2C_DATAIN_SELECT_INPUT, 0x00000001);

    SetHDMIPower(HdmiDisplayContextPtr, TRUE);

    // Mask all HDMI PHY interrupt
    HDMIWrite8(HDMI_PHY_MASK0, 0xFF);

    status = ReadEDID(
        DisplayContextPtr,
        HDMI_DISPLAY,
        HdmiDisplayContextPtr->EdidData,
        &HdmiDisplayContextPtr->EdidDataSize);
    if (status != OS_STATUS_SUCCESS) {
        OS_WARNING("Fail to read HDMI EDID data\n");
        status = OS_STATUS_SUCCESS;
    }

    status = GetPreferedTiming(
        HdmiDisplayContextPtr->EdidData,
        HdmiDisplayContextPtr->EdidDataSize,
        &HdmiDisplayContextPtr->PreferedTiming);
    if (status != OS_STATUS_SUCCESS) {
        OS_ERROR("Fail to retrieve HDMI prefered timing\n");
        goto Exit;
    }

    if ((HdmiDisplayContextPtr->PreferedTiming.HActive == 1920) &&
        (HdmiDisplayContextPtr->PreferedTiming.VActive == 1080)) {
        HdmiDisplayContextPtr->PreferedTiming.HBlank -= 6;
    }

Exit:
    return status;
}

OS_STATUS SetHDMIPower (
    DISPLAY_INTERFACE_CONTEXT* HdmiDisplayContextPtr,
    BOOLEAN PowerState
    )
{
    HDMI_PHY_CONF0_REG CurrentHDMIPhyConf0;

    CurrentHDMIPhyConf0.Reg = HDMIRead8(HDMI_PHY_CONF0);
    if (PowerState) {
        // Setup PHY
        CurrentHDMIPhyConf0.PDZ = 1;
        CurrentHDMIPhyConf0.ENTMDS = 1;
        CurrentHDMIPhyConf0.gen2_pddq = 1;
        CurrentHDMIPhyConf0.gen2_txpwron = 1;
        CurrentHDMIPhyConf0.seldataenpol = 1;
        CurrentHDMIPhyConf0.seldipif = 0;
    } else {
        // Just power down PHY for shutdown
        CurrentHDMIPhyConf0.PDZ = 0;
    }

    HDMIWrite8(HDMI_PHY_CONF0, CurrentHDMIPhyConf0.Reg);

    OS_SLEEP(3);

    return OS_STATUS_SUCCESS;
}

OS_STATUS SetHDMIPhy (
    DISPLAY_INTERFACE_CONTEXT* HdmiDisplayContextPtr,
    DISPLAY_TIMING* Timings
    )
{
    OS_STATUS status;
    HDMI_PHY_CONF0_REG CurrentHDMIPhyConf0;
    PLL_MPLL_CONFIG*  pllMpllConfig;

    // Disable Audio
    {
        HDMI_FC_AUDSCONF_REG fcAudsConf;

        fcAudsConf.Reg = HDMIRead8(HDMI_FC_AUDSCONF);
        fcAudsConf.aud_packet_layout = 0;
        HDMIWrite8(HDMI_FC_AUDSCONF, fcAudsConf.Reg);
    }

    // Minimum PCLK period / frequency (pixel repetition) : 74 ns / 13.5 MHz
    // Minimum PCLK period / frequency (no pixel repetition) : 39.7 ns / 24.175 MHz
    if(Timings->PixelClock < 13500000) {
        OS_ERROR("Unsupported pixel clock %d\n", Timings->PixelClock);
        status = OS_STATUS_INVALID_PARAM;
        goto Exit;
    }

    if (GetGenericConfigSetting(Timings, &pllMpllConfig) == FALSE) {
        OS_ERROR("No compatible generic config found\n");
        status = OS_STATUS_UNSUPPORTED;
        goto Exit;
    }

    // Color Space Converter : Not used in UEFI
    {
        HDMI_MC_CLKDIS_REG McClkdis;

        McClkdis.Reg = HDMIRead8(HDMI_MC_CLKDIS);

        // Disable CEC, color converter, audio & pixel repitition
        McClkdis.cecclk_disable = 1;
        McClkdis.cscclk_disable = 1;
        McClkdis.audclk_disable = 1;
        McClkdis.prepclk_disable = 1;
        McClkdis.hdcpclk_disable = 1;
        McClkdis.tmdsclk_disable = 0;
        McClkdis.pixelclk_disable = 0;

        HDMIWrite8(HDMI_MC_CLKDIS, McClkdis.Reg);
    }

    // Power down the PHY
    // To set the HDMI_PHY in Power-down mode, set the TX_PWRON signal to 1'b0
    // and the PDDQ signal to 1'b1. To power up the HDMI 3D Tx PHY and place it
    // in Active mode, set TX_PWRON to 1'b1 and PDDQ to 1'b0. Any configuration
    // programmed on the HDMI_PHY must be done in Power-down mode.
    CurrentHDMIPhyConf0.Reg = HDMIRead8(HDMI_PHY_CONF0);
    CurrentHDMIPhyConf0.gen2_txpwron = 0;
    CurrentHDMIPhyConf0.gen2_pddq = 1;
    HDMIWrite8(HDMI_PHY_CONF0, CurrentHDMIPhyConf0.Reg);

    // Let's reset the PHY to a well defined state based on spec.
    // The PHY_RESET signal is used to place the digital section of the IP in
    // a well - defined state
    {
        HDMI_MC_PHYRSTZ_REG phyRstzReg;
        HDMI_MC_HEACPHY_RST_REG heacphyRst;

        phyRstzReg.Reg = HDMIRead8(HDMI_MC_PHYRSTZ);
        heacphyRst.Reg = HDMIRead8(HDMI_MC_HEACPHY_RST);

        phyRstzReg.phyrstz = 1;
        HDMIWrite8(HDMI_MC_PHYRSTZ, phyRstzReg.Reg);
        phyRstzReg.phyrstz = 0;
        OS_SLEEP(10);
        HDMIWrite8(HDMI_MC_PHYRSTZ, phyRstzReg.Reg);

        // Even though we dont currently support this, reset the ethernet audio
        // control too
        heacphyRst.heacphyrst = 1;
        HDMIWrite8(HDMI_MC_HEACPHY_RST, heacphyRst.Reg);
    }

    // Program clock
    // PLL / MPLL Operation
    // The PLL / MPLL can be configured in Coherent mode or Non - Coherent mode (default).In
    //  Coherent mode, the TMDS clock is the MPLL feedback clock, which is coherent with the
    //  MPLL's high-speed output clock, because both clocks are shaped by the MPLL response.
    //  In Non - Coherent mode, the TMDS clock is the MPLL reference clock, which is not
    //  coherent with the MPLL's high-speed output clock.
    if (HDMIPhyI2cWrite(
            HdmiDisplayContextPtr,
            HDMI_PHY_CPCE_CTRL,
            pllMpllConfig->HdmiPhyCpceCtrl.Reg) == 0) {
        OS_ERROR("Fail to write to HDMI_PHY_CPCE_CTRL %x\n",
            pllMpllConfig->HdmiPhyCpceCtrl.Reg);
        status = OS_STATUS_DEVICE_ERROR;
        goto Exit;
    }

    if (HDMIPhyI2cWrite(
            HdmiDisplayContextPtr,
            HDMI_PHY_CURRCTRL,
            pllMpllConfig->HdmiPhyCurrctrl.Reg) == 0) {
        OS_ERROR("Fail to write to HDMI_PHY_CURRCTRL\n");
        status = OS_STATUS_DEVICE_ERROR;
        goto Exit;
    };

    if (HDMIPhyI2cWrite(
            HdmiDisplayContextPtr,
            HDMI_PHY_GMPCTRL,
            pllMpllConfig->HdmiPhyGmpctrl.Reg) == 0) {
        OS_ERROR("Fail to write to HDMI_PHY_GMPCTRL\n");
        status = OS_STATUS_DEVICE_ERROR;
        goto Exit;
    }

    // Maintaining the order of phy register writes
    if (HDMIPhyI2cWrite(
            HdmiDisplayContextPtr,
            HDMI_PHY_PLLPHBYCTRL,
            0x0000) == 0) {
        OS_ERROR("Fail to write to HDMI_PHY_PLLPHBYCTRL\n");
        status = OS_STATUS_DEVICE_ERROR;
        goto Exit;
    }

    // Coherent  mode
    if (HDMIPhyI2cWrite(
            HdmiDisplayContextPtr,
            HDMI_PHY_MSM_CTRL,
            0x0006) == 0) {
        OS_ERROR("Fail to write to HDMI_PHY_MSM_CTRL\n");
        status = OS_STATUS_DEVICE_ERROR;
        goto Exit;
    }

    // Resistance value 133.33 ohm
    if (HDMIPhyI2cWrite(
            HdmiDisplayContextPtr,
            HDMI_PHY_TXTERM,
            0x0005) == 0) {
        OS_ERROR("Fail to write to HDMI_PHY_TXTERM\n");
        status = OS_STATUS_DEVICE_ERROR;
        goto Exit;
    }

    // Enable clock symbol
    if (HDMIPhyI2cWrite(
            HdmiDisplayContextPtr,
            HDMI_PHY_CKSYMTXCTRL,
            0x8009) == 0) {
        OS_ERROR("Fail to write to HDMI_PHY_CKSYMTXCTRL\n");
        status = OS_STATUS_DEVICE_ERROR;
        goto Exit;
    }

    if (HDMIPhyI2cWrite(
            HdmiDisplayContextPtr,
            HDMI_PHY_VLEVCTRL,
            0x0210) == 0) {
        OS_ERROR("Fail to write to HDMI_PHY_VLEVCTRL\n");
        status = OS_STATUS_DEVICE_ERROR;
        goto Exit;
    }

    // Enable override
    if (HDMIPhyI2cWrite(
        HdmiDisplayContextPtr,
            HDMI_PHY_CKCALCTRL,
            0x8000) == 0) {
        OS_ERROR("Fail to write to HDMI_PHY_CKCALCTRL\n");
        status = OS_STATUS_DEVICE_ERROR;
        goto Exit;
    }

    CurrentHDMIPhyConf0.gen2_txpwron = 1;
    CurrentHDMIPhyConf0.gen2_pddq = 0;
    HDMIWrite8(HDMI_PHY_CONF0, CurrentHDMIPhyConf0.Reg);

    {
        HDMI_PHY_STAT0_REG phyStat0;
        UINT32 poolTimeOut = 5;

        status = OS_STATUS_DEVICE_ERROR;

        do {
            phyStat0.Reg = HDMIRead8(HDMI_PHY_STAT0);

            if (!phyStat0.TX_PHY_LOCK) {
                status = OS_STATUS_SUCCESS;
                break;
            }

            OS_SLEEP(1000);
            --poolTimeOut;
        } while (poolTimeOut);

        if (poolTimeOut == 0) {
            OS_ERROR("TX PHY remain unlock\n");
        }
    }

Exit:
    return status;
}

OS_STATUS SetHDMIDisplay (
    DISPLAY_INTERFACE_CONTEXT* HdmiDisplayContextPtr,
    DISPLAY_TIMING* Timings
    )
{
    OS_STATUS status;

    status = SetHDMIPhy(HdmiDisplayContextPtr, Timings);
    if (status != OS_STATUS_SUCCESS) {
        OS_ERROR("SetHDMIPhy failed\n");
        goto Exit;
    }

Exit:
    return status;
}

VOID SetDDCSpeed (
    DISPLAY_INTERFACE_CONTEXT* HdmiDisplayContextPtr,
    DDC_MODE mode
    )
{
    HDMIWrite8(HDMI_I2CM_DIV, mode);
}

OS_STATUS HDMIDDCRead (
    DISPLAY_INTERFACE_CONTEXT* HdmiDisplayContextPtr,
    UINT8 SlaveAddress,
    UINT8 RegisterAddress,
    UINT32 ReadSize,
    DDC_MODE DDCMode,
    UINT8* DataReadPtr
    )
{
    OS_STATUS status;
    UINT32 AddrCount;
    UINT8* CurrentDataReadPtr = DataReadPtr;

    // Setup EDID transaction and loop through all byte request
    SetDDCSpeed(HdmiDisplayContextPtr, DDCMode);

    HDMIWrite8(HDMI_IH_I2CM_STAT0, I2C_MASTER_ERROR | I2C_MASTER_DONE);
    HDMIWrite8(HDMI_I2CM_SLAVE, SlaveAddress);

    for (AddrCount = 0; AddrCount < ReadSize; ++AddrCount) {
        UINT32 i2CTimeOut = 1000;

        HDMIWrite8(HDMI_I2CM_ADDRESS, (UINT8)( RegisterAddress + AddrCount));
        HDMIWrite8(HDMI_I2CM_SEGADDR, 0x00);
        HDMIWrite8(HDMI_I2CM_OPERATION, DDC_READ_OPERATION);

        // Poll for completion
        UINT8 i2CMIntStatus = HDMIRead8(HDMI_IH_I2CM_STAT0);

        while ((i2CMIntStatus == 0) && (i2CTimeOut)) {
            i2CMIntStatus = HDMIRead8(HDMI_IH_I2CM_STAT0);
            --i2CTimeOut;
        }

        if (i2CTimeOut == 0) {
            status = OS_STATUS_DEVICE_ERROR;
            OS_ERROR("Timeout waiting for interrupt 0x%02x\n", i2CMIntStatus);
            goto Exit;
        }

        if (i2CMIntStatus & I2C_MASTER_ERROR) {
            status = OS_STATUS_DEVICE_ERROR;
            OS_ERROR("Failed to read with DDC 0x%02x\n", i2CMIntStatus);
            goto Exit;
        } else if (i2CMIntStatus & I2C_MASTER_DONE) {
            *CurrentDataReadPtr = HDMIRead8(HDMI_I2CM_DATAI);
            CurrentDataReadPtr++;
        } else {
            status = OS_STATUS_DEVICE_ERROR;
            OS_ERROR("Failed to read DDC unknown status 0x%02x\n", i2CMIntStatus);
            goto Exit;
        }

        HDMIWrite8(HDMI_IH_I2CM_STAT0, 0xFF);
    }

    status = OS_STATUS_SUCCESS;

Exit:
    return status;
}
