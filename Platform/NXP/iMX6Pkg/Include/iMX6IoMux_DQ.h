/** @file
*
*  Header defining IMX6 Dual and Quad Muxing definitions
*
*  Copyright (c), Microsoft Corporation. All rights reserved.
*
*  This program and the accompanying materials
*  are licensed and made available under the terms and conditions of the BSD License
*  which accompanies this distribution.  The full text of the license may be found at
*  http://opensource.org/licenses/bsd-license.php
*
*  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
*  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
*
**/
#ifndef _IMX6_IOMUX_DQ_H_
#define _IMX6_IOMUX_DQ_H_

//
// SELECT INPUT defines

#define EIM_DATA21_ALT6 0x0 // Selecting ALT6 mode of pad EIM_D21 for I2C1_SCL
#define CSI0_DAT9_ALT4 0x1 // Selecting ALT4 mode of pad CSI0_DAT9 for I2C1_SCL

#define EIM_DATA28_ALT1 0x0 // Selecting ALT1 mode of pad EIM_D28 for I2C1_SDA
#define CSI0_DAT8_ALT4 0x1 // Selecting ALT4 mode of pad CSI0_DAT8 for I2C1_SDA

#define EIM_EB2_B_ALT6 0x0 // Selecting ALT6 mode of pad EIM_EB2 for I2C2_SCL
#define KEY_COL3_ALT4 0x1 // Selecting ALT4 mode of pad KEY_COL3 for I2C2_SCL

#define EIM_DATA16_ALT6 0x0 // Selecting ALT6 mode of pad EIM_D16 for I2C2_SDA
#define KEY_ROW3_ALT4 0x1 // Selecting ALT4 mode of pad KEY_ROW3 for I2C2_SDA

#define EIM_DATA17_ALT6 0x0 // Selecting ALT6 mode of pad EIM_D17 for I2C3_SCL
#define GPIO03_ALT2 0x1 // Selecting ALT2 mode of pad GPIO_3 for I2C3_SCL
#define GPIO05_ALT6 0x2 // Selecting ALT6 mode of pad GPIO_5 for I2C3_SCL

#define EIM_DATA18_ALT6 0x0 // Selecting ALT6 mode of pad EIM_D18 for I2C3_SDA
#define GPIO06_ALT2 0x1 // Selecting ALT2 mode of pad GPIO_6 for I2C3_SDA
#define GPIO16_ALT6 0x2 // Selecting ALT6 mode of pad GPIO_16 for I2C3_SDA

#define DISP0_DATA19_ALT3 0
#define KEY_ROW1_ALT2 1

#define DISP0_DATA17_ALT3 0
#define KEY_ROW0_ALT2 1

#define DISP0_DATA16_ALT3 0
#define KEY_COL0_ALT2 1

#define DISP0_DATA18_ALT3 0
#define KEY_COL1_ALT2 1

#define EIM_DATA21_ALT4 0
#define KEY_COL4_ALT2 1

#define EIM_DATA30_ALT6 0
#define GPIO03_ALT6 1

#define RGMII_TX_CTL_ALT7 0
#define GPIO16_ALT2 1

#define CSI0_DATA10_ALT3 0 // Selecting ALT3 mode of pad CSI0_DAT10 for UART1_TX_DATA.
#define CSI0_DATA11_ALT3 1 // Selecting ALT3 mode of pad CSI0_DAT11 for UART1_RX_DATA.
#define SD3_DATA7_ALT1 2 // Selecting ALT1 mode of pad SD3_DAT7 for UART1_TX_DATA.
#define SD3_DATA6_ALT1 3 // Selecting ALT1 mode of pad SD3_DAT6 for UART1_RX_DATA.

#define EIM_DATA26_ALT4 0 // Selecting ALT4 mode of pad EIM_D26 for UART2_TX_DATA.
#define EIM_DATA27_ALT4 1 // Selecting ALT4 mode of pad EIM_D27 for UART2_RX_DATA.
#define GPIO07_ALT4 2 // Selecting ALT4 mode of pad GPIO_7 for UART2_TX_DATA.
#define GPIO08_ALT4 3 // Selecting ALT4 mode of pad GPIO_8 for UART2_RX_DATA.
#define SD3_DATA5_ALT1 4 // Selecting ALT1 mode of pad SD3_DAT5 for UART2_TX_DATA.
#define SD3_DATA4_ALT1 5 // Selecting ALT1 mode of pad SD3_DAT4 for UART2_RX_DATA.
#define SD4_DATA4_ALT2 6 // Selecting ALT2 mode of pad SD4_DAT4 for UART2_RX_DATA.
#define SD4_DATA7_ALT2 7 // Selecting ALT2 mode of pad SD4_DAT7 for UART2_TX_DATA.

#define EIM_DATA24_ALT2 0 // Selecting ALT2 mode of pad EIM_D24 for UART3_TX_DATA.
#define EIM_DATA25_ALT2 1 // Selecting ALT2 mode of pad EIM_D25 for UART3_RX_DATA.
#define SD4_CMD_ALT2 2 // Selecting ALT2 mode of pad SD4_CMD for UART3_TX_DATA.
#define SD4_CLK_ALT2 3 // Selecting ALT2 mode of pad SD4_CLK for UART3_RX_DATA.


