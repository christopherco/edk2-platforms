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

#include "Ipu.h"
#include "Display.h"
#include "DisplayInterface.h"

#define READ_WAVE_GEN(IPU_BASE, GEN_INDEX) \
    DiRead32(IPU_BASE, IPU_DIx_DW_GEN_OFFSET + (GEN_INDEX * 0x4))

#define WRITE_WAVE_GEN(IPU_BASE, GEN_INDEX, VALUE) \
    DiWrite32(IPU_BASE, IPU_DIx_DW_GEN_OFFSET + (GEN_INDEX * 0x4), VALUE)

#define READ_WAVE_SET(IPU_BASE, GEN_INDEX, SET_NUMBER) \
    DiRead32(IPU_BASE, IPU_DIx_DW_SET0_OFFSET + (SET_NUMBER * 0x30) + (GEN_INDEX * 0x4))

#define WRITE_WAVE_SET(IPU_BASE, GEN_INDEX, SET_NUMBER, VALUE) \
    DiWrite32(IPU_BASE, IPU_DIx_DW_SET0_OFFSET + (SET_NUMBER * 0x30) + (GEN_INDEX * 0x4), VALUE)

VOID DumpBasicDIReg (
    VOID* IpuMmioBasePtr,
    IPU_DIx_REGS* IpuDiRegsPtr
    )
{
    UINT32 index, setNumber, regVal;
    UINT32 printTotalGen = 8; // Limit printing (max 12)

    OS_INFO("---------- DI Register Dump ----------\n");
    // Print out generator value for D0
    OS_INFO("## Wave Gen\n");
    for (index = 0; index < printTotalGen; ++index) {
        regVal = READ_WAVE_GEN(IpuDiRegsPtr, index);
        OS_INFO("DI0_DW_GEN_%d 0x%08x\n", index, regVal);
    }
    // Print out generator value for D0
    OS_INFO("## Wave Set\n");
    for (index = 0; index < printTotalGen; ++index) {
        for (setNumber = 0; setNumber < 4; ++setNumber) {
            regVal = READ_WAVE_SET(IpuDiRegsPtr, index, setNumber);
            OS_INFO("DI0_DW_SET%d_%d 0x%08x\n", setNumber, index, regVal);
        }
    }

    regVal = IpuRead32(IpuMmioBasePtr, IPU_IPU_PM_OFFSET);
    OS_INFO("IPU_IPU_PM_OFFSET %x\n", regVal);

    regVal = DiRead32(IpuDiRegsPtr, IPU_DIx_BS_CLKGEN0_OFFSET);
    OS_INFO("IPU_DIx_BS_CLKGEN0_OFFSET %x\n", regVal);
    regVal = DiRead32(IpuDiRegsPtr, IPU_DIx_BS_CLKGEN1_OFFSET);
    OS_INFO("IPU_DIx_BS_CLKGEN1_OFFSET %x\n", regVal);
    regVal = DiRead32(IpuDiRegsPtr, IPU_DIx_SCR_CONF_OFFSET);
    OS_INFO("IPU_DIx_SCR_CONF_OFFSET %x\n", regVal);
    regVal = DiRead32(IpuDiRegsPtr, IPU_DIx_SW_GEN0_1_OFFSET);
    OS_INFO("IPU_DIx_SW_GEN0_1_OFFSET %x\n", regVal);
    regVal = DiRead32(IpuDiRegsPtr, IPU_DIx_SW_GEN1_1_OFFSET);
    OS_INFO("IPU_DIx_SW_GEN1_1_OFFSET %x\n", regVal);
    regVal = DiRead32(IpuDiRegsPtr, IPU_DIx_SW_GEN0_2_OFFSET);
    OS_INFO("IPU_DIx_SW_GEN0_2_OFFSET %x\n", regVal);
    regVal = DiRead32(IpuDiRegsPtr, IPU_DIx_SW_GEN1_2_OFFSET);
    OS_INFO("IPU_DIx_SW_GEN1_2_OFFSET %x\n", regVal);
    regVal = DiRead32(IpuDiRegsPtr, IPU_DIx_SW_GEN0_3_OFFSET);
    OS_INFO("IPU_DIx_SW_GEN0_3_OFFSET %x\n", regVal);
    regVal = DiRead32(IpuDiRegsPtr, IPU_DIx_SW_GEN1_3_OFFSET);
    OS_INFO("IPU_DIx_SW_GEN1_3_OFFSET %x\n", regVal);
    regVal = DiRead32(IpuDiRegsPtr, IPU_DIx_SW_GEN0_4_OFFSET);
    OS_INFO("IPU_DIx_SW_GEN0_4_OFFSET %x\n", regVal);
    regVal = DiRead32(IpuDiRegsPtr, IPU_DIx_SW_GEN1_4_OFFSET);
    OS_INFO("IPU_DIx_SW_GEN1_4_OFFSET %x\n", regVal);
    regVal = DiRead32(IpuDiRegsPtr, IPU_DIx_SW_GEN0_5_OFFSET);
    OS_INFO("IPU_DIx_SW_GEN0_5_OFFSET %x\n", regVal);
    regVal = DiRead32(IpuDiRegsPtr, IPU_DIx_SW_GEN1_5_OFFSET);
    OS_INFO("IPU_DIx_SW_GEN1_5_OFFSET %x\n", regVal);

    for (index = 0; index < 5; ++index) {
        regVal = DiRead32(IpuDiRegsPtr, IPU_DIx_STP_REP_OFFSET +  (index * 0x4));
        OS_INFO("IPU_DIx_STP_%d_REP_OFFSET %x\n", index + 1, regVal);
    }

    regVal = DiRead32(IpuDiRegsPtr, IPU_DIx_SYNC_AS_GEN_OFFSET);
    OS_INFO("IPU_DIx_SYNC_AS_GEN_OFFSET %x\n", regVal);
    regVal = DiRead32(IpuDiRegsPtr, IPU_DIx_GENERAL_OFFSET);
    OS_INFO("IPU_DIx_GENERAL_OFFSET %x\n", regVal);
    regVal = DiRead32(IpuDiRegsPtr, IPU_DIx_POL_OFFSET);
    OS_INFO("IPU_DIx_POL_OFFSET %x\n", regVal);
    regVal = DiRead32(IpuDiRegsPtr, IPU_IPU_DISP_GEN_OFFSET);
    OS_INFO("IPU_IPU_DISP_GEN_OFFSET %x\n", regVal);
    OS_INFO("------------------------------------\n\n");
}

