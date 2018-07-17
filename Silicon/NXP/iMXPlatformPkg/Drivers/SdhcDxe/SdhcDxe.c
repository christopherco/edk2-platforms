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

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/DevicePathLib.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DmaLib.h>
#include <Library/TimerLib.h>

#include <Protocol/EmbeddedExternalDevice.h>
#include <Protocol/BlockIo.h>
#include <Protocol/DevicePath.h>
#include <Protocol/Sdhc.h>

#include <iMXuSdhc.h>
#include <iMXGpio.h>

typedef struct {
    UINT32 IoNumber;
    IMX_GPIO_BANK Bank;
} IMX_GPIO_PIN;

#define PCD_GPIO_PIN_IO_NUMBER(X)   ((X) & 0xFF)
#define PCD_GPIO_PIN_BANK(X)        (((X) >> 8) & 0xFF)

//
// A special value to indicate that GPIO is not the signal source for either
// CardDetect or WriteProtect
//
typedef enum {
    USDHC_SIGNAL_GPIO_START = 0x000,
    USDHC_SIGNAL_GPIO_END = 0xFF00,
    USDHC_SIGNAL_OVERRIDE_PIN_LOW = 0xFF00,
    USDHC_SIGNAL_OVERRIDE_PIN_HIGH = 0xFF01,
    USDHC_SIGNAL_INTERNAL_PIN = 0xFFFF
} USDHC_SIGNAL_SOURCE;

#define USDHC_IS_GPIO_SIGNAL_SOURCE(X)  \
    (((X) >= USDHC_SIGNAL_GPIO_START) && ((X) < USDHC_SIGNAL_GPIO_END))

typedef struct {
    UINT32 SdhcId;
    EFI_HANDLE SdhcProtocolHandle;
    USDHC_REGISTERS *RegistersBase;
    USDHC_SIGNAL_SOURCE CardDetectSignal;
    USDHC_SIGNAL_SOURCE WriteProtectSignal;
    IMX_GPIO_PIN CardDetectGpioPin;
    IMX_GPIO_PIN WriteProtectGpioPin;
} USDHC_PRIVATE_CONTEXT;

#define LOG_FMT_HELPER(FMT, ...) \
    "SDHC%d:" FMT "%a\n", ((SdhcCtx != NULL) ? SdhcCtx->SdhcId : -1), __VA_ARGS__

#define LOG_INFO(...) \
    DEBUG((DEBUG_INFO | DEBUG_BLKIO, LOG_FMT_HELPER(__VA_ARGS__, "")))

#define LOG_TRACE(...) \
    DEBUG((DEBUG_VERBOSE | DEBUG_BLKIO, LOG_FMT_HELPER(__VA_ARGS__, "")))

#define LOG_ERROR(...) \
    DEBUG((DEBUG_ERROR | DEBUG_BLKIO, LOG_FMT_HELPER(__VA_ARGS__, "")))

#define LOG_ASSERT(TXT) \
    ASSERT(!"Sdhc: " TXT "\n")

#ifdef MIN
#undef MIN
#define MIN(x,y) ((x) > (y) ? (y) : (x))
#endif // MIN

//
// uSDHC read/write FIFO is 128x32-bit
//
#define USDHC_FIFO_MAX_WORD_COUNT       128

//
// Max block count allowed in a single transfer
//
#define USDHC_MAX_BLOCK_COUNT           0xFFFF

//
// Number of register maximum polls
//
#define USDHC_POLL_RETRY_COUNT          100000

//
// Waits between each registry poll
//
#define USDHC_POLL_WAIT_US              20

//
// uSDHC input clock. Ideally, should query it from clock manager
//
#define USDHC_BASE_CLOCK_FREQ_HZ        198000000

#define USDHC_BLOCK_LENGTH_BYTES               512

VOID
DumpState(
    IN USDHC_PRIVATE_CONTEXT *SdhcCtx
    )
{
DEBUG_CODE_BEGIN ();

    USDHC_REGISTERS *Reg = SdhcCtx->RegistersBase;

    USDHC_BLK_ATT_REG BlkAtt; BlkAtt.AsUint32 = MmioRead32((UINTN)&Reg->BLK_ATT);
    UINT32 CmdArg; CmdArg = MmioRead32((UINTN)&Reg->CMD_ARG);
    USDHC_CMD_XFR_TYP_REG CmdXfrTyp; CmdXfrTyp.AsUint32 = MmioRead32((UINTN)&Reg->CMD_XFR_TYP);
    USDHC_PROT_CTRL_REG ProtCtrl; ProtCtrl.AsUint32 = MmioRead32((UINTN)&Reg->PROT_CTRL);
    USDHC_WTMK_LVL_REG WtmkLvl; WtmkLvl.AsUint32 = MmioRead32((UINTN)&Reg->WTMK_LVL);
    USDHC_MIX_CTRL_REG MixCtrl; MixCtrl.AsUint32 = MmioRead32((UINTN)&Reg->MIX_CTRL);
    UINT32 IntStatusEn = MmioRead32((UINTN)&Reg->INT_STATUS_EN);
    UINT32 IntSignalEn = MmioRead32((UINTN)&Reg->INT_SIGNAL_EN);
    UINT32 VendSpec = MmioRead32((UINTN)&Reg->VEND_SPEC);
    UINT32 MmcBoot = MmioRead32((UINTN)&Reg->MMC_BOOT);
    UINT32 VendSpec2 = MmioRead32((UINTN)&Reg->VEND_SPEC2);
    USDHC_INT_STATUS_REG IntStatus; IntStatus.AsUint32 = MmioRead32((UINTN)&Reg->INT_STATUS);
    USDHC_PRES_STATE_REG PresState; PresState.AsUint32 = MmioRead32((UINTN)&Reg->PRES_STATE);

    LOG_INFO(
        " - BLK_ATT\t:0x%08x BLKSIZE:0x%x BLKCNT:0x%08x",
        BlkAtt.AsUint32,
        BlkAtt.Fields.BLKSIZE,
        BlkAtt.Fields.BLKCNT);

    LOG_INFO(" - CMD_ARG\t:0x%08x", CmdArg);

    LOG_INFO(
        " - CMD_XFR_TYP\t:0x%08x RSPTYP:%d CCCEN:%d CICEN:%d DPSEL:%d CMDTYP:%d CMDINX:%d",
        CmdXfrTyp.AsUint32,
        CmdXfrTyp.Fields.RSPTYP,
        CmdXfrTyp.Fields.CCCEN,
        CmdXfrTyp.Fields.CICEN,
        CmdXfrTyp.Fields.DPSEL,
        CmdXfrTyp.Fields.CMDTYP,
        CmdXfrTyp.Fields.CMDINX);

    LOG_INFO(
        " - PROT_CTRL\t:0x%08x DTW:%d D3CD:%d CDSS:%d EMODE:%d DMASEL:%d SABGREQ:%d BURST_LEN_EN:%d",
        ProtCtrl.AsUint32,
        ProtCtrl.Fields.DTW,
        ProtCtrl.Fields.D3CD,
        ProtCtrl.Fields.CDSS,
        ProtCtrl.Fields.EMODE,
        ProtCtrl.Fields.DMASEL,
        ProtCtrl.Fields.SABGREQ,
        ProtCtrl.Fields.BURST_LEN_EN);

    LOG_INFO(
        " - WTMK_LVL\t:0x%08x RD_WML:%d RD_BRST_LEN:%d WR_WML:%d WR_BRST_LEN:%d",
        WtmkLvl.AsUint32,
        WtmkLvl.Fields.RD_WML,
        WtmkLvl.Fields.RD_BRST_LEN,
        WtmkLvl.Fields.WR_WML,
        WtmkLvl.Fields.WR_BRST_LEN);

    LOG_INFO(
        " - MIX_CTRL\t:0x%08x DMAEN:%d BCEN:%d AC12EN:%d DTDSEL:%d MSBSEL:%d AC23EN:%d FBCLK_SEL:%d",
        MixCtrl.AsUint32,
        MixCtrl.Fields.DMAEN,
        MixCtrl.Fields.BCEN,
        MixCtrl.Fields.AC12EN,
        MixCtrl.Fields.DTDSEL,
        MixCtrl.Fields.MSBSEL,
        MixCtrl.Fields.AC23EN,
        MixCtrl.Fields.FBCLK_SEL);

    LOG_INFO(" - INT_STATUS_EN\t:0x%08x", IntStatusEn);
    LOG_INFO(" - INT_SIGNAL_EN\t:0x%08x", IntSignalEn);
    LOG_INFO(" - VEND_SPEC\t:0x%08x", VendSpec);
    LOG_INFO(" - MMC_BOOT\t:0x%08x", MmcBoot);
    LOG_INFO(" - VEND_SPEC2\t:0x%08x", VendSpec2);

    LOG_INFO(
        " - INT_STATUS\t:0x%08x CC:%d TC:%d BWR:%d BRR:%d CTOE:%d CCE:%d CEBE:%d CIE:%d DTOE:%d DCE:%d DEBE:%d",
        IntStatus.AsUint32,
        IntStatus.Fields.CC,
        IntStatus.Fields.TC,
        IntStatus.Fields.BWR,
        IntStatus.Fields.BRR,
        IntStatus.Fields.CTOE,
        IntStatus.Fields.CCE,
        IntStatus.Fields.CEBE,
        IntStatus.Fields.CIE,
        IntStatus.Fields.DTOE,
        IntStatus.Fields.DCE,
        IntStatus.Fields.DEBE);

    LOG_INFO(
        " - PRES_STATE\t:0x%08x CIHB:%d CDIHB:%d DLA:%d WTA:%d RTA:%d BWEN:%d BREN:%d CINST:%d DLSL:0x%x",
        PresState.AsUint32,
        PresState.Fields.CIHB,
        PresState.Fields.CDIHB,
        PresState.Fields.DLA,
        PresState.Fields.WTA,
        PresState.Fields.RTA,
        PresState.Fields.BWEN,
        PresState.Fields.BREN,
        PresState.Fields.CINST,
        PresState.Fields.DLSL);

DEBUG_CODE_END ();
}