//
// AUD5 select input register defines.
//
typedef enum {
   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_GPIO00)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_GPIO00)
   IMX_PAD_GPIO_0 = _IMX_PAD(0x5F0, 0x220), // CCM_CLKO1

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_GPIO01)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_GPIO01)
   IMX_PAD_GPIO_1 = _IMX_PAD(0x5F4, 0x224), // ESAI_RX_CLK

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_GPIO02)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_GPIO02)
   IMX_PAD_GPIO_2 = _IMX_PAD(0x604, 0x234), // ESAI_TX_FS

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_GPIO03)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_GPIO03)
   IMX_PAD_GPIO_3 = _IMX_PAD(0x5FC, 0x22C), // ESAI_RX_HF_CLK

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_GPIO04)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_GPIO04)
   IMX_PAD_GPIO_4 = _IMX_PAD(0x608, 0x238), // ESAI_TX_HF_CLK

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_GPIO05)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_GPIO05)
   IMX_PAD_GPIO_5 = _IMX_PAD(0x60C, 0x23C), // ESAI_TX2_RX3

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_GPIO06)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_GPIO06)
   IMX_PAD_GPIO_6 = _IMX_PAD(0x600, 0x230), // ESAI_TX_CLK

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_GPIO07)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_GPIO07)
   IMX_PAD_GPIO_7 = _IMX_PAD(0x610, 0x240), // ESAI_TX4_RX1

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_GPIO08)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_GPIO08)
   IMX_PAD_GPIO_8 = _IMX_PAD(0x614, 0x244), // ESAI_TX5_RX0

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_GPIO09)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_GPIO09)
   IMX_PAD_GPIO_9 = _IMX_PAD(0x5F8, 0x228), // ESAI_RX_FS

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD2_CLK)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD2_CLK)
   IMX_PAD_SD2_CLK = _IMX_PAD(0x73C, 0x354), // SD2_CLK

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD2_CMD)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD2_CMD)
   IMX_PAD_SD2_CMD = _IMX_PAD(0x740, 0x358), // SD2_CMD

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD2_DATA3)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD2_DATA3)
   IMX_PAD_SD2_DAT3 = _IMX_PAD(0x744, 0x35C), // SD2_DATA3

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD2_DATA2)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD2_DATA2)
   IMX_PAD_SD2_DAT2 = _IMX_PAD(0x364, 0x50), // SD2_DATA2

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD2_DATA1)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD2_DATA1)
   IMX_PAD_SD2_DAT1 = _IMX_PAD(0x360, 0x4C), // SD2_DATA1

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD2_DATA0)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD2_DATA0)
   IMX_PAD_SD2_DAT0 = _IMX_PAD(0x368, 0x54), // SD2_DATA0

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD1_DATA0)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD1_DATA0)
   IMX_PAD_SD1_DAT0 = _IMX_PAD(0x728, 0x340), // SD1_DATA0

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD1_DATA1)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD1_DATA1)
   IMX_PAD_SD1_DAT1 = _IMX_PAD(0x724, 0x33C), // SD1_DATA1

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD1_CMD)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD1_CMD)
   IMX_PAD_SD1_CMD = _IMX_PAD(0x730, 0x348), // SD1_CMD

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD1_DATA2)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD1_DATA2)
   IMX_PAD_SD1_DAT2 = _IMX_PAD(0x734, 0x34C), // SD1_DATA2

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD1_CLK)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD1_CLK)
   IMX_PAD_SD1_CLK = _IMX_PAD(0x738, 0x350), // SD1_CLK

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD1_DATA3)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD1_DATA3)
   IMX_PAD_SD1_DAT3 = _IMX_PAD(0x72C, 0x344), // SD1_DATA3

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_ENET_MDIO)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_ENET_MDIO)
   IMX_PAD_ENET_MDIO = _IMX_PAD(0x4E4, 0x1D0), // ENET_MDIO

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_ENET_REF_CLK)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_ENET_REF_CLK)
   IMX_PAD_ENET_REF_CLK = _IMX_PAD(0x4E8, 0x1D4), // ENET_TX_CLK

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_ENET_RX_ER)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_ENET_RX_ER)
   IMX_PAD_ENET_RX_ER = _IMX_PAD(0x4EC, 0x1D8), // USB_OTG_ID

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_ENET_CRS_DV)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_ENET_CRS_DV)
   IMX_PAD_ENET_CRS_DV = _IMX_PAD(0x4F0, 0x1DC), // ENET_RX_EN

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_ENET_RX_DATA1)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_ENET_RX_DATA1)
   IMX_PAD_ENET_RXD1 = _IMX_PAD(0x4F4, 0x1E0), // MLB_SIG

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_ENET_RX_DATA0)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_ENET_RX_DATA0)
   IMX_PAD_ENET_RXD0 = _IMX_PAD(0x4F8, 0x1E4), // XTALOSC_OSC32K_32K_OUT

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_ENET_TX_EN)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_ENET_TX_EN)
   IMX_PAD_ENET_TX_EN = _IMX_PAD(0x4FC, 0x1E8), // ENET_TX_EN

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_ENET_TX_DATA1)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_ENET_TX_DATA1)
   IMX_PAD_ENET_TXD1 = _IMX_PAD(0x500, 0x1EC), // MLB_CLK

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_ENET_TX_DATA0)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_ENET_TX_DATA0)
   IMX_PAD_ENET_TXD0 = _IMX_PAD(0x504, 0x1F0), // ENET_TX_DATA0

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_ENET_MDC)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_ENET_MDC)
   IMX_PAD_ENET_MDC = _IMX_PAD(0x508, 0x1F4), // MLB_DATA

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_DATA00)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_DATA00)
   IMX_PAD_NANDF_D0 = _IMX_PAD(0x6E4, 0x2FC), // NAND_DATA00

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_DATA01)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_DATA01)
   IMX_PAD_NANDF_D1 = _IMX_PAD(0x6E8, 0x300), // NAND_DATA01

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_DATA02)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_DATA02)
   IMX_PAD_NANDF_D2 = _IMX_PAD(0x6EC, 0x304), // NAND_DATA02

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_DATA03)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_DATA03)
   IMX_PAD_NANDF_D3 = _IMX_PAD(0x6F0, 0x308), // NAND_DATA03

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_DATA04)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_DATA04)
   IMX_PAD_NANDF_D4 = _IMX_PAD(0x6F4, 0x30C), // NAND_DATA04

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_DATA05)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_DATA05)
   IMX_PAD_NANDF_D5 = _IMX_PAD(0x6F8, 0x310), // NAND_DATA05

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_DATA06)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_DATA06)
   IMX_PAD_NANDF_D6 = _IMX_PAD(0x6FC, 0x314), // NAND_DATA06

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_DATA07)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_DATA07)
   IMX_PAD_NANDF_D7 = _IMX_PAD(0x700, 0x318), // NAND_DATA07

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD4_DATA0)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD4_DATA0)
   IMX_PAD_SD4_DAT0 = _IMX_PAD(0x704, 0x31C), // SD4_DATA0

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD4_DATA1)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD4_DATA1)
   IMX_PAD_SD4_DAT1 = _IMX_PAD(0x708, 0x320), // SD4_DATA1

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD4_DATA2)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD4_DATA2)
   IMX_PAD_SD4_DAT2 = _IMX_PAD(0x70C, 0x324), // SD4_DATA2

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD4_DATA3)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD4_DATA3)
   IMX_PAD_SD4_DAT3 = _IMX_PAD(0x710, 0x328), // SD4_DATA3

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD4_DATA4)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD4_DATA4)
   IMX_PAD_SD4_DAT4 = _IMX_PAD(0x714, 0x32C), // SD4_DATA4

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD4_DATA5)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD4_DATA5)
   IMX_PAD_SD4_DAT5 = _IMX_PAD(0x718, 0x330), // SD4_DATA5

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD4_DATA6)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD4_DATA6)
   IMX_PAD_SD4_DAT6 = _IMX_PAD(0x71C, 0x334), // SD4_DATA6

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD4_DATA7)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD4_DATA7)
   IMX_PAD_SD4_DAT7 = _IMX_PAD(0x720, 0x338), // SD4_DATA7

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_ADDR22)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_ADDR22)
   IMX_PAD_EIM_A22 = _IMX_PAD(0x3F0, 0xDC), // EIM_ADDR22

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_ADDR21)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_ADDR21)
   IMX_PAD_EIM_A21 = _IMX_PAD(0x3F4, 0xE0), // EIM_ADDR21

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_ADDR20)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_ADDR20)
   IMX_PAD_EIM_A20 = _IMX_PAD(0x3F8, 0xE4), // EIM_ADDR20

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_ADDR19)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_ADDR19)
   IMX_PAD_EIM_A19 = _IMX_PAD(0x3FC, 0xE8), // EIM_ADDR19

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_ADDR18)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_ADDR18)
   IMX_PAD_EIM_A18 = _IMX_PAD(0x400, 0xEC), // EIM_ADDR18

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_ADDR17)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_ADDR17)
   IMX_PAD_EIM_A17 = _IMX_PAD(0x404, 0xF0), // EIM_ADDR17

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_ADDR16)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_ADDR16)
   IMX_PAD_EIM_A16 = _IMX_PAD(0x408, 0xF4), // EIM_ADDR16

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_CS0_B)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_CS0_B)
   IMX_PAD_EIM_CS0 = _IMX_PAD(0x40C, 0xF8), // EIM_CS0_B

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_CS1_B)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_CS1_B)
   IMX_PAD_EIM_CS1 = _IMX_PAD(0x410, 0xFC), // EIM_CS1_B

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_OE_B)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_OE_B)
   IMX_PAD_EIM_OE = _IMX_PAD(0x414, 0x100), // EIM_OE_B

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_RW)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_RW)
   IMX_PAD_EIM_RW = _IMX_PAD(0x418, 0x104), // EIM_RW

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_LBA_B)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_LBA_B)
   IMX_PAD_EIM_LBA = _IMX_PAD(0x41C, 0x108), // EIM_LBA_B

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_EB0_B)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_EB0_B)
   IMX_PAD_EIM_EB0 = _IMX_PAD(0x420, 0x10C), // EIM_EB0_B

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_EB1_B)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_EB1_B)
   IMX_PAD_EIM_EB1 = _IMX_PAD(0x424, 0x110), // EIM_EB1_B

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_EB2_B)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_EB2_B)
   IMX_PAD_EIM_EB2 = _IMX_PAD(0x3A0, 0x8C), // EIM_EB2_B

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_EB3_B)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_EB3_B)
   IMX_PAD_EIM_EB3 = _IMX_PAD(0x3C4, 0xB0), // EIM_EB3_B

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_AD00)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_AD00)
   IMX_PAD_EIM_DA0 = _IMX_PAD(0x428, 0x114), // EIM_AD00

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_AD01)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_AD01)
   IMX_PAD_EIM_DA1 = _IMX_PAD(0x42C, 0x118), // EIM_AD01

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_AD02)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_AD02)
   IMX_PAD_EIM_DA2 = _IMX_PAD(0x430, 0x11C), // EIM_AD02

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_AD03)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_AD03)
   IMX_PAD_EIM_DA3 = _IMX_PAD(0x434, 0x120), // EIM_AD03

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_AD04)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_AD04)
   IMX_PAD_EIM_DA4 = _IMX_PAD(0x438, 0x124), // EIM_AD04

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_AD05)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_AD05)
   IMX_PAD_EIM_DA5 = _IMX_PAD(0x43C, 0x128), // EIM_AD05

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_AD06)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_AD06)
   IMX_PAD_EIM_DA6 = _IMX_PAD(0x440, 0x12C), // EIM_AD06

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_AD07)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_AD07)
   IMX_PAD_EIM_DA7 = _IMX_PAD(0x444, 0x130), // EIM_AD07

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_AD08)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_AD08)
   IMX_PAD_EIM_DA8 = _IMX_PAD(0x448, 0x134), // EIM_AD08

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_AD09)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_AD09)
   IMX_PAD_EIM_DA9 = _IMX_PAD(0x44C, 0x138), // EIM_AD09

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_AD10)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_AD10)
   IMX_PAD_EIM_DA10 = _IMX_PAD(0x450, 0x13C), // EIM_AD10

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_AD11)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_AD11)
   IMX_PAD_EIM_DA11 = _IMX_PAD(0x454, 0x140), // EIM_AD11

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_AD12)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_AD12)
   IMX_PAD_EIM_DA12 = _IMX_PAD(0x458, 0x144), // EIM_AD12

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_AD13)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_AD13)
   IMX_PAD_EIM_DA13 = _IMX_PAD(0x45C, 0x148), // EIM_AD13

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_AD14)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_AD14)
   IMX_PAD_EIM_DA14 = _IMX_PAD(0x460, 0x14C), // EIM_AD14

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_AD15)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_AD15)
   IMX_PAD_EIM_DA15 = _IMX_PAD(0x464, 0x150), // EIM_AD15

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_DATA16)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_DATA16)
   IMX_PAD_EIM_D16 = _IMX_PAD(0x3A4, 0x90), // EIM_DATA16

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_DATA17)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_DATA17)
   IMX_PAD_EIM_D17 = _IMX_PAD(0x3A8, 0x94), // EIM_DATA17

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_DATA18)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_DATA18)
   IMX_PAD_EIM_D18 = _IMX_PAD(0x3AC, 0x98), // EIM_DATA18

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_DATA19)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_DATA19)
   IMX_PAD_EIM_D19 = _IMX_PAD(0x3B0, 0x9C), // EIM_DATA19

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_DATA20)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_DATA20)
   IMX_PAD_EIM_D20 = _IMX_PAD(0x3B4, 0xA0), // EIM_DATA20

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_DATA21)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_DATA21)
   IMX_PAD_EIM_D21 = _IMX_PAD(0x3B8, 0xA4), // EIM_DATA21

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_DATA22)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_DATA22)
   IMX_PAD_EIM_D22 = _IMX_PAD(0x3BC, 0xA8), // EIM_DATA22

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_DATA23)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_DATA23)
   IMX_PAD_EIM_D23 = _IMX_PAD(0x3C0, 0xAC), // EIM_DATA23

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_DATA24)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_DATA24)
   IMX_PAD_EIM_D24 = _IMX_PAD(0x3C8, 0xB4), // EIM_DATA24

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_DATA25)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_DATA25)
   IMX_PAD_EIM_D25 = _IMX_PAD(0x3CC, 0xB8), // EIM_DATA25

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_DATA26)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_DATA26)
   IMX_PAD_EIM_D26 = _IMX_PAD(0x3D0, 0xBC), // EIM_DATA26

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_DATA27)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_DATA27)
   IMX_PAD_EIM_D27 = _IMX_PAD(0x3D4, 0xC0), // EIM_DATA27

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_DATA28)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_DATA28)
   IMX_PAD_EIM_D28 = _IMX_PAD(0x3D8, 0xC4), // EIM_DATA28

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_DATA29)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_DATA29)
   IMX_PAD_EIM_D29 = _IMX_PAD(0x3DC, 0xC8), // EIM_DATA29

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_DATA30)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_DATA30)
   IMX_PAD_EIM_D30 = _IMX_PAD(0x3E0, 0xCC), // EIM_DATA30

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_DATA31)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_DATA31)
   IMX_PAD_EIM_D31 = _IMX_PAD(0x3E4, 0xD0), // EIM_DATA31

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_GPIO19)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_GPIO19)
   IMX_PAD_GPIO_19 = _IMX_PAD(0x624, 0x254), // KEY_COL5

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_KEY_COL0)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_KEY_COL0)
   IMX_PAD_KEY_COL0 = _IMX_PAD(0x5C8, 0x1F8), // ECSPI1_SCLK

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_KEY_ROW0)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_KEY_ROW0)
   IMX_PAD_KEY_ROW0 = _IMX_PAD(0x5CC, 0x1FC), // ECSPI1_MOSI

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_KEY_COL1)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_KEY_COL1)
   IMX_PAD_KEY_COL1 = _IMX_PAD(0x5D0, 0x200), // ECSPI1_MISO

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_KEY_ROW1)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_KEY_ROW1)
   IMX_PAD_KEY_ROW1 = _IMX_PAD(0x5D4, 0x204), // ECSPI1_SS0

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_KEY_COL2)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_KEY_COL2)
   IMX_PAD_KEY_COL2 = _IMX_PAD(0x5D8, 0x208), // ECSPI1_SS1

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_KEY_ROW2)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_KEY_ROW2)
   IMX_PAD_KEY_ROW2 = _IMX_PAD(0x5DC, 0x20C), // ECSPI1_SS2

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_KEY_COL3)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_KEY_COL3)
   IMX_PAD_KEY_COL3 = _IMX_PAD(0x5E0, 0x210), // ECSPI1_SS3

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_KEY_ROW3)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_KEY_ROW3)
   IMX_PAD_KEY_ROW3 = _IMX_PAD(0x5E4, 0x214), // XTALOSC_OSC32K_32K_OUT

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_KEY_COL4)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_KEY_COL4)
   IMX_PAD_KEY_COL4 = _IMX_PAD(0x5E8, 0x218), // FLEXCAN2_TX

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_KEY_ROW4)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_KEY_ROW4)
   IMX_PAD_KEY_ROW4 = _IMX_PAD(0x5EC, 0x21C), // FLEXCAN2_RX

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_DI0_DISP_CLK)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_DI0_DISP_CLK)
   IMX_PAD_DI0_DISP_CLK = _IMX_PAD(0x470, 0x15C), // IPU1_DI0_DISP_CLK

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_DI0_PIN15)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_DI0_PIN15)
   IMX_PAD_DI0_PIN15 = _IMX_PAD(0x474, 0x160), // IPU1_DI0_PIN15

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_DI0_PIN02)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_DI0_PIN02)
   IMX_PAD_DI0_PIN2 = _IMX_PAD(0x478, 0x164), // IPU1_DI0_PIN02

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_DI0_PIN03)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_DI0_PIN03)
   IMX_PAD_DI0_PIN3 = _IMX_PAD(0x47C, 0x168), // IPU1_DI0_PIN03

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_DI0_PIN04)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_DI0_PIN04)
   IMX_PAD_DI0_PIN4 = _IMX_PAD(0x480, 0x16C), // IPU1_DI0_PIN04

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA00)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_DISP0_DATA00)
   IMX_PAD_DISP0_DAT0 = _IMX_PAD(0x484, 0x170), // IPU1_DISP0_DATA00

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA01)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_DISP0_DATA01)
   IMX_PAD_DISP0_DAT1 = _IMX_PAD(0x488, 0x174), // IPU1_DISP0_DATA01

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA02)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_DISP0_DATA02)
   IMX_PAD_DISP0_DAT2 = _IMX_PAD(0x48C, 0x178), // IPU1_DISP0_DATA02

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA03)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_DISP0_DATA03)
   IMX_PAD_DISP0_DAT3 = _IMX_PAD(0x490, 0x17C), // IPU1_DISP0_DATA03

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA04)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_DISP0_DATA04)
   IMX_PAD_DISP0_DAT4 = _IMX_PAD(0x494, 0x180), // IPU1_DISP0_DATA04

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA05)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_DISP0_DATA05)
   IMX_PAD_DISP0_DAT5 = _IMX_PAD(0x498, 0x184), // IPU1_DISP0_DATA05

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA06)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_DISP0_DATA06)
   IMX_PAD_DISP0_DAT6 = _IMX_PAD(0x49C, 0x188), // IPU1_DISP0_DATA06

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA07)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_DISP0_DATA07)
   IMX_PAD_DISP0_DAT7 = _IMX_PAD(0x4A0, 0x18C), // IPU1_DISP0_DATA07

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA08)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_DISP0_DATA08)
   IMX_PAD_DISP0_DAT8 = _IMX_PAD(0x4A4, 0x190), // IPU1_DISP0_DATA08

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA09)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_DISP0_DATA09)
   IMX_PAD_DISP0_DAT9 = _IMX_PAD(0x4A8, 0x194), // IPU1_DISP0_DATA09

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA10)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_DISP0_DATA10)
   IMX_PAD_DISP0_DAT10 = _IMX_PAD(0x4AC, 0x198), // IPU1_DISP0_DATA10

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_WAIT_B)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_WAIT_B)
   IMX_PAD_EIM_WAIT = _IMX_PAD(0x468, 0x154), // EIM_WAIT_B

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_ADDR25)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_ADDR25)
   IMX_PAD_EIM_A25 = _IMX_PAD(0x39C, 0x88), // EIM_ADDR25

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_ADDR24)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_ADDR24)
   IMX_PAD_EIM_A24 = _IMX_PAD(0x3E8, 0xD4), // EIM_ADDR24

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA11)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_DISP0_DATA11)
   IMX_PAD_DISP0_DAT11 = _IMX_PAD(0x4B0, 0x19C), // IPU1_DISP0_DATA11

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA12)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_DISP0_DATA12)
   IMX_PAD_DISP0_DAT12 = _IMX_PAD(0x4B4, 0x1A0), // IPU1_DISP0_DATA12

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA13)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_DISP0_DATA13)
   IMX_PAD_DISP0_DAT13 = _IMX_PAD(0x4B8, 0x1A4), // IPU1_DISP0_DATA13

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA14)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_DISP0_DATA14)
   IMX_PAD_DISP0_DAT14 = _IMX_PAD(0x4BC, 0x1A8), // IPU1_DISP0_DATA14

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA15)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_DISP0_DATA15)
   IMX_PAD_DISP0_DAT15 = _IMX_PAD(0x4C0, 0x1AC), // IPU1_DISP0_DATA15

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA16)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_DISP0_DATA16)
   IMX_PAD_DISP0_DAT16 = _IMX_PAD(0x4C4, 0x1B0), // IPU1_DISP0_DATA16

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA17)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_DISP0_DATA17)
   IMX_PAD_DISP0_DAT17 = _IMX_PAD(0x4C8, 0x1B4), // IPU1_DISP0_DATA17

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA18)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_DISP0_DATA18)
   IMX_PAD_DISP0_DAT18 = _IMX_PAD(0x4CC, 0x1B8), // IPU1_DISP0_DATA18

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA19)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_DISP0_DATA19)
   IMX_PAD_DISP0_DAT19 = _IMX_PAD(0x4D0, 0x1BC), // IPU1_DISP0_DATA19

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA20)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_DISP0_DATA20)
   IMX_PAD_DISP0_DAT20 = _IMX_PAD(0x4D4, 0x1C0), // IPU1_DISP0_DATA20

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA21)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_DISP0_DATA21)
   IMX_PAD_DISP0_DAT21 = _IMX_PAD(0x4D8, 0x1C4), // IPU1_DISP0_DATA21

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA22)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_DISP0_DATA22)
   IMX_PAD_DISP0_DAT22 = _IMX_PAD(0x4DC, 0x1C8), // IPU1_DISP0_DATA22

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_DISP0_DATA23)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_DISP0_DATA23)
   IMX_PAD_DISP0_DAT23 = _IMX_PAD(0x4E0, 0x1CC), // IPU1_DISP0_DATA23

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI0_PIXCLK)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI0_PIXCLK)
   IMX_PAD_CSI0_PIXCLK = _IMX_PAD(0x628, 0x258), // IPU1_CSI0_PIXCLK

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI0_HSYNC)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI0_HSYNC)
   IMX_PAD_CSI0_MCLK = _IMX_PAD(0x62C, 0x25C), // IPU1_CSI0_HSYNC

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA_EN)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA_EN)
   IMX_PAD_CSI0_DATA_EN = _IMX_PAD(0x630, 0x260), // IPU1_CSI0_DATA_EN

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI0_VSYNC)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI0_VSYNC)
   IMX_PAD_CSI0_VSYNC = _IMX_PAD(0x634, 0x264), // IPU1_CSI0_VSYNC

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA04)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA04)
   IMX_PAD_CSI0_DAT4 = _IMX_PAD(0x638, 0x268), // IPU1_CSI0_DATA04

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA05)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA05)
   IMX_PAD_CSI0_DAT5 = _IMX_PAD(0x63C, 0x26C), // IPU1_CSI0_DATA05

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA06)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA06)
   IMX_PAD_CSI0_DAT6 = _IMX_PAD(0x640, 0x270), // IPU1_CSI0_DATA06

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA07)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA07)
   IMX_PAD_CSI0_DAT7 = _IMX_PAD(0x644, 0x274), // IPU1_CSI0_DATA07

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA08)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA08)
   IMX_PAD_CSI0_DAT8 = _IMX_PAD(0x648, 0x278), // IPU1_CSI0_DATA08

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA09)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA09)
   IMX_PAD_CSI0_DAT9 = _IMX_PAD(0x64C, 0x27C), // IPU1_CSI0_DATA09

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA10)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA10)
   IMX_PAD_CSI0_DAT10 = _IMX_PAD(0x650, 0x280), // IPU1_CSI0_DATA10

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA11)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA11)
   IMX_PAD_CSI0_DAT11 = _IMX_PAD(0x654, 0x284), // IPU1_CSI0_DATA11

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA12)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA12)
   IMX_PAD_CSI0_DAT12 = _IMX_PAD(0x658, 0x288), // IPU1_CSI0_DATA12

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA13)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA13)
   IMX_PAD_CSI0_DAT13 = _IMX_PAD(0x65C, 0x28C), // IPU1_CSI0_DATA13

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA14)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA14)
   IMX_PAD_CSI0_DAT14 = _IMX_PAD(0x660, 0x290), // IPU1_CSI0_DATA14

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA15)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA15)
   IMX_PAD_CSI0_DAT15 = _IMX_PAD(0x664, 0x294), // IPU1_CSI0_DATA15

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA16)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA16)
   IMX_PAD_CSI0_DAT16 = _IMX_PAD(0x668, 0x298), // IPU1_CSI0_DATA16

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA17)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA17)
   IMX_PAD_CSI0_DAT17 = _IMX_PAD(0x66C, 0x29C), // IPU1_CSI0_DATA17

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA18)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA18)
   IMX_PAD_CSI0_DAT18 = _IMX_PAD(0x670, 0x2A0), // IPU1_CSI0_DATA18

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI0_DATA19)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI0_DATA19)
   IMX_PAD_CSI0_DAT19 = _IMX_PAD(0x674, 0x2A4), // IPU1_CSI0_DATA19

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_ADDR23)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_ADDR23)
   IMX_PAD_EIM_A23 = _IMX_PAD(0x3EC, 0xD8), // EIM_ADDR23

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_CLE)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_CLE)
   IMX_PAD_NANDF_CLE = _IMX_PAD(0x6BC, 0x2D4), // NAND_CLE

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_ALE)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_ALE)
   IMX_PAD_NANDF_ALE = _IMX_PAD(0x6C0, 0x2D8), // NAND_ALE

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_WP_B)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_WP_B)
   IMX_PAD_NANDF_WP_B = _IMX_PAD(0x6C4, 0x2DC), // NAND_WP_B

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_READY_B)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_READY_B)
   IMX_PAD_NANDF_RB0 = _IMX_PAD(0x6C8, 0x2E0), // NAND_READY_B

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_CS0_B)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_CS0_B)
   IMX_PAD_NANDF_CS0 = _IMX_PAD(0x6CC, 0x2E4), // NAND_CE0_B

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_CS1_B)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_CS1_B)
   IMX_PAD_NANDF_CS1 = _IMX_PAD(0x6D0, 0x2E8), // NAND_CE1_B

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_CS2_B)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_CS2_B)
   IMX_PAD_NANDF_CS2 = _IMX_PAD(0x6D4, 0x2EC), // NAND_CE2_B

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_CS3_B)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_CS3_B)
   IMX_PAD_NANDF_CS3 = _IMX_PAD(0x6D8, 0x2F0), // NAND_CE3_B

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD3_DATA7)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD3_DATA7)
   IMX_PAD_SD3_DAT7 = _IMX_PAD(0x690, 0x2A8), // SD3_DATA7

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD3_DATA6)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD3_DATA6)
   IMX_PAD_SD3_DAT6 = _IMX_PAD(0x694, 0x2AC), // SD3_DATA6

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII_TXC)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII_TXC)
   IMX_PAD_RGMII_TXC = _IMX_PAD(0x36C, 0x58), // USB_H2_DATA

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII_TD0)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII_TD0)
   IMX_PAD_RGMII_TD0 = _IMX_PAD(0x370, 0x5C), // HSI_TX_READY

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII_TD1)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII_TD1)
   IMX_PAD_RGMII_TD1 = _IMX_PAD(0x374, 0x60), // HSI_RX_FLAG

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII_TD2)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII_TD2)
   IMX_PAD_RGMII_TD2 = _IMX_PAD(0x378, 0x64), // HSI_RX_DATA

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII_TD3)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII_TD3)
   IMX_PAD_RGMII_TD3 = _IMX_PAD(0x37C, 0x68), // HSI_RX_WAKE

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII_RX_CTL)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII_RX_CTL)
   IMX_PAD_RGMII_RX_CTL = _IMX_PAD(0x380, 0x6C), // USB_H3_DATA

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII_RD0)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII_RD0)
   IMX_PAD_RGMII_RD0 = _IMX_PAD(0x384, 0x70), // HSI_RX_READY

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII_TX_CTL)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII_TX_CTL)
   IMX_PAD_RGMII_TX_CTL = _IMX_PAD(0x388, 0x74), // USB_H2_STROBE

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII_RD1)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII_RD1)
   IMX_PAD_RGMII_RD1 = _IMX_PAD(0x38C, 0x78), // HSI_TX_FLAG

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII_RD2)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII_RD2)
   IMX_PAD_RGMII_RD2 = _IMX_PAD(0x390, 0x7C), // HSI_TX_DATA

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII_RD3)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII_RD3)
   IMX_PAD_RGMII_RD3 = _IMX_PAD(0x394, 0x80), // HSI_TX_WAKE

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII_RXC)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII_RXC)
   IMX_PAD_RGMII_RXC = _IMX_PAD(0x398, 0x84), // USB_H3_STROBE

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_EIM_BCLK)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_EIM_BCLK)
   IMX_PAD_EIM_BCLK = _IMX_PAD(0x46C, 0x158), // EIM_BCLK

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD3_DATA5)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD3_DATA5)
   IMX_PAD_SD3_DAT5 = _IMX_PAD(0x698, 0x2B0), // SD3_DATA5

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD3_DATA4)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD3_DATA4)
   IMX_PAD_SD3_DAT4 = _IMX_PAD(0x69C, 0x2B4), // SD3_DATA4

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD3_CMD)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD3_CMD)
   IMX_PAD_SD3_CMD = _IMX_PAD(0x6A0, 0x2B8), // SD3_CMD

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD3_CLK)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD3_CLK)
   IMX_PAD_SD3_CLK = _IMX_PAD(0x6A4, 0x2BC), // SD3_CLK

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD3_DATA0)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD3_DATA0)
   IMX_PAD_SD3_DAT0 = _IMX_PAD(0x6A8, 0x2C0), // SD3_DATA0

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD3_DATA1)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD3_DATA1)
   IMX_PAD_SD3_DAT1 = _IMX_PAD(0x6AC, 0x2C4), // SD3_DATA1

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD3_DATA2)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD3_DATA2)
   IMX_PAD_SD3_DAT2 = _IMX_PAD(0x6B0, 0x2C8), // SD3_DATA2

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD3_DATA3)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD3_DATA3)
   IMX_PAD_SD3_DAT3 = _IMX_PAD(0x6B4, 0x2CC), // SD3_DATA3

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD3_RESET)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD3_RESET)
   IMX_PAD_SD3_RST = _IMX_PAD(0x6B8, 0x2D0), // SD3_RESET

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD4_CMD)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD4_CMD)
   IMX_PAD_SD4_CMD = _IMX_PAD(0x6DC, 0x2F4), // SD4_CMD

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD4_CLK)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD4_CLK)
   IMX_PAD_SD4_CLK = _IMX_PAD(0x6E0, 0x2F8), // SD4_CLK

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_GPIO16)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_GPIO16)
   IMX_PAD_GPIO_16 = _IMX_PAD(0x618, 0x248), // ESAI_TX3_RX2

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_GPIO17)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_GPIO17)
   IMX_PAD_GPIO_17 = _IMX_PAD(0x61C, 0x24C), // ESAI_TX0

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_GPIO18)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_GPIO18)
   IMX_PAD_GPIO_18 = _IMX_PAD(0x620, 0x250), // ESAI_TX1
} IMX_PAD;

//
// Alternate function numbers
//

typedef enum {
   IMX_IOMUXC_GPIO_0_ALT0_CCM_CLKO1 = 0,
   IMX_IOMUXC_GPIO_0_ALT2_KEY_COL5 = 2,
   IMX_IOMUXC_GPIO_0_ALT3_ASRC_EXT_CLK = 3,
   IMX_IOMUXC_GPIO_0_ALT4_EPIT1_OUT = 4,
   IMX_IOMUXC_GPIO_0_ALT5_GPIO1_IO00 = 5,
   IMX_IOMUXC_GPIO_0_ALT6_USB_H1_PWR = 6,
   IMX_IOMUXC_GPIO_0_ALT7_SNVS_VIO_5 = 7,
} IMX_IOMUXC_GPIO_0_ALT;

