/*

Copyright (c) Microsoft Corporation. All rights reserved.

This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

File name:

    DxeUtil.c

Abstract:

    implements Ethernet MAC (ENET) helper functions
*/

#include "EnetDxe.h"
#include <iMX6.h>
#include <iMX6ClkPwr.h>
#include <Library/TimerLib.h>
#include <Library/UncachedMemoryAllocationLib.h>
#include <Library/CacheMaintenanceLib.h>
extern EFI_PHYSICAL_ADDRESS ConvertToPhysicalAddress(IN VOID* VirtualAddress);

// Most common CRC32 Polynomial for little endian machines
#define CRC_POLYNOMIAL 0xEDB88320
#define HASH_BITS 6

/*++
Routine Description:
    Allocate all the memory for Block Decriptors, send and receive buffers

Arguments:

    SnpPtr     Pointer to our SNP adapter instance
Return Values:

    EFI_SUCCESS or error Status    
--*/
EFI_STATUS AllocAdapterMemory(IN EFI_SIMPLE_NETWORK_PROTOCOL* SnpPtr)
{
    EFI_STATUS Status = 0;
    LANENET_DRIVER* LanDriverPtr;
    INTN k = 0, j = 0;
    volatile ENET_BD* OneBDPtr = NULL;

    ENET_INFO("++AllocAdapterMemory(UNcached)\r\n");

    LanDriverPtr = INSTANCE_FROM_SNP_THIS(SnpPtr);

    // Allocated memory for ENET peripheral Receive Descriptors Table(ENET_RxBDT). 
    // Note: This memory must be 8 bytes aligned!
        
    LanDriverPtr->RecvBDs_Size = LANENET_RX_RING_NUM_ENTRIES * sizeof(ENET_BD);

    // note: uboot does roundup(size)

    LanDriverPtr->RecvBDBasePtr = UncachedAllocateAlignedPool(LanDriverPtr->RecvBDs_Size, IMX6_CACHE_ALIGN_SIZE);

    if(LanDriverPtr->RecvBDBasePtr == NULL) 
    {
        ENET_ERROR("--AllocAdapterMemory()=no res for Rx ring\r\n");
        return EFI_OUT_OF_RESOURCES;
    }
    ASSERT(!((UINT32)LanDriverPtr->RecvBDBasePtr & 0x7));   // This memory must be 8 bytes aligned!

    ENET_INFO("AllocAdapterMemory() recv descriptors at %08Xh va - %d blocks of %d bytes\r\n", LanDriverPtr->RecvBDBasePtr, 
                LANENET_RX_RING_NUM_ENTRIES, sizeof(ENET_BD));

    LanDriverPtr->RecvBDBase_Pa = (UINT32)ConvertToPhysicalAddress((VOID*)LanDriverPtr->RecvBDBasePtr);

    ENET_INFO("  recv ring starts at %08Xh virt %08Xh phys\r\n", LanDriverPtr->RecvBDBasePtr, LanDriverPtr->RecvBDBase_Pa);
    
    // zero out all receive descriptors

    ZeroMem((VOID*)LanDriverPtr->RecvBDBasePtr, LanDriverPtr->RecvBDs_Size);

    OneBDPtr = LanDriverPtr->RecvBDBasePtr;

    for(k = 0; k < LANENET_RX_RING_NUM_ENTRIES; k++, OneBDPtr++)
    {
        LanDriverPtr->RecvBDPtrs[k] = OneBDPtr;

        // note: uboot does roundup on size

        LanDriverPtr->RxBuffersPtr[k]  = (UINT8*)UncachedAllocateAlignedPool(ETHER_FRAME_MAX_LENGTH, IMX6_CACHE_ALIGN_SIZE);

        if(LanDriverPtr->RxBuffersPtr[k] == NULL) 
        {
            ENET_ERROR("--AllocAdapterMemory()=no res for Rx buffer[%d]\r\n", k);
            return EFI_OUT_OF_RESOURCES;
        }

        // compute physical memory address (for DMA) from virtual
        // and save physical address into RxBD

        OneBDPtr->BufferAddressPA = (UINT32)ConvertToPhysicalAddress((VOID*)LanDriverPtr->RxBuffersPtr[k]);

        ENET_INFO("     recvbuf[%d]=%08Xh virt %08Xh phys; size=%d\r\n",k, LanDriverPtr->RxBuffersPtr[k], 
                        OneBDPtr->BufferAddressPA, ETHER_FRAME_MAX_LENGTH);

        // Mark the last RBD to close the ring

        if(k == LANENET_RX_RING_NUM_ENTRIES-1)
        {
            ENET_INFO("AllocAdapterMemory() closed Rx ring buffer at [%d]\r\n", k);
            CleanOneBlockDescriptor_Rx(OneBDPtr, TRUE);
        }
        else
        {
            CleanOneBlockDescriptor_Rx(OneBDPtr, FALSE);
        }

        // verify physcial memory in Tx buffer is addressable

        ENET_INFO("AllocAdapterMemory() verify Rx buffer[%d] memory access\r\n", k);
        for(j = 0; j<ETHER_FRAME_MAX_LENGTH; j += 4)
        {
            MmioWrite32(OneBDPtr->BufferAddressPA + j, 0);
        }

    } // end FOR loop for number of elements in recv ring buffer
    
    LanDriverPtr->Rbd_index = 0;

    // Allocate memory for ENET peripheral Transmit Descriptors Table(ENET_TxBDT). 
    // Note: This memory must be 8 bytes aligned!

    LanDriverPtr->SendBDs_Size = LANENET_TX_RING_NUM_ENTRIES * sizeof(ENET_BD);

    LanDriverPtr->SendBDBasePtr = UncachedAllocateAlignedPool(LanDriverPtr->SendBDs_Size, IMX6_CACHE_ALIGN_SIZE);

    if (LanDriverPtr->SendBDBasePtr == NULL) 
    {
        ENET_ERROR("--AllocAdapterMemory()=no res for Tx ring\r\n");
        return EFI_OUT_OF_RESOURCES;
    }

    // zero out all transmit descriptors

    ZeroMem((VOID*)LanDriverPtr->SendBDBasePtr, LanDriverPtr->SendBDs_Size);

    LanDriverPtr->SendBD_Pa = (UINT32)ConvertToPhysicalAddress((VOID*)LanDriverPtr->SendBDBasePtr);
    
    ENET_INFO("  send ring starts at: %08Xh virt, %08Xh phys\r\n",LanDriverPtr->SendBDBasePtr, LanDriverPtr->SendBD_Pa);

    OneBDPtr = LanDriverPtr->SendBDBasePtr;

    for(k = 0; k < LANENET_TX_RING_NUM_ENTRIES; k++, OneBDPtr++)
    {
        LanDriverPtr->SendBDBPtrs[k] = OneBDPtr;

        LanDriverPtr->TxBuffersPtr[k]  = (UINT8*)UncachedAllocateAlignedPool(ETHER_FRAME_MAX_LENGTH, IMX6_CACHE_ALIGN_SIZE);

        if(LanDriverPtr->TxBuffersPtr[k] == NULL) 
        {
            ENET_ERROR("--AllocAdapterMemory()=no res for Tx buffer[%d]\r\n", k);
            return EFI_OUT_OF_RESOURCES;
        }

        OneBDPtr->BufferAddressPA = (UINT32)ConvertToPhysicalAddress((VOID*)LanDriverPtr->TxBuffersPtr[k]);

        // Mark the last RBD to close the ring

        if(k == LANENET_TX_RING_NUM_ENTRIES - 1)
        {
            ENET_INFO("AllocAdapterMemory() closed Tx ring buffer at [%d]\r\n", k);
            CleanOneBlockDescriptor_Tx(OneBDPtr, TRUE);
        }
        else
        {
            CleanOneBlockDescriptor_Tx(OneBDPtr, FALSE);
        }
        
        // verify physcial memory in Tx buffer is addressable

        ENET_INFO("AllocAdapterMemory() verify Tx buffer[%d] memory access\r\n", k);
        for(j = 0; j<ETHER_FRAME_MAX_LENGTH; j += 4)
        {
            MmioWrite32(OneBDPtr->BufferAddressPA + j, 0);
        }

        ENET_INFO("    sendbuf[%d]=%08Xh virt %08Xh phys size=%d\r\n",k, LanDriverPtr->TxBuffersPtr[k], 
                    OneBDPtr->BufferAddressPA, ETHER_FRAME_MAX_LENGTH);

    } // end FOR loop for number of elements in send ring buffer

    LanDriverPtr->tbd_index = 0;

    ENET_INFO("--AllocAdapterMemory()=%Xh\r\n",Status);
    return Status;
}

