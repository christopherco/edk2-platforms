/** @file
*
*  Header defining IMX6 SoloX Muxing definitions
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
#ifndef _IMX6_IOMUX_SX_H_
#define _IMX6_IOMUX_SX_H_

//
// SELECT INPUT defines

/*
   GPIO1_IO00_ALT0 = 0x1 // Selecting ALT0 of pad GPIO1_IO00 for I2C1_SCL

   GPIO1_IO01_ALT0 = 0x1 // Selecting ALT0 of pad GPIO1_IO01 for I2C1_SDA

   GPIO1_IO02_ALT0 = 0x1 // Selecting ALT0 of pad GPIO1_IO02 for I2C2_SCL
   GPIO1_IO02_ALT1 = 0x1 // Selecting ALT1 of pad GPIO1_IO02 for SD1_CD_B

   GPIO1_IO03_ALT0 = 0x1 // Selecting ALT0 of pad GPIO1_IO03 for I2C2_SDA
   GPIO1_IO03_ALT1 = 0x1 // Selecting ALT1 of pad GPIO1_IO03 for SD1_WP

   GPIO1_IO04_ALT0 = 0x0 // Selecting ALT0 of pad GPIO1_IO04 for UART1_TX_DATA
   GPIO1_IO04_ALT4 = 0x0 // Selecting ALT4 of pad GPIO1_IO04 for ENET2_REF_CLK2

   GPIO1_IO05_ALT0 = 0x1 // Selecting ALT0 of pad GPIO1_IO05 for UART1_RX_DATA
   GPIO1_IO05_ALT2 = 0x0 // Selecting ALT2 of pad GPIO1_IO05 for ENET1_MDIO
   GPIO1_IO05_ALT4 = 0x0 // Selecting ALT4 of pad GPIO1_IO05 for ENET1_REF_CLK1

   GPIO1_IO06_ALT0 = 0x0 // Selecting ALT0 of pad GPIO1_IO06 for UART2_TX_DATA
   GPIO1_IO06_ALT1 = 0x1 // Selecting ALT1 of pad GPIO1_IO06 for SD2_CD_B
   GPIO1_IO06_ALT4 = 0x0 // Selecting ALT4 of pad GPIO1_IO06 for UART1_RTS_B

   GPIO1_IO07_ALT0 = 0x1 // Selecting ALT0 of pad GPIO1_IO07 for UART2_RX_DATA
   GPIO1_IO07_ALT1 = 0x1 // Selecting ALT1 of pad GPIO1_IO07 for SD2_WP
   GPIO1_IO07_ALT2 = 0x0 // Selecting ALT2 of pad GPIO1_IO07 for ENET2_MDIO
   GPIO1_IO07_ALT4 = 0x1 // Selecting ALT4 of pad GPIO1_IO07 for UART1_CTS_B

   GPIO1_IO08_ALT0 = 0x0 // Selecting ALT0 of pad GPIO1_IO08 for USB_OTG1_OC
   GPIO1_IO08_ALT2 = 0x0 // Selecting ALT2 of pad GPIO1_IO08 for SDMA_EXT_EVENT0
   GPIO1_IO08_ALT3 = 0x1 // Selecting ALT3 of pad GPIO1_IO08 for CCM_PMIC_READY
   GPIO1_IO08_ALT4 = 0x0 // Selecting ALT4 of pad GPIO1_IO08 for UART2_RTS_B

   GPIO1_IO09_ALT2 = 0x0 // Selecting ALT2 of pad GPIO1_IO09 for SDMA_EXT_EVENT1
   GPIO1_IO09_ALT4 = 0x1 // Selecting ALT4 of pad GPIO1_IO09 for UART2_CTS_B

   GPIO1_IO10_ALT0 = 0x0 // Selecting ALT0 of pad GPIO1_IO10 for USB_OTG1_ID
   GPIO1_IO10_ALT1 = 0x0 // Selecting ALT1 of pad GPIO1_IO10 for SPDIF_EXT_CLK
   GPIO1_IO10_ALT4 = 0x1 // Selecting ALT4 of pad GPIO1_IO10 for CSI1_FIELD

   GPIO1_IO11_ALT0 = 0x0 // Selecting ALT0 of pad GPIO1_IO11 for USB_OTG2_OC
   GPIO1_IO11_ALT1 = 0x2 // Selecting ALT1 of pad GPIO1_IO11 for SPDIF_IN
   GPIO1_IO11_ALT4 = 0x0 // Selecting ALT4 of pad GPIO1_IO11 for MLB_DATA

   GPIO1_IO12_ALT4 = 0x0 // Selecting ALT4 of pad GPIO1_IO12 for MLB_CLK

   GPIO1_IO13_ALT1 = 0x0 // Selecting ALT1 of pad GPIO1_IO13 for USB_OTG2_ID
   GPIO1_IO13_ALT4 = 0x0 // Selecting ALT4 of pad GPIO1_IO13 for MLB_SIG

   CSI_DATA00_ALT0 = 0x0 // Selecting ALT0 of pad CSI_DATA00 for CSI1_DATA02
   CSI_DATA00_ALT1 = 0x1 // Selecting ALT1 of pad CSI_DATA00 for ESAI_TX_CLK
   CSI_DATA00_ALT2 = 0x1 // Selecting ALT2 of pad CSI_DATA00 for AUD6_TXC
   CSI_DATA00_ALT3 = 0x0 // Selecting ALT3 of pad CSI_DATA00 for I2C1_SCL
   CSI_DATA00_ALT7 = 0x0 // Selecting ALT7 of pad CSI_DATA00 for SAI1_TX_BCLK

   CSI_DATA01_ALT0 = 0x0 // Selecting ALT0 of pad CSI_DATA01 for CSI1_DATA03
   CSI_DATA01_ALT1 = 0x1 // Selecting ALT1 of pad CSI_DATA01 for ESAI_TX_FS
   CSI_DATA01_ALT2 = 0x1 // Selecting ALT2 of pad CSI_DATA01 for AUD6_TXFS
   CSI_DATA01_ALT3 = 0x0 // Selecting ALT3 of pad CSI_DATA01 for I2C1_SDA
   CSI_DATA01_ALT7 = 0x0 // Selecting ALT7 of pad CSI_DATA01 for SAI1_TX_SYNC

   CSI_DATA02_ALT0 = 0x0 // Selecting ALT0 of pad CSI_DATA02 for CSI1_DATA04
   CSI_DATA02_ALT1 = 0x1 // Selecting ALT1 of pad CSI_DATA02 for ESAI_RX_CLK
   CSI_DATA02_ALT2 = 0x1 // Selecting ALT2 of pad CSI_DATA02 for AUD6_RXC
   CSI_DATA02_ALT3 = 0x0 // Selecting ALT3 of pad CSI_DATA02 for KPP_COL5
   CSI_DATA02_ALT7 = 0x0 // Selecting ALT7 of pad CSI_DATA02 for SAI1_RX_BCLK

   CSI_DATA03_ALT0 = 0x0 // Selecting ALT0 of pad CSI_DATA03 for CSI1_DATA05
   CSI_DATA03_ALT1 = 0x1 // Selecting ALT1 of pad CSI_DATA03 for ESAI_RX_FS
   CSI_DATA03_ALT2 = 0x1 // Selecting ALT2 of pad CSI_DATA03 for AUD6_RXFS
   CSI_DATA03_ALT3 = 0x0 // Selecting ALT3 of pad CSI_DATA03 for KPP_ROW5
   CSI_DATA03_ALT7 = 0x0 // Selecting ALT7 of pad CSI_DATA03 for SAI1_RX_SYNC

   CSI_DATA04_ALT0 = 0x0 // Selecting ALT0 of pad CSI_DATA04 for CSI1_DATA06
   CSI_DATA04_ALT1 = 0x1 // Selecting ALT1 of pad CSI_DATA04 for ESAI_TX1
   CSI_DATA04_ALT3 = 0x0 // Selecting ALT3 of pad CSI_DATA04 for KPP_COL6
   CSI_DATA04_ALT4 = 0x0 // Selecting ALT4 of pad CSI_DATA04 for UART6_RX_DATA

   CSI_DATA05_ALT0 = 0x0 // Selecting ALT0 of pad CSI_DATA05 for CSI1_DATA07
   CSI_DATA05_ALT1 = 0x1 // Selecting ALT1 of pad CSI_DATA05 for ESAI_TX4_RX1
   CSI_DATA05_ALT2 = 0x1 // Selecting ALT2 of pad CSI_DATA05 for SPDIF_IN
   CSI_DATA05_ALT3 = 0x0 // Selecting ALT3 of pad CSI_DATA05 for KPP_ROW6
   CSI_DATA05_ALT4 = 0x1 // Selecting ALT4 of pad CSI_DATA05 for UART6_TX_DATA

   CSI_DATA06_ALT0 = 0x0 // Selecting ALT0 of pad CSI_DATA06 for CSI1_DATA08
   CSI_DATA06_ALT1 = 0x1 // Selecting ALT1 of pad CSI_DATA06 for ESAI_TX2_RX3
   CSI_DATA06_ALT2 = 0x2 // Selecting ALT2 of pad CSI_DATA06 for I2C4_SCL
   CSI_DATA06_ALT3 = 0x0 // Selecting ALT3 of pad CSI_DATA06 for KPP_COL7
   CSI_DATA06_ALT4 = 0x0 // Selecting ALT4 of pad CSI_DATA06 for UART6_RTS_B

   CSI_DATA07_ALT0 = 0x0 // Selecting ALT0 of pad CSI_DATA07 for CSI1_DATA09
   CSI_DATA07_ALT1 = 0x1 // Selecting ALT1 of pad CSI_DATA07 for ESAI_TX3_RX2
   CSI_DATA07_ALT2 = 0x2 // Selecting ALT2 of pad CSI_DATA07 for I2C4_SDA
   CSI_DATA07_ALT3 = 0x0 // Selecting ALT3 of pad CSI_DATA07 for KPP_ROW7
   CSI_DATA07_ALT4 = 0x1 // Selecting ALT4 of pad CSI_DATA07 for UART6_CTS_B

   CSI_HSYNC_ALT0 = 0x0 // Selecting ALT0 of pad CSI_HSYNC for CSI1_HSYNC
   CSI_HSYNC_ALT1 = 0x1 // Selecting ALT1 of pad CSI_HSYNC for ESAI_TX0
   CSI_HSYNC_ALT2 = 0x1 // Selecting ALT2 of pad CSI_HSYNC for AUD6_TXD
   CSI_HSYNC_ALT3 = 0x2 // Selecting ALT3 of pad CSI_HSYNC for UART4_RTS_B

   CSI_MCLK_ALT1 = 0x1 // Selecting ALT1 of pad CSI_MCLK for ESAI_TX_HF_CLK
   CSI_MCLK_ALT3 = 0x2 // Selecting ALT3 of pad CSI_MCLK for UART4_RX_DATA
   CSI_MCLK_ALT7 = 0x0 // Selecting ALT7 of pad CSI_MCLK for CSI1_FIELD

   CSI_PIXCLK_ALT0 = 0x0 // Selecting ALT0 of pad CSI_PIXCLK for CSI1_PIXCLK
   CSI_PIXCLK_ALT1 = 0x1 // Selecting ALT1 of pad CSI_PIXCLK for ESAI_RX_HF_CLK
   CSI_PIXCLK_ALT3 = 0x3 // Selecting ALT3 of pad CSI_PIXCLK for UART4_TX_DATA
   CSI_PIXCLK_ALT7 = 0x2 // Selecting ALT7 of pad CSI_PIXCLK for ESAI_TX_HF_CLK

   CSI_VSYNC_ALT0 = 0x0 // Selecting ALT0 of pad CSI_VSYNC for CSI1_VSYNC
   CSI_VSYNC_ALT1 = 0x1 // Selecting ALT1 of pad CSI_VSYNC for ESAI_TX5_RX0
   CSI_VSYNC_ALT2 = 0x1 // Selecting ALT2 of pad CSI_VSYNC for AUD6_RXD
   CSI_VSYNC_ALT3 = 0x3 // Selecting ALT3 of pad CSI_VSYNC for UART4_CTS_B
   CSI_VSYNC_ALT7 = 0x0 // Selecting ALT7 of pad CSI_VSYNC for SAI1_RX_DATA0

   ENET1_COL_ALT2 = 0x1 // Selecting ALT2 of pad ENET1_COL for AUD4_TXC
   ENET1_COL_ALT4 = 0x1 // Selecting ALT4 of pad ENET1_COL for SPDIF_EXT_CLK

   ENET1_CRS_ALT1 = 0x1 // Selecting ALT1 of pad ENET1_CRS for ENET2_MDIO
   ENET1_CRS_ALT2 = 0x1 // Selecting ALT2 of pad ENET1_CRS for AUD4_TXD

   ENET1_MDC_ALT2 = 0x1 // Selecting ALT2 of pad ENET1_MDC for AUD3_RXFS

   ENET1_MDIO_ALT0 = 0x1 // Selecting ALT0 of pad ENET1_MDIO for ENET1_MDIO
   ENET1_MDIO_ALT1 = 0x2 // Selecting ALT1 of pad ENET1_MDIO for ENET2_MDIO
   ENET1_MDIO_ALT6 = 0x1 // Selecting ALT6 of pad ENET1_MDIO for USB_OTG1_OC

   ENET1_RX_CLK_ALT0 = 0x0 // Selecting ALT0 of pad ENET1_RX_CLK for ENET1_RX_CLK
   ENET1_RX_CLK_ALT2 = 0x1 // Selecting ALT2 of pad ENET1_RX_CLK for AUD4_TXFS

   ENET1_TX_CLK_ALT1 = 0x1 // Selecting ALT1 of pad ENET1_TX_CLK for ENET1_REF_CLK1
   ENET1_TX_CLK_ALT2 = 0x1 // Selecting ALT2 of pad ENET1_TX_CLK for AUD4_RXD

   ENET2_COL_ALT2 = 0x1 // Selecting ALT2 of pad ENET2_COL for AUD4_RXC
   ENET2_COL_ALT3 = 0x2 // Selecting ALT3 of pad ENET2_COL for UART1_RX_DATA
   ENET2_COL_ALT4 = 0x3 // Selecting ALT4 of pad ENET2_COL for SPDIF_IN
   ENET2_COL_ALT6 = 0x1 // Selecting ALT6 of pad ENET2_COL for USB_OTG1_ID

   ENET2_CRS_ALT1 = 0x2 // Selecting ALT1 of pad ENET2_CRS for ENET1_MDIO
   ENET2_CRS_ALT2 = 0x1 // Selecting ALT2 of pad ENET2_CRS for AUD4_RXFS
   ENET2_CRS_ALT3 = 0x3 // Selecting ALT3 of pad ENET2_CRS for UART1_TX_DATA
   ENET2_CRS_ALT4 = 0x1 // Selecting ALT4 of pad ENET2_CRS for MLB_SIG
   ENET2_CRS_ALT6 = 0x1 // Selecting ALT6 of pad ENET2_CRS for USB_OTG2_ID

   ENET2_RX_CLK_ALT0 = 0x0 // Selecting ALT0 of pad ENET2_RX_CLK for ENET2_RX_CLK
   ENET2_RX_CLK_ALT2 = 0x1 // Selecting ALT2 of pad ENET2_RX_CLK for I2C3_SCL
   ENET2_RX_CLK_ALT3 = 0x2 // Selecting ALT3 of pad ENET2_RX_CLK for UART1_RTS_B
   ENET2_RX_CLK_ALT4 = 0x1 // Selecting ALT4 of pad ENET2_RX_CLK for MLB_DATA
   ENET2_RX_CLK_ALT6 = 0x1 // Selecting ALT6 of pad ENET2_RX_CLK for USB_OTG2_OC

   ENET2_TX_CLK_ALT1 = 0x1 // Selecting ALT1 of pad ENET2_TX_CLK for ENET2_REF_CLK2
   ENET2_TX_CLK_ALT2 = 0x1 // Selecting ALT2 of pad ENET2_TX_CLK for I2C3_SDA
   ENET2_TX_CLK_ALT3 = 0x3 // Selecting ALT3 of pad ENET2_TX_CLK for UART1_CTS_B
   ENET2_TX_CLK_ALT4 = 0x1 // Selecting ALT4 of pad ENET2_TX_CLK for MLB_CLK

   KEY_COL0_ALT2 = 0x2 // Selecting ALT2 of pad KEY_COL0 for UART6_RTS_B
   KEY_COL0_ALT3 = 0x0 // Selecting ALT3 of pad KEY_COL0 for ECSPI1_SCLK
   KEY_COL0_ALT4 = 0x0 // Selecting ALT4 of pad KEY_COL0 for AUD5_TXC
   KEY_COL0_ALT6 = 0x1 // Selecting ALT6 of pad KEY_COL0 for SDMA_EXT_EVENT1
   KEY_COL0_ALT7 = 0x0 // Selecting ALT7 of pad KEY_COL0 for SAI2_TX_BCLK

   KEY_COL1_ALT2 = 0x2 // Selecting ALT2 of pad KEY_COL1 for UART6_TX_DATA
   KEY_COL1_ALT3 = 0x0 // Selecting ALT3 of pad KEY_COL1 for ECSPI1_MISO
   KEY_COL1_ALT4 = 0x0 // Selecting ALT4 of pad KEY_COL1 for AUD5_TXFS
   KEY_COL1_ALT7 = 0x0 // Selecting ALT7 of pad KEY_COL1 for SAI2_TX_SYNC

   KEY_COL2_ALT1 = 0x1 // Selecting ALT1 of pad KEY_COL2 for SD4_CD_B
   KEY_COL2_ALT2 = 0x2 // Selecting ALT2 of pad KEY_COL2 for UART5_RTS_B

   KEY_COL3_ALT2 = 0x2 // Selecting ALT2 of pad KEY_COL3 for UART5_TX_DATA

   KEY_COL4_ALT2 = 0x2 // Selecting ALT2 of pad KEY_COL4 for I2C3_SCL
   KEY_COL4_ALT4 = 0x0 // Selecting ALT4 of pad KEY_COL4 for AUD5_RXC
   KEY_COL4_ALT7 = 0x0 // Selecting ALT7 of pad KEY_COL4 for SAI2_RX_BCLK

   KEY_ROW0_ALT2 = 0x3 // Selecting ALT2 of pad KEY_ROW0 for UART6_CTS_B
   KEY_ROW0_ALT3 = 0x0 // Selecting ALT3 of pad KEY_ROW0 for ECSPI1_MOSI
   KEY_ROW0_ALT4 = 0x0 // Selecting ALT4 of pad KEY_ROW0 for AUD5_TXD
   KEY_ROW0_ALT6 = 0x1 // Selecting ALT6 of pad KEY_ROW0 for SDMA_EXT_EVENT0

   KEY_ROW1_ALT2 = 0x3 // Selecting ALT2 of pad KEY_ROW1 for UART6_RX_DATA
   KEY_ROW1_ALT3 = 0x0 // Selecting ALT3 of pad KEY_ROW1 for ECSPI1_SS0
   KEY_ROW1_ALT4 = 0x0 // Selecting ALT4 of pad KEY_ROW1 for AUD5_RXD
   KEY_ROW1_ALT7 = 0x0 // Selecting ALT7 of pad KEY_ROW1 for SAI2_RX_DATA0

   KEY_ROW2_ALT2 = 0x3 // Selecting ALT2 of pad KEY_ROW2 for UART5_CTS_B
   KEY_ROW2_ALT3 = 0x1 // Selecting ALT3 of pad KEY_ROW2 for CAN1_RX

   KEY_ROW3_ALT2 = 0x3 // Selecting ALT2 of pad KEY_ROW3 for UART5_RX_DATA
   KEY_ROW3_ALT3 = 0x1 // Selecting ALT3 of pad KEY_ROW3 for CAN2_RX

   KEY_ROW4_ALT1 = 0x3 // Selecting ALT1 of pad KEY_ROW4 for ENET2_MDIO
   KEY_ROW4_ALT2 = 0x2 // Selecting ALT2 of pad KEY_ROW4 for I2C3_SDA
   KEY_ROW4_ALT4 = 0x0 // Selecting ALT4 of pad KEY_ROW4 for AUD5_RXFS
   KEY_ROW4_ALT7 = 0x0 // Selecting ALT7 of pad KEY_ROW4 for SAI2_RX_SYNC

   LCD1_CLK_ALT2 = 0x1 // Selecting ALT2 of pad LCD1_CLK for AUD3_RXC
   LCD1_CLK_ALT4 = 0x0 // Selecting ALT4 of pad LCD1_CLK for CSI1_DATA16
   LCD1_CLK_ALT6 = 0x0 // Selecting ALT6 of pad LCD1_CLK for SD1_WP

   LCD1_DATA00_ALT4 = 0x0 // Selecting ALT4 of pad LCD1_DATA00 for CSI1_DATA20

   LCD1_DATA01_ALT4 = 0x0 // Selecting ALT4 of pad LCD1_DATA01 for CSI1_DATA21

   LCD1_DATA02_ALT4 = 0x0 // Selecting ALT4 of pad LCD1_DATA02 for CSI1_DATA22

   LCD1_DATA03_ALT4 = 0x0 // Selecting ALT4 of pad LCD1_DATA03 for CSI1_DATA23

   LCD1_DATA04_ALT4 = 0x1 // Selecting ALT4 of pad LCD1_DATA04 for CSI1_VSYNC

   LCD1_DATA05_ALT4 = 0x1 // Selecting ALT4 of pad LCD1_DATA05 for CSI1_HSYNC

   LCD1_DATA06_ALT4 = 0x1 // Selecting ALT4 of pad LCD1_DATA06 for CSI1_PIXCLK

   LCD1_DATA08_ALT4 = 0x1 // Selecting ALT4 of pad LCD1_DATA08 for CSI1_DATA09

   LCD1_DATA09_ALT4 = 0x1 // Selecting ALT4 of pad LCD1_DATA09 for CSI1_DATA08

   LCD1_DATA10_ALT4 = 0x1 // Selecting ALT4 of pad LCD1_DATA10 for CSI1_DATA07

   LCD1_DATA11_ALT4 = 0x1 // Selecting ALT4 of pad LCD1_DATA11 for CSI1_DATA06

   LCD1_DATA12_ALT4 = 0x1 // Selecting ALT4 of pad LCD1_DATA12 for CSI1_DATA05

   LCD1_DATA13_ALT4 = 0x1 // Selecting ALT4 of pad LCD1_DATA13 for CSI1_DATA04

   LCD1_DATA14_ALT4 = 0x1 // Selecting ALT4 of pad LCD1_DATA14 for CSI1_DATA03

   LCD1_DATA15_ALT4 = 0x1 // Selecting ALT4 of pad LCD1_DATA15 for CSI1_DATA02

   LCD1_DATA16_ALT4 = 0x0 // Selecting ALT4 of pad LCD1_DATA16 for CSI1_DATA01

   LCD1_DATA17_ALT4 = 0x0 // Selecting ALT4 of pad LCD1_DATA17 for CSI1_DATA00

   LCD1_DATA18_ALT4 = 0x0 // Selecting ALT4 of pad LCD1_DATA18 for CSI1_DATA15

   LCD1_DATA19_ALT4 = 0x0 // Selecting ALT4 of pad LCD1_DATA19 for CSI1_DATA14

   LCD1_DATA20_ALT4 = 0x0 // Selecting ALT4 of pad LCD1_DATA20 for CSI1_DATA13

   LCD1_DATA21_ALT4 = 0x0 // Selecting ALT4 of pad LCD1_DATA21 for CSI1_DATA12

   LCD1_DATA22_ALT4 = 0x0 // Selecting ALT4 of pad LCD1_DATA22 for CSI1_DATA11

   LCD1_DATA23_ALT4 = 0x0 // Selecting ALT4 of pad LCD1_DATA23 for CSI1_DATA10

   LCD1_ENABLE_ALT2 = 0x1 // Selecting ALT2 of pad LCD1_ENABLE for AUD3_TXC
   LCD1_ENABLE_ALT4 = 0x0 // Selecting ALT4 of pad LCD1_ENABLE for CSI1_DATA17
   LCD1_ENABLE_ALT6 = 0x0 // Selecting ALT6 of pad LCD1_ENABLE for SD1_CD_B

   LCD1_HSYNC_ALT0 = 0x0 // Selecting ALT0 of pad LCD1_HSYNC for LCD1_HSYNC
   LCD1_HSYNC_ALT2 = 0x1 // Selecting ALT2 of pad LCD1_HSYNC for AUD3_TXD
   LCD1_HSYNC_ALT4 = 0x0 // Selecting ALT4 of pad LCD1_HSYNC for CSI1_DATA18
   LCD1_HSYNC_ALT6 = 0x0 // Selecting ALT6 of pad LCD1_HSYNC for SD2_WP

   LCD1_RESET_ALT2 = 0x1 // Selecting ALT2 of pad LCD1_RESET for AUD3_RXD
   LCD1_RESET_ALT6 = 0x0 // Selecting ALT6 of pad LCD1_RESET for CCM_PMIC_READY

   LCD1_VSYNC_ALT1 = 0x1 // Selecting ALT1 of pad LCD1_VSYNC for LCD1_BUSY
   LCD1_VSYNC_ALT2 = 0x1 // Selecting ALT2 of pad LCD1_VSYNC for AUD3_TXFS
   LCD1_VSYNC_ALT4 = 0x0 // Selecting ALT4 of pad LCD1_VSYNC for CSI1_DATA19
   LCD1_VSYNC_ALT6 = 0x0 // Selecting ALT6 of pad LCD1_VSYNC for SD2_CD_B

   NAND_ALE_ALT1 = 0x0 // Selecting ALT1 of pad NAND_ALE for I2C3_SDA
   NAND_ALE_ALT3 = 0x0 // Selecting ALT3 of pad NAND_ALE for ECSPI2_SS0
   NAND_ALE_ALT4 = 0x0 // Selecting ALT4 of pad NAND_ALE for ESAI_TX3_RX2

   NAND_CE0_B_ALT3 = 0x0 // Selecting ALT3 of pad NAND_CE0_B for AUD4_TXC
   NAND_CE0_B_ALT4 = 0x0 // Selecting ALT4 of pad NAND_CE0_B for ESAI_TX_CLK

   NAND_CE1_B_ALT3 = 0x0 // Selecting ALT3 of pad NAND_CE1_B for AUD4_TXD
   NAND_CE1_B_ALT4 = 0x0 // Selecting ALT4 of pad NAND_CE1_B for ESAI_TX0

   NAND_CLE_ALT1 = 0x0 // Selecting ALT1 of pad NAND_CLE for I2C3_SCL
   NAND_CLE_ALT3 = 0x0 // Selecting ALT3 of pad NAND_CLE for ECSPI2_SCLK
   NAND_CLE_ALT4 = 0x0 // Selecting ALT4 of pad NAND_CLE for ESAI_TX2_RX3

   NAND_DATA00_ALT3 = 0x0 // Selecting ALT3 of pad NAND_DATA00 for ECSPI5_MISO
   NAND_DATA00_ALT4 = 0x0 // Selecting ALT4 of pad NAND_DATA00 for ESAI_RX_CLK

   NAND_DATA01_ALT3 = 0x0 // Selecting ALT3 of pad NAND_DATA01 for ECSPI5_MOSI
   NAND_DATA01_ALT4 = 0x0 // Selecting ALT4 of pad NAND_DATA01 for ESAI_RX_FS

   NAND_DATA02_ALT3 = 0x0 // Selecting ALT3 of pad NAND_DATA02 for ECSPI5_SCLK
   NAND_DATA02_ALT4 = 0x0 // Selecting ALT4 of pad NAND_DATA02 for ESAI_TX_HF_CLK

   NAND_DATA03_ALT3 = 0x0 // Selecting ALT3 of pad NAND_DATA03 for ECSPI5_SS0
   NAND_DATA03_ALT4 = 0x0 // Selecting ALT4 of pad NAND_DATA03 for ESAI_RX_HF_CLK

   NAND_DATA04_ALT3 = 0x0 // Selecting ALT3 of pad NAND_DATA04 for UART3_RTS_B
   NAND_DATA04_ALT4 = 0x0 // Selecting ALT4 of pad NAND_DATA04 for AUD4_RXFS

   NAND_DATA05_ALT3 = 0x1 // Selecting ALT3 of pad NAND_DATA05 for UART3_CTS_B
   NAND_DATA05_ALT4 = 0x0 // Selecting ALT4 of pad NAND_DATA05 for AUD4_RXC

   NAND_DATA06_ALT3 = 0x0 // Selecting ALT3 of pad NAND_DATA06 for UART3_RX_DATA

   NAND_DATA07_ALT3 = 0x1 // Selecting ALT3 of pad NAND_DATA07 for UART3_TX_DATA

   NAND_RE_B_ALT3 = 0x0 // Selecting ALT3 of pad NAND_RE_B for AUD4_TXFS
   NAND_RE_B_ALT4 = 0x0 // Selecting ALT4 of pad NAND_RE_B for ESAI_TX_FS

   NAND_READY_B_ALT3 = 0x0 // Selecting ALT3 of pad NAND_READY_B for ECSPI2_MISO
   NAND_READY_B_ALT4 = 0x0 // Selecting ALT4 of pad NAND_READY_B for ESAI_TX1

   NAND_WE_B_ALT3 = 0x0 // Selecting ALT3 of pad NAND_WE_B for AUD4_RXD
   NAND_WE_B_ALT4 = 0x0 // Selecting ALT4 of pad NAND_WE_B for ESAI_TX5_RX0

   NAND_WP_B_ALT3 = 0x0 // Selecting ALT3 of pad NAND_WP_B for ECSPI2_MOSI
   NAND_WP_B_ALT4 = 0x0 // Selecting ALT4 of pad NAND_WP_B for ESAI_TX4_RX1

   QSPI1A_DATA0_ALT1 = 0x2 // Selecting ALT1 of pad QSPI1A_DATA0 for USB_OTG2_OC
   QSPI1A_DATA0_ALT2 = 0x1 // Selecting ALT2 of pad QSPI1A_DATA0 for ECSPI1_MOSI
   QSPI1A_DATA0_ALT3 = 0x2 // Selecting ALT3 of pad QSPI1A_DATA0 for ESAI_TX4_RX1
   QSPI1A_DATA0_ALT4 = 0x1 // Selecting ALT4 of pad QSPI1A_DATA0 for CSI1_DATA14

   QSPI1A_DATA1_ALT1 = 0x2 // Selecting ALT1 of pad QSPI1A_DATA1 for USB_OTG1_ID
   QSPI1A_DATA1_ALT2 = 0x1 // Selecting ALT2 of pad QSPI1A_DATA1 for ECSPI1_MISO
   QSPI1A_DATA1_ALT3 = 0x2 // Selecting ALT3 of pad QSPI1A_DATA1 for ESAI_TX1
   QSPI1A_DATA1_ALT4 = 0x1 // Selecting ALT4 of pad QSPI1A_DATA1 for CSI1_DATA13

   QSPI1A_DATA2_ALT3 = 0x2 // Selecting ALT3 of pad QSPI1A_DATA2 for ESAI_TX_CLK
   QSPI1A_DATA2_ALT4 = 0x1 // Selecting ALT4 of pad QSPI1A_DATA2 for CSI1_DATA12

   QSPI1A_DATA3_ALT1 = 0x2 // Selecting ALT1 of pad QSPI1A_DATA3 for USB_OTG1_OC
   QSPI1A_DATA3_ALT3 = 0x2 // Selecting ALT3 of pad QSPI1A_DATA3 for ESAI_TX0
   QSPI1A_DATA3_ALT4 = 0x1 // Selecting ALT4 of pad QSPI1A_DATA3 for CSI1_DATA11

   QSPI1A_DQS_ALT3 = 0x1 // Selecting ALT3 of pad QSPI1A_DQS for ECSPI5_MOSI
   QSPI1A_DQS_ALT4 = 0x1 // Selecting ALT4 of pad QSPI1A_DQS for CSI1_DATA15

   QSPI1A_SCLK_ALT1 = 0x2 // Selecting ALT1 of pad QSPI1A_SCLK for USB_OTG2_ID
   QSPI1A_SCLK_ALT2 = 0x1 // Selecting ALT2 of pad QSPI1A_SCLK for ECSPI1_SCLK
   QSPI1A_SCLK_ALT3 = 0x2 // Selecting ALT3 of pad QSPI1A_SCLK for ESAI_TX2_RX3
   QSPI1A_SCLK_ALT4 = 0x1 // Selecting ALT4 of pad QSPI1A_SCLK for CSI1_DATA01

   QSPI1A_SS0_B_ALT2 = 0x1 // Selecting ALT2 of pad QSPI1A_SS0_B for ECSPI1_SS0
   QSPI1A_SS0_B_ALT3 = 0x2 // Selecting ALT3 of pad QSPI1A_SS0_B for ESAI_TX3_RX2
   QSPI1A_SS0_B_ALT4 = 0x1 // Selecting ALT4 of pad QSPI1A_SS0_B for CSI1_DATA00

   QSPI1A_SS1_B_ALT1 = 0x2 // Selecting ALT1 of pad QSPI1A_SS1_B for CAN1_RX
   QSPI1A_SS1_B_ALT3 = 0x1 // Selecting ALT3 of pad QSPI1A_SS1_B for ECSPI5_MISO
   QSPI1A_SS1_B_ALT4 = 0x1 // Selecting ALT4 of pad QSPI1A_SS1_B for CSI1_DATA10

   QSPI1B_DATA0_ALT1 = 0x4 // Selecting ALT1 of pad QSPI1B_DATA0 for UART3_CTS_B
   QSPI1B_DATA0_ALT2 = 0x1 // Selecting ALT2 of pad QSPI1B_DATA0 for ECSPI3_MOSI
   QSPI1B_DATA0_ALT3 = 0x2 // Selecting ALT3 of pad QSPI1B_DATA0 for ESAI_RX_FS
   QSPI1B_DATA0_ALT4 = 0x1 // Selecting ALT4 of pad QSPI1B_DATA0 for CSI1_DATA22

   QSPI1B_DATA1_ALT1 = 0x5 // Selecting ALT1 of pad QSPI1B_DATA1 for UART3_RTS_B
   QSPI1B_DATA1_ALT2 = 0x1 // Selecting ALT2 of pad QSPI1B_DATA1 for ECSPI3_MISO
   QSPI1B_DATA1_ALT3 = 0x2 // Selecting ALT3 of pad QSPI1B_DATA1 for ESAI_RX_CLK
   QSPI1B_DATA1_ALT4 = 0x1 // Selecting ALT4 of pad QSPI1B_DATA1 for CSI1_DATA21

   QSPI1B_DATA2_ALT1 = 0x2 // Selecting ALT1 of pad QSPI1B_DATA2 for I2C2_SDA
   QSPI1B_DATA2_ALT3 = 0x2 // Selecting ALT3 of pad QSPI1B_DATA2 for ESAI_TX5_RX0
   QSPI1B_DATA2_ALT4 = 0x1 // Selecting ALT4 of pad QSPI1B_DATA2 for CSI1_DATA20

   QSPI1B_DATA3_ALT1 = 0x2 // Selecting ALT1 of pad QSPI1B_DATA3 for I2C2_SCL
   QSPI1B_DATA3_ALT3 = 0x2 // Selecting ALT3 of pad QSPI1B_DATA3 for ESAI_TX_FS
   QSPI1B_DATA3_ALT4 = 0x1 // Selecting ALT4 of pad QSPI1B_DATA3 for CSI1_DATA19

   QSPI1B_DQS_ALT3 = 0x1 // Selecting ALT3 of pad QSPI1B_DQS for ECSPI5_SS0
   QSPI1B_DQS_ALT4 = 0x1 // Selecting ALT4 of pad QSPI1B_DQS for CSI1_DATA23

   QSPI1B_SCLK_ALT1 = 0x4 // Selecting ALT1 of pad QSPI1B_SCLK for UART3_RX_DATA
   QSPI1B_SCLK_ALT2 = 0x1 // Selecting ALT2 of pad QSPI1B_SCLK for ECSPI3_SCLK
   QSPI1B_SCLK_ALT3 = 0x2 // Selecting ALT3 of pad QSPI1B_SCLK for ESAI_RX_HF_CLK
   QSPI1B_SCLK_ALT4 = 0x1 // Selecting ALT4 of pad QSPI1B_SCLK for CSI1_DATA16

   QSPI1B_SS0_B_ALT1 = 0x5 // Selecting ALT1 of pad QSPI1B_SS0_B for UART3_TX_DATA
   QSPI1B_SS0_B_ALT2 = 0x1 // Selecting ALT2 of pad QSPI1B_SS0_B for ECSPI3_SS0
   QSPI1B_SS0_B_ALT3 = 0x3 // Selecting ALT3 of pad QSPI1B_SS0_B for ESAI_TX_HF_CLK
   QSPI1B_SS0_B_ALT4 = 0x1 // Selecting ALT4 of pad QSPI1B_SS0_B for CSI1_DATA17

   QSPI1B_SS1_B_ALT1 = 0x2 // Selecting ALT1 of pad QSPI1B_SS1_B for CAN2_RX
   QSPI1B_SS1_B_ALT3 = 0x1 // Selecting ALT3 of pad QSPI1B_SS1_B for ECSPI5_SCLK
   QSPI1B_SS1_B_ALT4 = 0x1 // Selecting ALT4 of pad QSPI1B_SS1_B for CSI1_DATA18

   RGMII1_TD0_ALT2 = 0x1 // Selecting ALT2 of pad RGMII1_TD0 for SAI2_RX_SYNC

   RGMII1_TD1_ALT2 = 0x1 // Selecting ALT2 of pad RGMII1_TD1 for SAI2_RX_BCLK

   RGMII1_TD2_ALT2 = 0x1 // Selecting ALT2 of pad RGMII1_TD2 for SAI2_TX_SYNC

   RGMII1_TD3_ALT2 = 0x1 // Selecting ALT2 of pad RGMII1_TD3 for SAI2_TX_BCLK

   RGMII1_TX_CTL_ALT2 = 0x1 // Selecting ALT2 of pad RGMII1_TX_CTL for SAI2_RX_DATA0

   RGMII2_TD0_ALT2 = 0x1 // Selecting ALT2 of pad RGMII2_TD0 for SAI1_RX_SYNC

   RGMII2_TD1_ALT2 = 0x1 // Selecting ALT2 of pad RGMII2_TD1 for SAI1_RX_BCLK

   RGMII2_TD2_ALT2 = 0x1 // Selecting ALT2 of pad RGMII2_TD2 for SAI1_TX_SYNC

   RGMII2_TD3_ALT2 = 0x1 // Selecting ALT2 of pad RGMII2_TD3 for SAI1_TX_BCLK

   RGMII2_TX_CTL_ALT2 = 0x1 // Selecting ALT2 of pad RGMII2_TX_CTL for SAI1_RX_DATA0

   SD1_CLK_ALT1 = 0x1 // Selecting ALT1 of pad SD1_CLK for AUD5_RXFS

   SD1_CMD_ALT1 = 0x1 // Selecting ALT1 of pad SD1_CMD for AUD5_RXC

   SD1_DATA0_ALT1 = 0x1 // Selecting ALT1 of pad SD1_DATA0 for AUD5_RXD
   SD1_DATA0_ALT4 = 0x2 // Selecting ALT4 of pad SD1_DATA0 for UART2_RX_DATA

   SD1_DATA1_ALT1 = 0x1 // Selecting ALT1 of pad SD1_DATA1 for AUD5_TXC
   SD1_DATA1_ALT4 = 0x3 // Selecting ALT4 of pad SD1_DATA1 for UART2_TX_DATA

   SD1_DATA2_ALT1 = 0x1 // Selecting ALT1 of pad SD1_DATA2 for AUD5_TXFS
   SD1_DATA2_ALT4 = 0x2 // Selecting ALT4 of pad SD1_DATA2 for UART2_CTS_B

   SD1_DATA3_ALT1 = 0x1 // Selecting ALT1 of pad SD1_DATA3 for AUD5_TXD
   SD1_DATA3_ALT2 = 0x2 // Selecting ALT2 of pad SD1_DATA3 for AUD5_RXD
   SD1_DATA3_ALT4 = 0x3 // Selecting ALT4 of pad SD1_DATA3 for UART2_RTS_B
   SD1_DATA3_ALT7 = 0x2 // Selecting ALT7 of pad SD1_DATA3 for CCM_PMIC_READY

   SD2_CLK_ALT1 = 0x2 // Selecting ALT1 of pad SD2_CLK for AUD6_RXFS
   SD2_CLK_ALT2 = 0x1 // Selecting ALT2 of pad SD2_CLK for KPP_COL5
   SD2_CLK_ALT3 = 0x1 // Selecting ALT3 of pad SD2_CLK for ECSPI4_SCLK
   SD2_CLK_ALT4 = 0x2 // Selecting ALT4 of pad SD2_CLK for MLB_SIG

   SD2_CMD_ALT1 = 0x2 // Selecting ALT1 of pad SD2_CMD for AUD6_RXC
   SD2_CMD_ALT2 = 0x1 // Selecting ALT2 of pad SD2_CMD for KPP_ROW5
   SD2_CMD_ALT3 = 0x1 // Selecting ALT3 of pad SD2_CMD for ECSPI4_MOSI
   SD2_CMD_ALT4 = 0x2 // Selecting ALT4 of pad SD2_CMD for MLB_CLK

   SD2_DATA0_ALT1 = 0x2 // Selecting ALT1 of pad SD2_DATA0 for AUD6_RXD
   SD2_DATA0_ALT2 = 0x1 // Selecting ALT2 of pad SD2_DATA0 for KPP_ROW7
   SD2_DATA0_ALT4 = 0x3 // Selecting ALT4 of pad SD2_DATA0 for I2C4_SDA
   SD2_DATA0_ALT7 = 0x4 // Selecting ALT7 of pad SD2_DATA0 for UART4_RX_DATA

   SD2_DATA1_ALT1 = 0x2 // Selecting ALT1 of pad SD2_DATA1 for AUD6_TXC
   SD2_DATA1_ALT2 = 0x1 // Selecting ALT2 of pad SD2_DATA1 for KPP_COL7
   SD2_DATA1_ALT4 = 0x3 // Selecting ALT4 of pad SD2_DATA1 for I2C4_SCL
   SD2_DATA1_ALT7 = 0x5 // Selecting ALT7 of pad SD2_DATA1 for UART4_TX_DATA

   SD2_DATA2_ALT1 = 0x2 // Selecting ALT1 of pad SD2_DATA2 for AUD6_TXFS
   SD2_DATA2_ALT2 = 0x1 // Selecting ALT2 of pad SD2_DATA2 for KPP_ROW6
   SD2_DATA2_ALT3 = 0x1 // Selecting ALT3 of pad SD2_DATA2 for ECSPI4_SS0
   SD2_DATA2_ALT4 = 0x2 // Selecting ALT4 of pad SD2_DATA2 for SDMA_EXT_EVENT0
   SD2_DATA2_ALT7 = 0x4 // Selecting ALT7 of pad SD2_DATA2 for UART6_RX_DATA

   SD2_DATA3_ALT1 = 0x2 // Selecting ALT1 of pad SD2_DATA3 for AUD6_TXD
   SD2_DATA3_ALT2 = 0x1 // Selecting ALT2 of pad SD2_DATA3 for KPP_COL6
   SD2_DATA3_ALT3 = 0x1 // Selecting ALT3 of pad SD2_DATA3 for ECSPI4_MISO
   SD2_DATA3_ALT4 = 0x2 // Selecting ALT4 of pad SD2_DATA3 for MLB_DATA
   SD2_DATA3_ALT6 = 0x4 // Selecting ALT6 of pad SD2_DATA3 for SPDIF_IN
   SD2_DATA3_ALT7 = 0x5 // Selecting ALT7 of pad SD2_DATA3 for UART6_TX_DATA

   SD4_CLK_ALT2 = 0x1 // Selecting ALT2 of pad SD4_CLK for ECSPI2_MISO
   SD4_CLK_ALT3 = 0x0 // Selecting ALT3 of pad SD4_CLK for AUD3_RXFS

   SD4_CMD_ALT2 = 0x1 // Selecting ALT2 of pad SD4_CMD for ECSPI2_MOSI
   SD4_CMD_ALT3 = 0x0 // Selecting ALT3 of pad SD4_CMD for AUD3_RXC

   SD4_DATA0_ALT2 = 0x1 // Selecting ALT2 of pad SD4_DATA0 for ECSPI2_SS0
   SD4_DATA0_ALT3 = 0x0 // Selecting ALT3 of pad SD4_DATA0 for AUD3_RXD

   SD4_DATA1_ALT2 = 0x1 // Selecting ALT2 of pad SD4_DATA1 for ECSPI2_SCLK
   SD4_DATA1_ALT3 = 0x0 // Selecting ALT3 of pad SD4_DATA1 for AUD3_TXC

   SD4_DATA2_ALT2 = 0x0 // Selecting ALT2 of pad SD4_DATA2 for I2C2_SDA
   SD4_DATA2_ALT3 = 0x0 // Selecting ALT3 of pad SD4_DATA2 for AUD3_TXFS

   SD4_DATA3_ALT2 = 0x0 // Selecting ALT2 of pad SD4_DATA3 for I2C2_SCL
   SD4_DATA3_ALT3 = 0x0 // Selecting ALT3 of pad SD4_DATA3 for AUD3_TXD

   SD4_DATA4_ALT2 = 0x0 // Selecting ALT2 of pad SD4_DATA4 for UART5_RX_DATA
   SD4_DATA4_ALT3 = 0x0 // Selecting ALT3 of pad SD4_DATA4 for ECSPI3_SCLK

   SD4_DATA5_ALT2 = 0x1 // Selecting ALT2 of pad SD4_DATA5 for UART5_TX_DATA
   SD4_DATA5_ALT3 = 0x0 // Selecting ALT3 of pad SD4_DATA5 for ECSPI3_MOSI
   SD4_DATA5_ALT6 = 0x0 // Selecting ALT6 of pad SD4_DATA5 for SPDIF_IN

   SD4_DATA6_ALT2 = 0x0 // Selecting ALT2 of pad SD4_DATA6 for UART5_RTS_B
   SD4_DATA6_ALT3 = 0x0 // Selecting ALT3 of pad SD4_DATA6 for ECSPI3_MISO
   SD4_DATA6_ALT6 = 0x0 // Selecting ALT6 of pad SD4_DATA6 for SD4_WP

   SD4_DATA7_ALT2 = 0x1 // Selecting ALT2 of pad SD4_DATA7 for UART5_CTS_B
   SD4_DATA7_ALT3 = 0x0 // Selecting ALT3 of pad SD4_DATA7 for ECSPI3_SS0
   SD4_DATA7_ALT6 = 0x0 // Selecting ALT6 of pad SD4_DATA7 for SD4_CD_B

   SD3_CLK_ALT1 = 0x0 // Selecting ALT1 of pad SD3_CLK for UART4_CTS_B
   SD3_CLK_ALT2 = 0x0 // Selecting ALT2 of pad SD3_CLK for ECSPI4_SCLK
   SD3_CLK_ALT3 = 0x0 // Selecting ALT3 of pad SD3_CLK for AUD6_RXFS
   SD3_CLK_ALT6 = 0x0 // Selecting ALT6 of pad SD3_CLK for LCD2_BUSY

   SD3_CMD_ALT1 = 0x0 // Selecting ALT1 of pad SD3_CMD for UART4_TX_DATA
   SD3_CMD_ALT2 = 0x0 // Selecting ALT2 of pad SD3_CMD for ECSPI4_MOSI
   SD3_CMD_ALT3 = 0x0 // Selecting ALT3 of pad SD3_CMD for AUD6_RXC
   SD3_CMD_ALT4 = 0x1 // Selecting ALT4 of pad SD3_CMD for LCD2_HSYNC

   SD3_DATA0_ALT1 = 0x0 // Selecting ALT1 of pad SD3_DATA0 for I2C4_SCL
   SD3_DATA0_ALT3 = 0x0 // Selecting ALT3 of pad SD3_DATA0 for AUD6_RXD

   SD3_DATA1_ALT1 = 0x0 // Selecting ALT1 of pad SD3_DATA1 for I2C4_SDA
   SD3_DATA1_ALT3 = 0x0 // Selecting ALT3 of pad SD3_DATA1 for AUD6_TXC

   SD3_DATA2_ALT1 = 0x1 // Selecting ALT1 of pad SD3_DATA2 for UART4_RTS_B
   SD3_DATA2_ALT2 = 0x0 // Selecting ALT2 of pad SD3_DATA2 for ECSPI4_SS0
   SD3_DATA2_ALT3 = 0x0 // Selecting ALT3 of pad SD3_DATA2 for AUD6_TXFS

   SD3_DATA3_ALT1 = 0x1 // Selecting ALT1 of pad SD3_DATA3 for UART4_RX_DATA
   SD3_DATA3_ALT2 = 0x0 // Selecting ALT2 of pad SD3_DATA3 for ECSPI4_MISO
   SD3_DATA3_ALT3 = 0x0 // Selecting ALT3 of pad SD3_DATA3 for AUD6_TXD

   SD3_DATA4_ALT1 = 0x0 // Selecting ALT1 of pad SD3_DATA4 for CAN2_RX
   SD3_DATA4_ALT3 = 0x2 // Selecting ALT3 of pad SD3_DATA4 for UART3_RX_DATA

   SD3_DATA5_ALT3 = 0x3 // Selecting ALT3 of pad SD3_DATA5 for UART3_TX_DATA

   SD3_DATA6_ALT3 = 0x2 // Selecting ALT3 of pad SD3_DATA6 for UART3_RTS_B

   SD3_DATA7_ALT1 = 0x0 // Selecting ALT1 of pad SD3_DATA7 for CAN1_RX
   SD3_DATA7_ALT3 = 0x3 // Selecting ALT3 of pad SD3_DATA7 for UART3_CTS_B

   USB_H_DATA_ALT3 = 0x1 // Selecting ALT3 of pad USB_H_DATA for I2C4_SDA

   USB_H_STROBE_ALT3 = 0x1 // Selecting ALT3 of pad USB_H_STROBE for I2C4_SCL
*/

