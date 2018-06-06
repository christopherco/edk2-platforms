/*

Copyright (c) 2012-2014, ARM Limited. All rights reserved.
Copyright (c) Microsoft Corporation. All rights reserved.

This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

File name:

    Enet_MAC.c

Abstract:

    implements Ethernet MAC (ENET) MAC-address related functions
*/

#include "EnetDxe.h"
#include <iMX6.h>
#include <iMX6ClkPwr.h>
#include <Library/TimerLib.h>

// The leftmost 6 digits (24 bits) of a MAC address called a "prefix" is associated with the adapter manufacturer. d0:63:00
// The rightmost 6 digits (24 bits) of a MAC address represent an identification number for the specific device 00:00:00
// this is the default MAC address
// it will overwritten by values from OCOTP registers

UINT8 mZeroMac[NET_ETHER_ADDR_LEN] = { 0xD0, 0x63, 0x16, 0xE3, 0xD4, 0x61 };

/*
This function converts a multicast IP address to a multicast HW MAC address for all packet
transactions. If the mapping is accepted, then EFI_SUCCESS will be returned.

Arguments:
    SnpPtr      A pointer to the EFI_SIMPLE_NETWORK_PROTOCOL instance.
    IsIpv6      Set to TRUE if the multicast IP address is IPv6 [RFC 2460]. Set to FALSE if the multicast IP address is IPv4 [RFC 791].
    Ip          The multicast IP address that is to be converted to a multicast HW MAC address.
    McastMac    The multicast HW MAC address that is to be generated from IP.

Returns:
    EFI_SUCCESS or operation error status
*/
EFI_STATUS EFIAPI SnpMcastIptoMac(IN EFI_SIMPLE_NETWORK_PROTOCOL* SnpPtr,
                                IN BOOLEAN IsIpv6,
                                IN EFI_IP_ADDRESS* Ip,
                                OUT EFI_MAC_ADDRESS* McastMac)
{
    ENET_INFO("++SnpMcastIptoMac()\r\n");

    // Check Snp instance
    
    if(SnpPtr == NULL)
    {
        ENET_ERROR("ERROR: SnpMcastIptoMac null ptr\r\n");
        return EFI_INVALID_PARAMETER;
    }

    // Check that driver was started and initialised

    if(SnpPtr->Mode->State == EfiSimpleNetworkStarted)
    {
        ENET_WARNING("Warning: SnpMcastIptoMac Driver not initialized\r\n");
        return EFI_DEVICE_ERROR;
    } 
    else if(SnpPtr->Mode->State == EfiSimpleNetworkStopped) 
    {
        ENET_WARNING("Warning: SnpMcastIptoMac Driver in stopped state\r\n");
        return EFI_NOT_STARTED;
    }

    // Check parameters

    if((McastMac == NULL) || (Ip == NULL)) 
    {
        ENET_ERROR("ERROR: SnpMcastIptoMac bad parameter\r\n");
        return EFI_INVALID_PARAMETER;
    }

    // Make sure MAC address is empty

    ZeroMem(McastMac, sizeof(EFI_MAC_ADDRESS));

    // If we need ipv4 address

    if(IsIpv6 == FALSE) 
    {
        // Most significant 25 bits of a multicast HW address are set.
        // 01-00-5E is the IPv4 Ethernet Multicast Address (see RFC 1112)

        McastMac->Addr[0] = 0x01;
        McastMac->Addr[1] = 0x00;
        McastMac->Addr[2] = 0x5E;

        // Lower 23 bits from ipv4 address
        McastMac->Addr[3] = (Ip->v4.Addr[1] & 0x7F); // Clear the most significant bit (25th bit of MAC must be 0)
        McastMac->Addr[4] = Ip->v4.Addr[2];
        McastMac->Addr[5] = Ip->v4.Addr[3];
    } 
    else 
    {
        // Most significant 16 bits of multicast v6 HW address are set
        // 33-33 is the IPv6 Ethernet Multicast Address (see RFC 2464)

        McastMac->Addr[0] = 0x33;
        McastMac->Addr[1] = 0x33;

        // lower four octets are taken from ipv6 address

        McastMac->Addr[2] = Ip->v6.Addr[8];
        McastMac->Addr[3] = Ip->v6.Addr[9];
        McastMac->Addr[4] = Ip->v6.Addr[10];
        McastMac->Addr[5] = Ip->v6.Addr[11];
    }

    ENET_INFO("--SnpMcastIptoMac()=success\r\n");
    return EFI_SUCCESS;
}

