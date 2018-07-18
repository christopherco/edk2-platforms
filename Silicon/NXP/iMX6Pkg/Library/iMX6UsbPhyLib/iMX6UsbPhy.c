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

#include <PiDxe.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/TimerLib.h>
#include <Library/BaseMemoryLib.h>

#include <iMX6.h>
#include <iMX6IoMux.h>
#include <iMX6UsbPhy.h>

/**
  Timeout constants
**/

#define USB_PHY_PLL_LOCK_TIMEOUT_USEC (UINT32)(1000*1000)
#define USB_EHCI_STOP_RESET_TIMEOUT_USEC (UINT32)(1000*1000)

/**
  Required register bit masks
**/

#define IMX_CCM_ANALOG_PLL_USB1_REG_LOCK 0x80000000

#define IMX_USB_CMD_REG_RUN 0x00000001
#define IMX_USB_CMD_REG_RESET 0x00000002

/**
  Wait for a register bit to be on/off
**/
EFI_STATUS RegisterWaitBit (
    volatile VOID* RegisterAddr,
    UINT32 Mask,
    BOOLEAN IsWaitOn,
    UINT32 TimeOutUsec)
{
    UINT32 TimeUsec = 0;
    do {
        UINT32 RegisterValue = MmioRead32((UINTN)RegisterAddr) & Mask;
        if (((RegisterValue == Mask) && IsWaitOn) || ((RegisterValue == 0) && !IsWaitOn)) {
            return EFI_SUCCESS;
        }

        MicroSecondDelay(10);
        TimeUsec += 10;
    } while (TimeUsec < TimeOutUsec);

    return EFI_TIMEOUT;
}

/**
  Turn on the 480Mhz PLL
**/
EFI_STATUS ImxUsbPhyEnablePll (IMX_USBPHY_ID ImxUsbPhyId)
{
    volatile IMX_CCM_ANALOG_REGISTERS* CcmAnaRegsPtr = (IMX_CCM_ANALOG_REGISTERS*)IMX_CCM_ANALOG_BASE;
    volatile IMX_CCM_ANALOG_PLL_USB1_REG* PllUsbClrRegPtr;
    volatile IMX_CCM_ANALOG_PLL_USB1_REG* PllUsbSetRegPtr;
    EFI_STATUS Status;

    switch (ImxUsbPhyId) {
    case IMX_USBPHY0:
        PllUsbClrRegPtr = (IMX_CCM_ANALOG_PLL_USB1_REG*)&CcmAnaRegsPtr->PLL_USB1_CLR;
        PllUsbSetRegPtr = (IMX_CCM_ANALOG_PLL_USB1_REG*)&CcmAnaRegsPtr->PLL_USB1_SET;
        break;

    case IMX_USBPHY1:
        PllUsbClrRegPtr = (IMX_CCM_ANALOG_PLL_USB1_REG*)&CcmAnaRegsPtr->PLL_USB2_CLR;
        PllUsbSetRegPtr = (IMX_CCM_ANALOG_PLL_USB1_REG*)&CcmAnaRegsPtr->PLL_USB2_SET;
        break;

    default:
        return EFI_INVALID_PARAMETER;
    }

    IMX_CCM_ANALOG_PLL_USB1_REG PllUsbClrReg = { 0 };
    PllUsbClrReg.BYPASS = 1;
    MmioWrite32((UINTN)PllUsbClrRegPtr, PllUsbClrReg.AsUint32);

    IMX_CCM_ANALOG_PLL_USB1_REG PllUsbSetReg = { 0 };
    PllUsbSetReg.EN_USB_CLKS = 1;
    PllUsbSetReg.POWER = 1;
    PllUsbSetReg.ENABLE = 1;
    MmioWrite32((UINTN)PllUsbSetRegPtr, PllUsbSetReg.AsUint32);

    //
    // Wait for PLL to lock
    //
    Status = RegisterWaitBit(
        PllUsbSetRegPtr,
        IMX_CCM_ANALOG_PLL_USB1_REG_LOCK,
        TRUE, // On
        USB_PHY_PLL_LOCK_TIMEOUT_USEC);

    if (Status != EFI_SUCCESS) {
        DEBUG((DEBUG_ERROR, "PLL 480Mhz failed to lock for PHY %d\n", (UINT32)ImxUsbPhyId));

        //
        // On failure disable the PHY
        //
        PllUsbClrReg.AsUint32 = 0;
        PllUsbSetReg.EN_USB_CLKS = 1;
        PllUsbSetReg.POWER = 1;
        PllUsbSetReg.ENABLE = 1;
        MmioWrite32((UINTN)PllUsbClrRegPtr, PllUsbSetReg.AsUint32);
        return Status;
    }

    return EFI_SUCCESS;
}

