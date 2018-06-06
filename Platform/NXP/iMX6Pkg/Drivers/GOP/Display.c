//
// Copyright (C) Microsoft. All rights reserved
// Copyright 2018 NXP
//

#include "Osal.h"

// Display muxing register
#include "iMX6.h"

#include "Display.h"
#include "Edid.h"
#include "Hdmi.h"
#include "Lvds.h"
#include "DisplayInterface.h"
#include "DisplayController.h"
#include "CPMem.h"
#include "Ipu.h"
#include "IoMux.h"

DISPLAY_TIMING DefaultTiming =
{
    65000000,   // PixelClock
    1024,       // HActive
    320,        // HBlank
    768,        // VActive
    38,         // VBlank
    136,        // HSync
    6,          // VSync
    24,         // HSyncOffset;
    3,          // VSyncOffset;
    1024,       // HImageSize
    768,        // VImageSize
    0,          // HBorder
    0,          // VBorder
    0,          // EdidFlags
    0,          // Flags
    1,          // PixelRepetition
    32,          // Bpp
    PIXEL_FORMAT_BGRA32,       // PixelFormat
};

DISPLAY_TIMING Hannstar_XGA =
{
    65000000,   // PixelClock
    1024,       // HActive
    320,        // HBlank
    768,        // VActive
    38,         // VBlank
    60,         // HSync
    10,         // VSync
    24,         // HSyncOffset;
    3,          // VSyncOffset;
    1024,       // HImageSize
    768,        // VImageSize
    0,          // HBorder
    0,          // VBorder
    0,          // EdidFlags
    0,          // Flags
    1,          // PixelRepetition
    32,         // Bpp
    PIXEL_FORMAT_BGRA32,       // PixelFormat
};

OS_STATUS GetPreferedTiming (
    UINT8* EdidDataPtr,
    UINT32 EdidDataSize,
    DISPLAY_TIMING* PreferredTimingPtr
    )
{
    OS_STATUS status;

    if (FeaturePcdGet(PcdLvdsEnable)) {
        *PreferredTimingPtr = Hannstar_XGA;
        status = OS_STATUS_SUCCESS;
    } else {
        status = GetEDIDPreferedTiming(
            EdidDataPtr,
            EdidDataSize,
            PreferredTimingPtr);
        if (status != OS_STATUS_SUCCESS) {
            // If EDID is unavailable use the default timing
            status = OS_STATUS_SUCCESS;
            *PreferredTimingPtr = DefaultTiming;
            OS_WARNING("EDID data not available, falling back to default timing\n");
        }
    }

    // Only support 8 bit per pixel and no pixel pixel repetition for now
    PreferredTimingPtr->PixelRepetition = 1;
    PreferredTimingPtr->PixelFormat = PIXEL_FORMAT_BGRA32;
    PreferredTimingPtr->Bpp = 32;

#ifdef DEBUG
    PrintDisplayTiming(
        "Preferred Timing",
        PreferredTimingPtr);
#endif
    OS_WARNING("--GetPreferedTiming()\r\n");
    return status;
}