typedef enum {
   IMX_IOMUXC_GPIO_1_ALT0_ESAI_RX_CLK = 0,
   IMX_IOMUXC_GPIO_1_ALT1_WDOG2_B = 1,
   IMX_IOMUXC_GPIO_1_ALT2_KEY_ROW5 = 2,
   IMX_IOMUXC_GPIO_1_ALT3_USB_OTG_ID = 3,
   IMX_IOMUXC_GPIO_1_ALT4_PWM2_OUT = 4,
   IMX_IOMUXC_GPIO_1_ALT5_GPIO1_IO01 = 5,
   IMX_IOMUXC_GPIO_1_ALT6_SD1_CD_B = 6,
} IMX_IOMUXC_GPIO_1_ALT;

typedef enum {
   IMX_IOMUXC_GPIO_2_ALT0_ESAI_TX_FS = 0,
   IMX_IOMUXC_GPIO_2_ALT2_KEY_ROW6 = 2,
   IMX_IOMUXC_GPIO_2_ALT5_GPIO1_IO02 = 5,
   IMX_IOMUXC_GPIO_2_ALT6_SD2_WP = 6,
   IMX_IOMUXC_GPIO_2_ALT7_MLB_DATA = 7,
} IMX_IOMUXC_GPIO_2_ALT;

typedef enum {
   IMX_IOMUXC_GPIO_3_ALT0_ESAI_RX_HF_CLK = 0,
   IMX_IOMUXC_GPIO_3_ALT2_I2C3_SCL = 2,
   IMX_IOMUXC_GPIO_3_ALT3_XTALOSC_REF_CLK_24M = 3,
   IMX_IOMUXC_GPIO_3_ALT4_CCM_CLKO2 = 4,
   IMX_IOMUXC_GPIO_3_ALT5_GPIO1_IO03 = 5,
   IMX_IOMUXC_GPIO_3_ALT6_USB_H1_OC = 6,
   IMX_IOMUXC_GPIO_3_ALT7_MLB_CLK = 7,
} IMX_IOMUXC_GPIO_3_ALT;

typedef enum {
   IMX_IOMUXC_GPIO_4_ALT0_ESAI_TX_HF_CLK = 0,
   IMX_IOMUXC_GPIO_4_ALT2_KEY_COL7 = 2,
   IMX_IOMUXC_GPIO_4_ALT5_GPIO1_IO04 = 5,
   IMX_IOMUXC_GPIO_4_ALT6_SD2_CD_B = 6,
} IMX_IOMUXC_GPIO_4_ALT;

typedef enum {
   IMX_IOMUXC_GPIO_5_ALT0_ESAI_TX2_RX3 = 0,
   IMX_IOMUXC_GPIO_5_ALT2_KEY_ROW7 = 2,
   IMX_IOMUXC_GPIO_5_ALT3_CCM_CLKO1 = 3,
   IMX_IOMUXC_GPIO_5_ALT5_GPIO1_IO05 = 5,
   IMX_IOMUXC_GPIO_5_ALT6_I2C3_SCL = 6,
   IMX_IOMUXC_GPIO_5_ALT7_ARM_EVENTI = 7,
} IMX_IOMUXC_GPIO_5_ALT;

typedef enum {
   IMX_IOMUXC_GPIO_6_ALT0_ESAI_TX_CLK = 0,
   IMX_IOMUXC_GPIO_6_ALT1 = 1, 
   IMX_IOMUXC_GPIO_6_ALT2_I2C3_SDA = 2,
   IMX_IOMUXC_GPIO_6_ALT5_GPIO1_IO06 = 5,
   IMX_IOMUXC_GPIO_6_ALT6_SD2_LCTL = 6,
   IMX_IOMUXC_GPIO_6_ALT7_MLB_SIG = 7,
} IMX_IOMUXC_GPIO_6_ALT;

typedef enum {
   IMX_IOMUXC_GPIO_7_ALT0_ESAI_TX4_RX1 = 0,
   IMX_IOMUXC_GPIO_7_ALT1_ECSPI5_RDY = 1,
   IMX_IOMUXC_GPIO_7_ALT2_EPIT1_OUT = 2,
   IMX_IOMUXC_GPIO_7_ALT3_FLEXCAN1_TX = 3,
   IMX_IOMUXC_GPIO_7_ALT4_UART2_TX_DATA = 4,
   IMX_IOMUXC_GPIO_7_ALT5_GPIO1_IO07 = 5,
   IMX_IOMUXC_GPIO_7_ALT6_SPDIF_LOCK = 6,
   IMX_IOMUXC_GPIO_7_ALT7_USB_OTG_HOST_MODE = 7,
} IMX_IOMUXC_GPIO_7_ALT;

typedef enum {
   IMX_IOMUXC_GPIO_8_ALT0_ESAI_TX5_RX0 = 0,
   IMX_IOMUXC_GPIO_8_ALT1_XTALOSC_REF_CLK_32K = 1,
   IMX_IOMUXC_GPIO_8_ALT2_EPIT2_OUT = 2,
   IMX_IOMUXC_GPIO_8_ALT3_FLEXCAN1_RX = 3,
   IMX_IOMUXC_GPIO_8_ALT4_UART2_RX_DATA = 4,
   IMX_IOMUXC_GPIO_8_ALT5_GPIO1_IO08 = 5,
   IMX_IOMUXC_GPIO_8_ALT6_SPDIF_SR_CLK = 6,
   IMX_IOMUXC_GPIO_8_ALT7_USB_OTG_PWR_CTL_WAKE = 7,
} IMX_IOMUXC_GPIO_8_ALT;

typedef enum {
   IMX_IOMUXC_GPIO_9_ALT0_ESAI_RX_FS = 0,
   IMX_IOMUXC_GPIO_9_ALT1_WDOG1_B = 1,
   IMX_IOMUXC_GPIO_9_ALT2_KEY_COL6 = 2,
   IMX_IOMUXC_GPIO_9_ALT3_CCM_REF_EN_B = 3,
   IMX_IOMUXC_GPIO_9_ALT4_PWM1_OUT = 4,
   IMX_IOMUXC_GPIO_9_ALT5_GPIO1_IO09 = 5,
   IMX_IOMUXC_GPIO_9_ALT6_SD1_WP = 6,
} IMX_IOMUXC_GPIO_9_ALT;

typedef enum {
   IMX_IOMUXC_SD2_CLK_ALT0_SD2_CLK = 0,
   IMX_IOMUXC_SD2_CLK_ALT1_ECSPI5_SCLK = 1,
   IMX_IOMUXC_SD2_CLK_ALT2_KEY_COL5 = 2,
   IMX_IOMUXC_SD2_CLK_ALT3_AUD4_RXFS = 3,
   IMX_IOMUXC_SD2_CLK_ALT5_GPIO1_IO10 = 5,
} IMX_IOMUXC_SD2_CLK_ALT;

typedef enum {
   IMX_IOMUXC_SD2_CMD_ALT0_SD2_CMD = 0,
   IMX_IOMUXC_SD2_CMD_ALT1_ECSPI5_MOSI = 1,
   IMX_IOMUXC_SD2_CMD_ALT2_KEY_ROW5 = 2,
   IMX_IOMUXC_SD2_CMD_ALT3_AUD4_RXC = 3,
   IMX_IOMUXC_SD2_CMD_ALT5_GPIO1_IO11 = 5,
} IMX_IOMUXC_SD2_CMD_ALT;

typedef enum {
   IMX_IOMUXC_SD2_DAT3_ALT0_SD2_DATA3 = 0,
   IMX_IOMUXC_SD2_DAT3_ALT1_ECSPI5_SS3 = 1,
   IMX_IOMUXC_SD2_DAT3_ALT2_KEY_COL6 = 2,
   IMX_IOMUXC_SD2_DAT3_ALT3_AUD4_TXC = 3,
   IMX_IOMUXC_SD2_DAT3_ALT5_GPIO1_IO12 = 5,
} IMX_IOMUXC_SD2_DAT3_ALT;

typedef enum {
   IMX_IOMUXC_SD2_DAT2_ALT0_SD2_DATA2 = 0,
   IMX_IOMUXC_SD2_DAT2_ALT1_ECSPI5_SS1 = 1,
   IMX_IOMUXC_SD2_DAT2_ALT2_EIM_CS3_B = 2,
   IMX_IOMUXC_SD2_DAT2_ALT3_AUD4_TXD = 3,
   IMX_IOMUXC_SD2_DAT2_ALT4_KEY_ROW6 = 4,
   IMX_IOMUXC_SD2_DAT2_ALT5_GPIO1_IO13 = 5,
} IMX_IOMUXC_SD2_DAT2_ALT;

typedef enum {
   IMX_IOMUXC_SD2_DAT1_ALT0_SD2_DATA1 = 0,
   IMX_IOMUXC_SD2_DAT1_ALT1_ECSPI5_SS0 = 1,
   IMX_IOMUXC_SD2_DAT1_ALT2_EIM_CS2_B = 2,
   IMX_IOMUXC_SD2_DAT1_ALT3_AUD4_TXFS = 3,
   IMX_IOMUXC_SD2_DAT1_ALT4_KEY_COL7 = 4,
   IMX_IOMUXC_SD2_DAT1_ALT5_GPIO1_IO14 = 5,
} IMX_IOMUXC_SD2_DAT1_ALT;

typedef enum {
   IMX_IOMUXC_SD2_DAT0_ALT0_SD2_DATA0 = 0,
   IMX_IOMUXC_SD2_DAT0_ALT1_ECSPI5_MISO = 1,
   IMX_IOMUXC_SD2_DAT0_ALT3_AUD4_RXD = 3,
   IMX_IOMUXC_SD2_DAT0_ALT4_KEY_ROW7 = 4,
   IMX_IOMUXC_SD2_DAT0_ALT5_GPIO1_IO15 = 5,
   IMX_IOMUXC_SD2_DAT0_ALT6_DCIC2_OUT = 6,
} IMX_IOMUXC_SD2_DAT0_ALT;

typedef enum {
   IMX_IOMUXC_SD1_DAT0_ALT0_SD1_DATA0 = 0,
   IMX_IOMUXC_SD1_DAT0_ALT1_ECSPI5_MISO = 1,
   IMX_IOMUXC_SD1_DAT0_ALT3_GPT_CAPTURE1 = 3,
   IMX_IOMUXC_SD1_DAT0_ALT5_GPIO1_IO16 = 5,
} IMX_IOMUXC_SD1_DAT0_ALT;

typedef enum {
   IMX_IOMUXC_SD1_DAT1_ALT0_SD1_DATA1 = 0,
   IMX_IOMUXC_SD1_DAT1_ALT1_ECSPI5_SS0 = 1,
   IMX_IOMUXC_SD1_DAT1_ALT2_PWM3_OUT = 2,
   IMX_IOMUXC_SD1_DAT1_ALT3_GPT_CAPTURE2 = 3,
   IMX_IOMUXC_SD1_DAT1_ALT5_GPIO1_IO17 = 5,
} IMX_IOMUXC_SD1_DAT1_ALT;

typedef enum {
   IMX_IOMUXC_SD1_CMD_ALT0_SD1_CMD = 0,
   IMX_IOMUXC_SD1_CMD_ALT1_ECSPI5_MOSI = 1,
   IMX_IOMUXC_SD1_CMD_ALT2_PWM4_OUT = 2,
   IMX_IOMUXC_SD1_CMD_ALT3_GPT_COMPARE1 = 3,
   IMX_IOMUXC_SD1_CMD_ALT5_GPIO1_IO18 = 5,
} IMX_IOMUXC_SD1_CMD_ALT;

typedef enum {
   IMX_IOMUXC_SD1_DAT2_ALT0_SD1_DATA2 = 0,
   IMX_IOMUXC_SD1_DAT2_ALT1_ECSPI5_SS1 = 1,
   IMX_IOMUXC_SD1_DAT2_ALT2_GPT_COMPARE2 = 2,
   IMX_IOMUXC_SD1_DAT2_ALT3_PWM2_OUT = 3,
   IMX_IOMUXC_SD1_DAT2_ALT4_WDOG1_B = 4,
   IMX_IOMUXC_SD1_DAT2_ALT5_GPIO1_IO19 = 5,
   IMX_IOMUXC_SD1_DAT2_ALT6_WDOG1_RESET_B_DEB = 6,
} IMX_IOMUXC_SD1_DAT2_ALT;

typedef enum {
   IMX_IOMUXC_SD1_CLK_ALT0_SD1_CLK = 0,
   IMX_IOMUXC_SD1_CLK_ALT1_ECSPI5_SCLK = 1,
   IMX_IOMUXC_SD1_CLK_ALT2_XTALOSC_OSC32K_32K_OUT = 2,
   IMX_IOMUXC_SD1_CLK_ALT3_GPT_CLKIN = 3,
   IMX_IOMUXC_SD1_CLK_ALT5_GPIO1_IO20 = 5,
} IMX_IOMUXC_SD1_CLK_ALT;

typedef enum {
   IMX_IOMUXC_SD1_DAT3_ALT0_SD1_DATA3 = 0,
   IMX_IOMUXC_SD1_DAT3_ALT1_ECSPI5_SS2 = 1,
   IMX_IOMUXC_SD1_DAT3_ALT2_GPT_COMPARE3 = 2,
   IMX_IOMUXC_SD1_DAT3_ALT3_PWM1_OUT = 3,
   IMX_IOMUXC_SD1_DAT3_ALT4_WDOG2_B = 4,
   IMX_IOMUXC_SD1_DAT3_ALT5_GPIO1_IO21 = 5,
   IMX_IOMUXC_SD1_DAT3_ALT6_WDOG2_RESET_B_DEB = 6,
} IMX_IOMUXC_SD1_DAT3_ALT;

typedef enum {
   IMX_IOMUXC_ENET_MDIO_ALT1_ENET_MDIO = 1,
   IMX_IOMUXC_ENET_MDIO_ALT2_ESAI_RX_CLK = 2,
   IMX_IOMUXC_ENET_MDIO_ALT4_ENET_1588_EVENT1_OUT = 4,
   IMX_IOMUXC_ENET_MDIO_ALT5_GPIO1_IO22 = 5,
   IMX_IOMUXC_ENET_MDIO_ALT6_SPDIF_LOCK = 6,
} IMX_IOMUXC_ENET_MDIO_ALT;

typedef enum {
   IMX_IOMUXC_ENET_REF_CLK_ALT1_ENET_TX_CLK = 1,
   IMX_IOMUXC_ENET_REF_CLK_ALT2_ESAI_RX_FS = 2,
   IMX_IOMUXC_ENET_REF_CLK_ALT5_GPIO1_IO23 = 5,
   IMX_IOMUXC_ENET_REF_CLK_ALT6_SPDIF_SR_CLK = 6,
} IMX_IOMUXC_ENET_REF_CLK_ALT;

typedef enum {
   IMX_IOMUXC_ENET_RX_ER_ALT0_USB_OTG_ID = 0,
   IMX_IOMUXC_ENET_RX_ER_ALT1_ENET_RX_ER = 1,
   IMX_IOMUXC_ENET_RX_ER_ALT2_ESAI_RX_HF_CLK = 2,
   IMX_IOMUXC_ENET_RX_ER_ALT3_SPDIF_IN = 3,
   IMX_IOMUXC_ENET_RX_ER_ALT4_ENET_1588_EVENT2_OUT = 4,
   IMX_IOMUXC_ENET_RX_ER_ALT5_GPIO1_IO24 = 5,
} IMX_IOMUXC_ENET_RX_ER_ALT;

typedef enum {
   IMX_IOMUXC_ENET_CRS_DV_ALT1_ENET_RX_EN = 1,
   IMX_IOMUXC_ENET_CRS_DV_ALT2_ESAI_TX_CLK = 2,
   IMX_IOMUXC_ENET_CRS_DV_ALT3_SPDIF_EXT_CLK = 3,
   IMX_IOMUXC_ENET_CRS_DV_ALT5_GPIO1_IO25 = 5,
} IMX_IOMUXC_ENET_CRS_DV_ALT;

typedef enum {
   IMX_IOMUXC_ENET_RXD1_ALT0_MLB_SIG = 0,
   IMX_IOMUXC_ENET_RXD1_ALT1_ENET_RX_DATA1 = 1,
   IMX_IOMUXC_ENET_RXD1_ALT2_ESAI_TX_FS = 2,
   IMX_IOMUXC_ENET_RXD1_ALT4_ENET_1588_EVENT3_OUT = 4,
   IMX_IOMUXC_ENET_RXD1_ALT5_GPIO1_IO26 = 5,
} IMX_IOMUXC_ENET_RXD1_ALT;

typedef enum {
   IMX_IOMUXC_ENET_RXD0_ALT0_XTALOSC_OSC32K_32K_OUT = 0,
   IMX_IOMUXC_ENET_RXD0_ALT1_ENET_RX_DATA0 = 1,
   IMX_IOMUXC_ENET_RXD0_ALT2_ESAI_TX_HF_CLK = 2,
   IMX_IOMUXC_ENET_RXD0_ALT3_SPDIF_OUT = 3,
   IMX_IOMUXC_ENET_RXD0_ALT5_GPIO1_IO27 = 5,
} IMX_IOMUXC_ENET_RXD0_ALT;

typedef enum {
   IMX_IOMUXC_ENET_TX_EN_ALT1_ENET_TX_EN = 1,
   IMX_IOMUXC_ENET_TX_EN_ALT2_ESAI_TX3_RX2 = 2,
   IMX_IOMUXC_ENET_TX_EN_ALT5_GPIO1_IO28 = 5,
} IMX_IOMUXC_ENET_TX_EN_ALT;

typedef enum {
   IMX_IOMUXC_ENET_TXD1_ALT0_MLB_CLK = 0,
   IMX_IOMUXC_ENET_TXD1_ALT1_ENET_TX_DATA1 = 1,
   IMX_IOMUXC_ENET_TXD1_ALT2_ESAI_TX2_RX3 = 2,
   IMX_IOMUXC_ENET_TXD1_ALT4_ENET_1588_EVENT0_IN = 4,
   IMX_IOMUXC_ENET_TXD1_ALT5_GPIO1_IO29 = 5,
} IMX_IOMUXC_ENET_TXD1_ALT;

typedef enum {
   IMX_IOMUXC_ENET_TXD0_ALT1_ENET_TX_DATA0 = 1,
   IMX_IOMUXC_ENET_TXD0_ALT2_ESAI_TX4_RX1 = 2,
   IMX_IOMUXC_ENET_TXD0_ALT5_GPIO1_IO30 = 5,
} IMX_IOMUXC_ENET_TXD0_ALT;

typedef enum {
   IMX_IOMUXC_ENET_MDC_ALT0_MLB_DATA = 0,
   IMX_IOMUXC_ENET_MDC_ALT1_ENET_MDC = 1,
   IMX_IOMUXC_ENET_MDC_ALT2_ESAI_TX5_RX0 = 2,
   IMX_IOMUXC_ENET_MDC_ALT4_ENET_1588_EVENT1_IN = 4,
   IMX_IOMUXC_ENET_MDC_ALT5_GPIO1_IO31 = 5,
} IMX_IOMUXC_ENET_MDC_ALT;