//
// IMX_PAD register defines.
//
typedef enum {
   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO00)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO00)
   IMX_PAD_GPIO1_IO00 = _IMX_PAD(0x35C, 0x14), // I2C1_SCL

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO01)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO01)
   IMX_PAD_GPIO1_IO01 = _IMX_PAD(0x360, 0x18), // I2C1_SDA

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO02)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO02)
   IMX_PAD_GPIO1_IO02 = _IMX_PAD(0x364, 0x1C), // I2C2_SCL

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO03)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO03)
   IMX_PAD_GPIO1_IO03 = _IMX_PAD(0x368, 0x20), // I2C2_SDA

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO04)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO04)
   IMX_PAD_GPIO1_IO04 = _IMX_PAD(0x36C, 0x24), // UART1_TX_DATA

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO05)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO05)
   IMX_PAD_GPIO1_IO05 = _IMX_PAD(0x370, 0x28), // UART1_RX_DATA

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO06)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO06)
   IMX_PAD_GPIO1_IO06 = _IMX_PAD(0x374, 0x2C), // UART2_TX_DATA

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO07)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO07)
   IMX_PAD_GPIO1_IO07 = _IMX_PAD(0x378, 0x30), // UART2_RX_DATA

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO08)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO08)
   IMX_PAD_GPIO1_IO08 = _IMX_PAD(0x37C, 0x34), // USB_OTG1_OC

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO09)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO09)
   IMX_PAD_GPIO1_IO09 = _IMX_PAD(0x380, 0x38), // USB_OTG1_PWR

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO10)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO10)
   IMX_PAD_GPIO1_IO10 = _IMX_PAD(0x384, 0x3C), // USB_OTG1_ID

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO11)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO11)
   IMX_PAD_GPIO1_IO11 = _IMX_PAD(0x388, 0x40), // USB_OTG2_OC

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO12)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO12)
   IMX_PAD_GPIO1_IO12 = _IMX_PAD(0x38C, 0x44), // USB_OTG2_PWR

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_GPIO1_IO13)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_GPIO1_IO13)
   IMX_PAD_GPIO1_IO13 = _IMX_PAD(0x390, 0x48), // WDOG1_ANY

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI_DATA00)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI_DATA00)
   IMX_PAD_CSI_DATA00 = _IMX_PAD(0x394, 0x4C), // CSI1_DATA02

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI_DATA01)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI_DATA01)
   IMX_PAD_CSI_DATA01 = _IMX_PAD(0x398, 0x50), // CSI1_DATA03

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI_DATA02)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI_DATA02)
   IMX_PAD_CSI_DATA02 = _IMX_PAD(0x39C, 0x54), // CSI1_DATA04

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI_DATA03)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI_DATA03)
   IMX_PAD_CSI_DATA03 = _IMX_PAD(0x3A0, 0x58), // CSI1_DATA05

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI_DATA04)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI_DATA04)
   IMX_PAD_CSI_DATA04 = _IMX_PAD(0x3A4, 0x5C), // CSI1_DATA06

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI_DATA05)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI_DATA05)
   IMX_PAD_CSI_DATA05 = _IMX_PAD(0x3A8, 0x60), // CSI1_DATA07

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI_DATA06)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI_DATA06)
   IMX_PAD_CSI_DATA06 = _IMX_PAD(0x3AC, 0x64), // CSI1_DATA08

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI_DATA07)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI_DATA07)
   IMX_PAD_CSI_DATA07 = _IMX_PAD(0x3B0, 0x68), // CSI1_DATA09

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI_HSYNC)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI_HSYNC)
   IMX_PAD_CSI_HSYNC = _IMX_PAD(0x3B4, 0x6C), // CSI1_HSYNC

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI_MCLK)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI_MCLK)
   IMX_PAD_CSI_MCLK = _IMX_PAD(0x3B8, 0x70), // CSI1_MCLK

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI_PIXCLK)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI_PIXCLK)
   IMX_PAD_CSI_PIXCLK = _IMX_PAD(0x3BC, 0x74), // CSI1_PIXCLK

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_CSI_VSYNC)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_CSI_VSYNC)
   IMX_PAD_CSI_VSYNC = _IMX_PAD(0x3C0, 0x78), // CSI1_VSYNC

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_ENET1_COL)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_ENET1_COL)
   IMX_PAD_ENET1_COL = _IMX_PAD(0x3C4, 0x7C), // ENET1_COL

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_ENET1_CRS)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_ENET1_CRS)
   IMX_PAD_ENET1_CRS = _IMX_PAD(0x3C8, 0x80), // ENET1_CRS

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_ENET1_MDC)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_ENET1_MDC)
   IMX_PAD_ENET1_MDC = _IMX_PAD(0x3CC, 0x84), // ENET1_MDC

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_ENET1_MDIO)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_ENET1_MDIO)
   IMX_PAD_ENET1_MDIO = _IMX_PAD(0x3D0, 0x88), // ENET1_MDIO

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_ENET1_RX_CLK)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_ENET1_RX_CLK)
   IMX_PAD_ENET1_RX_CLK = _IMX_PAD(0x3D4, 0x8C), // ENET1_RX_CLK

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_ENET1_TX_CLK)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_ENET1_TX_CLK)
   IMX_PAD_ENET1_TX_CLK = _IMX_PAD(0x3D8, 0x90), // ENET1_TX_CLK

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_ENET2_COL)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_ENET2_COL)
   IMX_PAD_ENET2_COL = _IMX_PAD(0x3DC, 0x94), // ENET2_COL

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_ENET2_CRS)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_ENET2_CRS)
   IMX_PAD_ENET2_CRS = _IMX_PAD(0x3E0, 0x98), // ENET2_CRS

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_ENET2_RX_CLK)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_ENET2_RX_CLK)
   IMX_PAD_ENET2_RX_CLK = _IMX_PAD(0x3E4, 0x9C), // ENET2_RX_CLK

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_ENET2_TX_CLK)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_ENET2_TX_CLK)
   IMX_PAD_ENET2_TX_CLK = _IMX_PAD(0x3E8, 0xA0), // ENET2_TX_CLK

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_KEY_COL0)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_KEY_COL0)
   IMX_PAD_KEY_COL0 = _IMX_PAD(0x3EC, 0xA4), // KPP_COL0

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_KEY_COL1)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_KEY_COL1)
   IMX_PAD_KEY_COL1 = _IMX_PAD(0x3F0, 0xA8), // KPP_COL1

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_KEY_COL2)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_KEY_COL2)
   IMX_PAD_KEY_COL2 = _IMX_PAD(0x3F4, 0xAC), // KPP_COL2

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_KEY_COL3)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_KEY_COL3)
   IMX_PAD_KEY_COL3 = _IMX_PAD(0x3F8, 0xB0), // KPP_COL3

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_KEY_COL4)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_KEY_COL4)
   IMX_PAD_KEY_COL4 = _IMX_PAD(0x3FC, 0xB4), // KPP_COL4

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_KEY_ROW0)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_KEY_ROW0)
   IMX_PAD_KEY_ROW0 = _IMX_PAD(0x400, 0xB8), // KPP_ROW0

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_KEY_ROW1)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_KEY_ROW1)
   IMX_PAD_KEY_ROW1 = _IMX_PAD(0x404, 0xBC), // KPP_ROW1

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_KEY_ROW2)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_KEY_ROW2)
   IMX_PAD_KEY_ROW2 = _IMX_PAD(0x408, 0xC0), // KPP_ROW2

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_KEY_ROW3)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_KEY_ROW3)
   IMX_PAD_KEY_ROW3 = _IMX_PAD(0x40C, 0xC4), // KPP_ROW3

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_KEY_ROW4)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_KEY_ROW4)
   IMX_PAD_KEY_ROW4 = _IMX_PAD(0x410, 0xC8), // KPP_ROW4

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_LCD1_CLK)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_LCD1_CLK)
   IMX_PAD_LCD1_CLK = _IMX_PAD(0x414, 0xCC), // LCD1_CLK

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA00)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_LCD1_DATA00)
   IMX_PAD_LCD1_DATA00 = _IMX_PAD(0x418, 0xD0), // LCD1_DATA00

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA01)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_LCD1_DATA01)
   IMX_PAD_LCD1_DATA01 = _IMX_PAD(0x41C, 0xD4), // LCD1_DATA01

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA02)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_LCD1_DATA02)
   IMX_PAD_LCD1_DATA02 = _IMX_PAD(0x420, 0xD8), // LCD1_DATA02

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA03)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_LCD1_DATA03)
   IMX_PAD_LCD1_DATA03 = _IMX_PAD(0x424, 0xDC), // LCD1_DATA03

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA04)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_LCD1_DATA04)
   IMX_PAD_LCD1_DATA04 = _IMX_PAD(0x428, 0xE0), // LCD1_DATA04

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA05)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_LCD1_DATA05)
   IMX_PAD_LCD1_DATA05 = _IMX_PAD(0x42C, 0xE4), // LCD1_DATA05

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA06)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_LCD1_DATA06)
   IMX_PAD_LCD1_DATA06 = _IMX_PAD(0x430, 0xE8), // LCD1_DATA06

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA07)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_LCD1_DATA07)
   IMX_PAD_LCD1_DATA07 = _IMX_PAD(0x434, 0xEC), // LCD1_DATA07

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA08)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_LCD1_DATA08)
   IMX_PAD_LCD1_DATA08 = _IMX_PAD(0x438, 0xF0), // LCD1_DATA08

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA09)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_LCD1_DATA09)
   IMX_PAD_LCD1_DATA09 = _IMX_PAD(0x43C, 0xF4), // LCD1_DATA09

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA10)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_LCD1_DATA10)
   IMX_PAD_LCD1_DATA10 = _IMX_PAD(0x440, 0xF8), // LCD1_DATA10

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA11)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_LCD1_DATA11)
   IMX_PAD_LCD1_DATA11 = _IMX_PAD(0x444, 0xFC), // LCD1_DATA11

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA12)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_LCD1_DATA12)
   IMX_PAD_LCD1_DATA12 = _IMX_PAD(0x448, 0x100), // LCD1_DATA12

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA13)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_LCD1_DATA13)
   IMX_PAD_LCD1_DATA13 = _IMX_PAD(0x44C, 0x104), // LCD1_DATA13

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA14)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_LCD1_DATA14)
   IMX_PAD_LCD1_DATA14 = _IMX_PAD(0x450, 0x108), // LCD1_DATA14

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA15)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_LCD1_DATA15)
   IMX_PAD_LCD1_DATA15 = _IMX_PAD(0x454, 0x10C), // LCD1_DATA15

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA16)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_LCD1_DATA16)
   IMX_PAD_LCD1_DATA16 = _IMX_PAD(0x458, 0x110), // LCD1_DATA16

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA17)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_LCD1_DATA17)
   IMX_PAD_LCD1_DATA17 = _IMX_PAD(0x45C, 0x114), // LCD1_DATA17

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA18)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_LCD1_DATA18)
   IMX_PAD_LCD1_DATA18 = _IMX_PAD(0x460, 0x118), // LCD1_DATA18

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA19)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_LCD1_DATA19)
   IMX_PAD_LCD1_DATA19 = _IMX_PAD(0x464, 0x11C), // LCD1_DATA19

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA20)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_LCD1_DATA20)
   IMX_PAD_LCD1_DATA20 = _IMX_PAD(0x468, 0x120), // LCD1_DATA20

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA21)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_LCD1_DATA21)
   IMX_PAD_LCD1_DATA21 = _IMX_PAD(0x46C, 0x124), // LCD1_DATA21

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA22)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_LCD1_DATA22)
   IMX_PAD_LCD1_DATA22 = _IMX_PAD(0x470, 0x128), // LCD1_DATA22

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_LCD1_DATA23)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_LCD1_DATA23)
   IMX_PAD_LCD1_DATA23 = _IMX_PAD(0x474, 0x12C), // LCD1_DATA23

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_LCD1_ENABLE)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_LCD1_ENABLE)
   IMX_PAD_LCD1_ENABLE = _IMX_PAD(0x478, 0x130), // LCD1_ENABLE

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_LCD1_HSYNC)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_LCD1_HSYNC)
   IMX_PAD_LCD1_HSYNC = _IMX_PAD(0x47C, 0x134), // LCD1_HSYNC

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_LCD1_RESET)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_LCD1_RESET)
   IMX_PAD_LCD1_RESET = _IMX_PAD(0x480, 0x138), // LCD1_RESET

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_LCD1_VSYNC)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_LCD1_VSYNC)
   IMX_PAD_LCD1_VSYNC = _IMX_PAD(0x484, 0x13C), // LCD1_VSYNC

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_ALE)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_ALE)
   IMX_PAD_NAND_ALE = _IMX_PAD(0x488, 0x140), // NAND_ALE

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_CE0_B)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_CE0_B)
   IMX_PAD_NAND_CE0_B = _IMX_PAD(0x48C, 0x144), // NAND_CE0_B

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_CE1_B)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_CE1_B)
   IMX_PAD_NAND_CE1_B = _IMX_PAD(0x490, 0x148), // NAND_CE1_B

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_CLE)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_CLE)
   IMX_PAD_NAND_CLE = _IMX_PAD(0x494, 0x14C), // NAND_CLE

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_DATA00)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_DATA00)
   IMX_PAD_NAND_DATA00 = _IMX_PAD(0x498, 0x150), // NAND_DATA00

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_DATA01)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_DATA01)
   IMX_PAD_NAND_DATA01 = _IMX_PAD(0x49C, 0x154), // NAND_DATA01

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_DATA02)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_DATA02)
   IMX_PAD_NAND_DATA02 = _IMX_PAD(0x4A0, 0x158), // NAND_DATA02

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_DATA03)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_DATA03)
   IMX_PAD_NAND_DATA03 = _IMX_PAD(0x4A4, 0x15C), // NAND_DATA03

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_DATA04)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_DATA04)
   IMX_PAD_NAND_DATA04 = _IMX_PAD(0x4A8, 0x160), // NAND_DATA04

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_DATA05)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_DATA05)
   IMX_PAD_NAND_DATA05 = _IMX_PAD(0x4AC, 0x164), // NAND_DATA05

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_DATA06)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_DATA06)
   IMX_PAD_NAND_DATA06 = _IMX_PAD(0x4B0, 0x168), // NAND_DATA06

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_DATA07)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_DATA07)
   IMX_PAD_NAND_DATA07 = _IMX_PAD(0x4B4, 0x16C), // NAND_DATA07

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_RE_B)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_RE_B)
   IMX_PAD_NAND_RE_B = _IMX_PAD(0x4B8, 0x170), // NAND_RE_B

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_READY_B)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_READY_B)
   IMX_PAD_NAND_READY_B = _IMX_PAD(0x4BC, 0x174), // NAND_READY_B

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_WE_B)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_WE_B)
   IMX_PAD_NAND_WE_B = _IMX_PAD(0x4C0, 0x178), // NAND_WE_B

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_NAND_WP_B)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_NAND_WP_B)
   IMX_PAD_NAND_WP_B = _IMX_PAD(0x4C4, 0x17C), // NAND_WP_B

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_QSPI1A_DATA0)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_QSPI1A_DATA0)
   IMX_PAD_QSPI1A_DATA0 = _IMX_PAD(0x4C8, 0x180), // QSPI1A_DATA0

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_QSPI1A_DATA1)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_QSPI1A_DATA1)
   IMX_PAD_QSPI1A_DATA1 = _IMX_PAD(0x4CC, 0x184), // QSPI1A_DATA1

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_QSPI1A_DATA2)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_QSPI1A_DATA2)
   IMX_PAD_QSPI1A_DATA2 = _IMX_PAD(0x4D0, 0x188), // QSPI1A_DATA2

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_QSPI1A_DATA3)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_QSPI1A_DATA3)
   IMX_PAD_QSPI1A_DATA3 = _IMX_PAD(0x4D4, 0x18C), // QSPI1A_DATA3

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_QSPI1A_DQS)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_QSPI1A_DQS)
   IMX_PAD_QSPI1A_DQS = _IMX_PAD(0x4D8, 0x190), // QSPI1A_DQS

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_QSPI1A_SCLK)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_QSPI1A_SCLK)
   IMX_PAD_QSPI1A_SCLK = _IMX_PAD(0x4DC, 0x194), // QSPI1A_SCLK

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_QSPI1A_SS0_B)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_QSPI1A_SS0_B)
   IMX_PAD_QSPI1A_SS0_B = _IMX_PAD(0x4E0, 0x198), // QSPI1A_SS0_B

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_QSPI1A_SS1_B)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_QSPI1A_SS1_B)
   IMX_PAD_QSPI1A_SS1_B = _IMX_PAD(0x4E4, 0x19C), // QSPI1A_SS1_B

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_QSPI1B_DATA0)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_QSPI1B_DATA0)
   IMX_PAD_QSPI1B_DATA0 = _IMX_PAD(0x4E8, 0x1A0), // QSPI1B_DATA0

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_QSPI1B_DATA1)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_QSPI1B_DATA1)
   IMX_PAD_QSPI1B_DATA1 = _IMX_PAD(0x4EC, 0x1A4), // QSPI1B_DATA1

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_QSPI1B_DATA2)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_QSPI1B_DATA2)
   IMX_PAD_QSPI1B_DATA2 = _IMX_PAD(0x4F0, 0x1A8), // QSPI1B_DATA2

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_QSPI1B_DATA3)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_QSPI1B_DATA3)
   IMX_PAD_QSPI1B_DATA3 = _IMX_PAD(0x4F4, 0x1AC), // QSPI1B_DATA3

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_QSPI1B_DQS)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_QSPI1B_DQS)
   IMX_PAD_QSPI1B_DQS = _IMX_PAD(0x4F8, 0x1B0), // QSPI1B_DQS

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_QSPI1B_SCLK)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_QSPI1B_SCLK)
   IMX_PAD_QSPI1B_SCLK = _IMX_PAD(0x4FC, 0x1B4), // QSPI1B_SCLK

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_QSPI1B_SS0_B)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_QSPI1B_SS0_B)
   IMX_PAD_QSPI1B_SS0_B = _IMX_PAD(0x500, 0x1B8), // QSPI1B_SS0_B

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_QSPI1B_SS1_B)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_QSPI1B_SS1_B)
   IMX_PAD_QSPI1B_SS1_B = _IMX_PAD(0x504, 0x1BC), // QSPI1B_SS1_B

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII1_RD0)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII1_RD0)
   IMX_PAD_RGMII1_RD0 = _IMX_PAD(0x508, 0x1C0), // ENET1_RX_DATA0

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII1_RD1)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII1_RD1)
   IMX_PAD_RGMII1_RD1 = _IMX_PAD(0x50C, 0x1C4), // ENET1_RX_DATA1

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII1_RD2)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII1_RD2)
   IMX_PAD_RGMII1_RD2 = _IMX_PAD(0x510, 0x1C8), // ENET1_RX_DATA2

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII1_RD3)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII1_RD3)
   IMX_PAD_RGMII1_RD3 = _IMX_PAD(0x514, 0x1CC), // ENET1_RX_DATA3

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII1_RX_CTL)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII1_RX_CTL)
   IMX_PAD_RGMII1_RX_CTL = _IMX_PAD(0x518, 0x1D0), // ENET1_RX_EN

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII1_RXC)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII1_RXC)
   IMX_PAD_RGMII1_RXC = _IMX_PAD(0x51C, 0x1D4), // ENET1_RGMII_RXC

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII1_TD0)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII1_TD0)
   IMX_PAD_RGMII1_TD0 = _IMX_PAD(0x520, 0x1D8), // ENET1_TX_DATA0

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII1_TD1)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII1_TD1)
   IMX_PAD_RGMII1_TD1 = _IMX_PAD(0x524, 0x1DC), // ENET1_TX_DATA1

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII1_TD2)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII1_TD2)
   IMX_PAD_RGMII1_TD2 = _IMX_PAD(0x528, 0x1E0), // ENET1_TX_DATA2

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII1_TD3)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII1_TD3)
   IMX_PAD_RGMII1_TD3 = _IMX_PAD(0x52C, 0x1E4), // ENET1_TX_DATA3

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII1_TX_CTL)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII1_TX_CTL)
   IMX_PAD_RGMII1_TX_CTL = _IMX_PAD(0x530, 0x1E8), // ENET1_TX_EN

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII1_TXC)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII1_TXC)
   IMX_PAD_RGMII1_TXC = _IMX_PAD(0x534, 0x1EC), // ENET1_RGMII_TXC

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII2_RD0)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII2_RD0)
   IMX_PAD_RGMII2_RD0 = _IMX_PAD(0x538, 0x1F0), // ENET2_RX_DATA0

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII2_RD1)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII2_RD1)
   IMX_PAD_RGMII2_RD1 = _IMX_PAD(0x53C, 0x1F4), // ENET2_RX_DATA1

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII2_RD2)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII2_RD2)
   IMX_PAD_RGMII2_RD2 = _IMX_PAD(0x540, 0x1F8), // ENET2_RX_DATA2

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII2_RD3)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII2_RD3)
   IMX_PAD_RGMII2_RD3 = _IMX_PAD(0x544, 0x1FC), // ENET2_RX_DATA3

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII2_RX_CTL)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII2_RX_CTL)
   IMX_PAD_RGMII2_RX_CTL = _IMX_PAD(0x548, 0x200), // ENET2_RX_EN

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII2_RXC)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII2_RXC)
   IMX_PAD_RGMII2_RXC = _IMX_PAD(0x54C, 0x204), // ENET2_RGMII_RXC

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII2_TD0)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII2_TD0)
   IMX_PAD_RGMII2_TD0 = _IMX_PAD(0x550, 0x208), // ENET2_TX_DATA0

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII2_TD1)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII2_TD1)
   IMX_PAD_RGMII2_TD1 = _IMX_PAD(0x554, 0x20C), // ENET2_TX_DATA1

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII2_TD2)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII2_TD2)
   IMX_PAD_RGMII2_TD2 = _IMX_PAD(0x558, 0x210), // ENET2_TX_DATA2

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII2_TD3)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII2_TD3)
   IMX_PAD_RGMII2_TD3 = _IMX_PAD(0x55C, 0x214), // ENET2_TX_DATA3

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII2_TX_CTL)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII2_TX_CTL)
   IMX_PAD_RGMII2_TX_CTL = _IMX_PAD(0x560, 0x218), // ENET2_TX_EN

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_RGMII2_TXC)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_RGMII2_TXC)
   IMX_PAD_RGMII2_TXC = _IMX_PAD(0x564, 0x21C), // ENET2_RGMII_TXC

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD1_CLK)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD1_CLK)
   IMX_PAD_SD1_CLK = _IMX_PAD(0x568, 0x220), // SD1_CLK

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD1_CMD)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD1_CMD)
   IMX_PAD_SD1_CMD = _IMX_PAD(0x56C, 0x224), // SD1_CMD

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD1_DATA0)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD1_DATA0)
   IMX_PAD_SD1_DATA0 = _IMX_PAD(0x570, 0x228), // SD1_DATA0

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD1_DATA1)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD1_DATA1)
   IMX_PAD_SD1_DATA1 = _IMX_PAD(0x574, 0x22C), // SD1_DATA1

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD1_DATA2)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD1_DATA2)
   IMX_PAD_SD1_DATA2 = _IMX_PAD(0x578, 0x230), // SD1_DATA2

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD1_DATA3)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD1_DATA3)
   IMX_PAD_SD1_DATA3 = _IMX_PAD(0x57C, 0x234), // SD1_DATA3

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD2_CLK)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD2_CLK)
   IMX_PAD_SD2_CLK = _IMX_PAD(0x580, 0x238), // SD2_CLK

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD2_CMD)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD2_CMD)
   IMX_PAD_SD2_CMD = _IMX_PAD(0x584, 0x23C), // SD2_CMD

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD2_DATA0)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD2_DATA0)
   IMX_PAD_SD2_DATA0 = _IMX_PAD(0x588, 0x240), // SD2_DATA0

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD2_DATA1)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD2_DATA1)
   IMX_PAD_SD2_DATA1 = _IMX_PAD(0x58C, 0x244), // SD2_DATA1

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD2_DATA2)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD2_DATA2)
   IMX_PAD_SD2_DATA2 = _IMX_PAD(0x590, 0x248), // SD2_DATA2

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD2_DATA3)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD2_DATA3)
   IMX_PAD_SD2_DATA3 = _IMX_PAD(0x594, 0x24C), // SD2_DATA3

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD4_CLK)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD4_CLK)
   IMX_PAD_SD4_CLK = _IMX_PAD(0x5C0, 0x278), // SD4_CLK

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD4_CMD)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD4_CMD)
   IMX_PAD_SD4_CMD = _IMX_PAD(0x5C4, 0x27C), // SD4_CMD

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD4_DATA0)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD4_DATA0)
   IMX_PAD_SD4_DATA0 = _IMX_PAD(0x5C8, 0x280), // SD4_DATA0

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD4_DATA1)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD4_DATA1)
   IMX_PAD_SD4_DATA1 = _IMX_PAD(0x5CC, 0x284), // SD4_DATA1

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD4_DATA2)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD4_DATA2)
   IMX_PAD_SD4_DATA2 = _IMX_PAD(0x5D0, 0x288), // SD4_DATA2

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD4_DATA3)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD4_DATA3)
   IMX_PAD_SD4_DATA3 = _IMX_PAD(0x5D4, 0x28C), // SD4_DATA3

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD4_DATA4)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD4_DATA4)
   IMX_PAD_SD4_DATA4 = _IMX_PAD(0x5D8, 0x290), // SD4_DATA4

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD4_DATA5)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD4_DATA5)
   IMX_PAD_SD4_DATA5 = _IMX_PAD(0x5DC, 0x294), // SD4_DATA5

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD4_DATA6)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD4_DATA6)
   IMX_PAD_SD4_DATA6 = _IMX_PAD(0x5E0, 0x298), // SD4_DATA6

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD4_DATA7)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD4_DATA7)
   IMX_PAD_SD4_DATA7 = _IMX_PAD(0x5E4, 0x29C), // SD4_DATA7

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD4_RESET_B)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD4_RESET_B)
   IMX_PAD_SD4_RESET_B = _IMX_PAD(0x5E8, 0x2A0), // SD4_RESET_B

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD3_CLK)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD3_CLK)
   IMX_PAD_SD3_CLK = _IMX_PAD(0x598, 0x250), // SD3_CLK

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD3_CMD)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD3_CMD)
   IMX_PAD_SD3_CMD = _IMX_PAD(0x59C, 0x254), // SD3_CMD

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD3_DATA0)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD3_DATA0)
   IMX_PAD_SD3_DATA0 = _IMX_PAD(0x5A0, 0x258), // SD3_DATA0

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD3_DATA1)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD3_DATA1)
   IMX_PAD_SD3_DATA1 = _IMX_PAD(0x5A4, 0x25C), // SD3_DATA1

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD3_DATA2)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD3_DATA2)
   IMX_PAD_SD3_DATA2 = _IMX_PAD(0x5A8, 0x260), // SD3_DATA2

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD3_DATA3)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD3_DATA3)
   IMX_PAD_SD3_DATA3 = _IMX_PAD(0x5AC, 0x264), // SD3_DATA3

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD3_DATA4)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD3_DATA4)
   IMX_PAD_SD3_DATA4 = _IMX_PAD(0x5B0, 0x268), // SD3_DATA4

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD3_DATA5)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD3_DATA5)
   IMX_PAD_SD3_DATA5 = _IMX_PAD(0x5B4, 0x26C), // SD3_DATA5

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD3_DATA6)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD3_DATA6)
   IMX_PAD_SD3_DATA6 = _IMX_PAD(0x5B8, 0x270), // SD3_DATA6

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_SD3_DATA7)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_SD3_DATA7)
   IMX_PAD_SD3_DATA7 = _IMX_PAD(0x5BC, 0x274), // SD3_DATA7

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_USB_H_DATA)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_USB_H_DATA)
   IMX_PAD_USB_H_DATA = _IMX_PAD(0x5EC, 0x2A4), // USB_H_DATA

   // Pad Control Register (IOMUXC_SW_PAD_CTL_PAD_USB_H_STROBE)
   // Pad Mux Register (IOMUXC_SW_MUX_CTL_PAD_USB_H_STROBE)
   IMX_PAD_USB_H_STROBE = _IMX_PAD(0x5F0, 0x2A8), // USB_H_STROBE

} IMX_PAD;