EFI_STATUS
WaitForReadFifo(
    IN USDHC_PRIVATE_CONTEXT *SdhcCtx
    )
{
    USDHC_REGISTERS *Reg = SdhcCtx->RegistersBase;
    USDHC_INT_STATUS_REG IntStatus; IntStatus.AsUint32 = MmioRead32((UINTN)&Reg->INT_STATUS);
    UINT32 Retry = USDHC_POLL_RETRY_COUNT;

    while (!IntStatus.Fields.BRR &&
        !(IntStatus.AsUint32 & USDHC_INT_STATUS_ERROR) &&
        Retry) {
       --Retry;
       gBS->Stall(USDHC_POLL_WAIT_US);
       IntStatus.AsUint32 = MmioRead32((UINTN)&Reg->INT_STATUS);
    }

    if (IntStatus.AsUint32 & USDHC_INT_STATUS_ERROR) {
        LOG_ERROR("Error detected");
        DumpState(SdhcCtx);
        return EFI_DEVICE_ERROR;
    } else if (IntStatus.Fields.BRR) {
        MmioWrite32((UINTN)&Reg->INT_STATUS, IntStatus.AsUint32);
        return EFI_SUCCESS;
    } else {
        ASSERT(!Retry);
        LOG_ERROR("Time-out waiting on read FIFO");
        DumpState(SdhcCtx);
        return EFI_TIMEOUT;
     }
}

EFI_STATUS
WaitForWriteFifo(
    IN USDHC_PRIVATE_CONTEXT *SdhcCtx
    )
{
    USDHC_REGISTERS *Reg = SdhcCtx->RegistersBase;
    USDHC_INT_STATUS_REG IntStatus; IntStatus.AsUint32 = MmioRead32((UINTN)&Reg->INT_STATUS) ;
    UINT32 Retry = USDHC_POLL_RETRY_COUNT;

    while (!IntStatus.Fields.BWR &&
        !(IntStatus.AsUint32 & USDHC_INT_STATUS_ERROR) &&
        Retry) {
       --Retry;
       gBS->Stall(USDHC_POLL_WAIT_US);
       IntStatus.AsUint32 = MmioRead32((UINTN)&Reg->INT_STATUS);
    }

    if (IntStatus.AsUint32 & USDHC_INT_STATUS_ERROR) {
        LOG_ERROR("Error detected");
        DumpState(SdhcCtx);
        return EFI_DEVICE_ERROR;
    } else if (IntStatus.Fields.BWR) {
        MmioWrite32((UINTN)&Reg->INT_STATUS, IntStatus.AsUint32);
        return EFI_SUCCESS;
    } else {
        ASSERT(!Retry);
        LOG_ERROR("Time-out waiting on write FIFO");
        DumpState(SdhcCtx);
        return EFI_TIMEOUT;
    }
}

