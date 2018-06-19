#define SOC_TYPE 0x00000062    // iMX6 SoloX

DefinitionBlock ("DSDT.aml", "DSDT", 5, "MSFT", "EDK2", 1)
{
    Scope (\_SB_)
    {
        include("Dsdt-Common.inc")
        include("Dsdt-Platform.inc")
        include("Dsdt-Gpio.inc")
        include("Dsdt-Usb.inc")
        include("Dsdt-PCIe.inc")
        include("Dsdt-Sdhc.inc")
        include("Dsdt-Enet.inc")
        include("Dsdt-M4Comm.inc")
        include("Dsdt-Uart.inc")
        include("Dsdt-I2c.inc")
        include("Dsdt-Spi.inc")
        include("Dsdt-Rhp.inc")
        include("Dsdt-Pwm.inc")
        include("Dsdt-TrEE.inc")
    } // \_SB_
}