/*++
Routine Description:
   Cleans one receive Block Decriptor

Arguments:

    BDPtr     Pointer to block descriptor
Return Values:

    EFI_SUCCESS or error status

--*/
EFI_STATUS CleanOneBlockDescriptor_Rx(IN volatile ENET_BD* BDPtr, IN BOOLEAN IsLast)
{
    EFI_STATUS Status = 0;
    UINT16 CtrlStatus = BD_ENET_RX_EMPTY;
    ENET_INFO("++CleanOneBlockDescriptor_Rx()\r\n");
    if(BDPtr == NULL)
    {
        Status = EFI_INVALID_PARAMETER;
        ENET_ERROR(" CleanOneBlockDescriptor_Rx() error - null ptr\r\n");
    }
    else
    {
        if(IsLast == TRUE)
        {
            CtrlStatus |= BD_ENET_RX_WRAP;
        }
        BDPtr->ControlStatus = CtrlStatus;
        BDPtr->DataLen = (UINT16)0;
    }
    ENET_INFO("--CleanOneBlockDescriptor_Rx()=%Xh\r\n",Status);
    return Status;
}

/*++
Routine Description:
   Cleans one transmit Block Decriptor

Arguments:

    BDPtr     Pointer to block descriptor
Return Values:

    EFI_SUCCESS or error status

--*/

