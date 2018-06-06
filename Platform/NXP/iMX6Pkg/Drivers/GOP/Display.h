//
// Copyright (C) Microsoft. All rights reserved
// Copyright 2018 NXP
//

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

typedef enum {
   UNKNOWN_MODE,
   SINGLE_MODE,
   DUAL_MODE,
} DISPLAY_MODE;

typedef enum {
    IPU1,
#if !defined(CPU_IMX6SDL)
    IPU2,
#endif
    IPU_TOTAL,
} IPU_INDEX;

typedef enum {
    DI0,
    DI1,
    DI_TOTAL,
} DI_INDEX;

typedef enum {
    HDMI_DISPLAY,
    MIPI_DISPLAY,
    LVDS0_DISPLAY,
    LVDS1_DISPLAY,
    MAX_DISPLAY, // Only 4 display supported by IPU
    NO_DISPLAY = MAX_DISPLAY,
} DISPLAY_INTERFACE;

typedef struct _SURFACE_INFO {
    UINT32 PhyAddr;
    UINT32* VirtAddrPtr;
    UINT32 Width;
    UINT32 Height;
    UINT32 Pitch;
    UINT32 Bpp;
    PIXEL_FORMAT PixelFormat;
}SURFACE_INFO, *PSURFACE_INFO;

typedef struct _IPU_DIx_REGS {
    UINT32 DIxGENERAL;
    UINT32 DIxBS_CLKGEN0;
    UINT32 DIxBS_CLKGEN1;
    UINT32 DIxSW_GEN0_1;
    UINT32 DIxSW_GEN0_2;
    UINT32 DIxSW_GEN0_3;
    UINT32 DIxSW_GEN0_4;
    UINT32 DIxSW_GEN0_5;
    UINT32 DIxSW_GEN0_6;
    UINT32 DIxSW_GEN0_7;
    UINT32 DIxSW_GEN0_8;
    UINT32 DIxSW_GEN0_9;
    UINT32 DIxSW_GEN1_1;
    UINT32 DIxSW_GEN1_2;
    UINT32 DIxSW_GEN1_3;
    UINT32 DIxSW_GEN1_4;
    UINT32 DIxSW_GEN1_5;
    UINT32 DIxSW_GEN1_6;
    UINT32 DIxSW_GEN1_7;
    UINT32 DIxSW_GEN1_8;
    UINT32 DIxSW_GEN1_9;
    UINT32 DIxSYNC_AS_GEN;
    UINT32 DIxDW_GEN[12];
    UINT32 DIxDW_SET0[12];
    UINT32 DIxDW_SET1[12];
    UINT32 DIxDW_SET2[12];
    UINT32 DIxDW_SET3[12];
    UINT32 DIxSTP_REP[4];
    UINT32 DIxSTP_REP_9;
    UINT32 DIxSER_CONF;
    UINT32 DIxSSC;
    UINT32 DIxPOL;
    UINT32 DIxAW0;
    UINT32 DIxAW1;
    UINT32 DIxSCR_CONF;
    UINT32 DIxSTAT;
} IPU_DIx_REGS, *PIPU_DIx_REGS;

typedef struct _DISPLAY_INTERFACE_CONTEXT {
    DISPLAY_INTERFACE displayInterface;

    VOID* MmioBasePtr;
    VOID* IpuMmioBasePtr;
    VOID* CpMemParamBasePtr;
    IPU_DIx_REGS* IpuDiRegsPtr;
    
    UINT32 EdidDataSize;
    UINT8 EdidData[256];
    DISPLAY_TIMING PreferedTiming;
}DISPLAY_INTERFACE_CONTEXT, *PDISPLAY_INTERFACE_CONTEXT;

typedef struct _DISPLAY_CONFIG {
    DISPLAY_MODE DisplayMode;
    DISPLAY_INTERFACE DIOrder[MAX_DISPLAY];
    SURFACE_INFO DisplaySurface[MAX_DISPLAY];
    DISPLAY_TIMING DisplayTiming[MAX_DISPLAY];
    UINT32 OsHandle[MAX_DISPLAY];
}DISPLAY_CONFIG, *PDISPLAY_CONFIG;

typedef struct _DISPLAY_CONTEXT {

    //
    // Display configuration
    //
    DISPLAY_CONFIG DisplayConfig;

    //
    // Register
    //
    VOID* IoMuxMmioBasePtr;
    VOID* IpuMmioBasePtr[IPU_TOTAL];

    //
    // Display specific context
    DISPLAY_INTERFACE_CONTEXT DIContext[MAX_DISPLAY];
}DISPLAY_CONTEXT, *PDISPLAY_CONTEXT;

extern DISPLAY_TIMING DefaultTiming;

OS_STATUS GetPreferedTiming (
    UINT8* EdidDataPtr,
    UINT32 EdidDataSize,
    DISPLAY_TIMING* PreferedTimingPtr
    );

OS_STATUS InitDisplay (
    DISPLAY_CONTEXT** DisplayConfigPPtr
    );

OS_STATUS DeInitDisplay (
    DISPLAY_CONTEXT* DisplayContextPtr
    );

OS_STATUS ValidateDisplayConfig (
    DISPLAY_CONTEXT* DisplayContextPtr,
    DISPLAY_MODE DisplayMode,
    DISPLAY_INTERFACE* DIOrder
    );

OS_STATUS SetDisplayConfig (
    DISPLAY_CONTEXT* DisplayContextPtr,
    DISPLAY_MODE DisplayMode,
    DISPLAY_INTERFACE* DIOrder
    );

OS_STATUS ApplyDisplayConfig (
    DISPLAY_CONTEXT* DisplayContextPtr,
    DISPLAY_MODE DisplayMode,
    DISPLAY_INTERFACE* DIOrder
    );

OS_STATUS AllocateFrameBuffer (
    SURFACE_INFO* SurfaceInfoPtr
    );

OS_STATUS ConfigureFrameBuffer (
    DISPLAY_INTERFACE_CONTEXT* DIContextPtr,
    SURFACE_INFO* FrameBufferPtr
    );

UINT32 GetColorDepth (
    PIXEL_FORMAT PixelFormat
    );

#endif

