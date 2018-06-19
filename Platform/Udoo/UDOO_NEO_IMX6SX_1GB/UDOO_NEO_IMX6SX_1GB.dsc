#/** @file
# iMX6SoloX UDOO Neo board description
# The board is iMX6SX with 1GB DRAM
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
  BOARD_NAME = UDOO_NEO_IMX6SX_1GB
  DEFINE IMX_FAMILY      = IMX6SX
  DEFINE IMX_CHIP_TYPE   = SOLOX
  DEFINE DRAM_SIZE       = DRAM_1GB
  BOARD_DIR             = Platform/Udoo/$(BOARD_NAME)
  FLASH_DEFINITION      = $(BOARD_DIR)/$(BOARD_NAME).fdf

################################################################################
#
# Platform Description
#
################################################################################
!include Silicon/NXP/iMX6Pkg/iMX6CommonDsc.inc

[LibraryClasses.common]
  UdooNeoI2cLib|$(BOARD_DIR)/Library/UdooNeoI2cLib/UdooNeoI2cLib.inf

[Components.common]
  # M4 Communication (Not currently supported in UEFI)
  #$(BOARD_DIR)/Drivers/M4CommDxe/M4CommDxe.inf

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
# USB EHCI Controller USB OTG2
#
giMX6TokenSpaceGuid.PcdEHCIBase|0x02184200

#
# Enable uSDHC2 Controller.
# Udoo Neo Schem p8, CN2
#
giMXPlatformTokenSpaceGuid.PcdSdhc2Enable|TRUE
giMXPlatformTokenSpaceGuid.PcdSdhc2CardDetectSignal|0xFF00 # Use uSDHC internal CD circuit
giMXPlatformTokenSpaceGuid.PcdSdhc3Enable|FALSE


#
# No UART initialization required leveraging the first boot loader
#
giMXPlatformTokenSpaceGuid.PcdSerialRegisterBase|0x02020000   # UART1
giMXPlatformTokenSpaceGuid.PcdKdUartInstance|1                # UART1