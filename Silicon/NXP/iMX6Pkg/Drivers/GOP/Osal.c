//
// Copyright (C) Microsoft. All rights reserved
//

#include "Osal.h"

#include "Display.h"
#include "Ipu.h"


OS_STATUS UefiAllocContiguousMemory (
    UINT32 AllocSize,
    VOID** MemoryPointer)
{
    OS_STATUS status;

    *MemoryPointer = NULL;

    *MemoryPointer = AllocateRuntimePool(AllocSize);
    if (*MemoryPointer == NULL) {
        OS_ERROR("AllocateRuntimePool failed\n");
        status = OS_STATUS_INSUFFICIENT_RESOURCE;
        goto Exit;
    }

    status = OS_STATUS_SUCCESS;

Exit:
    return status;
}