EFI_STATUS
WaitForCmdAndOrDataLine(
    IN USDHC_PRIVATE_CONTEXT *SdhcCtx,
    IN const SD_COMMAND *Cmd
    )
{
    BOOLEAN WaitForDataLine;

    //
    // Waiting on the DATA lines is the default behavior if no CMD is specified
    //
    if (Cmd == NULL) {
        WaitForDataLine = TRUE;
    } else {
        //
        // Per datasheet, the SDHC can isssue CMD0, CMD12, CMD13 and CMD52
        // when the DATA lines are busy during a data transfer. Other commands
        // should wait on the DATA lines before issuing
        //
        switch (Cmd->Index) {
        case 0:
        case 12:
        case 13:
        case 52:
            WaitForDataLine = FALSE;
            break;
        default:
            WaitForDataLine = TRUE;
        }
    }

    USDHC_REGISTERS *Reg = SdhcCtx->RegistersBase;
    USDHC_PRES_STATE_REG PresState; PresState.AsUint32 = MmioRead32((UINTN)&Reg->PRES_STATE);
    USDHC_INT_STATUS_REG IntStatus; IntStatus.AsUint32 = MmioRead32((UINTN)&Reg->INT_STATUS) ;
    UINT32 Retry = USDHC_POLL_RETRY_COUNT;

    while (PresState.Fields.CIHB &&
           (!WaitForDataLine || PresState.Fields.CDIHB) &&
           !(IntStatus.AsUint32 & USDHC_INT_STATUS_ERROR) &&
           Retry) {
        gBS->Stall(USDHC_POLL_WAIT_US);
        --Retry;
        PresState.AsUint32 = MmioRead32((UINTN)&Reg->PRES_STATE);
        IntStatus.AsUint32 = MmioRead32((UINTN)&Reg->INT_STATUS);
    }

    if (IntStatus.AsUint32 & USDHC_INT_STATUS_ERROR) {
        LOG_ERROR("Error detected");
        DumpState(SdhcCtx);
        return EFI_DEVICE_ERROR;
    } else if (!(PresState.Fields.CIHB &&
           (!WaitForDataLine || PresState.Fields.CDIHB))) {
           return EFI_SUCCESS;
    } else {
        ASSERT(!Retry);
        LOG_ERROR("Time-out waiting on CMD and/or DATA lines");
        DumpState(SdhcCtx);
        return EFI_TIMEOUT;
    }
}

EFI_STATUS
WaitForCmdResponse(
    IN USDHC_PRIVATE_CONTEXT *SdhcCtx
    )
{
    USDHC_REGISTERS *Reg = SdhcCtx->RegistersBase;
    USDHC_INT_STATUS_REG IntStatus; IntStatus.AsUint32 = MmioRead32((UINTN)&Reg->INT_STATUS) ;
    UINT32 Retry = USDHC_POLL_RETRY_COUNT;

    //
    // Wait for command to finish execution either with success or failure
    //
    while (!IntStatus.Fields.CC &&
           !(IntStatus.AsUint32 & USDHC_INT_STATUS_ERROR) &&
           Retry) {
        gBS->Stall(USDHC_POLL_WAIT_US);
        --Retry;
        IntStatus.AsUint32 = MmioRead32((UINTN)&Reg->INT_STATUS);
    }

    if (IntStatus.AsUint32 & USDHC_INT_STATUS_ERROR) {
        LOG_ERROR("Error detected");
        DumpState(SdhcCtx);
        return EFI_DEVICE_ERROR;
    } else if (IntStatus.Fields.CC) {
        MmioWrite32((UINTN)&Reg->INT_STATUS, IntStatus.AsUint32);
        return EFI_SUCCESS;
    } else {
        ASSERT(!Retry);
        LOG_ERROR("Time-out waiting on command completion");
        DumpState(SdhcCtx);
        return EFI_TIMEOUT;
    }
}

EFI_STATUS
SdhcSetBusWidth(
  IN EFI_SDHC_PROTOCOL *This,
  IN SD_BUS_WIDTH BusWidth
  )
{
    USDHC_PRIVATE_CONTEXT *SdhcCtx = (USDHC_PRIVATE_CONTEXT*)This->PrivateContext;
    USDHC_REGISTERS *Reg = SdhcCtx->RegistersBase;
    USDHC_PROT_CTRL_REG ProtCtrl; ProtCtrl.AsUint32 = MmioRead32((UINTN)&Reg->PROT_CTRL);

    LOG_TRACE("SdhcSetBusWidth(%d)", BusWidth);

    switch (BusWidth) {
    case SdBusWidth1Bit:
        ProtCtrl.Fields.DTW = USDHC_PROT_CTRL_DTW_1BIT;
        break;
    case SdBusWidth4Bit:
        ProtCtrl.Fields.DTW = USDHC_PROT_CTRL_DTW_4BIT;
        break;
    case SdBusWidth8Bit:
        ProtCtrl.Fields.DTW = USDHC_PROT_CTRL_DTW_8BIT;
        break;
    default:
        LOG_ASSERT("Invalid bus width");
        return EFI_INVALID_PARAMETER;
    }

    MmioWrite32((UINTN)&Reg->PROT_CTRL, ProtCtrl.AsUint32);

    return EFI_SUCCESS;
}

EFI_STATUS
SdhcSetClock(
    IN EFI_SDHC_PROTOCOL *This,
    IN UINT32 TargetFreqHz
    )
{
    USDHC_PRIVATE_CONTEXT *SdhcCtx = (USDHC_PRIVATE_CONTEXT*)This->PrivateContext;

    LOG_TRACE("SdhcSetClock(%dHz)", TargetFreqHz);

    USDHC_REGISTERS *Reg = SdhcCtx->RegistersBase;
    USDHC_SYS_CTRL_REG SysCtrl; SysCtrl.AsUint32 = MmioRead32((UINTN)&Reg->SYS_CTRL);

    //
    // SDCLK = (Base Clock) / (prescaler x divisor)
    //
    UINT32 Prescaler;
    UINT32 Divisor;
    UINT32 SDCLK;

    USDHC_MIX_CTRL_REG MixCtrl; MixCtrl.AsUint32 = MmioRead32((UINTN)&Reg->MIX_CTRL);

    //
    // Bruteforce to find the best prescaler and divisor that result
    // in SDCLK less than or equal to the requested frequency
    //
    // Allowed |Base clock divided By
    // SDCLKFS |DDR_EN=0   |DDR_EN=1
    // 80h      256         512
    // 40h      128         256
    // 20h      64          128
    // 10h      32          64
    // 08h      16          32
    // 04h      8           16
    // 02h      4           8
    // 01h      2           4
    // 00h      1           2
    //
    const UINT32 PRESCALER_MIN = (MixCtrl.Fields.DDR_EN ? 2 : 1);
    const UINT32 PRESCALER_MAX = (MixCtrl.Fields.DDR_EN ? 512 : 256);;
    const UINT32 DIVISOR_MIN = 1;
    const UINT32 DIVISOR_MAX = 16;
    UINT32 MinFreqDistance = 0xFFFFFFFF;
    UINT32 FreqDistance;
    UINT32 BestPrescaler = 0;
    UINT32 BestDivisor = 0;

    //
    // Bruteforce to find the best prescaler and divisor that result
    // in SDCLK less than or equal to the requested frequency
    //
    for (Prescaler = PRESCALER_MAX; Prescaler >= PRESCALER_MIN; Prescaler /= 2) {
        for (Divisor = DIVISOR_MIN; Divisor <= DIVISOR_MAX; ++Divisor) {
            SDCLK = USDHC_BASE_CLOCK_FREQ_HZ / (Prescaler * Divisor);

            //
            // We are not willing to choose clocks higher than the target one
            // to avoid exceeding device limits
            //
            if (SDCLK > TargetFreqHz) {
                continue;
            } else if (SDCLK == TargetFreqHz) {
                BestPrescaler = Prescaler;
                BestDivisor = Divisor;
                break;
            } else {
                FreqDistance = TargetFreqHz - SDCLK;
                if (FreqDistance < MinFreqDistance) {
                    MinFreqDistance = FreqDistance;
                    BestPrescaler = Prescaler;
                    BestDivisor = Divisor;
                }
            }
        }
    }

    //
    // Wait for clock to become stable before any modifications
    //
    USDHC_PRES_STATE_REG PresState; PresState.AsUint32 = MmioRead32((UINTN)&Reg->PRES_STATE);
    UINT32 Retry = USDHC_POLL_RETRY_COUNT;

    while (!PresState.Fields.SDSTB &&
           Retry) {
        gBS->Stall(USDHC_POLL_WAIT_US);
        --Retry;
        PresState.AsUint32 = MmioRead32((UINTN)&Reg->PRES_STATE);
    }

    if (!PresState.Fields.SDSTB) {
        ASSERT(!Retry);
        LOG_ERROR("Time-out waiting on SD clock to stabilize");
        DumpState(SdhcCtx);
        return EFI_TIMEOUT;
    }

    SysCtrl.AsUint32 = MmioRead32((UINTN)&Reg->SYS_CTRL);
    SysCtrl.Fields.SDCLKFS = BestPrescaler / (MixCtrl.Fields.DDR_EN ? 4 : 2);
    SysCtrl.Fields.DVS = BestDivisor - 1;

    MmioWrite32((UINTN)&Reg->SYS_CTRL, SysCtrl.AsUint32);

    SDCLK = USDHC_BASE_CLOCK_FREQ_HZ / (BestPrescaler * BestDivisor);

    LOG_TRACE(
        "Current SDCLK:%dHz SDCLKFS:0x%x DVS:0x%x",
        SDCLK,
        (UINT32)SysCtrl.Fields.SDCLKFS,
        (UINT32)SysCtrl.Fields.DVS);

    return EFI_SUCCESS;
}

