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
#include "CPMem.h"
#include "Ipu.h"

CPMEM_PARAM* CpMemParamBasePtr = (CPMEM_PARAM*)(IPU1_BASE + CSP_IPUV3_CPMEM_REGS_OFFSET);

VOID DumpCPMEMParamPack (CPMEM_PARAM* ParamPtr)
{
    OS_INFO("--WORD0--\n");
    OS_INFO("XVVirtualCoordinate 0x%08x\n", ParamPtr->Word0Pack.XVVirtualCoordinate);
    OS_INFO("YVVirtualCoordinate 0x%08x\n", ParamPtr->Word0Pack.YVVirtualCoordinate);
    OS_INFO("XBinnerBlockCoordinate 0x%08x\n", ParamPtr->Word0Pack.XBinnerBlockCoordinate);
    OS_INFO("YBinnerBlockCoordinate 0x%08x\n", ParamPtr->Word0Pack.YBinnerBlockCoordinate);
    OS_INFO("NewSubBlock 0x%08x\n", ParamPtr->Word0Pack.NewSubBlock);
    OS_INFO("CurrentField 0x%08x\n", ParamPtr->Word0Pack.CurrentField);
    OS_INFO("ScrollXCounter 0x%08x\n", ParamPtr->Word0Pack.ScrollXCounter);
    OS_INFO("ScrollYCounter 0x%08x\n", ParamPtr->Word0Pack.ScrollYCounter);
    OS_INFO("NumberOfScroll 0x%08x\n", ParamPtr->Word0Pack.NumberOfScroll);
    OS_INFO("ScrollDeltaX 0x%08x\n", ParamPtr->Word0Pack.ScrollDeltaX);
    OS_INFO("ScrollMax 0x%08x\n", ParamPtr->Word0Pack.ScrollMax);
    OS_INFO("ScrollingConfiguration 0x%08x\n", ParamPtr->Word0Pack.ScrollingConfiguration);
    OS_INFO("ScrollingEnable 0x%08x\n", ParamPtr->Word0Pack.ScrollingEnable);
    OS_INFO("ScrollDeltaY 0x%08x\n", ParamPtr->Word0Pack.ScrollDeltaY);
    OS_INFO("ScrollHorizontalDirection 0x%08x\n", ParamPtr->Word0Pack.ScrollHorizontalDirection);
    OS_INFO("ScrollVerticalDirection 0x%08x\n", ParamPtr->Word0Pack.ScrollVerticalDirection);
    OS_INFO("BitsPerPixel 0x%08x\n", ParamPtr->Word0Pack.BitsPerPixel);
    OS_INFO("DecodeAddressSelect 0x%08x\n", ParamPtr->Word0Pack.DecodeAddressSelect);
    OS_INFO("AccessDimension 0x%08x\n", ParamPtr->Word0Pack.AccessDimension);
    OS_INFO("ScanOrder 0x%08x\n", ParamPtr->Word0Pack.ScanOrder);
    OS_INFO("BandMode 0x%08x\n", ParamPtr->Word0Pack.BandMode);
    OS_INFO("BlockMode 0x%08x\n", ParamPtr->Word0Pack.BlockMode);
    OS_INFO("Rotation 0x%08x\n", ParamPtr->Word0Pack.Rotation);
    OS_INFO("HorizontalFlip 0x%08x\n", ParamPtr->Word0Pack.HorizontalFlip);
    OS_INFO("VerticalFlip 0x%08x\n", ParamPtr->Word0Pack.VerticalFlip);
    OS_INFO("ThresholdEnable 0x%08x\n", ParamPtr->Word0Pack.ThresholdEnable);
    OS_INFO("ConditionalAccessPolarity 0x%08x\n", ParamPtr->Word0Pack.ConditionalAccessPolarity);
    OS_INFO("ConditionalAccessEnable 0x%08x\n", ParamPtr->Word0Pack.ConditionalAccessEnable);
    OS_INFO("FrameWidth 0x%08x\n", ParamPtr->Word0Pack.FrameWidth);
    OS_INFO("FrameHeight 0x%08x\n", ParamPtr->Word0Pack.FrameHeight);
    OS_INFO("EndOfLineInterrupt 0x%08x\n", ParamPtr->Word0Pack.EndOfLineInterrupt);

    OS_INFO("--WORD1--\n");
    OS_INFO("ExtMemBuffer0Address 0x%08x\n", ParamPtr->Word1Pack.ExtMemBuffer0Address);
    OS_INFO("ExtMemBuffer1Address 0x%08x\n", ParamPtr->Word1Pack.ExtMemBuffer1Address);
    OS_INFO("InterlaceOffset 0x%08x\n", ParamPtr->Word1Pack.InterlaceOffset);
    OS_INFO("NumberOfPixelsInWholeBurstAccess 0x%08x\n", ParamPtr->Word1Pack.NumberOfPixelsInWholeBurstAccess);
    OS_INFO("PixelFormatSelect 0x%08x\n", ParamPtr->Word1Pack.PixelFormatSelect);
    OS_INFO("AlphaUsed 0x%08x\n", ParamPtr->Word1Pack.AlphaUsed);
    OS_INFO("AlphaChannelMapping 0x%08x\n", ParamPtr->Word1Pack.AlphaChannelMapping);
    OS_INFO("AxiId 0x%08x\n", ParamPtr->Word1Pack.AxiId);
    OS_INFO("Threshold 0x%08x\n", ParamPtr->Word1Pack.Threshold);
    OS_INFO("StrideLine 0x%08x\n", ParamPtr->Word1Pack.StrideLine);
    OS_INFO("Width0 0x%08x\n", ParamPtr->Word1Pack.Width0);
    OS_INFO("Width1 0x%08x\n", ParamPtr->Word1Pack.Width1);
    OS_INFO("Width2 0x%08x\n", ParamPtr->Word1Pack.Width2);
    OS_INFO("Width3 0x%08x\n", ParamPtr->Word1Pack.Width3);
    OS_INFO("Offset0 0x%08x\n", ParamPtr->Word1Pack.Offset0);
    OS_INFO("Offset1 0x%08x\n", ParamPtr->Word1Pack.Offset1);
    OS_INFO("Offset2 0x%08x\n", ParamPtr->Word1Pack.Offset2);
    OS_INFO("Offset3 0x%08x\n", ParamPtr->Word1Pack.Offset3);
    OS_INFO("SelectSXSYSet 0x%08x\n", ParamPtr->Word1Pack.SelectSXSYSet);
    OS_INFO("ConditionalReadEnable 0x%08x\n", ParamPtr->Word1Pack.ConditionalReadEnable);
}

