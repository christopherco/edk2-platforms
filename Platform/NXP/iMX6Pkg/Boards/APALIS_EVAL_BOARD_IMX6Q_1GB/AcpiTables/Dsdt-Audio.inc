//
// Description: Synchronous Serial Interface (SSI)
//

Device (SSI1)
{
   Name (_HID, "FSCL000A")
   Name (_UID, 0x1)
   Method (_STA)
   {
       Return(0xf)
   }
   Method (_CRS, 0x0, NotSerialized) {
       Name (RBUF, ResourceTemplate () {
           MEMORY32FIXED(ReadWrite, 0x02028000, 0x4000, )
           Interrupt(ResourceConsumer, Level, ActiveHigh, Exclusive) { 78 }
       })
       Return(RBUF)
   }
}

Device (SSI2)
{
   Name (_HID, "FSCL000A")
   Name (_UID, 0x2)
   Method (_STA)
   {
       Return(0xf)
   }
   Method (_CRS, 0x0, NotSerialized) {
       Name (RBUF, ResourceTemplate () {
           MEMORY32FIXED(ReadWrite, 0x0202C000, 0x4000, )
           Interrupt(ResourceConsumer, Level, ActiveHigh, Exclusive) { 79 }
       })
       Return(RBUF)
   }
}

Device (SSI3)
{
   Name (_HID, "FSCL000A")
   Name (_UID, 0x3)
   Method (_STA)
   {
       Return(0xf)
   }
   Method (_CRS, 0x0, NotSerialized) {
       Name (RBUF, ResourceTemplate () {
           MEMORY32FIXED(ReadWrite, 0x02030000, 0x4000, )
           MEMORY32FIXED(ReadWrite, 0x021d8000, 0x38, ) // AUDMUX block
           Interrupt(ResourceConsumer, Level, ActiveHigh, Exclusive) { 80 }
       })
       Return(RBUF)
   }
}

//
// Description: Asynchronous Sample Rate Converter (ASRC)
//

Device (ASRC)
{
   Name (_HID, "FSCL000B")
   Name (_UID, 0x0)
   Method (_STA)
   {
       Return(0x0)
   }
   Method (_CRS, 0x0, NotSerialized) {
       Name (RBUF, ResourceTemplate () {
           MEMORY32FIXED(ReadWrite, 0x02034000, 0x4000, )
           Interrupt(ResourceConsumer, Level, ActiveHigh, Exclusive) { 82 }
       })
       Return(RBUF)
   }
}