typedef enum {
   IMX_IOMUXC_NANDF_D0_ALT0_NAND_DATA00 = 0,
   IMX_IOMUXC_NANDF_D0_ALT1_SD1_DATA4 = 1,
   IMX_IOMUXC_NANDF_D0_ALT5_GPIO2_IO00 = 5,
} IMX_IOMUXC_NANDF_D0_ALT;

typedef enum {
   IMX_IOMUXC_NANDF_D1_ALT0_NAND_DATA01 = 0,
   IMX_IOMUXC_NANDF_D1_ALT1_SD1_DATA5 = 1,
   IMX_IOMUXC_NANDF_D1_ALT5_GPIO2_IO01 = 5,
} IMX_IOMUXC_NANDF_D1_ALT;

typedef enum {
   IMX_IOMUXC_NANDF_D2_ALT0_NAND_DATA02 = 0,
   IMX_IOMUXC_NANDF_D2_ALT1_SD1_DATA6 = 1,
   IMX_IOMUXC_NANDF_D2_ALT5_GPIO2_IO02 = 5,
} IMX_IOMUXC_NANDF_D2_ALT;

typedef enum {
   IMX_IOMUXC_NANDF_D3_ALT0_NAND_DATA03 = 0,
   IMX_IOMUXC_NANDF_D3_ALT1_SD1_DATA7 = 1,
   IMX_IOMUXC_NANDF_D3_ALT5_GPIO2_IO03 = 5,
} IMX_IOMUXC_NANDF_D3_ALT;

typedef enum {
   IMX_IOMUXC_NANDF_D4_ALT0_NAND_DATA04 = 0,
   IMX_IOMUXC_NANDF_D4_ALT1_SD2_DATA4 = 1,
   IMX_IOMUXC_NANDF_D4_ALT5_GPIO2_IO04 = 5,
} IMX_IOMUXC_NANDF_D4_ALT;

typedef enum {
   IMX_IOMUXC_NANDF_D5_ALT0_NAND_DATA05 = 0,
   IMX_IOMUXC_NANDF_D5_ALT1_SD2_DATA5 = 1,
   IMX_IOMUXC_NANDF_D5_ALT5_GPIO2_IO05 = 5,
} IMX_IOMUXC_NANDF_D5_ALT;

typedef enum {
   IMX_IOMUXC_NANDF_D6_ALT0_NAND_DATA06 = 0,
   IMX_IOMUXC_NANDF_D6_ALT1_SD2_DATA6 = 1,
   IMX_IOMUXC_NANDF_D6_ALT5_GPIO2_IO06 = 5,
} IMX_IOMUXC_NANDF_D6_ALT;

typedef enum {
   IMX_IOMUXC_NANDF_D7_ALT0_NAND_DATA07 = 0,
   IMX_IOMUXC_NANDF_D7_ALT1_SD2_DATA7 = 1,
   IMX_IOMUXC_NANDF_D7_ALT5_GPIO2_IO07 = 5,
} IMX_IOMUXC_NANDF_D7_ALT;

typedef enum {
   IMX_IOMUXC_SD4_DAT0_ALT1_SD4_DATA0 = 1,
   IMX_IOMUXC_SD4_DAT0_ALT2_NAND_DQS = 2,
   IMX_IOMUXC_SD4_DAT0_ALT5_GPIO2_IO08 = 5,
} IMX_IOMUXC_SD4_DAT0_ALT;

typedef enum {
   IMX_IOMUXC_SD4_DAT1_ALT1_SD4_DATA1 = 1,
   IMX_IOMUXC_SD4_DAT1_ALT2_PWM3_OUT = 2,
   IMX_IOMUXC_SD4_DAT1_ALT5_GPIO2_IO09 = 5,
} IMX_IOMUXC_SD4_DAT1_ALT;

typedef enum {
   IMX_IOMUXC_SD4_DAT2_ALT1_SD4_DATA2 = 1,
   IMX_IOMUXC_SD4_DAT2_ALT2_PWM4_OUT = 2,
   IMX_IOMUXC_SD4_DAT2_ALT5_GPIO2_IO10 = 5,
} IMX_IOMUXC_SD4_DAT2_ALT;

typedef enum {
   IMX_IOMUXC_SD4_DAT3_ALT1_SD4_DATA3 = 1,
   IMX_IOMUXC_SD4_DAT3_ALT5_GPIO2_IO11 = 5,
} IMX_IOMUXC_SD4_DAT3_ALT;

typedef enum {
   IMX_IOMUXC_SD4_DAT4_ALT1_SD4_DATA4 = 1,
   IMX_IOMUXC_SD4_DAT4_ALT2_UART2_RX_DATA = 2,
   IMX_IOMUXC_SD4_DAT4_ALT5_GPIO2_IO12 = 5,
} IMX_IOMUXC_SD4_DAT4_ALT;

typedef enum {
   IMX_IOMUXC_SD4_DAT5_ALT1_SD4_DATA5 = 1,
   IMX_IOMUXC_SD4_DAT5_ALT2_UART2_RTS_B = 2,
   IMX_IOMUXC_SD4_DAT5_ALT5_GPIO2_IO13 = 5,
} IMX_IOMUXC_SD4_DAT5_ALT;

typedef enum {
   IMX_IOMUXC_SD4_DAT6_ALT1_SD4_DATA6 = 1,
   IMX_IOMUXC_SD4_DAT6_ALT2_UART2_CTS_B = 2,
   IMX_IOMUXC_SD4_DAT6_ALT5_GPIO2_IO14 = 5,
} IMX_IOMUXC_SD4_DAT6_ALT;

typedef enum {
   IMX_IOMUXC_SD4_DAT7_ALT1_SD4_DATA7 = 1,
   IMX_IOMUXC_SD4_DAT7_ALT2_UART2_TX_DATA = 2,
   IMX_IOMUXC_SD4_DAT7_ALT5_GPIO2_IO15 = 5,
} IMX_IOMUXC_SD4_DAT7_ALT;

typedef enum {
   IMX_IOMUXC_EIM_A22_ALT0_EIM_ADDR22 = 0,
   IMX_IOMUXC_EIM_A22_ALT1_IPU1_DISP1_DATA17 = 1,
   IMX_IOMUXC_EIM_A22_ALT2_IPU2_CSI1_DATA17 = 2,
   IMX_IOMUXC_EIM_A22_ALT5_GPIO2_IO16 = 5,
   IMX_IOMUXC_EIM_A22_ALT7_SRC_BOOT_CFG22 = 7,
} IMX_IOMUXC_EIM_A22_ALT;

typedef enum {
   IMX_IOMUXC_EIM_A21_ALT0_EIM_ADDR21 = 0,
   IMX_IOMUXC_EIM_A21_ALT1_IPU1_DISP1_DATA16 = 1,
   IMX_IOMUXC_EIM_A21_ALT2_IPU2_CSI1_DATA16 = 2,
   IMX_IOMUXC_EIM_A21_ALT5_GPIO2_IO17 = 5,
   IMX_IOMUXC_EIM_A21_ALT7_SRC_BOOT_CFG21 = 7,
} IMX_IOMUXC_EIM_A21_ALT;

typedef enum {
   IMX_IOMUXC_EIM_A20_ALT0_EIM_ADDR20 = 0,
   IMX_IOMUXC_EIM_A20_ALT1_IPU1_DISP1_DATA15 = 1,
   IMX_IOMUXC_EIM_A20_ALT2_IPU2_CSI1_DATA15 = 2,
   IMX_IOMUXC_EIM_A20_ALT5_GPIO2_IO18 = 5,
   IMX_IOMUXC_EIM_A20_ALT7_SRC_BOOT_CFG20 = 7,
} IMX_IOMUXC_EIM_A20_ALT;

typedef enum {
   IMX_IOMUXC_EIM_A19_ALT0_EIM_ADDR19 = 0,
   IMX_IOMUXC_EIM_A19_ALT1_IPU1_DISP1_DATA14 = 1,
   IMX_IOMUXC_EIM_A19_ALT2_IPU2_CSI1_DATA14 = 2,
   IMX_IOMUXC_EIM_A19_ALT5_GPIO2_IO19 = 5,
   IMX_IOMUXC_EIM_A19_ALT7_SRC_BOOT_CFG19 = 7,
} IMX_IOMUXC_EIM_A19_ALT;

typedef enum {
   IMX_IOMUXC_EIM_A18_ALT0_EIM_ADDR18 = 0,
   IMX_IOMUXC_EIM_A18_ALT1_IPU1_DISP1_DATA13 = 1,
   IMX_IOMUXC_EIM_A18_ALT2_IPU2_CSI1_DATA13 = 2,
   IMX_IOMUXC_EIM_A18_ALT5_GPIO2_IO20 = 5,
   IMX_IOMUXC_EIM_A18_ALT7_SRC_BOOT_CFG18 = 7,
} IMX_IOMUXC_EIM_A18_ALT;

typedef enum {
   IMX_IOMUXC_EIM_A17_ALT0_EIM_ADDR17 = 0,
   IMX_IOMUXC_EIM_A17_ALT1_IPU1_DISP1_DATA12 = 1,
   IMX_IOMUXC_EIM_A17_ALT2_IPU2_CSI1_DATA12 = 2,
   IMX_IOMUXC_EIM_A17_ALT5_GPIO2_IO21 = 5,
   IMX_IOMUXC_EIM_A17_ALT7_SRC_BOOT_CFG17 = 7,
} IMX_IOMUXC_EIM_A17_ALT;

typedef enum {
   IMX_IOMUXC_EIM_A16_ALT0_EIM_ADDR16 = 0,
   IMX_IOMUXC_EIM_A16_ALT1_IPU1_DI1_DISP_CLK = 1,
   IMX_IOMUXC_EIM_A16_ALT2_IPU2_CSI1_PIXCLK = 2,
   IMX_IOMUXC_EIM_A16_ALT5_GPIO2_IO22 = 5,
   IMX_IOMUXC_EIM_A16_ALT7_SRC_BOOT_CFG16 = 7,
} IMX_IOMUXC_EIM_A16_ALT;

typedef enum {
   IMX_IOMUXC_EIM_CS0_ALT0_EIM_CS0_B = 0,
   IMX_IOMUXC_EIM_CS0_ALT1_IPU1_DI1_PIN05 = 1,
   IMX_IOMUXC_EIM_CS0_ALT2_ECSPI2_SCLK = 2,
   IMX_IOMUXC_EIM_CS0_ALT5_GPIO2_IO23 = 5,
} IMX_IOMUXC_EIM_CS0_ALT;

typedef enum {
   IMX_IOMUXC_EIM_CS1_ALT0_EIM_CS1_B = 0,
   IMX_IOMUXC_EIM_CS1_ALT1_IPU1_DI1_PIN06 = 1,
   IMX_IOMUXC_EIM_CS1_ALT2_ECSPI2_MOSI = 2,
   IMX_IOMUXC_EIM_CS1_ALT5_GPIO2_IO24 = 5,
} IMX_IOMUXC_EIM_CS1_ALT;

typedef enum {
   IMX_IOMUXC_EIM_OE_ALT0_EIM_OE_B = 0,
   IMX_IOMUXC_EIM_OE_ALT1_IPU1_DI1_PIN07 = 1,
   IMX_IOMUXC_EIM_OE_ALT2_ECSPI2_MISO = 2,
   IMX_IOMUXC_EIM_OE_ALT5_GPIO2_IO25 = 5,
} IMX_IOMUXC_EIM_OE_ALT;

typedef enum {
   IMX_IOMUXC_EIM_RW_ALT0_EIM_RW = 0,
   IMX_IOMUXC_EIM_RW_ALT1_IPU1_DI1_PIN08 = 1,
   IMX_IOMUXC_EIM_RW_ALT2_ECSPI2_SS0 = 2,
   IMX_IOMUXC_EIM_RW_ALT5_GPIO2_IO26 = 5,
   IMX_IOMUXC_EIM_RW_ALT7_SRC_BOOT_CFG29 = 7,
} IMX_IOMUXC_EIM_RW_ALT;

typedef enum {
   IMX_IOMUXC_EIM_LBA_ALT0_EIM_LBA_B = 0,
   IMX_IOMUXC_EIM_LBA_ALT1_IPU1_DI1_PIN17 = 1,
   IMX_IOMUXC_EIM_LBA_ALT2_ECSPI2_SS1 = 2,
   IMX_IOMUXC_EIM_LBA_ALT5_GPIO2_IO27 = 5,
   IMX_IOMUXC_EIM_LBA_ALT7_SRC_BOOT_CFG26 = 7,
} IMX_IOMUXC_EIM_LBA_ALT;

typedef enum {
   IMX_IOMUXC_EIM_EB0_ALT0_EIM_EB0_B = 0,
   IMX_IOMUXC_EIM_EB0_ALT1_IPU1_DISP1_DATA11 = 1,
   IMX_IOMUXC_EIM_EB0_ALT2_IPU2_CSI1_DATA11 = 2,
   IMX_IOMUXC_EIM_EB0_ALT4_CCM_PMIC_READY = 4,
   IMX_IOMUXC_EIM_EB0_ALT5_GPIO2_IO28 = 5,
   IMX_IOMUXC_EIM_EB0_ALT7_SRC_BOOT_CFG27 = 7,
} IMX_IOMUXC_EIM_EB0_ALT;

typedef enum {
   IMX_IOMUXC_EIM_EB1_ALT0_EIM_EB1_B = 0,
   IMX_IOMUXC_EIM_EB1_ALT1_IPU1_DISP1_DATA10 = 1,
   IMX_IOMUXC_EIM_EB1_ALT2_IPU2_CSI1_DATA10 = 2,
   IMX_IOMUXC_EIM_EB1_ALT5_GPIO2_IO29 = 5,
   IMX_IOMUXC_EIM_EB1_ALT7_SRC_BOOT_CFG28 = 7,
} IMX_IOMUXC_EIM_EB1_ALT;

typedef enum {
   IMX_IOMUXC_EIM_EB2_ALT0_EIM_EB2_B = 0,
   IMX_IOMUXC_EIM_EB2_ALT1_ECSPI1_SS0 = 1,
   IMX_IOMUXC_EIM_EB2_ALT3_IPU2_CSI1_DATA19 = 3,
   IMX_IOMUXC_EIM_EB2_ALT4_HDMI_TX_DDC_SCL = 4,
   IMX_IOMUXC_EIM_EB2_ALT5_GPIO2_IO30 = 5,
   IMX_IOMUXC_EIM_EB2_ALT6_I2C2_SCL = 6,
   IMX_IOMUXC_EIM_EB2_ALT7_SRC_BOOT_CFG30 = 7,
} IMX_IOMUXC_EIM_EB2_ALT;

typedef enum {
   IMX_IOMUXC_EIM_EB3_ALT0_EIM_EB3_B = 0,
   IMX_IOMUXC_EIM_EB3_ALT1_ECSPI4_RDY = 1,
   IMX_IOMUXC_EIM_EB3_ALT2_UART3_RTS_B = 2,
   IMX_IOMUXC_EIM_EB3_ALT3_UART1_RI_B = 3,
   IMX_IOMUXC_EIM_EB3_ALT4_IPU2_CSI1_HSYNC = 4,
   IMX_IOMUXC_EIM_EB3_ALT5_GPIO2_IO31 = 5,
   IMX_IOMUXC_EIM_EB3_ALT6_IPU1_DI1_PIN03 = 6,
   IMX_IOMUXC_EIM_EB3_ALT7_SRC_BOOT_CFG31 = 7,
} IMX_IOMUXC_EIM_EB3_ALT;

typedef enum {
   IMX_IOMUXC_EIM_DA0_ALT0_EIM_AD00 = 0,
   IMX_IOMUXC_EIM_DA0_ALT1_IPU1_DISP1_DATA09 = 1,
   IMX_IOMUXC_EIM_DA0_ALT2_IPU2_CSI1_DATA09 = 2,
   IMX_IOMUXC_EIM_DA0_ALT5_GPIO3_IO00 = 5,
   IMX_IOMUXC_EIM_DA0_ALT7_SRC_BOOT_CFG00 = 7,
} IMX_IOMUXC_EIM_DA0_ALT;

typedef enum {
   IMX_IOMUXC_EIM_DA1_ALT0_EIM_AD01 = 0,
   IMX_IOMUXC_EIM_DA1_ALT1_IPU1_DISP1_DATA08 = 1,
   IMX_IOMUXC_EIM_DA1_ALT2_IPU2_CSI1_DATA08 = 2,
   IMX_IOMUXC_EIM_DA1_ALT5_GPIO3_IO01 = 5,
   IMX_IOMUXC_EIM_DA1_ALT7_SRC_BOOT_CFG01 = 7,
} IMX_IOMUXC_EIM_DA1_ALT;

typedef enum {
   IMX_IOMUXC_EIM_DA2_ALT0_EIM_AD02 = 0,
   IMX_IOMUXC_EIM_DA2_ALT1_IPU1_DISP1_DATA07 = 1,
   IMX_IOMUXC_EIM_DA2_ALT2_IPU2_CSI1_DATA07 = 2,
   IMX_IOMUXC_EIM_DA2_ALT5_GPIO3_IO02 = 5,
   IMX_IOMUXC_EIM_DA2_ALT7_SRC_BOOT_CFG02 = 7,
} IMX_IOMUXC_EIM_DA2_ALT;

typedef enum {
   IMX_IOMUXC_EIM_DA3_ALT0_EIM_AD03 = 0,
   IMX_IOMUXC_EIM_DA3_ALT1_IPU1_DISP1_DATA06 = 1,
   IMX_IOMUXC_EIM_DA3_ALT2_IPU2_CSI1_DATA06 = 2,
   IMX_IOMUXC_EIM_DA3_ALT5_GPIO3_IO03 = 5,
   IMX_IOMUXC_EIM_DA3_ALT7_SRC_BOOT_CFG03 = 7,
} IMX_IOMUXC_EIM_DA3_ALT;

typedef enum {
   IMX_IOMUXC_EIM_DA4_ALT0_EIM_AD04 = 0,
   IMX_IOMUXC_EIM_DA4_ALT1_IPU1_DISP1_DATA05 = 1,
   IMX_IOMUXC_EIM_DA4_ALT2_IPU2_CSI1_DATA05 = 2,
   IMX_IOMUXC_EIM_DA4_ALT5_GPIO3_IO04 = 5,
   IMX_IOMUXC_EIM_DA4_ALT7_SRC_BOOT_CFG04 = 7,
} IMX_IOMUXC_EIM_DA4_ALT;

typedef enum {
   IMX_IOMUXC_EIM_DA5_ALT0_EIM_AD05 = 0,
   IMX_IOMUXC_EIM_DA5_ALT1_IPU1_DISP1_DATA04 = 1,
   IMX_IOMUXC_EIM_DA5_ALT2_IPU2_CSI1_DATA04 = 2,
   IMX_IOMUXC_EIM_DA5_ALT5_GPIO3_IO05 = 5,
   IMX_IOMUXC_EIM_DA5_ALT7_SRC_BOOT_CFG05 = 7,
} IMX_IOMUXC_EIM_DA5_ALT;

