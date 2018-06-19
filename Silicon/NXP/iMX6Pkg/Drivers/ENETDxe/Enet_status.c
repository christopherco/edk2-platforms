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

    Enet_status.c

Abstract:

    implements Ethernet MAC (ENET) SNP status function.

*/

#include "EnetDxe.h"
#include <iMX6.h>
#include <iMX6ClkPwr.h>
#include <Library/TimerLib.h>

/*
This function gets the current interrupt and recycled transmit buffer status from the network
interface. The interrupt status is returned as a bit mask in InterruptStatus.
If InterruptStatus is NULL, the interrupt status will not be read. 
  
Upon successful return of the media status, the MediaPresent field of EFI_SIMPLE_NETWORK_MODE will be updated to
reflect any change of media status.
  
If TxBuffPtrPtr is not NULL, a recycled transmit buffer address will be retrieved. 
If a recycled transmit buffer address is returned in TxBuffPtrPtr, then the buffer has been successfully transmitted, and the status
    for that buffer is cleared. 
If the status of the network interface is successfully collected, EFI_SUCCESS will be returned. 
If the driver has not been initialized, EFI_DEVICE_ERROR will be returned.
    
Arguments:

SnpPtr              A pointer to the EFI_SIMPLE_NETWORK_PROTOCOL instance.
IrqStatPtr          A pointer to the bit mask of the currently active interrupts (see “Related Definitions”). 
    If this is NULL, the interrupt status will not be read from the device. 
    If this is not NULL, the interrupt status will be read from the device. 
        When the interrupt status is read, it will also be cleared. 
        Clearing the transmit interrupt does not empty the recycled transmit buffer array.
TxBuffPtrPtr        Recycled transmit buffer address. The network interface will not transmit if its internal recycled transmit buffer array is full. 
    Reading the transmit buffer does not clear the transmit interrupt. 
    If this is NULL, then the transmit buffer status will not be read. 
    If there are no transmit buffers to recycle and TxBuffPtrPtr is not NULL, *TxBuffPtrPtr will be set to NULL.

Status Codes Returned:

    EFI_SUCCESS The status of the network interface was retrieved.
    EFI_NOT_STARTED The network interface has not been started.
    EFI_INVALID_PARAMETER This parameter was NULL or did not point to a valid
    EFI_SIMPLE_NETWORK_PROTOCOL structure.
    EFI_DEVICE_ERROR The command could not be sent to the network interface. 

SnpGetStatus is called every 1 second when no send or receive is in progress. It mainly checks link status
SnpGetStatus is called every 10 milliseconds when either send or receive is in progress
*/
EFI_STATUS EFIAPI SnpGetStatus(IN EFI_SIMPLE_NETWORK_PROTOCOL* SnpPtr,
                            OUT UINT32* IrqStatPtr OPTIONAL,
                            OUT VOID** TxBuffPtrPtr OPTIONAL)
{
    EFI_STATUS Status = 0;
    UINT32 TxStatus;
    UINT16 PacketTag;
    UINT32 Interrupts;
    EFI_TPL SavedTpl;
    UINT32 EirErrorsMask = BIT18 | BIT29 | BIT30 | BIT22;
    LANENET_DRIVER* LanDriverPtr;
    ENET_INFO("++SnpGetStatus(IrqStatPtr=%p, TxBuffPtrPtr=%p)\r\n", IrqStatPtr, TxBuffPtrPtr);

    // Check preliminaries

    if(SnpPtr == NULL) 
    {
        ENET_ERROR("--SnpGetStatus() error - null ptr\r\n");
        return EFI_INVALID_PARAMETER;
    }
    SavedTpl = gBS->RaiseTPL(ENETIMX6_TPL);
    LanDriverPtr = INSTANCE_FROM_SNP_THIS(SnpPtr);

    // Check that driver was started and initialised

    if(SnpPtr->Mode->State == EfiSimpleNetworkStarted)
    {
        ENET_WARNING("Warning: SnpGetStatus Driver not initialized\r\n");
        Status=EFI_DEVICE_ERROR;
        goto EndCheckStatus;
    } 
    else if(SnpPtr->Mode->State == EfiSimpleNetworkStopped)
    {
        ENET_WARNING("Warning: SnpGetStatus Driver in stopped state\r\n");
        Status=EFI_NOT_STARTED;
        goto EndCheckStatus;
    }

    // Read ENET event status. 
    // If IrqStatPtr is provided then report Enet status into it

    // Check Enet controller Error Status and ack errors

    if( (MmioRead32((UINTN)&LanDriverPtr->enetRegisters->EIR) & EirErrorsMask) != 0x0) 
    {
        MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->EIR, EirErrorsMask);
        Status=EFI_DEVICE_ERROR;

        // TODO
        // stop Enet controller and then start it

        ENET_ERROR("SnpGetStatus Ethernet error. Restarting...");
        goto EndCheckStatus;
    }

    // Check Enet controller state

    if( (MmioRead32((UINTN)&LanDriverPtr->enetRegisters->EIR) & BIT28) != 0x0) 
    {
        MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->EIR, EirErrorsMask);
        Status=EFI_DEVICE_ERROR;

        ENET_ERROR("SnpGetStatus Transmitter stopped (GRA=1). Starting...");

        // TODO
        // need to start Enet controller

        goto EndCheckStatus;
    }

    // Check for receive event. Bit 25 RXF

    if((MmioRead32((UINTN)&LanDriverPtr->enetRegisters->EIR) & BIT25) != 0x0) 
    { 
        // Acknowledge the RXF

        MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->EIR, BIT25);

        if(IrqStatPtr != NULL) 
        {
            *IrqStatPtr |= EFI_SIMPLE_NETWORK_RECEIVE_INTERRUPT;
            ENET_INFO("SnpGetStatus recv event RXF (bit25) intr\r\n");
        }
        else
        {
            ENET_INFO("SnpGetStatus recv event RXF (bit25)\r\n");
        }
    }

    // Check for transmit interrupt. bit 27 TXF

    if( (MmioRead32((UINTN)&LanDriverPtr->enetRegisters->EIR) & BIT27) != 0x0) 
    {
        // Acknowledge the TXF

        MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->EIR, BIT27);

        if(IrqStatPtr != NULL) 
        {
            *IrqStatPtr |= EFI_SIMPLE_NETWORK_TRANSMIT_INTERRUPT;
            ENET_INFO("SnpGetStatus TXF event (bit27) intr\r\n");
        }
        else
        {
            ENET_INFO("SnpGetStatus TXF event (bit27)\r\n");
        }

        // tell UEFI network stack that we are done with their send buffer
        // which they supplied us last time in SnpTransmit()

        if(TxBuffPtrPtr != NULL) 
        {
            LanDriverPtr->Stats.TxTotalFrames += 1;
            if(LanDriverPtr->tbd_index == 0)
            {
                *TxBuffPtrPtr = LanDriverPtr->TxBuffCallerPtrs[1];
                ENET_INFO("SnpGetStatus TxBuffPtrPtr=%08Xh from clrs[1]\r\n",*TxBuffPtrPtr);
            }
            else
            {
                *TxBuffPtrPtr = LanDriverPtr->TxBuffCallerPtrs[0];
                ENET_INFO("SnpGetStatus TxBuffPtrPtr=%08Xh from clrs[0]\r\n",*TxBuffPtrPtr);
            }
        }
    }

    // Update the media status

    Status = CheckLinkStatus(SnpPtr);
    if (EFI_ERROR(Status)) 
    {
        SnpPtr->Mode->MediaPresent = FALSE;
    } 
    else 
    {
        SnpPtr->Mode->MediaPresent = TRUE;
    }
    Status = EFI_SUCCESS;