/**
  Reset the EHCI controller associated with the given PHY.
**/
EFI_STATUS ImxUsbEhciResetController (IMX_USBPHY_ID ImxUsbPhyId)
{
    volatile USB_USBCMD_REG* UsbCmdRegPtr;
    EFI_STATUS Status;

    switch (ImxUsbPhyId) {
    case IMX_USBPHY0:
        UsbCmdRegPtr = (USB_USBCMD_REG*)(IMX_USBCORE_BASE + IMX_USBCORE_LENGTH * 0 + IMX_USBCMD_OFFSET);
        break;

    case IMX_USBPHY1:
        UsbCmdRegPtr = (USB_USBCMD_REG*)(IMX_USBCORE_BASE + IMX_USBCORE_LENGTH * 1 + IMX_USBCMD_OFFSET);
        break;

    default:
        return EFI_INVALID_PARAMETER;
    }

    //
    // The host controller can only be reset when it is stopped.
    //
    USB_USBCMD_REG UsbCmdReg = { MmioRead32((UINTN)UsbCmdRegPtr) };
    UsbCmdReg.RS = 0;
    MmioWrite32((UINTN)UsbCmdRegPtr, UsbCmdReg.AsUint32);

    //
    // Wait for controller to stop
    //
    Status = RegisterWaitBit(
        UsbCmdRegPtr,
        IMX_USB_CMD_REG_RUN,
        FALSE, // Off
        USB_EHCI_STOP_RESET_TIMEOUT_USEC);

    if (Status != EFI_SUCCESS) {
        ASSERT_EFI_ERROR(Status);
        DEBUG((DEBUG_ERROR, "Failed to stop EHCI controller (PHY %d)\n", (UINT32)ImxUsbPhyId));
        return Status;
    }

    //
    // Reset the controller
    //
    UsbCmdReg.AsUint32 = MmioRead32((UINTN)UsbCmdRegPtr);
    UsbCmdReg.RST = 1;
    MmioWrite32((UINTN)UsbCmdRegPtr, UsbCmdReg.AsUint32);

    //
    // Wait for controller reset to complete
    //
    Status = RegisterWaitBit(
        UsbCmdRegPtr,
        IMX_USB_CMD_REG_RESET,
        FALSE, // Off
        USB_EHCI_STOP_RESET_TIMEOUT_USEC);

    if (Status != EFI_SUCCESS) {
        ASSERT_EFI_ERROR(Status);
        DEBUG((DEBUG_ERROR, "Failed to reset EHCI controller (PHY %d)\n", (UINT32)ImxUsbPhyId));
        return Status;
    }

    //
    // Force OTG port into Host mode. Depending on the ID_PIN tends to be
    // unreliable in some board designs such as SABRESED.
    // If the OTG port is not forced into Host mode, the USB stack fails to
    // start.
    //
    if (ImxUsbPhyId == IMX_USBPHY0) {
        volatile USB_USBMODE_REG* UsbModeRegPtr;
        USB_USBMODE_REG UsbModeReg;

        DEBUG((DEBUG_INFO, "Switching USB OTG Port to Host\n"));

        UsbModeRegPtr = (USB_USBMODE_REG*)(IMX_USBCORE_BASE + IMX_USBMODE_OFFSET);
        UsbModeReg.AsUint32 = MmioRead32((UINTN)UsbModeRegPtr);
        UsbModeReg.CM = IMX_USBMODE_HOST;
        MmioWrite32((UINTN)UsbModeRegPtr, UsbModeReg.AsUint32);

        DEBUG_CODE_BEGIN();
        UsbModeReg.AsUint32 = MmioRead32((UINTN)UsbModeRegPtr);
        ASSERT(UsbModeReg.CM == IMX_USBMODE_HOST);
        DEBUG_CODE_END();
    }

    return EFI_SUCCESS;
}