//
// Alternate function numbers
//

// Alternate function numbers
typedef enum {
   IMX_IOMUXC_GPIO1_IO00_ALT0_I2C1_SCL = 0,
   IMX_IOMUXC_GPIO1_IO00_ALT1_SD1_VSELECT = 1,
   IMX_IOMUXC_GPIO1_IO00_ALT2_SPDIF_LOCK = 2,
   IMX_IOMUXC_GPIO1_IO00_ALT4_WDOG1_ANY = 4,
   IMX_IOMUXC_GPIO1_IO00_ALT5_GPIO1_IO00 = 5,
   IMX_IOMUXC_GPIO1_IO00_ALT6_SNVS_VIO_5 = 6,
} IMX_IOMUXC_GPIO1_IO00_ALT;

typedef enum {
   IMX_IOMUXC_GPIO1_IO01_ALT0_I2C1_SDA = 0,
   IMX_IOMUXC_GPIO1_IO01_ALT1_SD1_RESET_B = 1,
   IMX_IOMUXC_GPIO1_IO01_ALT2_SPDIF_SR_CLK = 2,
   IMX_IOMUXC_GPIO1_IO01_ALT4_WDOG3_B = 4,
   IMX_IOMUXC_GPIO1_IO01_ALT5_GPIO1_IO01 = 5,
   IMX_IOMUXC_GPIO1_IO01_ALT6_SNVS_VIO_5_CTL = 6,
} IMX_IOMUXC_GPIO1_IO01_ALT;

