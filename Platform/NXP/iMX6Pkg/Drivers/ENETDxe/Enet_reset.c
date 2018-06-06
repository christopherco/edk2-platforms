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

    Enet_reset.c

Abstract:

    implements Ethernet MAC (ENET) reset related functions.

*/

#include "EnetDxe.h"
#include <iMX6.h>
#include <iMX6ClkPwr.h>
#include <Library/TimerLib.h>
#include <Library/PrintLib.h>

/*
    SnpReset

This function resets a network adapter and reinitializes it with the parameters that were provided in
the previous call to Initialize(). The transmit and receive queues are emptied and all pending
interrupts are cleared. Receive filters, the station address, the statistics, and the multicast-IP-to-HW
MAC addresses are not reset by this call. If the network interface was successfully reset, then
EFI_SUCCESS will be returned. If the driver has not been initialized, EFI_DEVICE_ERROR will
be returned.

Arguments:

SnpPtr          A pointer to the EFI_SIMPLE_NETWORK_PROTOCOL instance.
Verification    Indicates that the driver may perform a more exhaustive verification operation of the device during reset.

Return values:
    status of reset operation. EFI_SUCCESS if completed, error status otherwise

 */
EFI_STATUS EFIAPI SnpReset(IN EFI_SIMPLE_NETWORK_PROTOCOL* SnpPtr,
                           IN BOOLEAN Verification)
{
    EFI_STATUS Status;
    EFI_TPL SavedTpl;
    ENET_INFO("+SnpReset()\r\n");

    // Check Snp Instance

    if(SnpPtr == NULL)
    {
        ENET_ERROR( "--SnpReset() error null ptr\r\n");
        return EFI_INVALID_PARAMETER;
    }

    SavedTpl = gBS->RaiseTPL(ENETIMX6_TPL);

    // First check that driver has not already been initialized

    if(SnpPtr->Mode->State == EfiSimpleNetworkStarted)
    {
        ENET_WARNING("Warning: LANENET Driver not yet initialized\r\n");
        Status=EFI_DEVICE_ERROR;
        goto SnpRsetDone;
    } 
    else if(SnpPtr->Mode->State == EfiSimpleNetworkStopped)
    {
        ENET_WARNING("Warning: LANENET Driver not started\r\n");
        Status = EFI_NOT_STARTED;
        goto SnpRsetDone;
    }

    Status = RestartEnetController(SnpPtr);

    if(EFI_ERROR(Status))
    {
        ENET_ERROR("Warning: Restart ENET controller Failed: Hardware Error\r\n");
        Status = EFI_DEVICE_ERROR;
        goto SnpRsetDone;
    }

SnpRsetDone:
    gBS->RestoreTPL(SavedTpl);
    ENET_INFO( "--SnpReset()=%Xh\r\n", Status);
    return Status;
}

/*
    SetBlockDescrRegs

This function sets Enet network adapter registers to their proper values in order to function.

Arguments:

LanDriverPtr    A pointer to the Enet driver instance.

Return values:

    status of operation. EFI_SUCCESS if completed, error status otherwise

 */
EFI_STATUS SetBlockDescrRegs(IN LANENET_DRIVER* LanDriverPtr)
{
    EFI_STATUS Status=0;
    ENET_INFO("++SetBlockDescrRegs()\r\n");

    // RDSR points to the beginning of the circular receive BD in external
    // memory. This pointer must be 64-bit aligned (bits 2–0 must be zero); however, it is
    // recommended to be 128-bit aligned, that is, evenly divisible by 16.
    // This register must be initialized prior to operation.
    // bits 31–3 R_DES_START

    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->ERDSR, LanDriverPtr->RecvBDBase_Pa); // Set the receive and transmit BDs ring base to hardware registers(ERDSR & ETDSR)
    ENET_INFO(" SetBlockDescrRegs - check alignment for RDSR. Addr=%08Xh mod 16=%d\r\n", 
                LanDriverPtr->RecvBDBase_Pa, LanDriverPtr->RecvBDBase_Pa % 16);

    // TDSR provides a pointer to the beginning of the circular transmit DB queue
    // in external memory. This pointer must be 64-bit aligned (bits 2–0 must be zero);
    // however, it is recommended to be 128-bit aligned, that is, evenly divisible by 16.
    // This register must be initialized prior to operation.
    // bits 31–3 X_DES_START

    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->ETDSR, LanDriverPtr->SendBD_Pa); // As per buffer allocation
    ENET_INFO(" SetBlockDescrRegs - check alignment for TDSR. Addr=%08Xh mod 16=%d\r\n", 
            LanDriverPtr->SendBD_Pa, LanDriverPtr->SendBD_Pa % 16);

    // bits 10–4 R_BUF_SIZE. MRBR must be evenly divisible by 16

    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->EMRBR, ETHER_FRAME_MAX_LENGTH); // 1536
    ENET_INIT(" Buffer size=%d\r\n", ETHER_FRAME_MAX_LENGTH);

    ENET_INFO("--SetBlockDescrRegs()=%Xh\r\n", Status);
    return Status;                     
}