OS_STATUS InitDisplay (
    DISPLAY_CONTEXT** DisplayConfigPPtr
    )
{
    OS_STATUS status;
    DISPLAY_INTERFACE displayCounter;
    DISPLAY_CONTEXT* tempDisplayContext;

    status = OS_ALLOC_CONTIGUOUS_MEMORY(
        sizeof(*tempDisplayContext),
        &tempDisplayContext);
    if (status != OS_STATUS_SUCCESS) {
        OS_ERROR("Fail to allocate display context\n");
        goto Exit;
    }

    OS_ZERO_MEM(tempDisplayContext, sizeof(*tempDisplayContext));

    tempDisplayContext->IoMuxMmioBasePtr =
        (VOID*)OS_MMIO_MAP(IOMUXC_GPR_BASE_ADDRESS);
    if (tempDisplayContext->IoMuxMmioBasePtr == NULL) {
        OS_ERROR("Fail to map IO Mux register");
        goto Exit;
    }

    tempDisplayContext->IpuMmioBasePtr[IPU1] =
        (VOID*)OS_MMIO_MAP(IPU1_BASE);
    if (tempDisplayContext->IoMuxMmioBasePtr == NULL) {
        OS_ERROR("Fail to map IPU1 IO Mux register");
        goto Exit;
    }
#if !defined(CPU_IMX6SDL)
    tempDisplayContext->IpuMmioBasePtr[IPU2] =
        (VOID*)OS_MMIO_MAP(IPU2_BASE);
    if (tempDisplayContext->IoMuxMmioBasePtr == NULL) {
        OS_ERROR("Fail to map IPU2 IO Mux register");
        goto Exit;
    }
#endif
    for (displayCounter = HDMI_DISPLAY;
         displayCounter < MAX_DISPLAY;
         ++displayCounter) {
        tempDisplayContext->DIContext[displayCounter].displayInterface =
            displayCounter;
    }

    if (FeaturePcdGet(PcdLvdsEnable)) {
        status = InitLVDS(tempDisplayContext);
        if (status != OS_STATUS_SUCCESS) {
            OS_ERROR("Fail to intialize LVDS\n");
            goto Exit;
        }
    } else {
        status = InitHDMI(tempDisplayContext);
        if (status != OS_STATUS_SUCCESS) {
            OS_ERROR("Fail to intialize HDMI\n");
            goto Exit;
        }
    }

    *DisplayConfigPPtr = tempDisplayContext;

Exit:
    return status;
}


OS_STATUS DeInitDisplay (
    DISPLAY_CONTEXT* DisplayContextPtr
    )
{

    return OS_STATUS_SUCCESS;
}

OS_STATUS ValidateDisplayConfig (
    DISPLAY_CONTEXT* DisplayContextPtr,
    DISPLAY_MODE DisplayMode,
    DISPLAY_INTERFACE* DIOrder
    )
{
    OS_STATUS status;
    DISPLAY_INTERFACE DisplayDevice;

    if (FeaturePcdGet(PcdLvdsEnable)) {
        DisplayDevice = LVDS0_DISPLAY;
    } else {
        DisplayDevice = HDMI_DISPLAY;
    }

    // Currently only support single display mode on HDMI/LVDS
    if (DisplayMode != SINGLE_MODE && DIOrder[0] != DisplayDevice) {
        status = OS_STATUS_UNSUPPORTED;
        goto Exit;
    }

    // Currently going to a very simplistic approach of enabling HDMI/LVDS single
    // display on HDMI/LVDS port. This configuration is applied regardless if
    // there is a monitor connected. No hot plug, monitor detection support.

    status = OS_STATUS_SUCCESS;

Exit:
    return status;
}