typedef enum {
   IMX_IOMUXC_GPIO1_IO02_ALT0_I2C2_SCL = 0,
   IMX_IOMUXC_GPIO1_IO02_ALT1_SD1_CD_B = 1,
   IMX_IOMUXC_GPIO1_IO02_ALT2_CSI2_MCLK = 2,
   IMX_IOMUXC_GPIO1_IO02_ALT4_WDOG1_B = 4,
   IMX_IOMUXC_GPIO1_IO02_ALT5_GPIO1_IO02 = 5,
   IMX_IOMUXC_GPIO1_IO02_ALT6_CCM_REF_EN_B = 6,
} IMX_IOMUXC_GPIO1_IO02_ALT;

typedef enum {
   IMX_IOMUXC_GPIO1_IO03_ALT0_I2C2_SDA = 0,
   IMX_IOMUXC_GPIO1_IO03_ALT1_SD1_WP = 1,
   IMX_IOMUXC_GPIO1_IO03_ALT2_ENET1_REF_CLK_25M = 2,
   IMX_IOMUXC_GPIO1_IO03_ALT4_WDOG2_B = 4,
   IMX_IOMUXC_GPIO1_IO03_ALT5_GPIO1_IO03 = 5,
} IMX_IOMUXC_GPIO1_IO03_ALT;

typedef enum {
   IMX_IOMUXC_GPIO1_IO04_ALT0_UART1_TX_DATA = 0,
   IMX_IOMUXC_GPIO1_IO04_ALT1_SD2_RESET_B = 1,
   IMX_IOMUXC_GPIO1_IO04_ALT2_ENET1_MDC = 2,
   IMX_IOMUXC_GPIO1_IO04_ALT4_ENET2_REF_CLK2 = 4,
   IMX_IOMUXC_GPIO1_IO04_ALT5_GPIO1_IO04 = 5,
} IMX_IOMUXC_GPIO1_IO04_ALT;

typedef enum {
   IMX_IOMUXC_GPIO1_IO05_ALT0_UART1_RX_DATA = 0,
   IMX_IOMUXC_GPIO1_IO05_ALT1_SD2_VSELECT = 1,
   IMX_IOMUXC_GPIO1_IO05_ALT2_ENET1_MDIO = 2,
   IMX_IOMUXC_GPIO1_IO05_ALT3_ASRC_EXT_CLK = 3,
   IMX_IOMUXC_GPIO1_IO05_ALT4_ENET1_REF_CLK1 = 4,
   IMX_IOMUXC_GPIO1_IO05_ALT5_GPIO1_IO05 = 5,
} IMX_IOMUXC_GPIO1_IO05_ALT;

typedef enum {
   IMX_IOMUXC_GPIO1_IO06_ALT0_UART2_TX_DATA = 0,
   IMX_IOMUXC_GPIO1_IO06_ALT1_SD2_CD_B = 1,
   IMX_IOMUXC_GPIO1_IO06_ALT2_ENET2_MDC = 2,
   IMX_IOMUXC_GPIO1_IO06_ALT3_CSI1_MCLK = 3,
   IMX_IOMUXC_GPIO1_IO06_ALT4_UART1_RTS_B = 4,
   IMX_IOMUXC_GPIO1_IO06_ALT5_GPIO1_IO06 = 5,
} IMX_IOMUXC_GPIO1_IO06_ALT;

typedef enum {
   IMX_IOMUXC_GPIO1_IO07_ALT0_UART2_RX_DATA = 0,
   IMX_IOMUXC_GPIO1_IO07_ALT1_SD2_WP = 1,
   IMX_IOMUXC_GPIO1_IO07_ALT2_ENET2_MDIO = 2,
   IMX_IOMUXC_GPIO1_IO07_ALT3_AUDIO_CLK_OUT = 3,
   IMX_IOMUXC_GPIO1_IO07_ALT4_UART1_CTS_B = 4,
   IMX_IOMUXC_GPIO1_IO07_ALT5_GPIO1_IO07 = 5,
   IMX_IOMUXC_GPIO1_IO07_ALT7_DCIC2_OUT = 7,
} IMX_IOMUXC_GPIO1_IO07_ALT;

typedef enum {
   IMX_IOMUXC_GPIO1_IO08_ALT0_USB_OTG1_OC = 0,
   IMX_IOMUXC_GPIO1_IO08_ALT1_WDOG1_B = 1,
   IMX_IOMUXC_GPIO1_IO08_ALT2_SDMA_EXT_EVENT0 = 2,
   IMX_IOMUXC_GPIO1_IO08_ALT3_CCM_PMIC_READY = 3,
   IMX_IOMUXC_GPIO1_IO08_ALT4_UART2_RTS_B = 4,
   IMX_IOMUXC_GPIO1_IO08_ALT5_GPIO1_IO08 = 5,
   IMX_IOMUXC_GPIO1_IO08_ALT7_DCIC1_OUT = 7,
} IMX_IOMUXC_GPIO1_IO08_ALT;

typedef enum {
   IMX_IOMUXC_GPIO1_IO09_ALT0_USB_OTG1_PWR = 0,
   IMX_IOMUXC_GPIO1_IO09_ALT1_WDOG2_B = 1,
   IMX_IOMUXC_GPIO1_IO09_ALT2_SDMA_EXT_EVENT1 = 2,
   IMX_IOMUXC_GPIO1_IO09_ALT4_UART2_CTS_B = 4,
   IMX_IOMUXC_GPIO1_IO09_ALT5_GPIO1_IO09 = 5,
} IMX_IOMUXC_GPIO1_IO09_ALT;

typedef enum {
   IMX_IOMUXC_GPIO1_IO10_ALT0_USB_OTG1_ID = 0,
   IMX_IOMUXC_GPIO1_IO10_ALT1_SPDIF_EXT_CLK = 1,
   IMX_IOMUXC_GPIO1_IO10_ALT2_PWM1_OUT = 2,
   IMX_IOMUXC_GPIO1_IO10_ALT4_CSI1_FIELD = 4,
   IMX_IOMUXC_GPIO1_IO10_ALT5_GPIO1_IO10 = 5,
} IMX_IOMUXC_GPIO1_IO10_ALT;

typedef enum {
   IMX_IOMUXC_GPIO1_IO11_ALT0_USB_OTG2_OC = 0,
   IMX_IOMUXC_GPIO1_IO11_ALT1_SPDIF_IN = 1,
   IMX_IOMUXC_GPIO1_IO11_ALT2_PWM2_OUT = 2,
   IMX_IOMUXC_GPIO1_IO11_ALT3_CCM_CLKO1 = 3,
   IMX_IOMUXC_GPIO1_IO11_ALT4_MLB_DATA = 4,
   IMX_IOMUXC_GPIO1_IO11_ALT5_GPIO1_IO11 = 5,
} IMX_IOMUXC_GPIO1_IO11_ALT;

typedef enum {
   IMX_IOMUXC_GPIO1_IO12_ALT0_USB_OTG2_PWR = 0,
   IMX_IOMUXC_GPIO1_IO12_ALT1_SPDIF_OUT = 1,
   IMX_IOMUXC_GPIO1_IO12_ALT2_PWM3_OUT = 2,
   IMX_IOMUXC_GPIO1_IO12_ALT3_CCM_CLKO2 = 3,
   IMX_IOMUXC_GPIO1_IO12_ALT4_MLB_CLK = 4,
   IMX_IOMUXC_GPIO1_IO12_ALT5_GPIO1_IO12 = 5,
} IMX_IOMUXC_GPIO1_IO12_ALT;

typedef enum {
   IMX_IOMUXC_GPIO1_IO13_ALT0_WDOG1_ANY = 0,
   IMX_IOMUXC_GPIO1_IO13_ALT1_USB_OTG2_ID = 1,
   IMX_IOMUXC_GPIO1_IO13_ALT2_PWM4_OUT = 2,
   IMX_IOMUXC_GPIO1_IO13_ALT4_MLB_SIG = 4,
   IMX_IOMUXC_GPIO1_IO13_ALT5_GPIO1_IO13 = 5,
} IMX_IOMUXC_GPIO1_IO13_ALT;

typedef enum {
   IMX_IOMUXC_CSI_DATA00_ALT0_CSI1_DATA02 = 0,
   IMX_IOMUXC_CSI_DATA00_ALT1_ESAI_TX_CLK = 1,
   IMX_IOMUXC_CSI_DATA00_ALT2_AUD6_TXC = 2,
   IMX_IOMUXC_CSI_DATA00_ALT3_I2C1_SCL = 3,
   IMX_IOMUXC_CSI_DATA00_ALT4_UART6_RI_B = 4,
   IMX_IOMUXC_CSI_DATA00_ALT5_GPIO1_IO14 = 5,
   IMX_IOMUXC_CSI_DATA00_ALT6_EIM_DATA23 = 6,
   IMX_IOMUXC_CSI_DATA00_ALT7_SAI1_TX_BCLK = 7,
} IMX_IOMUXC_CSI_DATA00_ALT;

typedef enum {
   IMX_IOMUXC_CSI_DATA01_ALT0_CSI1_DATA03 = 0,
   IMX_IOMUXC_CSI_DATA01_ALT1_ESAI_TX_FS = 1,
   IMX_IOMUXC_CSI_DATA01_ALT2_AUD6_TXFS = 2,
   IMX_IOMUXC_CSI_DATA01_ALT3_I2C1_SDA = 3,
   IMX_IOMUXC_CSI_DATA01_ALT4_UART6_DSR_B = 4,
   IMX_IOMUXC_CSI_DATA01_ALT5_GPIO1_IO15 = 5,
   IMX_IOMUXC_CSI_DATA01_ALT6_EIM_DATA22 = 6,
   IMX_IOMUXC_CSI_DATA01_ALT7_SAI1_TX_SYNC = 7,
} IMX_IOMUXC_CSI_DATA01_ALT;

typedef enum {
   IMX_IOMUXC_CSI_DATA02_ALT0_CSI1_DATA04 = 0,
   IMX_IOMUXC_CSI_DATA02_ALT1_ESAI_RX_CLK = 1,
   IMX_IOMUXC_CSI_DATA02_ALT2_AUD6_RXC = 2,
   IMX_IOMUXC_CSI_DATA02_ALT3_KPP_COL5 = 3,
   IMX_IOMUXC_CSI_DATA02_ALT4_UART6_DTR_B = 4,
   IMX_IOMUXC_CSI_DATA02_ALT5_GPIO1_IO16 = 5,
   IMX_IOMUXC_CSI_DATA02_ALT6_EIM_DATA21 = 6,
   IMX_IOMUXC_CSI_DATA02_ALT7_SAI1_RX_BCLK = 7,
} IMX_IOMUXC_CSI_DATA02_ALT;

typedef enum {
   IMX_IOMUXC_CSI_DATA03_ALT0_CSI1_DATA05 = 0,
   IMX_IOMUXC_CSI_DATA03_ALT1_ESAI_RX_FS = 1,
   IMX_IOMUXC_CSI_DATA03_ALT2_AUD6_RXFS = 2,
   IMX_IOMUXC_CSI_DATA03_ALT3_KPP_ROW5 = 3,
   IMX_IOMUXC_CSI_DATA03_ALT4_UART6_DCD_B = 4,
   IMX_IOMUXC_CSI_DATA03_ALT5_GPIO1_IO17 = 5,
   IMX_IOMUXC_CSI_DATA03_ALT6_EIM_DATA20 = 6,
   IMX_IOMUXC_CSI_DATA03_ALT7_SAI1_RX_SYNC = 7,
} IMX_IOMUXC_CSI_DATA03_ALT;

typedef enum {
   IMX_IOMUXC_CSI_DATA04_ALT0_CSI1_DATA06 = 0,
   IMX_IOMUXC_CSI_DATA04_ALT1_ESAI_TX1 = 1,
   IMX_IOMUXC_CSI_DATA04_ALT2_SPDIF_OUT = 2,
   IMX_IOMUXC_CSI_DATA04_ALT3_KPP_COL6 = 3,
   IMX_IOMUXC_CSI_DATA04_ALT4_UART6_RX_DATA = 4,
   IMX_IOMUXC_CSI_DATA04_ALT5_GPIO1_IO18 = 5,
   IMX_IOMUXC_CSI_DATA04_ALT6_EIM_DATA19 = 6,
   IMX_IOMUXC_CSI_DATA04_ALT7_PWM5_OUT = 7,
} IMX_IOMUXC_CSI_DATA04_ALT;

typedef enum {
   IMX_IOMUXC_CSI_DATA05_ALT0_CSI1_DATA07 = 0,
   IMX_IOMUXC_CSI_DATA05_ALT1_ESAI_TX4_RX1 = 1,
   IMX_IOMUXC_CSI_DATA05_ALT2_SPDIF_IN = 2,
   IMX_IOMUXC_CSI_DATA05_ALT3_KPP_ROW6 = 3,
   IMX_IOMUXC_CSI_DATA05_ALT4_UART6_TX_DATA = 4,
   IMX_IOMUXC_CSI_DATA05_ALT5_GPIO1_IO19 = 5,
   IMX_IOMUXC_CSI_DATA05_ALT6_EIM_DATA18 = 6,
   IMX_IOMUXC_CSI_DATA05_ALT7_PWM6_OUT = 7,
} IMX_IOMUXC_CSI_DATA05_ALT;

typedef enum {
   IMX_IOMUXC_CSI_DATA06_ALT0_CSI1_DATA08 = 0,
   IMX_IOMUXC_CSI_DATA06_ALT1_ESAI_TX2_RX3 = 1,
   IMX_IOMUXC_CSI_DATA06_ALT2_I2C4_SCL = 2,
   IMX_IOMUXC_CSI_DATA06_ALT3_KPP_COL7 = 3,
   IMX_IOMUXC_CSI_DATA06_ALT4_UART6_RTS_B = 4,
   IMX_IOMUXC_CSI_DATA06_ALT5_GPIO1_IO20 = 5,
   IMX_IOMUXC_CSI_DATA06_ALT6_EIM_DATA17 = 6,
   IMX_IOMUXC_CSI_DATA06_ALT7_DCIC2_OUT = 7,
} IMX_IOMUXC_CSI_DATA06_ALT;

typedef enum {
   IMX_IOMUXC_CSI_DATA07_ALT0_CSI1_DATA09 = 0,
   IMX_IOMUXC_CSI_DATA07_ALT1_ESAI_TX3_RX2 = 1,
   IMX_IOMUXC_CSI_DATA07_ALT2_I2C4_SDA = 2,
   IMX_IOMUXC_CSI_DATA07_ALT3_KPP_ROW7 = 3,
   IMX_IOMUXC_CSI_DATA07_ALT4_UART6_CTS_B = 4,
   IMX_IOMUXC_CSI_DATA07_ALT5_GPIO1_IO21 = 5,
   IMX_IOMUXC_CSI_DATA07_ALT6_EIM_DATA16 = 6,
   IMX_IOMUXC_CSI_DATA07_ALT7_DCIC1_OUT = 7,
} IMX_IOMUXC_CSI_DATA07_ALT;

typedef enum {
   IMX_IOMUXC_CSI_HSYNC_ALT0_CSI1_HSYNC = 0,
   IMX_IOMUXC_CSI_HSYNC_ALT1_ESAI_TX0 = 1,
   IMX_IOMUXC_CSI_HSYNC_ALT2_AUD6_TXD = 2,
   IMX_IOMUXC_CSI_HSYNC_ALT3_UART4_RTS_B = 3,
   IMX_IOMUXC_CSI_HSYNC_ALT4_MQS_LEFT = 4,
   IMX_IOMUXC_CSI_HSYNC_ALT5_GPIO1_IO22 = 5,
   IMX_IOMUXC_CSI_HSYNC_ALT6_EIM_DATA25 = 6,
   IMX_IOMUXC_CSI_HSYNC_ALT7_SAI1_TX_DATA0 = 7,
} IMX_IOMUXC_CSI_HSYNC_ALT;

typedef enum {
   IMX_IOMUXC_CSI_MCLK_ALT0_CSI1_MCLK = 0,
   IMX_IOMUXC_CSI_MCLK_ALT1_ESAI_TX_HF_CLK = 1,
   IMX_IOMUXC_CSI_MCLK_ALT3_UART4_RX_DATA = 3,
   IMX_IOMUXC_CSI_MCLK_ALT4_XTALOSC_REF_CLK_32K = 4,
   IMX_IOMUXC_CSI_MCLK_ALT5_GPIO1_IO23 = 5,
   IMX_IOMUXC_CSI_MCLK_ALT6_EIM_DATA26 = 6,
   IMX_IOMUXC_CSI_MCLK_ALT7_CSI1_FIELD = 7,
} IMX_IOMUXC_CSI_MCLK_ALT;

typedef enum {
   IMX_IOMUXC_CSI_PIXCLK_ALT0_CSI1_PIXCLK = 0,
   IMX_IOMUXC_CSI_PIXCLK_ALT1_ESAI_RX_HF_CLK = 1,
   IMX_IOMUXC_CSI_PIXCLK_ALT2_AUDIO_CLK_OUT = 2,
   IMX_IOMUXC_CSI_PIXCLK_ALT3_UART4_TX_DATA = 3,
   IMX_IOMUXC_CSI_PIXCLK_ALT4_XTALOSC_REF_CLK_24M = 4,
   IMX_IOMUXC_CSI_PIXCLK_ALT5_GPIO1_IO24 = 5,
   IMX_IOMUXC_CSI_PIXCLK_ALT6_EIM_DATA27 = 6,
   IMX_IOMUXC_CSI_PIXCLK_ALT7_ESAI_TX_HF_CLK = 7,
} IMX_IOMUXC_CSI_PIXCLK_ALT;

typedef enum {
   IMX_IOMUXC_CSI_VSYNC_ALT0_CSI1_VSYNC = 0,
   IMX_IOMUXC_CSI_VSYNC_ALT1_ESAI_TX5_RX0 = 1,
   IMX_IOMUXC_CSI_VSYNC_ALT2_AUD6_RXD = 2,
   IMX_IOMUXC_CSI_VSYNC_ALT3_UART4_CTS_B = 3,
   IMX_IOMUXC_CSI_VSYNC_ALT4_MQS_RIGHT = 4,
   IMX_IOMUXC_CSI_VSYNC_ALT5_GPIO1_IO25 = 5,
   IMX_IOMUXC_CSI_VSYNC_ALT6_EIM_DATA24 = 6,
   IMX_IOMUXC_CSI_VSYNC_ALT7_SAI1_RX_DATA0 = 7,
} IMX_IOMUXC_CSI_VSYNC_ALT;

typedef enum {
   IMX_IOMUXC_ENET1_COL_ALT0_ENET1_COL = 0,
   IMX_IOMUXC_ENET1_COL_ALT1_ENET2_MDC = 1,
   IMX_IOMUXC_ENET1_COL_ALT2_AUD4_TXC = 2,
   IMX_IOMUXC_ENET1_COL_ALT3_UART1_RI_B = 3,
   IMX_IOMUXC_ENET1_COL_ALT4_SPDIF_EXT_CLK = 4,
   IMX_IOMUXC_ENET1_COL_ALT5_GPIO2_IO00 = 5,
   IMX_IOMUXC_ENET1_COL_ALT6_CSI2_DATA23 = 6,
   IMX_IOMUXC_ENET1_COL_ALT7_LCD2_DATA16 = 7,
} IMX_IOMUXC_ENET1_COL_ALT;

typedef enum {
   IMX_IOMUXC_ENET1_CRS_ALT0_ENET1_CRS = 0,
   IMX_IOMUXC_ENET1_CRS_ALT1_ENET2_MDIO = 1,
   IMX_IOMUXC_ENET1_CRS_ALT2_AUD4_TXD = 2,
   IMX_IOMUXC_ENET1_CRS_ALT3_UART1_DCD_B = 3,
   IMX_IOMUXC_ENET1_CRS_ALT4_SPDIF_LOCK = 4,
   IMX_IOMUXC_ENET1_CRS_ALT5_GPIO2_IO01 = 5,
   IMX_IOMUXC_ENET1_CRS_ALT6_CSI2_DATA22 = 6,
   IMX_IOMUXC_ENET1_CRS_ALT7_LCD2_DATA17 = 7,
} IMX_IOMUXC_ENET1_CRS_ALT;

typedef enum {
   IMX_IOMUXC_ENET1_MDC_ALT0_ENET1_MDC = 0,
   IMX_IOMUXC_ENET1_MDC_ALT1_ENET2_MDC = 1,
   IMX_IOMUXC_ENET1_MDC_ALT2_AUD3_RXFS = 2,
   IMX_IOMUXC_ENET1_MDC_ALT3_XTALOSC_REF_CLK_24M = 3,
   IMX_IOMUXC_ENET1_MDC_ALT4_EPIT2_OUT = 4,
   IMX_IOMUXC_ENET1_MDC_ALT5_GPIO2_IO02 = 5,
   IMX_IOMUXC_ENET1_MDC_ALT6_USB_OTG1_PWR = 6,
   IMX_IOMUXC_ENET1_MDC_ALT7_PWM7_OUT = 7,
} IMX_IOMUXC_ENET1_MDC_ALT;