VOID ConfigureSyncWave (
    VOID* IpuMmioBasePtr,
    IPU_DIx_REGS* IpuDiRegsPtr,
    UINT32 CounterIndex,
    UINT32 RunValue,
    UINT32 RunResolution,
    UINT32 OffsetValue,
    UINT32 OffsetResolution,
    UINT32 CounterPolarityGenEn,
    UINT32 CounterAutoReload,
    UINT32 CounterClearSelect,
    UINT32 CounterDown,
    UINT32 CounterPolarityTriggerSelect,
    UINT32 CounterPolarityClearSelect,
    UINT32 CounterUp,
    UINT32 StepRepeat
    )
{
    IPUx_DIx_SW_GEN0_x_REG diSwGen0Reg;
    IPUx_DIx_SW_GEN1_x_REG diSwGen1Reg;
    IPUx_DIx_STP_REP_REG stepRepeatReg;

    OS_ZERO_MEM((void*)&diSwGen0Reg, sizeof(diSwGen0Reg));
    diSwGen0Reg.dix_offset_resolution = OffsetResolution;
    diSwGen0Reg.dix_offset_value = OffsetValue;
    diSwGen0Reg.dix_run_resolution = RunResolution;
    diSwGen0Reg.dix_run_value_m1 = RunValue;

    DiWrite32(
        IpuDiRegsPtr,
        IPU_DIx_SW_GEN0_1_OFFSET + ((CounterIndex - 1) * 0x04),
        diSwGen0Reg.Reg);

    OS_ZERO_MEM((void*)&diSwGen1Reg, sizeof(diSwGen1Reg));
    diSwGen1Reg.dix_cnt_up = CounterUp;
    diSwGen1Reg.dix_cnt_polarity_clr_sel = CounterPolarityClearSelect;
    diSwGen1Reg.dix_cnt_polarity_trigger_sel = CounterPolarityTriggerSelect;
    diSwGen1Reg.dix_cnt_down = CounterDown;
    diSwGen1Reg.dix_cnt_clr_sel = CounterClearSelect;
    diSwGen1Reg.dix_cnt_auto_reload = CounterAutoReload;
    diSwGen1Reg.dix_cnt_polarity_gen_en = CounterPolarityGenEn;

    DiWrite32(
        IpuDiRegsPtr,
        IPU_DIx_SW_GEN1_1_OFFSET + ((CounterIndex - 1) * 0x04),
        diSwGen1Reg.Reg);

    {
        UINT32 stepIndex = (CounterIndex - 1) / 2;

        stepRepeatReg.Reg = IpuRead32(
            IpuMmioBasePtr,
            IPU_DI0_STP_REP_OFFSET + (stepIndex * 0x4));

        if (CounterIndex % 2) {
            stepRepeatReg.dix_step_repeat_2i_minus_1 = StepRepeat;
        } else {
            stepRepeatReg.dix_step_repeat_2i = StepRepeat;
        }

        IpuWrite32(
            IpuMmioBasePtr,
            IPU_DI0_STP_REP_OFFSET + (stepIndex * 0x4),
            stepRepeatReg.Reg);
    }
}

