/*

Copyright (c) 2012-2014, ARM Limited. All rights reserved.
Copyright (c) Microsoft Corporation. All rights reserved.

This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

    PHY.c

Abstract:

    Ethernet MAC (ENET) PHY related functions.

*/

#include "EnetDxe.h"
#include <iMX6.h>
#include <iMX6ClkPwr.h>
#include <iMX6IoMux.h>
#include <Library/TimerLib.h>

const INT32 MII_TIMEOUT = 9999; // in microseconds

/* PHYRead32

This function reads iMX6 PHY register using MDIO management
interface via a standardized method to access the PHY device management
registers. See docuemntation at 23.6.17 PHY management interface

Arguments:

    LanDriverPtr  A pointer to the Enet driver instance
    Index         PHY register number in range 0 - 31
    ValueReadPtr  PHY register value retruned

Retrun values:

    EFI_SUCCESS     The ENET's MAC address was copied into given variable
    error code      operation failed with error code

*/
EFI_STATUS PHYRead32(LANENET_DRIVER* LanDriverPtr, UINT32 Index, UINT32* ValueReadPtr)
{
    UINT32 ValueRead = 0;
    UINT32 MiiAcc;
    EFI_STATUS Status = 0;
    UINT32 RegValue = 0;
    UINT32 MIIReg = 0;
    INT32 iMMFR_timeout;
    ENET_PHY("++PHYRead32(%d)\r\n",Index);

    // Check if it is a valid index

    if(Index > 31)
    {
        ENET_ERROR(" PHYRead32(%d) ERROR - bad PhyAddress\r\n",Index);
        ASSERT(Index < 31);
    }

    // clear PHY event if any

    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->EIR, (0x1 << 23));

    // find extern PHY address if not known yet

    if(LanDriverPtr->PhyAddress == -1)
    {
        Status = EFI_DEVICE_ERROR;
        ENET_ERROR(" PHYRead32(%d) ERROR - unknown PhyAddress\r\n",Index);
        goto PhyReadDone;
    };

    // check MII clock

    if(MmioRead32((UINTN)&LanDriverPtr->enetRegisters->MSCR) == 0x0)
    {
        // Set MII speed to 2.5MHz

        MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->MSCR, 0xD << 1);
        ENET_WARNING(" PhyRead MSCR was not set!, new value=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->MSCR) );
    }

    RegValue = MII_READ_COMMAND(Index);
    RegValue |= CSP_BITFVAL(ENET_MMFR_PA, LanDriverPtr->PhyAddress);
    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->MMFR, RegValue);

    // wait for MII interrupt to happen - bit 23 in EIR

    iMMFR_timeout = MII_TIMEOUT;

    for( ; iMMFR_timeout >= 0; iMMFR_timeout -= 1)
    {
        if( (MmioRead32((UINTN)&LanDriverPtr->enetRegisters->EIR) & BIT23) !=0 )
        {
            // ack MII event
            
            MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->EIR, BIT23);
            break;
        }
        MicroSecondDelay(1);
    };

    // check for timeout

    if(iMMFR_timeout < 0)
    {
        Status = EFI_TIMEOUT;
        ENET_WARNING(" PhyRead command time out\r\n");
        goto PhyReadDone;
    };

    // Now read the value of the register
    // now get the MII frame value from MMFR register
    
    MIIReg = MmioRead32((UINTN)&LanDriverPtr->enetRegisters->MMFR);

    *ValueReadPtr = MIIReg;
     MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->EIR, BIT23);

PhyReadDone:
    ENET_PHY("--PHYRead32( PHY[%d]=>%Xh )=%08Xh\r\n", Index, *ValueReadPtr, Status);
    return Status;
}

/* PHYWrite32

This function writes iMX6 PHY register using MDIO management
interface via a standardized method to access the PHY device management
registers. See docuemntation at 23.6.17 PHY management interface

Arguments:

    LanDriverPtr    pointer to the Enet driver instance
    Index           PHY register number in range 0 - 31
    Value           PHY register value to write

Retrun values:

    EFI_SUCCESS     The ENET's MAC address was copied into given variable
    error code      operation failed with error code

*/
EFI_STATUS PHYWrite32(LANENET_DRIVER* LanDriverPtr, UINT32 Index, UINT32 Value)
{
    UINT32 MiiAcc = 0;
    UINT32 ValueWritten = 0;
    UINT32 ValueRead = 0;
    EFI_STATUS Status = 0;
    UINT32 RegValue = 0;
    UINT32 MIIReg = 0;
    INT32 iMMFR_timeout;
    ENET_PHY("++PHYWrite32(%d,%08Xh)\r\n",Index,Value);

    // Check it is a valid index

    if(Index > 31)
    {
        ENET_ERROR(" PHYWrite32(%d) ERROR - bad PhyAddress\r\n",Index);
        ASSERT(Index < 31);
    }

    // clear PHY event if any

    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->EIR, BIT23);

    // if PHY address is not known

    if(LanDriverPtr->PhyAddress == -1)
    {
        Status = EFI_DEVICE_ERROR;
        ENET_ERROR(" Error PHYWrite32(%d,%08Xh) invalid address\r\n", Index, Value);
        goto PhyReadDone;
    }

    // check MII clock

    if(MmioRead32((UINTN)&LanDriverPtr->enetRegisters->MSCR) == 0x0)
    {
        MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->MSCR, 0xD << 1);
        ENET_WARNING(" PhyWrite MSCR was 0, new value=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->MSCR) );
    }

    RegValue = MII_WRITE_COMMAND(Index, Value);
    RegValue |= CSP_BITFVAL(ENET_MMFR_PA, LanDriverPtr->PhyAddress);
    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->MMFR, RegValue);

    // wait for MII interrupt to happen - bit 23 in EIR

    iMMFR_timeout = MII_TIMEOUT;

    for(; iMMFR_timeout >= 0; iMMFR_timeout -= 1)
    {
        if( (MmioRead32((UINTN)&LanDriverPtr->enetRegisters->EIR) & BIT23) !=0 )
        {
            // ack MII event
            MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->EIR, BIT23);
            break;
        }
        MicroSecondDelay(1);
    }

    // check for timeout

    if(iMMFR_timeout < 0)
    {
        Status = EFI_TIMEOUT;
        ENET_WARNING(" PhyWrite - command time out\r\n");
    }
    else
    {
        Status = EFI_SUCCESS;
    }
    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->EIR, BIT23);
PhyReadDone:
    ENET_PHY("--PHYWrite32( %Xh=>PHY[%d] )=%08Xh\r\n", Value, Index, Status);
    return Status;
}

//
// Function Dumps PHY Registers
//      must know the address of the PHY

/* DumpPHYRegs

Function Dumps PHY Registers 0-31.
Note - PHY address must be set prior to this call (typically is 0 on iMX6)

Arguments:

    LanDriverPtr    pointer to the Enet driver instance

Retrun values:

    EFI_SUCCESS     The ENET's MAC address was copied into given variable
    error code      operation failed with error code

*/
VOID DumpPHYRegs(LANENET_DRIVER* LanDriverPtr)
{
    UINT32 uiIdx = 0, reg;
    ENET_PHY("++DumpPHYRegs\r\n");

    for(uiIdx = 0; uiIdx < 0xF; ++uiIdx)
    {
        PHYRead32(LanDriverPtr, uiIdx, &reg);
        ENET_PHY("\t PHY Reg[%02d] = %08Xh\r\n", uiIdx, reg);
    }
    ENET_PHY("--DumpPHYRegs\r\n");
    return;
}