typedef enum {
   IMX_IOMUXC_ENET1_MDIO_ALT0_ENET1_MDIO = 0,
   IMX_IOMUXC_ENET1_MDIO_ALT1_ENET2_MDIO = 1,
   IMX_IOMUXC_ENET1_MDIO_ALT2_AUDIO_CLK_OUT = 2,
   IMX_IOMUXC_ENET1_MDIO_ALT4_EPIT1_OUT = 4,
   IMX_IOMUXC_ENET1_MDIO_ALT5_GPIO2_IO03 = 5,
   IMX_IOMUXC_ENET1_MDIO_ALT6_USB_OTG1_OC = 6,
   IMX_IOMUXC_ENET1_MDIO_ALT7_PWM8_OUT = 7,
} IMX_IOMUXC_ENET1_MDIO_ALT;

typedef enum {
   IMX_IOMUXC_ENET1_RX_CLK_ALT0_ENET1_RX_CLK = 0,
   IMX_IOMUXC_ENET1_RX_CLK_ALT1_ENET1_REF_CLK_25M = 1,
   IMX_IOMUXC_ENET1_RX_CLK_ALT2_AUD4_TXFS = 2,
   IMX_IOMUXC_ENET1_RX_CLK_ALT3_UART1_DSR_B = 3,
   IMX_IOMUXC_ENET1_RX_CLK_ALT4_SPDIF_OUT = 4,
   IMX_IOMUXC_ENET1_RX_CLK_ALT5_GPIO2_IO04 = 5,
   IMX_IOMUXC_ENET1_RX_CLK_ALT6_CSI2_DATA21 = 6,
   IMX_IOMUXC_ENET1_RX_CLK_ALT7_LCD2_DATA18 = 7,
} IMX_IOMUXC_ENET1_RX_CLK_ALT;

typedef enum {
   IMX_IOMUXC_ENET1_TX_CLK_ALT0_ENET1_TX_CLK = 0,
   IMX_IOMUXC_ENET1_TX_CLK_ALT1_ENET1_REF_CLK1 = 1,
   IMX_IOMUXC_ENET1_TX_CLK_ALT2_AUD4_RXD = 2,
   IMX_IOMUXC_ENET1_TX_CLK_ALT3_UART1_DTR_B = 3,
   IMX_IOMUXC_ENET1_TX_CLK_ALT4_SPDIF_SR_CLK = 4,
   IMX_IOMUXC_ENET1_TX_CLK_ALT5_GPIO2_IO05 = 5,
   IMX_IOMUXC_ENET1_TX_CLK_ALT6_CSI2_DATA20 = 6,
   IMX_IOMUXC_ENET1_TX_CLK_ALT7_LCD2_DATA19 = 7,
} IMX_IOMUXC_ENET1_TX_CLK_ALT;

typedef enum {
   IMX_IOMUXC_ENET2_COL_ALT0_ENET2_COL = 0,
   IMX_IOMUXC_ENET2_COL_ALT1_ENET1_MDC = 1,
   IMX_IOMUXC_ENET2_COL_ALT2_AUD4_RXC = 2,
   IMX_IOMUXC_ENET2_COL_ALT3_UART1_RX_DATA = 3,
   IMX_IOMUXC_ENET2_COL_ALT4_SPDIF_IN = 4,
   IMX_IOMUXC_ENET2_COL_ALT5_GPIO2_IO06 = 5,
   IMX_IOMUXC_ENET2_COL_ALT6_USB_OTG1_ID = 6,
   IMX_IOMUXC_ENET2_COL_ALT7_LCD2_DATA20 = 7,
} IMX_IOMUXC_ENET2_COL_ALT;

typedef enum {
   IMX_IOMUXC_ENET2_CRS_ALT0_ENET2_CRS = 0,
   IMX_IOMUXC_ENET2_CRS_ALT1_ENET1_MDIO = 1,
   IMX_IOMUXC_ENET2_CRS_ALT2_AUD4_RXFS = 2,
   IMX_IOMUXC_ENET2_CRS_ALT3_UART1_TX_DATA = 3,
   IMX_IOMUXC_ENET2_CRS_ALT4_MLB_SIG = 4,
   IMX_IOMUXC_ENET2_CRS_ALT5_GPIO2_IO07 = 5,
   IMX_IOMUXC_ENET2_CRS_ALT6_USB_OTG2_ID = 6,
   IMX_IOMUXC_ENET2_CRS_ALT7_LCD2_DATA21 = 7,
} IMX_IOMUXC_ENET2_CRS_ALT;

typedef enum {
   IMX_IOMUXC_ENET2_RX_CLK_ALT0_ENET2_RX_CLK = 0,
   IMX_IOMUXC_ENET2_RX_CLK_ALT1_ENET2_REF_CLK_25M = 1,
   IMX_IOMUXC_ENET2_RX_CLK_ALT2_I2C3_SCL = 2,
   IMX_IOMUXC_ENET2_RX_CLK_ALT3_UART1_RTS_B = 3,
   IMX_IOMUXC_ENET2_RX_CLK_ALT4_MLB_DATA = 4,
   IMX_IOMUXC_ENET2_RX_CLK_ALT5_GPIO2_IO08 = 5,
   IMX_IOMUXC_ENET2_RX_CLK_ALT6_USB_OTG2_OC = 6,
   IMX_IOMUXC_ENET2_RX_CLK_ALT7_LCD2_DATA22 = 7,
} IMX_IOMUXC_ENET2_RX_CLK_ALT;

typedef enum {
   IMX_IOMUXC_ENET2_TX_CLK_ALT0_ENET2_TX_CLK = 0,
   IMX_IOMUXC_ENET2_TX_CLK_ALT1_ENET2_REF_CLK2 = 1,
   IMX_IOMUXC_ENET2_TX_CLK_ALT2_I2C3_SDA = 2,
   IMX_IOMUXC_ENET2_TX_CLK_ALT3_UART1_CTS_B = 3,
   IMX_IOMUXC_ENET2_TX_CLK_ALT4_MLB_CLK = 4,
   IMX_IOMUXC_ENET2_TX_CLK_ALT5_GPIO2_IO09 = 5,
   IMX_IOMUXC_ENET2_TX_CLK_ALT6_USB_OTG2_PWR = 6,
   IMX_IOMUXC_ENET2_TX_CLK_ALT7_LCD2_DATA23 = 7,
} IMX_IOMUXC_ENET2_TX_CLK_ALT;

typedef enum {
   IMX_IOMUXC_KEY_COL0_ALT0_KPP_COL0 = 0,
   IMX_IOMUXC_KEY_COL0_ALT1_SD3_CD_B = 1,
   IMX_IOMUXC_KEY_COL0_ALT2_UART6_RTS_B = 2,
   IMX_IOMUXC_KEY_COL0_ALT3_ECSPI1_SCLK = 3,
   IMX_IOMUXC_KEY_COL0_ALT4_AUD5_TXC = 4,
   IMX_IOMUXC_KEY_COL0_ALT5_GPIO2_IO10 = 5,
   IMX_IOMUXC_KEY_COL0_ALT6_SDMA_EXT_EVENT1 = 6,
   IMX_IOMUXC_KEY_COL0_ALT7_SAI2_TX_BCLK = 7,
} IMX_IOMUXC_KEY_COL0_ALT;

typedef enum {
   IMX_IOMUXC_KEY_COL1_ALT0_KPP_COL1 = 0,
   IMX_IOMUXC_KEY_COL1_ALT1_SD3_RESET_B = 1,
   IMX_IOMUXC_KEY_COL1_ALT2_UART6_TX_DATA = 2,
   IMX_IOMUXC_KEY_COL1_ALT3_ECSPI1_MISO = 3,
   IMX_IOMUXC_KEY_COL1_ALT4_AUD5_TXFS = 4,
   IMX_IOMUXC_KEY_COL1_ALT5_GPIO2_IO11 = 5,
   IMX_IOMUXC_KEY_COL1_ALT6_SD3_RESET = 6,
   IMX_IOMUXC_KEY_COL1_ALT7_SAI2_TX_SYNC = 7,
} IMX_IOMUXC_KEY_COL1_ALT;

typedef enum {
   IMX_IOMUXC_KEY_COL2_ALT0_KPP_COL2 = 0,
   IMX_IOMUXC_KEY_COL2_ALT1_SD4_CD_B = 1,
   IMX_IOMUXC_KEY_COL2_ALT2_UART5_RTS_B = 2,
   IMX_IOMUXC_KEY_COL2_ALT3_CAN1_TX = 3,
   IMX_IOMUXC_KEY_COL2_ALT5_GPIO2_IO12 = 5,
   IMX_IOMUXC_KEY_COL2_ALT6_EIM_DATA30 = 6,
   IMX_IOMUXC_KEY_COL2_ALT7_ECSPI1_RDY = 7,
} IMX_IOMUXC_KEY_COL2_ALT;

typedef enum {
   IMX_IOMUXC_KEY_COL3_ALT0_KPP_COL3 = 0,
   IMX_IOMUXC_KEY_COL3_ALT1_SD4_LCTL = 1,
   IMX_IOMUXC_KEY_COL3_ALT2_UART5_TX_DATA = 2,
   IMX_IOMUXC_KEY_COL3_ALT3_CAN2_TX = 3,
   IMX_IOMUXC_KEY_COL3_ALT5_GPIO2_IO13 = 5,
   IMX_IOMUXC_KEY_COL3_ALT6_EIM_DATA28 = 6,
   IMX_IOMUXC_KEY_COL3_ALT7_ECSPI1_SS2 = 7,
} IMX_IOMUXC_KEY_COL3_ALT;

typedef enum {
   IMX_IOMUXC_KEY_COL4_ALT0_KPP_COL4 = 0,
   IMX_IOMUXC_KEY_COL4_ALT1_ENET2_MDC = 1,
   IMX_IOMUXC_KEY_COL4_ALT2_I2C3_SCL = 2,
   IMX_IOMUXC_KEY_COL4_ALT3_SD2_LCTL = 3,
   IMX_IOMUXC_KEY_COL4_ALT4_AUD5_RXC = 4,
   IMX_IOMUXC_KEY_COL4_ALT5_GPIO2_IO14 = 5,
   IMX_IOMUXC_KEY_COL4_ALT6_EIM_CRE = 6,
   IMX_IOMUXC_KEY_COL4_ALT7_SAI2_RX_BCLK = 7,
} IMX_IOMUXC_KEY_COL4_ALT;

typedef enum {
   IMX_IOMUXC_KEY_ROW0_ALT0_KPP_ROW0 = 0,
   IMX_IOMUXC_KEY_ROW0_ALT1_SD3_WP = 1,
   IMX_IOMUXC_KEY_ROW0_ALT2_UART6_CTS_B = 2,
   IMX_IOMUXC_KEY_ROW0_ALT3_ECSPI1_MOSI = 3,
   IMX_IOMUXC_KEY_ROW0_ALT4_AUD5_TXD = 4,
   IMX_IOMUXC_KEY_ROW0_ALT5_GPIO2_IO15 = 5,
   IMX_IOMUXC_KEY_ROW0_ALT6_SDMA_EXT_EVENT0 = 6,
   IMX_IOMUXC_KEY_ROW0_ALT7_SAI2_TX_DATA0 = 7,
} IMX_IOMUXC_KEY_ROW0_ALT;

typedef enum {
   IMX_IOMUXC_KEY_ROW1_ALT0_KPP_ROW1 = 0,
   IMX_IOMUXC_KEY_ROW1_ALT1_SD4_VSELECT = 1,
   IMX_IOMUXC_KEY_ROW1_ALT2_UART6_RX_DATA = 2,
   IMX_IOMUXC_KEY_ROW1_ALT3_ECSPI1_SS0 = 3,
   IMX_IOMUXC_KEY_ROW1_ALT4_AUD5_RXD = 4,
   IMX_IOMUXC_KEY_ROW1_ALT5_GPIO2_IO16 = 5,
   IMX_IOMUXC_KEY_ROW1_ALT6_EIM_DATA31 = 6,
   IMX_IOMUXC_KEY_ROW1_ALT7_SAI2_RX_DATA0 = 7,
} IMX_IOMUXC_KEY_ROW1_ALT;

typedef enum {
   IMX_IOMUXC_KEY_ROW2_ALT0_KPP_ROW2 = 0,
   IMX_IOMUXC_KEY_ROW2_ALT1_SD4_WP = 1,
   IMX_IOMUXC_KEY_ROW2_ALT2_UART5_CTS_B = 2,
   IMX_IOMUXC_KEY_ROW2_ALT3_CAN1_RX = 3,
   IMX_IOMUXC_KEY_ROW2_ALT5_GPIO2_IO17 = 5,
   IMX_IOMUXC_KEY_ROW2_ALT6_EIM_DATA29 = 6,
   IMX_IOMUXC_KEY_ROW2_ALT7_ECSPI1_SS3 = 7,
} IMX_IOMUXC_KEY_ROW2_ALT;

typedef enum {
   IMX_IOMUXC_KEY_ROW3_ALT0_KPP_ROW3 = 0,
   IMX_IOMUXC_KEY_ROW3_ALT1_SD3_LCTL = 1,
   IMX_IOMUXC_KEY_ROW3_ALT2_UART5_RX_DATA = 2,
   IMX_IOMUXC_KEY_ROW3_ALT3_CAN2_RX = 3,
   IMX_IOMUXC_KEY_ROW3_ALT5_GPIO2_IO18 = 5,
   IMX_IOMUXC_KEY_ROW3_ALT6_EIM_DTACK_B = 6,
   IMX_IOMUXC_KEY_ROW3_ALT7_ECSPI1_SS1 = 7,
} IMX_IOMUXC_KEY_ROW3_ALT;

typedef enum {
   IMX_IOMUXC_KEY_ROW4_ALT0_KPP_ROW4 = 0,
   IMX_IOMUXC_KEY_ROW4_ALT1_ENET2_MDIO = 1,
   IMX_IOMUXC_KEY_ROW4_ALT2_I2C3_SDA = 2,
   IMX_IOMUXC_KEY_ROW4_ALT3_SD1_LCTL = 3,
   IMX_IOMUXC_KEY_ROW4_ALT4_AUD5_RXFS = 4,
   IMX_IOMUXC_KEY_ROW4_ALT5_GPIO2_IO19 = 5,
   IMX_IOMUXC_KEY_ROW4_ALT6_EIM_ACLK_FREERUN = 6,
   IMX_IOMUXC_KEY_ROW4_ALT7_SAI2_RX_SYNC = 7,
} IMX_IOMUXC_KEY_ROW4_ALT;

typedef enum {
   IMX_IOMUXC_LCD1_CLK_ALT0_LCD1_CLK = 0,
   IMX_IOMUXC_LCD1_CLK_ALT1_LCD1_WR_RWN = 1,
   IMX_IOMUXC_LCD1_CLK_ALT2_AUD3_RXC = 2,
   IMX_IOMUXC_LCD1_CLK_ALT3_ENET1_1588_EVENT2_IN = 3,
   IMX_IOMUXC_LCD1_CLK_ALT4_CSI1_DATA16 = 4,
   IMX_IOMUXC_LCD1_CLK_ALT5_GPIO3_IO00 = 5,
   IMX_IOMUXC_LCD1_CLK_ALT6_SD1_WP = 6,
} IMX_IOMUXC_LCD1_CLK_ALT;

typedef enum {
   IMX_IOMUXC_LCD1_DATA00_ALT0_LCD1_DATA00 = 0,
   IMX_IOMUXC_LCD1_DATA00_ALT1_EIM_CS1_B = 1,
   IMX_IOMUXC_LCD1_DATA00_ALT2_ARM_M4_TRACE0 = 2,
   IMX_IOMUXC_LCD1_DATA00_ALT3_ARM_A9_TRACE00 = 3,
   IMX_IOMUXC_LCD1_DATA00_ALT4_CSI1_DATA20 = 4,
   IMX_IOMUXC_LCD1_DATA00_ALT5_GPIO3_IO01 = 5,
   IMX_IOMUXC_LCD1_DATA00_ALT6_SRC_BOOT_CFG00 = 6,
} IMX_IOMUXC_LCD1_DATA00_ALT;

typedef enum {
   IMX_IOMUXC_LCD1_DATA01_ALT0_LCD1_DATA01 = 0,
   IMX_IOMUXC_LCD1_DATA01_ALT1_EIM_CS2_B = 1,
   IMX_IOMUXC_LCD1_DATA01_ALT2_ARM_M4_TRACE1 = 2,
   IMX_IOMUXC_LCD1_DATA01_ALT3_ARM_A9_TRACE01 = 3,
   IMX_IOMUXC_LCD1_DATA01_ALT4_CSI1_DATA21 = 4,
   IMX_IOMUXC_LCD1_DATA01_ALT5_GPIO3_IO02 = 5,
   IMX_IOMUXC_LCD1_DATA01_ALT6_SRC_BOOT_CFG01 = 6,
} IMX_IOMUXC_LCD1_DATA01_ALT;

typedef enum {
   IMX_IOMUXC_LCD1_DATA02_ALT0_LCD1_DATA02 = 0,
   IMX_IOMUXC_LCD1_DATA02_ALT1_EIM_CS3_B = 1,
   IMX_IOMUXC_LCD1_DATA02_ALT2_ARM_M4_TRACE2 = 2,
   IMX_IOMUXC_LCD1_DATA02_ALT3_ARM_A9_TRACE02 = 3,
   IMX_IOMUXC_LCD1_DATA02_ALT4_CSI1_DATA22 = 4,
   IMX_IOMUXC_LCD1_DATA02_ALT5_GPIO3_IO03 = 5,
   IMX_IOMUXC_LCD1_DATA02_ALT6_SRC_BOOT_CFG02 = 6,
} IMX_IOMUXC_LCD1_DATA02_ALT;

typedef enum {
   IMX_IOMUXC_LCD1_DATA03_ALT0_LCD1_DATA03 = 0,
   IMX_IOMUXC_LCD1_DATA03_ALT1_EIM_ADDR24 = 1,
   IMX_IOMUXC_LCD1_DATA03_ALT2_ARM_M4_TRACE3 = 2,
   IMX_IOMUXC_LCD1_DATA03_ALT3_ARM_A9_TRACE03 = 3,
   IMX_IOMUXC_LCD1_DATA03_ALT4_CSI1_DATA23 = 4,
   IMX_IOMUXC_LCD1_DATA03_ALT5_GPIO3_IO04 = 5,
   IMX_IOMUXC_LCD1_DATA03_ALT6_SRC_BOOT_CFG03 = 6,
} IMX_IOMUXC_LCD1_DATA03_ALT;

typedef enum {
   IMX_IOMUXC_LCD1_DATA04_ALT0_LCD1_DATA04 = 0,
   IMX_IOMUXC_LCD1_DATA04_ALT1_EIM_ADDR25 = 1,
   IMX_IOMUXC_LCD1_DATA04_ALT3_ARM_A9_TRACE04 = 3,
   IMX_IOMUXC_LCD1_DATA04_ALT4_CSI1_VSYNC = 4,
   IMX_IOMUXC_LCD1_DATA04_ALT5_GPIO3_IO05 = 5,
   IMX_IOMUXC_LCD1_DATA04_ALT6_SRC_BOOT_CFG04 = 6,
} IMX_IOMUXC_LCD1_DATA04_ALT;

typedef enum {
   IMX_IOMUXC_LCD1_DATA05_ALT0_LCD1_DATA05 = 0,
   IMX_IOMUXC_LCD1_DATA05_ALT1_EIM_ADDR26 = 1,
   IMX_IOMUXC_LCD1_DATA05_ALT3_ARM_A9_TRACE05 = 3,
   IMX_IOMUXC_LCD1_DATA05_ALT4_CSI1_HSYNC = 4,
   IMX_IOMUXC_LCD1_DATA05_ALT5_GPIO3_IO06 = 5,
   IMX_IOMUXC_LCD1_DATA05_ALT6_SRC_BOOT_CFG05 = 6,
} IMX_IOMUXC_LCD1_DATA05_ALT;

typedef enum {
   IMX_IOMUXC_LCD1_DATA06_ALT0_LCD1_DATA06 = 0,
   IMX_IOMUXC_LCD1_DATA06_ALT1_EIM_EB2_B = 1,
   IMX_IOMUXC_LCD1_DATA06_ALT3_ARM_A9_TRACE06 = 3,
   IMX_IOMUXC_LCD1_DATA06_ALT4_CSI1_PIXCLK = 4,
   IMX_IOMUXC_LCD1_DATA06_ALT5_GPIO3_IO07 = 5,
   IMX_IOMUXC_LCD1_DATA06_ALT6_SRC_BOOT_CFG06 = 6,
} IMX_IOMUXC_LCD1_DATA06_ALT;

typedef enum {
   IMX_IOMUXC_LCD1_DATA07_ALT0_LCD1_DATA07 = 0,
   IMX_IOMUXC_LCD1_DATA07_ALT1_EIM_EB3_B = 1,
   IMX_IOMUXC_LCD1_DATA07_ALT3_ARM_A9_TRACE07 = 3,
   IMX_IOMUXC_LCD1_DATA07_ALT4_CSI1_MCLK = 4,
   IMX_IOMUXC_LCD1_DATA07_ALT5_GPIO3_IO08 = 5,
   IMX_IOMUXC_LCD1_DATA07_ALT6_SRC_BOOT_CFG07 = 6,
} IMX_IOMUXC_LCD1_DATA07_ALT;

typedef enum {
   IMX_IOMUXC_LCD1_DATA08_ALT0_LCD1_DATA08 = 0,
   IMX_IOMUXC_LCD1_DATA08_ALT1_EIM_AD08 = 1,
   IMX_IOMUXC_LCD1_DATA08_ALT3_ARM_A9_TRACE08 = 3,
   IMX_IOMUXC_LCD1_DATA08_ALT4_CSI1_DATA09 = 4,
   IMX_IOMUXC_LCD1_DATA08_ALT5_GPIO3_IO09 = 5,
   IMX_IOMUXC_LCD1_DATA08_ALT6_SRC_BOOT_CFG08 = 6,
} IMX_IOMUXC_LCD1_DATA08_ALT;

typedef enum {
   IMX_IOMUXC_LCD1_DATA09_ALT0_LCD1_DATA09 = 0,
   IMX_IOMUXC_LCD1_DATA09_ALT1_EIM_AD09 = 1,
   IMX_IOMUXC_LCD1_DATA09_ALT3_ARM_A9_TRACE09 = 3,
   IMX_IOMUXC_LCD1_DATA09_ALT4_CSI1_DATA08 = 4,
   IMX_IOMUXC_LCD1_DATA09_ALT5_GPIO3_IO10 = 5,
   IMX_IOMUXC_LCD1_DATA09_ALT6_SRC_BOOT_CFG09 = 6,
} IMX_IOMUXC_LCD1_DATA09_ALT;

typedef enum {
   IMX_IOMUXC_LCD1_DATA10_ALT0_LCD1_DATA10 = 0,
   IMX_IOMUXC_LCD1_DATA10_ALT1_EIM_AD10 = 1,
   IMX_IOMUXC_LCD1_DATA10_ALT3_ARM_A9_TRACE10 = 3,
   IMX_IOMUXC_LCD1_DATA10_ALT4_CSI1_DATA07 = 4,
   IMX_IOMUXC_LCD1_DATA10_ALT5_GPIO3_IO11 = 5,
   IMX_IOMUXC_LCD1_DATA10_ALT6_SRC_BOOT_CFG10 = 6,
} IMX_IOMUXC_LCD1_DATA10_ALT;

typedef enum {
   IMX_IOMUXC_LCD1_DATA11_ALT0_LCD1_DATA11 = 0,
   IMX_IOMUXC_LCD1_DATA11_ALT1_EIM_AD11 = 1,
   IMX_IOMUXC_LCD1_DATA11_ALT3_ARM_A9_TRACE11 = 3,
   IMX_IOMUXC_LCD1_DATA11_ALT4_CSI1_DATA06 = 4,
   IMX_IOMUXC_LCD1_DATA11_ALT5_GPIO3_IO12 = 5,
   IMX_IOMUXC_LCD1_DATA11_ALT6_SRC_BOOT_CFG11 = 6,
} IMX_IOMUXC_LCD1_DATA11_ALT;

typedef enum {
   IMX_IOMUXC_LCD1_DATA12_ALT0_LCD1_DATA12 = 0,
   IMX_IOMUXC_LCD1_DATA12_ALT1_EIM_AD12 = 1,
   IMX_IOMUXC_LCD1_DATA12_ALT3_ARM_A9_TRACE12 = 3,
   IMX_IOMUXC_LCD1_DATA12_ALT4_CSI1_DATA05 = 4,
   IMX_IOMUXC_LCD1_DATA12_ALT5_GPIO3_IO13 = 5,
   IMX_IOMUXC_LCD1_DATA12_ALT6_SRC_BOOT_CFG12 = 6,
} IMX_IOMUXC_LCD1_DATA12_ALT;

typedef enum {
   IMX_IOMUXC_LCD1_DATA13_ALT0_LCD1_DATA13 = 0,
   IMX_IOMUXC_LCD1_DATA13_ALT1_EIM_AD13 = 1,
   IMX_IOMUXC_LCD1_DATA13_ALT3_ARM_A9_TRACE13 = 3,
   IMX_IOMUXC_LCD1_DATA13_ALT4_CSI1_DATA04 = 4,
   IMX_IOMUXC_LCD1_DATA13_ALT5_GPIO3_IO14 = 5,
   IMX_IOMUXC_LCD1_DATA13_ALT6_SRC_BOOT_CFG13 = 6,
} IMX_IOMUXC_LCD1_DATA13_ALT;

