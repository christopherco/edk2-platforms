/*

  iMX6 ENET register defintions

Copyright (c) Microsoft Corporation. All rights reserved.

This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

*/

#ifndef __IMX6ENET_DXE_HW_H__
#define __IMX6ENET_DXE_HW_H__


//  iMX6 ENET Registers

typedef struct _IMX6_ENET_REGISTERS
{
    UINT32  reserved0;     // 0
    UINT32 EIR;           // 4
    UINT32 EIMR;          // 8
    UINT32 reserved1;     // Ch
    UINT32 RDAR;          // 10h
    UINT32 TDAR;          // 14h
    UINT32 reserved2[3];  // 18h - 20h
    UINT32 ECR;           // 24h Ethernet Control Register (ENET_ECR)
    UINT32 reserved3[6];  // 28h - 3Ch
    UINT32 MMFR;          // 40h
    UINT32 MSCR;          // 44h
    UINT32 reserved4[7];  // 48h - 60h
    UINT32 MIBC;          // 64h
    UINT32 reserved5[7];  //
    UINT32 RCR;           // 84h
    UINT32 reserved6[15]; // 
    UINT32 TCR;           // C4h
    UINT32 reserved7[7];
    UINT32 PALR;          // E4h
    UINT32 PAUR;          // E8h
    UINT32 OPD;           // ECh
    UINT32  ___RES_0F0[10];
    UINT32  IAUR;               // 118
    UINT32  IALR;               // 11C
    UINT32  GAUR;               // 120
    UINT32  GALR;               // 124
    UINT32  ___RES_128[7];
    UINT32  TFWR;               // 144
    UINT32  ___RES_D148[14];
    UINT32  ERDSR;              // 180
    UINT32  ETDSR;              // 184
    UINT32  EMRBR;              // 188
    UINT32  ___RES_18C;
    UINT32  RSFL;               // 190
    UINT32  RSEM;               // 194
    UINT32  RAEM;               // 198
    UINT32  RAFL;               // 19C
    UINT32  TSEM;               // 1A0
    UINT32  TAEM;               // 1A4
    UINT32  TAFL;               // 1A8
    UINT32  TIPG;               // 1AC
    UINT32  FTRL;               // 1B0
    UINT32  ___RES_1B4[3];
    UINT32  TACC;               // 1C0
    UINT32  RACC;               // 1C4
    UINT32  ___RES_1C8[14];

    // statistics
    UINT32  RMON_T_DROP_NI;     // 200
    UINT32  RMON_T_PACKETS;     // 204
    UINT32  RMON_T_BC_PKT;      // 208
    UINT32  RMON_T_MC_PKT;      // 20C
    UINT32  RMON_T_CRC_ALIGN;   // 210
    UINT32  RMON_T_UNDERSIZE;   // 214
    UINT32  RMON_T_OVERSIZE;    // 218
    UINT32  RMON_T_FRAG;        // 21C
    UINT32  RMON_T_JAB;         // 220
    UINT32  RMON_T_COL;         // 224
    UINT32  RMON_T_P64;         // 228
    UINT32  RMON_T_P65TO127;    // 22C
    UINT32  RMON_T_P128TO255;   // 230
    UINT32  RMON_T_P256TO511;   // 234
    UINT32  RMON_T_P512TO1023;  // 238
    UINT32  RMON_T_P1024TO2047; // 23C
    UINT32  RMON_T_P_GTE2048;   // 240
    UINT32  RMON_T_OCTETS;      // 244
    UINT32  IEEE_T_DROP_NI;     // 248
    UINT32  IEEE_T_FRAME_OK;    // 24C
    UINT32  IEEE_T_1COL;        // 250
    UINT32  IEEE_T_MCOL;        // 254
    UINT32  IEEE_T_DEF;         // 258
    UINT32  IEEE_T_LCOL;        // 25C
    UINT32  IEEE_T_EXCOL;       // 260
    UINT32  IEEE_T_MACERR;      // 264
    UINT32  IEEE_T_CSERR;       // 268
    UINT32  IEEE_T_SQE_NI;      // 26C
    UINT32  IEEE_T_FDXFC;       // 270
    UINT32  IEEE_T_OCTETS_OK;   // 274
    UINT32  ___RES_278[3];
    UINT32  RMON_R_PACKETS;     // 284
    UINT32  RMON_R_BC_PKT;      // 288
    UINT32  RMON_R_MC_PKT;      // 28C
    UINT32  RMON_R_CRC_ALIGN;   // 290
    UINT32  RMON_R_UNDERSIZE;   // 294
    UINT32  RMON_R_OVERSIZE;    // 298
    UINT32  RMON_R_FRAG;        // 29C
    UINT32  RMON_R_JAB;         // 2A0
    UINT32  RMON_R_RESVD_0;     // 2A4
    UINT32  RMON_R_P64;         // 2A8
    UINT32  RMON_R_P65TO127;    // 2AC
    UINT32  RMON_R_P128TO255;   // 2B0
    UINT32  RMON_R_P256TO511;   // 2B4
    UINT32  RMON_R_P512TO1023;  // 2B8
    UINT32  RMON_R_P1024TO2047; // 2BC
    UINT32  RMON_R_P_GTE2048;   // 2C0
    UINT32  RMON_R_OCTETS;      // 2C4
    UINT32  IEEE_R_DROP;        // 2C8
    UINT32  IEEE_R_FRAME_OK;    // 2CC
    UINT32  IEEE_R_CRC;         // 2D0
    UINT32  IEEE_R_ALIGN;       // 2D4
    UINT32  IEEE_R_MACERR;      // 2D8
    UINT32  IEEE_R_FDXFC;       // 2DC
    UINT32  IEEE_R_OCTETS_OK;   // 2E0

#ifdef __USE_TIMER_REGISTERS__
    UINT32  _PAD2E4[71];
    UINT32  ATCR;               // 400
    UINT32  ATVR;               // 404
    UINT32  ATOFF;              // 408
    UINT32  ATPER;              // 40C
    UINT32  ATCOR;              // 410
    UINT32  ATINC;              // 414
    UINT32  ATSTMP;             // 418
    UINT32  _PAD41C[122];
    UINT32  TGSR;               // 604
    UINT32  TCSR0;              // 608
    UINT32  TCCR0;              // 60C
    UINT32  TCSR1;              // 610
    UINT32  TCCR1;              // 614
    UINT32  TCSR2;              // 618
    UINT32  TCCR2;              // 61C
    UINT32  TCSR3;              // 620
    UINT32  TCCR3;              // 624
#endif // __USE_TIMER_REGISTERS__

} IMX6_ENET_REGISTERS;