BOOLEAN
SdhcIsCardPresent(
    IN EFI_SDHC_PROTOCOL *This
    )
{
    USDHC_PRIVATE_CONTEXT *SdhcCtx = (USDHC_PRIVATE_CONTEXT*)This->PrivateContext;
    BOOLEAN IsCardPresent;

    if (SdhcCtx->CardDetectSignal == USDHC_SIGNAL_INTERNAL_PIN) {
        USDHC_REGISTERS *Reg = SdhcCtx->RegistersBase;
        USDHC_PRES_STATE_REG PresState; PresState.AsUint32 = MmioRead32((UINTN)&Reg->PRES_STATE);
        IsCardPresent = (PresState.Fields.CINST == 1);
    } else {
        IMX_GPIO_VALUE CardDetectLevel;
        if (USDHC_IS_GPIO_SIGNAL_SOURCE(SdhcCtx->CardDetectSignal)) {
            //
            //Read the state of  CD_B pin for the card socket
            //
            CardDetectLevel =
                ImxGpioRead(
                    SdhcCtx->CardDetectGpioPin.Bank,
                    SdhcCtx->CardDetectGpioPin.IoNumber);
        } else if (SdhcCtx->CardDetectSignal == USDHC_SIGNAL_OVERRIDE_PIN_LOW) {
            CardDetectLevel = IMX_GPIO_LOW;
        } else if (SdhcCtx->CardDetectSignal == USDHC_SIGNAL_OVERRIDE_PIN_HIGH) {
            CardDetectLevel = IMX_GPIO_HIGH;
        } else {
            ASSERT(!"Invalid CardDetect signal source");
            CardDetectLevel = IMX_GPIO_LOW;
        }

        //
        // When no card is present,  CD_B is pulled-high, and the SDCard when
        // inserted will pull CD_B low
        // CD_B=0 means card present, while CD_B=1 means card not present
        //
        IsCardPresent = (CardDetectLevel == IMX_GPIO_LOW);
    }

  // Enable if needed while trace debugging, otherwise this will flood the debug
  // console due to being called periodically every second for each SDHC
#if 0
  LOG_TRACE("SdhcIsCardPresent(): %d", IsCardPresent);
#endif

    return IsCardPresent;
}

BOOLEAN
SdhcIsReadOnly(
    IN EFI_SDHC_PROTOCOL *This
    )
{
    USDHC_PRIVATE_CONTEXT *SdhcCtx = (USDHC_PRIVATE_CONTEXT*)This->PrivateContext;
    BOOLEAN IsReadOnly;

    if (SdhcCtx->WriteProtectSignal == USDHC_SIGNAL_INTERNAL_PIN) {
        USDHC_REGISTERS *Reg = SdhcCtx->RegistersBase;
        USDHC_PRES_STATE_REG PresState; PresState.AsUint32 = MmioRead32((UINTN)&Reg->PRES_STATE);
        IsReadOnly = (PresState.Fields.WPSPL == 0);
    } else {
        IMX_GPIO_VALUE WriteProtectLevel;
        if (USDHC_IS_GPIO_SIGNAL_SOURCE(SdhcCtx->WriteProtectSignal)) {
            //
            //Read the state of  WP pin for the card socket
            //
            WriteProtectLevel =
                ImxGpioRead(
                    SdhcCtx->WriteProtectGpioPin.Bank,
                    SdhcCtx->WriteProtectGpioPin.IoNumber);
        } else if (SdhcCtx->WriteProtectSignal == USDHC_SIGNAL_OVERRIDE_PIN_LOW) {
            WriteProtectLevel = IMX_GPIO_LOW;
        } else if (SdhcCtx->WriteProtectSignal == USDHC_SIGNAL_OVERRIDE_PIN_HIGH) {
            WriteProtectLevel = IMX_GPIO_HIGH;
        } else {
            ASSERT(!"Invalid WriteProtect signal source");
            WriteProtectLevel = IMX_GPIO_LOW;
        }

        //
        // When no card is present,  WP is pulled-high, and the SDCard when
        // inserted will pull WP low if WP switch is configured to write enable
        // the SDCard, otherwise it WP will stay pulled-high
        // WP=0 means write enabled, while WP=1 means write protected
        //
         IsReadOnly = (WriteProtectLevel != IMX_GPIO_LOW);
    }

    LOG_TRACE("SdhcIsReadOnly(): %d", IsReadOnly);
    return IsReadOnly;
}