typedef enum {
   IMX_IOMUXC_LCD1_DATA14_ALT0_LCD1_DATA14 = 0,
   IMX_IOMUXC_LCD1_DATA14_ALT1_EIM_AD14 = 1,
   IMX_IOMUXC_LCD1_DATA14_ALT3_ARM_A9_TRACE14 = 3,
   IMX_IOMUXC_LCD1_DATA14_ALT4_CSI1_DATA03 = 4,
   IMX_IOMUXC_LCD1_DATA14_ALT5_GPIO3_IO15 = 5,
   IMX_IOMUXC_LCD1_DATA14_ALT6_SRC_BOOT_CFG14 = 6,
} IMX_IOMUXC_LCD1_DATA14_ALT;

typedef enum {
   IMX_IOMUXC_LCD1_DATA15_ALT0_LCD1_DATA15 = 0,
   IMX_IOMUXC_LCD1_DATA15_ALT1_EIM_AD15 = 1,
   IMX_IOMUXC_LCD1_DATA15_ALT3_ARM_A9_TRACE15 = 3,
   IMX_IOMUXC_LCD1_DATA15_ALT4_CSI1_DATA02 = 4,
   IMX_IOMUXC_LCD1_DATA15_ALT5_GPIO3_IO16 = 5,
   IMX_IOMUXC_LCD1_DATA15_ALT6_SRC_BOOT_CFG15 = 6,
} IMX_IOMUXC_LCD1_DATA15_ALT;

typedef enum {
   IMX_IOMUXC_LCD1_DATA16_ALT0_LCD1_DATA16 = 0,
   IMX_IOMUXC_LCD1_DATA16_ALT1_EIM_ADDR16 = 1,
   IMX_IOMUXC_LCD1_DATA16_ALT2_ARM_M4_TRACE_CLK = 2,
   IMX_IOMUXC_LCD1_DATA16_ALT3_ARM_A9_TRACE_CLK = 3,
   IMX_IOMUXC_LCD1_DATA16_ALT4_CSI1_DATA01 = 4,
   IMX_IOMUXC_LCD1_DATA16_ALT5_GPIO3_IO17 = 5,
   IMX_IOMUXC_LCD1_DATA16_ALT6_SRC_BOOT_CFG24 = 6,
} IMX_IOMUXC_LCD1_DATA16_ALT;

typedef enum {
   IMX_IOMUXC_LCD1_DATA17_ALT0_LCD1_DATA17 = 0,
   IMX_IOMUXC_LCD1_DATA17_ALT1_EIM_ADDR17 = 1,
   IMX_IOMUXC_LCD1_DATA17_ALT3_ARM_A9_TRACE_CTL = 3,
   IMX_IOMUXC_LCD1_DATA17_ALT4_CSI1_DATA00 = 4,
   IMX_IOMUXC_LCD1_DATA17_ALT5_GPIO3_IO18 = 5,
   IMX_IOMUXC_LCD1_DATA17_ALT6_SRC_BOOT_CFG25 = 6,
} IMX_IOMUXC_LCD1_DATA17_ALT;

typedef enum {
   IMX_IOMUXC_LCD1_DATA18_ALT0_LCD1_DATA18 = 0,
   IMX_IOMUXC_LCD1_DATA18_ALT1_EIM_ADDR18 = 1,
   IMX_IOMUXC_LCD1_DATA18_ALT2_ARM_M4_EVENTO = 2,
   IMX_IOMUXC_LCD1_DATA18_ALT3_ARM_A9_EVENTO = 3,
   IMX_IOMUXC_LCD1_DATA18_ALT4_CSI1_DATA15 = 4,
   IMX_IOMUXC_LCD1_DATA18_ALT5_GPIO3_IO19 = 5,
   IMX_IOMUXC_LCD1_DATA18_ALT6_SRC_BOOT_CFG26 = 6,
} IMX_IOMUXC_LCD1_DATA18_ALT;

typedef enum {
   IMX_IOMUXC_LCD1_DATA19_ALT0_LCD1_DATA19 = 0,
   IMX_IOMUXC_LCD1_DATA19_ALT1_EIM_ADDR19 = 1,
   IMX_IOMUXC_LCD1_DATA19_ALT2_ARM_M4_TRACE_SWO = 2,
   IMX_IOMUXC_LCD1_DATA19_ALT4_CSI1_DATA14 = 4,
   IMX_IOMUXC_LCD1_DATA19_ALT5_GPIO3_IO20 = 5,
   IMX_IOMUXC_LCD1_DATA19_ALT6_SRC_BOOT_CFG27 = 6,
} IMX_IOMUXC_LCD1_DATA19_ALT;

typedef enum {
   IMX_IOMUXC_LCD1_DATA20_ALT0_LCD1_DATA20 = 0,
   IMX_IOMUXC_LCD1_DATA20_ALT1_EIM_ADDR20 = 1,
   IMX_IOMUXC_LCD1_DATA20_ALT2_PWM8_OUT = 2,
   IMX_IOMUXC_LCD1_DATA20_ALT3_ENET1_1588_EVENT2_OUT = 3,
   IMX_IOMUXC_LCD1_DATA20_ALT4_CSI1_DATA13 = 4,
   IMX_IOMUXC_LCD1_DATA20_ALT5_GPIO3_IO21 = 5,
   IMX_IOMUXC_LCD1_DATA20_ALT6_SRC_BOOT_CFG28 = 6,
} IMX_IOMUXC_LCD1_DATA20_ALT;

typedef enum {
   IMX_IOMUXC_LCD1_DATA21_ALT0_LCD1_DATA21 = 0,
   IMX_IOMUXC_LCD1_DATA21_ALT1_EIM_ADDR21 = 1,
   IMX_IOMUXC_LCD1_DATA21_ALT2_PWM7_OUT = 2,
   IMX_IOMUXC_LCD1_DATA21_ALT3_ENET1_1588_EVENT3_OUT = 3,
   IMX_IOMUXC_LCD1_DATA21_ALT4_CSI1_DATA12 = 4,
   IMX_IOMUXC_LCD1_DATA21_ALT5_GPIO3_IO22 = 5,
   IMX_IOMUXC_LCD1_DATA21_ALT6_SRC_BOOT_CFG29 = 6,
} IMX_IOMUXC_LCD1_DATA21_ALT;

typedef enum {
   IMX_IOMUXC_LCD1_DATA22_ALT0_LCD1_DATA22 = 0,
   IMX_IOMUXC_LCD1_DATA22_ALT1_EIM_ADDR22 = 1,
   IMX_IOMUXC_LCD1_DATA22_ALT2_PWM6_OUT = 2,
   IMX_IOMUXC_LCD1_DATA22_ALT3_ENET2_1588_EVENT2_OUT = 3,
   IMX_IOMUXC_LCD1_DATA22_ALT4_CSI1_DATA11 = 4,
   IMX_IOMUXC_LCD1_DATA22_ALT5_GPIO3_IO23 = 5,
   IMX_IOMUXC_LCD1_DATA22_ALT6_SRC_BOOT_CFG30 = 6,
} IMX_IOMUXC_LCD1_DATA22_ALT;

typedef enum {
   IMX_IOMUXC_LCD1_DATA23_ALT0_LCD1_DATA23 = 0,
   IMX_IOMUXC_LCD1_DATA23_ALT1_EIM_ADDR23 = 1,
   IMX_IOMUXC_LCD1_DATA23_ALT2_PWM5_OUT = 2,
   IMX_IOMUXC_LCD1_DATA23_ALT3_ENET2_1588_EVENT3_OUT = 3,
   IMX_IOMUXC_LCD1_DATA23_ALT4_CSI1_DATA10 = 4,
   IMX_IOMUXC_LCD1_DATA23_ALT5_GPIO3_IO24 = 5,
   IMX_IOMUXC_LCD1_DATA23_ALT6_SRC_BOOT_CFG31 = 6,
} IMX_IOMUXC_LCD1_DATA23_ALT;

typedef enum {
   IMX_IOMUXC_LCD1_ENABLE_ALT0_LCD1_ENABLE = 0,
   IMX_IOMUXC_LCD1_ENABLE_ALT1_LCD1_RD_E = 1,
   IMX_IOMUXC_LCD1_ENABLE_ALT2_AUD3_TXC = 2,
   IMX_IOMUXC_LCD1_ENABLE_ALT3_ENET1_1588_EVENT3_IN = 3,
   IMX_IOMUXC_LCD1_ENABLE_ALT4_CSI1_DATA17 = 4,
   IMX_IOMUXC_LCD1_ENABLE_ALT5_GPIO3_IO25 = 5,
   IMX_IOMUXC_LCD1_ENABLE_ALT6_SD1_CD_B = 6,
} IMX_IOMUXC_LCD1_ENABLE_ALT;

typedef enum {
   IMX_IOMUXC_LCD1_HSYNC_ALT0_LCD1_HSYNC = 0,
   IMX_IOMUXC_LCD1_HSYNC_ALT1_LCD1_RS = 1,
   IMX_IOMUXC_LCD1_HSYNC_ALT2_AUD3_TXD = 2,
   IMX_IOMUXC_LCD1_HSYNC_ALT3_ENET2_1588_EVENT2_IN = 3,
   IMX_IOMUXC_LCD1_HSYNC_ALT4_CSI1_DATA18 = 4,
   IMX_IOMUXC_LCD1_HSYNC_ALT5_GPIO3_IO26 = 5,
   IMX_IOMUXC_LCD1_HSYNC_ALT6_SD2_WP = 6,
} IMX_IOMUXC_LCD1_HSYNC_ALT;

typedef enum {
   IMX_IOMUXC_LCD1_RESET_ALT0_LCD1_RESET = 0,
   IMX_IOMUXC_LCD1_RESET_ALT1_LCD1_CS = 1,
   IMX_IOMUXC_LCD1_RESET_ALT2_AUD3_RXD = 2,
   IMX_IOMUXC_LCD1_RESET_ALT3_ARM_A9_EVENTI = 3,
   IMX_IOMUXC_LCD1_RESET_ALT4_ARM_M4_EVENTI = 4,
   IMX_IOMUXC_LCD1_RESET_ALT5_GPIO3_IO27 = 5,
   IMX_IOMUXC_LCD1_RESET_ALT6_CCM_PMIC_READY = 6,
} IMX_IOMUXC_LCD1_RESET_ALT;

typedef enum {
   IMX_IOMUXC_LCD1_VSYNC_ALT0_LCD1_VSYNC = 0,
   IMX_IOMUXC_LCD1_VSYNC_ALT1_LCD1_BUSY = 1,
   IMX_IOMUXC_LCD1_VSYNC_ALT2_AUD3_TXFS = 2,
   IMX_IOMUXC_LCD1_VSYNC_ALT3_ENET2_1588_EVENT3_IN = 3,
   IMX_IOMUXC_LCD1_VSYNC_ALT4_CSI1_DATA19 = 4,
   IMX_IOMUXC_LCD1_VSYNC_ALT5_GPIO3_IO28 = 5,
   IMX_IOMUXC_LCD1_VSYNC_ALT6_SD2_CD_B = 6,
} IMX_IOMUXC_LCD1_VSYNC_ALT;

typedef enum {
   IMX_IOMUXC_NAND_ALE_ALT0_NAND_ALE = 0,
   IMX_IOMUXC_NAND_ALE_ALT1_I2C3_SDA = 1,
   IMX_IOMUXC_NAND_ALE_ALT2_QSPI2A_SS0_B = 2,
   IMX_IOMUXC_NAND_ALE_ALT3_ECSPI2_SS0 = 3,
   IMX_IOMUXC_NAND_ALE_ALT4_ESAI_TX3_RX2 = 4,
   IMX_IOMUXC_NAND_ALE_ALT5_GPIO4_IO00 = 5,
   IMX_IOMUXC_NAND_ALE_ALT6_EIM_CS0_B = 6,
} IMX_IOMUXC_NAND_ALE_ALT;

typedef enum {
   IMX_IOMUXC_NAND_CE0_B_ALT0_NAND_CE0_B = 0,
   IMX_IOMUXC_NAND_CE0_B_ALT1_SD2_VSELECT = 1,
   IMX_IOMUXC_NAND_CE0_B_ALT2_QSPI2A_DATA2 = 2,
   IMX_IOMUXC_NAND_CE0_B_ALT3_AUD4_TXC = 3,
   IMX_IOMUXC_NAND_CE0_B_ALT4_ESAI_TX_CLK = 4,
   IMX_IOMUXC_NAND_CE0_B_ALT5_GPIO4_IO01 = 5,
   IMX_IOMUXC_NAND_CE0_B_ALT6_EIM_LBA_B = 6,
} IMX_IOMUXC_NAND_CE0_B_ALT;

typedef enum {
   IMX_IOMUXC_NAND_CE1_B_ALT0_NAND_CE1_B = 0,
   IMX_IOMUXC_NAND_CE1_B_ALT1_SD3_RESET_B = 1,
   IMX_IOMUXC_NAND_CE1_B_ALT2_QSPI2A_DATA3 = 2,
   IMX_IOMUXC_NAND_CE1_B_ALT3_AUD4_TXD = 3,
   IMX_IOMUXC_NAND_CE1_B_ALT4_ESAI_TX0 = 4,
   IMX_IOMUXC_NAND_CE1_B_ALT5_GPIO4_IO02 = 5,
   IMX_IOMUXC_NAND_CE1_B_ALT6_EIM_OE = 6,
} IMX_IOMUXC_NAND_CE1_B_ALT;

typedef enum {
   IMX_IOMUXC_NAND_CLE_ALT0_NAND_CLE = 0,
   IMX_IOMUXC_NAND_CLE_ALT1_I2C3_SCL = 1,
   IMX_IOMUXC_NAND_CLE_ALT2_QSPI2A_SCLK = 2,
   IMX_IOMUXC_NAND_CLE_ALT3_ECSPI2_SCLK = 3,
   IMX_IOMUXC_NAND_CLE_ALT4_ESAI_TX2_RX3 = 4,
   IMX_IOMUXC_NAND_CLE_ALT5_GPIO4_IO03 = 5,
   IMX_IOMUXC_NAND_CLE_ALT6_EIM_BCLK = 6,
} IMX_IOMUXC_NAND_CLE_ALT;

typedef enum {
   IMX_IOMUXC_NAND_DATA00_ALT0_NAND_DATA00 = 0,
   IMX_IOMUXC_NAND_DATA00_ALT1_SD1_DATA4 = 1,
   IMX_IOMUXC_NAND_DATA00_ALT2_QSPI2B_DATA1 = 2,
   IMX_IOMUXC_NAND_DATA00_ALT3_ECSPI5_MISO = 3,
   IMX_IOMUXC_NAND_DATA00_ALT4_ESAI_RX_CLK = 4,
   IMX_IOMUXC_NAND_DATA00_ALT5_GPIO4_IO04 = 5,
   IMX_IOMUXC_NAND_DATA00_ALT6_EIM_AD00 = 6,
} IMX_IOMUXC_NAND_DATA00_ALT;

typedef enum {
   IMX_IOMUXC_NAND_DATA01_ALT0_NAND_DATA01 = 0,
   IMX_IOMUXC_NAND_DATA01_ALT1_SD1_DATA5 = 1,
   IMX_IOMUXC_NAND_DATA01_ALT2_QSPI2B_DATA0 = 2,
   IMX_IOMUXC_NAND_DATA01_ALT3_ECSPI5_MOSI = 3,
   IMX_IOMUXC_NAND_DATA01_ALT4_ESAI_RX_FS = 4,
   IMX_IOMUXC_NAND_DATA01_ALT5_GPIO4_IO05 = 5,
   IMX_IOMUXC_NAND_DATA01_ALT6_EIM_AD01 = 6,
} IMX_IOMUXC_NAND_DATA01_ALT;

typedef enum {
   IMX_IOMUXC_NAND_DATA02_ALT0_NAND_DATA02 = 0,
   IMX_IOMUXC_NAND_DATA02_ALT1_SD1_DATA6 = 1,
   IMX_IOMUXC_NAND_DATA02_ALT2_QSPI2B_SCLK = 2,
   IMX_IOMUXC_NAND_DATA02_ALT3_ECSPI5_SCLK = 3,
   IMX_IOMUXC_NAND_DATA02_ALT4_ESAI_TX_HF_CLK = 4,
   IMX_IOMUXC_NAND_DATA02_ALT5_GPIO4_IO06 = 5,
   IMX_IOMUXC_NAND_DATA02_ALT6_EIM_AD02 = 6,
} IMX_IOMUXC_NAND_DATA02_ALT;

typedef enum {
   IMX_IOMUXC_NAND_DATA03_ALT0_NAND_DATA03 = 0,
   IMX_IOMUXC_NAND_DATA03_ALT1_SD1_DATA7 = 1,
   IMX_IOMUXC_NAND_DATA03_ALT2_QSPI2B_SS0_B = 2,
   IMX_IOMUXC_NAND_DATA03_ALT3_ECSPI5_SS0 = 3,
   IMX_IOMUXC_NAND_DATA03_ALT4_ESAI_RX_HF_CLK = 4,
   IMX_IOMUXC_NAND_DATA03_ALT5_GPIO4_IO07 = 5,
   IMX_IOMUXC_NAND_DATA03_ALT6_EIM_AD03 = 6,
} IMX_IOMUXC_NAND_DATA03_ALT;

typedef enum {
   IMX_IOMUXC_NAND_DATA04_ALT0_NAND_DATA04 = 0,
   IMX_IOMUXC_NAND_DATA04_ALT1_SD2_DATA4 = 1,
   IMX_IOMUXC_NAND_DATA04_ALT2_QSPI2B_SS1_B = 2,
   IMX_IOMUXC_NAND_DATA04_ALT3_UART3_RTS_B = 3,
   IMX_IOMUXC_NAND_DATA04_ALT4_AUD4_RXFS = 4,
   IMX_IOMUXC_NAND_DATA04_ALT5_GPIO4_IO08 = 5,
   IMX_IOMUXC_NAND_DATA04_ALT6_EIM_AD04 = 6,
} IMX_IOMUXC_NAND_DATA04_ALT;

typedef enum {
   IMX_IOMUXC_NAND_DATA05_ALT0_NAND_DATA05 = 0,
   IMX_IOMUXC_NAND_DATA05_ALT1_SD2_DATA5 = 1,
   IMX_IOMUXC_NAND_DATA05_ALT2_QSPI2B_DQS = 2,
   IMX_IOMUXC_NAND_DATA05_ALT3_UART3_CTS_B = 3,
   IMX_IOMUXC_NAND_DATA05_ALT4_AUD4_RXC = 4,
   IMX_IOMUXC_NAND_DATA05_ALT5_GPIO4_IO09 = 5,
   IMX_IOMUXC_NAND_DATA05_ALT6_EIM_AD05 = 6,
} IMX_IOMUXC_NAND_DATA05_ALT;

typedef enum {
   IMX_IOMUXC_NAND_DATA06_ALT0_NAND_DATA06 = 0,
   IMX_IOMUXC_NAND_DATA06_ALT1_SD2_DATA6 = 1,
   IMX_IOMUXC_NAND_DATA06_ALT2_QSPI2A_SS1_B = 2,
   IMX_IOMUXC_NAND_DATA06_ALT3_UART3_RX_DATA = 3,
   IMX_IOMUXC_NAND_DATA06_ALT4_PWM3_OUT = 4,
   IMX_IOMUXC_NAND_DATA06_ALT5_GPIO4_IO10 = 5,
   IMX_IOMUXC_NAND_DATA06_ALT6_EIM_AD06 = 6,
} IMX_IOMUXC_NAND_DATA06_ALT;

typedef enum {
   IMX_IOMUXC_NAND_DATA07_ALT0_NAND_DATA07 = 0,
   IMX_IOMUXC_NAND_DATA07_ALT1_SD2_DATA7 = 1,
   IMX_IOMUXC_NAND_DATA07_ALT2_QSPI2A_DQS = 2,
   IMX_IOMUXC_NAND_DATA07_ALT3_UART3_TX_DATA = 3,
   IMX_IOMUXC_NAND_DATA07_ALT4_PWM4_OUT = 4,
   IMX_IOMUXC_NAND_DATA07_ALT5_GPIO4_IO11 = 5,
   IMX_IOMUXC_NAND_DATA07_ALT6_EIM_AD07 = 6,
} IMX_IOMUXC_NAND_DATA07_ALT;

typedef enum {
   IMX_IOMUXC_NAND_RE_B_ALT0_NAND_RE_B = 0,
   IMX_IOMUXC_NAND_RE_B_ALT1_SD2_RESET_B = 1,
   IMX_IOMUXC_NAND_RE_B_ALT2_QSPI2B_DATA3 = 2,
   IMX_IOMUXC_NAND_RE_B_ALT3_AUD4_TXFS = 3,
   IMX_IOMUXC_NAND_RE_B_ALT4_ESAI_TX_FS = 4,
   IMX_IOMUXC_NAND_RE_B_ALT5_GPIO4_IO12 = 5,
   IMX_IOMUXC_NAND_RE_B_ALT6_EIM_RW = 6,
} IMX_IOMUXC_NAND_RE_B_ALT;

typedef enum {
   IMX_IOMUXC_NAND_READY_B_ALT0_NAND_READY_B = 0,
   IMX_IOMUXC_NAND_READY_B_ALT1_SD1_VSELECT = 1,
   IMX_IOMUXC_NAND_READY_B_ALT2_QSPI2A_DATA1 = 2,
   IMX_IOMUXC_NAND_READY_B_ALT3_ECSPI2_MISO = 3,
   IMX_IOMUXC_NAND_READY_B_ALT4_ESAI_TX1 = 4,
   IMX_IOMUXC_NAND_READY_B_ALT5_GPIO4_IO13 = 5,
   IMX_IOMUXC_NAND_READY_B_ALT6_EIM_EB1_B = 6,
} IMX_IOMUXC_NAND_READY_B_ALT;

typedef enum {
   IMX_IOMUXC_NAND_WE_B_ALT0_NAND_WE_B = 0,
   IMX_IOMUXC_NAND_WE_B_ALT1_SD4_VSELECT = 1,
   IMX_IOMUXC_NAND_WE_B_ALT2_QSPI2B_DATA2 = 2,
   IMX_IOMUXC_NAND_WE_B_ALT3_AUD4_RXD = 3,
   IMX_IOMUXC_NAND_WE_B_ALT4_ESAI_TX5_RX0 = 4,
   IMX_IOMUXC_NAND_WE_B_ALT5_GPIO4_IO14 = 5,
   IMX_IOMUXC_NAND_WE_B_ALT6_EIM_WAIT = 6,
} IMX_IOMUXC_NAND_WE_B_ALT;

typedef enum {
   IMX_IOMUXC_NAND_WP_B_ALT0_NAND_WP_B = 0,
   IMX_IOMUXC_NAND_WP_B_ALT1_SD1_RESET_B = 1,
   IMX_IOMUXC_NAND_WP_B_ALT2_QSPI2A_DATA0 = 2,
   IMX_IOMUXC_NAND_WP_B_ALT3_ECSPI2_MOSI = 3,
   IMX_IOMUXC_NAND_WP_B_ALT4_ESAI_TX4_RX1 = 4,
   IMX_IOMUXC_NAND_WP_B_ALT5_GPIO4_IO15 = 5,
   IMX_IOMUXC_NAND_WP_B_ALT6_EIM_EB0_B = 6,
} IMX_IOMUXC_NAND_WP_B_ALT;

typedef enum {
   IMX_IOMUXC_QSPI1A_DATA0_ALT0_QSPI1A_DATA0 = 0,
   IMX_IOMUXC_QSPI1A_DATA0_ALT1_USB_OTG2_OC = 1,
   IMX_IOMUXC_QSPI1A_DATA0_ALT2_ECSPI1_MOSI = 2,
   IMX_IOMUXC_QSPI1A_DATA0_ALT3_ESAI_TX4_RX1 = 3,
   IMX_IOMUXC_QSPI1A_DATA0_ALT4_CSI1_DATA14 = 4,
   IMX_IOMUXC_QSPI1A_DATA0_ALT5_GPIO4_IO16 = 5,
   IMX_IOMUXC_QSPI1A_DATA0_ALT6_EIM_DATA06 = 6,
} IMX_IOMUXC_QSPI1A_DATA0_ALT;

typedef enum {
   IMX_IOMUXC_QSPI1A_DATA1_ALT0_QSPI1A_DATA1 = 0,
   IMX_IOMUXC_QSPI1A_DATA1_ALT1_USB_OTG1_ID = 1,
   IMX_IOMUXC_QSPI1A_DATA1_ALT2_ECSPI1_MISO = 2,
   IMX_IOMUXC_QSPI1A_DATA1_ALT3_ESAI_TX1 = 3,
   IMX_IOMUXC_QSPI1A_DATA1_ALT4_CSI1_DATA13 = 4,
   IMX_IOMUXC_QSPI1A_DATA1_ALT5_GPIO4_IO17 = 5,
   IMX_IOMUXC_QSPI1A_DATA1_ALT6_EIM_DATA05 = 6,
} IMX_IOMUXC_QSPI1A_DATA1_ALT;