/* SnpStationAddress

This function modifies or resets the current station address of a network interface, if supported. If
Reset is TRUE, then the current station address is set to the network interface’s permanent address.
If Reset is FALSE, and the network interface allows its station address to be modified, then the
current station address is changed to the address specified by New. If the network interface does not
allow its station address to be modified, then EFI_INVALID_PARAMETER will be returned. If the
station address is successfully updated on the network interface, EFI_SUCCESS will be returned. If
the driver has not been initialized, EFI_DEVICE_ERROR will be returned.

Arguments:

    SnpPtr  A pointer to the EFI_SIMPLE_NETWORK_PROTOCOL instance.
    Reset   Flag used to reset the station address to the ENET's permanent address.
    New     New station address to be used for the network interface.

Retrun values:

    EFI_SUCCESS            The ENET's station address was updated.
    EFI_NOT_STARTED        The ENET has not been started.
    EFI_INVALID_PARAMETER  One or more of the following conditions is TRUE :
                                      . The "New" station address is invalid.
                                      . "Reset" is FALSE and "New" is NULL.
    EFI_DEVICE_ERROR       The ENET has been started but not initialized.

*/
EFI_STATUS EFIAPI SnpStationAddress(IN EFI_SIMPLE_NETWORK_PROTOCOL* SnpPtr,
                    IN BOOLEAN Reset,
                    IN EFI_MAC_ADDRESS* NewMacAddrPtr)
{
    UINT32 Count;
    EFI_STATUS status = 0;
    EFI_TPL SavedTpl;
    UINT8 PermAddr[NET_ETHER_ADDR_LEN];
    LANENET_DRIVER* LanDriverPtr;
    ENET_INFO("++SnpStationAddress(reset=%d, new MAC addr %02X-%02X-%02X-%02X-%02X)\r\n",
                Reset,NewMacAddrPtr->Addr[0] & 0xFF, NewMacAddrPtr->Addr[1] & 0xFF,NewMacAddrPtr->Addr[2] & 0xFF,
                NewMacAddrPtr->Addr[3] & 0xFF,NewMacAddrPtr->Addr[4] & 0xFF,NewMacAddrPtr->Addr[5] & 0xFF);

    // Check Snp instance

    if(SnpPtr == NULL) 
    {
        ENET_ERROR( "--SnpStationAddress Snp is nul\r\n");
        return EFI_INVALID_PARAMETER;
    }

    SavedTpl = gBS->RaiseTPL(ENETIMX6_TPL);
    LanDriverPtr = INSTANCE_FROM_SNP_THIS(SnpPtr);

    // Check that driver was started and initialised

    if(SnpPtr->Mode->State == EfiSimpleNetworkStarted) 
    {
        ENET_WARNING( " SnpStationAddress Driver not initialized\r\n");
        goto EndSetStationAddress;
        status = EFI_DEVICE_ERROR;
    } 
    else if(SnpPtr->Mode->State == EfiSimpleNetworkStopped) 
    {
        ENET_WARNING( " SnpStationAddress Driver in stopped state\r\n");
        goto EndSetStationAddress;
        status = EFI_NOT_STARTED;
    }

    // Get the Permanent MAC address if need reset

    if(Reset==TRUE) 
    {    
        NewMacAddrPtr = (EFI_MAC_ADDRESS*)&mZeroMac;
    }
    else
    {
        // Otherwise use the specified new MAC address

        if(NewMacAddrPtr == NULL) 
        {
            ENET_ERROR( " ERROR SnpStationAddress invalid New parameter\r\n");
            status = EFI_INVALID_PARAMETER;
            goto EndSetStationAddress;
        }

        // If it is a multicast address, it is not valid.

        if(NewMacAddrPtr->Addr[0] & 0x01) 
        {
            ENET_ERROR( " ERROR SnpStationAddress invalid Address\r\n");
            status = EFI_INVALID_PARAMETER;
            goto EndSetStationAddress;
        }

        CopyMem(&SnpPtr->Mode->CurrentAddress, NewMacAddrPtr, NET_ETHER_ADDR_LEN);
    }

    // If packet reception is currently activated, stop and reset it,
    // set the new ethernet address and restart the packet reception.
    // Otherwise, nothing to do, the MAC address will be updated in
    // SnpReceiveFilters() when the UNICAST packet reception will be
    // activated.

    if(SnpPtr->Mode->ReceiveFilterSetting  != 0)
    {
        StopReceiver(LanDriverPtr);

        EnetSetMacAddress(LanDriverPtr, NewMacAddrPtr);

        StartReceiver(LanDriverPtr);
    }

EndSetStationAddress:
    gBS->RestoreTPL(SavedTpl);
    ENET_INFO("--SnpStationAddress()=%Xh\r\n", status);
    return status;
}