OS_STATUS SetDisplayConfig (
    DISPLAY_CONTEXT* DisplayContextPtr,
    DISPLAY_MODE DisplayMode,
    DISPLAY_INTERFACE* DIOrder
    )
{
    OS_STATUS status;
    IPU_INDEX iPUIndex;
    DI_INDEX diIndex;
    UINT32 displayModeIndex;
    UINT32 diOffset[DI_TOTAL] =
        { IPU_DI0_GENERAL_OFFSET, IPU_DI1_GENERAL_OFFSET };

    status = ValidateDisplayConfig(
        DisplayContextPtr,
        DisplayMode,
        DIOrder);
    if (status != OS_STATUS_SUCCESS) {
        DisplayContextPtr->DisplayConfig.DisplayMode = UNKNOWN_MODE;
        OS_ZERO_MEM(
            DisplayContextPtr->DisplayConfig.DIOrder,
            sizeof(DisplayContextPtr->DisplayConfig.DIOrder));
        OS_ERROR("Unsupported display configuration\n");
        status = OS_STATUS_UNSUPPORTED;
        goto Exit;
    }

    DisplayContextPtr->DisplayConfig.DisplayMode = DisplayMode;

    OS_ZERO_MEM(
        DisplayContextPtr->DisplayConfig.DIOrder,
        sizeof(DisplayContextPtr->DisplayConfig.DIOrder));

    // Assigning display interface in order. Require mode information on IPU
    // and DI valid combination
    for (iPUIndex = IPU1, displayModeIndex = 0;
         iPUIndex < IPU_TOTAL && displayModeIndex < (UINT32)DisplayMode;
        ++iPUIndex) {
        for (diIndex = DI0;
            diIndex < DI_TOTAL && displayModeIndex < (UINT32)DisplayMode;
            ++diIndex) {
            DisplayContextPtr->DisplayConfig.DIOrder[diIndex] =
                DIOrder[diIndex];
            DISPLAY_INTERFACE_CONTEXT* diContextPtr =
                &DisplayContextPtr->DIContext[DIOrder[diIndex]];
            diContextPtr->IpuMmioBasePtr =
                DisplayContextPtr->IpuMmioBasePtr[iPUIndex];
            diContextPtr->IpuDiRegsPtr =
                (IPU_DIx_REGS*)(((UINTN)DisplayContextPtr->IpuMmioBasePtr[iPUIndex]) +
                    diOffset[diIndex]);
            diContextPtr->CpMemParamBasePtr = (VOID *)
                (((UINTN)diContextPtr->IpuMmioBasePtr) + CSP_IPUV3_CPMEM_REGS_OFFSET);
            ++displayModeIndex;
        }
    }

    status = OS_STATUS_SUCCESS;

Exit:
    return status;
}

OS_STATUS ApplyDisplayConfig (
    DISPLAY_CONTEXT* DisplayContextPtr,
    DISPLAY_MODE DisplayMode,
    DISPLAY_INTERFACE* DIOrder
    )
{
    DISPLAY_CONFIG* displayConfigPtr = &DisplayContextPtr->DisplayConfig;
    UINT32 displayModeIndex;
    OS_STATUS status;

    status = SetDisplayConfig(
        DisplayContextPtr,
        DisplayMode,
        DIOrder);
    if (status != OS_STATUS_SUCCESS) {
        OS_ERROR("Fail to set display configuration %d\n", DisplayMode);
        status = OS_STATUS_UNSUPPORTED;
        goto Exit;
    }

    // Setup muxing first before configuring DI and DC
    status = SetupDisplayMux(
        DisplayContextPtr);
    if (status != OS_STATUS_SUCCESS) {
        OS_ERROR("SetDisplayMux failed \n");
        goto Exit;
    }

    for (displayModeIndex = 0;
         displayModeIndex < (UINT32)displayConfigPtr->DisplayMode;
         ++displayModeIndex) {
        UINT32 currentDI = displayConfigPtr->DIOrder[displayModeIndex];
        DISPLAY_INTERFACE_CONTEXT* displayInterfaceContextPtr =
            &DisplayContextPtr->DIContext[currentDI];
        DISPLAY_TIMING* currentDisplayTimingPtr =
            &displayConfigPtr->DisplayTiming[displayModeIndex];

        status = ConfigureDCChannel(
            displayInterfaceContextPtr,
            currentDI,
            displayModeIndex,
            currentDisplayTimingPtr);
        if (status != OS_STATUS_SUCCESS) {
            OS_ERROR(
                "ConfigureDCChannel fail display %d index %d\n",
                currentDI,
                displayModeIndex);
            goto Exit;
        }

        status = ConfigureDI(
            displayInterfaceContextPtr,
            displayModeIndex,
            currentDisplayTimingPtr);
        if (status != OS_STATUS_SUCCESS) {
            OS_ERROR("Fail to configure DI\n");
            goto Exit;
        }

        switch (currentDI)
        {
            case HDMI_DISPLAY:
                status = SetHDMIDisplay(
                    displayInterfaceContextPtr,
                    currentDisplayTimingPtr);
                if (status != OS_STATUS_SUCCESS) {
                    OS_ERROR("Fail to set HDMI timing\n");
                    goto Exit;
                }
                break;
            case LVDS0_DISPLAY:
            case LVDS1_DISPLAY:
                break;
            default:
                status = OS_STATUS_UNSUPPORTED;
                goto Exit;
        }

        status = ConfigureFrameBuffer(
            displayInterfaceContextPtr,
            &displayConfigPtr->DisplaySurface[displayModeIndex]);
        if (status != OS_STATUS_SUCCESS) {
            OS_ERROR("Fail to configure frame buffer (%d)\n", displayModeIndex);
            goto Exit;
        }
    }

Exit:
    return status;
}