typedef enum {
   IMX_IOMUXC_QSPI1A_DATA2_ALT0_QSPI1A_DATA2 = 0,
   IMX_IOMUXC_QSPI1A_DATA2_ALT1_USB_OTG1_PWR = 1,
   IMX_IOMUXC_QSPI1A_DATA2_ALT2_ECSPI5_SS1 = 2,
   IMX_IOMUXC_QSPI1A_DATA2_ALT3_ESAI_TX_CLK = 3,
   IMX_IOMUXC_QSPI1A_DATA2_ALT4_CSI1_DATA12 = 4,
   IMX_IOMUXC_QSPI1A_DATA2_ALT5_GPIO4_IO18 = 5,
   IMX_IOMUXC_QSPI1A_DATA2_ALT6_EIM_DATA04 = 6,
} IMX_IOMUXC_QSPI1A_DATA2_ALT;

typedef enum {
   IMX_IOMUXC_QSPI1A_DATA3_ALT0_QSPI1A_DATA3 = 0,
   IMX_IOMUXC_QSPI1A_DATA3_ALT1_USB_OTG1_OC = 1,
   IMX_IOMUXC_QSPI1A_DATA3_ALT2_ECSPI5_SS2 = 2,
   IMX_IOMUXC_QSPI1A_DATA3_ALT3_ESAI_TX0 = 3,
   IMX_IOMUXC_QSPI1A_DATA3_ALT4_CSI1_DATA11 = 4,
   IMX_IOMUXC_QSPI1A_DATA3_ALT5_GPIO4_IO19 = 5,
   IMX_IOMUXC_QSPI1A_DATA3_ALT6_EIM_DATA03 = 6,
} IMX_IOMUXC_QSPI1A_DATA3_ALT;

typedef enum {
   IMX_IOMUXC_QSPI1A_DQS_ALT0_QSPI1A_DQS = 0,
   IMX_IOMUXC_QSPI1A_DQS_ALT1_CAN2_TX = 1,
   IMX_IOMUXC_QSPI1A_DQS_ALT3_ECSPI5_MOSI = 3,
   IMX_IOMUXC_QSPI1A_DQS_ALT4_CSI1_DATA15 = 4,
   IMX_IOMUXC_QSPI1A_DQS_ALT5_GPIO4_IO20 = 5,
   IMX_IOMUXC_QSPI1A_DQS_ALT6_EIM_DATA07 = 6,
} IMX_IOMUXC_QSPI1A_DQS_ALT;

typedef enum {
   IMX_IOMUXC_QSPI1A_SCLK_ALT0_QSPI1A_SCLK = 0,
   IMX_IOMUXC_QSPI1A_SCLK_ALT1_USB_OTG2_ID = 1,
   IMX_IOMUXC_QSPI1A_SCLK_ALT2_ECSPI1_SCLK = 2,
   IMX_IOMUXC_QSPI1A_SCLK_ALT3_ESAI_TX2_RX3 = 3,
   IMX_IOMUXC_QSPI1A_SCLK_ALT4_CSI1_DATA01 = 4,
   IMX_IOMUXC_QSPI1A_SCLK_ALT5_GPIO4_IO21 = 5,
   IMX_IOMUXC_QSPI1A_SCLK_ALT6_EIM_DATA00 = 6,
} IMX_IOMUXC_QSPI1A_SCLK_ALT;

typedef enum {
   IMX_IOMUXC_QSPI1A_SS0_B_ALT0_QSPI1A_SS0_B = 0,
   IMX_IOMUXC_QSPI1A_SS0_B_ALT1_USB_OTG2_PWR = 1,
   IMX_IOMUXC_QSPI1A_SS0_B_ALT2_ECSPI1_SS0 = 2,
   IMX_IOMUXC_QSPI1A_SS0_B_ALT3_ESAI_TX3_RX2 = 3,
   IMX_IOMUXC_QSPI1A_SS0_B_ALT4_CSI1_DATA00 = 4,
   IMX_IOMUXC_QSPI1A_SS0_B_ALT5_GPIO4_IO22 = 5,
   IMX_IOMUXC_QSPI1A_SS0_B_ALT6_EIM_DATA01 = 6,
} IMX_IOMUXC_QSPI1A_SS0_B_ALT;

typedef enum {
   IMX_IOMUXC_QSPI1A_SS1_B_ALT0_QSPI1A_SS1_B = 0,
   IMX_IOMUXC_QSPI1A_SS1_B_ALT1_CAN1_RX = 1,
   IMX_IOMUXC_QSPI1A_SS1_B_ALT3_ECSPI5_MISO = 3,
   IMX_IOMUXC_QSPI1A_SS1_B_ALT4_CSI1_DATA10 = 4,
   IMX_IOMUXC_QSPI1A_SS1_B_ALT5_GPIO4_IO23 = 5,
   IMX_IOMUXC_QSPI1A_SS1_B_ALT6_EIM_DATA02 = 6,
} IMX_IOMUXC_QSPI1A_SS1_B_ALT;

typedef enum {
   IMX_IOMUXC_QSPI1B_DATA0_ALT0_QSPI1B_DATA0 = 0,
   IMX_IOMUXC_QSPI1B_DATA0_ALT1_UART3_CTS_B = 1,
   IMX_IOMUXC_QSPI1B_DATA0_ALT2_ECSPI3_MOSI = 2,
   IMX_IOMUXC_QSPI1B_DATA0_ALT3_ESAI_RX_FS = 3,
   IMX_IOMUXC_QSPI1B_DATA0_ALT4_CSI1_DATA22 = 4,
   IMX_IOMUXC_QSPI1B_DATA0_ALT5_GPIO4_IO24 = 5,
   IMX_IOMUXC_QSPI1B_DATA0_ALT6_EIM_DATA14 = 6,
} IMX_IOMUXC_QSPI1B_DATA0_ALT;

typedef enum {
   IMX_IOMUXC_QSPI1B_DATA1_ALT0_QSPI1B_DATA1 = 0,
   IMX_IOMUXC_QSPI1B_DATA1_ALT1_UART3_RTS_B = 1,
   IMX_IOMUXC_QSPI1B_DATA1_ALT2_ECSPI3_MISO = 2,
   IMX_IOMUXC_QSPI1B_DATA1_ALT3_ESAI_RX_CLK = 3,
   IMX_IOMUXC_QSPI1B_DATA1_ALT4_CSI1_DATA21 = 4,
   IMX_IOMUXC_QSPI1B_DATA1_ALT5_GPIO4_IO25 = 5,
   IMX_IOMUXC_QSPI1B_DATA1_ALT6_EIM_DATA13 = 6,
} IMX_IOMUXC_QSPI1B_DATA1_ALT;

typedef enum {
   IMX_IOMUXC_QSPI1B_DATA2_ALT0_QSPI1B_DATA2 = 0,
   IMX_IOMUXC_QSPI1B_DATA2_ALT1_I2C2_SDA = 1,
   IMX_IOMUXC_QSPI1B_DATA2_ALT2_ECSPI5_RDY = 2,
   IMX_IOMUXC_QSPI1B_DATA2_ALT3_ESAI_TX5_RX0 = 3,
   IMX_IOMUXC_QSPI1B_DATA2_ALT4_CSI1_DATA20 = 4,
   IMX_IOMUXC_QSPI1B_DATA2_ALT5_GPIO4_IO26 = 5,
   IMX_IOMUXC_QSPI1B_DATA2_ALT6_EIM_DATA12 = 6,
} IMX_IOMUXC_QSPI1B_DATA2_ALT;

typedef enum {
   IMX_IOMUXC_QSPI1B_DATA3_ALT0_QSPI1B_DATA3 = 0,
   IMX_IOMUXC_QSPI1B_DATA3_ALT1_I2C2_SCL = 1,
   IMX_IOMUXC_QSPI1B_DATA3_ALT2_ECSPI5_SS3 = 2,
   IMX_IOMUXC_QSPI1B_DATA3_ALT3_ESAI_TX_FS = 3,
   IMX_IOMUXC_QSPI1B_DATA3_ALT4_CSI1_DATA19 = 4,
   IMX_IOMUXC_QSPI1B_DATA3_ALT5_GPIO4_IO27 = 5,
   IMX_IOMUXC_QSPI1B_DATA3_ALT6_EIM_DATA11 = 6,
} IMX_IOMUXC_QSPI1B_DATA3_ALT;

typedef enum {
   IMX_IOMUXC_QSPI1B_DQS_ALT0_QSPI1B_DQS = 0,
   IMX_IOMUXC_QSPI1B_DQS_ALT1_CAN1_TX = 1,
   IMX_IOMUXC_QSPI1B_DQS_ALT3_ECSPI5_SS0 = 3,
   IMX_IOMUXC_QSPI1B_DQS_ALT4_CSI1_DATA23 = 4,
   IMX_IOMUXC_QSPI1B_DQS_ALT5_GPIO4_IO28 = 5,
   IMX_IOMUXC_QSPI1B_DQS_ALT6_EIM_DATA15 = 6,
} IMX_IOMUXC_QSPI1B_DQS_ALT;

typedef enum {
   IMX_IOMUXC_QSPI1B_SCLK_ALT0_QSPI1B_SCLK = 0,
   IMX_IOMUXC_QSPI1B_SCLK_ALT1_UART3_RX_DATA = 1,
   IMX_IOMUXC_QSPI1B_SCLK_ALT2_ECSPI3_SCLK = 2,
   IMX_IOMUXC_QSPI1B_SCLK_ALT3_ESAI_RX_HF_CLK = 3,
   IMX_IOMUXC_QSPI1B_SCLK_ALT4_CSI1_DATA16 = 4,
   IMX_IOMUXC_QSPI1B_SCLK_ALT5_GPIO4_IO29 = 5,
   IMX_IOMUXC_QSPI1B_SCLK_ALT6_EIM_DATA08 = 6,
} IMX_IOMUXC_QSPI1B_SCLK_ALT;

typedef enum {
   IMX_IOMUXC_QSPI1B_SS0_B_ALT0_QSPI1B_SS0_B = 0,
   IMX_IOMUXC_QSPI1B_SS0_B_ALT1_UART3_TX_DATA = 1,
   IMX_IOMUXC_QSPI1B_SS0_B_ALT2_ECSPI3_SS0 = 2,
   IMX_IOMUXC_QSPI1B_SS0_B_ALT3_ESAI_TX_HF_CLK = 3,
   IMX_IOMUXC_QSPI1B_SS0_B_ALT4_CSI1_DATA17 = 4,
   IMX_IOMUXC_QSPI1B_SS0_B_ALT5_GPIO4_IO30 = 5,
   IMX_IOMUXC_QSPI1B_SS0_B_ALT6_EIM_DATA09 = 6,
} IMX_IOMUXC_QSPI1B_SS0_B_ALT;

typedef enum {
   IMX_IOMUXC_QSPI1B_SS1_B_ALT0_QSPI1B_SS1_B = 0,
   IMX_IOMUXC_QSPI1B_SS1_B_ALT1_CAN2_RX = 1,
   IMX_IOMUXC_QSPI1B_SS1_B_ALT3_ECSPI5_SCLK = 3,
   IMX_IOMUXC_QSPI1B_SS1_B_ALT4_CSI1_DATA18 = 4,
   IMX_IOMUXC_QSPI1B_SS1_B_ALT5_GPIO4_IO31 = 5,
   IMX_IOMUXC_QSPI1B_SS1_B_ALT6_EIM_DATA10 = 6,
} IMX_IOMUXC_QSPI1B_SS1_B_ALT;

typedef enum {
   IMX_IOMUXC_RGMII1_RD0_ALT0_ENET1_RX_DATA0 = 0,
   IMX_IOMUXC_RGMII1_RD0_ALT5_GPIO5_IO00 = 5,
   IMX_IOMUXC_RGMII1_RD0_ALT6_CSI2_DATA10 = 6,
} IMX_IOMUXC_RGMII1_RD0_ALT;

typedef enum {
   IMX_IOMUXC_RGMII1_RD1_ALT0_ENET1_RX_DATA1 = 0,
   IMX_IOMUXC_RGMII1_RD1_ALT5_GPIO5_IO01 = 5,
   IMX_IOMUXC_RGMII1_RD1_ALT6_CSI2_DATA11 = 6,
} IMX_IOMUXC_RGMII1_RD1_ALT;

typedef enum {
   IMX_IOMUXC_RGMII1_RD2_ALT0_ENET1_RX_DATA2 = 0,
   IMX_IOMUXC_RGMII1_RD2_ALT5_GPIO5_IO02 = 5,
   IMX_IOMUXC_RGMII1_RD2_ALT6_CSI2_DATA12 = 6,
} IMX_IOMUXC_RGMII1_RD2_ALT;

typedef enum {
   IMX_IOMUXC_RGMII1_RD3_ALT0_ENET1_RX_DATA3 = 0,
   IMX_IOMUXC_RGMII1_RD3_ALT5_GPIO5_IO03 = 5,
   IMX_IOMUXC_RGMII1_RD3_ALT6_CSI2_DATA13 = 6,
} IMX_IOMUXC_RGMII1_RD3_ALT;

typedef enum {
   IMX_IOMUXC_RGMII1_RX_CTL_ALT0_ENET1_RX_EN = 0,
   IMX_IOMUXC_RGMII1_RX_CTL_ALT5_GPIO5_IO04 = 5,
   IMX_IOMUXC_RGMII1_RX_CTL_ALT6_CSI2_DATA14 = 6,
} IMX_IOMUXC_RGMII1_RX_CTL_ALT;

typedef enum {
   IMX_IOMUXC_RGMII1_RXC_ALT0_ENET1_RGMII_RXC = 0,
   IMX_IOMUXC_RGMII1_RXC_ALT1_ENET1_RX_ER = 1,
   IMX_IOMUXC_RGMII1_RXC_ALT5_GPIO5_IO05 = 5,
   IMX_IOMUXC_RGMII1_RXC_ALT6_CSI2_DATA15 = 6,
} IMX_IOMUXC_RGMII1_RXC_ALT;

typedef enum {
   IMX_IOMUXC_RGMII1_TD0_ALT0_ENET1_TX_DATA0 = 0,
   IMX_IOMUXC_RGMII1_TD0_ALT2_SAI2_RX_SYNC = 2,
   IMX_IOMUXC_RGMII1_TD0_ALT5_GPIO5_IO06 = 5,
   IMX_IOMUXC_RGMII1_TD0_ALT6_CSI2_DATA16 = 6,
} IMX_IOMUXC_RGMII1_TD0_ALT;

typedef enum {
   IMX_IOMUXC_RGMII1_TD1_ALT0_ENET1_TX_DATA1 = 0,
   IMX_IOMUXC_RGMII1_TD1_ALT2_SAI2_RX_BCLK = 2,
   IMX_IOMUXC_RGMII1_TD1_ALT5_GPIO5_IO07 = 5,
   IMX_IOMUXC_RGMII1_TD1_ALT6_CSI2_DATA17 = 6,
} IMX_IOMUXC_RGMII1_TD1_ALT;

typedef enum {
   IMX_IOMUXC_RGMII1_TD2_ALT0_ENET1_TX_DATA2 = 0,
   IMX_IOMUXC_RGMII1_TD2_ALT2_SAI2_TX_SYNC = 2,
   IMX_IOMUXC_RGMII1_TD2_ALT5_GPIO5_IO08 = 5,
   IMX_IOMUXC_RGMII1_TD2_ALT6_CSI2_DATA18 = 6,
} IMX_IOMUXC_RGMII1_TD2_ALT;

typedef enum {
   IMX_IOMUXC_RGMII1_TD3_ALT0_ENET1_TX_DATA3 = 0,
   IMX_IOMUXC_RGMII1_TD3_ALT2_SAI2_TX_BCLK = 2,
   IMX_IOMUXC_RGMII1_TD3_ALT5_GPIO5_IO09 = 5,
   IMX_IOMUXC_RGMII1_TD3_ALT6_CSI2_DATA19 = 6,
} IMX_IOMUXC_RGMII1_TD3_ALT;

typedef enum {
   IMX_IOMUXC_RGMII1_TX_CTL_ALT0_ENET1_TX_EN = 0,
   IMX_IOMUXC_RGMII1_TX_CTL_ALT2_SAI2_RX_DATA0 = 2,
   IMX_IOMUXC_RGMII1_TX_CTL_ALT5_GPIO5_IO10 = 5,
   IMX_IOMUXC_RGMII1_TX_CTL_ALT6_CSI2_DATA00 = 6,
} IMX_IOMUXC_RGMII1_TX_CTL_ALT;

typedef enum {
   IMX_IOMUXC_RGMII1_TXC_ALT0_ENET1_RGMII_TXC = 0,
   IMX_IOMUXC_RGMII1_TXC_ALT1_ENET1_TX_ER = 1,
   IMX_IOMUXC_RGMII1_TXC_ALT2_SAI2_TX_DATA0 = 2,
   IMX_IOMUXC_RGMII1_TXC_ALT5_GPIO5_IO11 = 5,
   IMX_IOMUXC_RGMII1_TXC_ALT6_CSI2_DATA01 = 6,
} IMX_IOMUXC_RGMII1_TXC_ALT;

typedef enum {
   IMX_IOMUXC_RGMII2_RD0_ALT0_ENET2_RX_DATA0 = 0,
   IMX_IOMUXC_RGMII2_RD0_ALT2_PWM4_OUT = 2,
   IMX_IOMUXC_RGMII2_RD0_ALT5_GPIO5_IO12 = 5,
   IMX_IOMUXC_RGMII2_RD0_ALT6_CSI2_DATA02 = 6,
} IMX_IOMUXC_RGMII2_RD0_ALT;

typedef enum {
   IMX_IOMUXC_RGMII2_RD1_ALT0_ENET2_RX_DATA1 = 0,
   IMX_IOMUXC_RGMII2_RD1_ALT2_PWM3_OUT = 2,
   IMX_IOMUXC_RGMII2_RD1_ALT5_GPIO5_IO13 = 5,
   IMX_IOMUXC_RGMII2_RD1_ALT6_CSI2_DATA03 = 6,
} IMX_IOMUXC_RGMII2_RD1_ALT;

typedef enum {
   IMX_IOMUXC_RGMII2_RD2_ALT0_ENET2_RX_DATA2 = 0,
   IMX_IOMUXC_RGMII2_RD2_ALT2_PWM2_OUT = 2,
   IMX_IOMUXC_RGMII2_RD2_ALT5_GPIO5_IO14 = 5,
   IMX_IOMUXC_RGMII2_RD2_ALT6_CSI2_DATA04 = 6,
} IMX_IOMUXC_RGMII2_RD2_ALT;

typedef enum {
   IMX_IOMUXC_RGMII2_RD3_ALT0_ENET2_RX_DATA3 = 0,
   IMX_IOMUXC_RGMII2_RD3_ALT2_PWM1_OUT = 2,
   IMX_IOMUXC_RGMII2_RD3_ALT5_GPIO5_IO15 = 5,
   IMX_IOMUXC_RGMII2_RD3_ALT6_CSI2_DATA05 = 6,
} IMX_IOMUXC_RGMII2_RD3_ALT;

typedef enum {
   IMX_IOMUXC_RGMII2_RX_CTL_ALT0_ENET2_RX_EN = 0,
   IMX_IOMUXC_RGMII2_RX_CTL_ALT5_GPIO5_IO16 = 5,
   IMX_IOMUXC_RGMII2_RX_CTL_ALT6_CSI2_DATA06 = 6,
} IMX_IOMUXC_RGMII2_RX_CTL_ALT;

typedef enum {
   IMX_IOMUXC_RGMII2_RXC_ALT0_ENET2_RGMII_RXC = 0,
   IMX_IOMUXC_RGMII2_RXC_ALT1_ENET2_RX_ER = 1,
   IMX_IOMUXC_RGMII2_RXC_ALT5_GPIO5_IO17 = 5,
   IMX_IOMUXC_RGMII2_RXC_ALT6_CSI2_DATA07 = 6,
} IMX_IOMUXC_RGMII2_RXC_ALT;

typedef enum {
   IMX_IOMUXC_RGMII2_TD0_ALT0_ENET2_TX_DATA0 = 0,
   IMX_IOMUXC_RGMII2_TD0_ALT2_SAI1_RX_SYNC = 2,
   IMX_IOMUXC_RGMII2_TD0_ALT3_PWM8_OUT = 3,
   IMX_IOMUXC_RGMII2_TD0_ALT5_GPIO5_IO18 = 5,
   IMX_IOMUXC_RGMII2_TD0_ALT6_CSI2_DATA08 = 6,
} IMX_IOMUXC_RGMII2_TD0_ALT;

typedef enum {
   IMX_IOMUXC_RGMII2_TD1_ALT0_ENET2_TX_DATA1 = 0,
   IMX_IOMUXC_RGMII2_TD1_ALT2_SAI1_RX_BCLK = 2,
   IMX_IOMUXC_RGMII2_TD1_ALT3_PWM7_OUT = 3,
   IMX_IOMUXC_RGMII2_TD1_ALT5_GPIO5_IO19 = 5,
   IMX_IOMUXC_RGMII2_TD1_ALT6_CSI2_DATA09 = 6,
} IMX_IOMUXC_RGMII2_TD1_ALT;

typedef enum {
   IMX_IOMUXC_RGMII2_TD2_ALT0_ENET2_TX_DATA2 = 0,
   IMX_IOMUXC_RGMII2_TD2_ALT2_SAI1_TX_SYNC = 2,
   IMX_IOMUXC_RGMII2_TD2_ALT3_PWM6_OUT = 3,
   IMX_IOMUXC_RGMII2_TD2_ALT5_GPIO5_IO20 = 5,
   IMX_IOMUXC_RGMII2_TD2_ALT6_CSI2_VSYNC = 6,
} IMX_IOMUXC_RGMII2_TD2_ALT;

typedef enum {
   IMX_IOMUXC_RGMII2_TD3_ALT0_ENET2_TX_DATA3 = 0,
   IMX_IOMUXC_RGMII2_TD3_ALT2_SAI1_TX_BCLK = 2,
   IMX_IOMUXC_RGMII2_TD3_ALT3_PWM5_OUT = 3,
   IMX_IOMUXC_RGMII2_TD3_ALT5_GPIO5_IO21 = 5,
   IMX_IOMUXC_RGMII2_TD3_ALT6_CSI2_HSYNC = 6,
} IMX_IOMUXC_RGMII2_TD3_ALT;

typedef enum {
   IMX_IOMUXC_RGMII2_TX_CTL_ALT0_ENET2_TX_EN = 0,
   IMX_IOMUXC_RGMII2_TX_CTL_ALT2_SAI1_RX_DATA0 = 2,
   IMX_IOMUXC_RGMII2_TX_CTL_ALT5_GPIO5_IO22 = 5,
   IMX_IOMUXC_RGMII2_TX_CTL_ALT6_CSI2_FIELD = 6,
   IMX_IOMUXC_RGMII2_TX_CTL_ALT7_JTAG_DE_B = 7,
} IMX_IOMUXC_RGMII2_TX_CTL_ALT;

typedef enum {
   IMX_IOMUXC_RGMII2_TXC_ALT0_ENET2_RGMII_TXC = 0,
   IMX_IOMUXC_RGMII2_TXC_ALT1_ENET2_TX_ER = 1,
   IMX_IOMUXC_RGMII2_TXC_ALT2_SAI1_TX_DATA0 = 2,
   IMX_IOMUXC_RGMII2_TXC_ALT5_GPIO5_IO23 = 5,
   IMX_IOMUXC_RGMII2_TXC_ALT6_CSI2_PIXCLK = 6,
} IMX_IOMUXC_RGMII2_TXC_ALT;

typedef enum {
   IMX_IOMUXC_SD1_CLK_ALT0_SD1_CLK = 0,
   IMX_IOMUXC_SD1_CLK_ALT1_AUD5_RXFS = 1,
   IMX_IOMUXC_SD1_CLK_ALT2_WDOG2_B = 2,
   IMX_IOMUXC_SD1_CLK_ALT3_GPT_CLK = 3,
   IMX_IOMUXC_SD1_CLK_ALT4_WDOG2_RST_B_DEB = 4,
   IMX_IOMUXC_SD1_CLK_ALT5_GPIO6_IO00 = 5,
   IMX_IOMUXC_SD1_CLK_ALT6_ENET2_1588_EVENT1_OUT = 6,
} IMX_IOMUXC_SD1_CLK_ALT;

typedef enum {
   IMX_IOMUXC_SD1_CMD_ALT0_SD1_CMD = 0,
   IMX_IOMUXC_SD1_CMD_ALT1_AUD5_RXC = 1,
   IMX_IOMUXC_SD1_CMD_ALT2_WDOG1_B = 2,
   IMX_IOMUXC_SD1_CMD_ALT3_GPT_COMPARE1 = 3,
   IMX_IOMUXC_SD1_CMD_ALT4_WDOG1_RST_B_DEB = 4,
   IMX_IOMUXC_SD1_CMD_ALT5_GPIO6_IO01 = 5,
   IMX_IOMUXC_SD1_CMD_ALT6_ENET2_1588_EVENT1_IN = 6,
   IMX_IOMUXC_SD1_CMD_ALT7_CCM_CLKO1 = 7,
} IMX_IOMUXC_SD1_CMD_ALT;