/*
    SnpShutdown

This function releases the memory buffers assigned in the Initialize() call. Pending transmits
and receives are lost, and interrupts are cleared and disabled. After this call, only the
Initialize() and Stop() calls may be used. If the network interface was successfully
shutdown, then EFI_SUCCESS will be returned. If the driver has not been initialized,
EFI_DEVICE_ERROR will be returned. 
    
Arguments

    SnpPtr  A pointer to the EFI_SIMPLE_NETWORK_PROTOCOL instance.

Status Codes Returned

    EFI_SUCCESS             The network interface was shutdown.
    EFI_NOT_STARTED         The network interface has not been started.
    EFI_INVALID_PARAMETER   This parameter was NULL or did not point to a valid EFI_SIMPLE_NETWORK_PROTOCOL structure.
    EFI_DEVICE_ERROR        The command could not be sent to the network interface.
 */
EFI_STATUS EFIAPI SnpShutdown(IN EFI_SIMPLE_NETWORK_PROTOCOL* SnpPtr)
{
    EFI_STATUS Status;
    UINT32 TempReg;
    EFI_TPL SavedTpl;
    LANENET_DRIVER* LanDriverPtr;
    ENET_INFO("+SnpShutdown()\r\n");

    // Check Snp Instance

    if(SnpPtr == NULL)
    {
        ENET_INFO("--SnpShutdown(ERR) null ptr\r\n");
        return EFI_INVALID_PARAMETER;
    }

    SavedTpl = gBS->RaiseTPL(ENETIMX6_TPL);
    LanDriverPtr = INSTANCE_FROM_SNP_THIS(SnpPtr); 

    // First check that driver has not already been initialized

    if(SnpPtr->Mode->State == EfiSimpleNetworkStarted)
    {
        ENET_ERROR("SnpShutdown ENET Driver not yet initialized\r\n");
        Status = EFI_DEVICE_ERROR;
        goto ShutdownDone;
    }
    else if(SnpPtr->Mode->State == EfiSimpleNetworkStopped)
    {
        ENET_ERROR("SnpShutdown Warning: ENET Driver not started\r\n");
        Status = EFI_NOT_STARTED;
        goto ShutdownDone;
    }

    ENET_INFO(" SnpShutdown - ENET disabled\r\n");
    Status = EFI_SUCCESS;

ShutdownDone:
    // release circular buffers for descriptors and individual buffers linked to them

    Status = ReleaseAdapterMemory(SnpPtr);
    if(Status != EFI_SUCCESS) 
    {
        ENET_ERROR("SnpShutdown: Error in ReleaseAdapterMemory\r\n");
        Status = EFI_OUT_OF_RESOURCES;
    }
    gBS->RestoreTPL(SavedTpl);

    // Back to the started and thus not initialized state

    SnpPtr->Mode->State = EfiSimpleNetworkStarted;

    ENET_INFO( "--SnpShutdown()=%Xh\r\n", Status);
    return Status;
}

/*
    RestartEnetController

This function restart Enet controller. 
    
Arguments

    SnpPtr  A pointer to the EFI_SIMPLE_NETWORK_PROTOCOL instance.

Status Codes Returned

    EFI_SUCCESS             The network interface was shutdown.
    EFI_NOT_STARTED         The network interface has not been started.
    EFI_INVALID_PARAMETER   This parameter was NULL or did not point to a valid EFI_SIMPLE_NETWORK_PROTOCOL structure.
    EFI_DEVICE_ERROR        The command could not be sent to the network interface.
 */
