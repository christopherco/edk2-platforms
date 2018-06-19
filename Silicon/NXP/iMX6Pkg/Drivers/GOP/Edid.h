//
// Copyright (C) Microsoft. All rights reserved
//

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