OS_STATUS ConfigureDI (
    DISPLAY_INTERFACE_CONTEXT* DIContextPtr,
    UINT32 DisplayIndex,
    DISPLAY_TIMING* DisplayTimingPtr
    )
{
    OS_STATUS status;
    UINT32 baseDiv;
    UINT64 diFreq = DisplayTimingPtr->PixelClock;
    UINT32 hTotal = DisplayTimingPtr->HActive + DisplayTimingPtr->HBlank;
    UINT32 vTotal = DisplayTimingPtr->VActive + DisplayTimingPtr->VBlank;
    VOID* ipuMmioBasePtr = DIContextPtr->IpuMmioBasePtr;
    IPU_DIx_REGS* ipuDiRegsPtr = DIContextPtr->IpuDiRegsPtr;

    status = ImxSetPll5ReferenceRate(DisplayTimingPtr->PixelClock);
    if (status != OS_STATUS_SUCCESS) {
        OS_ERROR("Fail to setup PLL5=%r\n", status);
        goto Exit;
    }

    // Setup base timer (fundamental timer). The base timer should already
    // setup to match the pixel clock frequency.
    // Shift 4 as the bottom 4 bits are fractional
    baseDiv = (UINT32)((diFreq << 4) / DisplayTimingPtr->PixelClock);

    DiWrite32(ipuDiRegsPtr, IPU_DIx_BS_CLKGEN0_OFFSET, baseDiv);

    // Up is always set to 0. Down is half of the pixel clock period where
    // the first bit is fraction
    baseDiv >>= 4;

    DiWrite32(ipuDiRegsPtr, IPU_DIx_BS_CLKGEN1_OFFSET, baseDiv << 16);
    // Calculate divisor, again this would usually be 1.
    baseDiv = (UINT32)(diFreq / DisplayTimingPtr->PixelClock);

    // Set up wave, there 12 wave quartet, for now default to the first.
    // Each wave quartet has 4 set register
    {
        IPUx_DIx_DW_SET_REG dixDwSetReg;
        IPUx_DIx_DW_GEN_REG dixDwGenReg;

        // Set 0 is just a blank signal where up and down is set to 0
        OS_ZERO_MEM((void*)&dixDwSetReg, sizeof(dixDwSetReg));
        dixDwSetReg.dix_data_cnt_upx_i = 0;
        dixDwSetReg.dix_data_cnt_downx_i = 0;
        WRITE_WAVE_SET(
            ipuDiRegsPtr,
            DW_GEN_0,
            DW_SET_0,
            dixDwSetReg.Reg);

        // Set 3 is setup to match pixel clock
        OS_ZERO_MEM((void*)&dixDwSetReg, sizeof(dixDwSetReg));
        dixDwSetReg.dix_data_cnt_upx_i = 0;
        dixDwSetReg.dix_data_cnt_downx_i = baseDiv * 2;
        WRITE_WAVE_SET(
            ipuDiRegsPtr,
            DW_GEN_0,
            DW_SET_3,
            dixDwSetReg.Reg);

        // All pins blank signal except pin 15
        // Need to get pin mapping documentation
        OS_ZERO_MEM((void*)&dixDwGenReg, sizeof(dixDwGenReg));
        dixDwGenReg.dix_pt_0_i = DW_SET_0;
        dixDwGenReg.dix_pt_1_i = DW_SET_0;
        dixDwGenReg.dix_pt_2_i = DW_SET_0;
        dixDwGenReg.dix_pt_3_i = DW_SET_0;
        dixDwGenReg.dix_pt_4_i = DW_SET_3;
        dixDwGenReg.dix_pt_5_i = DW_SET_0;
        dixDwGenReg.dix_pt_6_i = DW_SET_0;
        dixDwGenReg.dix_cst_i = DW_SET_0;

        // Reuse the base divisor to determine extra IPU cycles.
        dixDwGenReg.dix_componnent_size_i = dixDwGenReg.dix_access_size_i =
            baseDiv - 1;
        WRITE_WAVE_GEN(ipuDiRegsPtr, DW_GEN_0, dixDwGenReg.Reg);
    }

    // Spec mention this as number of display rows but display only works
    // proper if this is setup as vertical total
    DiWrite32(ipuDiRegsPtr, IPU_DIx_SCR_CONF_OFFSET, vTotal - 1);

    {
        // Internal HSYNC
        ConfigureSyncWave(
            ipuMmioBasePtr,
            ipuDiRegsPtr,
            DI_COUNTER_1_INTERNAL_HSYNC, // CounterIndex
            hTotal - 1,   // Runvalue
            DI_COUNTER_0_DISPLAY_CLOCK + 1, // RunResolution
            0,            // OffsetValue
            0,            // OffsetResolution
            0,            // CounterPolarityGenEn
            1,            // CounterAutoReload
            DI_COUNTER_DISABLED, // CounterClearSelect
            0,            // CountDown
            0,            // CounterPolarityTriggerSelect
            0,            // CounterPolarityClearSelect
            0,            // CounterUp
            0);           // StepRepeat

        // Output HSYNC
        ConfigureSyncWave(
            ipuMmioBasePtr,
            ipuDiRegsPtr,
            DI_COUNTER_2_OUTPUT_HSYNC, // CounterIndex
            hTotal - 1,   // Runvalue
            DI_COUNTER_0_DISPLAY_CLOCK + 1, // RunResolution
            0,            // OffsetValue
            DI_COUNTER_0_DISPLAY_CLOCK + 1, // OffsetResolution - Display clock
            1,            // CounterPolarityGenEn
            1,            // CounterAutoReload
            DI_COUNTER_DISABLED, // CounterClearSelect
            DisplayTimingPtr->HSync * 2,    // CountDown
            1,            // CounterPolarityTriggerSelect
            0,            // CounterPolarityClearSelect
            0,            // CounterUp
            0);           // StepRepeat

        // Output VSYNC
        ConfigureSyncWave(
            ipuMmioBasePtr,
            ipuDiRegsPtr,
            DI_COUNTER_3_OUTPUT_VSYNC, // CounterIndex
            vTotal - 1,   // Runvalue
            DI_COUNTER_1_INTERNAL_HSYNC + 1, // RunResolution - Counter 1
            0,            // OffsetValue
            0,            // OffsetResolution
            1,            // CounterPolarityGenEn
            1,            // CounterAutoReload
            DI_COUNTER_DISABLED, // CounterClearSelect
            DisplayTimingPtr->VSync * 2,    // CountDown
            2,            // CounterPolarityTriggerSelect
            0,            // CounterPolarityClearSelect
            0,            // CounterUp
            0);           // StepRepeat

        // Active lines
        ConfigureSyncWave(
            ipuMmioBasePtr,
            ipuDiRegsPtr,
            DI_COUNTER_4_ACTIVE_LINE , // CounterIndex
            0,            // Runvalue
            DI_COUNTER_2_OUTPUT_HSYNC + 1, // RunResolution - Counter 2
            DisplayTimingPtr->VSync + DisplayTimingPtr->VSyncOffset, // Offset
            DI_COUNTER_2_OUTPUT_HSYNC + 1,// OffsetResolution - Counter 2
            0,            // CounterPolarityGenEn
            0,            // CounterAutoReload
            DI_COUNTER_3_OUTPUT_VSYNC + 1, // CounterClearSelect - Counter 3
            0,            // CountDown
            0,            // CounterPolarityTriggerSelect
            0,            // CounterPolarityClearSelect
            0,            // CounterUp
            DisplayTimingPtr->VActive); // StepRepeat repeat for total VActive

        // Active clock
        ConfigureSyncWave(
            ipuMmioBasePtr,
            ipuDiRegsPtr,
            DI_COUNTER_5_ACTIVE_CLOCK, // CounterIndex
            0,            // Runvalue
            DI_COUNTER_0_DISPLAY_CLOCK + 1, // RunResolution - Display clock
            DisplayTimingPtr->HSync + DisplayTimingPtr->HSyncOffset, // Offset
            DI_COUNTER_0_DISPLAY_CLOCK + 1, // OffsetResolution - Display clock
            0,            // CounterPolarityGenEn
            0,            // CounterAutoReload
            DI_COUNTER_4_ACTIVE_LINE + 1, // CounterClearSelect - Counter 4
            0,            // CountDown
            0,            // CounterPolarityTriggerSelect
            0,            // CounterPolarityClearSelect
            0,            // CounterUp
            DisplayTimingPtr->HActive); // StepRepeat
    }

    {
        IPUx_DIx_SYNC_AS_GEN_REG dixSyncAsGenReg;

        OS_ZERO_MEM((void*)&dixSyncAsGenReg, sizeof(dixSyncAsGenReg));
        // VSYNC is setup as counter 3 above, 0 index based
        dixSyncAsGenReg.dix_vsync_sel = 3 - 1;
        // Number of row DI prepares next frame data.
        // This seem to be the default value.
        dixSyncAsGenReg.dix_sync_start = 2;
        DiWrite32(ipuDiRegsPtr, IPU_DIx_SYNC_AS_GEN_OFFSET, dixSyncAsGenReg.Reg);
    }

    // Setup general register
    {
        IPUx_DIx_GENERAL_REG dixGeneralReg;

        OS_ZERO_MEM((void*)&dixGeneralReg, sizeof(dixGeneralReg));
        // Counter 1 as display line
        dixGeneralReg.dix_disp_y_sel = DI_COUNTER_1_INTERNAL_HSYNC - 1;
        // Stop at the next edge of the display clock
        dixGeneralReg.DIx_CLOCK_STOP_MODE = 0;
        // The display's clock is stopped after the next VSYNC
        dixGeneralReg.DIx_DISP_CLOCK_INIT = 0;
        // IPP_PIN_2 is coming from counter #2
        dixGeneralReg.dix_mask_sel = 0;
        // External clock - for not the video PLL
        dixGeneralReg.dix_vsync_ext = 1;
        // External clock - for not the video PLL
        dixGeneralReg.dix_clk_ext = 1;
        // 4 cycle watch dog based on BSP
        dixGeneralReg.DIx_WATCHDOG_MODE = 0;
        // default sync to counter 0
        dixGeneralReg.dix_sync_count_sel = DI_COUNTER_1_INTERNAL_HSYNC - 1;
        // In the event of error drive the last component
        dixGeneralReg.dix_err_treatment = 0;
        // An internal VSYNC signal asserted 2 lines before the DI's VSYNC
        dixGeneralReg.dix_erm_vsync_sel = 0;

        switch(DIContextPtr->displayInterface)
        {
            case HDMI_DISPLAY:
                // Zero for HDMI display
                dixGeneralReg.dix_polarity_disp_clk = 0;
                dixGeneralReg.dix_polarity_cs1 = 0;
                dixGeneralReg.dix_polarity_cs0 = 0;
                dixGeneralReg.dix_polarity_i_1 = 0;
                break;
            default:
                status = OS_STATUS_UNSUPPORTED;
                OS_ERROR(
                    "Unsupported display interface %d",
                    DIContextPtr->displayInterface);
                goto Exit;
        }

        DiWrite32(ipuDiRegsPtr, IPU_DIx_GENERAL_OFFSET, dixGeneralReg.Reg);
    }

    {
        IPUx_DIx_POL_REG dixPolReg;

        OS_ZERO_MEM((void*)&dixPolReg, sizeof(dixPolReg));
        // CS0
        dixPolReg.DIx_CS0_DATA_POLARITY = 1;
        dixPolReg.dix_cs0_polarity = 0x7F;
        // CS1
        dixPolReg.DIx_CS1_DATA_POLARITY = 1;
        dixPolReg.dix_cs1_polarity = 0x7F;
        // DRDY
        dixPolReg.DIx_DRDY_DATA_POLARITY = 0;
        dixPolReg.dix_drdy_polarity = 0x7F;
        // Wait
        dixPolReg.DIx_WAIT_POLARITY = 0;
        // CS0 byte enable polarity
        dixPolReg.DIx_CS0_BYTE_EN_POLARITY = 0;
        // CS1 byte enable polarity
        dixPolReg.DIx_CS1_BYTE_EN_POLARITY = 0;

        DiWrite32(ipuDiRegsPtr, IPU_DIx_POL_OFFSET, dixPolReg.Reg);
    }

    {
        UINT32 dispGenReg;

        dispGenReg = IpuRead32(ipuMmioBasePtr, IPU_IPU_DISP_GEN_OFFSET);
        dispGenReg &= ~(0x0F << 18);
        dispGenReg |= (2 << 18);
        IpuWrite32(ipuMmioBasePtr, IPU_IPU_DISP_GEN_OFFSET, dispGenReg);
    }

    // Register dump, commented out by default
#ifdef REGISTER_DUMP
    DumpBasicDIReg(ipuMmioBasePtr, ipuDiRegsPtr);
#endif

    status = OS_STATUS_SUCCESS;

Exit:
    return status;
}
