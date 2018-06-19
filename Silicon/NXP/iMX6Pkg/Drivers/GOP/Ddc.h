//
// Copyright (C) Microsoft. All rights reserved
//

#ifndef _DDC_H_
#define _DDC_H_

OS_STATUS IMX6DDCRead (
    DISPLAY_CONTEXT* DisplayContextPtr,
    DISPLAY_INTERFACE DisplayInterface,
    UINT8 SlaveAddress,
    UINT8 RegisterAddress,
    UINT32 ReadSize,
    UINT8* DataReadPtr
    );

#endif