/**
  Initialize a USB PHY
**/
EFI_STATUS ImxUsbPhyInit (IMX_USBPHY_ID ImxUsbPhyId)
{
    volatile IMX_USBNONCORE_REGISTERS* UsbNonCoreRegPtr = (IMX_USBNONCORE_REGISTERS*)IMX_USBNONCORE_BASE;
    volatile IMX_USBANA_REGISTERS* UsbAnaRegsPtr = (IMX_USBANA_REGISTERS*)IMX_USBANA_BASE;
    volatile IMX_USBPHY_REGISTERS* UsbPhyRegsPtr;
    volatile IMX_USBANA_USB_REGISTERS* UsbAnaUsbRegsPtr;
    volatile USBNC_USB_UH_CTRL_REG* UsbNcUhCtrlRegPtr;
    EFI_STATUS Status;

    switch (ImxUsbPhyId) {
    case IMX_USBPHY0:
        UsbPhyRegsPtr = (IMX_USBPHY_REGISTERS*)IMX_USBPHY1_BASE;
        UsbAnaUsbRegsPtr = &UsbAnaRegsPtr->USBANA[0];
        UsbNcUhCtrlRegPtr = (USBNC_USB_UH_CTRL_REG*)&UsbNonCoreRegPtr->USBNC_USB_OTG_CTRL;
        break;

    case IMX_USBPHY1:
        UsbPhyRegsPtr = (IMX_USBPHY_REGISTERS*)IMX_USBPHY2_BASE;
        UsbAnaUsbRegsPtr = &UsbAnaRegsPtr->USBANA[1];
        UsbNcUhCtrlRegPtr = (USBNC_USB_UH_CTRL_REG*)&UsbNonCoreRegPtr->USBNC_USB_UH1_CTRL;
        break;

    default:
        return EFI_INVALID_PARAMETER;
    }

    //
    // USB power configuration:
    //
    {
        //
        // Set power polarity
        //
        USBNC_USB_UH_CTRL_REG UsbNcHcCtrlReg = { MmioRead32((UINTN)UsbNcUhCtrlRegPtr) };
        UsbNcHcCtrlReg.PWR_POL = 1;
        UsbNcHcCtrlReg.AsUint32 |= 0x2;     // Reserved bit
        MmioWrite32((UINTN)UsbNcUhCtrlRegPtr, UsbNcHcCtrlReg.AsUint32);

        //
        // Disable external USB charger detector
        //
        USB_ANALOG_USB_CHRG_DETECT_REG UsbAnaChrgDetReg = { 0 };
        UsbAnaChrgDetReg.EN_B = 1;
        UsbAnaChrgDetReg.CHK_CHRG_B = 1;
        MmioWrite32((UINTN)&UsbAnaUsbRegsPtr->USB_ANALOG_USB_CHRG_DETECT_SET, UsbAnaChrgDetReg.AsUint32);

        //
        // Enable the 480Mhz PLL
        //
        Status = ImxUsbPhyEnablePll(ImxUsbPhyId);
        if (Status != EFI_SUCCESS) {
            ASSERT_EFI_ERROR(Status);
            DEBUG((DEBUG_ERROR, "Failed to enable PLL 480Mhz failed for PHY %d\n", (UINT32)ImxUsbPhyId));
            return Status;
        }
    }

    //
    // Configure Over Current
    //
    {
        USBNC_USB_UH_CTRL_REG UsbNcHcCtrlReg = { MmioRead32((UINTN)UsbNcUhCtrlRegPtr) };
        UsbNcHcCtrlReg.OVER_CUR_POL = 0;
        UsbNcHcCtrlReg.OVER_CUR_DIS = 1;
        MmioWrite32((UINTN)UsbNcUhCtrlRegPtr, UsbNcHcCtrlReg.AsUint32);
    }

    //
    // Enable USBH PHY clock
    //
    {
        USBPHYx_CTRL_REG UsbPhyCtrlReg = { 0 };
        UsbPhyCtrlReg.CLKGATE = 1;
        MmioWrite32((UINTN)&UsbPhyRegsPtr->USBPHY_CTRL_CLR, UsbPhyCtrlReg.AsUint32);
        MicroSecondDelay(10);
    }

    //
    // Enable clock to UTMI block
    //
    {
        USB_ANALOG_USB_MISC_REG UsbAnaMicReg = { 0 };
        UsbAnaMicReg.EN_CLK_UTMI = 1;
        MmioWrite32((UINTN)&UsbAnaUsbRegsPtr->USB_ANALOG_USB_MISC_SET, UsbAnaMicReg.AsUint32);
        MicroSecondDelay(10);
    }

    //
    // Enable USBH PHY
    //
    {
        //
        // Reset the associated EHCI controller
        //
        Status = ImxUsbEhciResetController(ImxUsbPhyId);
        if (Status != EFI_SUCCESS) {
            return Status;
        }

        //
        // Reset the PHY
        //
        USBPHYx_CTRL_REG UsbPhyCtrl;
        {
            UsbPhyCtrl.AsUint32 = 0;
            UsbPhyCtrl.SFTRST = 1;
            MmioWrite32((UINTN)&UsbPhyRegsPtr->USBPHY_CTRL_SET, UsbPhyCtrl.AsUint32);
            MicroSecondDelay(10);

            UsbPhyCtrl.AsUint32 = 0;
            UsbPhyCtrl.SFTRST = 1;
            UsbPhyCtrl.CLKGATE = 1;
            MmioWrite32((UINTN)&UsbPhyRegsPtr->USBPHY_CTRL_CLR, UsbPhyCtrl.AsUint32);
            MicroSecondDelay(10);
        }

        //
        // Power UP the PHY
        //
        MmioWrite32((UINTN)&UsbPhyRegsPtr->USBPHY_PWD, 0);

        //
        // Apply PHY configuration:
        // - Enable low/full speed devices.
        //
        UsbPhyCtrl.AsUint32 = 0;
        // iMX6 Solo and DualLite - 66.3.4 USB PHY General Control Register (USBPHYx_CTRLn)
#if !(defined(CPU_IMX6SX) || defined(CPU_IMX6SDL))
        UsbPhyCtrl.ENAUTOSET_USBCLKS = 1;
        UsbPhyCtrl.ENAUTOCLR_USBCLKGATE = 1;
#endif
        UsbPhyCtrl.ENAUTOCLR_PHY_PWD = 1;
        UsbPhyCtrl.ENAUTOCLR_CLKGATE = 1;
#if !(defined(CPU_IMX6SX) || defined(CPU_IMX6SDL))
        UsbPhyCtrl.ENAUTO_PWRON_PLL = 1;
#endif
        UsbPhyCtrl.ENUTMILEVEL2 = 1;
        UsbPhyCtrl.ENUTMILEVEL3 = 1;
        MmioWrite32((UINTN)&UsbPhyRegsPtr->USBPHY_CTRL_SET, UsbPhyCtrl.AsUint32);
#if !(defined(CPU_IMX6SX) || defined(CPU_IMX6SDL))
        MmioWrite32 ((UINTN)&UsbPhyRegsPtr->USBPHY_IP_SET, IMX_USBPHY_IP_FIX);
#endif
    }

    return EFI_SUCCESS;
}