EFI_STATUS CleanOneBlockDescriptor_Tx(IN volatile ENET_BD* BDPtr, IN BOOLEAN IsLast)
{
    EFI_STATUS Status = 0;
    UINT16 CtrlStatus = 0;
    ENET_INFO("++CleanOneBlockDescriptor_Tx()\r\n");

    if(BDPtr == NULL)
    {
        Status = EFI_INVALID_PARAMETER;
        ENET_ERROR(" CleanOneBlockDescriptor_Tx() error - null ptr\r\n");
    }
    else
    {
        if(IsLast == TRUE)
        {
            CtrlStatus |= BD_ENET_TX_WRAP;
        }
        BDPtr->ControlStatus = CtrlStatus;
        BDPtr->DataLen = (UINT16)0;
    }
    ENET_INFO("--CleanOneBlockDescriptor_Tx()=%Xh\r\n",Status);
    return Status;
}

/*++
Routine Description:
   Releases all allocated SNP adapter memory

Arguments:

    SnpPtr     Pointer to SNP adapter instance
Return Values:

    EFI_SUCCESS or error status

--*/

EFI_STATUS ReleaseAdapterMemory(IN EFI_SIMPLE_NETWORK_PROTOCOL* SnpPtr)
{
    EFI_STATUS Status = 0;
    INT32 RxBD_Index;
    INT32 TxBD_Index;
    UINT8* pMem;
    LANENET_DRIVER* LanDriverPtr;
    ENET_INFO("++ReleaseAdapterMemory()\r\n");

    LanDriverPtr = INSTANCE_FROM_SNP_THIS(SnpPtr); 
    
    // release all rx buffers

    for(RxBD_Index = 0; RxBD_Index < LANENET_RX_RING_NUM_ENTRIES; RxBD_Index++)
    {
        if(LanDriverPtr->RxBuffersPtr[RxBD_Index] != NULL)
        {
            UncachedFreeAlignedPool((VOID*)LanDriverPtr->RxBuffersPtr[RxBD_Index]);

            ENET_INFO(" ReleaseAdapterMemory() freed recvbuf[%d]=%08Xh size=%d\r\n",RxBD_Index, LanDriverPtr->RxBuffersPtr[RxBD_Index], 
                            LanDriverPtr->RecvBDs_Size);
            LanDriverPtr->RxBuffersPtr[RxBD_Index] = NULL;
        }
        
    } // end FOR loop for number of elements in recv ring buffer

    // release all rx BD descriptors as one chunk

    UncachedFreeAlignedPool((VOID*)LanDriverPtr->RecvBDBasePtr);

    // release memory of all tx buffers

    for(TxBD_Index = 0; TxBD_Index < LANENET_TX_RING_NUM_ENTRIES; TxBD_Index++)
    {
        if(LanDriverPtr->TxBuffersPtr[TxBD_Index] != NULL)
        {
            UncachedFreeAlignedPool((VOID*)LanDriverPtr->TxBuffersPtr[TxBD_Index]);

            ENET_INFO(" ReleaseAdapterMemory() freed sendbuf[%d]=%08Xh size=%d\r\n",TxBD_Index,  LanDriverPtr->TxBuffersPtr[TxBD_Index], 
                    ETHER_FRAME_MAX_LENGTH);
            LanDriverPtr->TxBuffersPtr[TxBD_Index] = NULL;
        }
    }

    // release all tx BD descriptors as one chunk

    UncachedFreeAlignedPool((VOID*)LanDriverPtr->SendBDBasePtr);

    ENET_INFO("--ReleaseAdapterMemory()=%Xh\r\n",Status);
    return Status;
}

