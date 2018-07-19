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

#ifndef _EDID_H_
#define _EDID_H_

OS_STATUS ReadEDID (
    DISPLAY_CONTEXT* DisplayContextPtr,
    DISPLAY_INTERFACE DisplayInterface,
    UINT8* EdidDataPtr,
    UINT32* EdidDataSizePtr
    );

OS_STATUS GetEDIDPreferedTiming (
    UINT8* EdidDataPtr,
    UINT32 EdidDataSizePtr,
    DISPLAY_TIMING* PreferedTiming
    );

#endif
