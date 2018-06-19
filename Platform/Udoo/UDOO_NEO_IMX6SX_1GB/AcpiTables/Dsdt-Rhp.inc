//
// Description: Resource Hub Proxy
//

Device(RHPX)
{
   Name(_HID, "MSFT8000")
   Name(_CID, "MSFT8000")
   Name(_UID, 1)

   Name(_CRS, ResourceTemplate()
   {
       // Index 0
       I2CSerialBus(0xFFFF,, 0,, "\\_SB.I2C1",,,,)  // LVDS CN3, JTAG J11, PMIC

       // Index 1
       I2CSerialBus(0xFFFF,, 0,, "\\_SB.I2C2",,,,)  // J10, J6

//       I2CSerialBus(0xFFFF,, 0,, "\\_SB.I2C3",,,,)  // HDMI

       // Index 2
       I2CSerialBus(0xFFFF,, 0,, "\\_SB.I2C4",,,,)  // Accelerometer, Gyroscope 

       // Index 3
       SPISerialBus(              // SCKL - 
                                  // MOSI - 
                                  // MISO - 
                                  // CE0  - 
           0,                     // Device selection (CE0)
           PolarityLow,           // Device selection polarity
           FourWireMode,          // wiremode
           8,                     // databit len
           ControllerInitiated,   // slave mode
           4000000,               // connection speed
           ClockPolarityLow,      // clock polarity
           ClockPhaseFirst,       // clock phase
           "\\_SB.SPI2",          // ResourceSource: SPI bus controller name
           0,                     // ResourceSourceIndex
                                  // Resource usage
                                  // DescriptorName: creates name for offset of resource descriptor
           )                      // Vendor Data

       // Index 4
       SPISerialBus(              // SCKL - 
                                  // MOSI - 
                                  // MISO - 
                                  // CE0  - 
           0,                     // Device selection (CE0)
           PolarityLow,           // Device selection polarity
           FourWireMode,          // wiremode
           8,                     // databit len
           ControllerInitiated,   // slave mode
           4000000,               // connection speed
           ClockPolarityLow,      // clock polarity
           ClockPhaseFirst,       // clock phase
           "\\_SB.SPI3",          // ResourceSource: SPI bus controller name
           0,                     // ResourceSourceIndex
                                  // Resource usage
                                  // DescriptorName: creates name for offset of resource descriptor
           )                      // Vendor Data

       // Index 5
       SPISerialBus(              // SCKL - 
                                  // MOSI - 
                                  // MISO - 
                                  // CE0  - 
           0,                     // Device selection (CE0)
           PolarityLow,           // Device selection polarity
           FourWireMode,          // wiremode
           8,                     // databit len
           ControllerInitiated,   // slave mode
           4000000,               // connection speed
           ClockPolarityLow,      // clock polarity
           ClockPhaseFirst,       // clock phase
           "\\_SB.SPI5",          // ResourceSource: SPI bus controller name
           0,                     // ResourceSourceIndex
                                  // Resource usage
                                  // DescriptorName: creates name for offset of resource descriptor
           )                      // Vendor Data

// ** reserved for I2C channel 2
// GPIO1_IO02 PAD_GPIO1_IO02
// GPIO1_IO03 PAD_GPIO1_IO03

// ** reserved for debug UARTS
//       // GPIO1_IO04 PAD_GPIO1_IO04 -- UART1_TX
//       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 4 }
//       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 4 }

//       // GPIO1_IO05 PAD_GPIO1_IO05 -- UART1_RX
//       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 5 }
//       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 5 }

//       // GPIO1_IO06 PAD_GPIO1_IO06 -- UART2_TX
//       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 6 }
//       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 6 }

//       // GPIO1_IO07 PAD_GPIO1_IO07 -- UART2_RX
//       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 7 }
//       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 7 }

       // GPIO1_IO14 PAD_CSI_DATA00
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 14 }
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 14 }

       // GPIO1_IO15 PAD_CSI_DATA01
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 15 }
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 15 }

       // GPIO1_IO16 PAD_CSI_DATA02
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 16 }
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 16 }

       // GPIO1_IO17 PAD_CSI_DATA03
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 17 }
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 17 }

       // GPIO1_IO18 PAD_CSI_DATA04
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 18 }
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 18 }

       // GPIO1_IO19 PAD_CSI_DATA05
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 19 }
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 19 }

       // GPIO1_IO20 PAD_CSI_DATA06
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 20 }
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 20 }

       // GPIO1_IO21 PAD_CSI_DATA07
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 21 }
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 21 }

       // GPIO1_IO22 PAD_CSI_HSYNC
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 22 }
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 22 }

       // GPIO1_IO24 PAD_CSI_PIXCLK
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 24 }
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 24 }

       // GPIO1_IO25 PAD_CSI_VSYNC
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 25 }
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 25 }

       // **
       // GPIO4_IO04 PAD_NAND_DATA00 - ECSPI5_MISO
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 100 } // 3 * 32 + 4
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 100 }

       // **
       // GPIO4_IO06 PAD_NAND_DATA02 - ECSPI5_SCLK
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 102 } // 3 * 32 + 6
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 102 }

       // **
       // GPIO4_IO09 PAD_NAND_DATA04 - GPIO_3
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 104 } // 3 * 32 + 8
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 104 }

       // **
       // GPIO4_IO09 PAD_NAND_DATA05 - GPIO_8
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 105 } // 3 * 32 + 9
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 105 }

       // GPIO4_IO10 PAD_NAND_DATA06
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 106 } // 3 * 32 + 10
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 106 }

       // GPIO4_IO11 PAD_NAND_DATA07
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 107 } // 3 * 32 + 11
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 107 }

       // GPIO4_IO20 PAD_QSPI1A_DQS
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 116 } // 3 * 32 + 20
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 116 }

       // GPIO4_IO23 PAD_QSPI1A_SS1_B
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 119 } // 3 * 32 + 23
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 119 }

       // ** MUX required.
       // GPIO4_IO24 PAD_QSPI1B_DATA0
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 120 } // 3 * 32 + 24
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 120 }

       // ** MUX required.
       // GPIO4_IO25 PAD_QSPI1B_DATA1
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 121 } // 3 * 32 + 25
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 121 }

       // GPIO4_IO28 PAD_QSPI1B_DQS
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 124 } // 3 * 32 + 28
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 124 }

       // ** MUX required.
       // GPIO4_IO29 PAD_QSPI1B_SCLK
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 125 } // 3 * 32 + 29
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 125 }

       // ** MUX required.
       // GPIO4_IO30 PAD_QSPI1B_SS0
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 126 } // 3 * 32 + 30
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 126 }

       // GPIO4_IO31 PAD_QSPI1B_SS1_B
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 127 } // 3 * 32 + 31
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 127 }

       // **
       // GPIO5_IO12 PAD_RGMII2_RD0 - PWM_4
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 140 } // 4 * 32 + 12
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 140 }

       // **
       // GPIO5_IO13 PAD_RGMII2_RD0 - PWM_3
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 141 } // 4 * 32 + 13
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 141 }

       // **
       // GPIO5_IO14 PAD_RGMII2_RD2 - PWM_2
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 142 } // 4 * 32 + 14
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 142 }

       // **
       // GPIO5_IO15 PAD_RGMII2_RD3 - PWM_1
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 143 } // 4 * 32 + 15
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 143 }

       // **
       // GPIO5_IO18 PAD_RGMII2_TD0 - PWM_8 ??
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 146 } // 4 * 32 + 18
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 146 }

       // **
       // GPIO5_IO19 PAD_RGMII2_TD1 - PWM_7 ??
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 147 } // 4 * 32 + 19
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 147 }

       // **
       // GPIO5_IO20 PAD_RGMII2_TD2 - PWM_6
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 148 } // 4 * 32 + 20
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 148 }

       // **
       // GPIO5_IO21 PAD_RGMII2_TD2 - PWM_5
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 149 } // 4 * 32 + 21
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 149 }

       // ** MUX required.
       // GPIO5_IO22 PAD_RGMII2_TX_CTL
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 150 } // 4 * 32 + 22
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 150 }

       // ** MUX required.
       // GPIO5_IO27 PAD_RGMII2_RXC
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 155 } // 4 * 32 + 27
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 155 }

       // GPIO6_IO00 PAD_SD1_CLK
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 160 } // 5 * 32 + 0
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 160 }

       // GPIO6_IO12 PAD_SD4_CLK
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 172 } // 5 * 32 + 12
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 172 }

       // GPIO6_IO13 PAD_SD4_CMD
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 173 } // 5 * 32 + 13
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 173 }

       // GPIO6_IO14 PAD_SD4_DATA0
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 174 } // 5 * 32 + 14
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 174 }

       // GPIO6_IO15 PAD_SD4_DATA1
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 175 } // 5 * 32 + 15
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 175 }

       // GPIO6_IO16 PAD_SD4_DATA2
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 176 } // 5 * 32 + 16
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 176 }

       // GPIO6_IO17 PAD_SD4_DATA3
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 177 } // 5 * 32 + 17
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 177 }

       // **
       // GPIO6_IO19 PAD_SD4_DATA4
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 178 } // 5 * 32 + 18
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 178 }

       // **
       // GPIO6_IO19 PAD_SD4_DATA5
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 179 } // 5 * 32 + 19
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 179 }

       // GPIO6_IO20 PAD_SD4_DATA6
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 180 } // 5 * 32 + 20
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 180 }

       // GPIO6_IO21 PAD_SD4_DATA7
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 181 } // 5 * 32 + 21
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 181 }

       // GPIO6_IO22 PAD_SD4_RESET_B
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 182 } // 5 * 32 + 22
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 182 }

       // GPIO7_IO10 PAD_USB_H_DATA
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 202 } // 6 * 32 + 10
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 202 }

       // GPIO7_IO11 PAD_USB_H_STROBE
       GpioIO(Shared, PullUp, 0, 0, IoRestrictionNone, "\\_SB.GPIO", 0, ResourceConsumer, , ) { 203 } // 6 * 32 + 11
       GpioInt(Edge, ActiveBoth, Shared, PullUp, 0, "\\_SB.GPIO",) { 203 }
   })

   Name(_DSD, Package()
   {
       ToUUID("daffd814-6eba-4d8c-8a91-bc9bbf4aa301"),
       Package()
       {
           Package(2) { "bus-I2C-I2C1", Package() { 0 }},
           Package(2) { "bus-I2C-I2C2", Package() { 1 }},
           Package(2) { "bus-I2C-I2C4", Package() { 2 }},

           // SPI 2
           Package(2) { "bus-SPI-SPI2", Package() { 3 }},                        // Index 3
           Package(2) { "SPI2-MinClockInHz", 115 },                              // 115 Hz
           Package(2) { "SPI2-MaxClockInHz", 8000000 },                          // 8 MHz
           Package(2) { "SPI2-SupportedDataBitLengths", Package() { 8,16,32 }},  // Data bit length

           // SPI 3
           Package(2) { "bus-SPI-SPI3", Package() { 4 }},                        // Index 4
           Package(2) { "SPI3-MinClockInHz", 115 },                              // 115 Hz
           Package(2) { "SPI3-MaxClockInHz", 8000000 },                          // 8 MHz
           Package(2) { "SPI3-SupportedDataBitLengths", Package() { 8,16,32 }},  // Data bit length

           // SPI 5
           Package(2) { "bus-SPI-SPI5", Package() { 5 }},                        // Index 5
           Package(2) { "SPI5-MinClockInHz", 115 },                              // 115 Hz
           Package(2) { "SPI5-MaxClockInHz", 8000000 },                          // 8 MHz
           Package(2) { "SPI5-SupportedDataBitLengths", Package() { 8,16,32 }},  // Data bit length

           // GPIO Pin Count and supported drive modes
           Package (2) { "GPIO-PinCount", 204 },
           Package (2) { "GPIO-UseDescriptorPinNumbers", 1 },

           // InputHighImpedance, InputPullUp, InputPullDown, OutputCmos
           Package (2) { "GPIO-SupportedDriveModes", 0xf },
       }
   })
}