/* EnetGetMacAddressFromFuses

This function reads OCOTP registers from chip control module to compose hw MAC address from those.
It must be called when Enet is enabled, otherwise fefault values of 00000000 00008808 will be returned.

Arguments:

    SnpPtr  A pointer to the EFI_SIMPLE_NETWORK_PROTOCOL instance
    MacPtr  New MAC address to be used for the network interface

Retrun values:

    EFI_SUCCESS     The ENET's MAC address was retrieved.
    error code      operation failed with error code

*/
VOID EnetGetMacAddressFromFuses(IN EFI_SIMPLE_NETWORK_PROTOCOL* SnpPtr, OUT EFI_MAC_ADDRESS* MacPtr)
{
    const UINT32 RegOCOTP_CFG0Addr = 0x021BC410;
    const UINT32 RegOCOTP_CFG1Addr = 0x021BC420;
    const UINT32 RegOCOTP_MAC0Addr = 0x021BC620;
    const UINT32 RegOCOTP_MAC1Addr = 0x021BC630;
    EFI_TPL SavedTpl;
    LANENET_DRIVER* LanDriverPtr = NULL;
    ENET_INFO("++EnetGetMacAddressFromFuses()\r\n");

    LanDriverPtr = INSTANCE_FROM_SNP_THIS(SnpPtr);

    SavedTpl = gBS->RaiseTPL(TPL_CALLBACK);

    // read mac address from fuses 
    // Be prepared for OCOTP to return zeroes, which means hardware is not intialized properly

    mZeroMac[4] = MmioRead32(RegOCOTP_MAC0Addr)>>8; // 21BC620 mac_addr_high
    mZeroMac[5] = MmioRead32(RegOCOTP_MAC0Addr);
    mZeroMac[2] = MmioRead32(RegOCOTP_MAC1Addr)>>24; // 21BC630 mac_addr_low
    mZeroMac[3] = MmioRead32(RegOCOTP_MAC1Addr)>>16;
    mZeroMac[0] = MmioRead32(RegOCOTP_MAC1Addr)>>8;
    mZeroMac[1] = MmioRead32(RegOCOTP_MAC1Addr);
    ENET_INIT(" MAC address from OCOTP_MAC %02X-%02X-%02X-%02X-%02X-%02X\r\n", 
            mZeroMac[0], mZeroMac[1], mZeroMac[2], mZeroMac[3], mZeroMac[4], mZeroMac[5]);

    CopyMem((VOID*)MacPtr,& mZeroMac[0],sizeof(EFI_MAC_ADDRESS));
    gBS->RestoreTPL(SavedTpl);
    ENET_INFO("--EnetGetMacAddressFromFuses()\r\n");
}

/* EnetSetMacAddress

This function sets SNP MAC address from previosuly retrieved hardware MAC address.

Arguments:

    SnpPtr  A pointer to the EFI_SIMPLE_NETWORK_PROTOCOL instance
    MacPtr  New SNP MAC address to be used for the network interface

Retrun values:

    EFI_SUCCESS     The ENET's MAC address was copied into given variable
    error code      operation failed with error code

*/
VOID EnetSetMacAddress(IN LANENET_DRIVER* LanDriverPtr, IN EFI_MAC_ADDRESS* MacPtr)
{
    EFI_TPL SavedTpl;
    ENET_INFO("++EnetSetMacAddress(set %02X-%02X-%02X-%02X-%02X-%02X)\r\n",
                    MacPtr->Addr[0] & 0xFF, MacPtr->Addr[1] & 0xFF,MacPtr->Addr[2] & 0xFF,
                    MacPtr->Addr[3] & 0xFF,MacPtr->Addr[4] & 0xFF,MacPtr->Addr[5] & 0xFF);

    SavedTpl = gBS->RaiseTPL(TPL_CALLBACK);

    // PALR contains the lower 32 bits (bytes 0, 1, 2, 3) of the 48-bit address

    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->PALR,  ((MacPtr->Addr[0]<<24) |
                                                            (MacPtr->Addr[1]<<16) | (MacPtr->Addr[2]<<8) | (MacPtr->Addr[3])) );

    // PAUR contains the upper 16 bits (bytes 4 and 5) of the 48-bit address

    MmioWrite32((UINTN)&LanDriverPtr->enetRegisters->PAUR, 0x8808 + ((MacPtr->Addr[4]<<24) | (MacPtr->Addr[5]<<16)) );

    ENET_INFO("EnetSetMacAddress() PALR=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->PALR));
    ENET_INFO("EnetSetMacAddress() PAUR=%08Xh\r\n", MmioRead32((UINTN)&LanDriverPtr->enetRegisters->PAUR));
    gBS->RestoreTPL(SavedTpl);
    ENET_INFO("--EnetSetMacAddress()\r\n");
}