/*++
Routine Description:
   Initializes Enet controller. Leaves fully configured for use but in disabled state.

Arguments:

    SnpPtr     Pointer to SNP adapter instance
Return Values:

    EFI_SUCCESS or error status

--*/
EFI_STATUS InitializeAndSetupEnetController(IN EFI_SIMPLE_NETWORK_PROTOCOL* SnpPtr)
{
    EFI_STATUS Status = 0;
    INT32 timeout = 500;
    UINT32 RegValue = 0;
    UINT32 MIIReg = 0;
    LANENET_DRIVER* LanDriverPtr;
    IMX_CLOCK_GATE_STATE gateState;
    INT32 i,k = 0;
    UINT32 linkSpeed;
    UINT32 PhyReg;
    UINT32 MIIPhyAddr = 0;

    ENET_INIT("++InitializeAndSetupEnetController()\r\n");

    // Check Snp instance

    if(SnpPtr == NULL) 
    {
        ENET_ERROR("--InitializeAndSetupEnetController() null ptr\r\n");
        return EFI_INVALID_PARAMETER;
    }

    LanDriverPtr = INSTANCE_FROM_SNP_THIS(SnpPtr);
    LanDriverPtr->PhyAddress = 0;   

    // turn on ENET clock

    ImxClkPwrSetClockGate(IMX_ENET_CLK_ENABLE, IMX_CLOCK_GATE_STATE_ON);
    MicroSecondDelay(10);
   
    gateState = ImxClkPwrGetClockGate(IMX_ENET_CLK_ENABLE);

    if(gateState == IMX_CLOCK_GATE_STATE_OFF)
    {
	    ENET_ERROR(" failed to enable clocks for ENET\r\n");
	    ASSERT(FALSE);
    }
    ENET_INIT(" ENET clock enabled\r\n");

    // UEFI pin muxing is not entirely clean yet
    // restore/set pin muxing for Enet module - IOMUXC_SW_PAD_CTL_PAD_ENET_REF_CLK

    MmioWrite32(IOMUXC_SW_PAD_CTL_PAD_ENET_REF_CLK_ADR, IOMUXC_SW_PAD_CTL_PAD_ENET_REF_CLK_VAL);

    // intialization sequence for iMX6 Enet controller
    // set MII clock speed 2.36 MHz 

    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->MSCR, 0xD << 1); // 1Ah

    ENET_INIT(" PHY clock enabled\r\n");

    Status = PHYRead32(LanDriverPtr, MII_REG_PHYID1, &PhyReg); // 4d
    if(Status != EFI_SUCCESS)
    {
        Status=EFI_TIMEOUT;
        ENET_ERROR(" InitializeAndSetupEnetController() MII failed read PhyId1\r\n");
        goto EndInitSetupCtrl;
    }
    LanDriverPtr->PhyId = (PhyReg & MMI_DATA_MASK) << 16;

    Status = PHYRead32(LanDriverPtr, MII_REG_PHYID2, &PhyReg); // d072
    if(Status != EFI_SUCCESS)
    {
        Status = EFI_TIMEOUT;
        ENET_ERROR(" InitializeAndSetupEnetController() MII failed read PhyId2\r\n");
        goto EndInitSetupCtrl;
    }
    LanDriverPtr->PhyId |= (PhyReg & MMI_DATA_MASK);

    // that gives full PHY id (and assume address is 0)

    ENET_INIT(" InitializeAndSetupEnetController() PHY detected Id=%04Xh\r\n", LanDriverPtr->PhyId);

    // put ENET controller into reset state

    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->ECR, (MmioRead32((UINTN)&LanDriverPtr->enetRegisters->ECR) | ECR_BIT0_RESET)); 

    timeout = 1000;
    // wait till bit 0 becomes 0 - then ENET reset is complete 
    // If time taken exceeds 100us, then there was an error condition

    while( ((MmioRead32((UINTN)&LanDriverPtr->enetRegisters->ECR) & ECR_BIT0_RESET) != 0) && (--timeout != 0))
    {
        MicroSecondDelay(1);
    }

    // wait for reset to complete
  
    if(timeout == 0) 
    {
        Status = EFI_TIMEOUT;
        ENET_ERROR(" InitializeAndSetupEnetController() ENET reset timed out\r\n");
        goto EndInitSetupCtrl;
    }
    ENET_INIT(" in reset\r\n");

    // set up some Enet controller registers

    SetupEnetRegs(LanDriverPtr);

    // again set MII speed 

    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->MSCR, 0xD << 1); // 1Ah

    // reset PHY

    Status = PHYRead32(LanDriverPtr, MII_REG_CR, &PhyReg);
    PhyReg |= MII_CR_BIT15_RESET; 

    Status = PHYWrite32(LanDriverPtr, MII_REG_CR, PhyReg);

    // wait for reset to commplete - Poll the control register for the reset bit to go to 0 (it is
	// auto-clearing).  This should happen within 0.5 seconds per IEEE

    timeout = 500;
    while((PhyReg & MII_CR_BIT15_RESET) && (timeout--) !=0 )
    {
        Status = PHYRead32(LanDriverPtr, 0, &PhyReg);

        if(Status != EFI_SUCCESS)
        {
	        ENET_ERROR(" InitializeAndSetupEnetController() PHY read error\r\n");
	        goto EndInitSetupCtrl;
        }
        MicroSecondDelay(1000);
    }

    if(timeout == 0)
    {
	    ENET_ERROR(" InitializeAndSetupEnetController() PHY reset timed out\r\n");
	    goto EndInitSetupCtrl;
	}
    ENET_INIT("InitializeAndSetupEnetController PHY was reset\r\n");

    // configure specific PHY model - AR8035 on HumminboardEdge

    switch(LanDriverPtr->PhyId)
    {
        case 0x00221621: // KSZ9031
        ENET_INIT("Additional init for PHY KSZ9031 - TODO\r\n");
        break;

        case  0x004DD072: // AR8035 - on HummingboardEdge
        ENET_INIT("Additional init for PHY AR8035\r\n");

        // To enable AR8035 ouput a 125MHz clk from CLK_25M 
            
        Status = PHYWrite32(LanDriverPtr, 0xD, 0x0007);
        Status = PHYWrite32(LanDriverPtr, 0xE, 0x8016);
        Status = PHYWrite32(LanDriverPtr, 0xD, 0x4007);
        Status = PHYRead32(LanDriverPtr, 0xE, &PhyReg);
        Status = PHYWrite32(LanDriverPtr, 0xE,  (PhyReg | 0x0018));
        Status = PHYWrite32(LanDriverPtr, 0x1D, 0x0005);
        Status = PHYRead32(LanDriverPtr, 0x1E, &PhyReg);
        Status = PHYWrite32(LanDriverPtr, 0x1E,  (PhyReg | 0x0100));
        break;

        case 0x004DD074: // AR8031
        ENET_INIT("Additional init for PHY AR8031 - TODO\r\n");
        break;
        
        case 0x001cc915: // RTL8211E Add by kmslove, for WAD-MX6W
        Status=PHYWrite32(LanDriverPtr, 0x00, 0x3140); 
        Status=PHYWrite32(LanDriverPtr, 0x00, 0x3340);
        break;

        case 0x00221611: // KSZ9021 - on Sabre
        ENET_INIT("Additional init for PHY KSZ9021 - TODO\r\n");
        // TODO
        break;

        default: // unknown
        ENET_INIT("External PHY model is unknown=%08Xh - no additional init\r\n", LanDriverPtr->PhyId);
        break;
    }
   
    // configure phy
    // restart auto-negotiation or write CR

    // Writes MII_ADVERTISE with the appropriate values

    Status = PHYRead32(LanDriverPtr, MII_REG_ANAR, &PhyReg);

    Status = PHYWrite32(LanDriverPtr, MII_REG_ANAR, 0x11E1);

    // Configure gigabit if it's supported 

    Status = PHYRead32(LanDriverPtr, MII_REG_1000BASET_CRL, &PhyReg);

    PhyReg |= (MII_GCR_BIT9_1000HAFLDPLX_CAP | MII_GCR_BIT8_1000FLDPLX_CAP);

    Status = PHYWrite32(LanDriverPtr, MII_REG_1000BASET_CRL, PhyReg);

    Status = PHYRead32(LanDriverPtr, MII_REG_CR, &PhyReg);
    if((PhyReg & MII_CR_BIT12_ANEG_ENABLE) == 0x0 || (PhyReg & MII_CR_BIT10_MII_DISABLE_PHY_ISOLATE) != 0x0)
    {
        PhyReg |= (MII_CR_BIT12_ANEG_ENABLE | MII_CR_BIT9_AUTONEG_RESET); // enable and restart aneg
        PhyReg &= ~(MII_CR_BIT10_MII_DISABLE_PHY_ISOLATE);                // do not isolate phy

        Status = PHYWrite32(LanDriverPtr, MII_REG_CR, PhyReg);
    }

    // perform phy reset

     Status = PHYRead32(LanDriverPtr, MII_REG_CR, &PhyReg);
     PhyReg |= MII_CR_BIT15_RESET;

    Status = PHYWrite32(LanDriverPtr, MII_REG_CR, PhyReg);

    // read phy reg[0] - Poll the control register for the reset bit to go to 0

    Status = PHYRead32(LanDriverPtr, MII_REG_CR, &PhyReg);

    timeout = 500;
    while((PhyReg & MII_CR_BIT15_RESET) && (timeout--) != 0)
    {
        Status = PHYRead32(LanDriverPtr, MII_REG_CR, &PhyReg);

        if(Status != EFI_SUCCESS)
        {
	        ENET_ERROR(" InitializeAndSetupEnetController() PHY read error\r\n");
	        goto EndInitSetupCtrl;
        }
        MicroSecondDelay(1000);
    }

    if(timeout == 0)
    {
	    ENET_ERROR(" InitializeAndSetupEnetController() PHY reset timed out\r\n");
	    goto EndInitSetupCtrl;
	}
    ENET_INIT("InitializeAndSetupEnetController PHY reset complete\r\n");

    // get hw MAC addr from OCOTP registers

    EnetGetMacAddressFromFuses(SnpPtr, (EFI_MAC_ADDRESS*)&mZeroMac[0]);

    // one-time intialization complete. Controller left disabled
        
