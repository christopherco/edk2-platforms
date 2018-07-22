/*
* Description: iMX6 Quad Ultra Secured Digital Host Controllers (uSDHC)
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

// uSDHC1: WLAN SDIO Socket
Device (SDH1)
{
    Name (_HID, "FSCL0008")
    Name (_UID, 0x1)

    Method (_STA)
    {
        Return(0xf)
    }

    Name (_S1D, 0x1)
    Name (_S2D, 0x1)
    Name (_S3D, 0x1)
    Name (_S4D, 0x1)

    Method (_CRS, 0x0, NotSerialized)
    {
        Name (RBUF, ResourceTemplate () {
            MEMORY32FIXED(ReadWrite, 0x02190000, 0x4000, )
            Interrupt(ResourceConsumer, Level, ActiveHigh, Exclusive) { 54 }
        })
        Return(RBUF)
    }

    Name (_DSD, Package()
    {
        ToUUID ("DAFFD814-6EBA-4D8C-8A91-BC9BBF4AA301"),
        Package ()
        {
            Package (2) { "BaseClockFrequencyHz", 198000000 },  // SDHC Base/Input Clock: 198MHz
            Package (2) { "Regulator1V8Exist", 0 },             // 1.8V Switching External Circuitry: Not-Implemented
            Package (2) { "SlotCount", 1 },                     // Number of SD/MMC slots connected on the bus: 1
            Package (2) { "RegisterBasePA", 0x02190000 }        // Register base physical address
        }
    })

    Device (SD0)
    {
        Method (_ADR)
        {
            Return (0)
        }

        Method (_RMV)
        {
            Return (0)
        }
    }
}

// uSDHC2: SDCard Socket
Device (SDH2)
{
    Name (_HID, "FSCL0008")
    Name (_UID, 0x2)

    Method (_STA) {
        Return(0xf)
    }

    Name (_S1D, 0x1)
    Name (_S2D, 0x1)
    Name (_S3D, 0x1)
    Name (_S4D, 0x1)

    Method (_CRS, 0x0, NotSerialized)
    {
        Name (RBUF, ResourceTemplate () {
            MEMORY32FIXED(ReadWrite, 0x02194000, 0x4000, )
            Interrupt(ResourceConsumer, Level, ActiveHigh, Exclusive) { 55 }
        })
        Return(RBUF)
    }

    Name (_DSD, Package()
    {
        ToUUID ("DAFFD814-6EBA-4D8C-8A91-BC9BBF4AA301"),
        Package ()
        {
            Package (2) { "BaseClockFrequencyHz", 198000000 },  // SDHC Base/Input Clock: 198MHz
                                                                // ** Temporary disable circuitry until stability is investigated. **
            Package (2) { "Regulator1V8Exist", 0 },             // 1.8V Switching External Circuitry: Implemented
            Package (2) { "SlotCount", 1 },                     // Number of SD/MMC slots connected on the bus: 1
            Package (2) { "RegisterBasePA", 0x02194000 }        // Register base physical address
        }
    })

    OperationRegion (GPI4, SystemMemory, 0x020A8000, 0x4)

    // SD2_CLK
    // IOMUXC_SW_MUX_CTL_PAD_SD2_CLK
    OperationRegion (MXCK, SystemMemory, 0x020E0354, 0x4)

    // SD2_CMD
    // IOMUXC_SW_PAD_CTL_PAD_SD2_CMD
    OperationRegion (PDCD, SystemMemory, 0x020E0740, 0x4)
    // IOMUXC_SW_MUX_CTL_PAD_SD2_CMD
    OperationRegion (MXCD, SystemMemory, 0x020E0358, 0x4)

    // SD2_DATA0
    // IOMUXC_SW_PAD_CTL_PAD_SD2_DATA0
    OperationRegion (PDD0, SystemMemory, 0x020E0368, 0x4)
    // IOMUXC_SW_MUX_CTL_PAD_SD2_DATA0
    OperationRegion (MXD0, SystemMemory, 0x020E0054, 0x4)

    // SD2_DATA1
    // IOMUXC_SW_PAD_CTL_PAD_SD2_DATA1
    OperationRegion (PDD1, SystemMemory, 0x020E0360, 0x4)
    // IOMUXC_SW_MUX_CTL_PAD_SD2_DATA1
    OperationRegion (MXD1, SystemMemory, 0x020E004C, 0x4)

    // SD2_DATA2
    // IOMUXC_SW_PAD_CTL_PAD_SD2_DATA2
    OperationRegion (PDD2, SystemMemory, 0x020E0364, 0x4)
    // IOMUXC_SW_MUX_CTL_PAD_SD2_DATA2
    OperationRegion (MXD2, SystemMemory, 0x020E0050, 0x4)

    // SD2_DATA3
    // IOMUXC_SW_PAD_CTL_PAD_SD2_DATA3
    OperationRegion (PDD3, SystemMemory, 0x020E0744, 0x4)
    // IOMUXC_SW_MUX_CTL_PAD_SD2_DATA3
    OperationRegion (MXD3, SystemMemory, 0x020E035C, 0x4)

    Field (GPI4, DWordAcc, NoLock, Preserve)
    {
        G4DR, 32,       // GPIOx_DR
    }

    Field (MXCK, DWordAcc, NoLock, Preserve)
    {
        MCCK, 32,       // IOMUXC_SW_MUX_CTL_PAD_SD2_CLK
    }

    Field (MXCD, DWordAcc, NoLock, Preserve)
    {
        MCCD, 32,       // IOMUXC_SW_MUX_CTL_PAD_SD2_CMD
    }

    Field (MXD0, DWordAcc, NoLock, Preserve)
    {
        MCD0, 32,       // IOMUXC_SW_MUX_CTL_PAD_SD2_DATA0
    }

    Field (MXD1, DWordAcc, NoLock, Preserve)
    {
        MCD1, 32,       // IOMUXC_SW_MUX_CTL_PAD_SD2_DATA1
    }

    Field (MXD2, DWordAcc, NoLock, Preserve)
    {
        MCD2, 32,       // IOMUXC_SW_MUX_CTL_PAD_SD2_DATA2
    }

    Field (MXD3, DWordAcc, NoLock, Preserve)
    {
        MCD3, 32,       // IOMUXC_SW_MUX_CTL_PAD_SD2_DATA3
    }

    Field (PDCD, DWordAcc, NoLock, Preserve)
    {
        PCCD, 32,       // IOMUXC_SW_PAD_CTL_PAD_SD2_CMD
    }

    Field (PDD0, DWordAcc, NoLock, Preserve)
    {
        PCD0, 32,       // IOMUXC_SW_PAD_CTL_PAD_SD2_DATA0
    }

    Field (PDD1, DWordAcc, NoLock, Preserve)
    {
        PCD1, 32,       // IOMUXC_SW_PAD_CTL_PAD_SD2_DATA1
    }

    Field (PDD2, DWordAcc, NoLock, Preserve)
    {
        PCD2, 32,       // IOMUXC_SW_PAD_CTL_PAD_SD2_DATA2
    }

    Field (PDD3, DWordAcc, NoLock, Preserve)
    {
        PCD3, 32,       // IOMUXC_SW_PAD_CTL_PAD_SD2_DATA3
    }

    // Device Specific Method takes 4 args:
    //  Arg0 : Buffer containing a UUID [16 bytes]
    //  Arg1 : Integer containing the Revision ID
    //  Arg2 : Integer containing the Function Index
    //  Arg3 : Package that contains function-specific arguments
    Function(_DSM,{BuffObj, IntObj},{BuffObj, IntObj, IntObj, PkgObj})
    {
        Name (REG, 0x0);

        // UUID selector
        switch (ToBuffer (Arg0))
        {
            // SDHC interface identifier
            case (ToUUID ("D4AC1EA1-BC53-416A-9B8C-481FEE75365C"))
            {
                // Function selector
                switch (Arg2)
                {
                // Function 0: Return supported functions, based on revision
                case (0)
                {
                    // Version selector
                    switch (Arg1)
                    {
                        // Revision0: functions {0,1,2} supported
                        case (0) { Return (Buffer (){0x07}); }
                        default { Return (Buffer (){0x01}); }
                    }
                }

                // GPIO4_IO30 is connected to the SDSocket power MOSFET Gate
                // Setting to HIGH turns-off power, while LOW turns-on power

                // Function 1: SDSocket Power-On
                case (1)
                {
                    // Power-On the SD VDD
                    Store (G4DR, REG);
                    And (REG, 0xBFFFFFFF, REG);
                    Store (REG, G4DR);

                    // Connect all SD2 pins by switching them to SD and
                    // enable the pull-up resistor for CMD/DAT[0:3]

                    // SD2_CLK
                    Store (MCCK, REG);
                    And (REG, 0xF8, REG); // ALT0 SD2_CLK
                    Store (REG, MCCK);

                    // SD2_CMD
                    Store (MCCD, REG);
                    And (REG, 0xF8, REG); // ALT0 SD2_CMD
                    Store (REG, MCCD);

                    Store (PCCD, REG);
                    Or (REG, 0x1000, REG);
                    Store (REG, PCCD);

                    // SD2_DATA0
                    Store (MCD0, REG);
                    And (REG, 0xF8, REG); // ALT0 SD2_DATA0
                    Store (REG, MCD0);

                    Store (PCD0, REG);
                    Or (REG, 0x1000, REG);
                    Store (REG, PCD0);

                    // SD2_DATA1
                    Store (MCD1, REG);
                    And (REG, 0xF8, REG); // ALT0 SD2_DATA1
                    Store (REG, MCD1);

                    Store (PCD1, REG);
                    Or (REG, 0x1000, REG);
                    Store (REG, PCD1);

                    // SD2_DATA2
                    Store (MCD2, REG);
                    And (REG, 0xF8, REG); // ALT0 SD2_DATA2
                    Store (REG, MCD2);

                    Store (PCD2, REG);
                    Or (REG, 0x1000, REG);
                    Store (REG, PCD2);

                    // SD2_DATA3
                    Store (MCD3, REG);
                    And (REG, 0xF8, REG); // ALT0 SD2_DATA3
                    Store (REG, MCD3);

                    Store (PCD3, REG);
                    Or (REG, 0x1000, REG);
                    Store (REG, PCD3);

                    Return (0);
                }

                // Function 2: SDSocket Power-Off
                case (2)
                {
                    // Power-Off the SD VDD
                    Store (G4DR, REG);
                    Or (REG, 0x40000000, REG); // Set GPIO4_IO30 value
                    Store (REG, G4DR);

                    // Disconnect all SD2 pins by switching them to GPIO Input
                    // and disable the pull-up resistor on CMD/DAT[0:3]

                    // SD2_CLK
                    Store (MCCK, REG);
                    Or (REG, 0x5, REG); // ALT5 GPIO1_IO10
                    Store (REG, MCCK);

                    // SD2_CMD
                    Store (MCCD, REG);
                    Or (REG, 0x5, REG); // ALT5 GPIO1_IO11
                    Store (REG, MCCD);

                    Store (PCCD, REG);
                    And (REG, 0xEFFF, REG);
                    Store (REG, PCCD);

                    // SD2_DATA0
                    Store (MCD0, REG);
                    Or (REG, 0x5, REG); // ALT5 GPIO1_IO15
                    Store (REG, MCD0);

                    Store (PCD0, REG);
                    And (REG, 0xEFFF, REG);
                    Store (REG, PCD0);

                    // SD2_DATA1
                    Store (MCD1, REG);
                    Or (REG, 0x5, REG); // ALT5 GPIO1_IO14
                    Store (REG, MCD1);

                    Store (PCD1, REG);
                    And (REG, 0xEFFF, REG);
                    Store (REG, PCD1);

                    // SD2_DATA2
                    Store (MCD2, REG);
                    Or (REG, 0x5, REG); // ALT5 GPIO1_IO13
                    Store (REG, MCD2);

                    Store (PCD2, REG);
                    And (REG, 0xEFFF, REG);
                    Store (REG, PCD2);

                    // SD2_DATA3
                    Store (MCD3, REG);
                    Or (REG, 0x5, REG); // ALT5 GPIO1_IO12
                    Store (REG, MCD3);

                    Store (PCD3, REG);
                    And (REG, 0xEFFF, REG);
                    Store (REG, PCD3);

                    Return (0);
                }

                default { Return (Buffer (){0}); }
                } // Function
            } // {D4AC1EA1-BC53-416A-9B8C-481FEE75365C}

            default { Return (Buffer (){0}); }
        } // UUID
    } // _DSM

    Device (SD0)
    {
        Method (_ADR)
        {
            Return (0)
        }

        // Despite the SDCard is a removal device, UWF requires the
        // boot device to be non-removable. This is required for the
        // Windows SDCard boot scenario with UWF enabled.
        Method (_RMV)
        {
            Return (0)
        }
    }
}

// uSDHC3: eMMC
Device (SDH3)
{
    Name (_HID, "FSCL0008")
    Name (_UID, 0x3)

    Method (_STA)
    {
        Return(0xf)
    }

    Name (_S1D, 0x1)
    Name (_S2D, 0x1)
    Name (_S3D, 0x1)
    Name (_S4D, 0x1)

    Method (_CRS, 0x0, NotSerialized)
    {
        Name (RBUF, ResourceTemplate () {
            MEMORY32FIXED(ReadWrite, 0x02198000, 0x4000, )
            Interrupt(ResourceConsumer, Level, ActiveHigh, Exclusive) { 56 }
        })
        Return(RBUF)
    }

    Name (_DSD, Package()
    {
        ToUUID ("DAFFD814-6EBA-4D8C-8A91-BC9BBF4AA301"),
        Package ()
        {
            Package (2) { "BaseClockFrequencyHz", 198000000 },  // SDHC Base/Input Clock: 198MHz
            Package (2) { "Regulator1V8Exist", 0 },             // 1.8V Switching External Circuitry: N/A
            Package (2) { "SlotCount", 1 },                     // Number of SD/MMC slots connected on the bus: 1
            Package (2) { "RegisterBasePA", 0x02198000 }        // Register base physical address
        }
    })

    Device (MMC0)
    {
        Method (_ADR)
        {
            Return (0)
        }

        // eMMC is non-removable
        Method (_RMV)
        {
            Return (0)
        }
    }
}
