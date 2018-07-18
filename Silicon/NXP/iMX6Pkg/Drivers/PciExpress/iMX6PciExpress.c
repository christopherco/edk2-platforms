/** @file
*
*  Copyright (c) Microsoft Corporation. All rights reserved.
*  Copyright (c) 2005 - 2016, Intel Corporation. All rights reserved.<BR>
*  (C) Copyright 2015 Hewlett Packard Enterprise Development LP<BR>
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

#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <IndustryStandard/Pci.h>

#include <Protocol/PciIo.h>
#include <Protocol/PciRootBridgeIo.h>

#include <iMX6.h>
#include <iMX6ClkPwr.h>
#include <iMX6IoMux.h>

#include "iMX6PciExpress.h"

PCI_RESOURCE PCIeResource[] =
{
    //
    // Memory resource
    //
    {
        PCIE_MEMORY_SPACE_BASE,
        PCIE_MEMORY_SPACE_SIZE,
        PCIE_MEMORY_SPACE_BASE
    },
};

//
// PCIe read and write function
//
EFI_STATUS PCIePciWrite (
    IN EFI_PCI_IO_PROTOCOL_WIDTH Width,
    IN UINTN Address,
    IN UINTN Count,
    IN VOID *Buffer
    );

EFI_STATUS PCIePciRead (
    IN EFI_PCI_IO_PROTOCOL_WIDTH Width,
    IN UINTN Address,
    IN UINTN Count,
    IN VOID *Buffer
    );

//
// Internal address translation unit configuration table. Map the PCIe device
// configuration baesd on configuration. PCI IO space is not supported on
// Windows. Memory space segment is just mapped back to the same address.
//
// The following table is used to setup basic translation setting on various
// ATU (Address Translation Unit). The ATU is responsible to retranslate
// address for inbound and outbound message.
//
// Address match mode address translation is based on the following formula :
//     Address = Address - Base Address + Target Address
//
// There really isnt a need to retranslate the address for iMX6 however proceed
// the program the ATU to for configuration and memory message.
//

IATU_SETTINGS iMX6iATUSettings[] =
{
    //
    // Configuration message
    //
    {
        OUTBOUND,
        0,
        CFG0_TYPE,
        PCIE_DEVICE_CONFIG_BASE_REG,
        0,
        PCIE_DEVICE_CONFIG_BASE_REG + PCIE_DEVICE_CONFIG_SIZE - 1,
        PCIE_DEVICE_CONFIG_BASE_REG,
        0,
        REGION_ENABLE,
    },

    //
    // Memory message
    //
    {
        OUTBOUND,
        2,
        MEMORY_TYPE,
        PCIE_MEMORY_SPACE_BASE,
        0,
        PCIE_MEMORY_SPACE_BASE + PCIE_MEMORY_SPACE_SIZE - 1,
        PCIE_MEMORY_SPACE_BASE,
        0,
        REGION_ENABLE,
    },
};

VOID PCIeSetupiATU (
    IN IATU_SETTINGS* SettingsPtr
    )
{
    volatile CSP_PCIE_PL_REGS* portLogicRegsPtr =
        (CSP_PCIE_PL_REGS*)PCIE_CTRL_PORT_LOGIG_BASE_REG;

    ASSERT(SettingsPtr->RegionIndex < MAX_iATU_REGION);

    //
    // Programs specific ATU region. Refer to the comment above
    // iMX6iATUSettings table for more detail.
    //
    MmioWrite32(
        (UINTN)&portLogicRegsPtr->PCIE_PL_iATUVR,
        (SettingsPtr->RegionDirection << 31 | SettingsPtr->RegionIndex));

    MmioWrite32(
        (UINTN)&portLogicRegsPtr->PCIE_PL_iATURC2,
        REGION_DISABLE);

    MmioWrite32(
        (UINTN)&portLogicRegsPtr->PCIE_PL_iATURLBA,
        SettingsPtr->LowerBaseAddr);

    MmioWrite32(
        (UINTN)&portLogicRegsPtr->PCIE_PL_iATURUBA,
        SettingsPtr->UpperBaseAddr);

    MmioWrite32(
        (UINTN)&portLogicRegsPtr->PCIE_PL_iATURLA,
        SettingsPtr->LimitAddr);

    MmioWrite32(
        (UINTN)&portLogicRegsPtr->PCIE_PL_iATURLTA,
        SettingsPtr->LowerTargetAddr);

    MmioWrite32(
        (UINTN)&portLogicRegsPtr->PCIE_PL_iATURUTA,
        SettingsPtr->UpperTargetAddr);

    MmioWrite32(
        (UINTN)&portLogicRegsPtr->PCIE_PL_iATURC1,
        SettingsPtr->Type);

    MmioWrite32(
        (UINTN)&portLogicRegsPtr->PCIE_PL_iATURC2,
        SettingsPtr->State);
}

VOID PCIeSetupiATUSettings (
    VOID
    )
{
    UINT32 i;

    //
    // Initialize internal address translation unit based on settings specify
    // in iMX6iATUSettings table.
    //
    for (i = 0; i < ARRAYSIZE (iMX6iATUSettings); ++i) {
        PCIeSetupiATU(&iMX6iATUSettings[i]);
    }

    return;
}

EFI_STATUS PCIeSetPhyState (
    IN BOOLEAN State
    )
{
    IMX_IOMUXC_GPR1_REG gpr1Reg;
    volatile IMX_IOMUXC_GPR_REGISTERS* ioMuxcGprRegisters =
        (IMX_IOMUXC_GPR_REGISTERS*)IOMUXC_GPR_BASE_ADDRESS;

    gpr1Reg.AsUint32 = MmioRead32((UINTN)&ioMuxcGprRegisters->GPR1);

    if (State == TRUE) {
        gpr1Reg.REF_SSP_EN = 1;     // Enable PCIe PHY
        gpr1Reg.TEST_POWERDOWN = 0; // Power down is not requested
    } else {
        gpr1Reg.REF_SSP_EN = 0;     // Disable PCIe PHY
        gpr1Reg.TEST_POWERDOWN = 1; // Power down is requested
    }

    MmioWrite32((UINTN)&ioMuxcGprRegisters->GPR1, gpr1Reg.AsUint32);

    return EFI_SUCCESS;
}

EFI_STATUS PCIeSetupInitSetting (
    VOID
    )
{
    EFI_STATUS status;
    IMX_IOMUXC_GPR1_REG gpr1Reg;
    volatile IMX_IOMUXC_GPR_REGISTERS* ioMuxcGprRegisters =
        (IMX_IOMUXC_GPR_REGISTERS*)IOMUXC_GPR_BASE_ADDRESS;

    //
    // If PCIe PHY is already enabled we are in an unexpected state, just exit
    // and assume a bootloader has already setup PCIe and assigned resources.
    //
    gpr1Reg.AsUint32 = MmioRead32((UINTN)&ioMuxcGprRegisters->GPR1);

    if (gpr1Reg.REF_SSP_EN == 1) {
        status = EFI_DEVICE_ERROR;
        goto Exit;
    }

    //
    // Disable the PHY first, without this PCI link randomly does not come up
    //
    status = PCIeSetPhyState(FALSE);
    if (EFI_ERROR(status)) {
        PCIE_ERROR("Failed to disable PCIe PHY\n");
        goto Exit;
    }

    //
    // First configure PCIe and PCIe PHY default setting
    //
    {
        IMX_IOMUXC_GPR12_REG gpr12Reg;
        IMX_IOMUXC_GPR8_REG gpr8Reg;
        volatile IMX_IOMUXC_GPR_REGISTERS* ioMuxcGprRegisters =
            (IMX_IOMUXC_GPR_REGISTERS*)IOMUXC_GPR_BASE_ADDRESS;

        gpr12Reg.AsUint32 = MmioRead32((UINTN)&ioMuxcGprRegisters->GPR12);

        gpr12Reg.APP_LTSSM_ENABLE = 0;          // Set application not ready
        gpr12Reg.DIA_STATUS_BUS_SELECT = 0xB;   // Debug functionality
        gpr12Reg.DEVICE_TYPE = 0x4;             // Set to RC mode
        gpr12Reg.LOS_LEVEL = 0x9;               // Set to 0x9 per reference manual

        MmioWrite32((UINTN)&ioMuxcGprRegisters->GPR12, gpr12Reg.AsUint32);

        // Gen1 | Gen2 3p5 | Gen2 6 | Swing full 127 | Swing low 127
        gpr8Reg.PCS_TX_DEEMPH_GEN1 = 0;
        gpr8Reg.PCS_TX_DEEMPH_GEN2_3P5DB = 0;
        gpr8Reg.PCS_TX_DEEMPH_GEN2_6DB = 20;
        gpr8Reg.PCS_TX_SWING_FULL = 127;
        gpr8Reg.PCS_TX_SWING_LOW = 127;

        MmioWrite32((UINTN)&ioMuxcGprRegisters->GPR8, gpr8Reg.AsUint32);
    }

    status = EFI_SUCCESS;

Exit:
    return status;
}

EFI_STATUS PCIeSetClockGate (
    IN IMX_CLOCK_GATE_STATE State
    )
{
    ImxClkPwrSetClockGate(IMX_PCIE_ROOT_ENABLE, State);
    return EFI_SUCCESS;
}

EFI_STATUS PCIeVerifyClocks (
    VOID
    )
{
    IMX_CCM_ANALOG_PLL_ENET_REG ccmAnalogPllReg;
    volatile IMX_CCM_ANALOG_REGISTERS *ccmAnalogRegisters =
        (IMX_CCM_ANALOG_REGISTERS *)IMX_CCM_ANALOG_BASE;

    ccmAnalogPllReg.AsUint32 = MmioRead32((UINTN)&ccmAnalogRegisters->PLL_ENET);

    if ((ccmAnalogPllReg.POWERDOWN == 0) &&
        (ccmAnalogPllReg.BYPASS == 0) &&
        (ccmAnalogPllReg.ENABLE_125M == 1) &&
        (ccmAnalogPllReg.LOCK == 1)) {
        return EFI_SUCCESS;
    }

    return EFI_DEVICE_ERROR;
}

VOID PCIeEnablePerstLine (
    VOID
    )
{
    //
    // Enable board specific PERST line if one is defined
    //
    if (FixedPcdGet32(PcdPcieResetGpio)) {
        ImxGpioWrite(
            FixedPcdGet32(PcdPcieResetGpioBankNumber),
            FixedPcdGet32(PcdPcieResetGpioIoNumber),
            IMX_GPIO_HIGH);
        gBS->Stall(20000);
    }
}

EFI_STATUS PCIeSetupPCIBridge (
    VOID
    )
{
    UINT8 classCode[0];

    //
    // Setup the bridge class
    //
    classCode[0] = PCI_IF_BRIDGE_P2P;
    classCode[1] = PCI_CLASS_BRIDGE_P2P;
    classCode[2] = PCI_CLASS_BRIDGE;

    return PCIePciWrite(
        EfiPciIoWidthUint8,
        PCIE_HOST_CONFIG_BASE_REG + PCI_CLASSCODE_OFFSET,
        3,
        classCode);
}

EFI_STATUS PCIeSetLinkStatus (
    IN BOOLEAN State
    )
{
    IMX_IOMUXC_GPR12_REG gpr12Reg;
    volatile IMX_IOMUXC_GPR_REGISTERS* ioMuxcGprRegisters =
        (IMX_IOMUXC_GPR_REGISTERS*)IOMUXC_GPR_BASE_ADDRESS;

    gpr12Reg.AsUint32 = MmioRead32((UINTN)&ioMuxcGprRegisters->GPR12);

    if (State == TRUE) {
        gpr12Reg.APP_LTSSM_ENABLE = 1; // Enable link
    } else {
        gpr12Reg.APP_LTSSM_ENABLE = 0; // Disable link
    }

    MmioWrite32((UINTN)&ioMuxcGprRegisters->GPR12, gpr12Reg.AsUint32);

    return EFI_SUCCESS;
}

BOOLEAN PCIeIsLinkUp (
    VOID
    )
{
    UINT32 debug1Reg;
    volatile CSP_PCIE_PL_REGS* portLogicRegsPtr =
        (CSP_PCIE_PL_REGS*)PCIE_CTRL_PORT_LOGIG_BASE_REG;

    debug1Reg = MmioRead32((UINTN)&portLogicRegsPtr->PCIE_PL_DEBUG1);

    return (debug1Reg & PCIE_PL_DEBUG1_PHY_LINK_UP) ? TRUE : FALSE;
}

EFI_STATUS PCIeWaitForLink (
    VOID
    )
{
    UINT32 counter = 200;
    BOOLEAN linkStatus;

    linkStatus = PCIeIsLinkUp();

    //
    // To optimize boot time, consider lowering timeout value
    //
    while (linkStatus == FALSE && counter > 0) {
        --counter;
        gBS->Stall(1000);
        linkStatus = PCIeIsLinkUp();
    }

    return (linkStatus) ? EFI_SUCCESS : EFI_DEVICE_ERROR;
}

EFI_STATUS PCIeGetAlignAddress (
    IN UINTN Address,
    IN UINTN AlignmentSize,
    OUT UINTN *AlignAddress
    )
{
    EFI_STATUS status;

    *AlignAddress = 0;

    if ((AlignmentSize & (AlignmentSize - 1)) != 0) {
        status = EFI_INVALID_PARAMETER;
        goto Exit;
    }

    //
    // Even though we do not add a (AlignmentSize + 1) to the incoming address
    // we would still align to the upper boundary as bit [19:00] is assumed to
    // be 0x000FFFFF per PCIe spec.
    //
    *AlignAddress = (Address) & ~(AlignmentSize - 1);

    status = EFI_SUCCESS;
Exit:
    return status;
}

EFI_STATUS PCIeGetPCIConfigAddress (
    IN UINTN BusNumber,
    IN UINTN DevNumber,
    IN UINTN FuncNumber,
    IN UINTN Register,
    OUT UINTN* Address
    )
{
    UINT64 offset;
    EFI_STATUS status;

    //
    // For now only support bus 0 and bus 1 with one device in each bus
    //
    if (BusNumber == 0 && DevNumber == 0) {

        offset = EFI_PCI_ADDRESS (BusNumber, DevNumber, FuncNumber, Register);
        *Address = PCIE_HOST_CONFIG_BASE_REG + offset;

        status = EFI_SUCCESS;

    } else if (BusNumber == 1 && DevNumber == 0) {

        offset = EFI_PCI_ADDRESS (BusNumber, DevNumber, FuncNumber, Register);
        offset -= EFI_PCI_ADDRESS (1, 0, FuncNumber, 0);
        *Address = PCIE_DEVICE_CONFIG_BASE_REG + offset;

        status = EFI_SUCCESS;

    } else {
        *Address = 0;
        status = EFI_INVALID_PARAMETER;
    }

    return status;
}

EFI_STATUS PCIePciRead (
    IN EFI_PCI_IO_PROTOCOL_WIDTH Width,
    IN UINTN Address,
    IN UINTN Count,
    OUT VOID *Buffer
    )
{
    PTR dest;
    UINTN stride;
    EFI_STATUS status;

    dest.ui = (UINTN)Buffer;
    Width = (EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH)(Width & 0x03);
    stride = (UINTN)1 << Width;

    //
    // Adopted from PciRootBridgeIoMemRW
    //
    switch (Width) {
    case EfiPciWidthUint8:
        for (; Count > 0; --Count, dest.buf += stride, Address += stride) {
            *dest.ui8 = MmioRead8(Address);
        }
        status = EFI_SUCCESS;
        break;
    case EfiPciWidthUint16:
        for (; Count > 0; --Count, dest.buf += stride, Address += stride) {
            *dest.ui16 = MmioRead16(Address);
        }
        status = EFI_SUCCESS;
        break;
    case EfiPciWidthUint32:
        for (; Count > 0; --Count, dest.buf += stride, Address += stride) {
            *dest.ui32 = MmioRead32(Address);
        }
        status = EFI_SUCCESS;
        break;
    default:
        status = EFI_INVALID_PARAMETER;
        goto Exit;
    }

Exit:
    return status;
}

EFI_STATUS PCIePciWrite (
    IN EFI_PCI_IO_PROTOCOL_WIDTH Width,
    IN UINTN Address,
    IN UINTN Count,
    IN VOID *Buffer
    )
{
    PTR src;
    UINTN stride;
    EFI_STATUS status;

    src.ui = (UINTN)Buffer;
    Width = (EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL_WIDTH)(Width & 0x03);
    stride = (UINTN)1 << Width;

    //
    // Adopted from PciRootBridgeIoMemRW
    //
    switch (Width) {
    case EfiPciWidthUint8:
        for (; Count > 0; --Count, src.buf += stride, Address += stride) {
            MmioWrite8(Address, *src.ui8);
        }
        status = EFI_SUCCESS;
        break;
    case EfiPciWidthUint16:
        for (; Count > 0; --Count, src.buf += stride, Address += stride) {
            MmioWrite16(Address, *src.ui16);
        }
        status = EFI_SUCCESS;
        break;
    case EfiPciWidthUint32:
        for (; Count > 0; --Count, src.buf += stride, Address += stride) {
            MmioWrite32(Address, *src.ui32);
        }
        status = EFI_SUCCESS;
        break;
    default:
        status = EFI_INVALID_PARAMETER;
        goto Exit;
    }

Exit:
    return status;
}

EFI_STATUS PCIeDevicePresent (
    OUT PCI_TYPE00* PciDevice,
    IN UINTN Bus,
    IN UINTN Device,
    IN UINTN Func
    )
{
    UINTN address;
    EFI_STATUS status;

    //
    // Create PCI address map in terms of Bus, Device, and Func
    //
    status = PCIeGetPCIConfigAddress(Bus, Device, Func, 0, &address);
    if (EFI_ERROR(status)) {
        status = EFI_NOT_FOUND;
        goto Exit;
    }

    //
    // Read the Vendor ID register
    //
    status = PCIePciRead(
        EfiPciWidthUint32,
        address,
        1,
        PciDevice);
    if (!EFI_ERROR(status) && (PciDevice->Hdr).VendorId != 0xffff) {
        //
        // Read the entire config header for the device
        //
        status = PCIePciRead(
            EfiPciWidthUint32,
            address,
            sizeof (PCI_TYPE00) / sizeof (UINT32),
            PciDevice);
        if (EFI_ERROR(status)) {
            PCIE_ERROR("Failed to read PCI config space\n");
        }
    } else {
        PCIE_INFO("No PCIe device found\n");
        status = EFI_NOT_FOUND;
    }

Exit:
    return status;
}

EFI_STATUS PCIeGetMemoryBarResource (
    IN UINTN BarSize,
    IN UINTN* BarAddress,
    IN BOOLEAN IsBridgeDevice
    )
{
    EFI_STATUS status;

    if (BarSize > PCIeResource->Size) {
        PCIE_ERROR("Insufficient PCIe memory for 0x%08x (Current size 0x%08x)\n",
            BarSize,
            PCIeResource->Size);
        status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    *BarAddress = PCIeResource->Curr;

    if (IsBridgeDevice == FALSE) {
        PCIeResource->Curr += BarSize;
        PCIeResource->Size -= BarSize;

        PCIE_INFO("Allocating memory resource 0x%08x size 0x%08x\n",
            *BarAddress,
            BarSize);
    }

    PCIE_INFO("Current memory resource 0x%08x Size 0x%08x\n",
        PCIeResource->Curr,
        PCIeResource->Size);

    status = EFI_SUCCESS;

Exit:
    return status;
}

EFI_STATUS PCIeParseAssignBar (
    IN UINTN BaseAddress,
    IN UINTN MaxBarIndex,
    IN BOOLEAN IsBridgeDevice
    )
{
    EFI_STATUS status;
    UINTN barIndex, barOffset;
    UINT32 allOne32 = 0xFFFFFFFF;

    for (barOffset = 0x10, barIndex = 0;
         barOffset <= 0x24 && barIndex < MaxBarIndex;
         barOffset += sizeof (UINT32), ++barIndex) {

        UINTN originalvalue, responseValue, barSize, resourceAddress;

        status = PCIePciRead(
            EfiPciWidthUint32,
            BaseAddress + barOffset,
            1,
            &originalvalue);
        ASSERT_EFI_ERROR(status);

        status = PCIePciWrite(
            EfiPciIoWidthUint32,
            BaseAddress + barOffset,
            1,
            &allOne32);
        ASSERT_EFI_ERROR(status);

        status = PCIePciRead(
            EfiPciWidthUint32,
            BaseAddress + barOffset,
            1,
            &responseValue);
        ASSERT_EFI_ERROR(status);

        //
        // No support for IO memory
        // Refer : PCI Local Bus Specification (6.2.5.1)
        //
        if ((responseValue & 0x01) == 0x01) {
            status = PCIePciWrite(
                EfiPciIoWidthUint32,
                BaseAddress + barOffset,
                1,
                &originalvalue);
            ASSERT_EFI_ERROR(status);
            continue;
        }

        //
        // No support for prefetch memory
        //
        if (((responseValue & 0x01) == 0x00) &&
            ((responseValue & 0x08) == 0x08)) {
            status = PCIePciWrite(
                EfiPciIoWidthUint32,
                BaseAddress + barOffset,
                1,
                &originalvalue);
            ASSERT_EFI_ERROR(status);
            continue;
        }

        barSize = (~(responseValue & 0xFFFFFFF0)) + 1;

        status = PCIeGetMemoryBarResource(
            barSize,
            &resourceAddress,
            IsBridgeDevice);
        if (EFI_ERROR(status)) {
            PCIE_ERROR("Failed to acquire BAR resource\n");
            goto Exit;
        }

        status = PCIePciWrite(
            EfiPciIoWidthUint32,
            BaseAddress + barOffset,
            1,
            &resourceAddress);
        ASSERT_EFI_ERROR(status);

        //
        // The subsequent BAR is the upper 32 bit address
        //
        if (((responseValue & 0x04) == 0x04) &&
            (barIndex + 1) < MaxBarIndex) {

            UINT32 allZero = 0;
            barOffset += sizeof (UINT32);
            ++barIndex;

            status = PCIePciWrite(
                EfiPciIoWidthUint32,
                BaseAddress + barOffset,
                1,
                &allZero);
            ASSERT_EFI_ERROR(status);

            continue;
        }
    }

    status = EFI_SUCCESS;

Exit:
    return status;
}

EFI_STATUS PCIeConfigureDevice (
    IN PCI_TYPE00 pciDevice,
    IN UINTN BusNumber,
    IN UINTN DevNumber,
    IN UINTN FuncNumber
    )
{
    EFI_STATUS status;
    UINTN baseAddress;

    PCIE_INFO(
        "Configuring B:%02d D:%02d F:%02d\n",
        BusNumber,
        DevNumber,
        FuncNumber);

    status = PCIeGetPCIConfigAddress(
        BusNumber,
        DevNumber,
        FuncNumber,
        0,
        &baseAddress);
    ASSERT_EFI_ERROR(status);

    //
    // Use a fixed cacheline size
    //
    {
        UINT8 fixedCacheLineSize = 0x10;

        status = PCIePciWrite(
            EfiPciIoWidthUint8,
            baseAddress + PCI_CACHELINE_SIZE_OFFSET,
            1,
            &fixedCacheLineSize);
        ASSERT_EFI_ERROR(status);
    }

    if (IS_PCI_BRIDGE (&pciDevice)) {
        UINT32 allZero = 0;

        PCIE_INFO("PCI Bridge\n");

        //
        // PCIe initialization sequence, referenced from
        // InitializePpb in MdeModulePkg/Bus/Pci/PciBusDxe
        // No support for IO and prefetch memory
        //

        status = PCIePciWrite(
            EfiPciIoWidthUint8,
            baseAddress + 0x1C,
            1,
            &allZero);
        ASSERT_EFI_ERROR(status);

        status = PCIePciWrite(
            EfiPciIoWidthUint8,
            baseAddress + 0x1D,
            1,
            &allZero);

        status = PCIePciWrite(
            EfiPciIoWidthUint16,
            baseAddress + 0x24,
            1,
            &allZero);
        ASSERT_EFI_ERROR(status);

        status = PCIePciWrite(
            EfiPciIoWidthUint16,
            baseAddress + 0x26,
            1,
            &allZero);
        ASSERT_EFI_ERROR(status);

        status = PCIePciWrite(
            EfiPciIoWidthUint32,
            baseAddress + 0x28,
            1,
            &allZero);
        ASSERT_EFI_ERROR(status);

        status = PCIePciWrite(
            EfiPciIoWidthUint32,
            baseAddress + 0x2C,
            1,
            &allZero);
        ASSERT_EFI_ERROR(status);

        status = PCIePciWrite(
            EfiPciIoWidthUint16,
            baseAddress + 0x30,
            1,
            &allZero);
        ASSERT_EFI_ERROR(status);

        status = PCIePciWrite(
            EfiPciIoWidthUint16,
            baseAddress + 0x32,
            1,
            &allZero);
        ASSERT_EFI_ERROR(status);

        //
        // Type 1 bridge only has 2 BAR register
        //
        status = PCIeParseAssignBar(
            baseAddress,
            2,
            TRUE);
        if (EFI_ERROR(status)) {
            PCIE_ERROR("Failed to assign resource to PCI bridge\n");
            goto Exit;
        }

    } else {

        //
        // Device specific configuration should be implemented here
        //
        PCIE_INFO("PCI device\n");

        status = PCIeParseAssignBar(
            baseAddress,
            PCI_MAX_BAR,
            FALSE);
        if (EFI_ERROR(status)) {
            PCIE_ERROR("Failed to assign resource to PCI device\n");
            goto Exit;
        }
    }

    {
        UINT16 pciCommand;

        status = PCIePciRead(
            EfiPciIoWidthUint16,
            baseAddress + PCI_COMMAND_OFFSET,
            1,
            &pciCommand);
        ASSERT_EFI_ERROR(status);

        pciCommand |=
            (EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER);

        status = PCIePciWrite(
            EfiPciIoWidthUint16,
            baseAddress + PCI_COMMAND_OFFSET,
            1,
            &pciCommand);
        ASSERT_EFI_ERROR(status);
    }

    status = EFI_SUCCESS;

Exit:
    return status;
}

EFI_STATUS PCIeSimpleScanBusAndAssignResource (
    IN UINTN BusNumber
    )
{
    EFI_STATUS status;
    UINTN devNumber;
    UINTN functionNumber;
    PCI_TYPE00 pciDevice;

    for (devNumber = 0; devNumber <= PCI_MAX_DEVICE; ++devNumber) {
        for (functionNumber = 0; functionNumber <= PCI_MAX_FUNC; ++functionNumber) {

            PCIE_INFO("Scanning device B: %02d D: %02d F: %02d\n",
                BusNumber,
                devNumber,
                functionNumber);

            status = PCIeDevicePresent(
                &pciDevice,
                BusNumber,
                devNumber,
                functionNumber);
            if (status == EFI_NOT_FOUND) {
                PCIE_INFO("No PCI device found\n");
                status = EFI_SUCCESS;
                goto Exit;
            } else if (EFI_ERROR(status)) {
                PCIE_ERROR("Error detecting PCI device\n");
                goto Exit;
            }

            status = PCIeConfigureDevice(
                pciDevice,
                BusNumber,
                devNumber,
                functionNumber);
            if (EFI_ERROR(status)) {
                PCIE_ERROR(
                    "Failed to configure device B:%02d D:%02d F:%02d\n",
                    BusNumber,
                    devNumber,
                    functionNumber);
                continue;
            }

            if (IS_PCI_BRIDGE (&pciDevice)) {
                UINTN busBaseRegisterAddress;
                UINTN resourceAddress, bridgeMemory;
                UINTN bridgeMemoryBase, bridgeMemoryLimit;
                UINT16 busRegister;
                UINT8 subBus;

                busRegister = (UINT16)(((BusNumber + 1) << 8) | (UINT16)BusNumber);
                status = PCIeGetPCIConfigAddress(
                    BusNumber,
                    devNumber,
                    functionNumber,
                    0,
                    &busBaseRegisterAddress);

                ASSERT_EFI_ERROR(status);

                status = PCIePciWrite(
                    EfiPciWidthUint16,
                    busBaseRegisterAddress + PCI_BRIDGE_PRIMARY_BUS_REGISTER_OFFSET,
                    1,
                    &busRegister);
                if (EFI_ERROR(status)) {
                    PCIE_ERROR("Failed to update bridge bus number %d\n", BusNumber);
                    continue;
                }

                //
                // Temporarily set maximum subordinate bus number, although for now
                // only support 2 buses.
                //
                subBus = 0XFF;
                status = PCIePciWrite(
                    EfiPciWidthUint8,
                    busBaseRegisterAddress + PCI_BRIDGE_SUBORDINATE_BUS_REGISTER_OFFSET,
                    1,
                    &subBus);
                if (EFI_ERROR(status)) {
                    PCIE_ERROR("Failed to update bridge bus number %d\n", BusNumber);
                    continue;
                }

                //
                // Setup the memory base.
                //
                status = PCIeGetMemoryBarResource(
                    0,
                    &bridgeMemoryBase,
                    TRUE);
                if (EFI_ERROR(status)) {
                    PCIE_ERROR("Failed to acquire BAR resource\n");
                    goto Exit;
                }

                bridgeMemory = (bridgeMemoryBase >> 16) & 0xFFF0;

                status = PCIePciWrite(
                    EfiPciIoWidthUint32,
                    busBaseRegisterAddress + 0x20,
                    1,
                    &bridgeMemory);
                ASSERT_EFI_ERROR(status);

                status = PCIeSimpleScanBusAndAssignResource(
                    BusNumber + 1);
                if (EFI_ERROR(status)) {
                    PCIE_ERROR("Failed to scan new bus %d\n", BusNumber + 1);
                    continue;
                }

                //
                // Setup the memory limit.
                //
                status = PCIeGetMemoryBarResource(
                    0,
                    &resourceAddress,
                    TRUE);
                if (EFI_ERROR(status)) {
                    PCIE_ERROR("Failed to acquire BAR resource\n");
                    goto Exit;
                }

                ASSERT(bridgeMemoryBase != resourceAddress);

                //
                // Per spec align address has to be 1MB boundary
                //
                PCIeGetAlignAddress(
                    resourceAddress,
                    0x00100000,
                    &bridgeMemoryLimit);
                ASSERT_EFI_ERROR(status);

                bridgeMemory |= bridgeMemoryLimit;

                status = PCIePciWrite(
                    EfiPciIoWidthUint32,
                    busBaseRegisterAddress + 0x20,
                    1,
                    &bridgeMemory);
                ASSERT_EFI_ERROR(status);

                subBus = (BusNumber + 1);
                status = PCIePciWrite(
                    EfiPciWidthUint8,
                    busBaseRegisterAddress +
                        PCI_BRIDGE_SUBORDINATE_BUS_REGISTER_OFFSET,
                    1,
                    &subBus);
                if (EFI_ERROR(status)) {
                    PCIE_ERROR(
                        "Failed to update subordinate bus number %d\n",
                        BusNumber);
                    continue;
                }

                //
                // Claim any memory that is used for padding
                //
                status = PCIeGetMemoryBarResource(
                    (bridgeMemoryLimit + 0x00100000) - resourceAddress,
                    &resourceAddress,
                    FALSE);
                if (EFI_ERROR(status)) {
                    PCIE_ERROR("Failed to realign resource\n");
                    goto Exit;
                }
            }

            //
            // Skip sub functions, this is not a multi function device
            //
            if (functionNumber == 0 && !IS_PCI_MULTI_FUNC (&pciDevice)) {

                functionNumber = PCI_MAX_FUNC;
            }
        }
    }

Exit:
    return status;
}

EFI_STATUS PCIeInitialize (
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE* SystemTablePtr
    )
{
    EFI_STATUS status;

    status = PCIeSetupInitSetting();
    if (EFI_ERROR(status)) {

        //
        // EFI_DEVICE_ERROR indicate that a bootloader has already setup the
        // PCIe controller. In this case just return success immediately
        //
        if (status == EFI_DEVICE_ERROR) {
            status = EFI_SUCCESS;
            PCIE_WARNING("PCIe already initialized\n");
            goto Exit;
        }

        PCIE_ERROR("Failed to enable PCIe gates\n");
        goto Exit;
    }

    status = PCIeSetClockGate(IMX_CLOCK_GATE_STATE_ON);
    if (EFI_ERROR(status)) {
        PCIE_ERROR("Failed to enable PCIe gates\n");
        goto Exit;
    }

    status = PCIeVerifyClocks();
    if (EFI_ERROR(status)) {
        PCIE_ERROR("Failed to verify PCIe clocks, not configured!\n");
        goto Exit;
    }

    status = PCIeSetPhyState(TRUE);
    if (EFI_ERROR(status)) {
        PCIE_ERROR("Failed to enable PCIe PHY\n");
        goto Exit;
    }

    //
    // Very important to wait for PCIe PHY to settle here or the controller
    // behaviour becomes unpredictable.
    //
    gBS->Stall(50000);

    PCIeEnablePerstLine();

    status = PCIeSetupPCIBridge();
    if (EFI_ERROR(status)) {
        PCIE_ERROR("Failed to setup PCI bridge\n");
        goto Exit;
    }

    status = PCIeSetLinkStatus(TRUE);
    if (EFI_ERROR(status)) {
        PCIE_ERROR("Failed to enable PCIe link\n");
        goto Exit;
    }

    status = PCIeWaitForLink();
    if (EFI_ERROR(status)) {
        PCIE_ERROR("PCI link never came up\n");
        goto Exit;
    }

    PCIeSetupiATUSettings();

    //
    // Start scanning from bus 0 onward
    //
    status = PCIeSimpleScanBusAndAssignResource(0);
    if (EFI_ERROR(status)) {
        PCIE_ERROR("PCIeSimpleScanBusAndAssignResource failed %r\n", status);
        goto Exit;
    }

#ifdef DEBUG
    {
        UINT32 printIndex = 0;
        volatile UINT32* printAddr = (UINT32*)PCIE_HOST_CONFIG_BASE_REG;

        PCIE_INFO("===============================\n");
        PCIE_INFO("Host Device Configuration space\n");
        PCIE_INFO("===============================\n");
        for (; printIndex < 16; ++printIndex) {
            PCIE_INFO("PCI [%02x] 0x%08x 0x%08x 0x%08x 0x%08x\n", \
                printIndex * 16, \
                printAddr[0], \
                printAddr[1], \
                printAddr[2], \
                printAddr[3]);

            printAddr += 4;
        }

        PCIE_INFO("===============================\n");
        PCIE_INFO("Device Configuration space 0x%08x\n", printAddr);
        PCIE_INFO("===============================\n");
        for (printIndex = 0; printIndex < 16; ++printIndex) {
            PCIE_INFO("PCI [%02x] 0x%08x 0x%08x 0x%08x 0x%08x\n", \
                printIndex * 16, \
                printAddr[0], \
                printAddr[1], \
                printAddr[2], \
                printAddr[3]);

            printAddr += 4;
        }
        PCIE_INFO("===============================\n");
    }
#endif

Exit:

    if (EFI_ERROR(status)) {
        PCIE_ERROR("Failed to initialize PCIe, disabling controller\n");
    PCIeSetLinkStatus(FALSE);
        PCIeSetPhyState(FALSE);
        PCIeSetClockGate(IMX_CLOCK_GATE_STATE_OFF);
    }

  //
  // For debug printout the state of the PLL/PHY
  //
#ifdef DEBUG
  {
    volatile IMX_CCM_ANALOG_REGISTERS* ccmAnalogRegsPtr = (IMX_CCM_ANALOG_REGISTERS*)IMX_CCM_ANALOG_BASE;
    volatile IMX_IOMUXC_GPR_REGISTERS* ioMuxcRegsPtr = (IMX_IOMUXC_GPR_REGISTERS*)IMX_IOMUXC_BASE;

    PCIE_INFO( "IMX_CCM_PLL_ENET 0x%08X\n", MmioRead32((UINTN) &ccmAnalogRegsPtr->PLL_ENET));
    PCIE_INFO( "IOMUXC_GPR1 0x%08X\n", MmioRead32((UINTN) &ioMuxcRegsPtr->GPR1));
  }
#endif
    return status;
}