typedef enum {
   IMX_IOMUXC_EIM_DA6_ALT0_EIM_AD06 = 0,
   IMX_IOMUXC_EIM_DA6_ALT1_IPU1_DISP1_DATA03 = 1,
   IMX_IOMUXC_EIM_DA6_ALT2_IPU2_CSI1_DATA03 = 2,
   IMX_IOMUXC_EIM_DA6_ALT5_GPIO3_IO06 = 5,
   IMX_IOMUXC_EIM_DA6_ALT7_SRC_BOOT_CFG06 = 7,
} IMX_IOMUXC_EIM_DA6_ALT;

typedef enum {
   IMX_IOMUXC_EIM_DA7_ALT0_EIM_AD07 = 0,
   IMX_IOMUXC_EIM_DA7_ALT1_IPU1_DISP1_DATA02 = 1,
   IMX_IOMUXC_EIM_DA7_ALT2_IPU2_CSI1_DATA02 = 2,
   IMX_IOMUXC_EIM_DA7_ALT5_GPIO3_IO07 = 5,
   IMX_IOMUXC_EIM_DA7_ALT7_SRC_BOOT_CFG07 = 7,
} IMX_IOMUXC_EIM_DA7_ALT;

typedef enum {
   IMX_IOMUXC_EIM_DA8_ALT0_EIM_AD08 = 0,
   IMX_IOMUXC_EIM_DA8_ALT1_IPU1_DISP1_DATA01 = 1,
   IMX_IOMUXC_EIM_DA8_ALT2_IPU2_CSI1_DATA01 = 2,
   IMX_IOMUXC_EIM_DA8_ALT5_GPIO3_IO08 = 5,
   IMX_IOMUXC_EIM_DA8_ALT7_SRC_BOOT_CFG08 = 7,
} IMX_IOMUXC_EIM_DA8_ALT;

typedef enum {
   IMX_IOMUXC_EIM_DA9_ALT0_EIM_AD09 = 0,
   IMX_IOMUXC_EIM_DA9_ALT1_IPU1_DISP1_DATA00 = 1,
   IMX_IOMUXC_EIM_DA9_ALT2_IPU2_CSI1_DATA00 = 2,
   IMX_IOMUXC_EIM_DA9_ALT5_GPIO3_IO09 = 5,
   IMX_IOMUXC_EIM_DA9_ALT7_SRC_BOOT_CFG09 = 7,
} IMX_IOMUXC_EIM_DA9_ALT;

typedef enum {
   IMX_IOMUXC_EIM_DA10_ALT0_EIM_AD10 = 0,
   IMX_IOMUXC_EIM_DA10_ALT1_IPU1_DI1_PIN15 = 1,
   IMX_IOMUXC_EIM_DA10_ALT2_IPU2_CSI1_DATA_EN = 2,
   IMX_IOMUXC_EIM_DA10_ALT5_GPIO3_IO10 = 5,
   IMX_IOMUXC_EIM_DA10_ALT7_SRC_BOOT_CFG10 = 7,
} IMX_IOMUXC_EIM_DA10_ALT;

typedef enum {
   IMX_IOMUXC_EIM_DA11_ALT0_EIM_AD11 = 0,
   IMX_IOMUXC_EIM_DA11_ALT1_IPU1_DI1_PIN02 = 1,
   IMX_IOMUXC_EIM_DA11_ALT2_IPU2_CSI1_HSYNC = 2,
   IMX_IOMUXC_EIM_DA11_ALT5_GPIO3_IO11 = 5,
   IMX_IOMUXC_EIM_DA11_ALT7_SRC_BOOT_CFG11 = 7,
} IMX_IOMUXC_EIM_DA11_ALT;

typedef enum {
   IMX_IOMUXC_EIM_DA12_ALT0_EIM_AD12 = 0,
   IMX_IOMUXC_EIM_DA12_ALT1_IPU1_DI1_PIN03 = 1,
   IMX_IOMUXC_EIM_DA12_ALT2_IPU2_CSI1_VSYNC = 2,
   IMX_IOMUXC_EIM_DA12_ALT5_GPIO3_IO12 = 5,
   IMX_IOMUXC_EIM_DA12_ALT7_SRC_BOOT_CFG12 = 7,
} IMX_IOMUXC_EIM_DA12_ALT;

typedef enum {
   IMX_IOMUXC_EIM_DA13_ALT0_EIM_AD13 = 0,
   IMX_IOMUXC_EIM_DA13_ALT1_IPU1_DI1_D0_CS = 1,
   IMX_IOMUXC_EIM_DA13_ALT5_GPIO3_IO13 = 5,
   IMX_IOMUXC_EIM_DA13_ALT7_SRC_BOOT_CFG13 = 7,
} IMX_IOMUXC_EIM_DA13_ALT;

typedef enum {
   IMX_IOMUXC_EIM_DA14_ALT0_EIM_AD14 = 0,
   IMX_IOMUXC_EIM_DA14_ALT1_IPU1_DI1_D1_CS = 1,
   IMX_IOMUXC_EIM_DA14_ALT5_GPIO3_IO14 = 5,
   IMX_IOMUXC_EIM_DA14_ALT7_SRC_BOOT_CFG14 = 7,
} IMX_IOMUXC_EIM_DA14_ALT;

typedef enum {
   IMX_IOMUXC_EIM_DA15_ALT0_EIM_AD15 = 0,
   IMX_IOMUXC_EIM_DA15_ALT1_IPU1_DI1_PIN01 = 1,
   IMX_IOMUXC_EIM_DA15_ALT2_IPU1_DI1_PIN04 = 2,
   IMX_IOMUXC_EIM_DA15_ALT5_GPIO3_IO15 = 5,
   IMX_IOMUXC_EIM_DA15_ALT7_SRC_BOOT_CFG15 = 7,
} IMX_IOMUXC_EIM_DA15_ALT;

typedef enum {
   IMX_IOMUXC_EIM_D16_ALT0_EIM_DATA16 = 0,
   IMX_IOMUXC_EIM_D16_ALT1_ECSPI1_SCLK = 1,
   IMX_IOMUXC_EIM_D16_ALT2_IPU1_DI0_PIN05 = 2,
   IMX_IOMUXC_EIM_D16_ALT3_IPU2_CSI1_DATA18 = 3,
   IMX_IOMUXC_EIM_D16_ALT4_HDMI_TX_DDC_SDA = 4,
   IMX_IOMUXC_EIM_D16_ALT5_GPIO3_IO16 = 5,
   IMX_IOMUXC_EIM_D16_ALT6_I2C2_SDA = 6,
} IMX_IOMUXC_EIM_D16_ALT;

typedef enum {
   IMX_IOMUXC_EIM_D17_ALT0_EIM_DATA17 = 0,
   IMX_IOMUXC_EIM_D17_ALT1_ECSPI1_MISO = 1,
   IMX_IOMUXC_EIM_D17_ALT2_IPU1_DI0_PIN06 = 2,
   IMX_IOMUXC_EIM_D17_ALT3_IPU2_CSI1_PIXCLK = 3,
   IMX_IOMUXC_EIM_D17_ALT4_DCIC1_OUT = 4,
   IMX_IOMUXC_EIM_D17_ALT5_GPIO3_IO17 = 5,
   IMX_IOMUXC_EIM_D17_ALT6_I2C3_SCL = 6,
} IMX_IOMUXC_EIM_D17_ALT;

typedef enum {
   IMX_IOMUXC_EIM_D18_ALT0_EIM_DATA18 = 0,
   IMX_IOMUXC_EIM_D18_ALT1_ECSPI1_MOSI = 1,
   IMX_IOMUXC_EIM_D18_ALT2_IPU1_DI0_PIN07 = 2,
   IMX_IOMUXC_EIM_D18_ALT3_IPU2_CSI1_DATA17 = 3,
   IMX_IOMUXC_EIM_D18_ALT4_IPU1_DI1_D0_CS = 4,
   IMX_IOMUXC_EIM_D18_ALT5_GPIO3_IO18 = 5,
   IMX_IOMUXC_EIM_D18_ALT6_I2C3_SDA = 6,
} IMX_IOMUXC_EIM_D18_ALT;

typedef enum {
   IMX_IOMUXC_EIM_D19_ALT0_EIM_DATA19 = 0,
   IMX_IOMUXC_EIM_D19_ALT1_ECSPI1_SS1 = 1,
   IMX_IOMUXC_EIM_D19_ALT2_IPU1_DI0_PIN08 = 2,
   IMX_IOMUXC_EIM_D19_ALT3_IPU2_CSI1_DATA16 = 3,
   IMX_IOMUXC_EIM_D19_ALT4_UART1_CTS_B = 4,
   IMX_IOMUXC_EIM_D19_ALT5_GPIO3_IO19 = 5,
   IMX_IOMUXC_EIM_D19_ALT6_EPIT1_OUT = 6,
} IMX_IOMUXC_EIM_D19_ALT;

typedef enum {
   IMX_IOMUXC_EIM_D20_ALT0_EIM_DATA20 = 0,
   IMX_IOMUXC_EIM_D20_ALT1_ECSPI4_SS0 = 1,
   IMX_IOMUXC_EIM_D20_ALT2_IPU1_DI0_PIN16 = 2,
   IMX_IOMUXC_EIM_D20_ALT3_IPU2_CSI1_DATA15 = 3,
   IMX_IOMUXC_EIM_D20_ALT4_UART1_RTS_B = 4,
   IMX_IOMUXC_EIM_D20_ALT5_GPIO3_IO20 = 5,
   IMX_IOMUXC_EIM_D20_ALT6_EPIT2_OUT = 6,
} IMX_IOMUXC_EIM_D20_ALT;

typedef enum {
   IMX_IOMUXC_EIM_D21_ALT0_EIM_DATA21 = 0,
   IMX_IOMUXC_EIM_D21_ALT1_ECSPI4_SCLK = 1,
   IMX_IOMUXC_EIM_D21_ALT2_IPU1_DI0_PIN17 = 2,
   IMX_IOMUXC_EIM_D21_ALT3_IPU2_CSI1_DATA11 = 3,
   IMX_IOMUXC_EIM_D21_ALT4_USB_OTG_OC = 4,
   IMX_IOMUXC_EIM_D21_ALT5_GPIO3_IO21 = 5,
   IMX_IOMUXC_EIM_D21_ALT6_I2C1_SCL = 6,
   IMX_IOMUXC_EIM_D21_ALT7_SPDIF_IN = 7,
} IMX_IOMUXC_EIM_D21_ALT;

typedef enum {
   IMX_IOMUXC_EIM_D22_ALT0_EIM_DATA22 = 0,
   IMX_IOMUXC_EIM_D22_ALT1_ECSPI4_MISO = 1,
   IMX_IOMUXC_EIM_D22_ALT2_IPU1_DI0_PIN01 = 2,
   IMX_IOMUXC_EIM_D22_ALT3_IPU2_CSI1_DATA10 = 3,
   IMX_IOMUXC_EIM_D22_ALT4_USB_OTG_PWR = 4,
   IMX_IOMUXC_EIM_D22_ALT5_GPIO3_IO22 = 5,
   IMX_IOMUXC_EIM_D22_ALT6_SPDIF_OUT = 6,
} IMX_IOMUXC_EIM_D22_ALT;

typedef enum {
   IMX_IOMUXC_EIM_D23_ALT0_EIM_DATA23 = 0,
   IMX_IOMUXC_EIM_D23_ALT1_IPU1_DI0_D0_CS = 1,
   IMX_IOMUXC_EIM_D23_ALT2_UART3_CTS_B = 2,
   IMX_IOMUXC_EIM_D23_ALT3_UART1_DCD_B = 3,
   IMX_IOMUXC_EIM_D23_ALT4_IPU2_CSI1_DATA_EN = 4,
   IMX_IOMUXC_EIM_D23_ALT5_GPIO3_IO23 = 5,
   IMX_IOMUXC_EIM_D23_ALT6_IPU1_DI1_PIN02 = 6,
   IMX_IOMUXC_EIM_D23_ALT7_IPU1_DI1_PIN14 = 7,
} IMX_IOMUXC_EIM_D23_ALT;

typedef enum {
   IMX_IOMUXC_EIM_D24_ALT0_EIM_DATA24 = 0,
   IMX_IOMUXC_EIM_D24_ALT1_ECSPI4_SS2 = 1,
   IMX_IOMUXC_EIM_D24_ALT2_UART3_TX_DATA = 2,
   IMX_IOMUXC_EIM_D24_ALT3_ECSPI1_SS2 = 3,
   IMX_IOMUXC_EIM_D24_ALT4_ECSPI2_SS2 = 4,
   IMX_IOMUXC_EIM_D24_ALT5_GPIO3_IO24 = 5,
   IMX_IOMUXC_EIM_D24_ALT6_AUD5_RXFS = 6,
   IMX_IOMUXC_EIM_D24_ALT7_UART1_DTR_B = 7,
} IMX_IOMUXC_EIM_D24_ALT;

typedef enum {
   IMX_IOMUXC_EIM_D25_ALT0_EIM_DATA25 = 0,
   IMX_IOMUXC_EIM_D25_ALT1_ECSPI4_SS3 = 1,
   IMX_IOMUXC_EIM_D25_ALT2_UART3_RX_DATA = 2,
   IMX_IOMUXC_EIM_D25_ALT3_ECSPI1_SS3 = 3,
   IMX_IOMUXC_EIM_D25_ALT4_ECSPI2_SS3 = 4,
   IMX_IOMUXC_EIM_D25_ALT5_GPIO3_IO25 = 5,
   IMX_IOMUXC_EIM_D25_ALT6_AUD5_RXC = 6,
   IMX_IOMUXC_EIM_D25_ALT7_UART1_DSR_B = 7,
} IMX_IOMUXC_EIM_D25_ALT;

typedef enum {
   IMX_IOMUXC_EIM_D26_ALT0_EIM_DATA26 = 0,
   IMX_IOMUXC_EIM_D26_ALT1_IPU1_DI1_PIN11 = 1,
   IMX_IOMUXC_EIM_D26_ALT2_IPU1_CSI0_DATA01 = 2,
   IMX_IOMUXC_EIM_D26_ALT3_IPU2_CSI1_DATA14 = 3,
   IMX_IOMUXC_EIM_D26_ALT4_UART2_TX_DATA = 4,
   IMX_IOMUXC_EIM_D26_ALT5_GPIO3_IO26 = 5,
   IMX_IOMUXC_EIM_D26_ALT6_IPU1_SISG2 = 6,
   IMX_IOMUXC_EIM_D26_ALT7_IPU1_DISP1_DATA22 = 7,
} IMX_IOMUXC_EIM_D26_ALT;

typedef enum {
   IMX_IOMUXC_EIM_D27_ALT0_EIM_DATA27 = 0,
   IMX_IOMUXC_EIM_D27_ALT1_IPU1_DI1_PIN13 = 1,
   IMX_IOMUXC_EIM_D27_ALT2_IPU1_CSI0_DATA00 = 2,
   IMX_IOMUXC_EIM_D27_ALT3_IPU2_CSI1_DATA13 = 3,
   IMX_IOMUXC_EIM_D27_ALT4_UART2_RX_DATA = 4,
   IMX_IOMUXC_EIM_D27_ALT5_GPIO3_IO27 = 5,
   IMX_IOMUXC_EIM_D27_ALT6_IPU1_SISG3 = 6,
   IMX_IOMUXC_EIM_D27_ALT7_IPU1_DISP1_DATA23 = 7,
} IMX_IOMUXC_EIM_D27_ALT;

typedef enum {
   IMX_IOMUXC_EIM_D28_ALT0_EIM_DATA28 = 0,
   IMX_IOMUXC_EIM_D28_ALT1_I2C1_SDA = 1,
   IMX_IOMUXC_EIM_D28_ALT2_ECSPI4_MOSI = 2,
   IMX_IOMUXC_EIM_D28_ALT3_IPU2_CSI1_DATA12 = 3,
   IMX_IOMUXC_EIM_D28_ALT4_UART2_CTS_B = 4,
   IMX_IOMUXC_EIM_D28_ALT5_GPIO3_IO28 = 5,
   IMX_IOMUXC_EIM_D28_ALT6_IPU1_EXT_TRIG = 6,
   IMX_IOMUXC_EIM_D28_ALT7_IPU1_DI0_PIN13 = 7,
} IMX_IOMUXC_EIM_D28_ALT;

typedef enum {
   IMX_IOMUXC_EIM_D29_ALT0_EIM_DATA29 = 0,
   IMX_IOMUXC_EIM_D29_ALT1_IPU1_DI1_PIN15 = 1,
   IMX_IOMUXC_EIM_D29_ALT2_ECSPI4_SS0 = 2,
   IMX_IOMUXC_EIM_D29_ALT4_UART2_RTS_B = 4,
   IMX_IOMUXC_EIM_D29_ALT5_GPIO3_IO29 = 5,
   IMX_IOMUXC_EIM_D29_ALT6_IPU2_CSI1_VSYNC = 6,
   IMX_IOMUXC_EIM_D29_ALT7_IPU1_DI0_PIN14 = 7,
} IMX_IOMUXC_EIM_D29_ALT;

typedef enum {
   IMX_IOMUXC_EIM_D30_ALT0_EIM_DATA30 = 0,
   IMX_IOMUXC_EIM_D30_ALT1_IPU1_DISP1_DATA21 = 1,
   IMX_IOMUXC_EIM_D30_ALT2_IPU1_DI0_PIN11 = 2,
   IMX_IOMUXC_EIM_D30_ALT3_IPU1_CSI0_DATA03 = 3,
   IMX_IOMUXC_EIM_D30_ALT4_UART3_CTS_B = 4,
   IMX_IOMUXC_EIM_D30_ALT5_GPIO3_IO30 = 5,
   IMX_IOMUXC_EIM_D30_ALT6_USB_H1_OC = 6,
} IMX_IOMUXC_EIM_D30_ALT;

typedef enum {
   IMX_IOMUXC_EIM_D31_ALT0_EIM_DATA31 = 0,
   IMX_IOMUXC_EIM_D31_ALT1_IPU1_DISP1_DATA20 = 1,
   IMX_IOMUXC_EIM_D31_ALT2_IPU1_DI0_PIN12 = 2,
   IMX_IOMUXC_EIM_D31_ALT3_IPU1_CSI0_DATA02 = 3,
   IMX_IOMUXC_EIM_D31_ALT4_UART3_RTS_B = 4,
   IMX_IOMUXC_EIM_D31_ALT5_GPIO3_IO31 = 5,
   IMX_IOMUXC_EIM_D31_ALT6_USB_H1_PWR = 6,
} IMX_IOMUXC_EIM_D31_ALT;

typedef enum {
   IMX_IOMUXC_GPIO_19_ALT0_KEY_COL5 = 0,
   IMX_IOMUXC_GPIO_19_ALT1_ENET_1588_EVENT0_OUT = 1,
   IMX_IOMUXC_GPIO_19_ALT2_SPDIF_OUT = 2,
   IMX_IOMUXC_GPIO_19_ALT3_CCM_CLKO1 = 3,
   IMX_IOMUXC_GPIO_19_ALT4_ECSPI1_RDY = 4,
   IMX_IOMUXC_GPIO_19_ALT5_GPIO4_IO05 = 5,
   IMX_IOMUXC_GPIO_19_ALT6_ENET_TX_ER = 6,
} IMX_IOMUXC_GPIO_19_ALT;

