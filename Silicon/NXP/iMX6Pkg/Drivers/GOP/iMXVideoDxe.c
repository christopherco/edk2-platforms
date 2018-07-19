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

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/UefiBootServicesTableLib.h>

#include <Protocol/EmbeddedExternalDevice.h>
#include <Protocol/BlockIo.h>
#include <Protocol/Cpu.h>
#include <Protocol/DevicePath.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/EdidDiscovered.h>
#include <Protocol/EdidActive.h>

#include "Osal.h"
#include "Display.h"
#include "Hdmi.h"
#include "Lvds.h"

#define PIXEL_BYTES 4

typedef struct {
    VENDOR_DEVICE_PATH Mmc;
    EFI_DEVICE_PATH End;
} VID_DEVICE_PATH;

DISPLAY_TIMING const FullHDTiming =
{
    148500000,  // Full 1080p HD PixelClock
    1920,       // HActive
    280,        // HBlank
    1080,       // VActive
    45,         // VBlank
    44,         // HSync
    5,          // VSync
    88,         // HSyncOffset;
    4,          // VSyncOffset;
    1920,       // HImageSize
    1080,       // VImageSize
    0,          // HBorder
    0,          // VBorder
    30,         // EdidFlags
    0,          // Flags
    1,          // PixelRepetition
    32,         // Bpp
    PIXEL_FORMAT_BGRA32,       // PixelFormat
};

EFI_STATUS
EFIAPI
VidGopQueryMode(
    IN EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
    IN UINT32 ModeNumber,
    OUT UINTN *SizeOfInfo,
    OUT EFI_GRAPHICS_OUTPUT_MODE_INFORMATION **Info
    );

EFI_STATUS
VidGopSetMode(
    IN EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
    IN UINT32 ModeNumber
    );

EFI_STATUS
VidGopBlt(
    IN EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
    IN OUT EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltBuffer,
    IN EFI_GRAPHICS_OUTPUT_BLT_OPERATION BltOperation,
    IN UINTN SourceX,
    IN UINTN SourceY,
    IN UINTN DestinationX,
    IN UINTN DestinationY,
    IN UINTN Width,
    IN UINTN Height,
    IN UINTN Delta
    );

//--------------------------------------------------------------------- Globals.

static VID_DEVICE_PATH g_VidDevicePath =
{
    {
        {
            HARDWARE_DEVICE_PATH,
            HW_VENDOR_DP,
            {
                (UINT8)sizeof(VENDOR_DEVICE_PATH),
                (UINT8)((sizeof(VENDOR_DEVICE_PATH)) >> 8),
            }
        },
        {
            0xa6b94ebe,
            0x5ba3,
            0x44b0,
            { 0x95, 0x92, 0xdc, 0x04, 0x5e, 0xb8, 0xf8, 0x9e }
        }
    },
    {
        END_DEVICE_PATH_TYPE,
        END_ENTIRE_DEVICE_PATH_SUBTYPE,
        {
            sizeof(EFI_DEVICE_PATH_PROTOCOL),
            0
        }
    }
};

static EFI_GRAPHICS_OUTPUT_MODE_INFORMATION g_VidGopModeInfo;
static EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE g_VidGopMode;

static EFI_GRAPHICS_OUTPUT_PROTOCOL g_VidGop =
{
    VidGopQueryMode, // QueryMode
    VidGopSetMode,   // SetMode
    VidGopBlt,       // Blt
    &g_VidGopMode    // Mode
};

EFI_EDID_DISCOVERED_PROTOCOL g_EdidDiscovered = {
    0,
    NULL
};

EFI_EDID_ACTIVE_PROTOCOL g_EdidActive = {
    0,
    NULL
};

DISPLAY_CONTEXT* DisplayContextPtr;

DISPLAY_INTERFACE DisplayDevice;