EFI_STATUS
SdhcSendCommand(
    IN EFI_SDHC_PROTOCOL *This,
    IN const SD_COMMAND *Cmd,
    IN UINT32 Argument,
    IN OPTIONAL const SD_COMMAND_XFR_INFO *XfrInfo
    )
{
    EFI_STATUS Status;
    USDHC_PRIVATE_CONTEXT *SdhcCtx = (USDHC_PRIVATE_CONTEXT*)This->PrivateContext;
    USDHC_REGISTERS *Reg = SdhcCtx->RegistersBase;

    LOG_TRACE(
        "SdhcSendCommand(%cCMD%d, %08x)",
        ((Cmd->Class == SdCommandClassApp) ? 'A' : ' '),
        (UINT32)Cmd->Index,
        Argument);

    Status = WaitForCmdAndOrDataLine(SdhcCtx, Cmd);
    if (Status != EFI_SUCCESS) {
        LOG_ERROR("SdhcWaitForCmdAndDataLine failed");
        return Status;
    }

    //
    // Clear Interrupt status
    //
    MmioWrite32((UINTN)&Reg->INT_STATUS, (UINT32)~0);

    //
    // Setup data transfer command
    //
    if (XfrInfo) {
        if (XfrInfo->BlockCount > USDHC_MAX_BLOCK_COUNT) {
            LOG_ERROR(
                "Provided %d block count while SDHC max block count is %d",
                XfrInfo->BlockCount,
                USDHC_MAX_BLOCK_COUNT);
            return EFI_INVALID_PARAMETER;
        }

        //
        // Set block size and count
        //
        USDHC_BLK_ATT_REG BlkAtt = { 0 };
        BlkAtt.Fields.BLKSIZE = XfrInfo->BlockSize;
        ASSERT (XfrInfo->BlockCount > 0);
        BlkAtt.Fields.BLKCNT = XfrInfo->BlockCount;
        MmioWrite32((UINTN)&Reg->BLK_ATT, BlkAtt.AsUint32);

        //
        // Set transfer parameters
        //
        USDHC_MIX_CTRL_REG MixCtrl = { 0 };
        if (Cmd->TransferDirection == SdTransferDirectionRead) {
            MixCtrl.Fields.DTDSEL = 1;
        }

        if (XfrInfo->BlockCount > 1) {
            ASSERT((Cmd->TransferType == SdTransferTypeMultiBlock) ||
                (Cmd->TransferType == SdTransferTypeMultiBlockNoStop));
            MixCtrl.Fields.MSBSEL = 1;
            MixCtrl.Fields.BCEN = 1;
        }

        MmioWrite32((UINTN)&Reg->MIX_CTRL, MixCtrl.AsUint32);

        USDHC_WTMK_LVL_REG WtmkLvl = { 0 };

#if 0
        //
        // Set FIFO watermarks
        //
        // Configure FIFO watermark levels to 1/2 the FIFO capacity for read,
        // and 1/3 the FIFO capacity for write.
        // In case the whole transfer can fit in the FIFO, then use
        // the whole transfer length as the FIFO threshold, so we do
        // the read/write in one-shot
        //

        UINT32 FifoThresholdWordCount;
        if (Cmd->TransferDirection == SdTransferDirectionRead) {
            FifoThresholdWordCount = USDHC_FIFO_MAX_WORD_COUNT / 2;
        } else {
            FifoThresholdWordCount = USDHC_FIFO_MAX_WORD_COUNT / 3;
        }

        ASSERT(XfrInfo->BlockSize % sizeof(UINT32) == 0);
        UINT32 TransferByteLength = XfrInfo->BlockSize * XfrInfo->BlockCount;
        const UINT32 TransferWordCount = TransferByteLength / sizeof(UINT32);
        FifoThresholdWordCount = MIN(TransferWordCount, FifoThresholdWordCount);

        ASSERT(FifoThresholdWordCount <= 0xFFFF);
        const UINT16 Wml = (UINT16)FifoThresholdWordCount;
        ASSERT(Wml <= USDHC_FIFO_MAX_WORD_COUNT);

        if (Cmd->TransferDirection == SdTransferDirectionRead) {
            WtmkLvl.Fields.RD_WML = (UINT8)Wml;
            WtmkLvl.Fields.RD_BRST_LEN = MIN(Wml, 8);
        } else {
            WtmkLvl.Fields.WR_WML = (UINT8)Wml;
            WtmkLvl.Fields.WR_BRST_LEN = MIN(Wml, 8);;
        }
#endif

#if 0
        WtmkLvl.Fields.RD_WML = 64;
        WtmkLvl.Fields.RD_BRST_LEN = 16;
        WtmkLvl.Fields.WR_WML = 64;
        WtmkLvl.Fields.WR_BRST_LEN = 16;
#endif

        UINT32 WtmkThreshold = USDHC_BLOCK_LENGTH_BYTES / 4;
        if (Cmd->TransferDirection == SdTransferDirectionRead) {
            if (WtmkThreshold > USDHC_WTMK_RD_WML_MAX_VAL) {
                WtmkThreshold = USDHC_WTMK_RD_WML_MAX_VAL;
            }
            WtmkLvl.Fields.RD_WML = WtmkThreshold;
        } else {
            if (WtmkThreshold > USDHC_WTMK_WR_WML_MAX_VAL) {
                WtmkThreshold = USDHC_WTMK_WR_WML_MAX_VAL;
            }
            WtmkLvl.Fields.WR_WML = WtmkThreshold;
        }

        MmioWrite32((UINTN)&Reg->WTMK_LVL, WtmkLvl.AsUint32);
    }

    //
    // Set CMD parameters
    //
    USDHC_CMD_XFR_TYP_REG CmdXfrTyp = { 0 };
    CmdXfrTyp.Fields.CMDINX = Cmd->Index;

    switch (Cmd->ResponseType) {
    case SdResponseTypeNone:
        break;

    case SdResponseTypeR1:
    case SdResponseTypeR5:
    case SdResponseTypeR6:
        CmdXfrTyp.Fields.RSPTYP = USDHC_CMD_XFR_TYP_RSPTYP_RSP_48;
        CmdXfrTyp.Fields.CICEN = 1;
        CmdXfrTyp.Fields.CCCEN = 1;
        break;

    case SdResponseTypeR1B:
    case SdResponseTypeR5B:
        CmdXfrTyp.Fields.RSPTYP = USDHC_CMD_XFR_TYP_RSPTYP_RSP_48_CHK_BSY;
        CmdXfrTyp.Fields.CICEN = 1;
        CmdXfrTyp.Fields.CCCEN = 1;
        break;

    case SdResponseTypeR2:
        CmdXfrTyp.Fields.RSPTYP = USDHC_CMD_XFR_TYP_RSPTYP_RSP_136;
        CmdXfrTyp.Fields.CCCEN = 1;
        break;

    case SdResponseTypeR3:
    case SdResponseTypeR4:
        CmdXfrTyp.Fields.RSPTYP = USDHC_CMD_XFR_TYP_RSPTYP_RSP_48;
        break;

    default:
        LOG_ASSERT("SdhcSendCommand(): Invalid response type");
        return EFI_INVALID_PARAMETER;
    }

    if (Cmd->Type == SdCommandTypeAbort) {
        CmdXfrTyp.Fields.CMDTYP = USDHC_CMD_XFR_TYP_CMDTYP_ABORT;
    }

    if (XfrInfo) {
        CmdXfrTyp.Fields.DPSEL = 1;
    }

    //
    // Send command and wait for response
    //
    MmioWrite32((UINTN)&Reg->CMD_ARG, Argument);
    MmioWrite32((UINTN)&Reg->CMD_XFR_TYP, CmdXfrTyp.AsUint32);

    Status = WaitForCmdResponse(SdhcCtx);
    if (EFI_ERROR(Status)) {
        LOG_ERROR("WaitForCmdResponse() failed. %r", Status);
        return Status;
    }

    return EFI_SUCCESS;
}

