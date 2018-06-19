//
// Description: SPI Controllers - Udoo NEO Imx6 SoloX
//

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
            
            // CS0: PAD_SD4_DATA0 (GPIO6_IO14)       - Udoo pin 39
            GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 174 }
            
            // MISO: PAD_SD4_CLK (GPIO6_IO12) Alt2   - Udoo pin 20
            // MOSI: PAD_SD4_CMD (GPIO6_IO13) Alt2   - Udoo pin 21
            // SCLK: PAD_SD4_DATA1 (GPIO6_IO15) Alt2 - Udoo pin 38
            MsftFunctionConfig(Exclusive, PullDown, IMX_ALT2, "\\_SB.GPIO", 0, ResourceConsumer, ) { 172, 173, 175 }
        })
        Return(RBUF)
    }
}

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
            MEMORY32FIXED(ReadWrite, 0x02010000, 0x4000, )
            Interrupt(ResourceConsumer, Level, ActiveHigh, Exclusive) { 65 }

            // CS0: PAD_SD4_DATA7 (GPIO6_IO21)       - Udoo pin 19
            GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 181 }
            // CS1: PAD_SD4_CMD (GPIO6_IO13)         - Udoo pin 21 ** conflict with SPI2
            GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 173 }
            // CS2: PAD_SD4_CLK (GPIO6_IO12)         - Udoo pin 20 ** conflict with SPI2
            GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 172 }
            // CS3: PAD_SD4_DATA0 (GPIO6_IO14)       - Udoo pin 39
            GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 174 }
            
            // MISO: PAD_SD4_DATA6 (GPIO6_IO20) Alt3 - Udoo pin 18
            // MOSI: PAD_SD4_DATA5 (GPIO6_IO19) Alt3 - Udoo pin Tx (J4) ** conflict with UART5
            // SCLK: PAD_SD4_DATA4 (GPIO6_IO18) Alt3 - Udoo pin Rx (J4) ** conflict with UART5
            MsftFunctionConfig(Exclusive, PullDown, IMX_ALT3, "\\_SB.GPIO", 0, ResourceConsumer, ) { 180, 179, 178 }

/*
//
// Alternate config muxes SPI3 control lines to analog pins, needs additional
// GPIO pins set to configure external 74HC4053AFT device.
//
            // CS0: QSPI1B_SS0_B (GPIO4_IO30)        - Udoo pin A5
            GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 126 }
            // CS1: PAD_SD4_CMD (GPIO6_IO13)         - Udoo pin 21  ** conflict with SPI2
            GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 173 }
            // CS2: PAD_SD4_CLK (GPIO6_IO12)         - Udoo pin 20  ** conflict with SPI2
            GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 172 }
            // CS3: PAD_SD4_DATA0 (GPIO6_IO14)       - Udoo pin 39
            GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 174 }

            // MISO: PAD_QSPI1B_DATA1 (GPIO4_IO25) Alt2 - Udoo pin A1
            // MOSI: PAD_QSPI1B_DATA0 (GPIO4_IO24) Alt2 - Udoo pin A0
            // SCLK: PAD_QSPI1B_SCLK (GPIO4_IO29) Alt2 - Udoo pin A4
            MsftFunctionConfig(Exclusive, PullDown, IMX_ALT2, "\\_SB.GPIO", 0, ResourceConsumer, ) { 121, 120, 125 }
*/
        })
        Return(RBUF)
    }
}

Device (SPI5)
{
    Name (_HID, "FSCL0005")
    Name (_UID, 0x5)
    Method (_STA)
    {
        Return(0xf)
    }
    Method (_CRS, 0x0, NotSerialized) {
        Name (RBUF, ResourceTemplate () {
            MEMORY32FIXED(ReadWrite, 0x0228C000, 0x4000, )
            Interrupt(ResourceConsumer, Level, ActiveHigh, Exclusive) { 50 }

            //
            // SPI5 is reserved for M4 core at boot and routed to inner pins.
            // This config uses outer pins 40 - 43.
            //

            // CS0: PAD_QSPI1B_DQS (GPIO4_IO28)         - Udoo pin 41
            GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 124 }
            
            // MISO: PAD_QSPI1A_SS1_B (GPIO4_IO23) Alt3 - Udoo pin 40
            // MOSI: PAD_QSPI1A_DQS (GPIO4_IO20) Alt3   - Udoo pin 43
            // SCLK: PAD_QSPI1B_SS1_B (GPIO4_IO31) Alt3 - Udoo pin 42
            MsftFunctionConfig(Exclusive, PullDown, IMX_ALT3, "\\_SB.GPIO", 0, ResourceConsumer, ) { 119, 116, 127 }
        })
        Return(RBUF)
    }
}
