/** @file
*
*  iMX6 Quad SPI Controller
*
*  Copyright (c) 2018 Microsoft Corporation. All rights reserved.
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

Device (SPI2)
{
  Name (_HID, "NXP0105")
  Name (_UID, 0x2)
  Method (_STA) {
    Return (0xf)
  }
  Method (_CRS, 0x0, NotSerialized) {
    Name (RBUF, ResourceTemplate () {
      MEMORY32FIXED (ReadWrite, 0x0200C000, 0x4000, )
      Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) { 64 }

      // CS0 (PAD_EIM_RW) GPIO2_IO26
      GpioIO (Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0,
              ResourceConsumer,, ) { 58 }
      // CS1 (PAD_EIM_LBA) GPIO2_IO27
      GpioIO (Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0,
              ResourceConsumer,, ) { 59 }

      // MISO: PAD_EIM_OE_B (GPIO2_IO25) Alt2
      // MOSI: PAD_EIM_CS1_B (GPIO2_IO24) Alt2
      // SCLK: PAD_EIM_CS0_B (GPIO2_IO23) Alt2
      MsftFunctionConfig (Exclusive, PullDown, IMX_ALT2, "\\_SB.GPIO", 0,
                          ResourceConsumer, ) { 57, 56, 55 } })
    Return (RBUF)
  }
}
