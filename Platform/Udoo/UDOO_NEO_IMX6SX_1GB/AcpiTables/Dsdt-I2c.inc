//
// Description: I2C Controllers
//

Device (I2C1)
{
   Name (_HID, "FSCL0004")
   Name (_UID, 0x1)
   Method (_STA)
   {
       Return(0xf)
   }
   Method (_CRS, 0x0, NotSerialized) {
       Name (RBUF, ResourceTemplate () {
           MEMORY32FIXED(ReadWrite, 0x021A0000, 0x14, )
           Interrupt(ResourceConsumer, Level, ActiveHigh, Exclusive) { 68 }
       })
       Return(RBUF)
   }
}

Device (I2C2)
{
   Name (_HID, "FSCL0004")
   Name (_UID, 0x2)
   Method (_STA)
   {
       Return(0xf)
   }
   Method (_CRS, 0x0, NotSerialized) {
       Name (RBUF, ResourceTemplate () {
           MEMORY32FIXED(ReadWrite, 0x021A4000, 0x14, )
           Interrupt(ResourceConsumer, Level, ActiveHigh, Exclusive) { 69 }
       })
       Return(RBUF)
   }
}

// Device (I2C3) 
// do not include I2C3 resources since it is only connected to HDMI

Device (I2C4)
{
   Name (_HID, "FSCL0004")
   Name (_UID, 0x4)
   Method (_STA)
   {
       Return(0xf)
   }
   Method (_CRS, 0x0, NotSerialized) {
       Name (RBUF, ResourceTemplate () {
           MEMORY32FIXED(ReadWrite, 0x021F8000, 0x14, )
           Interrupt(ResourceConsumer, Level, ActiveHigh, Exclusive) { 67 }
       })
       Return(RBUF)
   }
}