EndInitSetupCtrl:
    ENET_INIT("--InitializeAndSetupEnetController()=%Xh\r\n", Status);
    return Status;
}

/*
    NvData

    This function performs read and write operations on the NVRAM device attached to a network
interface. If ReadWrite is TRUE, a read operation is performed. If ReadWrite is FALSE, a write
operation is performed.

Arguments

    ObjPtr      pointer to the EFI_SIMPLE_NETWORK_PROTOCOL instance.
    read_write  TRUE for read operations, FALSE for write operations.
    offset      Byte offset in the NVRAM device at which to start the read or write operation. This must be a multiple of NvRamAccessSize and less than NvRamSize. (See EFI_SIMPLE_NETWORK_MODE)
    buff_size   The number of bytes to read or write from the NVRAM device. This must also be a multiple of NvramAccessSize.
    dataPtr     pointer to the data buffer.

Retruns:
    EFI_SUCCESS or operation error status
 */
EFI_STATUS EFIAPI SnpNvData(IN EFI_SIMPLE_NETWORK_PROTOCOL* ObjPtr,
                            IN BOOLEAN read_write,
                            IN UINTN offset,
                            IN UINTN buff_size,
                            IN OUT VOID* dataPtr)
{
    ENET_INFO("+-SnpNvData()\r\n");

    return EFI_UNSUPPORTED;
}

