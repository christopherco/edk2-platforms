//
// Copyright (C) Microsoft. All rights reserved
//

#ifndef _IO_MUX_H_
#define _IO_MUX_H_

#define HDMI_MUX_CTL_OFFSET         2
#define HDMI_MUX_CTL_MASK           0x000C
#define MIPI_MUX_CTL_OFFSET         4
#define MIPI_MUX_CTL_MASK           0x0030
#define LVDS0_MUX_CTL_OFFSET        6
#define LVDS0_MUX_CTL_MASK          0x00C0
#define LVDS1_MUX_CTL_OFFSET        8
#define LVDS1_MUX_CTL_MASK          0x0300

OS_STATUS SetupDisplayMux (
    DISPLAY_CONTEXT* DisplayContextPtr
    );

#endif
