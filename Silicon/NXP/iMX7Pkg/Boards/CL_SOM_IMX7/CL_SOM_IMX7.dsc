#/** @file
# Compulab iMX7 Dual SoM board description
#
# The board is iMX7 with 1GB DRAM
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
  DEFINE BOARD_NAME     = CL_SOM_IMX7
  DEFINE IMX_FAMILY     = IMX7
  DEFINE IMX_CHIP_TYPE  = DUAL

################################################################################
#
# Platform Description
#
################################################################################
!include Silicon/NXP/iMX7Pkg/iMX7CommonDsc.inc

################################################################################
#
# Board PCD Sections
#
################################################################################

########################
#
# iMX7Pkg PCDs
#
########################
[PcdsFixedAtBuild.common]

  # System memory size (1GB)
  gArmTokenSpaceGuid.PcdSystemMemorySize|0x40000000

  # uSDHCx | CL_SOM_IMX7 Connections
  #-------------------------------------
  # uSDHC1 | SD Card slot
  # uSDHC2 | WL1801MOD wifi (optional)
  # uSDHC3 | eMMC
  # uSDHC4 | N/A
  #
  giMXPlatformTokenSpaceGuid.PcdSdhc1Enable|TRUE
  giMXPlatformTokenSpaceGuid.PcdSdhc2Enable|FALSE
  giMXPlatformTokenSpaceGuid.PcdSdhc3Enable|TRUE
  giMXPlatformTokenSpaceGuid.PcdSdhc4Enable|FALSE

  giMXPlatformTokenSpaceGuid.PcdSdhc1CardDetectSignal|0xFF00
  giMXPlatformTokenSpaceGuid.PcdSdhc1WriteProtectSignal|0xFF01
  giMXPlatformTokenSpaceGuid.PcdSdhc2CardDetectSignal|0xFF00
  giMXPlatformTokenSpaceGuid.PcdSdhc2WriteProtectSignal|0xFF01
  giMXPlatformTokenSpaceGuid.PcdSdhc3CardDetectSignal|0xFF00
  giMXPlatformTokenSpaceGuid.PcdSdhc3WriteProtectSignal|0xFF01
  giMXPlatformTokenSpaceGuid.PcdSdhc4CardDetectSignal|0xFF00
  giMXPlatformTokenSpaceGuid.PcdSdhc4WriteProtectSignal|0xFF01

  #
  # USB EHCI Controller
  #
  giMX7TokenSpaceGuid.PcdUsbOTGBase|0x30B20000
  giMX7TokenSpaceGuid.PcdUsbEHCILength|0x4000
  giMX7TokenSpaceGuid.PcdIsUsbPortOTG|TRUE

  #
  # Default to watchdog 1
  #
  giMX7TokenSpaceGuid.PcdWatchdogResetIndex|1

  #
  # No UART initialization required. Leveraging the first boot loader
  #
  giMXPlatformTokenSpaceGuid.PcdSerialRegisterBase|0x30860000

