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

    Enet_init.c

Abstract:

    implements Ethernet MAC (ENET) initialization related functions
*/

#include "EnetDxe.h"
#include <iMX6.h>
#include <iMX6ClkPwr.h>
#include <Library/TimerLib.h>

/*
    SnpInitialize

Resets a network adapter and allocates the transmit and receive buffers required by the network
interface; optionally, also requests allocation of additional transmit and receive buffers. 
    
Arguments:

SnpPtr          A pointer to the EFI_SIMPLE_NETWORK_PROTOCOL instance.
RxBufferSize    The size, in bytes, of the extra receive buffer space that the driver should allocate for the network interface.
                Some network interfaces will not be able to use the extra buffer, and the caller will not know if it is actually being used.
TxBufferSize    The size, in bytes, of the extra transmit buffer space that the driver should allocate for the network interface. 
                Some network interfaces will not be able to use the extra buffer, and the caller will not know if it is actually being used.    

Status Codes Returned:

    EFI_SUCCESS The network interface was initialized.
    EFI_NOT_STARTED The network interface has not been started.
    EFI_OUT_OF_RESOURCES There was not enough memory for the transmit and receive buffers.
    EFI_INVALID_PARAMETER This parameter was NULL or did not point to a valid
    EFI_SIMPLE_NETWORK_PROTOCOL structure.
    EFI_DEVICE_ERROR The command could not be sent to the network interface.
    EFI_UNSUPPORTED The increased buffer size feature is not supported.
 */
EFI_STATUS EFIAPI SnpInitialize(IN EFI_SIMPLE_NETWORK_PROTOCOL* SnpPtr,
                                IN UINTN RxBufferSize OPTIONAL,
                                IN UINTN TxBufferSize OPTIONAL)
{
    EFI_STATUS Status;
    UINT32 PmConf;
    INT32 AllocResult;
    UINT32 TempReg;
    UINT32 Speed = 0;
    INT32 timeout = 999;
    EFI_TPL SavedTpl;
    LANENET_DRIVER* LanDriverPtr;
    ENET_INFO("++SnpInitialize(RxBufSz=%d TxBufSz=%d)\r\n", RxBufferSize, TxBufferSize);

    // Check Snp instance

    if(SnpPtr == NULL) 
    {
        ENET_ERROR("--SnpInitialize() Error null ptr\r\n");
        return EFI_INVALID_PARAMETER;
    }

    SavedTpl = gBS->RaiseTPL(ENETIMX6_TPL);
    
    LanDriverPtr = INSTANCE_FROM_SNP_THIS(SnpPtr);

    // Check Snp Instance

    if(LanDriverPtr == NULL) 
    {
        ENET_ERROR("  SnpInitialize - invalid parameter\r\n");
        Status = EFI_INVALID_PARAMETER;
        goto EnetInitDone;
    }

    // First check that driver has not already been initialized

    if(SnpPtr->Mode->State == EfiSimpleNetworkInitialized)
    {
        ENET_WARNING(" SNP Driver already initialized\r\n");
        Status = EFI_SUCCESS;
        goto EnetInitDone;
    } 
    else
    {
        // SnpStart must be called before

        if(SnpPtr->Mode->State == EfiSimpleNetworkStopped)
        {
            ENET_WARNING(" SNP Driver not started\r\n");
            Status = EFI_NOT_STARTED;
            goto EnetInitDone;
        }
    }

    Status = RestartEnetController(SnpPtr);

    if(Status != EFI_SUCCESS)
    {
        ENET_ERROR("SnpInitialize(ERROR) - restart Enet controller failed!\r\n");
        goto EnetInitDone;
    }

    Status = StartReceiver(LanDriverPtr);

    if(Status != EFI_SUCCESS)
    {
        ENET_ERROR("SnpInitialize(ERROR) - Start Enet receiver failed!\r\n");
        goto EnetInitDone;
    }

    // Rx enabled. u-boot allows or 100 msec delay before using Enet

    MicroSecondDelay(100000);

    // dump Enet registers here

    if(Status == EFI_SUCCESS)
    {
        // Declare the driver as initialized

        SnpPtr->Mode->State = EfiSimpleNetworkInitialized;
        ENET_INIT(" SNP initialized.\r\n");

        // tell SNP our MAC address

        CopyMem((UINT8*)&SnpPtr->Mode->CurrentAddress, &mZeroMac, NET_ETHER_ADDR_LEN);
    }

EnetInitDone:
    DumpEnetRegs(LanDriverPtr);

    gBS->RestoreTPL(SavedTpl);
    ENET_INFO("--SnpInitialize()=%Xh\r\n", Status);
    return Status;
}