/*
    GenerateHash

    This function computes hash on given MAC address.

Arguments

    MacPtr     pointer to MAC address

Retruns:
    hash value
 */
UINT8 GenerateHash(IN EFI_MAC_ADDRESS* MacPtr)
{
    UINT8 hash = 0;
    UINT32 CRC = 0xFFFFFFFF;    // standard seed for Ethernet
    UINT8 AddrByte;
    INT32 byte, bit;
    UINT8* AddrBytePtr = (UINT8*)MacPtr;
    ENET_INFO("++GenerateHash()\r\n");

    for(byte = 0; byte < NET_ETHER_ADDR_LEN; byte++) 
    {
        AddrByte = *AddrBytePtr++;

        for(bit = 0; bit < 8; bit++, AddrByte >>= 1) 
        {
            CRC = (CRC >> 1) ^ (((CRC ^ AddrByte) & 1) ? CRC_POLYNOMIAL : 0);
        }
    }

    // The most significant 6 bits of the MAC address CRC constitute the hash
    // value of the MAC address.

    hash = (UINT8)((CRC >> (32 - HASH_BITS)) & 0x3F);

    ENET_INFO("--GenerateHash()=%02Xh\r\n", hash);
    return hash;
}

/*
    SetupEnetRegs

    This function sets up enet controller registers when controller is being prepared for use.
    Steps depend on which MII mode Enet driver is compiled in - MII, RMII or RGMII

Arguments

    LanDriverPtr     pointer to Enet driver instance

Retruns:
    EFI_SUCCESS or error status code
 */
