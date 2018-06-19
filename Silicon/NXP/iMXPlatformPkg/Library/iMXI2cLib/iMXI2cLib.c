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
#include <Base.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/IoLib.h>
#include <Library/TimerLib.h>
#include <Library/DebugLib.h>

#include <iMXI2cLib.h>

typedef struct {
  UINT32 Divider;
  UINT32 IC;
} IMX_I2C_DIVIDER;

IMX_I2C_DIVIDER DividerValue[] = {
  { 22, 0x20, },
  { 24, 0x21, },
  { 26, 0x22, },
  { 28, 0x23, },
  { 30, 0x00, },
  { 32, 0x24, },
  { 36, 0x25, },
  { 40, 0x26, },
  { 42, 0x03, },
  { 44, 0x27, },
  { 48, 0x28, },
  { 52, 0x05, },
  { 56, 0x29, },
  { 60, 0x06, },
  { 64, 0x2A, },
  { 72, 0x2B, },
  { 80, 0x2C, },
  { 88, 0x09, },
  { 96, 0x2D, },
  { 104, 0x0A, },
  { 112, 0x2E, },
  { 128, 0x2F, },
  { 144, 0x0C, },
  { 160, 0x30, },
  { 192, 0x31, },
  { 224, 0x32, },
  { 240, 0x0F, },
  { 256, 0x33, },
  { 288, 0x10, },
  { 320, 0x34, },
  { 384, 0x35, },
  { 448, 0x36, },
  { 480, 0x13, },
  { 512, 0x37, },
  { 576, 0x14, },
  { 640, 0x38, },
  { 768, 0x39, },
  { 896, 0x3A, },
  { 960, 0x17, },
  { 1024, 0x3B, },
  { 1152, 0x18, },
  { 1280, 0x3C, },
  { 1536, 0x3D, },
  { 1792, 0x3E, },
  { 1920, 0x1B, },
  { 2048, 0x3F, },
  { 2304, 0x1C, },
  { 2560, 0x1D, },
  { 3072, 0x1E, },
  { 3840, 0x1F, },
};

#define DIVIDER_VALUE_TOTAL (sizeof(DividerValue) / sizeof(DividerValue[0]))

BOOLEAN
iMXI2cWaitStatusSet (
  IMX_I2C_CONFIG* I2cConfigPtr,
  UINT16          StatusBits
  )
{
  UINT32 counter = I2cConfigPtr->TimeoutInUs;
  IMX_I2C_REGS* i2cRegsPtr = (IMX_I2C_REGS*)I2cConfigPtr->ControllerAddress;

  while (counter) {
    IMX_I2C_I2SR_REG i2srReg = { MmioRead16((UINTN)&i2cRegsPtr->I2SR) };

    if ((i2srReg.AsUint16 & StatusBits) == StatusBits) {
      return TRUE;
    }

    MicroSecondDelay(1);
    --counter;
  }

  return FALSE;
}

BOOLEAN
iMXI2cWaitStatusUnSet (
  IMX_I2C_CONFIG* I2cConfigPtr,
  UINT16          StatusBits
)
{
  UINT32 counter = I2cConfigPtr->TimeoutInUs;
  IMX_I2C_REGS* i2cRegsPtr = (IMX_I2C_REGS*)I2cConfigPtr->ControllerAddress;

  while (counter) {
    IMX_I2C_I2SR_REG i2srReg = { MmioRead16((UINTN)&i2cRegsPtr->I2SR) };

    if ((i2srReg.AsUint16 & StatusBits) == 0) {
      return TRUE;
    }

    MicroSecondDelay(1);
    --counter;
  }

  return FALSE;;
}

BOOLEAN
iMXI2cSendByte (
  IMX_I2C_CONFIG* I2cConfigPtr,
  UINT8           Data
)
{
  UINT16 sendData = Data;
  UINT32 counter = I2cConfigPtr->TimeoutInUs;
  IMX_I2C_REGS* i2cRegsPtr = (IMX_I2C_REGS*)I2cConfigPtr->ControllerAddress;

  //
  // Clear status
  //
  MmioWrite16((UINTN)&i2cRegsPtr->I2SR, 0);

  //
  // Transfer byte
  //
  MmioWrite16((UINTN)&i2cRegsPtr->I2DR, sendData);

  while (counter) {
    IMX_I2C_I2SR_REG i2srReg = { MmioRead16((UINTN)&i2cRegsPtr->I2SR) };

    if (i2srReg.IIF == 1) {
      return TRUE;
    }
    else if (i2srReg.IAL == 1) {

      DEBUG((
        DEBUG_ERROR,
        "iMXI2cSendByte: fail 0x%04x\n",
        i2srReg.AsUint16));
      return FALSE;
    }

    MicroSecondDelay(1);
    --counter;
  }

  DEBUG((DEBUG_ERROR, "iMXI2cSendByte: Fail timeout\n"));

  return FALSE;
}

