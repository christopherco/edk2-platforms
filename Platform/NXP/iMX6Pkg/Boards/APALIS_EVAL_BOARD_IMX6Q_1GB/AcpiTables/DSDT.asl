#define SOC_TYPE 0x00000063  // iMX6 Quad

//
// Configuration area base address.
// layout is described in iMXMiscConfig.h
//

//
// Base address and size needs to match
// PcdMiscConfigBaseAddress & PcdMiscConfigSize.
// Pcd??? variables cannot be used here, since
// this file is consumed by ASL/ASM files.
//
#define IMX_MISC_CONFIG_BASE_ADDR 0x10813000

DefinitionBlock ("DSDT.aml", "DSDT", 5, "MSFT", "EDK2", 1)
{
    Scope (\_SB_)
    {
        include("Dsdt-Common.inc")
        include("Dsdt-Platform.inc")
        include("Dsdt-Gpio.inc")
        include("Dsdt-Gfx.inc")
        include("Dsdt-Usb.inc")
        include("Dsdt-PCIe.inc")
        include("Dsdt-Sdhc.inc")
        include("Dsdt-Enet.inc")
        include("Dsdt-Audio.inc")
        include("Dsdt-Uart.inc")
        include("Dsdt-I2c.inc")
        include("Dsdt-Spi.inc")
        include("Dsdt-Rhp.inc")
    } // \_SB_
}
