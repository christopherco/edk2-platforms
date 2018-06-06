//
// Description: SPI Controllers
//

Device (SPI1)
{
    Name (_HID, "FSCL0005")
    Name (_UID, 0x1)
    Method (_STA)
    {
        Return(0xf)
    }
    Method (_CRS, 0x0, NotSerialized) {
        Name (RBUF, ResourceTemplate () {
            MEMORY32FIXED(ReadWrite, 0x02008000, 0x4000, )
            Interrupt(ResourceConsumer, Level, ActiveHigh, Exclusive) { 63 }
            
            // CS0 (CSI0_DATA07) GPIO5_IO25
            GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 153 }

            // MISO: PAD_CSI0_DATA06 (GPIO5_IO24) Alt2
            // MOSI: PAD_CSI0_DATA05 (GPIO5_IO23) Alt2
            // SCLK: PAD_CSI0_DATA04 (GPIO5_IO22) Alt2 
            MsftFunctionConfig(Exclusive, PullDown, IMX_ALT2, "\\_SB.GPIO", 0, ResourceConsumer, ) { 152, 151, 150 }
        })
        Return(RBUF)
    }
}

Device (SPI2)
{
    Name (_HID, "FSCL0005")
    Name (_UID, 0x2)
    Method (_STA)
    {
        Return(0xf)
    }
    Method (_CRS, 0x0, NotSerialized) {
        Name (RBUF, ResourceTemplate () {
            MEMORY32FIXED(ReadWrite, 0x0200C000, 0x4000, )
            Interrupt(ResourceConsumer, Level, ActiveHigh, Exclusive) { 64 }
            
            // CS0 (PAD_EIM_RW) GPIO2_IO26
            GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 58 }				
            
            // MISO: PAD_EIM_OE_B (GPIO2_IO25) Alt2
            // MOSI: PAD_EIM_CS1_B (GPIO2_IO24) Alt2
            // SCLK: PAD_EIM_CS0_B (GPIO2_IO23) Alt2 
            MsftFunctionConfig(Exclusive, PullDown, IMX_ALT2, "\\_SB.GPIO", 0, ResourceConsumer, ) { 57, 56, 55 }
        })
        Return(RBUF)
    }
}

//
// ECSPI3 is available on the Apalis but PADs are shared with SD/MMC.
// Currently it is not exposed!
//

Device (SPI3)
{
    Name (_HID, "FSCL0005")
    Name (_UID, 0x3)
    Method (_STA)
    {
        Return(0x0)
    }
    Method (_CRS, 0x0, NotSerialized) {
        Name (RBUF, ResourceTemplate () {
            MEMORY32FIXED(ReadWrite, 0x02010000, 0x4000, )
            Interrupt(ResourceConsumer, Level, ActiveHigh, Exclusive) { 65 }

			//
			// To do:
			// - Configure GPIOs for CS0..CS3
			// - Configure MsftFunctionConfig() for MISO/MOSI/SCLK
			//
        })
        Return(RBUF)
    }
}