EFI_STATUS SetupEnetRegs(IN LANENET_DRIVER* LanDriverPtr)
{
    EFI_STATUS retValue = 0;
    ENET_INIT("++SetupEnetRegs()\r\n");

    // set up some Enet controller registers 

    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->EIMR, 0);
    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->EIR, 0xFFFFFFFF);

    // select receiver control: RGMII mode(bit 6), flow control(bit5),  and bit2 - always set

#if (defined RGMII_MODE)
        ENET_INIT(" MAC configured for RGMII operation. 10/100/1000 possible\r\n");

        // if ECR BIT5=1 then 1000 Mbps, else 10/100 MBps

        MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->RCR, ((ETHER_FRAME_MAX_LENGTH << 16) | (RCR_BIT5_FLOWCTRL | RCR_BIT6_RGMII_EN)) );
#else 
        // BIT2 - MII or RMII mode, as indicated by the RMII_MODE field BIT8
        MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->RCR, ((ETHER_FRAME_MAX_LENGTH << 16) | (RCR_BIT5_FLOWCTRL | RCR_BIT2_MII_MODE)) );

#if (defined RMII_MODE)
        ENET_INIT(" MAC configured for RMII operation. 10/100 possible\r\n");
        MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->RCR, (MmioRead32((UINTN)&LanDriverPtr->enetRegisters->RCR) | RCR_BIT8_RMII_MODE) );

