#
# iMX6 Solo SoM board description
# The board is iMX6 Solo with 512MB DRAM
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
#

################################################################################
#
# Board [Defines] Section
#
################################################################################

[Defines]
  DEFINE BOARD_NAME      = HUMMINGBOARD_SOLO_IMX6S_512MB
  DEFINE IMX_FAMILY      = IMX6SDL
  DEFINE IMX_CHIP_TYPE   = SOLO
  DEFINE DRAM_SIZE       = DRAM_512MB

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
# USB EHCI Controller (USB_UH1)
#
giMX6TokenSpaceGuid.PcdEHCIBase|0x02184200

#
# Enable uSDHC2 and uSDHC3 Controllers.
# On HummingboardEdge, SDCard slot is attached to uSDHC2
# with CD wired to SD2_CD_B, eMMC is attached to uSDHC3
#
giMXPlatformTokenSpaceGuid.PcdSdhc2Enable|TRUE
giMXPlatformTokenSpaceGuid.PcdSdhc2CardDetectSignal|0xFFFF # Use uSDHC internal CD circuit
giMXPlatformTokenSpaceGuid.PcdSdhc3Enable|FALSE

#
# UART initialization required
#
giMXPlatformTokenSpaceGuid.PcdSerialRegisterBase|0x02020000   # UART1
giMXPlatformTokenSpaceGuid.PcdKdUartInstance|1                # UART1

#
# GPIO reset pin (PERST)
#
giMX6TokenSpaceGuid.PcdPcieResetGpio|TRUE
giMX6TokenSpaceGuid.PcdPcieResetGpioBankNumber|2
giMX6TokenSpaceGuid.PcdPcieResetGpioIoNumber|11
