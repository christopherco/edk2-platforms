Device (CPU1)
{
    Name (_HID, "UdooNeoM4Comm")
    Name (_CID, "m4comm")
    Name (_UID, 0x1)
    Method (_STA) // Status
    {
        Return(0xf) // Enabled
    }
    Method (_CRS, 0x0, NotSerialized) {
        Name (RBUF, ResourceTemplate () {
            MEMORY32FIXED(ReadWrite, 0x00907000, 0x1000 ) // SOC_OCRAM_M4COMM_BUFFER_BASE
            MEMORY32FIXED(ReadWrite, 0x007F8000, 0x8000 ) // SOC_M4TCM_PHYSICAL_BASE
            MEMORY32FIXED(ReadWrite, 0x020D8000, 0x4000 ) // IMX6SX_PHYSADDR_SRC
            MEMORY32FIXED(ReadWrite, 0x02294000, 0x4001 ) // IMX6SX_PHYSADDR_MU_A
            MEMORY32FIXED(ReadWrite, 0x020C4000, 0x4002 ) // IMX6SX_PHYSADDR_CCM
            Interrupt(ResourceConsumer, Level, ActiveHigh, Exclusive) { 122 } // IMX6SX_IRQ_MU_TO_A9
        })
        Return(RBUF)
    }
}