EFI_STATUS
VideoiMX6DxeInitialize (
    IN EFI_HANDLE       ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
  )
{
    EFI_STATUS status;
    UINT32 ReservedDisplayMemorySize;
    UINT32 RequestedDisplayMemorySize;
    DEBUG((DEBUG_INFO,"++VideoiMX6DxeInitialize()\r\n"));

       ReservedDisplayMemorySize = FixedPcdGet32(PcdFrameBufferSize);

    if (FeaturePcdGet(PcdLvdsEnable)) {
        DisplayDevice = LVDS0_DISPLAY;
    } else {
        DisplayDevice = HDMI_DISPLAY;
    }

    status = InitDisplay(&DisplayContextPtr);
    if (EFI_ERROR(status)) {
        DEBUG(
            (DEBUG_ERROR,
            "VideoiMX6DxeInitialize: Fail to init display, status=%r\n",
            status));
        goto Exit;
    }

    DEBUG((DEBUG_INFO,"VideoiMX6DxeInitialize - Allocate frame buffer\r\n"));
    // To allocate frame buffer dynamically, there isn`t a built in graphic memory
    // manager for UEFI, so we are allocating frame buffer manually. Currently only
    // support single display, so allocate single(1) frame buffer
    {
        // Allocate frame buffer
        DisplayContextPtr->DisplayConfig.DisplaySurface[0].Width =
            DisplayContextPtr->DIContext[DisplayDevice].PreferedTiming.HActive;
        DisplayContextPtr->DisplayConfig.DisplaySurface[0].Height =
            DisplayContextPtr->DIContext[DisplayDevice].PreferedTiming.VActive;
        DisplayContextPtr->DisplayConfig.DisplaySurface[0].Bpp =
            DisplayContextPtr->DIContext[DisplayDevice].PreferedTiming.Bpp;
        DisplayContextPtr->DisplayConfig.DisplaySurface[0].PixelFormat =
            DisplayContextPtr->DIContext[DisplayDevice].PreferedTiming.PixelFormat;

        // iMX6 UEFI reserves display memory for fullHD buffer size.
        // PcdFrameBufferSize=800000h or 8388608 bytes - 1920x1080x4 bytes
        // to prevent larger displays overrun our reserved memory size, cap display resolution to fullHD
        // NOTE: for displays which do not have supported 1920x1080 mode may cause poor or missing picture

        RequestedDisplayMemorySize=DisplayContextPtr->DisplayConfig.DisplaySurface[0].Width *
            DisplayContextPtr->DisplayConfig.DisplaySurface[0].Height *
            (DisplayContextPtr->DisplayConfig.DisplaySurface[0].Bpp/8);

        DEBUG((DEBUG_INFO,"VideoiMX6DxeInitialize: Display Memory: Needed=%d, Available=%d\r\n",RequestedDisplayMemorySize,
            ReservedDisplayMemorySize));

        if (RequestedDisplayMemorySize > ReservedDisplayMemorySize) {
            DEBUG((DEBUG_INFO,"VideoiMX6DxeInitialize WARNING. Display resolution needs more video memory than reserved by %d bytes\r\n",
                RequestedDisplayMemorySize - ReservedDisplayMemorySize));
            DEBUG((DEBUG_ERROR,"VideoiMX6DxeInitialize - display horizontal resolution too big. Cap to HD 1080p\r\n"));

            DisplayContextPtr->DisplayConfig.DisplaySurface[0].Width = FullHDTiming.HActive;
            DisplayContextPtr->DisplayConfig.DisplaySurface[0].Height = FullHDTiming.VActive;
            DisplayContextPtr->DisplayConfig.DisplaySurface[0].Bpp = FullHDTiming.Bpp;

             OS_MEM_COPY(&DisplayContextPtr->DIContext[DisplayDevice].PreferedTiming,
                    &FullHDTiming, sizeof(DISPLAY_TIMING));
        }

        DEBUG((DEBUG_INFO,"VideoiMX6DxeInitialize - allocating frame buffer... \r\n"));
        status = AllocateFrameBuffer(
            &DisplayContextPtr->DisplayConfig.DisplaySurface[0]);
        if (EFI_ERROR(status)) {
            DEBUG(
                (DEBUG_ERROR,
                "VideoiMX6DxeInitialize: Fail to allocate fb, status=%r\n",
                status));
            goto Exit;
        };

        DEBUG((DEBUG_INFO,"VideoiMX6DxeInitialize - Initialize the frame buffer to black\r\n"));
        // Initialize the frame buffer to black
        SetMem32(
            (void*)DisplayContextPtr->DisplayConfig.DisplaySurface[0].PhyAddr,
            DisplayContextPtr->DisplayConfig.DisplaySurface[0].Width *
                DisplayContextPtr->DisplayConfig.DisplaySurface[0].Height * 4,
            0xFF000000);

    }

    DEBUG((DEBUG_INFO,"VideoiMX6DxeInitialize - set the display configuration to single HDMI mode\r\n"));
    // Set the display configuration to single HDMI/LVDS mode
    {
        DISPLAY_INTERFACE displayInterfaceOrder[MAX_DISPLAY] = {
            DisplayDevice,
            NO_DISPLAY,
            NO_DISPLAY,
            NO_DISPLAY,
        };

        DisplayContextPtr->DisplayConfig.DisplayTiming[0] =
            DisplayContextPtr->DIContext[DisplayDevice].PreferedTiming;

        status = ApplyDisplayConfig(
            DisplayContextPtr,
            SINGLE_MODE,
            displayInterfaceOrder);
        if (EFI_ERROR(status)) {
            DEBUG(
                (DEBUG_ERROR,
                "VideoiMX6DxeInitialize: Fail to set display. Exit status=%r\n",
                status));
            goto Exit;
        }
    }

    g_VidGopModeInfo.Version = 0;
    g_VidGopModeInfo.HorizontalResolution =
        DisplayContextPtr->DisplayConfig.DisplayTiming[0].HActive;
    g_VidGopModeInfo.VerticalResolution =
        DisplayContextPtr->DisplayConfig.DisplayTiming[0].VActive;
    g_VidGopModeInfo.PixelFormat = PixelBlueGreenRedReserved8BitPerColor;

    OS_ZERO_MEM(
        &g_VidGopModeInfo.PixelInformation,
        sizeof(g_VidGopModeInfo.PixelInformation));

    g_VidGopModeInfo.PixelsPerScanLine = g_VidGopModeInfo.HorizontalResolution;
    g_VidGopMode.MaxMode = 1;
    g_VidGopMode.Mode = 0;
    g_VidGopMode.Info = &g_VidGopModeInfo;
    g_VidGopMode.SizeOfInfo = sizeof(g_VidGopModeInfo);
    g_VidGopMode.FrameBufferBase =
        (EFI_PHYSICAL_ADDRESS)
            DisplayContextPtr->DisplayConfig.DisplaySurface[0].PhyAddr;
    g_VidGopMode.FrameBufferSize =
        g_VidGopModeInfo.HorizontalResolution *
            g_VidGopModeInfo.VerticalResolution *
            (DisplayContextPtr->DisplayConfig.DisplaySurface[0].Bpp / 8);

    DisplayContextPtr->DisplayConfig.OsHandle[0] = (UINT32)&ImageHandle;

    status = gBS->InstallMultipleProtocolInterfaces(
        &ImageHandle,
        &gEfiGraphicsOutputProtocolGuid,
        &g_VidGop,
        &gEfiDevicePathProtocolGuid,
        &g_VidDevicePath,
        NULL);
    if (EFI_ERROR(status)) {
        DEBUG(
            (DEBUG_ERROR,
            "VideoiMX6DxeInitialize: Fail to install protocol, status=%r\n",
            status));
        goto Exit;
    }

Exit:
    DEBUG((DEBUG_INFO,"--VideoiMX6DxeInitialize()=%Xh\r\n",status));
    return status;
}

