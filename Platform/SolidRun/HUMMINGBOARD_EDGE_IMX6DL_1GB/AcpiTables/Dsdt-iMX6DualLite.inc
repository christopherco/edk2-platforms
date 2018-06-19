/*
* Description: iMX6 DualLite Processor Devices
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
//
// Description: This is a Processor #0 Device
//

Device (CPU0)
{
   Name (_HID, "ACPI0007")
   Name (_UID, 0x0)
   Method (_STA)
   {
       Return(0xf)
   }
}

//
// Description: This is a Processor #1 Device
//

Device (CPU1)
{
   Name (_HID, "ACPI0007")
   Name (_UID, 0x1)
   Method (_STA)
   {
       Return(0xf)
   }
}

//
// Description: Timers HAL extension
//

Device (EPIT)
{
   Name (_HID, "FSCL0001")
   Name (_UID, 0x0)
   Method (_STA)
   {
       Return(0xf)
   }
}

//
// Description: Platform Extension Plugin
//

Device (PEP0)
{
   Name (_HID, "FSCL0002")
   Name (_UID, 0x0)
   Method (_STA)
   {
       Return(0xf)
   }
   Method (_CRS, 0x0, NotSerialized) {
       Name (RBUF, ResourceTemplate () {
           Interrupt(ResourceConsumer, Level, ActiveHigh, Exclusive) { 119 } // CCM request 1
           Interrupt(ResourceConsumer, Level, ActiveHigh, Exclusive) { 120 } // CCM request 2
           Interrupt(ResourceConsumer, Level, ActiveHigh, Exclusive) { 121 } // GPC request 1
           Interrupt(ResourceConsumer, Level, ActiveHigh, Shared) { 58 }  // UART1
       })
       Return(RBUF)
   }
}