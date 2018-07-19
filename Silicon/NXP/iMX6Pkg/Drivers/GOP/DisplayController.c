/** @file
*
*  Copyright (c) Microsoft Corporation. All rights reserved.
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

#include "osal.h"

#include "Ipu.h"
#include "Display.h"
#include "DisplayController.h"
#include "DisplayInterface.h"

VOID DumpBasicDCReg(
    VOID* IpuMmioBasePtr)
{
    UINT32 regVal;
    UINT32 counter, index;

    OS_INFO("---------- DC Register Dump ----------\n");
    OS_INFO("## Configuration\n\n");
    regVal = IpuRead32(IpuMmioBasePtr, IPU_DC_WR_CH_CONF_5_OFFSET);
    OS_INFO("IPU_DC_WR_CH_CONF_5_OFFSET %x\n", regVal);
    regVal = IpuRead32(IpuMmioBasePtr, IPU_DC_WR_CH_CONF_1_OFFSET);
    OS_INFO("IPU_DC_WR_CH_CONF_1_OFFSET %x\n", regVal);
    regVal = IpuRead32(IpuMmioBasePtr, IPU_DC_DISP_CONF1_0_OFFSET);
    OS_INFO("IPU_DC_DISP_CONF1_0_OFFSET %x\n", regVal);
    regVal = IpuRead32(IpuMmioBasePtr, IPU_DC_DISP_CONF1_1_OFFSET);
    OS_INFO("IPU_DC_DISP_CONF1_1_OFFSET %x\n", regVal);
    regVal = IpuRead32(IpuMmioBasePtr, IPU_DC_DISP_CONF1_2_OFFSET);
    OS_INFO("IPU_DC_DISP_CONF1_2_OFFSET %x\n", regVal);
    regVal = IpuRead32(IpuMmioBasePtr, IPU_DC_DISP_CONF1_3_OFFSET);
    OS_INFO("IPU_DC_DISP_CONF1_3_OFFSET %x\n", regVal);
    regVal = IpuRead32(IpuMmioBasePtr, IPU_DC_DISP_CONF2_0_OFFSET);
    OS_INFO("IPU_DC_DISP_CONF2_0_OFFSET %x\n", regVal);
    regVal = IpuRead32(IpuMmioBasePtr, IPU_DC_GEN_OFFSET);
    OS_INFO("IPU_DC_GEN_OFFSET %x\n", regVal);
    OS_INFO("## Bus MAPPING\n\n");
    {
        for (counter = 0, index = 0; index < 26; counter += 4, ++index) {
            regVal = IpuRead32(IpuMmioBasePtr, IPU_DC_MAP_CONF_0_OFFSET + counter);
            OS_INFO("IPU_DC_MAP_CONF_%d %x\n", index, regVal);
        }
    }

    OS_INFO("## Channel MicroCode setup\n\n");
    {
        // Only print out channel 5 as we only support single mode for now
        regVal = IpuRead32(IpuMmioBasePtr, IPU_DC_RL0_CH_5_OFFSET);
        OS_INFO("IPU_DC_RL0_CH_5_OFFSET %x\n", regVal);
        regVal = IpuRead32(IpuMmioBasePtr, IPU_DC_RL1_CH_5_OFFSET);
        OS_INFO("IPU_DC_RL1_CH_5_OFFSET %x\n", regVal);
        regVal = IpuRead32(IpuMmioBasePtr, IPU_DC_RL2_CH_5_OFFSET);
        OS_INFO("IPU_DC_RL2_CH_5_OFFSET %x\n", regVal);
        regVal = IpuRead32(IpuMmioBasePtr, IPU_DC_RL3_CH_5_OFFSET);
        OS_INFO("IPU_DC_RL3_CH_5_OFFSET %x\n", regVal);
        regVal = IpuRead32(IpuMmioBasePtr, IPU_DC_RL4_CH_5_OFFSET);
        OS_INFO("IPU_DC_RL4_CH_5_OFFSET %x\n", regVal);
    }

    OS_INFO("## MicroCode\n\n");
    {
        // There are 256 template, only print out the first 10
        for (counter = 0, index = 0; index < 10; counter += 8, ++index) {
            OS_INFO("(%d)", index);
            regVal = IpuRead32(
                IpuMmioBasePtr,
                IPU_DC_TEMPLATE_REGS_ADDR_OFFSET + counter);
            OS_INFO("- %8x", regVal);
            regVal = IpuRead32(
                IpuMmioBasePtr,
                IPU_DC_TEMPLATE_REGS_ADDR_OFFSET + counter + 4);
            OS_INFO(" %8x -\n", regVal);
        }
    }
    OS_INFO("------------------------------------\n\n");
}

#pragma pack(push, 1)
typedef union {
    struct {
        UINT32 SYNC : 4;
        UINT32 GLUELOGIC : 7;
        UINT32 WAVEFORM : 4;
        UINT32 MAPPING : 5;
        UINT32 DATA : 16;
        UINT32 OPCODE : 5;
        UINT32 STOP : 1;
        UINT32 Unused : 22;
    };
    struct     {
        UINT32 LowWord;
        UINT32 HighWord;
    };
} DC_WROD_COMMAND_TEMPLATE;
#pragma pack(pop)

OS_STATUS WriteWRODCommand (
    VOID* IpuMmioBasePtr,
    UINT32 MicroCodeAddr,
    UINT32 Data,
    UINT32 Mapping,
    UINT32 WaveForm,
    UINT32 GlueLogic,
    UINT32 Sync)
{
    DC_WROD_COMMAND_TEMPLATE wrodCommand;
    UINT32 microCodeAddrOffset =
        IPU_DC_TEMPLATE_REGS_ADDR_OFFSET + (MicroCodeAddr * 8);

    OS_ZERO_MEM((void*)&wrodCommand, sizeof(wrodCommand));
    wrodCommand.STOP = 1;
    wrodCommand.OPCODE = 0x18;
    wrodCommand.DATA = Data;
    wrodCommand.MAPPING = Mapping;
    wrodCommand.WAVEFORM = WaveForm + 1;
    wrodCommand.GLUELOGIC = GlueLogic;
    wrodCommand.SYNC = Sync;

    IpuWrite32(IpuMmioBasePtr, microCodeAddrOffset, wrodCommand.LowWord);
    IpuWrite32(IpuMmioBasePtr, microCodeAddrOffset + 4, wrodCommand.HighWord);

    return OS_STATUS_SUCCESS;
}

OS_STATUS SetDCChannelState (
    VOID* IpuMmioBasePtr,
    PROG_CHAN_TYP ChannelType
    )
{
    IPU_DC_WR_CH_CONF_5_REG wrChConfigReg;

    wrChConfigReg.Reg = IpuRead32(IpuMmioBasePtr, IPU_DC_WR_CH_CONF_5_OFFSET);

    wrChConfigReg.PROG_CHAN_TYP = ChannelType;

    IpuWrite32(IpuMmioBasePtr, IPU_DC_WR_CH_CONF_5_OFFSET, wrChConfigReg.Reg);

    return OS_STATUS_SUCCESS;
}

OS_STATUS ConfigureDCChannel (
    DISPLAY_INTERFACE_CONTEXT* DIContextPtr,
    DISPLAY_INTERFACE DisplayInterface,
    UINT32 DisplayIndex,
    DISPLAY_TIMING* DisplayTimingPtr)
{
    OS_STATUS status;
    IPU_DC_WR_CH_CONF_5_REG wrChConfigReg;
    VOID* ipuMmioBasePtr = DIContextPtr->IpuMmioBasePtr;

    OS_ZERO_MEM((void*)&wrChConfigReg, sizeof(wrChConfigReg));
    wrChConfigReg.PROG_START_TIME = 0;
    wrChConfigReg.FILED_MODE = 0;
    wrChConfigReg.CHAN_MASK_DEFAULT = 0; // only used highest priority
    wrChConfigReg.PROG_CHAN_TYP = 0; // Begin as disable
    wrChConfigReg.PROG_DISP_ID = DisplayInterface;
    wrChConfigReg.PROG_DI_ID = DisplayIndex % 2;
    wrChConfigReg.W_SIZE = 0x02; // 24 Bits
    wrChConfigReg.Reserved1 = 0;
    wrChConfigReg.Reserved2 = 0;

    // Channel 5 is used main primary flow
    IpuWrite32(ipuMmioBasePtr, IPU_DC_WR_CH_CONF_5_OFFSET, wrChConfigReg.Reg);
    // Start address of memory always 0
    IpuWrite32(ipuMmioBasePtr, IPU_DC_WR_CH_ADDR_5_OFFSET, 0);

    OS_ZERO_MEM((void*)&wrChConfigReg, sizeof(wrChConfigReg));
    wrChConfigReg.FILED_MODE = 0;
    wrChConfigReg.CHAN_MASK_DEFAULT = 0; // only used highest priority
    wrChConfigReg.PROG_CHAN_TYP = 4; // Enable
    wrChConfigReg.PROG_DISP_ID = DisplayInterface;
    wrChConfigReg.PROG_DI_ID = DisplayIndex % 2;
    wrChConfigReg.W_SIZE = 0x02; // 1 Bits
    wrChConfigReg.Reserved1 = 0;
    wrChConfigReg.Reserved2 = 0;

    // Channel 1 is used as sync/async flow
    IpuWrite32(ipuMmioBasePtr, IPU_DC_WR_CH_CONF_1_OFFSET, wrChConfigReg.Reg);
    IpuWrite32(ipuMmioBasePtr, IPU_DC_WR_CH_ADDR_1_OFFSET, 0);

    {
        IPUx_DC_DISP_CONF1_REG dispConf1Reg;

        dispConf1Reg.DISP_TYP = 0x02; // What is byte_enabled
        dispConf1Reg.ADDR_INCREMENT = 0; // Increase by 1 byte
        dispConf1Reg.ADDR_BE_L_INC = 0;
        dispConf1Reg.MCU_ACC_LB_MASK_3 = 0;
        dispConf1Reg.DISP_RD_VALUE_PTR = 0;
        IpuWrite32(ipuMmioBasePtr, IPU_DC_DISP_CONF1_0_OFFSET, dispConf1Reg.Reg);

        // set stride
        IpuWrite32(ipuMmioBasePtr, IPU_DC_DISP_CONF2_0_OFFSET, DisplayTimingPtr->VActive);
    }

    // Setup general register
    {
        IPUx_IPU_DC_GEN_REG dcGenReg;

        dcGenReg.Sync_1_6 = 2; // Sync flow
        dcGenReg.MASK_EN = 0; // Disable masking
        dcGenReg.MASK4CHAN_5 = 0; // Ignore as mask is disabled
        dcGenReg.SYNC_PRIORITY_5 = 1; // Higher sync priority for channel 5 which is the main channel
        dcGenReg.SYNC_PRIORITY_1 = 0; // Lower sync priority
        dcGenReg.DC_CH5_TYPE = 0; // Normal mode, sync flow throuh channel 5
        dcGenReg.DC_BK_EN = 0; // No cursor support
        dcGenReg.DC_BKDIV = 0; // No cursor support

        IpuWrite32(ipuMmioBasePtr, IPU_DC_GEN_OFFSET, dcGenReg.Reg);
    }

    // Do not use any user event
    IpuWrite32(ipuMmioBasePtr, IPU_DC_UGDE0_0_OFFSET, 0);
    IpuWrite32(ipuMmioBasePtr, IPU_DC_UGDE1_0_OFFSET, 0);
    IpuWrite32(ipuMmioBasePtr, IPU_DC_UGDE2_0_OFFSET, 0);
    IpuWrite32(ipuMmioBasePtr, IPU_DC_UGDE3_0_OFFSET, 0);

    {
        IPUx_DC_MAP_CONF_MAP_REG dcMapConf0Reg;
        DC_MAP_CONF_OFFSET_MASK_REG dcConfOffsetMaskReg;
        UINT32 mask0, mask1, mask2;
        UINT32 offset0, offset1, offset2;

        dcMapConf0Reg.MAPPING_PNTR_BYTE0_X = 0;
        dcMapConf0Reg.MAPPING_PNTR_BYTE1_X = 1;
        dcMapConf0Reg.MAPPING_PNTR_BYTE2_X = 2;
        dcMapConf0Reg.MAPPING_PNTR_BYTE0_Y = 3; // Unused
        dcMapConf0Reg.MAPPING_PNTR_BYTE1_Y = 4; // Unused
        dcMapConf0Reg.MAPPING_PNTR_BYTE2_Y = 5; // Unused

        IpuWrite32(ipuMmioBasePtr, IPU_DC_MAP_CONF_0_OFFSET, dcMapConf0Reg.Reg);

        switch (DisplayInterface)
        {
            // PixelFormat RGB24
            case HDMI_DISPLAY:
                mask0 = mask1 = mask2 = 0xFF;
                offset0 = 7;
                offset1 = 15;
                offset2 = 23;
                break;
            // PixelFormat RGB666
            case LVDS0_DISPLAY:
            case LVDS1_DISPLAY:
                mask0 = mask1 = mask2 = 0xFC;
                offset0 = 5;
                offset1 = 11;
                offset2 = 17;
                break;
            default:
                ASSERT(FALSE);
                status = OS_STATUS_UNSUPPORTED;
                goto Exit;
        }

        dcConfOffsetMaskReg.MD_MASK_X = mask0;
        dcConfOffsetMaskReg.MD_OFFSET_X = offset0; // Blue
        dcConfOffsetMaskReg.MD_MASK_Y = mask1;
        dcConfOffsetMaskReg.MD_OFFSET_Y = offset1; // Green

        IpuWrite32(ipuMmioBasePtr, IPU_DC_MAP_CONF_15_OFFSET, dcConfOffsetMaskReg.Reg);

        dcConfOffsetMaskReg.MD_MASK_X = mask2;
        dcConfOffsetMaskReg.MD_OFFSET_X = offset2; // Red
        dcConfOffsetMaskReg.MD_MASK_Y = 0x00;
        dcConfOffsetMaskReg.MD_OFFSET_Y = 0; // Unused

        IpuWrite32(ipuMmioBasePtr, IPU_DC_MAP_CONF_16_OFFSET, dcConfOffsetMaskReg.Reg);
    }

    // Setup microcode
    {
        IPU_DC_RL0_CH_5_REG dcRl0Ch5Reg;
        IPU_DC_RL2_CH_5_REG dcRl2Ch5Reg;
        IPU_DC_RL4_CH_5_REG dcRl4Ch5Reg;

        // New line event point to the first microcode (0)
        OS_ZERO_MEM((void*)&dcRl0Ch5Reg, sizeof(dcRl0Ch5Reg));
        dcRl0Ch5Reg.COD_NL_START_CHAN_5 = 0;
        dcRl0Ch5Reg.COD_NL_PRIORITY_CHAN_5 = 3;
        IpuWrite32(ipuMmioBasePtr, IPU_DC_RL0_CH_5_OFFSET, dcRl0Ch5Reg.Reg);

        // End of line event point to the second microcode (1)
        OS_ZERO_MEM((void*)&dcRl2Ch5Reg, sizeof(dcRl2Ch5Reg));
        dcRl2Ch5Reg.COD_EOL_START_CHAN_5 = 1;
        dcRl2Ch5Reg.COD_EOL_PRIORITY_CHAN_5 = 2;
        IpuWrite32(ipuMmioBasePtr, IPU_DC_RL2_CH_5_OFFSET, dcRl2Ch5Reg.Reg);

        // New data event point to the first microcode (2)
        OS_ZERO_MEM((void*)&dcRl4Ch5Reg, sizeof(dcRl4Ch5Reg));
        dcRl4Ch5Reg.COD_NEW_DATA_START_CHAN_5 = 2;
        dcRl4Ch5Reg.COD_NEW_DATA_PRIORITY_CHAN_5 = 1;
        IpuWrite32(ipuMmioBasePtr, IPU_DC_RL4_CH_5_OFFSET, dcRl4Ch5Reg.Reg);

        // MicroCodeAddr
        // - 0 set for new line event
        // Data
        // - Unsused
        // Map to mapping parameter 0
        // - In order to point to MAPPING_PNTR_BYTE2_0, MAPPING_PNTR_BYTE1_0,
        //   MAPPING_PNTR_BYTE0_0 the user should write 1 to the MAPPING field
        // WaveForm
        // - Points to DI0_DW_GEN_0 or DI1_DW_GEN_0 (Define which waveform
        //   register is used, default to first IPUx_DI0_DW_SET0_1)
        // GlueLogic
        // - Once the signal is asserted then it remains asserted (high or low
        //   according to the polarity)
        // Sync
        // - Sync with counter 5
        WriteWRODCommand(
            ipuMmioBasePtr,
            0,
            0,
            1,
            DW_GEN_0,
            8,
            DI_COUNTER_5_ACTIVE_CLOCK);

        // MicroCodeAddr
        // - 1 set for end of line event
        // Data
        // - Unsused
        // Map to mapping parameter 0
        // - In order to point to MAPPING_PNTR_BYTE2_0, MAPPING_PNTR_BYTE1_0,
        //   MAPPING_PNTR_BYTE0_0 the user should write 1 to the MAPPING field
        // WaveForm
        // - Points to DI0_DW_GEN_0 or DI1_DW_GEN_0 (Define which waveform
        //   register is used, default to first IPUx_DI0_DW_SET0_1)
        // GlueLogic
        // - Once the signal is negated then it remains negated (high or low
        //   according to the polarity)
        // Sync
        // - Sync with counter 5
        WriteWRODCommand(
            ipuMmioBasePtr,
            1,
            0,
            1,
            DW_GEN_0,
            4,
            DI_COUNTER_5_ACTIVE_CLOCK);

        // MicroCodeAddr
        // - 2 set for new data event
        // Data
        // - Unsused
        // Map to mapping parameter 0
        // - In order to point to MAPPING_PNTR_BYTE2_0, MAPPING_PNTR_BYTE1_0,
        //   MAPPING_PNTR_BYTE0_0 the user should write 1 to the MAPPING field
        // WaveForm
        // - Points to DI0_DW_GEN_0 or DI1_DW_GEN_0 (Define which waveform
        //   register is used, default to first IPUx_DI0_DW_SET0_1)
        // GlueLogic
        // - CS mode No impact on the waveform
        // Sync
        // - Sync with channel 5
        WriteWRODCommand(
            ipuMmioBasePtr,
            2,
            0,
            1,
            DW_GEN_0,
            8,
            DI_COUNTER_5_ACTIVE_CLOCK);
    }

    // Turn on channel without anti tearing
    SetDCChannelState(DIContextPtr->IpuMmioBasePtr, PROG_CHAN_TYP_NORMAL);

    // Register dump, commented out by default
#ifdef REGISTER_DUMP
    DumpBasicDCReg(ipuMmioBasePtr);
#endif

    status = OS_STATUS_SUCCESS;

Exit:
    return status;
}
