/*
*
Copyright (c) Microsoft Corp. All rights reserved.
*
*/

#ifndef __IMX6ENET_DXE_H__
#define __IMX6ENET_DXE_H__

#include <Uefi.h>
#include <Uefi/UefiSpec.h>
#include <Base.h>

// Protocols used by this driver
#include <Protocol/SimpleNetwork.h>
#include <Protocol/ComponentName2.h>
#include <Protocol/PxeBaseCode.h>
#include <Protocol/DevicePath.h>

// Libraries used by this driver
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/NetLib.h>
#include <Library/DevicePathLib.h>

// ENET debug print macros

#define ENET_INIT(PRINT_OUT, ...) DEBUG((DEBUG_INIT, "ENET:" PRINT_OUT, ##__VA_ARGS__)) // DEBUG_INIT
#define ENET_RECV(PRINT_OUT, ...) DEBUG((DEBUG_INFO, "ENET:" PRINT_OUT, ##__VA_ARGS__)) // DEBUG_INFO  DEBUG_ERROR
#define ENET_SEND(PRINT_OUT, ...) DEBUG((DEBUG_INFO, "ENET:" PRINT_OUT, ##__VA_ARGS__))
#define ENET_PHY(PRINT_OUT, ...) DEBUG((DEBUG_INFO, "ENET:" PRINT_OUT, ##__VA_ARGS__)) 
#define ENET_MAC(PRINT_OUT, ...) DEBUG((DEBUG_INFO, "ENET:" PRINT_OUT, ##__VA_ARGS__)) 
#define ENET_INFO(PRINT_OUT, ...) DEBUG((DEBUG_INFO, "ENET:" PRINT_OUT, ##__VA_ARGS__))
#define ENET_WARNING(PRINT_OUT, ...) DEBUG((DEBUG_WARN, "ENET:" PRINT_OUT, ##__VA_ARGS__))
#define ENET_ERROR(PRINT_OUT, ...) DEBUG((DEBUG_ERROR, "ENET:" PRINT_OUT, ##__VA_ARGS__))

// choose one of MII modes to operate in
// NOTE: enable only ONE mode at at time

#define RGMII_MODE  3       // supports 10/100/1000 - use  it to enable 1 Gbit speed
//#define MII_MODE    1     // supports 10/100
//#define RMII_MODE   2     // supports 10/100

extern UINTN EFIAPI SerialPortWrite(IN UINT8* Buffer, IN UINTN NumberOfBytes);
#define SerialPrint(text)  SerialPortWrite((UINT8*)text, AsciiStrLen(text)+1);

// Numbers of buffer descriptors for receiving 
// larger number increases driver ability to operate in busy networks
#define LANENET_RX_RING_NUM_ENTRIES 32

// keep at 2 - changes to this number require modifications in SnpReceive()
#define LANENET_TX_RING_NUM_ENTRIES 2   

#define LANENET_SIGNATURE SIGNATURE_32('E', 'N', 'E', 'T')
#define INSTANCE_FROM_SNP_THIS(a) CR(a, LANENET_DRIVER, Snp, LANENET_SIGNATURE)

#include "EnetDxeHw.h"

// the buffer descriptor structure for the ENET Legacy Buffer Descriptor
// Receive & Transmit Buffer Descriptor definitions
// Note: The first BD must be aligned (see IMX6_CACHE_ALIGN_SIZE)

typedef struct  _ENET_BD 
{
    UINT16 DataLen;           // payload's length in bytes  volatile
    UINT16 ControlStatus;     // BD's status (see datasheet)
    UINT32 BufferAddressPA;   // ethernet frame buffer physical address 
} ENET_BD;


/*
*  LAN ENET Information Structure
*/