EFI_STATUS
SdhcReceiveResponse(
    IN EFI_SDHC_PROTOCOL *This,
    IN const SD_COMMAND *Cmd,
    OUT UINT32 *Buffer
    )
{

    USDHC_PRIVATE_CONTEXT *SdhcCtx = (USDHC_PRIVATE_CONTEXT*)This->PrivateContext;

    if (Buffer == NULL) {
        LOG_ERROR("Input Buffer is NULL");
        return EFI_INVALID_PARAMETER;
    }

    USDHC_REGISTERS *Reg = SdhcCtx->RegistersBase;

    switch (Cmd->ResponseType) {
    case SdResponseTypeNone:
        break;
    case SdResponseTypeR1:
    case SdResponseTypeR1B:
    case SdResponseTypeR3:
    case SdResponseTypeR4:
    case SdResponseTypeR5:
    case SdResponseTypeR5B:
    case SdResponseTypeR6:
        Buffer[0] = MmioRead32((UINTN)&Reg->CMD_RSP0);
        LOG_TRACE(
            "SdhcReceiveResponse(Type: %x), Buffer[0]: %08x",
            Cmd->ResponseType,
            Buffer[0]);
        break;
    case SdResponseTypeR2:
        Buffer[0] = MmioRead32((UINTN)&Reg->CMD_RSP0);
        Buffer[1] = MmioRead32((UINTN)&Reg->CMD_RSP1);
        Buffer[2] = MmioRead32((UINTN)&Reg->CMD_RSP2);
        Buffer[3] = MmioRead32((UINTN)&Reg->CMD_RSP3);

        LOG_TRACE(
            "SdhcReceiveResponse(Type: %x), Buffer[0-3]: %08x, %08x, %08x, %08x",
            Cmd->ResponseType,
            Buffer[0],
            Buffer[1],
            Buffer[2],
            Buffer[3]);
        break;
    default:
        LOG_ASSERT("SdhcReceiveResponse(): Invalid response type");
        return EFI_INVALID_PARAMETER;
    }

    return EFI_SUCCESS;
}

EFI_STATUS
SdhcReadBlockData(
    IN EFI_SDHC_PROTOCOL *This,
    IN UINTN LengthInBytes,
    OUT UINT32* Buffer
    )
{
    USDHC_PRIVATE_CONTEXT *SdhcCtx = (USDHC_PRIVATE_CONTEXT*)This->PrivateContext;

    LOG_TRACE(
        "SdhcReadBlockData(LengthInBytes: 0x%x, Buffer: 0x%x)",
        LengthInBytes,
        Buffer);

    ASSERT(Buffer != NULL);
    ASSERT(LengthInBytes % sizeof(UINT32) == 0);

    UINTN WordIdx = 0;
    UINTN NumWords = LengthInBytes / sizeof(UINT32);
    USDHC_REGISTERS *Reg = SdhcCtx->RegistersBase;
    USDHC_WTMK_LVL_REG WtmkLvl; WtmkLvl.AsUint32 = MmioRead32((UINTN)&Reg->WTMK_LVL);
    UINT32 FifoWords;
    EFI_STATUS Status;

    ASSERT(WtmkLvl.Fields.RD_WML > 0);

    while (WordIdx < NumWords) {
        Status = WaitForReadFifo(SdhcCtx);
        if (EFI_ERROR(Status)) {
            LOG_ERROR(
                "WaitForReadFifo() failed at Word%d. %r",
                (UINT32)WordIdx,
                Status);
            return Status;
        }

        FifoWords = WtmkLvl.Fields.RD_WML;
        while (WordIdx < NumWords && FifoWords--) {
            Buffer[WordIdx] = MmioRead32((UINTN)&Reg->DATA_BUFF_ACC_PORT);
            ++WordIdx;
        }
    }

    return EFI_SUCCESS;
}

EFI_STATUS
SdhcWriteBlockData(
    IN EFI_SDHC_PROTOCOL *This,
    IN UINTN LengthInBytes,
    IN const UINT32* Buffer
    )
{
    USDHC_PRIVATE_CONTEXT *SdhcCtx = (USDHC_PRIVATE_CONTEXT*)This->PrivateContext;

    LOG_TRACE(
        "SdhcWriteBlockData(LengthInBytes: 0x%x, Buffer: 0x%x)",
        LengthInBytes,
        Buffer);

    ASSERT(Buffer != NULL);
    ASSERT(LengthInBytes % USDHC_BLOCK_LENGTH_BYTES == 0);

    const UINTN BlockWordCount = USDHC_BLOCK_LENGTH_BYTES / sizeof(UINT32);
    UINTN NumBlocks = LengthInBytes / USDHC_BLOCK_LENGTH_BYTES;
    USDHC_REGISTERS *Reg = SdhcCtx->RegistersBase;
    USDHC_INT_STATUS_REG IntStatus;
    USDHC_PRES_STATE_REG PresState;
    INT32 Timeout = 100000; // Nothing special about that constant

    while (NumBlocks > 0) {
        UINTN RemainingWords = BlockWordCount;
        IntStatus.AsUint32 = MmioRead32((UINTN)&Reg->INT_STATUS);
        PresState.AsUint32 = MmioRead32((UINTN)&Reg->PRES_STATE);
        while (!PresState.Fields.BWEN && --Timeout);
        if (Timeout <= 0) {
            LOG_ERROR ("Timeout waiting for FIFO PRES_STATE.BWEN flag");
            return EFI_TIMEOUT;
        }

        while (RemainingWords > 0 && !IntStatus.Fields.TC) {
            MicroSecondDelay (100);
            IntStatus.AsUint32 = MmioRead32((UINTN)&Reg->INT_STATUS);
            MmioWrite32((UINTN)&Reg->DATA_BUFF_ACC_PORT, *Buffer);
            Buffer++;
            RemainingWords--;
        }
        NumBlocks--;
    }

    return EFI_SUCCESS;
}