EndCheckStatus:
    gBS->RestoreTPL(SavedTpl);
    ENET_INFO("--SnpGetStatus()=%Xh\r\n", Status);
    return Status;
}

/*
This function checks the ENET link status and takes appropriate action. Uses MDIO commands to communicate to PHY
    
Arguments:

SnpPtr  A pointer to the EFI_SIMPLE_NETWORK_PROTOCOL instance.

Status Codes Returned:

    EFI_SUCCESS             The status of the network link status was retrieved.
    EFI_NOT_STARTED         The network interface has not been started.
    EFI_INVALID_PARAMETER   This parameter was NULL or did not point to a valid EFI_SIMPLE_NETWORK_PROTOCOL structure.
    EFI_DEVICE_ERROR        The command could not be sent to the network interface. 
*/

EFI_STATUS CheckLinkStatus(IN EFI_SIMPLE_NETWORK_PROTOCOL* SnpPtr)
{
    EFI_STATUS Status = 0;
    UINT32 RegValue = 0;
    static INT32 linkStatus =- 1; // -1 is unknown, 1 is link exists, 0 is no link
    LANENET_DRIVER* LanDriverPtr;
    ENET_INFO("++CheckLinkStatus()\r\n");

    // Check Snp instance

    if(SnpPtr == NULL) 
    {
        Status = EFI_INVALID_PARAMETER;
        ENET_ERROR("CheckLinkStatus error - nul ptr\r\n");
        goto LinkStatusDone;
    }

    LanDriverPtr = INSTANCE_FROM_SNP_THIS(SnpPtr);

    // check if autonegotation is supported

    Status = PHYRead32(LanDriverPtr, MII_REG_SR, &RegValue);

    if(Status == EFI_SUCCESS)
    {
        // check if link is up

        if(((RegValue & MMI_DATA_MASK) & 0x0004) == 0)
        {
            ENET_INFO(" no link\r\n");

            if(linkStatus == -1)
            {
                linkStatus = 0;
            }

            if(linkStatus == 1)
            {
                linkStatus = 0;
                SerialPrint("Ethernet link lost! Check Ethernet cable\n\r");
            }
            Status = EFI_NOT_READY;
        }
        else
        {
            ENET_INFO(" link present\r\n");

            if(linkStatus == -1)
            {
                linkStatus = 1;
            }

            if(linkStatus == 0)
            {
                SerialPrint("Ethernet link restored\r\n");
                linkStatus = 1;
            }
            Status = EFI_SUCCESS;
        }
    }

LinkStatusDone:
    ENET_INFO("--CheckLinkStatus()=%Xh\r\n", Status);
    return Status;
}