// Synchronization TPL - Serialize access to Enet data and registers
#define ENETIMX6_TPL  TPL_CALLBACK

#define IOMUXC_SW_PAD_CTL_PAD_ENET_REF_CLK_ADR  0x020E04E8
#define IOMUXC_SW_PAD_CTL_PAD_ENET_REF_CLK_VAL  0x0000a0b1

// MIB RAM location and size
#define ENET_MIB_SEND_RAM_SIZE     0x74
#define ENET_MIB_RECV_RAM_SIZE     0x5C // 0xE0-0x84

// Buffer descriptor control/status used by Ethernet receive

#define BD_ENET_RX_EMPTY        ((UINT16)0x8000) // Buffer is empty 
#define BD_ENET_RX_PAD          ((UINT16)0x4000) // enable frame padding
#define BD_ENET_RX_WRAP         ((UINT16)0x2000) // Buffer is last in frame 
#define BD_ENET_RX_LAST         ((UINT16)0x0800) // Last frame is sequence
#define BD_ENET_RX_MISS         ((UINT16)0x0100) // Miss bit for prom mode   
#define BD_ENET_RX_BC           ((UINT16)0x0080) // The received frame is broadcast frame 
#define BD_ENET_RX_MC           ((UINT16)0x0040) // The received frame is multicast frame
#define BD_ENET_RX_LG           ((UINT16)0x0020) // Frame length violation 
#define BD_ENET_RX_NO           ((UINT16)0x0010) // Nonoctet align frame 
#define BD_ENET_RX_CR           ((UINT16)0x0004) // CRC error 
#define BD_ENET_RX_OV           ((UINT16)0x0002) // Receive FIFO overrun 
#define BD_ENET_RX_TR           ((UINT16)0x0001) // Frame is truncated 
#define BD_ENET_RX_STATS        ((UINT16)0x01ff) // All status bits mask
#define BD_ENET_RX_ERRORS       ((UINT16)0x0037) // All errors status bits mask

