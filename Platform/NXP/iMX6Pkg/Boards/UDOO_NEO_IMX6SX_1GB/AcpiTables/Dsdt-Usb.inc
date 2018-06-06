//
// Description: EHCI USB Controllers
//

Device (USB2)
{
    Name (_HID, "FSCL000C")
    Name (_CID, "PNP0D20")
    Name (_UID, 0x1)
    Name (_S0W, 0x3)
    Name (_HRV, 0x1)	// Hardware revision 1 supports integrated Transaction Translator (TT) in PortSC register
    Method (_STA)
    {
        Return(0xf)
    }
    Method (_CRS, 0x0, NotSerialized) {
        Name (RBUF, ResourceTemplate () {
            MEMORY32FIXED(ReadWrite, 0x02184300, 0x100 )
            Interrupt(ResourceConsumer, Level, ActiveHigh, Exclusive) { 74 }
        })
        Return(RBUF)
    }

    OperationRegion (OTGM, SystemMemory, 0x02184300, 0x100)
    Field (OTGM, WordAcc, NoLock, Preserve)
    {
        Offset(0x84),   // skip to register 84h
        PTSC, 32,       // port status control
        Offset(0xA8),   // skip to register A8h
        DSBM, 32,       // UOG_USBMOD
    }

    Name (REG, 0x0);    // Declare register read variable
    Method (_UBF, 0x0, NotSerialized) {
        //
        // Reset handled by driver so no reset required here
        //
        Store(0x03, DSBM);          // set host mode & little endian
        Store(PTSC, REG);           // read PORTSC status
        Store(OR(REG,0x2),PTSC);    // clear current PORTSC status
    }
}