typedef enum {
   IMX_IOMUXC_SD1_DATA0_ALT0_SD1_DATA0 = 0,
   IMX_IOMUXC_SD1_DATA0_ALT1_AUD5_RXD = 1,
   IMX_IOMUXC_SD1_DATA0_ALT3_GPT_CAPTURE1 = 3,
   IMX_IOMUXC_SD1_DATA0_ALT4_UART2_RX_DATA = 4,
   IMX_IOMUXC_SD1_DATA0_ALT5_GPIO6_IO02 = 5,
   IMX_IOMUXC_SD1_DATA0_ALT6_ENET1_1588_EVENT1_IN = 6,
} IMX_IOMUXC_SD1_DATA0_ALT;

typedef enum {
   IMX_IOMUXC_SD1_DATA1_ALT0_SD1_DATA1 = 0,
   IMX_IOMUXC_SD1_DATA1_ALT1_AUD5_TXC = 1,
   IMX_IOMUXC_SD1_DATA1_ALT2_PWM4_OUT = 2,
   IMX_IOMUXC_SD1_DATA1_ALT3_GPT_CAPTURE2 = 3,
   IMX_IOMUXC_SD1_DATA1_ALT4_UART2_TX_DATA = 4,
   IMX_IOMUXC_SD1_DATA1_ALT5_GPIO6_IO03 = 5,
   IMX_IOMUXC_SD1_DATA1_ALT6_ENET1_1588_EVENT1_OUT = 6,
   IMX_IOMUXC_SD1_DATA1_ALT7_CCM_CLKO2 = 7,
} IMX_IOMUXC_SD1_DATA1_ALT;

typedef enum {
   IMX_IOMUXC_SD1_DATA2_ALT0_SD1_DATA2 = 0,
   IMX_IOMUXC_SD1_DATA2_ALT1_AUD5_TXFS = 1,
   IMX_IOMUXC_SD1_DATA2_ALT2_PWM3_OUT = 2,
   IMX_IOMUXC_SD1_DATA2_ALT3_GPT_COMPARE2 = 3,
   IMX_IOMUXC_SD1_DATA2_ALT4_UART2_CTS_B = 4,
   IMX_IOMUXC_SD1_DATA2_ALT5_GPIO6_IO04 = 5,
   IMX_IOMUXC_SD1_DATA2_ALT6_ECSPI4_RDY = 6,
} IMX_IOMUXC_SD1_DATA2_ALT;

typedef enum {
   IMX_IOMUXC_SD1_DATA3_ALT0_SD1_DATA3 = 0,
   IMX_IOMUXC_SD1_DATA3_ALT1_AUD5_TXD = 1,
   IMX_IOMUXC_SD1_DATA3_ALT2_AUD5_RXD = 2,
   IMX_IOMUXC_SD1_DATA3_ALT3_GPT_COMPARE3 = 3,
   IMX_IOMUXC_SD1_DATA3_ALT4_UART2_RTS_B = 4,
   IMX_IOMUXC_SD1_DATA3_ALT5_GPIO6_IO05 = 5,
   IMX_IOMUXC_SD1_DATA3_ALT6_ECSPI4_SS1 = 6,
   IMX_IOMUXC_SD1_DATA3_ALT7_CCM_PMIC_READY = 7,
} IMX_IOMUXC_SD1_DATA3_ALT;

typedef enum {
   IMX_IOMUXC_SD2_CLK_ALT0_SD2_CLK = 0,
   IMX_IOMUXC_SD2_CLK_ALT1_AUD6_RXFS = 1,
   IMX_IOMUXC_SD2_CLK_ALT2_KPP_COL5 = 2,
   IMX_IOMUXC_SD2_CLK_ALT3_ECSPI4_SCLK = 3,
   IMX_IOMUXC_SD2_CLK_ALT4_MLB_SIG = 4,
   IMX_IOMUXC_SD2_CLK_ALT5_GPIO6_IO06 = 5,
   IMX_IOMUXC_SD2_CLK_ALT6_MQS_RIGHT = 6,
   IMX_IOMUXC_SD2_CLK_ALT7_WDOG1_ANY = 7,
} IMX_IOMUXC_SD2_CLK_ALT;

typedef enum {
   IMX_IOMUXC_SD2_CMD_ALT0_SD2_CMD = 0,
   IMX_IOMUXC_SD2_CMD_ALT1_AUD6_RXC = 1,
   IMX_IOMUXC_SD2_CMD_ALT2_KPP_ROW5 = 2,
   IMX_IOMUXC_SD2_CMD_ALT3_ECSPI4_MOSI = 3,
   IMX_IOMUXC_SD2_CMD_ALT4_MLB_CLK = 4,
   IMX_IOMUXC_SD2_CMD_ALT5_GPIO6_IO07 = 5,
   IMX_IOMUXC_SD2_CMD_ALT6_MQS_LEFT = 6,
   IMX_IOMUXC_SD2_CMD_ALT7_WDOG3_B = 7,
} IMX_IOMUXC_SD2_CMD_ALT;

typedef enum {
   IMX_IOMUXC_SD2_DATA0_ALT0_SD2_DATA0 = 0,
   IMX_IOMUXC_SD2_DATA0_ALT1_AUD6_RXD = 1,
   IMX_IOMUXC_SD2_DATA0_ALT2_KPP_ROW7 = 2,
   IMX_IOMUXC_SD2_DATA0_ALT3_PWM1_OUT = 3,
   IMX_IOMUXC_SD2_DATA0_ALT4_I2C4_SDA = 4,
   IMX_IOMUXC_SD2_DATA0_ALT5_GPIO6_IO08 = 5,
   IMX_IOMUXC_SD2_DATA0_ALT6_ECSPI4_SS3 = 6,
   IMX_IOMUXC_SD2_DATA0_ALT7_UART4_RX_DATA = 7,
} IMX_IOMUXC_SD2_DATA0_ALT;

typedef enum {
   IMX_IOMUXC_SD2_DATA1_ALT0_SD2_DATA1 = 0,
   IMX_IOMUXC_SD2_DATA1_ALT1_AUD6_TXC = 1,
   IMX_IOMUXC_SD2_DATA1_ALT2_KPP_COL7 = 2,
   IMX_IOMUXC_SD2_DATA1_ALT3_PWM2_OUT = 3,
   IMX_IOMUXC_SD2_DATA1_ALT4_I2C4_SCL = 4,
   IMX_IOMUXC_SD2_DATA1_ALT5_GPIO6_IO09 = 5,
   IMX_IOMUXC_SD2_DATA1_ALT6_ECSPI4_SS2 = 6,
   IMX_IOMUXC_SD2_DATA1_ALT7_UART4_TX_DATA = 7,
} IMX_IOMUXC_SD2_DATA1_ALT;

typedef enum {
   IMX_IOMUXC_SD2_DATA2_ALT0_SD2_DATA2 = 0,
   IMX_IOMUXC_SD2_DATA2_ALT1_AUD6_TXFS = 1,
   IMX_IOMUXC_SD2_DATA2_ALT2_KPP_ROW6 = 2,
   IMX_IOMUXC_SD2_DATA2_ALT3_ECSPI4_SS0 = 3,
   IMX_IOMUXC_SD2_DATA2_ALT4_SDMA_EXT_EVENT0 = 4,
   IMX_IOMUXC_SD2_DATA2_ALT5_GPIO6_IO10 = 5,
   IMX_IOMUXC_SD2_DATA2_ALT6_SPDIF_OUT = 6,
   IMX_IOMUXC_SD2_DATA2_ALT7_UART6_RX_DATA = 7,
} IMX_IOMUXC_SD2_DATA2_ALT;

typedef enum {
   IMX_IOMUXC_SD2_DATA3_ALT0_SD2_DATA3 = 0,
   IMX_IOMUXC_SD2_DATA3_ALT1_AUD6_TXD = 1,
   IMX_IOMUXC_SD2_DATA3_ALT2_KPP_COL6 = 2,
   IMX_IOMUXC_SD2_DATA3_ALT3_ECSPI4_MISO = 3,
   IMX_IOMUXC_SD2_DATA3_ALT4_MLB_DATA = 4,
   IMX_IOMUXC_SD2_DATA3_ALT5_GPIO6_IO11 = 5,
   IMX_IOMUXC_SD2_DATA3_ALT6_SPDIF_IN = 6,
   IMX_IOMUXC_SD2_DATA3_ALT7_UART6_TX_DATA = 7,
} IMX_IOMUXC_SD2_DATA3_ALT;

typedef enum {
   IMX_IOMUXC_SD4_CLK_ALT0_SD4_CLK = 0,
   IMX_IOMUXC_SD4_CLK_ALT1_NAND_DATA15 = 1,
   IMX_IOMUXC_SD4_CLK_ALT2_ECSPI2_MISO = 2,
   IMX_IOMUXC_SD4_CLK_ALT3_AUD3_RXFS = 3,
   IMX_IOMUXC_SD4_CLK_ALT4_LCD2_DATA13 = 4,
   IMX_IOMUXC_SD4_CLK_ALT5_GPIO6_IO12 = 5,
   IMX_IOMUXC_SD4_CLK_ALT6_ECSPI3_SS2 = 6,
} IMX_IOMUXC_SD4_CLK_ALT;

typedef enum {
   IMX_IOMUXC_SD4_CMD_ALT0_SD4_CMD = 0,
   IMX_IOMUXC_SD4_CMD_ALT1_NAND_DATA14 = 1,
   IMX_IOMUXC_SD4_CMD_ALT2_ECSPI2_MOSI = 2,
   IMX_IOMUXC_SD4_CMD_ALT3_AUD3_RXC = 3,
   IMX_IOMUXC_SD4_CMD_ALT4_LCD2_DATA14 = 4,
   IMX_IOMUXC_SD4_CMD_ALT5_GPIO6_IO13 = 5,
   IMX_IOMUXC_SD4_CMD_ALT6_ECSPI3_SS1 = 6,
} IMX_IOMUXC_SD4_CMD_ALT;

typedef enum {
   IMX_IOMUXC_SD4_DATA0_ALT0_SD4_DATA0 = 0,
   IMX_IOMUXC_SD4_DATA0_ALT1_NAND_DATA10 = 1,
   IMX_IOMUXC_SD4_DATA0_ALT2_ECSPI2_SS0 = 2,
   IMX_IOMUXC_SD4_DATA0_ALT3_AUD3_RXD = 3,
   IMX_IOMUXC_SD4_DATA0_ALT4_LCD2_DATA12 = 4,
   IMX_IOMUXC_SD4_DATA0_ALT5_GPIO6_IO14 = 5,
   IMX_IOMUXC_SD4_DATA0_ALT6_ECSPI3_SS3 = 6,
} IMX_IOMUXC_SD4_DATA0_ALT;

typedef enum {
   IMX_IOMUXC_SD4_DATA1_ALT0_SD4_DATA1 = 0,
   IMX_IOMUXC_SD4_DATA1_ALT1_NAND_DATA11 = 1,
   IMX_IOMUXC_SD4_DATA1_ALT2_ECSPI2_SCLK = 2,
   IMX_IOMUXC_SD4_DATA1_ALT3_AUD3_TXC = 3,
   IMX_IOMUXC_SD4_DATA1_ALT4_LCD2_DATA11 = 4,
   IMX_IOMUXC_SD4_DATA1_ALT5_GPIO6_IO15 = 5,
   IMX_IOMUXC_SD4_DATA1_ALT6_ECSPI3_RDY = 6,
} IMX_IOMUXC_SD4_DATA1_ALT;

typedef enum {
   IMX_IOMUXC_SD4_DATA2_ALT0_SD4_DATA2 = 0,
   IMX_IOMUXC_SD4_DATA2_ALT1_NAND_DATA12 = 1,
   IMX_IOMUXC_SD4_DATA2_ALT2_I2C2_SDA = 2,
   IMX_IOMUXC_SD4_DATA2_ALT3_AUD3_TXFS = 3,
   IMX_IOMUXC_SD4_DATA2_ALT4_LCD2_DATA10 = 4,
   IMX_IOMUXC_SD4_DATA2_ALT5_GPIO6_IO16 = 5,
   IMX_IOMUXC_SD4_DATA2_ALT6_ECSPI2_SS3 = 6,
} IMX_IOMUXC_SD4_DATA2_ALT;

typedef enum {
   IMX_IOMUXC_SD4_DATA3_ALT0_SD4_DATA3 = 0,
   IMX_IOMUXC_SD4_DATA3_ALT1_NAND_DATA13 = 1,
   IMX_IOMUXC_SD4_DATA3_ALT2_I2C2_SCL = 2,
   IMX_IOMUXC_SD4_DATA3_ALT3_AUD3_TXD = 3,
   IMX_IOMUXC_SD4_DATA3_ALT4_LCD2_DATA09 = 4,
   IMX_IOMUXC_SD4_DATA3_ALT5_GPIO6_IO17 = 5,
   IMX_IOMUXC_SD4_DATA3_ALT6_ECSPI2_RDY = 6,
} IMX_IOMUXC_SD4_DATA3_ALT;

typedef enum {
   IMX_IOMUXC_SD4_DATA4_ALT0_SD4_DATA4 = 0,
   IMX_IOMUXC_SD4_DATA4_ALT1_NAND_DATA09 = 1,
   IMX_IOMUXC_SD4_DATA4_ALT2_UART5_RX_DATA = 2,
   IMX_IOMUXC_SD4_DATA4_ALT3_ECSPI3_SCLK = 3,
   IMX_IOMUXC_SD4_DATA4_ALT4_LCD2_DATA08 = 4,
   IMX_IOMUXC_SD4_DATA4_ALT5_GPIO6_IO18 = 5,
   IMX_IOMUXC_SD4_DATA4_ALT6_SPDIF_OUT = 6,
} IMX_IOMUXC_SD4_DATA4_ALT;

typedef enum {
   IMX_IOMUXC_SD4_DATA5_ALT0_SD4_DATA5 = 0,
   IMX_IOMUXC_SD4_DATA5_ALT1_NAND_CE2_B = 1,
   IMX_IOMUXC_SD4_DATA5_ALT2_UART5_TX_DATA = 2,
   IMX_IOMUXC_SD4_DATA5_ALT3_ECSPI3_MOSI = 3,
   IMX_IOMUXC_SD4_DATA5_ALT4_LCD2_DATA07 = 4,
   IMX_IOMUXC_SD4_DATA5_ALT5_GPIO6_IO19 = 5,
   IMX_IOMUXC_SD4_DATA5_ALT6_SPDIF_IN = 6,
} IMX_IOMUXC_SD4_DATA5_ALT;

typedef enum {
   IMX_IOMUXC_SD4_DATA6_ALT0_SD4_DATA6 = 0,
   IMX_IOMUXC_SD4_DATA6_ALT1_NAND_CE3_B = 1,
   IMX_IOMUXC_SD4_DATA6_ALT2_UART5_RTS_B = 2,
   IMX_IOMUXC_SD4_DATA6_ALT3_ECSPI3_MISO = 3,
   IMX_IOMUXC_SD4_DATA6_ALT4_LCD2_DATA06 = 4,
   IMX_IOMUXC_SD4_DATA6_ALT5_GPIO6_IO20 = 5,
   IMX_IOMUXC_SD4_DATA6_ALT6_SD4_WP = 6,
} IMX_IOMUXC_SD4_DATA6_ALT;

typedef enum {
   IMX_IOMUXC_SD4_DATA7_ALT0_SD4_DATA7 = 0,
   IMX_IOMUXC_SD4_DATA7_ALT1_NAND_DATA08 = 1,
   IMX_IOMUXC_SD4_DATA7_ALT2_UART5_CTS_B = 2,
   IMX_IOMUXC_SD4_DATA7_ALT3_ECSPI3_SS0 = 3,
   IMX_IOMUXC_SD4_DATA7_ALT4_LCD2_DATA15 = 4,
   IMX_IOMUXC_SD4_DATA7_ALT5_GPIO6_IO21 = 5,
   IMX_IOMUXC_SD4_DATA7_ALT6_SD4_CD_B = 6,
} IMX_IOMUXC_SD4_DATA7_ALT;

typedef enum {
   IMX_IOMUXC_SD4_RESET_B_ALT0_SD4_RESET_B = 0,
   IMX_IOMUXC_SD4_RESET_B_ALT1_NAND_DQS = 1,
   IMX_IOMUXC_SD4_RESET_B_ALT2_SD4_RESET = 2,
   IMX_IOMUXC_SD4_RESET_B_ALT3_AUDIO_CLK_OUT = 3,
   IMX_IOMUXC_SD4_RESET_B_ALT4_LCD2_RESET = 4,
   IMX_IOMUXC_SD4_RESET_B_ALT5_GPIO6_IO22 = 5,
   IMX_IOMUXC_SD4_RESET_B_ALT6_LCD2_CS = 6,
} IMX_IOMUXC_SD4_RESET_B_ALT;

typedef enum {
   IMX_IOMUXC_SD3_CLK_ALT0_SD3_CLK = 0,
   IMX_IOMUXC_SD3_CLK_ALT1_UART4_CTS_B = 1,
   IMX_IOMUXC_SD3_CLK_ALT2_ECSPI4_SCLK = 2,
   IMX_IOMUXC_SD3_CLK_ALT3_AUD6_RXFS = 3,
   IMX_IOMUXC_SD3_CLK_ALT4_LCD2_VSYNC = 4,
   IMX_IOMUXC_SD3_CLK_ALT5_GPIO7_IO00 = 5,
   IMX_IOMUXC_SD3_CLK_ALT6_LCD2_BUSY = 6,
} IMX_IOMUXC_SD3_CLK_ALT;

typedef enum {
   IMX_IOMUXC_SD3_CMD_ALT0_SD3_CMD = 0,
   IMX_IOMUXC_SD3_CMD_ALT1_UART4_TX_DATA = 1,
   IMX_IOMUXC_SD3_CMD_ALT2_ECSPI4_MOSI = 2,
   IMX_IOMUXC_SD3_CMD_ALT3_AUD6_RXC = 3,
   IMX_IOMUXC_SD3_CMD_ALT4_LCD2_HSYNC = 4,
   IMX_IOMUXC_SD3_CMD_ALT5_GPIO7_IO01 = 5,
   IMX_IOMUXC_SD3_CMD_ALT6_LCD2_RS = 6,
} IMX_IOMUXC_SD3_CMD_ALT;

typedef enum {
   IMX_IOMUXC_SD3_DATA0_ALT0_SD3_DATA0 = 0,
   IMX_IOMUXC_SD3_DATA0_ALT1_I2C4_SCL = 1,
   IMX_IOMUXC_SD3_DATA0_ALT2_ECSPI2_SS1 = 2,
   IMX_IOMUXC_SD3_DATA0_ALT3_AUD6_RXD = 3,
   IMX_IOMUXC_SD3_DATA0_ALT4_LCD2_DATA01 = 4,
   IMX_IOMUXC_SD3_DATA0_ALT5_GPIO7_IO02 = 5,
   IMX_IOMUXC_SD3_DATA0_ALT6_DCIC1_OUT = 6,
} IMX_IOMUXC_SD3_DATA0_ALT;

typedef enum {
   IMX_IOMUXC_SD3_DATA1_ALT0_SD3_DATA1 = 0,
   IMX_IOMUXC_SD3_DATA1_ALT1_I2C4_SDA = 1,
   IMX_IOMUXC_SD3_DATA1_ALT2_ECSPI2_SS2 = 2,
   IMX_IOMUXC_SD3_DATA1_ALT3_AUD6_TXC = 3,
   IMX_IOMUXC_SD3_DATA1_ALT4_LCD2_DATA00 = 4,
   IMX_IOMUXC_SD3_DATA1_ALT5_GPIO7_IO03 = 5,
   IMX_IOMUXC_SD3_DATA1_ALT6_DCIC2_OUT = 6,
} IMX_IOMUXC_SD3_DATA1_ALT;

typedef enum {
   IMX_IOMUXC_SD3_DATA2_ALT0_SD3_DATA2 = 0,
   IMX_IOMUXC_SD3_DATA2_ALT1_UART4_RTS_B = 1,
   IMX_IOMUXC_SD3_DATA2_ALT2_ECSPI4_SS0 = 2,
   IMX_IOMUXC_SD3_DATA2_ALT3_AUD6_TXFS = 3,
   IMX_IOMUXC_SD3_DATA2_ALT4_LCD2_CLK = 4,
   IMX_IOMUXC_SD3_DATA2_ALT5_GPIO7_IO04 = 5,
   IMX_IOMUXC_SD3_DATA2_ALT6_LCD2_WR_RWN = 6,
} IMX_IOMUXC_SD3_DATA2_ALT;

typedef enum {
   IMX_IOMUXC_SD3_DATA3_ALT0_SD3_DATA3 = 0,
   IMX_IOMUXC_SD3_DATA3_ALT1_UART4_RX_DATA = 1,
   IMX_IOMUXC_SD3_DATA3_ALT2_ECSPI4_MISO = 2,
   IMX_IOMUXC_SD3_DATA3_ALT3_AUD6_TXD = 3,
   IMX_IOMUXC_SD3_DATA3_ALT4_LCD2_ENABLE = 4,
   IMX_IOMUXC_SD3_DATA3_ALT5_GPIO7_IO05 = 5,
   IMX_IOMUXC_SD3_DATA3_ALT6_LCD2_RD_E = 6,
} IMX_IOMUXC_SD3_DATA3_ALT;

typedef enum {
   IMX_IOMUXC_SD3_DATA4_ALT0_SD3_DATA4 = 0,
   IMX_IOMUXC_SD3_DATA4_ALT1_CAN2_RX = 1,
   IMX_IOMUXC_SD3_DATA4_ALT3_UART3_RX_DATA = 3,
   IMX_IOMUXC_SD3_DATA4_ALT4_LCD2_DATA03 = 4,
   IMX_IOMUXC_SD3_DATA4_ALT5_GPIO7_IO06 = 5,
   IMX_IOMUXC_SD3_DATA4_ALT6_ENET2_1588_EVENT0_IN = 6,
} IMX_IOMUXC_SD3_DATA4_ALT;

typedef enum {
   IMX_IOMUXC_SD3_DATA5_ALT0_SD3_DATA5 = 0,
   IMX_IOMUXC_SD3_DATA5_ALT1_CAN1_TX = 1,
   IMX_IOMUXC_SD3_DATA5_ALT3_UART3_TX_DATA = 3,
   IMX_IOMUXC_SD3_DATA5_ALT4_LCD2_DATA02 = 4,
   IMX_IOMUXC_SD3_DATA5_ALT5_GPIO7_IO07 = 5,
   IMX_IOMUXC_SD3_DATA5_ALT6_ENET2_1588_EVENT0_OUT = 6,
} IMX_IOMUXC_SD3_DATA5_ALT;

typedef enum {
   IMX_IOMUXC_SD3_DATA6_ALT0_SD3_DATA6 = 0,
   IMX_IOMUXC_SD3_DATA6_ALT1_CAN2_TX = 1,
   IMX_IOMUXC_SD3_DATA6_ALT3_UART3_RTS_B = 3,
   IMX_IOMUXC_SD3_DATA6_ALT4_LCD2_DATA04 = 4,
   IMX_IOMUXC_SD3_DATA6_ALT5_GPIO7_IO08 = 5,
   IMX_IOMUXC_SD3_DATA6_ALT6_ENET1_1588_EVENT0_OUT = 6,
} IMX_IOMUXC_SD3_DATA6_ALT;

typedef enum {
   IMX_IOMUXC_SD3_DATA7_ALT0_SD3_DATA7 = 0,
   IMX_IOMUXC_SD3_DATA7_ALT1_CAN1_RX = 1,
   IMX_IOMUXC_SD3_DATA7_ALT3_UART3_CTS_B = 3,
   IMX_IOMUXC_SD3_DATA7_ALT4_LCD2_DATA05 = 4,
   IMX_IOMUXC_SD3_DATA7_ALT5_GPIO7_IO09 = 5,
   IMX_IOMUXC_SD3_DATA7_ALT6_ENET1_1588_EVENT0_IN = 6,
} IMX_IOMUXC_SD3_DATA7_ALT;

typedef enum {
   IMX_IOMUXC_USB_H_DATA_ALT0_USB_H_DATA = 0,
   IMX_IOMUXC_USB_H_DATA_ALT1_PWM2_OUT = 1,
   IMX_IOMUXC_USB_H_DATA_ALT2_XTALOSC_REF_CLK_24M = 2,
   IMX_IOMUXC_USB_H_DATA_ALT3_I2C4_SDA = 3,
   IMX_IOMUXC_USB_H_DATA_ALT4_WDOG3_B = 4,
   IMX_IOMUXC_USB_H_DATA_ALT5_GPIO7_IO10 = 5,
} IMX_IOMUXC_USB_H_DATA_ALT;

typedef enum {
   IMX_IOMUXC_USB_H_STROBE_ALT0_USB_H_STROBE = 0,
   IMX_IOMUXC_USB_H_STROBE_ALT1_PWM1_OUT = 1,
   IMX_IOMUXC_USB_H_STROBE_ALT2_XTALOSC_REF_CLK_32K = 2,
   IMX_IOMUXC_USB_H_STROBE_ALT3_I2C4_SCL = 3,
   IMX_IOMUXC_USB_H_STROBE_ALT4_WDOG3_RST_B_DEB = 4,
   IMX_IOMUXC_USB_H_STROBE_ALT5_GPIO7_IO11 = 5,
} IMX_IOMUXC_USB_H_STROBE_ALT;

#endif // _IMX6_IOMUX_SX_H_
