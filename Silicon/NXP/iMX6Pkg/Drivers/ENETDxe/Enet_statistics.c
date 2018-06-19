/*

Copyright (c) 2012-2014, ARM Limited. All rights reserved.
Copyright (c) Microsoft Corporation. All rights reserved.

This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

File name:

    Enet_statistics.c

Abstract:

    implements Ethernet MAC (ENET) SNP statistics functions.

*/

#include "EnetDxe.h"
#include <iMX6.h>
#include <iMX6ClkPwr.h>
#include <Library/TimerLib.h>

/*
This function resets or collects the statistics on a network interface. If the size of the statistics table
specified by StatisticsSize is not big enough for all the statistics that are collected by the
network interface, then a partial buffer of statistics is returned in StatisticsTable,
StatisticsSize is set to the size required to collect all the available statistics, and
EFI_BUFFER_TOO_SMALL is returned.

Arguments:

    SnpPtr          A pointer to the EFI_SIMPLE_NETWORK_PROTOCOL instance.
    Reset           Set to TRUE to reset the statistics for the network interface.
    StatisticsSize  On input the size, in bytes, of StatisticsTable. On output the size, in bytes, of the resulting table of statistics.
    StatisticsTable A pointer to the EFI_NETWORK_STATISTICS structure that contains the statistics. Type EFI_NETWORK

Status Codes Returned:

    EFI_SUCCESS             The requested operation succeeded.
    EFI_NOT_STARTED         The Simple Network Protocol interface has not been started by calling Start().
    EFI_BUFFER_TOO_SMALL    StatisticsSize is not NULL and StatisticsTable is NULL. The current buffer size that is needed to hold all the statistics is returned in StatisticsSize.
    EFI_BUFFER_TOO_SMALL    StatisticsSize is not NULL and StatisticsTable is not NULL. The current buffer size that is needed to hold all the statistics is returned in StatisticsSize. A partial set of statistics is returned in StatisticsTable.
    EFI_INVALID_PARAMETER   StatisticsSize is NULL and StatisticsTable is not NULL.
    EFI_DEVICE_ERROR        The Simple Network Protocol interface has not been initialized by calling Initialize(), or
                            an error was encountered collecting statistics from the NIC.
    EFI_UNSUPPORTED         The NIC does not support collecting statistics from the network interface.    
 */
EFI_STATUS EFIAPI SnpStatistics(IN EFI_SIMPLE_NETWORK_PROTOCOL* SnpPtr,
                                  IN BOOLEAN Reset,
                                  IN  OUT UINTN* StatSize,
                                  OUT EFI_NETWORK_STATISTICS* Statistics)
{
    LANENET_DRIVER* LanDriver;
    EFI_STATUS Status;
    EFI_TPL SavedTpl;
    ENET_INFO("++SnpStatistics()\r\n");

    // Check Snp instance

    if(SnpPtr == NULL) 
    {
        ENET_ERROR("++SnpStatistics() null ptr\r\n");
        return EFI_INVALID_PARAMETER;
    }
    SavedTpl = gBS->RaiseTPL(ENETIMX6_TPL);
    LanDriver = INSTANCE_FROM_SNP_THIS(SnpPtr);

    // Check that driver was started and initialised

    if(SnpPtr->Mode->State == EfiSimpleNetworkStarted)
    {
        ENET_ERROR("Warning: LANENET Driver not initialized\r\n");
        Status = EFI_DEVICE_ERROR;
        goto GetStatsDone;
    }
    else if(SnpPtr->Mode->State == EfiSimpleNetworkStopped) 
    {
        ENET_WARNING("Warning: LANENET Driver in stopped state\r\n");
        Status = EFI_NOT_STARTED;
        goto GetStatsDone;
    }

    // Do a reset if required. It is not clearly stated in the UEFI specification
    // whether the reset has to be done before to copy the statistics in "Statictics"
    // or after. It is a bit strange to do it before but that is what is expected by
    // the SCT test on Statistics() with reset : "0x3de76704,0x4bf5,0x42cd,0x8c,0x89,
    // 0x54,0x7e,0x4f,0xad,0x4f,0x24".

    if(Reset) 
    {
        ZeroMem(&LanDriver->Stats, sizeof(EFI_NETWORK_STATISTICS));
    }

    Status = EFI_SUCCESS;
    if(StatSize == NULL)
    {
        if(Statistics != NULL)
        {
            Status = EFI_INVALID_PARAMETER;
            goto GetStatsDone;
        }
    } 
    else 
    {
        if(Statistics == NULL) 
        {
            Status = EFI_BUFFER_TOO_SMALL;
        }
        else
        {
            // Fill in the statistics

            CopyMem(Statistics, &LanDriver->Stats,
                    MIN(*StatSize, sizeof(EFI_NETWORK_STATISTICS)));

            if(*StatSize < sizeof(EFI_NETWORK_STATISTICS))
            {
                Status = EFI_BUFFER_TOO_SMALL;
            }
        }
        *StatSize = sizeof(EFI_NETWORK_STATISTICS);
    }

GetStatsDone:
    gBS->RestoreTPL(SavedTpl);    
    ENET_INFO("--SnpStatistics()=%Xh\r\n", Status);
    return Status;
}