OS_STATUS AllocateFrameBuffer (
    SURFACE_INFO* SurfaceInfoPtr
    )
{
    OS_STATUS status;
    OS_INFO("++AllocateFrameBuffer()\r\n");
    if((SurfaceInfoPtr->Width == 0) ||
            (SurfaceInfoPtr->Height == 0)) {
        status = OS_STATUS_INVALID_PARAM;
        goto Exit;
    }

    // FIXME: Use a dedicated framebuffer region instead of dynamically allocating from the
    // DXE GCD through UncachedMemoryAllocationLib which seem to crash deep in the
    // stack when trying to allocate a big chunk of memory.
#if 0
    status = OS_ALLOC_CONTIGUOUS_MEMORY(
        SurfaceInfoPtr->Width *
            SurfaceInfoPtr->Height *
            (SurfaceInfoPtr->Bpp / 8),
        &SurfaceInfoPtr->VirtAddrPtr);
    if (status != OS_STATUS_SUCCESS) {
        OS_ERROR("Fail to allocate frame buffer\n");
        goto Exit;
    }

    if (SurfaceInfoPtr->VirtAddrPtr == NULL) {
        status = OS_STATUS_INSUFFICIENT_RESOURCE;
        goto Exit;
    }
#else
    OS_INFO("AllocateFrameBuffer() Frame Buffer AddrP=%Xh\r\n",FixedPcdGet32(PcdFrameBufferBase));
    OS_INFO("AllocateFrameBuffer() Frame Buffer Size=%Xh\r\n",FixedPcdGet32(PcdFrameBufferSize));
    SurfaceInfoPtr->VirtAddrPtr = (VOID*)(UINTN)FixedPcdGet32(PcdFrameBufferBase);
#endif

    SurfaceInfoPtr->PhyAddr =
        (UINT32)OS_VIRT_TO_PHY_ADDR(SurfaceInfoPtr->VirtAddrPtr);
    SurfaceInfoPtr->Pitch = SurfaceInfoPtr->Width;

    OS_INFO(
        "Allocate FB PhyAddr %x VirtAddr %x\n",
        SurfaceInfoPtr->PhyAddr,
        SurfaceInfoPtr->VirtAddrPtr);

    status = OS_STATUS_SUCCESS;

Exit:
    OS_INFO("--AllocateFrameBuffer()=%Xh\r\n",status);
    return status;
}

OS_STATUS ConfigureFrameBuffer (
    DISPLAY_INTERFACE_CONTEXT* DIContextPtr,
    SURFACE_INFO* FrameBufferPtr
    )
{
    OS_STATUS status;

    // Only support single display for now
    status = ConfigureCPMEMFrameBuffer(
        DIContextPtr,
        IDMAC_CHANNEL_DP_PRIMARY_FLOW_MAIN_PLANE,
        FrameBufferPtr);
    if (status != OS_STATUS_SUCCESS) {
        OS_ERROR("Fail to configure CPMEM\n");
        goto Exit;
    }

Exit:
    return status;
}

UINT32 GetColorDepth (
    PIXEL_FORMAT PixelFormat
    )
{
    UINT32 bitDepth;

    switch(PixelFormat)
    {
        case PIXEL_FORMAT_ARGB32:
        case PIXEL_FORMAT_BGRA32:
            bitDepth = 8;
            break;
        default:
            bitDepth = 0;
    }

    return bitDepth;
}