/*
* Description: iMX7 Dual SPI Controllers
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

Device (SPI3)
{
    Name (_HID, "FSCL0005")
    Name (_UID, 0x3)
    Method (_STA)
    {
        Return(0xf)
    }
    Method (_CRS, 0x0, NotSerialized) {
        Name (RBUF, ResourceTemplate () {
                MEMORY32FIXED(ReadWrite, 0x30840000, 0x4000, ) // TODO: Check memory length
                Interrupt(ResourceConsumer, Level, ActiveHigh, Exclusive) { 65 }

                // CS0 (PAD_I2C2_SDA) GPIO4_IO11 (3 * 32 + 11 = 107)
                GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 107 }

                // CS3 (PAD_I2C2_SDA) GPIO5_IO10 (4 * 32 + 10 = 138)
                GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 138 }

                // MISO: PAD_I2C1_SCL (GPIO4_IO08) ALT3 (3 * 32 + 8  = 104)
                // MOSI: PAD_I2C1_SDA (GPIO4_IO09) ALT3 (3 * 32 + 9  = 105)
                // SCLK: PAD_I2C2_SCL (GPIO4_IO10) ALT3 (3 * 32 + 10 = 106)
                MsftFunctionConfig(Exclusive, PullDown, 0x3, "\\_SB.GPIO", 0, ResourceConsumer, ) { 104, 105, 106 }
        })
        Return(RBUF)
    }
}