EFI_STATUS RestartEnetController(IN EFI_SIMPLE_NETWORK_PROTOCOL* SnpPtr)
{
    EFI_STATUS status = 0;
    UINT32 speed = 10;
    BOOLEAN fullduplex = FALSE;
    LANENET_DRIVER* LanDriverPtr;
    UINT32 RegValue=0;
    UINT32 MIIReg = 0;
    INT32 i,k = 0;
    UINT32 linkSpeed;
    UINT32 PhyReg;
    UINT32 MIIPhyAddr = 0;
    INT32 timeout = 500;
    UINT32 controlReg = 0;
    UINT32 recvControlReg = 0;
    CHAR8 abuffer[100]= { 0x0 };
    INTN charCount = 0;

    ENET_INIT("++RestartEnetController()\r\n");

    // steps from here on may be repeated whenever SNP needs to re-initlaize controller

    // Check Snp instance

    if(SnpPtr == NULL) 
    {
        ENET_ERROR("--RestartEnetController() null ptr\r\n");
        return EFI_INVALID_PARAMETER;
    }

    LanDriverPtr = INSTANCE_FROM_SNP_THIS(SnpPtr);

    // this function can be called when Enet controller can be in any state
    // to ensure consistent starting point, disable controller first

    DisableEnetController(LanDriverPtr);

    // clear out MAC filters

    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->IAUR, 0); 
    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->IALR, 0); 
    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->GAUR, 0); 
    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->GALR, 0); 

    // Set physical address - copy hw MAC addr into PA*R

    EnetSetMacAddress(LanDriverPtr, (EFI_MAC_ADDRESS*)&mZeroMac[0]);        
    CopyMem(&SnpPtr->Mode->CurrentAddress, (EFI_MAC_ADDRESS*)&mZeroMac[0], NET_ETHER_ADDR_LEN);      

    SetupEnetRegs(LanDriverPtr);

    // set MII clock speed 2.36 MHz                                           

    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->MSCR, 0xD << 1);

    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->OPD, 0x00010020);
    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->TFWR, 2);

    // set multicast address filter

    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->GAUR, 0); 
    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->GALR, 0); 

    // clear MIB RAM

    for(i = 0; i <= ENET_MIB_SEND_RAM_SIZE; i += 4)               // transmit side
    {
        MmioWrite32(((UINTN)&LanDriverPtr->enetRegisters->RMON_T_DROP_NI + i), 0x0);
    }

    for(i = 0; i <= ENET_MIB_RECV_RAM_SIZE; i += 4)               // receive side
    {
        MmioWrite32(((UINTN)&LanDriverPtr->enetRegisters->RMON_R_PACKETS + i), 0x0);
    }

    // FIFO receive start register - 2188000h + 150h, before RDSR. * UNDOCUMENTED *
    MmioWrite32((UINTN)0x2188150, 0x520);
    
    // set up size and address buffer registers

    status = SetBlockDescrRegs(LanDriverPtr);

    if(status != EFI_SUCCESS)
    {
        ENET_ERROR("RestartEnetController(ERROR) - SetBlockDescrRegs() failed!\r\n");
        goto RestartEnetCtrlDone;
    }

    // enable full duplex

    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->TCR,  (MmioRead32((UINTN)&LanDriverPtr->enetRegisters->TCR) | TCR_BIT2_FULLDPLX_EN) );

    // swap bytes in hardware

    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->ECR,  (MmioRead32((UINTN)&LanDriverPtr->enetRegisters->ECR) | ECR_BIT8_DESCBYTESWAP) ); 

    // set store and forward mode

    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->TFWR,  (MmioRead32((UINTN)&LanDriverPtr->enetRegisters->TFWR) | TFWR_BIT8_STORFWD) ); 

    // enable Enet controller

    status = EnableEnetController(LanDriverPtr); // do not start receiver yet
    if(status != EFI_SUCCESS)
    {
        ENET_ERROR("RestartEnetController(ERROR) - EnableEnetController() failed!\r\n");
        goto RestartEnetCtrlDone;
    }

    ENET_INIT("RestartEnetController() restarting ENET PHY\r\n");

    // wait if the link is up and autonegotation is in progress
    // i.e. we are capable and it is not completed yet

    status = PHYRead32(LanDriverPtr, MII_REG_SR, &PhyReg);
    if(status != EFI_SUCCESS)
    {
        ENET_ERROR("RestartEnetController(ERROR) - PHYRead32() failed!\r\n");
        goto RestartEnetCtrlDone;
    }

    if((PhyReg & MII_SR_BIT3_ANEG_CAP) != 0x0 )
    {
        if((PhyReg & MII_SR_BIT5_ANEG_COMPLETE_ACK) == 0x0 )
        {
            ENET_INIT("RestartEnetController() waiting for autonegotation to complete....\r\n");

            // per IEEE spec PHY negotiation should not take longer than 1/2 second
            // but for ENET to negotiate Gigabit link speed it may take longer
            timeout = 3500; 

            while((PhyReg & MII_SR_BIT5_ANEG_COMPLETE_ACK) == 0x0 && ((timeout--) != 0))
            {
                MicroSecondDelay(1000);
                status = PHYRead32(LanDriverPtr, MII_REG_SR, &PhyReg);
                if(status != EFI_SUCCESS)
                {
                    ENET_ERROR("RestartEnetController(ERROR) - PHYRead32() failed!\r\n");
                    goto RestartEnetCtrlDone;
                }

                if(timeout % 250 == 0)
                {
                    SerialPrint(".");
                }
            }
            SerialPrint("\r\n");

            if(timeout == 0)
            {
                // connection timed out

                ENET_ERROR("RestartEnetController(ERROR) Link autonegotation time out! \r\n");
                status = EFI_DEVICE_ERROR;     // do not return EFI_TIMEOUT or EFI_NOT_READY, otherwise SNP will call us again
                goto RestartEnetCtrlDone;
            }
        }

        ENET_INIT("RestartEnetController() Link autonegotation completed.\r\n");

        // read the link register 2nd time to clear latched state

        status = PHYRead32(LanDriverPtr, MII_REG_SR, &PhyReg);

        if((PhyReg & MII_SR_BIT2_LINK_STATUS) != 0x0)
        {
            // link already is up
            ENET_INIT("RestartEnetController() Link already up\r\n");		
        }
        else
        {
            // still no link
            ENET_ERROR("RestartEnetController() NO Link \r\n");
            charCount = AsciiSPrint(abuffer, sizeof(abuffer),"iMX6 Ethernet - NO connection. Check cable\r\n");
            SerialPortWrite((UINT8*)abuffer, charCount);
            status = EFI_DEVICE_ERROR;
            goto RestartEnetCtrlDone;
        }
    }
    else
    {
        // NOTE: this is not the case on iMX6 ENET controller PHYs.

        SerialPrint("not ANEG capable PHY. \r\n");
    }

    // parse link to find out its speed and duplex 

    status = PHYRead32(LanDriverPtr, MII_REG_SR, &PhyReg);

    if((PhyReg & MII_SR_BIT3_ANEG_CAP) != 0x0)
    {
        UINT32 gigaBitStatusReg = 0;
        UINT32 gigaBitControlReg = 0;
        UINT32 gigaBitLpa = 0;
        UINT32 Lpa = 0;
        UINT32 MiiLpa = 0;
        ENET_INIT("RestartEnetController() PHY is auto-neg capable\r\n");

        // check gigabit capability

        if((PhyReg & MII_SR_BIT0_EXT_CAP_REG_IMPL) != 0x0)
        {
            ENET_INIT("RestartEnetController() MII extended capability register present.\r\n");

            // get a list of states supported both by Enet and PHY
            // check if Gigabit is supported

             status = PHYRead32(LanDriverPtr, MII_REG_1000BASET_STS, &gigaBitStatusReg);

             if(status != EFI_SUCCESS)
             {
                ENET_WARNING("RestartEnetController() Ignoring gigabit capability\r\n");
             }
             else
             {
                ENET_INIT("RestartEnetController() gigaBitStatusReg=%08Xh\r\n", gigaBitStatusReg);
                gigaBitLpa = gigaBitStatusReg;
             }

             status = PHYRead32(LanDriverPtr, MII_REG_1000BASET_CRL, &gigaBitControlReg);
             ENET_INIT("RestartEnetController() gigaBitControlReg=%08Xh\r\n", gigaBitControlReg);

             gigaBitLpa &= gigaBitControlReg << 2;
             ENET_INIT("RestartEnetController() gigaBitLpa=%08Xh\r\n", gigaBitLpa);
         }

         // set baseline to minimal possible confit - 10Baset 1/2 duplex

         speed = 10;
         fullduplex = FALSE;

         // check gigabit fields

        if( (gigaBitLpa & (MII_GCR_BIT11_1000BASETFULDPLX_CAP | MII_GCR_BIT10_1000BASETXHAFLDPLX_CAP)) != 0x0 )
        {
            speed = 1000;

            if((gigaBitLpa & MII_GCR_BIT11_1000BASETFULDPLX_CAP) != 0x0)
            {
                fullduplex = TRUE;
            }
            ENET_INIT("RestartEnetController() Speed 1 GBit/s %a auto\r\n", fullduplex == TRUE? " Full" : "Half");
            goto LinkUpdateDone;
        }

        status = PHYRead32(LanDriverPtr, MII_REG_ANAR, &Lpa);
        status = PHYRead32(LanDriverPtr, MII_REG_ANLPAR, &MiiLpa);

         if((Lpa & (MII_PAR_BIT8_TX_FDX | MII_PAR_BIT7_HDX)) != 0x0)
         {
            speed = 100;

            if((Lpa & MII_PAR_BIT8_TX_FDX) != 0x0)
            {
                fullduplex = TRUE;
            }
            ENET_INIT("RestartEnetController() Speed 100 Mbit/s %a auto\r\n", fullduplex == TRUE? " Full" : "Half");
         }
         else
         {
            ENET_INFO("RestartEnetController() Speed 10 Mbit/s auto\r\n");
            speed = 10;
         }
    }
    else   // ANEG not capable, set link speed manually
    {
        ENET_INIT("RestartEnetController() PHY cannot auto-negotiate\r\n");

        fullduplex = FALSE;
        status = PHYRead32(LanDriverPtr, MII_REG_CR, &PhyReg);
        speed = 10;

        if((PhyReg & MII_CR_BIT8_DUPLEX_MODE) != 0x0)
        {
            fullduplex = TRUE;
        }

        if((PhyReg & 0x40) != 0x0)
        {
            speed = 1000;
        }
        else if((PhyReg & 0x2000) != 0x0)
        {
            speed = 100;
        }
        ENET_INIT("RestartEnetController() Speed %d Mbit/s %s\r\n", speed, fullduplex == TRUE? " Full" : "Half");
    }

