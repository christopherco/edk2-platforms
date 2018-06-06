/** @file
*
*  Copyright (c), Microsoft Corporation. All rights reserved.
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

#ifndef _IMX_I2C_H_
#define _IMX_I2C_H_

#pragma pack(push, 1)

typedef union {
  UINT16 AsUint16;
  struct {
    UINT16 Reserved0 : 1;
    UINT16 ADR : 7;
    UINT16 Reserved1 : 8;
  };
} IMX_I2C_IADR_REG;

typedef union {
  UINT16 AsUint16;
  struct {
    UINT16 IC : 6;
    UINT16 Reserved0 : 10;
  };
} IMX_I2C_IFDR_REG;


typedef union {
  UINT16 AsUint16;
  struct {
    UINT16 Reserved0 : 2;
    UINT16 RSTA : 1;
    UINT16 TXAK : 1;
    UINT16 MTX : 1;
    UINT16 MSTA : 1;
    UINT16 IIEN : 1;
    UINT16 IEN : 1;
    UINT16 Reserved1 : 8;
  };
} IMX_I2C_I2CR_REG;

#define IMX_I2C_I2SR_RXAK        0x0001
#define IMX_I2C_I2SR_IIF         0x0002
#define IMX_I2C_I2SR_SRW         0x0004
#define IMX_I2C_I2SR_IAL         0x0010
#define IMX_I2C_I2SR_IBB         0x0020
#define IMX_I2C_I2SR_IAAS        0x0040
#define IMX_I2C_I2SR_ICF         0x0080

typedef union {
  UINT16 AsUint16;
  struct {
    UINT16 RXAK : 1;
    UINT16 IIF : 1;
    UINT16 SRW : 1;
    UINT16 Reserved0 : 1;
    UINT16 IAL : 1;
    UINT16 IBB : 1;
    UINT16 IAAS : 1;
    UINT16 ICF : 1;
    UINT16 Reserved1 : 8;
  };
} IMX_I2C_I2SR_REG;

typedef union {
  UINT16 AsUint16;
  struct {
    UINT16 DATA : 8;
    UINT16 Reserved0 : 8;
  };
} IMX_I2C_I2DR_REG;

typedef struct {
  IMX_I2C_IADR_REG IADR;
  UINT16 Pad0;
  IMX_I2C_IFDR_REG IFDR;
  UINT16 Pad1;
  IMX_I2C_I2CR_REG I2CR;
  UINT16 Pad2;
  IMX_I2C_I2DR_REG I2SR;
  UINT16 Pad3;
  IMX_I2C_I2DR_REG I2DR;
  UINT16 Pad4;
} IMX_I2C_REGS;

#pragma pack(pop)

typedef struct {
  UINT32 ControllerAddress;
  UINT32 ControllerSlaveAddress;
  UINT32 ReferenceFreq;
  UINT32 TargetFreq;
  UINT32 SlaveAddress;
  UINT32 TimeoutInUs;
} IMX_I2C_CONFIG;

/** Performs i2c read operation.

  The iMXI2cRead perform i2c read operation by programming the i2c controller.
  The caller is responsible to provide i2c controller configuration.

  @param[in] IMX_I2C_CONFIG* Structure containing the targeted i2c controller
  to be used for i2c operation. The structure contains important information
  such as the controller base address, reference frequency.
  @param[in] RegisterAddress Targeted device register address to start read.
  @param[out] ReadBufferPtr Caller supplied buffer that would be written into
  with data from the read operation.
  @param[in] ReadBufferSize Size of caller supplied buffer.

  @retval EFI_SUCCESS i2c Read operation succeed.
  @retval !EFI_SUCCESS Failure.

--*/
RETURN_STATUS
iMXI2cRead (
  IN IMX_I2C_CONFIG*  I2cConfigPtr,
  IN UINT8            RegisterAddress,
  OUT UINT8*          ReadBufferPtr,
  IN UINT32           ReadBufferSize
  );

/** Performs i2c write operation.

  The iMXI2cWrite perform i2c write operation by programming the i2c
  controller. The caller is responsible to provide i2c controller
  configuration.

  @param[in] IMX_I2C_CONFIG* Structure containing the targeted i2c controller
  to be used for i2c operation. The structure contains important information
  such as the controller base address, reference frequency.
  @param[in] RegisterAddress Targeted device register address to start write.
  @param[out] WriteBufferPtr Caller supplied buffer that contained data that 
  would be read from for i2c write operation..
  @param[in] WriteBufferSize Size of caller supplied buffer.

  @retval EFI_SUCCESS i2c Write operation succeed.
  @retval !EFI_SUCCESS Failure.

--*/
RETURN_STATUS
iMXI2cWrite (
  IN IMX_I2C_CONFIG*  I2cConfigPtr,
  IN UINT8            RegisterAddress,
  IN UINT8*           WriteBufferPtr,
  IN UINT32           WriteBufferSize
  );

#endif