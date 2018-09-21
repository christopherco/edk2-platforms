/** @file
*
*  iMX6 Quad Ultra Secured Digital Host Controllers (uSDHC)
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

// uSDHC1: WLAN SDIO Socket
Device (SDH1)
{
  Name (_HID, "NXP0108")
  Name (_UID, 0x1)

  Method (_STA) {
    Return (0xf)
  }

  Name (_S1D, 0x1)
  Name (_S2D, 0x1)
  Name (_S3D, 0x1)
  Name (_S4D, 0x1)

  Method (_CRS, 0x0, NotSerialized) {
    Name (RBUF, ResourceTemplate () {
      MEMORY32FIXED (ReadWrite, 0x02190000, 0x4000, )
      Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) { 54 }
    })
    Return (RBUF)
  }

  Device (SD0) {
    Method (_ADR) {
      Return (0)
    }

    Method (_RMV) {
      Return (0)
    }
  }

  Device (TIWL)
  {
    Name (_ADR, 0)
    // TODO: We must replace these HID and CID values with valid ones
    Name (_HID, "TI_WLAN")
    Name (_CID, "TI_WLAN")
    Name (_UID, 1)

    Method (_STA) {
      Return(0xf)
    }

    Method (_CRS, 0x0, NotSerialized) {
      Name (RBUF, ResourceTemplate () {
        GpioInt(Edge, ActiveHigh, Exclusive, PullNone, 0, "\\_SB.GPIO", 0,
                ResourceConsumer,,) { 164 } // WLAN_EN
        GpioIo(Exclusive, PullNone, 0, 2, IoRestrictionOutputOnly,
                "\\_SB.GPIO",0, ResourceConsumer,,) { 154 }
      })
      Return (RBUF)
    }
  }
}

// uSDHC2: SDCard Socket
Device (SDH2)
{
  Name (_HID, "NXP0108")
  Name (_UID, 0x2)

  Method (_STA) {
    Return (0xf)
  }

  Name (_S1D, 0x1)
  Name (_S2D, 0x1)
  Name (_S3D, 0x1)
  Name (_S4D, 0x1)

  Method (_CRS, 0x0, NotSerialized) {
    Name (RBUF, ResourceTemplate () {
      MEMORY32FIXED (ReadWrite, 0x02194000, 0x4000, )
      Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) { 55 }
    })
    Return (RBUF)
  }

  Device (SD0) {
    Method (_ADR) {
      Return (0)
    }

    // Despite the SDCard is a removal device, UWF requires the
    // boot device to be non-removable. This is required for the
    // Windows SDCard boot scenario with UWF enabled.
    Method (_RMV) {
      Return (0)
    }
  }
}

// uSDHC3: eMMC
Device (SDH3)
{
  Name (_HID, "NXP0108")
  Name (_UID, 0x3)

  Method (_STA) {
    Return (0xf)
  }

  Name (_S1D, 0x1)
  Name (_S2D, 0x1)
  Name (_S3D, 0x1)
  Name (_S4D, 0x1)

  Method (_CRS, 0x0, NotSerialized) {
    Name (RBUF, ResourceTemplate () {
      MEMORY32FIXED (ReadWrite, 0x02198000, 0x4000, )
      Interrupt (ResourceConsumer, Level, ActiveHigh, Exclusive) { 56 }
    })
    Return (RBUF)
  }

  Device (MMC0) {
    Method (_ADR) {
      Return (0)
    }

    // eMMC is non-removable
    Method (_RMV) {
      Return (0)
    }
  }
}
