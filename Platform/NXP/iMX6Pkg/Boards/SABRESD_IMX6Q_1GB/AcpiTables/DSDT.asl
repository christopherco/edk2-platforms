/*
* iMX6 Sabre DSDT
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
*/
#define SOC_TYPE 0x00000063  // iMX6 Quad

DefinitionBlock ("DSDT.aml", "DSDT", 5, "MSFT", "EDK2", 1)
{
    Scope (\_SB_)
    {
        include("Dsdt-Common.inc")
        include("Dsdt-Platform.inc")
        include("Dsdt-Gpio.inc")
        include("Dsdt-Gfx.inc")
        include("Dsdt-Usb.inc")
        include("Dsdt-PCIe.inc")
        include("Dsdt-Sdhc.inc")
        include("Dsdt-Enet.inc")
        include("Dsdt-Audio.inc")
        include("Dsdt-AudioCodec.inc")
        include("Dsdt-Uart.inc")
        include("Dsdt-I2c.inc")
        include("Dsdt-Spi.inc")
        include("Dsdt-Rhp.inc")
        include("Dsdt-Buttons.inc")
        include("Dsdt-TrEE.inc")
    } // \_SB_
}
