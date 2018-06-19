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

    Enet_start_stop.c

Abstract:

    implements Ethernet MAC (ENET) start and stop related functions, including sub components separately

*/

#include "EnetDxe.h"
#include <iMX6.h>
#include <iMX6ClkPwr.h>
#include <Library/TimerLib.h>

const INT32 EIR_REG_TIMEOUT = 999; // in microseconds

/* DisableEnetController

Function disables Enet controller. It also stops receive and transmit operations prior to stop 
controller if they are in progress.

Arguments:

    LanDriverPtr    pointer to the Enet driver instance

Retrun values:

    EFI_SUCCESS     The ENET's MAC address was copied into given variable
    error code      operation failed with error code

*/
EFI_STATUS DisableEnetController(IN LANENET_DRIVER* LanDriverPtr)
{
    EFI_STATUS retValue=0;
    UINT32 regvalue = 0;
    INT32 timeout;
    ENET_INFO("++DisableEnetController()\r\n");

    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->EIR, BIT28);

    // stop receiver

    StopReceiver(LanDriverPtr); 

    // perform graceful transmitter stop first
    
    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->TCR, MmioRead32((UINTN)&LanDriverPtr->enetRegisters->TCR) | TCR_BIT0_GRACEFUL_TXSTOP );

    timeout = EIR_REG_TIMEOUT;

    while( (MmioRead32((UINTN)&LanDriverPtr->enetRegisters->EIR) & BIT28) == 0 && --timeout != 0)
    {
        MicroSecondDelay(1);
    }

    // finally clear bit 1 in ECR

    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->ECR, MmioRead32((UINTN)&LanDriverPtr->enetRegisters->ECR) & ~ECR_BIT1_ENABLED );

    ENET_INIT(" disabled ----\r\n");

    // reset DMA indeces to initial values
    
    LanDriverPtr->Rbd_index = 0;
    LanDriverPtr->tbd_index = 0;

    ENET_INFO("++DisableEnetController()=%Xh\r\n", retValue );
    return retValue;
}


/* EnableEnetController

This function enables Enet controller,
it also restores registers which are lost when EN bit transitions from 0 to 1.
When the MAC is disabled, the buffer descriptors for an aborted transmit frame are not updated. 
The sDMA, buffer descriptor, and FIFO control logic are reset, including the buffer descriptor and FIFO pointers.

ETHEREN bit of ECR register must be set at the very last step during ENET configuration/setup/(re)initialization,
only after all other ENET-related registers have been configured.
If ETHEREN is cleared to 0 by software then next time ETHEREN is set, the EIR interrupts
must cleared to 0 due to previous pending interrupts.

    LanDriverPtr    pointer to the Enet driver instance

Retrun values:

    EFI_SUCCESS     operation succeded
    error code

*/
EFI_STATUS EnableEnetController(IN LANENET_DRIVER* LanDriverPtr)
{
    EFI_STATUS retValue = 0;
    UINT32 TempReg = 0;
    INT32 k = 0;
    INT32 timeout;
    volatile ENET_BD* OneBDPtr = NULL;
    ENET_INFO("++EnableEnetController()\r\n");

    // the following registers lose content when Enet controller cycles enable-disable
    // TDSr, RDSR, MRBR, RDAR, TDAR 

    SetBlockDescrRegs(LanDriverPtr);

    // clean all block descriptors

    OneBDPtr = LanDriverPtr->RecvBDBasePtr;
    for(k = 0; k < LANENET_RX_RING_NUM_ENTRIES; k++, OneBDPtr++)
    {
        if(k == LANENET_RX_RING_NUM_ENTRIES - 1)
        {
            ENET_INFO("EnableEnetController() closed Rx ring buffer at [%d]\r\n", k);
            CleanOneBlockDescriptor_Rx(OneBDPtr, TRUE);
        }
        else
        {
            CleanOneBlockDescriptor_Rx(OneBDPtr, FALSE);
        }
    }

    OneBDPtr = LanDriverPtr->SendBDBasePtr;
    for(k = 0; k < LANENET_TX_RING_NUM_ENTRIES; k++, OneBDPtr++)
    {
        if(k == LANENET_TX_RING_NUM_ENTRIES - 1)
        {
            ENET_INFO("EnableEnetController() closed Rx ring buffer at [%d]\r\n", k);
            CleanOneBlockDescriptor_Tx(OneBDPtr, TRUE);
        }
        else
        {
            CleanOneBlockDescriptor_Tx(OneBDPtr, FALSE);
        }
    }

    // also reset receive and transmit buffer counters - since uDMA was reset

    LanDriverPtr->tbd_index = 0;
    LanDriverPtr->Rbd_index =  0;

    // all is ready, enable Enet controller

    TempReg = MmioRead32((UINTN)&LanDriverPtr->enetRegisters->ECR);
    TempReg |= ECR_BIT1_ENABLED;
    TempReg &= ~ECR_BIT0_RESET;
    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->ECR, TempReg);

    ENET_INIT(" waiting to Enet to become ready ECR=%08Xh\r\n", TempReg);

    timeout = EIR_REG_TIMEOUT;

    while((MmioRead32((UINTN)&LanDriverPtr->enetRegisters->ECR) & ECR_BIT1_ENABLED) == 0x0 && timeout != 0)
    {
        MicroSecondDelay(10);
        timeout -= 1;
    }

    if(timeout == 0)
    {
        ENET_ERROR(" Enet error - controller timeout\r\n");
        retValue = EFI_NOT_READY;
    }
    else
    {
        ENET_INIT(" enabled *** \r\n");
        retValue = EFI_SUCCESS;
    }
    ENET_INFO("--EnableEnetController()=%Xh\r\n", retValue );
    return retValue;
}