// Buffer descriptor control/status used by Ethernet transmit.

#define BD_ENET_TX_READY        ((UINT16)0x8000) // Buffer is ready 
#define BD_ENET_TX_PAD          ((UINT16)0x4000) // padding not used in this driver
#define BD_ENET_TX_WRAP         ((UINT16)0x2000) // Mark as last BD in ring 
#define BD_ENET_TX_LAST         ((UINT16)0x0800) // Buffer is last in frame 
#define BD_ENET_TX_TC           ((UINT16)0x0400) // Transmit the CRC 
#define BD_ENET_TX_ABC          ((UINT16)0x0200) // Append bad CRC 
#define BD_ENET_TX_HB           ((UINT16)0x0100)  /* SW flag */
#define BD_ENET_TX_LC           ((UINT16)0x0080)  /* SW flag */
#define BD_ENET_TX_RL           ((UINT16)0x0040)  /* SW flag */
#define BD_ENET_TX_RCMASK       ((UINT16)0x003c)  /* SW flag */
#define BD_ENET_TX_UN           ((UINT16)0x0002)  /* SW flag */
#define BD_ENET_TX_CSL          ((UINT16)0x0001)  /* SW flag */
#define BD_ENET_TX_STATS        ((UINT16)0x03ff)  /* All status bits */

#define DIV_ROUND_UP(n,d) (((n)+(d)-1)/(d))

// URXD register Receiver Status bits

#define RXSTATUS_CRC_ERROR                    BIT1                      // Cyclic Redundancy Check Error
#define RXSTATUS_DB                           BIT2                      // Dribbling bit: Frame had non-integer multiple of 8bits
#define RXSTATUS_MII_ERROR                    BIT3                      // Receive error during interception
#define RXSTATUS_RXW_TO                       BIT4                      // Incomming frame larger than 2kb
#define RXSTATUS_FT                           BIT5                      // 1: Ether type / 0: 802.3 type frame
#define RXSTATUS_LCOLL                        BIT6                      // Late collision detected
#define RXSTATUS_FTL                          BIT7                      // Frame longer than Ether type
#define RXSTATUS_MCF                          BIT10                     // Frame has Multicast Address
#define RXSTATUS_RUNT                         BIT11                     // Bad frame
#define RXSTATUS_LE                           BIT12                     // Actual length of frame different than it claims
#define RXSTATUS_BCF                          BIT13                     // Frame has Broadcast Address
#define RXSTATUS_ES                           BIT15                     // Reports any error from bits 1,6,7 and 11
#define RXSTATUS_PL_MASK                      (0x3FFF0000)              // Packet length bit mask
#define GET_RXSTATUS_PACKET_LENGTH(RxStatus)  (((RxStatus) >> 16) & 0x3FFF) // Packet length bit mask
#define RXSTATUS_FILT_FAIL                    BIT30                     // The frame failed filtering test

// UTXD register Transmitter Status bits

#define TXSTATUS_DEF                          BIT0                      // Packet tx was deferred
#define TXSTATUS_EDEF                         BIT2                      // Tx ended because of excessive deferral (> 24288 bit times)
#define TXSTATUS_CC_MASK                      (0x00000078)              // Collision Count (before Tx) bit mask
#define TXSTATUS_ECOLL                        BIT8                      // Tx ended because of Excessive Collisions (makes CC_MASK invalid after 16 collisions)
#define TXSTATUS_LCOLL                        BIT9                      // Packet Tx aborted after coll window of 64 bytes
#define TXSTATUS_NO_CA                        BIT10                     // Carrier signal not present during Tx (bad?)
#define TXSTATUS_LOST_CA                      BIT11                     // Lost carrier during Tx
#define TXSTATUS_ES                           BIT15                     // Reports any errors from bits 1,2,8,9,10 and 11
#define TXSTATUS_PTAG_MASK                    (0xFFFF0000)              // Mask for Unique ID of packets (So we know who the packets are for)