EFI_STATUS
SdhcSoftwareReset(
    IN EFI_SDHC_PROTOCOL *This,
    IN SDHC_RESET_TYPE ResetType
    )
{
    USDHC_PRIVATE_CONTEXT *SdhcCtx = (USDHC_PRIVATE_CONTEXT*)This->PrivateContext;
    USDHC_REGISTERS *Reg = SdhcCtx->RegistersBase;

    UINT32 Retry;

    if (ResetType == SdhcResetTypeAll) {
        LOG_TRACE("SdhcSoftwareReset(ALL)");
        //
        // Software reset for ALL
        //
        USDHC_SYS_CTRL_REG SysCtrl; SysCtrl.AsUint32 = MmioRead32((UINTN)&Reg->SYS_CTRL);
        SysCtrl.Fields.RSTA = 1;
        MmioWrite32((UINTN)&Reg->SYS_CTRL, SysCtrl.AsUint32);
        Retry = USDHC_POLL_RETRY_COUNT;
        //
        // Wait for reset to complete
        //
        while (SysCtrl.Fields.RSTA && Retry) {
            --Retry;
            gBS->Stall(USDHC_POLL_WAIT_US);
            SysCtrl.AsUint32 = MmioRead32((UINTN)&Reg->SYS_CTRL);
        }

        if (SysCtrl.Fields.RSTA) {
            ASSERT(!Retry);
            LOG_ERROR("Time-out waiting on RSTA for self-clear");
            return EFI_TIMEOUT;
        }

        //
        // Disconnect interrupt signals between SDHC and GIC
        //
        MmioWrite32((UINTN)&Reg->INT_SIGNAL_EN, 0);

        //
        // Clear and Enable all interrupts
        //
        MmioWrite32((UINTN)&Reg->INT_STATUS, (UINT32)~0);
        MmioWrite32((UINTN)&Reg->INT_STATUS_EN, (UINT32)~0);

        LOG_TRACE("Waiting for CMD and DATA lines");

        //
        // Wait for CMD and DATA lines to become available
        //
        EFI_STATUS Status = WaitForCmdAndOrDataLine(SdhcCtx, NULL);
        if (Status != EFI_SUCCESS) {
            LOG_ERROR("SdhcWaitForCmdAndDataLine() failed. %r", Status);
            return Status;
        }

        //
        // Send 80 clock ticks to power-up the card
        //
        SysCtrl.AsUint32 = MmioRead32((UINTN)&Reg->SYS_CTRL);
        SysCtrl.Fields.INITA = 1;
        MmioWrite32((UINTN)&Reg->SYS_CTRL, SysCtrl.AsUint32);
        Retry = USDHC_POLL_RETRY_COUNT;

        //
        // Wait for the 80 clock ticks to complete
        //
        while (SysCtrl.Fields.INITA && Retry) {
            --Retry;
            gBS->Stall(USDHC_POLL_WAIT_US);
            SysCtrl.AsUint32 = MmioRead32((UINTN)&Reg->SYS_CTRL);
        }

        if (SysCtrl.Fields.INITA) {
            ASSERT(!Retry);
            LOG_ERROR("Time-out waiting on INITA for self-clear");
            return EFI_TIMEOUT;
        }

        LOG_TRACE("Card power-up complete");

        //
        // Set max data-timout counter value
        //
        SysCtrl.AsUint32 = MmioRead32((UINTN)&Reg->SYS_CTRL);
        SysCtrl.Fields.DTOCV = 0xF;
        MmioWrite32((UINTN)&Reg->SYS_CTRL, SysCtrl.AsUint32);

        //
        // Reset Mixer Control
        //
        MmioWrite32((UINTN)&Reg->MIX_CTRL, 0);

        USDHC_PROT_CTRL_REG ProtCtrl = { 0 };
        ProtCtrl.Fields.EMODE = USDHC_PROT_CTRL_EMODE_LITTLE_ENDIAN;
        ProtCtrl.Fields.LCTL = 1;
        MmioWrite32((UINTN)&Reg->PROT_CTRL, ProtCtrl.AsUint32);

        LOG_TRACE("Reset ALL complete");

    }else if (ResetType == SdhcResetTypeCmd) {
        LOG_TRACE("SdhcSoftwareReset(CMD)");
        //
        // Software reset for CMD
        //
        USDHC_SYS_CTRL_REG SysCtrl; SysCtrl.AsUint32 = MmioRead32((UINTN)&Reg->SYS_CTRL);
        SysCtrl.Fields.RSTC = 1;
        MmioWrite32((UINTN)&Reg->SYS_CTRL, SysCtrl.AsUint32);
        Retry = USDHC_POLL_RETRY_COUNT;

        //
        // Wait for reset to complete
        //
        while (SysCtrl.Fields.RSTC && Retry) {
            --Retry;
            gBS->Stall(USDHC_POLL_WAIT_US);
            SysCtrl.AsUint32 = MmioRead32((UINTN)&Reg->SYS_CTRL);
        }

        if (SysCtrl.Fields.RSTC) {
            ASSERT(!Retry);
            LOG_ERROR("Time-out waiting on RSTC for self-clear");
            return EFI_TIMEOUT;
        }

        MmioWrite32((UINTN)&Reg->INT_STATUS, (UINT32)~0);

        LOG_TRACE("Reset CMD complete");

    } else if (ResetType == SdhcResetTypeData) {
        LOG_TRACE("SdhcSoftwareReset(DAT)");
        //
        // Software reset for DAT
        //
        USDHC_SYS_CTRL_REG SysCtrl; SysCtrl.AsUint32 = MmioRead32((UINTN)&Reg->SYS_CTRL);
        SysCtrl.Fields.RSTD = 1;
        MmioWrite32((UINTN)&Reg->SYS_CTRL, SysCtrl.AsUint32);
        Retry = USDHC_POLL_RETRY_COUNT;

        //
        // Wait for reset to complete
        //
        while (SysCtrl.Fields.RSTD && Retry) {
            --Retry;
            gBS->Stall(USDHC_POLL_WAIT_US);
            SysCtrl.AsUint32 = MmioRead32((UINTN)&Reg->SYS_CTRL);
        }

        if (SysCtrl.Fields.RSTD) {
            ASSERT(!Retry);
            LOG_ERROR("Time-out waiting on RSTD for self-clear");
            return EFI_TIMEOUT;
        }

        MmioWrite32((UINTN)&Reg->INT_STATUS, (UINT32)~0);

        LOG_TRACE("Reset DAT complete");

    } else {
        return EFI_INVALID_PARAMETER;
    }

    return EFI_SUCCESS;
}

VOID
SdhcCleanup(
    IN EFI_SDHC_PROTOCOL *This
    )
{
    if (This->PrivateContext != NULL) {
        FreePool(This->PrivateContext);
        This->PrivateContext = NULL;
    }

    FreePool(This);

    //
    // Any SDHC protocol call to this instance is illegal beyond this point
    //
}

VOID
SdhcGetCapabilities(
    IN EFI_SDHC_PROTOCOL *This,
    OUT SDHC_CAPABILITIES *Capabilities
  )
{
    USDHC_PRIVATE_CONTEXT *SdhcCtx = (USDHC_PRIVATE_CONTEXT*)This->PrivateContext;
    USDHC_REGISTERS *Reg = SdhcCtx->RegistersBase;

    USDHC_HOST_CTRL_CAP_REG Caps; Caps.AsUint32 = MmioRead32((UINTN)&Reg->HOST_CTRL_CAP);

    Capabilities->MaximumBlockSize = (UINT32)(512 << Caps.Fields.MBL);
    Capabilities->MaximumBlockCount = 0xFFFF; // UINT16_MAX
}


EFI_SDHC_PROTOCOL gSdhcProtocolTemplate =
{
    SDHC_PROTOCOL_INTERFACE_REVISION,   // Revision
    0,                                  // DeviceId
    NULL,                               // PrivateContext
    SdhcGetCapabilities,
    SdhcSoftwareReset,
    SdhcSetClock,
    SdhcSetBusWidth,
    SdhcIsCardPresent,
    SdhcIsReadOnly,
    SdhcSendCommand,
    SdhcReceiveResponse,
    SdhcReadBlockData,
    SdhcWriteBlockData,
    SdhcCleanup
};

