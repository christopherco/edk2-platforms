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

#include <PiDxe.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>

#include <iMXGpio.h>
#include <iMXIoMux.h>

typedef UINT32 IMX_PAD;

//
// Muxing functions
//

VOID
ImxPadConfig (
    IMX_PAD Pad,
    IMX_PADCFG PadConfig
    )
{

}

VOID
ImxPadDumpConfig (
    char *SignalFriendlyName,
    IMX_PAD Pad
    )
{

}

//
// GPIO functions
//

VOID
ImxGpioDirection (
    IMX_GPIO_BANK Bank,
    UINT32 IoNumber,
    IMX_GPIO_DIR Direction
)
{

}

VOID
ImxGpioWrite (
    IMX_GPIO_BANK Bank,
    UINT32 IoNumber,
    IMX_GPIO_VALUE Value
    )
{

}

IMX_GPIO_VALUE
ImxGpioRead (
    IMX_GPIO_BANK Bank,
    UINT32 IoNumber
    )
{
    return IMX_GPIO_HIGH;
}

