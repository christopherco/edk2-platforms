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
#include <iMXDisplay.h>
#include "Display.h"
#include "Edid.h"
#include "Ddc.h"

OS_STATUS ReadEDID (
    DISPLAY_CONTEXT* DisplayContextPtr,
    DISPLAY_INTERFACE DisplayInterface,
    UINT8* EdidDataPtr,
    UINT32* EdidDataSizePtr)
{
    OS_STATUS status;

    status = IMX6DDCRead(
        DisplayContextPtr,
        DisplayInterface,
        EDID_I2C_ADDRESS,
        0,
        EDID_MIN_SIZE,
        EdidDataPtr);
    if (status != OS_STATUS_SUCCESS) {
        goto Exit;
    }

    status = ValidateEdidData(
        EdidDataPtr);
    if (status != OS_STATUS_SUCCESS) {
        OS_WARNING("Invalid EDID data\n");
        goto Exit;
    }

    OS_INFO("EDID initialized\n");

    *EdidDataSizePtr = EDID_MIN_SIZE;

Exit:
    return status;
}

OS_STATUS GetEDIDPreferedTiming (
    UINT8* EdidDataPtr,
    UINT32 EdidDataSizePtr,
    DISPLAY_TIMING* PreferedTiming
)
{
    OS_STATUS status;
    DETAILED_TIMING_DESCRIPTOR* edidPreferedtiming;

    if (EdidDataSizePtr < EDID_MIN_SIZE) {
        OS_WARNING("Insufficient EDID data\n");
        status = OS_STATUS_INVALID_PARAM;
        goto Exit;
    }

    edidPreferedtiming =
        (DETAILED_TIMING_DESCRIPTOR*)&EdidDataPtr[EDID_DTD_1_OFFSET];

    status = ConvertDTDToDisplayTiming(edidPreferedtiming, PreferedTiming);
    if (status != OS_STATUS_SUCCESS) {
        OS_ERROR("Conversion to display timing failed\n");
        goto Exit;
    }

Exit:

    return status;
}