// RDAR register bits
#define ENET_RDAR_ACTIVE_ACTIVE             BIT24

// ECR register bits
#define ECR_BIT0_RESET          BIT0
#define ECR_BIT1_ENABLED        BIT1
#define ECR_BIT5_GIGABITSPD     BIT5
#define ECR_BIT8_DESCBYTESWAP   BIT8

// EIR register bits
#define EIR_BIT22_EBERR     BIT22
#define EIR_BIT23_MIIIEVT   BIT23
#define EIR_BIT24_RECVBEVT  BIT24
#define EIR_BIT26_TXBEVT    BIT26
#define EIR_BIT28_GRASTOP   BIT28
#define EIR_BIT29_BABTERR   BIT29
#define EIR_BIT30_BABERR    BIT30   

// TCR register bits
#define TCR_BIT0_GRACEFUL_TXSTOP    BIT0
#define TCR_BIT2_FULLDPLX_EN        BIT2

// RCR register bits
#define RCR_BIT2_MII_MODE   BIT2       
#define RCR_BIT5_FLOWCTRL   BIT5
#define RCR_BIT6_RGMII_EN   BIT6
#define RCR_BIT8_RMII_MODE  BIT8
#define RCR_BIT9_RMII_10T   BIT9

// TFWR register bits
#define TFWR_BIT8_STORFWD   BIT8

// PHY control register bits

#define PHYCR_COLL_TEST                       BIT7                  // Collision test enable
#define PHYCR_DUPLEX_MODE                     BIT8                  // Set Duplex Mode
#define PHYCR_RST_AUTO                        BIT9                  // Restart Auto-Negotiation of Link abilities
#define PHYCR_PD                              BIT11                 // Power-Down switch
#define PHYCR_AUTO_EN                         BIT12                 // Auto-Negotiation Enable
#define PHYCR_SPEED_SEL                       BIT13                 // Link Speed Selection
#define PHYCR_LOOPBK                          BIT14                 // Set loopback mode
#define PHYCR_RESET                           BIT15                 // Do a PHY reset

// PHY status register bits

#define PHYSTS_EXT_CAP                        BIT0                  // Extended Capabilities Register capability
#define PHYSTS_JABBER                         BIT1                  // Jabber condition detected
#define PHYSTS_LINK_STS                       BIT2                  // Link Status
#define PHYSTS_AUTO_CAP                       BIT3                  // Auto-Negotiation Capability
#define PHYSTS_REMOTE_FAULT                   BIT4                  // Remote fault detected
#define PHYSTS_AUTO_COMP                      BIT5                  // Auto-Negotiation Completed
#define PHYSTS_10BASET_HDPLX                  BIT11                 // 10Mbps Half-Duplex ability
#define PHYSTS_10BASET_FDPLX                  BIT12                 // 10Mbps Full-Duplex ability
#define PHYSTS_100BASETX_HDPLX                BIT13                 // 100Mbps Half-Duplex ability
#define PHYSTS_100BASETX_FDPLX                BIT14                 // 100Mbps Full-Duplex ability
#define PHYSTS_100BASE_T4                     BIT15                 // Base T4 ability

// PHY Auto-Negotiation advertisement

#define PHYANA_SEL_MASK                       ((UINT32)0x1F)        // Link type selector
#define PHYANA_10BASET                        BIT5                  // Advertise 10BASET capability
#define PHYANA_10BASETFD                      BIT6                  // Advertise 10BASET Full duplex capability
#define PHYANA_100BASETX                      BIT7                  // Advertise 100BASETX capability
#define PHYANA_100BASETXFD                    BIT8                  // Advertise 100 BASETX Full duplex capability
#define PHYANA_PAUSE_OP_MASK                  (3 << 10)             // Advertise PAUSE frame capability
#define PHYANA_REMOTE_FAULT                   BIT13                 // Remote fault detected