VOID DumpBasicCPMEMReg (
    CPMEM_PARAM* CpmemChannel)
{
    OS_INFO("---------- CPMEM Register Dump ----------\n");
    OS_INFO("CPMEM\n");
    OS_INFO("IDMAC_CHANNEL_DP_PRIMARY_FLOW_MAIN_PLANE\n");
    DumpCPMEMParamPack(CpmemChannel);
    OS_INFO("------------------------------------\n");
}

//
// Enable IDMAC lock setting, which optimises memory accesses and reduces
// power consumption
//
VOID SetIdmacLockEn(
    DISPLAY_INTERFACE_CONTEXT* DIContextPtr,
    UINT32 Channel,
    UINT32 Setting
    )
{
    static const UINT8 channelMap[] = {
        5, 0,
        11, 2,
        12, 4,
        14, 6,
        15, 8,
        20, 10,
        21, 12,
        22, 14,
        23, 16,
        27, 18,
        28, 20,
        45, 0,
        46, 2,
        47, 4,
        48, 6,
        49, 8,
        50, 10,
    };

    UINTN lockReg;
    UINT32 value;
    int shift = -1;
    int i;

    for (i = 0; i < (sizeof(channelMap) / sizeof(channelMap[0])); i += 2) {
        if (channelMap[i] == Channel) {
            shift = channelMap[i + 1];
            break;
        }
    }

    if (shift == -1) {
        OS_WARNING("Channel %d does not have lock bits", Channel);
        return;
    }

    if (Channel < 29) {
        lockReg = (UINTN)DIContextPtr->IpuMmioBasePtr + IPU_IDMAC_LOCK_EN_1;
    } else {
        lockReg = (UINTN)DIContextPtr->IpuMmioBasePtr + IPU_IDMAC_LOCK_EN_2;
    }

    value = OS_READ32(lockReg);
    value &= ~(0x3 << shift);
    value |= (Setting & 0x3) << shift;
    OS_WRITE32(lockReg, value);
}

