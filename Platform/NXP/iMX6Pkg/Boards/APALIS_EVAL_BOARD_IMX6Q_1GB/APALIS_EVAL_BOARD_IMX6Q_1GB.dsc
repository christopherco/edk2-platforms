#/** @file
# iMX6Q Toradex Apalis board description
# The board is Toradex Apalis with 1GB DRAM
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
  BOARD_NAME            = APALIS_EVAL_BOARD_IMX6Q_1GB
  DEFINE IMX_FAMILY     = IMX6DQ
  DEFINE IMX_CHIP_TYPE  = QUAD
  DEFINE DRAM_SIZE      = DRAM_1GB

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
# GPIO reset pin, not yet set for APALIS
#
giMX6TokenSpaceGuid.PcdPcieResetGpio|FALSE
giMX6TokenSpaceGuid.PcdPcieResetGpioBankNumber|0
giMX6TokenSpaceGuid.PcdPcieResetGpioIoNumber|0

#
# No UART initialization required leveraging the first boot loader
#
giMXPlatformTokenSpaceGuid.PcdSerialRegisterBase|0x02020000   # UART1
giMXPlatformTokenSpaceGuid.PcdKdUartInstance|1                # UART1