//---------------------------------------------------------------- GOP routines.

EFI_STATUS
EFIAPI
VidGopQueryMode (
    IN EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
    IN UINT32 ModeNumber,
    OUT UINTN *SizeOfInfo,
    OUT EFI_GRAPHICS_OUTPUT_MODE_INFORMATION **Info
    )
{
    EFI_STATUS status;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *outputMode;

    if (FeaturePcdGet(PcdLvdsEnable)) {
        DisplayDevice = LVDS0_DISPLAY;
    } else {
        DisplayDevice = HDMI_DISPLAY;
    }


    g_EdidDiscovered.SizeOfEdid =
        DisplayContextPtr->DIContext[DisplayDevice].EdidDataSize;
    g_EdidDiscovered.Edid =
        DisplayContextPtr->DIContext[DisplayDevice].EdidData;
    g_EdidActive.SizeOfEdid =
        DisplayContextPtr->DIContext[DisplayDevice].EdidDataSize;
    g_EdidActive.Edid =
        DisplayContextPtr->DIContext[DisplayDevice].EdidData;

    status = gBS->InstallMultipleProtocolInterfaces(
        (EFI_HANDLE)DisplayContextPtr->DisplayConfig.OsHandle[0],
        &gEfiEdidDiscoveredProtocolGuid,
        &g_EdidDiscovered,
        &gEfiEdidActiveProtocolGuid,
        &g_EdidActive,
        NULL);
    if (EFI_ERROR(status)) {
        DEBUG(
            (DEBUG_ERROR,
            "Fail to install EDID discover and active protocol status=%r\n",
            status));
    }

    if (ModeNumber != 0) {
        DEBUG((DEBUG_ERROR, "VidGopQueryMode: Saw request to query mode %d\n", ModeNumber));
        status = EFI_INVALID_PARAMETER;
        goto Exit;
    }

    outputMode = (EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *)
        AllocatePool (sizeof(EFI_GRAPHICS_OUTPUT_MODE_INFORMATION));
    if (outputMode == NULL) {
        status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    outputMode->Version = 0;
    outputMode->HorizontalResolution = g_VidGopModeInfo.HorizontalResolution;
    outputMode->VerticalResolution = g_VidGopModeInfo.VerticalResolution;
    outputMode->PixelFormat = PixelBlueGreenRedReserved8BitPerColor;

    outputMode->PixelsPerScanLine = g_VidGopModeInfo.HorizontalResolution;
    *SizeOfInfo = sizeof(EFI_GRAPHICS_OUTPUT_MODE_INFORMATION);
    *Info = outputMode;

    status = EFI_SUCCESS;

Exit:
    return status;
}

EFI_STATUS
VidGopSetMode (
    IN EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
    IN UINT32 ModeNumber
    )
{
    OS_STATUS status;

    if (ModeNumber != 0) {
        DEBUG((DEBUG_ERROR, "VidGopSetMode: Saw request to set mode to %d\n", ModeNumber));
        status = OS_STATUS_UNSUPPORTED;
        goto Exit;
    }

    status = OS_STATUS_SUCCESS;

Exit:
    return status;
}

EFI_STATUS
VidGopBlt (
    IN EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
    IN OUT EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltBuffer, OPTIONAL
    IN EFI_GRAPHICS_OUTPUT_BLT_OPERATION BltOperation,
    IN UINTN SourceX,
    IN UINTN SourceY,
    IN UINTN DestinationX,
    IN UINTN DestinationY,
    IN UINTN Width,
    IN UINTN Height,
    IN UINTN Delta OPTIONAL
    )
{
    UINT32 *frameBuffer;
    UINT32 frameWidth;
    UINT32 frameOffset;
    UINT32 bufferOffset;
    UINT32 bufferWidth;
    UINT32 i;

    frameBuffer = (UINT32 *) (UINTN) g_VidGopMode.FrameBufferBase;
    frameWidth = g_VidGopModeInfo.HorizontalResolution;

    if (Delta == 0) {
        bufferWidth = Width;
    } else {
        bufferWidth = Delta / PIXEL_BYTES;
    }

    if (BltOperation == EfiBltVideoFill) {

        frameOffset = frameWidth * DestinationY + DestinationX;
        for (i = DestinationY; i < DestinationY + Height; i++) {
            SetMem32(frameBuffer + frameOffset,
                     Width * PIXEL_BYTES,
                     *(UINT32 *)BltBuffer
                     );
            frameOffset += frameWidth;
        }
    } else if (BltOperation == EfiBltVideoToBltBuffer) {

        frameOffset = frameWidth * SourceY + SourceX;
        bufferOffset = bufferWidth * DestinationY + DestinationX;

        for (i = SourceY; i < SourceY + Height; i++) {
            CopyMem(BltBuffer + bufferOffset,
                    frameBuffer + frameOffset,
                    Width * PIXEL_BYTES);
            frameOffset += frameWidth;
            bufferOffset += bufferWidth;
        }
    } else if (BltOperation == EfiBltBufferToVideo) {

        frameOffset = frameWidth * DestinationY + DestinationX;
        bufferOffset = bufferWidth * SourceY + SourceX;

        for (i = SourceY; i < SourceY + Height; i++) {
            CopyMem(frameBuffer + frameOffset,
                    BltBuffer + bufferOffset,
                    Width * PIXEL_BYTES);
            frameOffset += frameWidth;
            bufferOffset += bufferWidth;
        }

    } else if (BltOperation == EfiBltVideoToVideo) {

        frameOffset = frameWidth * DestinationY + DestinationX;
        bufferOffset = frameWidth * SourceY + SourceX;

        for (i = SourceY; i < SourceY + Height; i++) {
            CopyMem(frameBuffer + frameOffset,
                    frameBuffer + bufferOffset,
                    Width * PIXEL_BYTES);
            frameOffset += frameWidth;
            bufferOffset += frameWidth;
        }

    } else {
        DEBUG((DEBUG_ERROR, "VideoDxe:VidGopBlt not impl %d\n", BltOperation));
        return EFI_INVALID_PARAMETER;
    }

    return EFI_SUCCESS;
}
