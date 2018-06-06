#/** @file
# iMX6Q SabreSD board description
# The board is iMX6Q with 1GB DRAM
#
#  Copyright (c) Microsoft Corporation. All rights reserved.
#
#  This program and the accompanying materials
#  are licensed and made available under the terms and conditions of the BSD License
#  which accompanies this distribution.  The full text of the license may be found at
#  http://opensource.org/licenses/bsd-license.php
#
#  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
#  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
#
#**/

################################################################################
#
# Board [Defines] Section
#
################################################################################

[Defines]
  DEFINE BOARD_NAME               = SABRESD_IMX6Q_1GB
  DEFINE IMX_FAMILY               = IMX6DQ
  DEFINE IMX_CHIP_TYPE            = QUAD
  DEFINE DRAM_SIZE                = DRAM_1GB
  DEFINE CONFIG_DUMP_SYMBOL_INFO  = TRUE

################################################################################
#
# Platform Description
#
################################################################################
!include Platform/NXP/iMX6Pkg/iMX6CommonDsc.inc

################################################################################
#
# Board PCD Sections
#
################################################################################

########################
#
# iMX6Pkg PCDs
#
########################
[PcdsFixedAtBuild.common]

  #
  # uSDHC Controllers as connected on iMX6DQ SabreSD
  #
  # uSDHCx | SabreSD On-board Connection | Physical Base
  #-----------------------------------------------------
  # uSDHC1 | Not Connected               | 0x02190000
  # uSDHC2 | J500 � SD2 AUX SDIO Socket  | 0x02194000
  # uSDHC3 | J507 � SD3 Card Socket      | 0x02198000
  # uSDHC4 | eMMC (SanDisk 8GB MMC 4.41) | 0x0219C000
  #
  giMXPlatformTokenSpaceGuid.PcdSdhc1Base|0x02190000
  giMXPlatformTokenSpaceGuid.PcdSdhc2Base|0x02194000
  giMXPlatformTokenSpaceGuid.PcdSdhc3Base|0x02198000
  giMXPlatformTokenSpaceGuid.PcdSdhc4Base|0x0219C000
  
  #
  # SDCard Slot (uSDHC3)
  #---------------------------------------------------
  # Card Detect Signal   | NANDF_D0 | ALT5 | GPIO2_IO0
  # Write Protect Signal | NANDF_D1 | ALT5 | GPIO2_IO1
  #
  # MSB byte is GPIO bank number, and LSB byte is IO number
  #
  giMXPlatformTokenSpaceGuid.PcdSdhc3Enable|TRUE
  giMXPlatformTokenSpaceGuid.PcdSdhc3CardDetectSignal|0x0200
  #giMXPlatformTokenSpaceGuid.PcdSdhc3WriteProtectSignal|0x0201

  #
  # eMMC Slot (uSDHC4)
  #
  giMXPlatformTokenSpaceGuid.PcdSdhc4Enable|TRUE
  giMXPlatformTokenSpaceGuid.PcdSdhc4CardDetectSignal|0xFF00
  giMXPlatformTokenSpaceGuid.PcdSdhc4WriteProtectSignal|0xFF01

  #
  # GPIO reset pin
  #
  giMX6TokenSpaceGuid.PcdPcieResetGpio|TRUE
  giMX6TokenSpaceGuid.PcdPcieResetGpioBankNumber|7
  giMX6TokenSpaceGuid.PcdPcieResetGpioIoNumber|12

  #
  # No UART initialization required leveraging the first boot loader
  #
  giMXPlatformTokenSpaceGuid.PcdSerialRegisterBase|0x02020000   # UART1
  giMXPlatformTokenSpaceGuid.PcdKdUartInstance|1                # UART1