EFI_STATUS
uSdhcDeviceRegister(
    IN EFI_HANDLE ImageHandle,
    IN UINT32 SdhcId,
    IN VOID* RegistersBase,
    IN USDHC_SIGNAL_SOURCE CardDetectSignal,
    IN USDHC_SIGNAL_SOURCE WriteProtectSignal
    )
{
    EFI_STATUS Status;
    EFI_SDHC_PROTOCOL *SdhcProtocol = NULL;
    USDHC_PRIVATE_CONTEXT *SdhcCtx = NULL;

    if (ImageHandle == NULL ||
        RegistersBase == NULL) {
        Status = EFI_INVALID_PARAMETER;
        goto Exit;
    }

    //
    // Allocate per-device SDHC protocol and private context storage
    //

    SdhcProtocol = AllocateCopyPool(sizeof(EFI_SDHC_PROTOCOL), &gSdhcProtocolTemplate);
    if (SdhcProtocol == NULL) {
        Status =  EFI_OUT_OF_RESOURCES;
        goto Exit;
    }
    SdhcProtocol->SdhcId = SdhcId;
    SdhcProtocol->PrivateContext = AllocateZeroPool(sizeof(USDHC_PRIVATE_CONTEXT));
    if (SdhcProtocol->PrivateContext == NULL) {
        Status = EFI_OUT_OF_RESOURCES;
        goto Exit;
    }

    SdhcCtx = (USDHC_PRIVATE_CONTEXT*)SdhcProtocol->PrivateContext;
    SdhcCtx->SdhcId = SdhcId;
    SdhcCtx->RegistersBase = (USDHC_REGISTERS*)RegistersBase;
    SdhcCtx->CardDetectSignal = CardDetectSignal;
    if (USDHC_IS_GPIO_SIGNAL_SOURCE(SdhcCtx->CardDetectSignal)) {
        SdhcCtx->CardDetectGpioPin.IoNumber = PCD_GPIO_PIN_IO_NUMBER((UINT16)CardDetectSignal);
        SdhcCtx->CardDetectGpioPin.Bank = PCD_GPIO_PIN_BANK(CardDetectSignal);
    }

    SdhcCtx->WriteProtectSignal= WriteProtectSignal;
    if (USDHC_IS_GPIO_SIGNAL_SOURCE(SdhcCtx->WriteProtectSignal)) {
        SdhcCtx->WriteProtectGpioPin.IoNumber = PCD_GPIO_PIN_IO_NUMBER((UINT16)WriteProtectSignal);
        SdhcCtx->WriteProtectGpioPin.Bank = PCD_GPIO_PIN_BANK(WriteProtectSignal);
    }

    LOG_INFO(
        "Initializing uSDHC%d @%p GPIO CD?:%d WP?:%d",
        SdhcId,
        RegistersBase,
        (USDHC_IS_GPIO_SIGNAL_SOURCE(SdhcCtx->CardDetectSignal) ? 1 : 0),
        (USDHC_IS_GPIO_SIGNAL_SOURCE(SdhcCtx->WriteProtectSignal) ? 1 : 0));

    if (USDHC_IS_GPIO_SIGNAL_SOURCE(SdhcCtx->CardDetectSignal)) {
      LOG_INFO(
          "Using GPIO%d_IO%d for CardDetect",
          SdhcCtx->CardDetectGpioPin.Bank,
          SdhcCtx->CardDetectGpioPin.IoNumber);
    }

    if (USDHC_IS_GPIO_SIGNAL_SOURCE(SdhcCtx->WriteProtectSignal)) {
      LOG_INFO(
          "Using GPIO%d_IO%d for WriteProtect",
          SdhcCtx->WriteProtectGpioPin.Bank,
          SdhcCtx->WriteProtectGpioPin.IoNumber);
    }

    Status = gBS->InstallMultipleProtocolInterfaces(
                                                &SdhcCtx->SdhcProtocolHandle,
                                                &gEfiSdhcProtocolGuid,
                                                SdhcProtocol,
                                                NULL);
    if (EFI_ERROR(Status)) {
        LOG_ERROR("InstallMultipleProtocolInterfaces failed. %r", Status);
        goto Exit;
    }

Exit:
    if (EFI_ERROR(Status)) {
        LOG_ERROR("Failed to register and initialize uSDHC%d", SdhcId);

        if (SdhcProtocol != NULL && SdhcProtocol->PrivateContext != NULL) {
            FreePool(SdhcProtocol->PrivateContext);
            SdhcProtocol->PrivateContext = NULL;
        }

        if (SdhcProtocol != NULL) {
            FreePool(SdhcProtocol);
            SdhcProtocol = NULL;
        }
    }

    return Status;
}

EFI_STATUS
SdhcInitialize(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *SystemTable
    )
{
    EFI_STATUS Status = EFI_SUCCESS;
    UINT32 uSdhcRegisteredCount = 0;

    //
    // Register uSDHC1 through uSDHC4 if their base address is non-zero
    //

    //
    // uSDHC1
    //
    if (FixedPcdGet32(PcdSdhc1Enable)) {
        Status = uSdhcDeviceRegister(
            ImageHandle,
            1,
            (VOID*)FixedPcdGet32(PcdSdhc1Base),
            FixedPcdGet32(PcdSdhc1CardDetectSignal),
            FixedPcdGet32(PcdSdhc1WriteProtectSignal));
        if (!EFI_ERROR(Status)) {
            ++uSdhcRegisteredCount;
        }
    }

    //
    // uSDHC2
    //
    if (FixedPcdGet32(PcdSdhc2Enable)) {
        Status = uSdhcDeviceRegister(
            ImageHandle,
            2,
            (VOID*)FixedPcdGet32(PcdSdhc2Base),
            FixedPcdGet32(PcdSdhc2CardDetectSignal),
            FixedPcdGet32(PcdSdhc2WriteProtectSignal));
        if (!EFI_ERROR(Status)) {
            ++uSdhcRegisteredCount;
        }
    }

    //
    // uSDHC3
    //
    if (FixedPcdGet32(PcdSdhc3Enable)) {
        Status = uSdhcDeviceRegister(
            ImageHandle,
            3,
            (VOID*)FixedPcdGet32(PcdSdhc3Base),
            FixedPcdGet32(PcdSdhc3CardDetectSignal),
            FixedPcdGet32(PcdSdhc3WriteProtectSignal));
        if (!EFI_ERROR(Status)) {
            ++uSdhcRegisteredCount;
        }
    }

    //
    // uSDHC4
    //
    if (FixedPcdGet32(PcdSdhc4Enable)) {
        Status = uSdhcDeviceRegister(
            ImageHandle,
            4,
            (VOID*)FixedPcdGet32(PcdSdhc4Base),
            FixedPcdGet32(PcdSdhc4CardDetectSignal),
            FixedPcdGet32(PcdSdhc4WriteProtectSignal));
        if (!EFI_ERROR(Status)) {
            ++uSdhcRegisteredCount;
        }
    }

    //
    // Succeed driver loading if at least one enabled uSDHC got registered successfully
    //
    if ((Status != EFI_SUCCESS) && (uSdhcRegisteredCount > 0)) {
        Status = EFI_SUCCESS;
    }

    return Status;
}