typedef struct _ENET_LANENET_DRIVER
{
    // Driver signature
    
    UINT32 Signature;
    EFI_HANDLE ControllerHandle;

    // EFI SNP protocol instances
    
    EFI_SIMPLE_NETWORK_PROTOCOL Snp;
    EFI_SIMPLE_NETWORK_MODE SnpMode;

    // EFI Snp statistics instance

    EFI_NETWORK_STATISTICS Stats;

    INT16 PhyAddress;
    UINT32 PhyId;

    // iMX6 ENET registers pointer
    volatile IMX6_ENET_REGISTERS* enetRegisters;

    // RECV control blocks

    volatile ENET_BD* RecvBDBasePtr __attribute__((aligned(16)));
    volatile ENET_BD* RecvBDPtrs[LANENET_RX_RING_NUM_ENTRIES] __attribute__((aligned(16)));
    UINT32 RecvBDs_Size;        // 8-64 * sizeof RxBD
    UINT32 RecvBDBase_Pa;       // points to block of RxBDs

    // virtual addresses of rx buffers to match RxBD->BufferAddressPA
    
    UINT8* RxBuffersPtr[LANENET_RX_RING_NUM_ENTRIES];       // local, aligned receive 8-64 buffers
    INT32 Rbd_index;
    BOOLEAN  ReceiverActivated;

    // SEND control blocks

    volatile ENET_BD* SendBDBasePtr __attribute__((aligned(16)));
    volatile ENET_BD* SendBDBPtrs[LANENET_TX_RING_NUM_ENTRIES] __attribute__((aligned(16)));
    UINT32 SendBDs_Size;     // 2 * sizeof TxBD
    UINT32 SendBD_Pa;        // points to block of TxBDs

    // virtual addresses of tx buffers to match TxBD->BufferAddressPA

    UINT8* TxBuffersPtr[LANENET_TX_RING_NUM_ENTRIES];       // local, aligned 2 transmit buffers
    UINT8* TxBuffCallerPtrs[LANENET_TX_RING_NUM_ENTRIES];   // saved caller buffer pointers
    INT32 tbd_index;
} LANENET_DRIVER;

#include "EnetDxeUtil.h"

extern UINT8 mZeroMac[NET_ETHER_ADDR_LEN];
extern EFI_DRIVER_BINDING_PROTOCOL    gSnpDxeBinding;
extern EFI_COMPONENT_NAME_PROTOCOL    gSnpDriverComponentName;
extern EFI_COMPONENT_NAME2_PROTOCOL   gSnpDriverComponentName2;

EFI_STATUS CleanOneBlockDescriptor_Rx(IN volatile ENET_BD* BDPtr, IN BOOLEAN IsLast);
EFI_STATUS CleanOneBlockDescriptor_Tx(IN volatile ENET_BD* BDPtr, IN BOOLEAN IsLast);
EFI_STATUS SetupEnetRegs(IN LANENET_DRIVER* LanDriverPtr);
EFI_STATUS SetBlockDescrRegs(IN LANENET_DRIVER* LanDriverPtr);

//  UEFI-Compliant function declarations for EFI_SIMPLE_NETWORK_PROTOCOL
// Refer to the Simple Network Protocol section (21.1) in the UEFI 2.3.1 Specification for related definitions

/*
 *  UEFI Start() function
 */
EFI_STATUS EFIAPI SnpStart(IN EFI_SIMPLE_NETWORK_PROTOCOL* Snp);

/*
 *  UEFI Stop() function
 */
EFI_STATUS EFIAPI SnpStop(IN EFI_SIMPLE_NETWORK_PROTOCOL* Snp);

/*
 *  UEFI Initialize() function
 */
EFI_STATUS EFIAPI SnpInitialize(IN EFI_SIMPLE_NETWORK_PROTOCOL* Snp,
  IN UINTN rx_buff_size,
  IN UINTN tx_buff_size);

/*
 *  UEFI Reset() function
 */
EFI_STATUS EFIAPI SnpReset(IN EFI_SIMPLE_NETWORK_PROTOCOL* Snp,
  IN BOOLEAN ext_ver);

/*
 *  UEFI Shutdown() function
 */