/* StartReceiver

Function starts Enet receiver only.

Arguments:

    LanDriverPtr    pointer to the Enet driver instance

Retrun values:

    EFI_SUCCESS     operation succeded
    error code

*/
EFI_STATUS StartReceiver(IN LANENET_DRIVER* LanDriverPtr)
{
    EFI_STATUS retValue = 0;
    if(NULL == LanDriverPtr)
    {
        ENET_INFO("StartReceiver() error null ptr\r\n");
        retValue = EFI_INVALID_PARAMETER;
    }
    else
    {
        MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->RDAR, ENET_RDAR_ACTIVE_ACTIVE); 
        ENET_INFO(" receiver started\r\n");
        LanDriverPtr->ReceiverActivated = TRUE;
    }
    return retValue;
}

/* StopReceiver

Function stops Enet receiver only.

Arguments:

    LanDriverPtr    pointer to the Enet driver instance

Retrun values:

    EFI_SUCCESS     operation succeded
    error code

*/
EFI_STATUS StopReceiver(IN LANENET_DRIVER* LanDriverPtr)
{
    EFI_STATUS retValue = 0;
    if(NULL == LanDriverPtr)
    {
        ENET_INFO("StopReceiver() error null ptr\r\n");
        retValue = EFI_INVALID_PARAMETER;
    }
    else
    {
        MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->RDAR, 0); 

        // wait for graceful receiver stop
        MicroSecondDelay(1300);

        // verify
        if(MmioRead32((UINTN)&LanDriverPtr->enetRegisters->RDAR)==0)
        {
            ENET_INFO(" receiver stopped\r\n");
            retValue = EFI_SUCCESS;
            LanDriverPtr->ReceiverActivated = FALSE;
        }
        else
        {
            ENET_INFO(" receiver failed to stop!\r\n");
            retValue = EFI_DEVICE_ERROR;
        }
    }
    return retValue;
}

/* StartTransmitter

Function starts Enet transmitter only.

Arguments:

    LanDriverPtr    pointer to the Enet driver instance

Retrun values:

    EFI_SUCCESS     operation succeded
    error code

*/
EFI_STATUS StartTransmitter(IN LANENET_DRIVER* LanDriverPtr)
{
    EFI_STATUS retValue = 0;
    ENET_INFO("++StartTransmitter()\r\n");

    if(NULL == LanDriverPtr)
    {
        ENET_INFO("StartTransmitter() error null ptr\r\n");
        retValue = EFI_INVALID_PARAMETER;
    }
    else
    {
        // clear GTS to restart transmitter

        MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->TCR, (MmioRead32((UINTN)&LanDriverPtr->enetRegisters->TCR) & ~TCR_BIT0_GRACEFUL_TXSTOP)); 

        // wait for transmitter to clear out stale frames
        MicroSecondDelay(1300);

        // verify
        if((MmioRead32((UINTN)&LanDriverPtr->enetRegisters->TCR) & TCR_BIT0_GRACEFUL_TXSTOP) == 0)
        {
            ENET_INFO(" transmitter started\r\n");
            retValue = EFI_SUCCESS;
        }
        else
        {
            ENET_INFO(" transmitter failed to start!\r\n");
            retValue = EFI_DEVICE_ERROR;
        }
    }

    ENET_INFO("--StartTransmitter()=%Xh\r\n", retValue );
    return retValue;
}

/* StopTransmitter

Function stops Enet transmitter only by attempting to perform graceful stop (GTS) operation first.
Whether GTS succeeds or not, transmitter is stopped anyway.

Arguments:

    LanDriverPtr    pointer to the Enet driver instance

Retrun values:

    EFI_SUCCESS     operation succeded
    error code

*/
EFI_STATUS StopTransmitter(IN LANENET_DRIVER* LanDriverPtr)
{
    EFI_STATUS retValue = 0;
    ENET_INFO("++StopTransmitter()\r\n");

    if(NULL == LanDriverPtr)
    {
        ENET_INFO("StartTransmitter() error null ptr\r\n");
        retValue = EFI_INVALID_PARAMETER;
    }
    else
    {
        // set GTS to stop transmitter

        MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->TCR, (MmioRead32((UINTN)&LanDriverPtr->enetRegisters->TCR) | TCR_BIT0_GRACEFUL_TXSTOP)); 

        // wait for transmitter to clear out stale frames
        MicroSecondDelay(1300);

        // verify
        if((MmioRead32((UINTN)&LanDriverPtr->enetRegisters->TCR) & TCR_BIT0_GRACEFUL_TXSTOP) != 0x0)
        {
            ENET_INFO(" transmitter stopped\r\n");
            retValue = EFI_SUCCESS;
        }
        else
        {
            ENET_INFO(" transmitter failed to stop!\r\n");
            retValue = EFI_DEVICE_ERROR;
        }
    }

    ENET_INFO("--StopTransmitter()=%Xh\r\n", retValue );
    return retValue;
}

