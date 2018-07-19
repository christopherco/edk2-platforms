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