typedef enum {
   IMX_IOMUXC_KEY_COL0_ALT0_ECSPI1_SCLK = 0,
   IMX_IOMUXC_KEY_COL0_ALT1_ENET_RX_DATA3 = 1,
   IMX_IOMUXC_KEY_COL0_ALT2_AUD5_TXC = 2,
   IMX_IOMUXC_KEY_COL0_ALT3_KEY_COL0 = 3,
   IMX_IOMUXC_KEY_COL0_ALT4_UART4_TX_DATA = 4,
   IMX_IOMUXC_KEY_COL0_ALT5_GPIO4_IO06 = 5,
   IMX_IOMUXC_KEY_COL0_ALT6_DCIC1_OUT = 6,
} IMX_IOMUXC_KEY_COL0_ALT;

typedef enum {
   IMX_IOMUXC_KEY_ROW0_ALT0_ECSPI1_MOSI = 0,
   IMX_IOMUXC_KEY_ROW0_ALT1_ENET_TX_DATA3 = 1,
   IMX_IOMUXC_KEY_ROW0_ALT2_AUD5_TXD = 2,
   IMX_IOMUXC_KEY_ROW0_ALT3_KEY_ROW0 = 3,
   IMX_IOMUXC_KEY_ROW0_ALT4_UART4_RX_DATA = 4,
   IMX_IOMUXC_KEY_ROW0_ALT5_GPIO4_IO07 = 5,
   IMX_IOMUXC_KEY_ROW0_ALT6_DCIC2_OUT = 6,
} IMX_IOMUXC_KEY_ROW0_ALT;

typedef enum {
   IMX_IOMUXC_KEY_COL1_ALT0_ECSPI1_MISO = 0,
   IMX_IOMUXC_KEY_COL1_ALT1_ENET_MDIO = 1,
   IMX_IOMUXC_KEY_COL1_ALT2_AUD5_TXFS = 2,
   IMX_IOMUXC_KEY_COL1_ALT3_KEY_COL1 = 3,
   IMX_IOMUXC_KEY_COL1_ALT4_UART5_TX_DATA = 4,
   IMX_IOMUXC_KEY_COL1_ALT5_GPIO4_IO08 = 5,
   IMX_IOMUXC_KEY_COL1_ALT6_SD1_VSELECT = 6,
} IMX_IOMUXC_KEY_COL1_ALT;

typedef enum {
   IMX_IOMUXC_KEY_ROW1_ALT0_ECSPI1_SS0 = 0,
   IMX_IOMUXC_KEY_ROW1_ALT1_ENET_COL = 1,
   IMX_IOMUXC_KEY_ROW1_ALT2_AUD5_RXD = 2,
   IMX_IOMUXC_KEY_ROW1_ALT3_KEY_ROW1 = 3,
   IMX_IOMUXC_KEY_ROW1_ALT4_UART5_RX_DATA = 4,
   IMX_IOMUXC_KEY_ROW1_ALT5_GPIO4_IO09 = 5,
   IMX_IOMUXC_KEY_ROW1_ALT6_SD2_VSELECT = 6,
} IMX_IOMUXC_KEY_ROW1_ALT;

typedef enum {
   IMX_IOMUXC_KEY_COL2_ALT0_ECSPI1_SS1 = 0,
   IMX_IOMUXC_KEY_COL2_ALT1_ENET_RX_DATA2 = 1,
   IMX_IOMUXC_KEY_COL2_ALT2_FLEXCAN1_TX = 2,
   IMX_IOMUXC_KEY_COL2_ALT3_KEY_COL2 = 3,
   IMX_IOMUXC_KEY_COL2_ALT4_ENET_MDC = 4,
   IMX_IOMUXC_KEY_COL2_ALT5_GPIO4_IO10 = 5,
   IMX_IOMUXC_KEY_COL2_ALT6_USB_H1_PWR_CTL_WAKE = 6,
} IMX_IOMUXC_KEY_COL2_ALT;

typedef enum {
   IMX_IOMUXC_KEY_ROW2_ALT0_ECSPI1_SS2 = 0,
   IMX_IOMUXC_KEY_ROW2_ALT1_ENET_TX_DATA2 = 1,
   IMX_IOMUXC_KEY_ROW2_ALT2_FLEXCAN1_RX = 2,
   IMX_IOMUXC_KEY_ROW2_ALT3_KEY_ROW2 = 3,
   IMX_IOMUXC_KEY_ROW2_ALT4_SD2_VSELECT = 4,
   IMX_IOMUXC_KEY_ROW2_ALT5_GPIO4_IO11 = 5,
   IMX_IOMUXC_KEY_ROW2_ALT6_HDMI_TX_CEC_LINE = 6,
} IMX_IOMUXC_KEY_ROW2_ALT;

typedef enum {
   IMX_IOMUXC_KEY_COL3_ALT0_ECSPI1_SS3 = 0,
   IMX_IOMUXC_KEY_COL3_ALT1_ENET_CRS = 1,
   IMX_IOMUXC_KEY_COL3_ALT2_HDMI_TX_DDC_SCL = 2,
   IMX_IOMUXC_KEY_COL3_ALT3_KEY_COL3 = 3,
   IMX_IOMUXC_KEY_COL3_ALT4_I2C2_SCL = 4,
   IMX_IOMUXC_KEY_COL3_ALT5_GPIO4_IO12 = 5,
   IMX_IOMUXC_KEY_COL3_ALT6_SPDIF_IN = 6,
} IMX_IOMUXC_KEY_COL3_ALT;

typedef enum {
   IMX_IOMUXC_KEY_ROW3_ALT0_XTALOSC_OSC32K_32K_OUT = 0,
   IMX_IOMUXC_KEY_ROW3_ALT1_ASRC_EXT_CLK = 1,
   IMX_IOMUXC_KEY_ROW3_ALT2_HDMI_TX_DDC_SDA = 2,
   IMX_IOMUXC_KEY_ROW3_ALT3_KEY_ROW3 = 3,
   IMX_IOMUXC_KEY_ROW3_ALT4_I2C2_SDA = 4,
   IMX_IOMUXC_KEY_ROW3_ALT5_GPIO4_IO13 = 5,
   IMX_IOMUXC_KEY_ROW3_ALT6_SD1_VSELECT = 6,
} IMX_IOMUXC_KEY_ROW3_ALT;

typedef enum {
   IMX_IOMUXC_KEY_COL4_ALT0_FLEXCAN2_TX = 0,
   IMX_IOMUXC_KEY_COL4_ALT1_IPU1_SISG4 = 1,
   IMX_IOMUXC_KEY_COL4_ALT2_USB_OTG_OC = 2,
   IMX_IOMUXC_KEY_COL4_ALT3_KEY_COL4 = 3,
   IMX_IOMUXC_KEY_COL4_ALT4_UART5_RTS_B = 4,
   IMX_IOMUXC_KEY_COL4_ALT5_GPIO4_IO14 = 5,
} IMX_IOMUXC_KEY_COL4_ALT;

typedef enum {
   IMX_IOMUXC_KEY_ROW4_ALT0_FLEXCAN2_RX = 0,
   IMX_IOMUXC_KEY_ROW4_ALT1_IPU1_SISG5 = 1,
   IMX_IOMUXC_KEY_ROW4_ALT2_USB_OTG_PWR = 2,
   IMX_IOMUXC_KEY_ROW4_ALT3_KEY_ROW4 = 3,
   IMX_IOMUXC_KEY_ROW4_ALT4_UART5_CTS_B = 4,
   IMX_IOMUXC_KEY_ROW4_ALT5_GPIO4_IO15 = 5,
} IMX_IOMUXC_KEY_ROW4_ALT;

typedef enum {
   IMX_IOMUXC_DI0_DISP_CLK_ALT0_IPU1_DI0_DISP_CLK = 0,
   IMX_IOMUXC_DI0_DISP_CLK_ALT1_IPU2_DI0_DISP_CLK = 1,
   IMX_IOMUXC_DI0_DISP_CLK_ALT5_GPIO4_IO16 = 5,
} IMX_IOMUXC_DI0_DISP_CLK_ALT;

typedef enum {
   IMX_IOMUXC_DI0_PIN15_ALT0_IPU1_DI0_PIN15 = 0,
   IMX_IOMUXC_DI0_PIN15_ALT1_IPU2_DI0_PIN15 = 1,
   IMX_IOMUXC_DI0_PIN15_ALT2_AUD6_TXC = 2,
   IMX_IOMUXC_DI0_PIN15_ALT5_GPIO4_IO17 = 5,
} IMX_IOMUXC_DI0_PIN15_ALT;

typedef enum {
   IMX_IOMUXC_DI0_PIN2_ALT0_IPU1_DI0_PIN02 = 0,
   IMX_IOMUXC_DI0_PIN2_ALT1_IPU2_DI0_PIN02 = 1,
   IMX_IOMUXC_DI0_PIN2_ALT2_AUD6_TXD = 2,
   IMX_IOMUXC_DI0_PIN2_ALT5_GPIO4_IO18 = 5,
} IMX_IOMUXC_DI0_PIN2_ALT;

typedef enum {
   IMX_IOMUXC_DI0_PIN3_ALT0_IPU1_DI0_PIN03 = 0,
   IMX_IOMUXC_DI0_PIN3_ALT1_IPU2_DI0_PIN03 = 1,
   IMX_IOMUXC_DI0_PIN3_ALT2_AUD6_TXFS = 2,
   IMX_IOMUXC_DI0_PIN3_ALT5_GPIO4_IO19 = 5,
} IMX_IOMUXC_DI0_PIN3_ALT;

typedef enum {
   IMX_IOMUXC_DI0_PIN4_ALT0_IPU1_DI0_PIN04 = 0,
   IMX_IOMUXC_DI0_PIN4_ALT1_IPU2_DI0_PIN04 = 1,
   IMX_IOMUXC_DI0_PIN4_ALT2_AUD6_RXD = 2,
   IMX_IOMUXC_DI0_PIN4_ALT3_SD1_WP = 3,
   IMX_IOMUXC_DI0_PIN4_ALT5_GPIO4_IO20 = 5,
} IMX_IOMUXC_DI0_PIN4_ALT;

typedef enum {
   IMX_IOMUXC_DISP0_DAT0_ALT0_IPU1_DISP0_DATA00 = 0,
   IMX_IOMUXC_DISP0_DAT0_ALT1_IPU2_DISP0_DATA00 = 1,
   IMX_IOMUXC_DISP0_DAT0_ALT2_ECSPI3_SCLK = 2,
   IMX_IOMUXC_DISP0_DAT0_ALT5_GPIO4_IO21 = 5,
} IMX_IOMUXC_DISP0_DAT0_ALT;

typedef enum {
   IMX_IOMUXC_DISP0_DAT1_ALT0_IPU1_DISP0_DATA01 = 0,
   IMX_IOMUXC_DISP0_DAT1_ALT1_IPU2_DISP0_DATA01 = 1,
   IMX_IOMUXC_DISP0_DAT1_ALT2_ECSPI3_MOSI = 2,
   IMX_IOMUXC_DISP0_DAT1_ALT5_GPIO4_IO22 = 5,
} IMX_IOMUXC_DISP0_DAT1_ALT;

typedef enum {
   IMX_IOMUXC_DISP0_DAT2_ALT0_IPU1_DISP0_DATA02 = 0,
   IMX_IOMUXC_DISP0_DAT2_ALT1_IPU2_DISP0_DATA02 = 1,
   IMX_IOMUXC_DISP0_DAT2_ALT2_ECSPI3_MISO = 2,
   IMX_IOMUXC_DISP0_DAT2_ALT5_GPIO4_IO23 = 5,
} IMX_IOMUXC_DISP0_DAT2_ALT;

typedef enum {
   IMX_IOMUXC_DISP0_DAT3_ALT0_IPU1_DISP0_DATA03 = 0,
   IMX_IOMUXC_DISP0_DAT3_ALT1_IPU2_DISP0_DATA03 = 1,
   IMX_IOMUXC_DISP0_DAT3_ALT2_ECSPI3_SS0 = 2,
   IMX_IOMUXC_DISP0_DAT3_ALT5_GPIO4_IO24 = 5,
} IMX_IOMUXC_DISP0_DAT3_ALT;

typedef enum {
   IMX_IOMUXC_DISP0_DAT4_ALT0_IPU1_DISP0_DATA04 = 0,
   IMX_IOMUXC_DISP0_DAT4_ALT1_IPU2_DISP0_DATA04 = 1,
   IMX_IOMUXC_DISP0_DAT4_ALT2_ECSPI3_SS1 = 2,
   IMX_IOMUXC_DISP0_DAT4_ALT5_GPIO4_IO25 = 5,
} IMX_IOMUXC_DISP0_DAT4_ALT;

typedef enum {
   IMX_IOMUXC_DISP0_DAT5_ALT0_IPU1_DISP0_DATA05 = 0,
   IMX_IOMUXC_DISP0_DAT5_ALT1_IPU2_DISP0_DATA05 = 1,
   IMX_IOMUXC_DISP0_DAT5_ALT2_ECSPI3_SS2 = 2,
   IMX_IOMUXC_DISP0_DAT5_ALT3_AUD6_RXFS = 3,
   IMX_IOMUXC_DISP0_DAT5_ALT5_GPIO4_IO26 = 5,
} IMX_IOMUXC_DISP0_DAT5_ALT;

typedef enum {
   IMX_IOMUXC_DISP0_DAT6_ALT0_IPU1_DISP0_DATA06 = 0,
   IMX_IOMUXC_DISP0_DAT6_ALT1_IPU2_DISP0_DATA06 = 1,
   IMX_IOMUXC_DISP0_DAT6_ALT2_ECSPI3_SS3 = 2,
   IMX_IOMUXC_DISP0_DAT6_ALT3_AUD6_RXC = 3,
   IMX_IOMUXC_DISP0_DAT6_ALT5_GPIO4_IO27 = 5,
} IMX_IOMUXC_DISP0_DAT6_ALT;

typedef enum {
   IMX_IOMUXC_DISP0_DAT7_ALT0_IPU1_DISP0_DATA07 = 0,
   IMX_IOMUXC_DISP0_DAT7_ALT1_IPU2_DISP0_DATA07 = 1,
   IMX_IOMUXC_DISP0_DAT7_ALT2_ECSPI3_RDY = 2,
   IMX_IOMUXC_DISP0_DAT7_ALT5_GPIO4_IO28 = 5,
} IMX_IOMUXC_DISP0_DAT7_ALT;

typedef enum {
   IMX_IOMUXC_DISP0_DAT8_ALT0_IPU1_DISP0_DATA08 = 0,
   IMX_IOMUXC_DISP0_DAT8_ALT1_IPU2_DISP0_DATA08 = 1,
   IMX_IOMUXC_DISP0_DAT8_ALT2_PWM1_OUT = 2,
   IMX_IOMUXC_DISP0_DAT8_ALT3_WDOG1_B = 3,
   IMX_IOMUXC_DISP0_DAT8_ALT5_GPIO4_IO29 = 5,
} IMX_IOMUXC_DISP0_DAT8_ALT;

typedef enum {
   IMX_IOMUXC_DISP0_DAT9_ALT0_IPU1_DISP0_DATA09 = 0,
   IMX_IOMUXC_DISP0_DAT9_ALT1_IPU2_DISP0_DATA09 = 1,
   IMX_IOMUXC_DISP0_DAT9_ALT2_PWM2_OUT = 2,
   IMX_IOMUXC_DISP0_DAT9_ALT3_WDOG2_B = 3,
   IMX_IOMUXC_DISP0_DAT9_ALT5_GPIO4_IO30 = 5,
} IMX_IOMUXC_DISP0_DAT9_ALT;

typedef enum {
   IMX_IOMUXC_DISP0_DAT10_ALT0_IPU1_DISP0_DATA10 = 0,
   IMX_IOMUXC_DISP0_DAT10_ALT1_IPU2_DISP0_DATA10 = 1,
   IMX_IOMUXC_DISP0_DAT10_ALT5_GPIO4_IO31 = 5,
} IMX_IOMUXC_DISP0_DAT10_ALT;

typedef enum {
   IMX_IOMUXC_EIM_WAIT_ALT0_EIM_WAIT_B = 0,
   IMX_IOMUXC_EIM_WAIT_ALT1_EIM_DTACK_B = 1,
   IMX_IOMUXC_EIM_WAIT_ALT5_GPIO5_IO00 = 5,
   IMX_IOMUXC_EIM_WAIT_ALT7_SRC_BOOT_CFG25 = 7,
} IMX_IOMUXC_EIM_WAIT_ALT;

typedef enum {
   IMX_IOMUXC_EIM_A25_ALT0_EIM_ADDR25 = 0,
   IMX_IOMUXC_EIM_A25_ALT1_ECSPI4_SS1 = 1,
   IMX_IOMUXC_EIM_A25_ALT2_ECSPI2_RDY = 2,
   IMX_IOMUXC_EIM_A25_ALT3_IPU1_DI1_PIN12 = 3,
   IMX_IOMUXC_EIM_A25_ALT4_IPU1_DI0_D1_CS = 4,
   IMX_IOMUXC_EIM_A25_ALT5_GPIO5_IO02 = 5,
   IMX_IOMUXC_EIM_A25_ALT6_HDMI_TX_CEC_LINE = 6,
} IMX_IOMUXC_EIM_A25_ALT;

typedef enum {
   IMX_IOMUXC_EIM_A24_ALT0_EIM_ADDR24 = 0,
   IMX_IOMUXC_EIM_A24_ALT1_IPU1_DISP1_DATA19 = 1,
   IMX_IOMUXC_EIM_A24_ALT2_IPU2_CSI1_DATA19 = 2,
   IMX_IOMUXC_EIM_A24_ALT3_IPU2_SISG2 = 3,
   IMX_IOMUXC_EIM_A24_ALT4_IPU1_SISG2 = 4,
   IMX_IOMUXC_EIM_A24_ALT5_GPIO5_IO04 = 5,
   IMX_IOMUXC_EIM_A24_ALT7_SRC_BOOT_CFG24 = 7,
} IMX_IOMUXC_EIM_A24_ALT;

typedef enum {
   IMX_IOMUXC_DISP0_DAT11_ALT0_IPU1_DISP0_DATA11 = 0,
   IMX_IOMUXC_DISP0_DAT11_ALT1_IPU2_DISP0_DATA11 = 1,
   IMX_IOMUXC_DISP0_DAT11_ALT5_GPIO5_IO05 = 5,
} IMX_IOMUXC_DISP0_DAT11_ALT;

typedef enum {
   IMX_IOMUXC_DISP0_DAT12_ALT0_IPU1_DISP0_DATA12 = 0,
   IMX_IOMUXC_DISP0_DAT12_ALT1_IPU2_DISP0_DATA12 = 1,
   IMX_IOMUXC_DISP0_DAT12_ALT5_GPIO5_IO06 = 5,
} IMX_IOMUXC_DISP0_DAT12_ALT;