RETURN_STATUS
iMXI2cSetupController (
  IMX_I2C_CONFIG* I2cConfigPtr,
  UINT8           RegisterAddress
  )
{
  IMX_I2C_REGS* i2cRegsPtr = (IMX_I2C_REGS*)I2cConfigPtr->ControllerAddress;

  //
  // Disable controller and clear any pending interrupt
  //
  MmioWrite16((UINTN)&i2cRegsPtr->I2CR, 0);
  MmioWrite16((UINTN)&i2cRegsPtr->I2SR, 0);

  //
  // Setup divider if reference freq is provided. If no use value setup by
  // 1st boot loader
  //
  if (I2cConfigPtr->ReferenceFreq != 0) {

    UINT32 ifdrDiv = 0;
    UINT32 dividerCount;
    UINT32 divider = I2cConfigPtr->ReferenceFreq / I2cConfigPtr->TargetFreq;

    for (dividerCount = 0;
      dividerCount < DIVIDER_VALUE_TOTAL;
      ++dividerCount) {

      if (DividerValue[dividerCount].Divider >= divider) {

        DEBUG((
          DEBUG_INFO,
          "iMXI2cSetupController: divider %d IC 0x%02x\n",
          DividerValue[dividerCount].Divider,
          DividerValue[dividerCount].IC));

        ifdrDiv = DividerValue[dividerCount].IC;
        break;
      }
    }

    if (ifdrDiv == 0) {
      DEBUG((
        DEBUG_ERROR,
        "iMXI2cSetupController: could not find divider for %d\n",
        divider));
      return RETURN_INVALID_PARAMETER;
    }

    MmioWrite16((UINTN)&i2cRegsPtr->IFDR, ifdrDiv);
  }

  //
  // Setup slave address
  //
  MmioWrite16((UINTN)&i2cRegsPtr->IADR, (I2cConfigPtr->ControllerSlaveAddress << 1));

  //
  // Enable controller and set to master mode.
  //
  {
    IMX_I2C_I2CR_REG i2crReg = { MmioRead16((UINTN)&i2cRegsPtr->I2CR) };

    //
    // This bit must be set before any other I2C_I2CR bits have an effect
    //
    i2crReg.IEN = 1;
    MmioWrite16((UINTN)&i2cRegsPtr->I2CR, i2crReg.AsUint16);
    MicroSecondDelay(100);

    MmioWrite16((UINTN)&i2cRegsPtr->I2SR, 0);

    //
    // Wait for bus to be idle
    //
    if (iMXI2cWaitStatusUnSet(I2cConfigPtr, IMX_I2C_I2SR_IBB) == FALSE) {
      DEBUG((DEBUG_ERROR, "iMXI2cGenerateStart: Controller remains busy\n"));
      return RETURN_DEVICE_ERROR;
    }

    i2crReg.MSTA = 1;
    MmioWrite16((UINTN)&i2cRegsPtr->I2CR, i2crReg.AsUint16);

    //
    // Now wait for bus to be busy
    //
    if (iMXI2cWaitStatusSet(I2cConfigPtr, IMX_I2C_I2SR_IBB) == FALSE) {
      DEBUG((DEBUG_ERROR, "iMXI2cGenerateStart: Controller remains idle\n"));
      return RETURN_DEVICE_ERROR;
    }
  }

  return RETURN_SUCCESS;
}

