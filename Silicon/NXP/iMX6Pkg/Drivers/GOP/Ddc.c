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

#include "Display.h"
#include "Edid.h"
#include "Ddc.h"
#include "Hdmi.h"
#include "Lvds.h"

OS_STATUS IMX6DDCRead (
    DISPLAY_CONTEXT* DisplayContextPtr,
    DISPLAY_INTERFACE DisplayInterface,
    UINT8 SlaveAddress,
    UINT8 RegisterAddress,
    UINT32 ReadSize,
    UINT8* DataReadPtr)
{
    OS_STATUS status;

    switch (DisplayInterface)
    {
    case HDMI_DISPLAY:
        status = HDMIDDCRead(
            &DisplayContextPtr->DIContext[HDMI_DISPLAY],
            SlaveAddress,
            RegisterAddress,
            ReadSize,
            HDMI_DDC_STANDARD_MODE,
            DataReadPtr);
        if (status != OS_STATUS_SUCCESS) {
            OS_ERROR("HDMIDDCRead failed\n");
        }
        break;
    case MIPI_DISPLAY:
    case LVDS0_DISPLAY:
    case LVDS1_DISPLAY:
    default:
        status = OS_STATUS_UNSUPPORTED;
        break;
    }

    return status;
}

