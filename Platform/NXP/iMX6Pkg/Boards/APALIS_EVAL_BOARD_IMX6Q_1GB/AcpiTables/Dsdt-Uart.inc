//
// Description: UART Controllers
//

Device (UAR1)
{
    Name (_HID, "FSCL0006")
    Name (_UID, 0x1)
    Name (_DDN, "UART1")
    Method (_STA)
    {
        Return(0xf)
    }
    Method (_CRS, 0x0, NotSerialized) {
        Name (RBUF, ResourceTemplate () {
            MEMORY32FIXED(ReadWrite, 0x02020000, 0x4000, )
            Interrupt(ResourceConsumer, Level, ActiveHigh, Shared) { 58 }
            
            // DMA channel 2, SDMA_REQ_UART1_RX for UART1 RX DMA
            FixedDMA(SDMA_REQ_UART1_RX, 2, Width8Bit, )           
            // DMA channel 1, SDMA_REQ_UART1_TX for UART1 TX DMA
            FixedDMA(SDMA_REQ_UART1_TX, 1, Width8Bit, )
            
            // UART1_TX_DATA - CSI0_DAT10 - GPIO5_IO28 - 156
            // UART1_RX_DATA - CSI0_DAT11 - GPIO5_IO29 - 157
            MsftFunctionConfig(Exclusive, PullUp, IMX_ALT3, "\\_SB.GPIO", 0, ResourceConsumer, ) { 156, 157 }

            // UART1_RTS_B - EIM_D20 - GPIO3_IO20 - 84
            // UART1_CTS_B - EIM_D19 - GPIO3_IO19 - 83
            MsftFunctionConfig(Exclusive, PullUp, IMX_ALT4, "\\_SB.GPIO", 0, ResourceConsumer, ) { 83, 84 }

            UARTSerialBus(
                115200,
                DataBitsEight,
                StopBitsOne,
                0xC0,                  // LinesInUse
                LittleEndian,
                ParityTypeNone,
                FlowControlNone,
                0,
                0,
                "\\_SB.CPU0",
                0,
                ResourceConsumer,
                ,)
        })
        Return(RBUF)
    }
}

Device (UAR2)
{
    Name (_HID, "FSCL0007")
    Name (_UID, 0x2)
    Name (_DDN, "UART2")
    Method (_STA)
    {
        Return(0xf)
    }
    Method (_CRS, 0x0, NotSerialized) {
        Name (RBUF, ResourceTemplate () {
            MEMORY32FIXED(ReadWrite, 0x021E8000, 0x4000, )
            Interrupt(ResourceConsumer, Level, ActiveHigh, Exclusive) { 59 }

            // DMA channel 4, SDMA_REQ_UART2_RX for UART2 RX DMA
            FixedDMA(SDMA_REQ_UART2_RX, 4, Width8Bit, )           
            // DMA channel 3, SDMA_REQ_UART2_TX for UART2 TX DMA
            FixedDMA(SDMA_REQ_UART2_TX, 3, Width8Bit, )
            
            // UART2_TX_DATA - SD4_DAT7 - GPIO2_IO15 - 47
            // UART2_RX_DATA - SD4_DAT4 - GPIO2_IO12 - 44
            // UART2_RTS_B - SD4_DAT5 - GPIO2_IO13 - 45
            // UART2_CTS_B - SD4_DAT6 - GPIO2_IO14 - 46
            MsftFunctionConfig(Exclusive, PullUp, IMX_ALT2, "\\_SB.GPIO", 0, ResourceConsumer, ) { 44, 45, 46, 47 }

            UARTSerialBus(
                115200,
                DataBitsEight,
                StopBitsOne,
                0xC0,                  // LinesInUse
                LittleEndian,
                ParityTypeNone,
                FlowControlNone,
                0,
                0,
                "\\_SB.CPU0",
                0,
                ResourceConsumer,
                ,)
        })
        Return(RBUF)
    }
}