/* SnpStart

Prepares the network interface for further command operations. No other EFI_SIMPLE_NETWORK_PROTOCOL interface functions will operate
until this call is made. 
Changes the state of a network interface from “stopped” to “started.”
If the network interface successfully starts, then EFI_SUCCESS will be returned.

Arguments:
    SnpPtr  pointer to our SNP protocol instance
return values:

    EFI_SUCCESS             The network interface was started.
    EFI_ALREADY_STARTED     The network interface is already in the started state.
    EFI_INVALID_PARAMETER   This parameter was NULL or did not point to a valid EFI_SIMPLE_NETWORK_PROTOCOL structure.
    EFI_DEVICE_ERROR        The command could not be sent to the network interface.
    EFI_UNSUPPORTED         This function is not supported by the network interface
*/
EFI_STATUS EFIAPI SnpStart(IN EFI_SIMPLE_NETWORK_PROTOCOL* SnpPtr)
{
    EFI_STATUS retValue;
    EFI_TPL SavedTpl;
    ENET_INFO("++SnpStart()\r\n");
  
    // Check Snp instance

    if(SnpPtr == NULL) 
    {
        ENET_ERROR( " SnpStart() invalid SnpPtr parameter\r\n");
        retValue=EFI_INVALID_PARAMETER;
    }
    else
    {
        SavedTpl = gBS->RaiseTPL(ENETIMX6_TPL);

        // Check state

        if((SnpPtr->Mode->State == EfiSimpleNetworkStarted) || (SnpPtr->Mode->State == EfiSimpleNetworkInitialized))
        {
            ENET_WARNING( " SnpStart() - already started!\r\n");
            retValue = EFI_ALREADY_STARTED;
        }
        else
        {
            // Change state

            SnpPtr->Mode->State = EfiSimpleNetworkStarted;
            retValue = EFI_SUCCESS;
            ENET_INIT(" Snp Started\r\n");
        }
        gBS->RestoreTPL(SavedTpl);
    }
    ENET_INFO( "--SnpStart()=%Xh\r\n", retValue);
    return retValue;
}

 /* SnpStop

Stops further network interface command processing. Changes the state of a network interface from “started” to “stopped.”
No other EFI_SIMPLE_NETWORK_PROTOCOL interface functions will operate after this call is made until
another Start() call is made. 
This call is only valid if the network interface is in the started state. If the network interface was successfully stopped, 
then EFI_SUCCESS will be returned.

Arguments:

    SnpPtr  pointer to our SNP protocol instance

return values:

    EFI_SUCCESS             The network interface was stopped.
    EFI_NOT_STARTED         The network interface has not been started.
    EFI_INVALID_PARAMETER   This parameter was NULL or did not point to a valid EFI_SIMPLE_NETWORK_PROTOCOL structure.
    EFI_DEVICE_ERROR        The command could not be sent to the network interface.
    EFI_UNSUPPORTED         This function is not supported by the network interface. 
*/
EFI_STATUS EFIAPI SnpStop(IN EFI_SIMPLE_NETWORK_PROTOCOL* SnpPtr)
{
    EFI_STATUS status = 0;
    EFI_TPL SavedTpl;
    ENET_INFO("+SnpStop()\r\n");

    // Check Snp Instance

    if(SnpPtr == NULL) 
    {
        ENET_ERROR( "--SnpStop() null ptr\r\n");
        return EFI_INVALID_PARAMETER;
    }

     SavedTpl = gBS->RaiseTPL(ENETIMX6_TPL);

    // Check state of the driver
    if(SnpPtr->Mode->State == EfiSimpleNetworkStopped)
    {
        ENET_ERROR( " SnpStop() not started\r\n");
        status = EFI_NOT_STARTED;
        goto StopDone;
    }

    // Change the state

    switch(SnpPtr->Mode->State)
    {
        case EfiSimpleNetworkStarted:
        case EfiSimpleNetworkInitialized:
            SnpPtr->Mode->State = EfiSimpleNetworkStopped;
            status = EFI_SUCCESS;
            break;
        default:
            ENET_ERROR( " SnpStart() unknown Mode\r\n");
            status = EFI_DEVICE_ERROR;
    }

StopDone:
    gBS->RestoreTPL(SavedTpl);
    ENET_INFO( "--SnpStop()=%Xh\r\n", status);
    return status;
}