RETURN_STATUS
iMXI2cGenerateStart (
  IMX_I2C_CONFIG* I2cConfigPtr,
  UINT8           RegisterAddress,
  BOOLEAN         Read
  )
{
  BOOLEAN result;
  RETURN_STATUS status;
  IMX_I2C_REGS* i2cRegsPtr = (IMX_I2C_REGS*)I2cConfigPtr->ControllerAddress;

  status = iMXI2cSetupController(
    I2cConfigPtr,
    RegisterAddress);
  if (RETURN_ERROR(status)) {
    DEBUG((DEBUG_ERROR, "iMXI2cGenerateStart: Fail to setup controller %r\n", status));
    return status;
  }

  //
  // Send slave address so set controller to transmit mode
  //
  {
    IMX_I2C_I2CR_REG i2crReg = { MmioRead16((UINTN)&i2cRegsPtr->I2CR) };

    i2crReg.MTX = 1;
    MmioWrite16((UINTN)&i2cRegsPtr->I2CR, i2crReg.AsUint16);
  }

  result = iMXI2cSendByte(
    I2cConfigPtr,
    (I2cConfigPtr->SlaveAddress << 1));
  if (result == FALSE) {
    DEBUG((
      DEBUG_ERROR,
      "iMXI2cGenerateStart: Slave address transfer fail 0x%04x\n",
      MmioRead16((UINTN)&i2cRegsPtr->I2SR)));
    return RETURN_DEVICE_ERROR;
  }

  //
  // Send slave register
  //
  result = iMXI2cSendByte(
    I2cConfigPtr,
    RegisterAddress);
  if (result == FALSE) {
    DEBUG((
      DEBUG_ERROR,
      "iMXI2cGenerateStart: Slave register address transfer fail 0x%04x\n",
      MmioRead16((UINTN)&i2cRegsPtr->I2SR)));
    return RETURN_DEVICE_ERROR;
  }

  return RETURN_SUCCESS;
}

RETURN_STATUS
iMXI2cGenerateStop (
  IMX_I2C_CONFIG* I2cConfigPtr
  )
{
  IMX_I2C_REGS* i2cRegsPtr = (IMX_I2C_REGS*)I2cConfigPtr->ControllerAddress;
  IMX_I2C_I2CR_REG i2crReg = { MmioRead16((UINTN)&i2cRegsPtr->I2CR) };

  i2crReg.MSTA = 0;
  i2crReg.MTX = 0;
  MmioWrite16((UINTN)&i2cRegsPtr->I2CR, i2crReg.AsUint16);

  //
  // Bus should go idle
  //
  if (iMXI2cWaitStatusUnSet(I2cConfigPtr, IMX_I2C_I2SR_IBB) == FALSE) {
    DEBUG((DEBUG_ERROR, "iMXI2cGenerateStop: Controller remains busy\n"));
    return RETURN_DEVICE_ERROR;
  }

  return RETURN_SUCCESS;
}

