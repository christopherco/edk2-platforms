//
// Description: USB Host and OTG Controllers
//

//
// CL-SOM-iMX7 USB port 1 (i.MX7 Controller Core 0) supports for OTG signaling, session
// request protocol (SRP), host negotiation protocol (HNP), and attach
// detection protocol (ADP). ADP support includes dedicated timer hardware and
// register interface.
//
// CL-SOM-iMX7 USB port 2 (i.MX7 Controller Core 1) is an OTG capable port but is configured
// to operate in host only mode onboard CL-SOM-iMX7.
//
// CL-SOM-iMX7 USB port 3 (i.MX7 Controller Core 2) is an HSIC capable port onboard CL-SOM-iMX7.
//
// TODO add OTG support once PEP driver is available which is a requirement
// of the UFX/URS framework
//

Device (USB1)
{
    Name (_HID, "FSCL000C")
    Name (_CID, "PNP0D20")
    Name (_UID, 0x1)
    Name (_HRV, 0x1)	// Hardware revision 1 supports integrated Transaction Translator (TT) in PortSC register
    Name (_S0W, 0x0)    // D0 is the lowest supported state to wake itself up

    Method (_STA)
    {
        Return(0xf)
    }

    Method (_CRS, 0x0, NotSerialized) {
        Name (RBUF, ResourceTemplate () {
            MEMORY32FIXED(ReadWrite, 0x30B10100, 0x100, )
            Interrupt(ResourceConsumer, Level, ActiveHigh, SharedAndWake) { 75 }
        })
        Return(RBUF)
    }

    OperationRegion (OTGM, SystemMemory, 0x30B10100, 0x100)
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

Device (USB2)
{
    Name (_HID, "FSCL000C")
    Name (_CID, "PNP0D20")
    Name (_UID, 0x2)
    Name (_HRV, 0x1)	// Hardware revision 1 supports integrated Transaction Translator (TT) in PortSC register
    Name (_S0W, 0x0)    // D0 is the lowest supported state to wake itself up

    Method (_STA)
    {
        Return(0xf)
    }

    Method (_CRS, 0x0, NotSerialized) {
        Name (RBUF, ResourceTemplate () {
            MEMORY32FIXED(ReadWrite, 0x30B20100, 0x100, )
            Interrupt(ResourceConsumer, Level, ActiveHigh, SharedAndWake) { 74 }
        })
        Return(RBUF)
    }

    OperationRegion (OTGM, SystemMemory, 0x30B20100, 0x100)
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