Device (UAR3)
{
    Name (_HID, "FSCL0007")
    Name (_UID, 0x3)
    Name (_DDN, "UART3")
    Method (_STA)
    {
        Return(0xf)
    }
    Method (_CRS, 0x0, NotSerialized) {
        Name (RBUF, ResourceTemplate () {
            MEMORY32FIXED(ReadWrite, 0x021EC000, 0x4000, )
            Interrupt(ResourceConsumer, Level, ActiveHigh, Exclusive) { 60 }

            // DMA channel 6, SDMA_REQ_UART3_RX for UART3 RX DMA
            FixedDMA(SDMA_REQ_UART3_RX, 6, Width8Bit, )           
            // DMA channel 5, SDMA_REQ_UART3_TX for UART3 TX DMA
            FixedDMA(SDMA_REQ_UART3_TX, 5, Width8Bit, )
            
            // UART3_TX - EIM_D24 - GPIO3_IO24 - 88
            // UART3_RX - EIM_D25 - GPIO3_IO25 - 89
            // UART3_CTS_B - EIM_DATA23 - GPIO3_IO23 - 87
            MsftFunctionConfig(Exclusive, PullUp, IMX_ALT2, "\\_SB.GPIO", 0, ResourceConsumer, ) { 87, 88, 89 }

            // UART3_RTS_B - EIM_EB3 - GPIO2_IO31 - 63
            MsftFunctionConfig(Exclusive, PullUp, IMX_ALT2, "\\_SB.GPIO", 0, ResourceConsumer, ) { 63 }

            UARTSerialBus(
                115200,
                DataBitsEight,
                StopBitsOne,
                0xC0,                  // LinesInUse
                LittleEndian,
                ParityTypeNone,
                FlowControlNone,
                0,
                0,
                "\\_SB.CPU0",
                0,
                ResourceConsumer,
                ,)
        })
        Return(RBUF)
    }
}

Device (UAR4)
{
    Name (_HID, "FSCL0007")
    Name (_UID, 0x4)
    Name (_DDN, "UART4")
    Method (_STA)
    {
        Return(0xf)
    }
    Method (_CRS, 0x0, NotSerialized) {
        Name (RBUF, ResourceTemplate () {
            MEMORY32FIXED(ReadWrite, 0x021F0000, 0x4000, )
            Interrupt(ResourceConsumer, Level, ActiveHigh, Exclusive) { 61 }

            // DMA channel 8, SDMA_REQ_UART4_RX for UART4 RX DMA
            FixedDMA(SDMA_REQ_UART4_RX, 8, Width8Bit, )           
            // DMA channel 7, SDMA_REQ_UART4_TX for UART4 TX DMA
            FixedDMA(SDMA_REQ_UART4_TX, 7, Width8Bit, )
            
            // UART4_TX_DATA - KEY_COL0 - GPIO4_IO06 - 102
            // UART4_RX_DATA - KEY_ROW0 - GPIO4_IO07 - 103
            MsftFunctionConfig(Exclusive, PullUp, IMX_ALT4, "\\_SB.GPIO", 0, ResourceConsumer, ) { 102, 103 }

            UARTSerialBus(
                115200,
                DataBitsEight,
                StopBitsOne,
                0,                  // LinesInUse
                LittleEndian,
                ParityTypeNone,
                FlowControlNone,
                0,
                0,
                "\\_SB.CPU0",
                0,
                ResourceConsumer,
                ,)
        })
        Return(RBUF)
    }
}

Device (UAR5)
{
    Name (_HID, "FSCL0007")
    Name (_UID, 0x5)
    Name (_DDN, "UART5")
    Method (_STA)
    {
        Return(0xf)
    }
    Method (_CRS, 0x0, NotSerialized) {
        Name (RBUF, ResourceTemplate () {
            MEMORY32FIXED(ReadWrite, 0x021F4000, 0x4000, )
            Interrupt(ResourceConsumer, Level, ActiveHigh, Exclusive) { 62 }

            // DMA channel 10, SDMA_REQ_UART5_RX for UART5 RX DMA
            FixedDMA(SDMA_REQ_UART5_RX, 10, Width8Bit, )           
            // DMA channel 9, SDMA_REQ_UART5_TX for UART5 TX DMA
            FixedDMA(SDMA_REQ_UART5_TX, 9, Width8Bit, )
            
            // UART5_TX_DATA - KEY_COL1 - GPIO4_IO08 - 104
            // UART5_RX_DATA - KEY_ROW1 - GPIO4_IO09 - 105
            MsftFunctionConfig(Exclusive, PullUp, IMX_ALT4, "\\_SB.GPIO", 0, ResourceConsumer, ) { 104, 105 }

            UARTSerialBus(
                115200,
                DataBitsEight,
                StopBitsOne,
                0,                  // LinesInUse
                LittleEndian,
                ParityTypeNone,
                FlowControlNone,
                0,
                0,
                "\\_SB.CPU0",
                0,
                ResourceConsumer,
                ,)
        })
        Return(RBUF)
    }
}