RETURN_STATUS
iMXI2cRead (
  IN IMX_I2C_CONFIG*  I2cConfigPtr,
  IN UINT8            RegisterAddress,
  OUT UINT8*          ReadBufferPtr,
  IN UINT32           ReadBufferSize
  )
{
  RETURN_STATUS status;
  IMX_I2C_REGS* i2cRegsPtr = (IMX_I2C_REGS*)I2cConfigPtr->ControllerAddress;

  status = iMXI2cGenerateStart(
    I2cConfigPtr,
    RegisterAddress,
    TRUE);
  if (RETURN_ERROR(status)) {
    DEBUG((DEBUG_ERROR, "iMXI2cRead: iMXI2cGenerateStart failed %r\n", status));
    goto Exit;
  }

  //
  // Send slave address again to begin read
  //
  {
    BOOLEAN result;
    IMX_I2C_I2CR_REG i2crReg = { MmioRead16((UINTN)&i2cRegsPtr->I2CR) };

    i2crReg.RSTA = 1; // Repeated start
    MmioWrite16((UINTN)&i2cRegsPtr->I2CR, i2crReg.AsUint16);

    result = iMXI2cSendByte(
      I2cConfigPtr,
      (I2cConfigPtr->SlaveAddress << 1 | 1));
    if (result == FALSE) {
      DEBUG((
        DEBUG_ERROR,
        "iMXI2cRead: 2nd Slave address transfer failed 0x%04x\n",
        MmioRead16((UINTN)&i2cRegsPtr->I2SR)));
      status = RETURN_DEVICE_ERROR;
      goto Exit;
    }
  }

  //
  // Disable master mode
  //
  {
    IMX_I2C_I2CR_REG i2crReg = { MmioRead16((UINTN)&i2cRegsPtr->I2CR) };

    //
    // NXP application note AN4481
    // Only one byte so do not send acknowledge
    //
    if (ReadBufferSize == 1) {
      i2crReg.TXAK = 1;
    }
    else {
      i2crReg.TXAK = 0;
    }

    i2crReg.MTX = 0;
    MmioWrite16((UINTN)&i2cRegsPtr->I2CR, i2crReg.AsUint16);
  }

  //
  // A data transfer can now be initiated by a read from I2C_I2DR in Slave
  // Receive mode.
  //
  {
    MmioWrite16((UINTN)&i2cRegsPtr->I2SR, 0);
    MmioRead16((UINTN)&i2cRegsPtr->I2DR);
  }

  do {
    //
    // Wait for transfer to complete
    //
    if (iMXI2cWaitStatusSet(I2cConfigPtr, IMX_I2C_I2SR_IIF) == FALSE) {
      DEBUG((DEBUG_ERROR, "iMXI2cRead: waiting for read fail\n"));
      status = RETURN_DEVICE_ERROR;
      goto Exit;
    }

    if (iMXI2cWaitStatusSet(I2cConfigPtr, IMX_I2C_I2SR_ICF) == FALSE) {
      DEBUG((DEBUG_ERROR, "iMXI2cRead: waiting for read fail\n"));
      status = RETURN_DEVICE_ERROR;
      goto Exit;
    }

    //
    // Per spec. Before the last byte is read, a Stop signal must be generated
    //
    if (ReadBufferSize == 1) {

      status = iMXI2cGenerateStop(
        I2cConfigPtr);
      if (RETURN_ERROR(status)) {
        DEBUG((DEBUG_ERROR, "iMXI2cRead: iMXI2cGenerateStop fail %r\n", status));
        goto Exit;
      }
    }

    if (ReadBufferSize == 2) {
      IMX_I2C_I2CR_REG i2crReg = { MmioRead16((UINTN)&i2cRegsPtr->I2CR) };

      i2crReg.TXAK = 1;
      MmioWrite16((UINTN)&i2cRegsPtr->I2CR, i2crReg.AsUint16);
    }

    MmioWrite16((UINTN)&i2cRegsPtr->I2SR, 0);

    *ReadBufferPtr = MmioRead8((UINTN)&i2cRegsPtr->I2DR);

    ++ReadBufferPtr;
    --ReadBufferSize;

  } while (ReadBufferSize > 0);

Exit:

  status = iMXI2cGenerateStop(
    I2cConfigPtr);
  if (RETURN_ERROR(status)) {
    DEBUG((DEBUG_ERROR, "iMXI2cRead: Final iMXI2cGenerateStop fail %r\n", status));
  }

  return status;
}

RETURN_STATUS
iMXI2cWrite (
  IN IMX_I2C_CONFIG*  I2cConfigPtr,
  IN UINT8            RegisterAddress,
  IN UINT8*           WriteBufferPtr,
  IN UINT32           WriteBufferSize
  )
{
  RETURN_STATUS status;
  IMX_I2C_REGS* i2cRegsPtr = (IMX_I2C_REGS*)I2cConfigPtr->ControllerAddress;

  status = iMXI2cGenerateStart(
    I2cConfigPtr,
    RegisterAddress,
    FALSE);
  if (RETURN_ERROR(status)) {
    DEBUG((DEBUG_ERROR, "iMXI2cWrite: iMXI2cGenerateStart fail %r\n", status));
    goto Exit;
  }

  while (WriteBufferSize > 0) {

    BOOLEAN result = iMXI2cSendByte(
      I2cConfigPtr,
      *WriteBufferPtr);
    if (result == FALSE) {
      DEBUG((
        DEBUG_ERROR,
        "iMXI2cWrite: Slave address transfer fail 0x%04x\n",
        MmioRead16((UINTN)&i2cRegsPtr->I2SR)));
      status = RETURN_DEVICE_ERROR;
      goto Exit;
    }

    ++WriteBufferPtr;
    --WriteBufferSize;
  }

Exit:
  status = iMXI2cGenerateStop(
    I2cConfigPtr);
  if (RETURN_ERROR(status)) {
    DEBUG((DEBUG_ERROR, "iMXI2cWrite: iMXI2cGenerateStop fail %r\n", status));
  }

  return status;
}