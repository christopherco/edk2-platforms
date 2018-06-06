/*
** ##############################################################################
**
** Copyright 2018 NXP
** NXP Confidential and Proprietary
** Your rights to use this software are contained in the license that accompanies this software.
**
** ##############################################################################
*/

#include "Osal.h"

#include "Display.h"
#include "Lvds.h"
#include "Edid.h"


OS_STATUS InitLVDS (
    DISPLAY_CONTEXT* DisplayContextPtr
    )
{
    DISPLAY_INTERFACE_CONTEXT* LvdsDisplayContextPtr = &DisplayContextPtr->DIContext[LVDS0_DISPLAY];
    OS_STATUS status = 0;

    OS_ZERO_MEM(LvdsDisplayContextPtr, sizeof(*LvdsDisplayContextPtr));

    LvdsDisplayContextPtr->MmioBasePtr = (VOID*)OS_MMIO_MAP(LDB_BASE);
    if (LvdsDisplayContextPtr->MmioBasePtr == NULL) {
        OS_ERROR("Fail to map LDB register\n");
        goto Exit;
    }


    // LVDS CH1 enabled, routed to DI0; ipu_di01_vsync_active_low
    {


        LDB_CTRL_REG LdbCtrlReg;
        LdbCtrlReg.Reg = LVDSRead32(LDB_CTRL);
        LdbCtrlReg.ch0_mode = 1;
        LdbCtrlReg.ch1_mode = 1;
        LdbCtrlReg.di0_vs_polarity = 1;
        LdbCtrlReg.di1_vs_polarity = 1;
        LVDSWrite32(LDB_CTRL, LdbCtrlReg.Reg);
    }

    // No EDID available
    LvdsDisplayContextPtr->EdidDataSize = 0;

    status = GetPreferedTiming(
        LvdsDisplayContextPtr->EdidData,
        LvdsDisplayContextPtr->EdidDataSize,
        &LvdsDisplayContextPtr->PreferedTiming);
    if (status != OS_STATUS_SUCCESS) {
        OS_ERROR("Fail to retrieve LVDS prefered timing\n");
        goto Exit;
    }

Exit:
    return status;
}

OS_STATUS SetLVDSPower (
    DISPLAY_INTERFACE_CONTEXT* HdmiDisplayContextPtr,
    BOOLEAN PowerState
    )
{
    return OS_STATUS_UNSUPPORTED;
}

OS_STATUS SetLVDSDisplay (
    DISPLAY_INTERFACE_CONTEXT* LvdsDisplayContextPtr,
    DISPLAY_TIMING* Timings
    )
{
    return OS_STATUS_UNSUPPORTED;
}