EFI_STATUS EFIAPI SnpShutdown(IN EFI_SIMPLE_NETWORK_PROTOCOL* Snp);

/*
 *  UEFI ReceiveFilters() function
 */
EFI_STATUS EFIAPI SnpReceiveFilters(IN EFI_SIMPLE_NETWORK_PROTOCOL* Snp,
  IN UINT32 enable,
  IN UINT32 disable,
  IN BOOLEAN reset_mfilter,
  IN UINTN num_mfilter,
  IN EFI_MAC_ADDRESS* mfilter);

/*
 *  UEFI StationAddress() function
 */
EFI_STATUS EFIAPI SnpStationAddress(IN EFI_SIMPLE_NETWORK_PROTOCOL* Snp,
  IN BOOLEAN reset,
  IN EFI_MAC_ADDRESS* new_maddr);

/*
 *  UEFI Statistics() function
 */
EFI_STATUS EFIAPI SnpStatistics(IN EFI_SIMPLE_NETWORK_PROTOCOL* Snp,
  IN BOOLEAN reset,
  IN OUT UINTN* stat_size,
  OUT EFI_NETWORK_STATISTICS* stat_table);

/*
 *  UEFI MCastIPtoMAC() function
 */
EFI_STATUS EFIAPI SnpMcastIptoMac(IN EFI_SIMPLE_NETWORK_PROTOCOL* Snp,
  IN BOOLEAN use_ipv6,
  IN EFI_IP_ADDRESS* ip_addr,
  OUT EFI_MAC_ADDRESS* mac_addr);

/*
 *  UEFI NvData() function
 */
EFI_STATUS EFIAPI SnpNvData(IN EFI_SIMPLE_NETWORK_PROTOCOL* Snp,
  IN BOOLEAN read_write,
  IN UINTN offset,
  IN UINTN buff_size,
  IN OUT VOID* data);

/*
 *  UEFI GetStatus() function
 */
EFI_STATUS EFIAPI SnpGetStatus(IN EFI_SIMPLE_NETWORK_PROTOCOL* Snp,
      OUT UINT32* irq_stat OPTIONAL,
      OUT VOID** tx_buff OPTIONAL);

/*
 *  UEFI Transmit() function
 */
EFI_STATUS EFIAPI SnpTransmit(IN EFI_SIMPLE_NETWORK_PROTOCOL* Snp,
  IN UINTN hdr_size,
  IN UINTN buff_size,
  IN VOID *data,
  IN EFI_MAC_ADDRESS* src_addr OPTIONAL,
  IN EFI_MAC_ADDRESS* dest_addr OPTIONAL,
  IN UINT16* protocol OPTIONAL);

/*
 *  UEFI Receive() function
 */
EFI_STATUS EFIAPI SnpReceive(IN EFI_SIMPLE_NETWORK_PROTOCOL* Snp,
      OUT UINTN* hdr_size OPTIONAL,
      IN  OUT UINTN* buff_size,
      OUT VOID* data,
      OUT EFI_MAC_ADDRESS* src_addr OPTIONAL,
      OUT EFI_MAC_ADDRESS* dest_addr OPTIONAL,
      OUT UINT16* protocol OPTIONAL);

/*
 *  UEFI GetDriverName() function
 */
EFI_STATUS EFIAPI SnpGetDriverName(IN EFI_COMPONENT_NAME2_PROTOCOL* Snp,
  IN CHAR8* Lang,
  OUT CHAR16** DriverName);

/*
 *  UEFI GetControllerName() function
 */
EFI_STATUS EFIAPI SnpGetControllerName(IN EFI_COMPONENT_NAME2_PROTOCOL* Cnp,
  IN EFI_HANDLE ControllerHandle,
  IN EFI_HANDLE ChildHandle OPTIONAL,
  IN CHAR8* Lang,
  OUT CHAR16** ControllerName);


#endif // of __IMX6ENET_DXE_H__