// Standard MII Register definitions for the PHY 

#define MII_REG_CR				0  /* Control Register */

#define MII_CR_BIT15_RESET          BIT15       // 8000h
#define MII_CR_BIT14_LOOPBACK       BIT14
#define MII_CR_BIT13_SPEED_10_100   BIT13       // 2000h
#define MII_CR_BIT12_ANEG_ENABLE    BIT12       // 1000h
#define MII_CR_BIT11_PWR_DOWN       BIT11       // 800h when set the PHY will NOT respond to management transactions. 
#define MII_CR_BIT10_MII_DISABLE_PHY_ISOLATE    BIT10   // when set the PHY will respond to management transaction, but ignore data
#define MII_CR_BIT9_AUTONEG_RESET   BIT9        // 200h
#define MII_CR_BIT8_DUPLEX_MODE     BIT8        // 100h
#define MII_CR_BIT7_COLLSN_TEST     BIT7

#define MII_REG_SR				1  /* Status Register */

#define MII_SR_BIT15_100BASET4_CAP          BIT15
#define MII_SR_BIT14_100BASETXFULLDUPLX_CAP BIT14
#define MII_SR_BIT13_100BASETXHALFDPLX_CAP  BIT13
#define MII_SR_BIT12_10BASETFULDPLX_CAP     BIT12
#define MII_SR_BIT11_10BASETHALFDPLX_CAP    BIT11   // 80h
#define MII_SR_BIT6_PREABLE_SUPRS_CAP       BIT6    // 40h
#define MII_SR_BIT5_ANEG_COMPLETE_ACK       BIT5    // 20h; aneg has been completed and that contents in registers 4,5,6 and 7 are valid
#define MII_SR_BIT4_REMOTE_FLT_DET          BIT4    // 10h
#define MII_SR_BIT3_ANEG_CAP                BIT3    // 8
#define MII_SR_BIT2_LINK_STATUS             BIT2    // 4
#define MII_SR_BIT1_JABBER_DET              BIT1    // 2
#define MII_SR_BIT0_EXT_CAP_REG_IMPL        BIT0    // 1

#define MII_REG_PHYID1			2  /* PHY Identification Register 1 */
#define MII_REG_PHYID2			3  /* PHY Identification Register 2 */

#define MII_REG_ANAR			4  /* A-N Advertisement Register */ 

#define MII_AR_BIT15_NEXT_PAGE              BIT15
#define MII_AR_BIT14_RECVD_LNK_PRTNR_CODE   BIT14
#define MII_AR_BIT13_REMOTE_FLT             BIT13
#define MII_AR_BIT12_100BASET4_CAP_PHY      BIT12       // 1000h
#define MII_AR_BIT11_100BASETFULDPLX_CAP_PHY BIT11      // 800h
#define MII_AR_BIT10_100BASETXHAFLDPLX_CAP_PHY BIT10    // 400h
#define MII_AR_BIT9_10BASETFULDPLX_CAP_PHY  BIT9        // 200h
#define MII_AR_BIT8_10BASETHALFDPLX_CAP_PHY BIT8        // 100h
#define MII_AR_8023CSMA_CAP_PHY             BIT0

#define MII_REG_ANLPAR			5  /* A-N Link Partner Ability Register */

#define MII_PAR_BIT15_NP        BIT15
#define MII_PAR_BIT14_ACK       BIT14
#define MII_PAR_BIT13_RF        BIT13
#define MII_PAR_BIT9_T4         BIT9
#define MII_PAR_BIT8_TX_FDX     BIT8    // 100h
#define MII_PAR_BIT7_HDX        BIT7    // 80h
#define MII_PAR_BIT6_10_FDX     BIT6
#define MII_PAR_BIT5_10_HDX     BIT5
#define MII_PAR_BIT0_CSMA       BIT0

