//
// Copyright (C) Microsoft. All rights reserved
//

#ifndef _OSAL_H_
#define _OSAL_H_

// OS abstraction header

#ifdef WIN32 // Windows

#else // UEFI

#include <Uefi.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>

// UEFI only headers
#include <iMX6.h>
#include <iMXDisplay.h>
#include <iMX6ClkPwr.h>

#define OS_READ8(ADDRESS)  MmioRead8(ADDRESS)
#define OS_WRITE8(ADDRESS, VALUE)  MmioWrite8(ADDRESS, VALUE)
#define OS_READ32(ADDRESS)  MmioRead32((UINT32)ADDRESS)
#define OS_WRITE32(ADDRESS, VALUE)  MmioWrite32((UINT32)ADDRESS, VALUE)

#ifndef ARRAYSIZE
#define ARRAYSIZE(__array__) (sizeof((__array__))/sizeof((__array__[0])))
#endif

#define OS_STATUS                           EFI_STATUS
#define OS_STATUS_SUCCESS                   EFI_SUCCESS
#define OS_STATUS_INVALID_PARAM             EFI_INVALID_PARAMETER
#define OS_STATUS_DEVICE_ERROR              EFI_DEVICE_ERROR
#define OS_STATUS_UNSUPPORTED               EFI_UNSUPPORTED
#define OS_STATUS_INSUFFICIENT_RESOURCE     EFI_OUT_OF_RESOURCES

OS_STATUS UefiAllocContiguousMemory (
    UINT32 AllocSize,
    VOID** MemoryPointer
    );

#define OS_MMIO_MAP(PHYSICAL_ADDRESS)           PHYSICAL_ADDRESS
#define OS_SLEEP(MILISECOND)                    gBS->Stall(MILISECOND)
#define OS_ALLOC_CONTIGUOUS_MEMORY(ALLOC_SIZE, MEMORY_POINTER) \
            UefiAllocContiguousMemory(ALLOC_SIZE, (VOID**) MEMORY_POINTER)
#define OS_VIRT_TO_PHY_ADDR(VIRT_ADDR)          (VIRT_ADDR)
#define OS_MEM_COPY(DEST, SRC, SIZE)            CopyMem(DEST, SRC, SIZE)
#define OS_ZERO_MEM(VIRT_ADDR, SIZE)            ZeroMem(VIRT_ADDR, SIZE)

#define OS_LOG_FMT_HELPER(FMT, ...) \
    "iMX6Gop:" FMT "%a", __VA_ARGS__

#define OS_INFO(...) DEBUG((DEBUG_INFO, OS_LOG_FMT_HELPER(__VA_ARGS__, "")))
#define OS_WARNING(...) DEBUG((DEBUG_WARN, OS_LOG_FMT_HELPER(__VA_ARGS__, "")))
#define OS_ERROR(...) DEBUG((DEBUG_ERROR, OS_LOG_FMT_HELPER(__VA_ARGS__, "")))

#endif

#endif