typedef enum {
   IMX_IOMUXC_DISP0_DAT13_ALT0_IPU1_DISP0_DATA13 = 0,
   IMX_IOMUXC_DISP0_DAT13_ALT1_IPU2_DISP0_DATA13 = 1,
   IMX_IOMUXC_DISP0_DAT13_ALT3_AUD5_RXFS = 3,
   IMX_IOMUXC_DISP0_DAT13_ALT5_GPIO5_IO07 = 5,
} IMX_IOMUXC_DISP0_DAT13_ALT;

typedef enum {
   IMX_IOMUXC_DISP0_DAT14_ALT0_IPU1_DISP0_DATA14 = 0,
   IMX_IOMUXC_DISP0_DAT14_ALT1_IPU2_DISP0_DATA14 = 1,
   IMX_IOMUXC_DISP0_DAT14_ALT3_AUD5_RXC = 3,
   IMX_IOMUXC_DISP0_DAT14_ALT5_GPIO5_IO08 = 5,
} IMX_IOMUXC_DISP0_DAT14_ALT;

typedef enum {
   IMX_IOMUXC_DISP0_DAT15_ALT0_IPU1_DISP0_DATA15 = 0,
   IMX_IOMUXC_DISP0_DAT15_ALT1_IPU2_DISP0_DATA15 = 1,
   IMX_IOMUXC_DISP0_DAT15_ALT2_ECSPI1_SS1 = 2,
   IMX_IOMUXC_DISP0_DAT15_ALT3_ECSPI2_SS1 = 3,
   IMX_IOMUXC_DISP0_DAT15_ALT5_GPIO5_IO09 = 5,
} IMX_IOMUXC_DISP0_DAT15_ALT;

typedef enum {
   IMX_IOMUXC_DISP0_DAT16_ALT0_IPU1_DISP0_DATA16 = 0,
   IMX_IOMUXC_DISP0_DAT16_ALT1_IPU2_DISP0_DATA16 = 1,
   IMX_IOMUXC_DISP0_DAT16_ALT2_ECSPI2_MOSI = 2,
   IMX_IOMUXC_DISP0_DAT16_ALT3_AUD5_TXC = 3,
   IMX_IOMUXC_DISP0_DAT16_ALT4_SDMA_EXT_EVENT0 = 4,
   IMX_IOMUXC_DISP0_DAT16_ALT5_GPIO5_IO10 = 5,
} IMX_IOMUXC_DISP0_DAT16_ALT;

typedef enum {
   IMX_IOMUXC_DISP0_DAT17_ALT0_IPU1_DISP0_DATA17 = 0,
   IMX_IOMUXC_DISP0_DAT17_ALT1_IPU2_DISP0_DATA17 = 1,
   IMX_IOMUXC_DISP0_DAT17_ALT2_ECSPI2_MISO = 2,
   IMX_IOMUXC_DISP0_DAT17_ALT3_AUD5_TXD = 3,
   IMX_IOMUXC_DISP0_DAT17_ALT4_SDMA_EXT_EVENT1 = 4,
   IMX_IOMUXC_DISP0_DAT17_ALT5_GPIO5_IO11 = 5,
} IMX_IOMUXC_DISP0_DAT17_ALT;

typedef enum {
   IMX_IOMUXC_DISP0_DAT18_ALT0_IPU1_DISP0_DATA18 = 0,
   IMX_IOMUXC_DISP0_DAT18_ALT1_IPU2_DISP0_DATA18 = 1,
   IMX_IOMUXC_DISP0_DAT18_ALT2_ECSPI2_SS0 = 2,
   IMX_IOMUXC_DISP0_DAT18_ALT3_AUD5_TXFS = 3,
   IMX_IOMUXC_DISP0_DAT18_ALT4_AUD4_RXFS = 4,
   IMX_IOMUXC_DISP0_DAT18_ALT5_GPIO5_IO12 = 5,
   IMX_IOMUXC_DISP0_DAT18_ALT7_EIM_CS2_B = 7,
} IMX_IOMUXC_DISP0_DAT18_ALT;

typedef enum {
   IMX_IOMUXC_DISP0_DAT19_ALT0_IPU1_DISP0_DATA19 = 0,
   IMX_IOMUXC_DISP0_DAT19_ALT1_IPU2_DISP0_DATA19 = 1,
   IMX_IOMUXC_DISP0_DAT19_ALT2_ECSPI2_SCLK = 2,
   IMX_IOMUXC_DISP0_DAT19_ALT3_AUD5_RXD = 3,
   IMX_IOMUXC_DISP0_DAT19_ALT4_AUD4_RXC = 4,
   IMX_IOMUXC_DISP0_DAT19_ALT5_GPIO5_IO13 = 5,
   IMX_IOMUXC_DISP0_DAT19_ALT7_EIM_CS3_B = 7,
} IMX_IOMUXC_DISP0_DAT19_ALT;

typedef enum {
   IMX_IOMUXC_DISP0_DAT20_ALT0_IPU1_DISP0_DATA20 = 0,
   IMX_IOMUXC_DISP0_DAT20_ALT1_IPU2_DISP0_DATA20 = 1,
   IMX_IOMUXC_DISP0_DAT20_ALT2_ECSPI1_SCLK = 2,
   IMX_IOMUXC_DISP0_DAT20_ALT3_AUD4_TXC = 3,
   IMX_IOMUXC_DISP0_DAT20_ALT5_GPIO5_IO14 = 5,
} IMX_IOMUXC_DISP0_DAT20_ALT;

typedef enum {
   IMX_IOMUXC_DISP0_DAT21_ALT0_IPU1_DISP0_DATA21 = 0,
   IMX_IOMUXC_DISP0_DAT21_ALT1_IPU2_DISP0_DATA21 = 1,
   IMX_IOMUXC_DISP0_DAT21_ALT2_ECSPI1_MOSI = 2,
   IMX_IOMUXC_DISP0_DAT21_ALT3_AUD4_TXD = 3,
   IMX_IOMUXC_DISP0_DAT21_ALT5_GPIO5_IO15 = 5,
} IMX_IOMUXC_DISP0_DAT21_ALT;

typedef enum {
   IMX_IOMUXC_DISP0_DAT22_ALT0_IPU1_DISP0_DATA22 = 0,
   IMX_IOMUXC_DISP0_DAT22_ALT1_IPU2_DISP0_DATA22 = 1,
   IMX_IOMUXC_DISP0_DAT22_ALT2_ECSPI1_MISO = 2,
   IMX_IOMUXC_DISP0_DAT22_ALT3_AUD4_TXFS = 3,
   IMX_IOMUXC_DISP0_DAT22_ALT5_GPIO5_IO16 = 5,
} IMX_IOMUXC_DISP0_DAT22_ALT;

typedef enum {
   IMX_IOMUXC_DISP0_DAT23_ALT0_IPU1_DISP0_DATA23 = 0,
   IMX_IOMUXC_DISP0_DAT23_ALT1_IPU2_DISP0_DATA23 = 1,
   IMX_IOMUXC_DISP0_DAT23_ALT2_ECSPI1_SS0 = 2,
   IMX_IOMUXC_DISP0_DAT23_ALT3_AUD4_RXD = 3,
   IMX_IOMUXC_DISP0_DAT23_ALT5_GPIO5_IO17 = 5,
} IMX_IOMUXC_DISP0_DAT23_ALT;

typedef enum {
   IMX_IOMUXC_CSI0_PIXCLK_ALT0_IPU1_CSI0_PIXCLK = 0,
   IMX_IOMUXC_CSI0_PIXCLK_ALT5_GPIO5_IO18 = 5,
   IMX_IOMUXC_CSI0_PIXCLK_ALT7_ARM_EVENTO = 7,
} IMX_IOMUXC_CSI0_PIXCLK_ALT;

typedef enum {
   IMX_IOMUXC_CSI0_MCLK_ALT0_IPU1_CSI0_HSYNC = 0,
   IMX_IOMUXC_CSI0_MCLK_ALT3_CCM_CLKO1 = 3,
   IMX_IOMUXC_CSI0_MCLK_ALT5_GPIO5_IO19 = 5,
   IMX_IOMUXC_CSI0_MCLK_ALT7_ARM_TRACE_CTL = 7,
} IMX_IOMUXC_CSI0_MCLK_ALT;

typedef enum {
   IMX_IOMUXC_CSI0_DATA_EN_ALT0_IPU1_CSI0_DATA_EN = 0,
   IMX_IOMUXC_CSI0_DATA_EN_ALT1_EIM_DATA00 = 1,
   IMX_IOMUXC_CSI0_DATA_EN_ALT5_GPIO5_IO20 = 5,
   IMX_IOMUXC_CSI0_DATA_EN_ALT7_ARM_TRACE_CLK = 7,
} IMX_IOMUXC_CSI0_DATA_EN_ALT;

typedef enum {
   IMX_IOMUXC_CSI0_VSYNC_ALT0_IPU1_CSI0_VSYNC = 0,
   IMX_IOMUXC_CSI0_VSYNC_ALT1_EIM_DATA01 = 1,
   IMX_IOMUXC_CSI0_VSYNC_ALT5_GPIO5_IO21 = 5,
   IMX_IOMUXC_CSI0_VSYNC_ALT7_ARM_TRACE00 = 7,
} IMX_IOMUXC_CSI0_VSYNC_ALT;

typedef enum {
   IMX_IOMUXC_CSI0_DAT4_ALT0_IPU1_CSI0_DATA04 = 0,
   IMX_IOMUXC_CSI0_DAT4_ALT1_EIM_DATA02 = 1,
   IMX_IOMUXC_CSI0_DAT4_ALT2_ECSPI1_SCLK = 2,
   IMX_IOMUXC_CSI0_DAT4_ALT3_KEY_COL5 = 3,
   IMX_IOMUXC_CSI0_DAT4_ALT4_AUD3_TXC = 4,
   IMX_IOMUXC_CSI0_DAT4_ALT5_GPIO5_IO22 = 5,
   IMX_IOMUXC_CSI0_DAT4_ALT7_ARM_TRACE01 = 7,
} IMX_IOMUXC_CSI0_DAT4_ALT;

typedef enum {
   IMX_IOMUXC_CSI0_DAT5_ALT0_IPU1_CSI0_DATA05 = 0,
   IMX_IOMUXC_CSI0_DAT5_ALT1_EIM_DATA03 = 1,
   IMX_IOMUXC_CSI0_DAT5_ALT2_ECSPI1_MOSI = 2,
   IMX_IOMUXC_CSI0_DAT5_ALT3_KEY_ROW5 = 3,
   IMX_IOMUXC_CSI0_DAT5_ALT4_AUD3_TXD = 4,
   IMX_IOMUXC_CSI0_DAT5_ALT5_GPIO5_IO23 = 5,
   IMX_IOMUXC_CSI0_DAT5_ALT7_ARM_TRACE02 = 7,
} IMX_IOMUXC_CSI0_DAT5_ALT;

typedef enum {
   IMX_IOMUXC_CSI0_DAT6_ALT0_IPU1_CSI0_DATA06 = 0,
   IMX_IOMUXC_CSI0_DAT6_ALT1_EIM_DATA04 = 1,
   IMX_IOMUXC_CSI0_DAT6_ALT2_ECSPI1_MISO = 2,
   IMX_IOMUXC_CSI0_DAT6_ALT3_KEY_COL6 = 3,
   IMX_IOMUXC_CSI0_DAT6_ALT4_AUD3_TXFS = 4,
   IMX_IOMUXC_CSI0_DAT6_ALT5_GPIO5_IO24 = 5,
   IMX_IOMUXC_CSI0_DAT6_ALT7_ARM_TRACE03 = 7,
} IMX_IOMUXC_CSI0_DAT6_ALT;

typedef enum {
   IMX_IOMUXC_CSI0_DAT7_ALT0_IPU1_CSI0_DATA07 = 0,
   IMX_IOMUXC_CSI0_DAT7_ALT1_EIM_DATA05 = 1,
   IMX_IOMUXC_CSI0_DAT7_ALT2_ECSPI1_SS0 = 2,
   IMX_IOMUXC_CSI0_DAT7_ALT3_KEY_ROW6 = 3,
   IMX_IOMUXC_CSI0_DAT7_ALT4_AUD3_RXD = 4,
   IMX_IOMUXC_CSI0_DAT7_ALT5_GPIO5_IO25 = 5,
   IMX_IOMUXC_CSI0_DAT7_ALT7_ARM_TRACE04 = 7,
} IMX_IOMUXC_CSI0_DAT7_ALT;

typedef enum {
   IMX_IOMUXC_CSI0_DAT8_ALT0_IPU1_CSI0_DATA08 = 0,
   IMX_IOMUXC_CSI0_DAT8_ALT1_EIM_DATA06 = 1,
   IMX_IOMUXC_CSI0_DAT8_ALT2_ECSPI2_SCLK = 2,
   IMX_IOMUXC_CSI0_DAT8_ALT3_KEY_COL7 = 3,
   IMX_IOMUXC_CSI0_DAT8_ALT4_I2C1_SDA = 4,
   IMX_IOMUXC_CSI0_DAT8_ALT5_GPIO5_IO26 = 5,
   IMX_IOMUXC_CSI0_DAT8_ALT7_ARM_TRACE05 = 7,
} IMX_IOMUXC_CSI0_DAT8_ALT;

typedef enum {
   IMX_IOMUXC_CSI0_DAT9_ALT0_IPU1_CSI0_DATA09 = 0,
   IMX_IOMUXC_CSI0_DAT9_ALT1_EIM_DATA07 = 1,
   IMX_IOMUXC_CSI0_DAT9_ALT2_ECSPI2_MOSI = 2,
   IMX_IOMUXC_CSI0_DAT9_ALT3_KEY_ROW7 = 3,
   IMX_IOMUXC_CSI0_DAT9_ALT4_I2C1_SCL = 4,
   IMX_IOMUXC_CSI0_DAT9_ALT5_GPIO5_IO27 = 5,
   IMX_IOMUXC_CSI0_DAT9_ALT7_ARM_TRACE06 = 7,
} IMX_IOMUXC_CSI0_DAT9_ALT;

typedef enum {
   IMX_IOMUXC_CSI0_DAT10_ALT0_IPU1_CSI0_DATA10 = 0,
   IMX_IOMUXC_CSI0_DAT10_ALT1_AUD3_RXC = 1,
   IMX_IOMUXC_CSI0_DAT10_ALT2_ECSPI2_MISO = 2,
   IMX_IOMUXC_CSI0_DAT10_ALT3_UART1_TX_DATA = 3,
   IMX_IOMUXC_CSI0_DAT10_ALT5_GPIO5_IO28 = 5,
   IMX_IOMUXC_CSI0_DAT10_ALT7_ARM_TRACE07 = 7,
} IMX_IOMUXC_CSI0_DAT10_ALT;

typedef enum {
   IMX_IOMUXC_CSI0_DAT11_ALT0_IPU1_CSI0_DATA11 = 0,
   IMX_IOMUXC_CSI0_DAT11_ALT1_AUD3_RXFS = 1,
   IMX_IOMUXC_CSI0_DAT11_ALT2_ECSPI2_SS0 = 2,
   IMX_IOMUXC_CSI0_DAT11_ALT3_UART1_RX_DATA = 3,
   IMX_IOMUXC_CSI0_DAT11_ALT5_GPIO5_IO29 = 5,
   IMX_IOMUXC_CSI0_DAT11_ALT7_ARM_TRACE08 = 7,
} IMX_IOMUXC_CSI0_DAT11_ALT;

typedef enum {
   IMX_IOMUXC_CSI0_DAT12_ALT0_IPU1_CSI0_DATA12 = 0,
   IMX_IOMUXC_CSI0_DAT12_ALT1_EIM_DATA08 = 1,
   IMX_IOMUXC_CSI0_DAT12_ALT3_UART4_TX_DATA = 3,
   IMX_IOMUXC_CSI0_DAT12_ALT5_GPIO5_IO30 = 5,
   IMX_IOMUXC_CSI0_DAT12_ALT7_ARM_TRACE09 = 7,
} IMX_IOMUXC_CSI0_DAT12_ALT;

typedef enum {
   IMX_IOMUXC_CSI0_DAT13_ALT0_IPU1_CSI0_DATA13 = 0,
   IMX_IOMUXC_CSI0_DAT13_ALT1_EIM_DATA09 = 1,
   IMX_IOMUXC_CSI0_DAT13_ALT3_UART4_RX_DATA = 3,
   IMX_IOMUXC_CSI0_DAT13_ALT5_GPIO5_IO31 = 5,
   IMX_IOMUXC_CSI0_DAT13_ALT7_ARM_TRACE10 = 7,
} IMX_IOMUXC_CSI0_DAT13_ALT;

typedef enum {
   IMX_IOMUXC_CSI0_DAT14_ALT0_IPU1_CSI0_DATA14 = 0,
   IMX_IOMUXC_CSI0_DAT14_ALT1_EIM_DATA10 = 1,
   IMX_IOMUXC_CSI0_DAT14_ALT3_UART5_TX_DATA = 3,
   IMX_IOMUXC_CSI0_DAT14_ALT5_GPIO6_IO00 = 5,
   IMX_IOMUXC_CSI0_DAT14_ALT7_ARM_TRACE11 = 7,
} IMX_IOMUXC_CSI0_DAT14_ALT;

typedef enum {
   IMX_IOMUXC_CSI0_DAT15_ALT0_IPU1_CSI0_DATA15 = 0,
   IMX_IOMUXC_CSI0_DAT15_ALT1_EIM_DATA11 = 1,
   IMX_IOMUXC_CSI0_DAT15_ALT3_UART5_RX_DATA = 3,
   IMX_IOMUXC_CSI0_DAT15_ALT5_GPIO6_IO01 = 5,
   IMX_IOMUXC_CSI0_DAT15_ALT7_ARM_TRACE12 = 7,
} IMX_IOMUXC_CSI0_DAT15_ALT;

typedef enum {
   IMX_IOMUXC_CSI0_DAT16_ALT0_IPU1_CSI0_DATA16 = 0,
   IMX_IOMUXC_CSI0_DAT16_ALT1_EIM_DATA12 = 1,
   IMX_IOMUXC_CSI0_DAT16_ALT3_UART4_RTS_B = 3,
   IMX_IOMUXC_CSI0_DAT16_ALT5_GPIO6_IO02 = 5,
   IMX_IOMUXC_CSI0_DAT16_ALT7_ARM_TRACE13 = 7,
} IMX_IOMUXC_CSI0_DAT16_ALT;

typedef enum {
   IMX_IOMUXC_CSI0_DAT17_ALT0_IPU1_CSI0_DATA17 = 0,
   IMX_IOMUXC_CSI0_DAT17_ALT1_EIM_DATA13 = 1,
   IMX_IOMUXC_CSI0_DAT17_ALT3_UART4_CTS_B = 3,
   IMX_IOMUXC_CSI0_DAT17_ALT5_GPIO6_IO03 = 5,
   IMX_IOMUXC_CSI0_DAT17_ALT7_ARM_TRACE14 = 7,
} IMX_IOMUXC_CSI0_DAT17_ALT;

typedef enum {
   IMX_IOMUXC_CSI0_DAT18_ALT0_IPU1_CSI0_DATA18 = 0,
   IMX_IOMUXC_CSI0_DAT18_ALT1_EIM_DATA14 = 1,
   IMX_IOMUXC_CSI0_DAT18_ALT3_UART5_RTS_B = 3,
   IMX_IOMUXC_CSI0_DAT18_ALT5_GPIO6_IO04 = 5,
   IMX_IOMUXC_CSI0_DAT18_ALT7_ARM_TRACE15 = 7,
} IMX_IOMUXC_CSI0_DAT18_ALT;

