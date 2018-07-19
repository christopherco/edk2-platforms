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

#include "Osal.h"
#include "Display.h"
#include "IoMux.h"

OS_STATUS SetupDisplayMux (
    DISPLAY_CONTEXT* DisplayContextPtr
    )
{
    OS_STATUS status;
    DISPLAY_MODE displayMode = DisplayContextPtr->DisplayConfig.DisplayMode;
    DISPLAY_INTERFACE* displayInterface =
        DisplayContextPtr->DisplayConfig.DIOrder;
    UINT32 regGPR3, sourceMask, sourceVal, dIIndex;
    volatile IMX_IOMUXC_GPR_REGISTERS* ioMuxcGprRegisters =
        DisplayContextPtr->IoMuxMmioBasePtr;

    regGPR3 =
        OS_READ32(&ioMuxcGprRegisters->GPR3);

    regGPR3 &= ~(HDMI_MUX_CTL_MASK |
                 MIPI_MUX_CTL_MASK |
                 LVDS0_MUX_CTL_MASK |
                 LVDS1_MUX_CTL_MASK);

    OS_WRITE32(
        &ioMuxcGprRegisters->GPR3,
        regGPR3);

    for (dIIndex = 0; dIIndex < (UINT32)displayMode; ++dIIndex) {
        regGPR3 =
            OS_READ32(&ioMuxcGprRegisters->GPR3);

        switch (displayInterface[dIIndex])
        {
        case HDMI_DISPLAY:
            sourceMask = HDMI_MUX_CTL_MASK;
            sourceVal = dIIndex << HDMI_MUX_CTL_OFFSET;
            break;
        case MIPI_DISPLAY:
            sourceMask = MIPI_MUX_CTL_MASK;
            sourceVal = dIIndex << MIPI_MUX_CTL_OFFSET;
            break;
        case LVDS0_DISPLAY:
            sourceMask = LVDS0_MUX_CTL_MASK;
            sourceVal = dIIndex << LVDS0_MUX_CTL_OFFSET;
            break;
        case LVDS1_DISPLAY:
            sourceMask = LVDS1_MUX_CTL_MASK;
            sourceVal = dIIndex << LVDS1_MUX_CTL_OFFSET;
            break;
        default:
            status = OS_STATUS_UNSUPPORTED;
            goto Exit;
        }

        regGPR3 &= ~sourceMask;
        regGPR3 |= sourceVal;

        OS_WRITE32(
            &ioMuxcGprRegisters->GPR3,
            regGPR3);
    }

    status = OS_STATUS_SUCCESS;

Exit:
    return status;
}