#define MII_REG_ANER			6  /* A-N Expansion Register                   */
#define MII_REG_ANNPTR			7  /* A-N Next Page Transmit Register          */
#define MII_REG_ANLPRNPR		8  /* A-N Link Partner Received Next Page Reg. */

#define MII_REG_1000BASET_CRL	9  /* 1000 Base-T control*/

#define MII_GCR_BIT12_1000BASET4_CAP            BIT12    // 1000h
#define MII_GCR_BIT11_1000BASETFULDPLX_CAP      BIT11    // 800h
#define MII_GCR_BIT10_1000BASETXHAFLDPLX_CAP    BIT10    // 400h
#define MII_GCR_BIT9_1000HAFLDPLX_CAP           BIT9     // 200h
#define MII_GCR_BIT8_1000FLDPLX_CAP             BIT8     // 100h

#define MII_REG_1000BASET_STS	0xA  /* 1000 Base-T status */

#define MII_REG_EXTCR			0xB  /* Extended Register -- Control */
#define MII_REG_EXTDW			0xC  /* Extended Register -- Data Write */
#define MII_REG_EXTDR			0xD  /* Extended Register -- Data Read */
#define MII_REG_EXTMIISR		0xF  /* Extended -- MII Status */
#define MII_REG_MMD_CR			0xD  /* MMD Access -- Control */
#define MII_REG_MMD_RD			0xE  /* MMD Access -- Register/Data */
#define MII_REG_EXTSTATUS		0xF  /* Extended Status */

// Non-Standard MII Register definitions for the PHY used on iMX6
// includes Ateros and KZ PHY models

// MMFR register
#define ENET_MMFR_TA_VALUE  2
#define ENET_MMFR_OP_WRITE  1
#define ENET_MMFR_OP_READ   2
#define ENET_MMFR_ST_VALUE  1

#define ENET_MMFR_DATA_LSH  0
#define ENET_MMFR_TA_LSH    16
#define ENET_MMFR_RA_LSH    18
#define ENET_MMFR_PA_LSH    23
#define ENET_MMFR_OP_LSH    28
#define ENET_MMFR_ST_LSH    30

#define ENET_MMFR_DATA_WID  16
#define ENET_MMFR_TA_WID    2
#define ENET_MMFR_RA_WID    5
#define ENET_MMFR_PA_WID    5
#define ENET_MMFR_OP_WID    2
#define ENET_MMFR_ST_WID    2

// Bitfield macros that use rely on bitfield width/shift information
// defined in SOC header files
#define CSP_BITFMASK(bit) (((1U << (bit ## _WID)) - 1) << (bit ## _LSH))
#define CSP_BITFVAL(bit, val) ((val) << (bit ## _LSH))

// Make MII read/write commands for the external PHY
#define MII_READ_COMMAND(reg)           CSP_BITFVAL(ENET_MMFR_ST, ENET_MMFR_ST_VALUE)|\
                                        CSP_BITFVAL(ENET_MMFR_OP, ENET_MMFR_OP_READ)|\
                                        CSP_BITFVAL(ENET_MMFR_TA, ENET_MMFR_TA_VALUE)|\
                                        CSP_BITFVAL(ENET_MMFR_RA, reg & 0x1F)|\
                                        CSP_BITFVAL(ENET_MMFR_DATA, 0x0 & 0xFFFF)

#define MII_WRITE_COMMAND(reg, val)     CSP_BITFVAL(ENET_MMFR_ST, ENET_MMFR_ST_VALUE)|\
                                        CSP_BITFVAL(ENET_MMFR_OP, ENET_MMFR_OP_WRITE)|\
                                        CSP_BITFVAL(ENET_MMFR_TA, ENET_MMFR_TA_VALUE)|\
                                        CSP_BITFVAL(ENET_MMFR_RA, reg & 0x1F)|\
                                        CSP_BITFVAL(ENET_MMFR_DATA, val & 0xFFFF)




#endif // of __IMX6ENET_DXE_HW_H__