typedef enum {
   IMX_IOMUXC_CSI0_DAT19_ALT0_IPU1_CSI0_DATA19 = 0,
   IMX_IOMUXC_CSI0_DAT19_ALT1_EIM_DATA15 = 1,
   IMX_IOMUXC_CSI0_DAT19_ALT3_UART5_CTS_B = 3,
   IMX_IOMUXC_CSI0_DAT19_ALT5_GPIO6_IO05 = 5,
} IMX_IOMUXC_CSI0_DAT19_ALT;

typedef enum {
   IMX_IOMUXC_EIM_A23_ALT0_EIM_ADDR23 = 0,
   IMX_IOMUXC_EIM_A23_ALT1_IPU1_DISP1_DATA18 = 1,
   IMX_IOMUXC_EIM_A23_ALT2_IPU2_CSI1_DATA18 = 2,
   IMX_IOMUXC_EIM_A23_ALT3_IPU2_SISG3 = 3,
   IMX_IOMUXC_EIM_A23_ALT4_IPU1_SISG3 = 4,
   IMX_IOMUXC_EIM_A23_ALT5_GPIO6_IO06 = 5,
   IMX_IOMUXC_EIM_A23_ALT7_SRC_BOOT_CFG23 = 7,
} IMX_IOMUXC_EIM_A23_ALT;

typedef enum {
   IMX_IOMUXC_NANDF_CLE_ALT0_NAND_CLE = 0,
   IMX_IOMUXC_NANDF_CLE_ALT1_IPU2_SISG4 = 1,
   IMX_IOMUXC_NANDF_CLE_ALT5_GPIO6_IO07 = 5,
} IMX_IOMUXC_NANDF_CLE_ALT;

typedef enum {
   IMX_IOMUXC_NANDF_ALE_ALT0_NAND_ALE = 0,
   IMX_IOMUXC_NANDF_ALE_ALT1_SD4_RESET = 1,
   IMX_IOMUXC_NANDF_ALE_ALT5_GPIO6_IO08 = 5,
} IMX_IOMUXC_NANDF_ALE_ALT;

typedef enum {
   IMX_IOMUXC_NANDF_WP_B_ALT0_NAND_WP_B = 0,
   IMX_IOMUXC_NANDF_WP_B_ALT1_IPU2_SISG5 = 1,
   IMX_IOMUXC_NANDF_WP_B_ALT5_GPIO6_IO09 = 5,
} IMX_IOMUXC_NANDF_WP_B_ALT;

typedef enum {
   IMX_IOMUXC_NANDF_RB0_ALT0_NAND_READY_B = 0,
   IMX_IOMUXC_NANDF_RB0_ALT1_IPU2_DI0_PIN01 = 1,
   IMX_IOMUXC_NANDF_RB0_ALT5_GPIO6_IO10 = 5,
} IMX_IOMUXC_NANDF_RB0_ALT;

typedef enum {
   IMX_IOMUXC_NANDF_CS0_ALT0_NAND_CE0_B = 0,
   IMX_IOMUXC_NANDF_CS0_ALT5_GPIO6_IO11 = 5,
} IMX_IOMUXC_NANDF_CS0_ALT;

typedef enum {
   IMX_IOMUXC_NANDF_CS1_ALT0_NAND_CE1_B = 0,
   IMX_IOMUXC_NANDF_CS1_ALT1_SD4_VSELECT = 1,
   IMX_IOMUXC_NANDF_CS1_ALT2_SD3_VSELECT = 2,
   IMX_IOMUXC_NANDF_CS1_ALT5_GPIO6_IO14 = 5,
} IMX_IOMUXC_NANDF_CS1_ALT;

typedef enum {
   IMX_IOMUXC_NANDF_CS2_ALT0_NAND_CE2_B = 0,
   IMX_IOMUXC_NANDF_CS2_ALT1_IPU1_SISG0 = 1,
   IMX_IOMUXC_NANDF_CS2_ALT2_ESAI_TX0 = 2,
   IMX_IOMUXC_NANDF_CS2_ALT3_EIM_CRE = 3,
   IMX_IOMUXC_NANDF_CS2_ALT4_CCM_CLKO2 = 4,
   IMX_IOMUXC_NANDF_CS2_ALT5_GPIO6_IO15 = 5,
   IMX_IOMUXC_NANDF_CS2_ALT6_IPU2_SISG0 = 6,
} IMX_IOMUXC_NANDF_CS2_ALT;

typedef enum {
   IMX_IOMUXC_NANDF_CS3_ALT0_NAND_CE3_B = 0,
   IMX_IOMUXC_NANDF_CS3_ALT1_IPU1_SISG1 = 1,
   IMX_IOMUXC_NANDF_CS3_ALT2_ESAI_TX1 = 2,
   IMX_IOMUXC_NANDF_CS3_ALT3_EIM_ADDR26 = 3,
   IMX_IOMUXC_NANDF_CS3_ALT5_GPIO6_IO16 = 5,
   IMX_IOMUXC_NANDF_CS3_ALT6_IPU2_SISG1 = 6,
} IMX_IOMUXC_NANDF_CS3_ALT;

typedef enum {
   IMX_IOMUXC_SD3_DAT7_ALT0_SD3_DATA7 = 0,
   IMX_IOMUXC_SD3_DAT7_ALT1_UART1_TX_DATA = 1,
   IMX_IOMUXC_SD3_DAT7_ALT5_GPIO6_IO17 = 5,
} IMX_IOMUXC_SD3_DAT7_ALT;

typedef enum {
   IMX_IOMUXC_SD3_DAT6_ALT0_SD3_DATA6 = 0,
   IMX_IOMUXC_SD3_DAT6_ALT1_UART1_RX_DATA = 1,
   IMX_IOMUXC_SD3_DAT6_ALT5_GPIO6_IO18 = 5,
} IMX_IOMUXC_SD3_DAT6_ALT;

typedef enum {
   IMX_IOMUXC_RGMII_TXC_ALT0_USB_H2_DATA = 0,
   IMX_IOMUXC_RGMII_TXC_ALT1_RGMII_TXC = 1,
   IMX_IOMUXC_RGMII_TXC_ALT2_SPDIF_EXT_CLK = 2,
   IMX_IOMUXC_RGMII_TXC_ALT5_GPIO6_IO19 = 5,
   IMX_IOMUXC_RGMII_TXC_ALT7_XTALOSC_REF_CLK_24M = 7,
} IMX_IOMUXC_RGMII_TXC_ALT;

typedef enum {
   IMX_IOMUXC_RGMII_TD0_ALT0_HSI_TX_READY = 0,
   IMX_IOMUXC_RGMII_TD0_ALT1_RGMII_TD0 = 1,
   IMX_IOMUXC_RGMII_TD0_ALT5_GPIO6_IO20 = 5,
} IMX_IOMUXC_RGMII_TD0_ALT;

typedef enum {
   IMX_IOMUXC_RGMII_TD1_ALT0_HSI_RX_FLAG = 0,
   IMX_IOMUXC_RGMII_TD1_ALT1_RGMII_TD1 = 1,
   IMX_IOMUXC_RGMII_TD1_ALT5_GPIO6_IO21 = 5,
} IMX_IOMUXC_RGMII_TD1_ALT;

typedef enum {
   IMX_IOMUXC_RGMII_TD2_ALT0_HSI_RX_DATA = 0,
   IMX_IOMUXC_RGMII_TD2_ALT1_RGMII_TD2 = 1,
   IMX_IOMUXC_RGMII_TD2_ALT5_GPIO6_IO22 = 5,
} IMX_IOMUXC_RGMII_TD2_ALT;

typedef enum {
   IMX_IOMUXC_RGMII_TD3_ALT0_HSI_RX_WAKE = 0,
   IMX_IOMUXC_RGMII_TD3_ALT1_RGMII_TD3 = 1,
   IMX_IOMUXC_RGMII_TD3_ALT5_GPIO6_IO23 = 5,
} IMX_IOMUXC_RGMII_TD3_ALT;

typedef enum {
   IMX_IOMUXC_RGMII_RX_CTL_ALT0_USB_H3_DATA = 0,
   IMX_IOMUXC_RGMII_RX_CTL_ALT1_RGMII_RX_CTL = 1,
   IMX_IOMUXC_RGMII_RX_CTL_ALT5_GPIO6_IO24 = 5,
} IMX_IOMUXC_RGMII_RX_CTL_ALT;

typedef enum {
   IMX_IOMUXC_RGMII_RD0_ALT0_HSI_RX_READY = 0,
   IMX_IOMUXC_RGMII_RD0_ALT1_RGMII_RD0 = 1,
   IMX_IOMUXC_RGMII_RD0_ALT5_GPIO6_IO25 = 5,
} IMX_IOMUXC_RGMII_RD0_ALT;

typedef enum {
   IMX_IOMUXC_RGMII_TX_CTL_ALT0_USB_H2_STROBE = 0,
   IMX_IOMUXC_RGMII_TX_CTL_ALT1_RGMII_TX_CTL = 1,
   IMX_IOMUXC_RGMII_TX_CTL_ALT5_GPIO6_IO26 = 5,
   IMX_IOMUXC_RGMII_TX_CTL_ALT7_ENET_REF_CLK = 7,
} IMX_IOMUXC_RGMII_TX_CTL_ALT;

typedef enum {
   IMX_IOMUXC_RGMII_RD1_ALT0_HSI_TX_FLAG = 0,
   IMX_IOMUXC_RGMII_RD1_ALT1_RGMII_RD1 = 1,
   IMX_IOMUXC_RGMII_RD1_ALT5_GPIO6_IO27 = 5,
} IMX_IOMUXC_RGMII_RD1_ALT;

typedef enum {
   IMX_IOMUXC_RGMII_RD2_ALT0_HSI_TX_DATA = 0,
   IMX_IOMUXC_RGMII_RD2_ALT1_RGMII_RD2 = 1,
   IMX_IOMUXC_RGMII_RD2_ALT5_GPIO6_IO28 = 5,
} IMX_IOMUXC_RGMII_RD2_ALT;

typedef enum {
   IMX_IOMUXC_RGMII_RD3_ALT0_HSI_TX_WAKE = 0,
   IMX_IOMUXC_RGMII_RD3_ALT1_RGMII_RD3 = 1,
   IMX_IOMUXC_RGMII_RD3_ALT5_GPIO6_IO29 = 5,
} IMX_IOMUXC_RGMII_RD3_ALT;

typedef enum {
   IMX_IOMUXC_RGMII_RXC_ALT0_USB_H3_STROBE = 0,
   IMX_IOMUXC_RGMII_RXC_ALT1_RGMII_RXC = 1,
   IMX_IOMUXC_RGMII_RXC_ALT5_GPIO6_IO30 = 5,
} IMX_IOMUXC_RGMII_RXC_ALT;

typedef enum {
   IMX_IOMUXC_EIM_BCLK_ALT0_EIM_BCLK = 0,
   IMX_IOMUXC_EIM_BCLK_ALT1_IPU1_DI1_PIN16 = 1,
   IMX_IOMUXC_EIM_BCLK_ALT5_GPIO6_IO31 = 5,
} IMX_IOMUXC_EIM_BCLK_ALT;

typedef enum {
   IMX_IOMUXC_SD3_DAT5_ALT0_SD3_DATA5 = 0,
   IMX_IOMUXC_SD3_DAT5_ALT1_UART2_TX_DATA = 1,
   IMX_IOMUXC_SD3_DAT5_ALT5_GPIO7_IO00 = 5,
} IMX_IOMUXC_SD3_DAT5_ALT;

typedef enum {
   IMX_IOMUXC_SD3_DAT4_ALT0_SD3_DATA4 = 0,
   IMX_IOMUXC_SD3_DAT4_ALT1_UART2_RX_DATA = 1,
   IMX_IOMUXC_SD3_DAT4_ALT5_GPIO7_IO01 = 5,
} IMX_IOMUXC_SD3_DAT4_ALT;

typedef enum {
   IMX_IOMUXC_SD3_CMD_ALT0_SD3_CMD = 0,
   IMX_IOMUXC_SD3_CMD_ALT1_UART2_CTS_B = 1,
   IMX_IOMUXC_SD3_CMD_ALT2_FLEXCAN1_TX = 2,
   IMX_IOMUXC_SD3_CMD_ALT5_GPIO7_IO02 = 5,
} IMX_IOMUXC_SD3_CMD_ALT;

typedef enum {
   IMX_IOMUXC_SD3_CLK_ALT0_SD3_CLK = 0,
   IMX_IOMUXC_SD3_CLK_ALT1_UART2_RTS_B = 1,
   IMX_IOMUXC_SD3_CLK_ALT2_FLEXCAN1_RX = 2,
   IMX_IOMUXC_SD3_CLK_ALT5_GPIO7_IO03 = 5,
} IMX_IOMUXC_SD3_CLK_ALT;

typedef enum {
   IMX_IOMUXC_SD3_DAT0_ALT0_SD3_DATA0 = 0,
   IMX_IOMUXC_SD3_DAT0_ALT1_UART1_CTS_B = 1,
   IMX_IOMUXC_SD3_DAT0_ALT2_FLEXCAN2_TX = 2,
   IMX_IOMUXC_SD3_DAT0_ALT5_GPIO7_IO04 = 5,
} IMX_IOMUXC_SD3_DAT0_ALT;

typedef enum {
   IMX_IOMUXC_SD3_DAT1_ALT0_SD3_DATA1 = 0,
   IMX_IOMUXC_SD3_DAT1_ALT1_UART1_RTS_B = 1,
   IMX_IOMUXC_SD3_DAT1_ALT2_FLEXCAN2_RX = 2,
   IMX_IOMUXC_SD3_DAT1_ALT5_GPIO7_IO05 = 5,
} IMX_IOMUXC_SD3_DAT1_ALT;

typedef enum {
   IMX_IOMUXC_SD3_DAT2_ALT0_SD3_DATA2 = 0,
   IMX_IOMUXC_SD3_DAT2_ALT5_GPIO7_IO06 = 5,
} IMX_IOMUXC_SD3_DAT2_ALT;

typedef enum {
   IMX_IOMUXC_SD3_DAT3_ALT0_SD3_DATA3 = 0,
   IMX_IOMUXC_SD3_DAT3_ALT1_UART3_CTS_B = 1,
   IMX_IOMUXC_SD3_DAT3_ALT5_GPIO7_IO07 = 5,
} IMX_IOMUXC_SD3_DAT3_ALT;

typedef enum {
   IMX_IOMUXC_SD3_RST_ALT0_SD3_RESET = 0,
   IMX_IOMUXC_SD3_RST_ALT1_UART3_RTS_B = 1,
   IMX_IOMUXC_SD3_RST_ALT5_GPIO7_IO08 = 5,
} IMX_IOMUXC_SD3_RST_ALT;

typedef enum {
   IMX_IOMUXC_SD4_CMD_ALT0_SD4_CMD = 0,
   IMX_IOMUXC_SD4_CMD_ALT1_NAND_RE_B = 1,
   IMX_IOMUXC_SD4_CMD_ALT2_UART3_TX_DATA = 2,
   IMX_IOMUXC_SD4_CMD_ALT5_GPIO7_IO09 = 5,
} IMX_IOMUXC_SD4_CMD_ALT;

typedef enum {
   IMX_IOMUXC_SD4_CLK_ALT0_SD4_CLK = 0,
   IMX_IOMUXC_SD4_CLK_ALT1_NAND_WE_B = 1,
   IMX_IOMUXC_SD4_CLK_ALT2_UART3_RX_DATA = 2,
   IMX_IOMUXC_SD4_CLK_ALT5_GPIO7_IO10 = 5,
} IMX_IOMUXC_SD4_CLK_ALT;

typedef enum {
   IMX_IOMUXC_GPIO_16_ALT0_ESAI_TX3_RX2 = 0,
   IMX_IOMUXC_GPIO_16_ALT1_ENET_1588_EVENT2_IN = 1,
   IMX_IOMUXC_GPIO_16_ALT2_ENET_REF_CLK = 2,
   IMX_IOMUXC_GPIO_16_ALT3_SD1_LCTL = 3,
   IMX_IOMUXC_GPIO_16_ALT4_SPDIF_IN = 4,
   IMX_IOMUXC_GPIO_16_ALT5_GPIO7_IO11 = 5,
   IMX_IOMUXC_GPIO_16_ALT6_I2C3_SDA = 6,
   IMX_IOMUXC_GPIO_16_ALT7_JTAG_DE_B = 7,
} IMX_IOMUXC_GPIO_16_ALT;

typedef enum {
   IMX_IOMUXC_GPIO_17_ALT0_ESAI_TX0 = 0,
   IMX_IOMUXC_GPIO_17_ALT1_ENET_1588_EVENT3_IN = 1,
   IMX_IOMUXC_GPIO_17_ALT2_CCM_PMIC_READY = 2,
   IMX_IOMUXC_GPIO_17_ALT3_SDMA_EXT_EVENT0 = 3,
   IMX_IOMUXC_GPIO_17_ALT4_SPDIF_OUT = 4,
   IMX_IOMUXC_GPIO_17_ALT5_GPIO7_IO12 = 5,
} IMX_IOMUXC_GPIO_17_ALT;

typedef enum {
   IMX_IOMUXC_GPIO_18_ALT0_ESAI_TX1 = 0,
   IMX_IOMUXC_GPIO_18_ALT1_ENET_RX_CLK = 1,
   IMX_IOMUXC_GPIO_18_ALT2_SD3_VSELECT = 2,
   IMX_IOMUXC_GPIO_18_ALT3_SDMA_EXT_EVENT1 = 3,
   IMX_IOMUXC_GPIO_18_ALT4_ASRC_EXT_CLK = 4,
   IMX_IOMUXC_GPIO_18_ALT5_GPIO7_IO13 = 5,
   IMX_IOMUXC_GPIO_18_ALT6_SNVS_VIO_5_CTL = 6,
} IMX_IOMUXC_GPIO_18_ALT;

typedef enum {
    IMX_IOMUXC_ECSPI1_MISO_EIM_DATA17_ALT1 = 0,
    IMX_IOMUXC_ECSPI1_MISO_DISP0_DATA22_ALT2 = 1,
    IMX_IOMUXC_ECSPI1_MISO_KEY_COL1_ALT0 = 2,
    IMX_IOMUXC_ECSPI1_MISO_CSI0_DATA06_ALT2 = 3,
} IMX_IOMUXC_ECSPI1_MISO_SELECT_INPUT;

typedef enum {
    IMX_IOMUXC_ECSPI2_MISO_EIM_OE_B_ALT2 = 0,
    IMX_IOMUXC_ECSPI2_MISO_DISP0_DATA17_ALT2 = 1,
    IMX_IOMUXC_ECSPI2_MISO_CSI0_DATA10_ALT2 = 2,
} IMX_IOMUXC_ECSPI2_MISO_SELECT_INPUT;

#endif // _IMX6_IOMUX_DQ_H_