LinkUpdateDone:

    if(FALSE == fullduplex)
    {
        ENET_INIT("RestartEnetController() set Transmitter in half Duplex\r\n");
        MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->TCR, (MmioRead32((UINTN)&LanDriverPtr->enetRegisters->TCR) & ~TCR_BIT2_FULLDPLX_EN) ); 
    }

    charCount = AsciiSPrint(abuffer, sizeof(abuffer),"iMX6 Ethernet connected at %d MBit %a Duplex\r\n", 
                speed, fullduplex == TRUE? "Full" : "Half");
    SerialPortWrite((UINT8*)abuffer, charCount);

    controlReg = MmioRead32((UINTN)&LanDriverPtr->enetRegisters->ECR);
    recvControlReg = MmioRead32((UINTN)&LanDriverPtr->enetRegisters->RCR);

    if(speed == 1000)
    {
        ENET_INIT("RestartEnetController() enable Gigabit speed in ECR\r\n");
        MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->ECR,  controlReg |= ECR_BIT5_GIGABITSPD);
    }
    else 
    {
         MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->ECR,  controlReg &= ~ECR_BIT5_GIGABITSPD);
#if (defined RMII_MODE) || (defined MII_MODE)
        
        if(speed == 10)
        {
            ENET_INIT("RestartEnetController() enable 10Mbit speed in RCR\r\n");
            recvControlReg |= 0x200;
            MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->RCR,  recvControlReg | RCR_BIT9_RMII_10T);
        }
        else
        {
            // speed 100
            ENET_INIT("RestartEnetController() default 100 Mbit speed \r\n");
            MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->RCR,  recvControlReg & ~RCR_BIT9_RMII_10T);
        }
#endif
    }

    // start receiver and transmitter
    StartReceiver(LanDriverPtr);
    StartTransmitter(LanDriverPtr);

    // delay 100 msec
    MicroSecondDelay(10000);

RestartEnetCtrlDone:
 
    DumpEnetRegs(LanDriverPtr);
    DumpPHYRegs(LanDriverPtr);

    ENET_INIT("--RestartEnetController()=%Xh\r\n", status );
    return status;
}