OS_STATUS ConfigureCPMEMFrameBuffer (
    DISPLAY_INTERFACE_CONTEXT* DIContextPtr,
    UINT32 Channel,
    SURFACE_INFO* FrameBufferPtr)
{
    OS_STATUS status;
    CPMEM_WORD0_PACKED_REG cpmemWord0PackedReg;
    CPMEM_WORD1_PACKED_REG cpmemWord1PackedReg;
    CPMEM_DEC_SEL decodeAddressSelect = CPMEM_DEC_SEL_0_15; // Only applicable for 4 bpp
    UINT32 pixelBurst = 1;
    CPMEM_PFS_PACKED pixelFormatSelector;
    UINT32 width0, width1, width2, width3;
    UINT32 offset0, offset1, offset2, offset3;
    UINT32 bytesPerPixel;
    CPMEM_PARAM* cpmemChannel = DIContextPtr->CpMemParamBasePtr;

    OS_ZERO_MEM(&cpmemWord0PackedReg, sizeof(cpmemWord0PackedReg));
    OS_ZERO_MEM(&cpmemWord1PackedReg, sizeof(cpmemWord1PackedReg));

    switch (FrameBufferPtr->PixelFormat)
    {
    case PIXEL_FORMAT_BGRA32:
        pixelBurst = 15; // 16 Pixel. Valid range is 1 - 64 pixel
        pixelFormatSelector = CPMEM_PFS_RGB;
        offset0 = 8;
        offset1 = 16;
        offset2 = 24;
        offset3 = 0;
        bytesPerPixel = 4;
        break;
    default:
        ASSERT(FALSE);
        status = OS_STATUS_UNSUPPORTED;
        goto Exit;
    }

    switch (FrameBufferPtr->Bpp)
    {
    case 8:
        width0 = width1 = width2 = width3 = 0;
        break;
    case 32:
        if (pixelFormatSelector == CPMEM_PFS_RGB) {
            width0 = width1 = width2 = width3 = 7;
        } else {
            width0 = width1 = width2 = width3 = 0;
        }
        break;
    default:
        ASSERT(FALSE);
        status = OS_STATUS_UNSUPPORTED;
        goto Exit;
    }

    // Setting up CPMEM word 0
    // Is this coordinate top-left or bottom-right? Either way both virtual
    // and block would be { 0, 0 }.
    cpmemWord0PackedReg.XVVirtualCoordinate = 0;
    cpmemWord0PackedReg.YVVirtualCoordinate = 0;

    // Subblock is unused although expect to have some value after write
    cpmemWord0PackedReg.XBinnerBlockCoordinate = 0;
    cpmemWord0PackedReg.YBinnerBlockCoordinate = 0;
    cpmemWord0PackedReg.NewSubBlock = 0;

    // Verify "current field" definition
    cpmemWord0PackedReg.CurrentField = 0;

    // Disable scrolling
    cpmemWord0PackedReg.ScrollXCounter= 0;
    cpmemWord0PackedReg.ScrollYCounter = 0;
    cpmemWord0PackedReg.NumberOfScroll = 0;
    cpmemWord0PackedReg.ScrollDeltaX = 0;
    cpmemWord0PackedReg.ScrollMax = 0;
    cpmemWord0PackedReg.ScrollingConfiguration = 0;
    cpmemWord0PackedReg.ScrollingEnable = 0;
    cpmemWord0PackedReg.ScrollDeltaY = 0;
    cpmemWord0PackedReg.ScrollHorizontalDirection = 0;
    cpmemWord0PackedReg.ScrollVerticalDirection = 0;

    // Bits per pixel
    cpmemWord0PackedReg.BitsPerPixel = FrameBufferPtr->Bpp;

    // Decode Address Select
    cpmemWord0PackedReg.DecodeAddressSelect = decodeAddressSelect;

    // Scan order is progressive no support for interlace mode
    cpmemWord0PackedReg.ScanOrder = CPMEM_SO_PROGRESSIVE;

    // Band mode is sub frame double buffering
    cpmemWord0PackedReg.BandMode = CPMEM_BNDM_DISABLE;

    // Block mode used for post filtering and rotation
    cpmemWord0PackedReg.BlockMode = CPMEM_BM_DISABLE;

    // No support for rotation and flipping for now
    cpmemWord0PackedReg.Rotation = CPMEM_ROT_NO_ROTATION;
    cpmemWord0PackedReg.HorizontalFlip = CPMEM_HF_NO_HFLIP;
    cpmemWord0PackedReg.VerticalFlip = CPMEM_HF_NO_VFLIP;
    cpmemWord0PackedReg.ThresholdEnable = CPMEM_THE_DISABLE;

    // Disable conditional access
    cpmemWord0PackedReg.ConditionalAccessEnable = CPMEM_CAP_SKIP_LOW;
    cpmemWord0PackedReg.ConditionalAccessPolarity = CPMEM_CAE_DISABLE;

    // Frame width and height, minus one as 0 == 1 pixel
    cpmemWord0PackedReg.FrameWidth = FrameBufferPtr->Width - 1;
    cpmemWord0PackedReg.FrameHeight = FrameBufferPtr->Height - 1;

    // No interrupt required at the end of line
    cpmemWord0PackedReg.EndOfLineInterrupt = CPMEM_EOLI_DISABLE;

    // Setting up CPMEM word 1
    // Buffer 0, use the [31:3] bit address
    cpmemWord1PackedReg.ExtMemBuffer0Address = FrameBufferPtr->PhyAddr >> 3;

    // Buffer 1, use the same buffer for now
    cpmemWord1PackedReg.ExtMemBuffer1Address = FrameBufferPtr->PhyAddr >> 3;

    // Currently do not support interlace mode
    cpmemWord1PackedReg.InterlaceOffset = 0;

    // Pixel format and burst
    cpmemWord1PackedReg.NumberOfPixelsInWholeBurstAccess = pixelBurst;
    cpmemWord1PackedReg.PixelFormatSelect = pixelFormatSelector;

    // Alpha config
    cpmemWord1PackedReg.AlphaUsed = CPMEM_ALU_SAME_BUFFER;
    // cpmemWord1PackedReg.AlphaChannelMapping = ???;

    // TODO determine correct AXI id
    cpmemWord1PackedReg.AxiId = CPMEM_ID_ID_0;

    cpmemWord1PackedReg.Threshold = CPMEM_THE_DISABLE;

    // Stride, width and offset
    cpmemWord1PackedReg.StrideLine =
        (FrameBufferPtr->Pitch * bytesPerPixel) - 1;
    cpmemWord1PackedReg.Width0 = width0;
    cpmemWord1PackedReg.Width1 = width1;
    cpmemWord1PackedReg.Width2 = width2;
    cpmemWord1PackedReg.Width3 = width3;
    cpmemWord1PackedReg.Offset0 = offset0;
    cpmemWord1PackedReg.Offset1 = offset1;
    cpmemWord1PackedReg.Offset2 = offset2;
    cpmemWord1PackedReg.Offset3 = offset3;

    // SX SY is ignored since scrolling is disabled
    cpmemWord1PackedReg.SelectSXSYSet = 0;

    // Conditional read is always enabled so fully transperant pixel are
    // not read.
    cpmemWord1PackedReg.ConditionalReadEnable = CPMEM_CRE_ENABLE;

    // Finallu write into cpmem IDMAC channel
    cpmemChannel = (cpmemChannel + Channel);

    OS_MEM_COPY(
        &cpmemChannel->Word0Pack,
        &cpmemWord0PackedReg,
        sizeof(cpmemChannel->Word0Pack));

    OS_MEM_COPY(
        &cpmemChannel->Word1Pack,
        &cpmemWord1PackedReg,
        sizeof(cpmemChannel->Word1Pack));

    // IDMAC will generate 8 AXI bursts upon assertion of the DMA request
    // This significantly reduces memory activity and power consumption
    SetIdmacLockEn(DIContextPtr, Channel, 0x3);

    // Register dump, commented out by default
#ifdef REGISTER_DUMP
    DumpBasicCPMEMReg(cpmemChannel);
#endif

    status = OS_STATUS_SUCCESS;

Exit:
    return status;
}