#else   // MII 
        ENET_INIT(" MAC configured for MII mode. 10/100 possible\r\n");
        MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->RCR, (MmioRead32((UINTN)&LanDriverPtr->enetRegisters->RCR) & ~RCR_BIT8_RMII_MODE) );
#endif
#endif

    // check - RCR reg value will be 05EE0064h for RGMII

    ENET_INFO("--SetupEnetRegs()=%02Xh\r\n", retValue);
    return retValue;
}

/*
    DumpEnetRegs

    This function prints Enet registers, used in this driver

Arguments

    LanDriverPtr     pointer to Enet driver instance

Retruns:
    EFI_SUCCESS or error status code
 */
VOID DumpEnetRegs(LANENET_DRIVER* LanDriverPtr)
{
    ENET_INIT("EIR=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->EIR));
    ENET_INIT("EIMR=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->EIMR));
    ENET_INIT("RDAR=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->RDAR));
    ENET_INIT("TDAR=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->TDAR));
    ENET_INIT("ECR=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->ECR));
    ENET_INIT("MMFR=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->MMFR));
    ENET_INIT("MSCR=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->MSCR));
    ENET_INIT("MIBC=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->MIBC));
    ENET_INIT("RCR=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->RCR));   // check MAX_FL vs buffer size in RAM
    ENET_INIT("TCR=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->TCR));
    ENET_INIT("PALR=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->PALR));
    ENET_INIT("PAUR=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->PAUR));
    ENET_INIT("OPD=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->OPD));
    ENET_INIT("IAUR=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->IAUR));
    ENET_INIT("IALR=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->IALR));
    ENET_INIT("GAUR=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->GAUR));
    ENET_INIT("GALR=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->GALR));
    ENET_INIT("TFWR=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->TFWR));
    ENET_INIT("RDSR=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->ERDSR));
    ENET_INIT("TDSR=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->ETDSR));
    ENET_INIT("MRBR=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->EMRBR));
    ENET_INIT("RSFL=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->RSFL));
    ENET_INIT("RSEM=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->RSEM));
    ENET_INIT("RAEM=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->RAEM));
    ENET_INIT("RAFL=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->RAFL));
    ENET_INIT("TSEM=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->TSEM));
    ENET_INIT("TAEM=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->TAEM));
    ENET_INIT("TAFL=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->TAFL));
    ENET_INIT("TIPG=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->TIPG));
    ENET_INIT("FTRL=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->FTRL)); // Must be greater than or equal to RCR[MAX_FL].
    ENET_INIT("TACC=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->TACC));
    ENET_INIT("RACC=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->RACC));
}

