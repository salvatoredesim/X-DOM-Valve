#ifndef __BLUENRG1_GAP_ACI_H__
#define __BLUENRG1_GAP_ACI_H__


/**
  ******************************************************************************
  * @file    bluenrg1_gap_aci.h
  * @author  AMS - VMA RF Application team
  * @version V1.0.0
  * @date    21-Sept-2015
  * @brief   Header file for BlueNRG-1 Bluetooth Low Energy stack APIs
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  ******************************************************************************
  */
#include "bluenrg1_types.h"
/** Documentation for Whitelist_Entry_t */
typedef struct Whitelist_Entry_t_s {
  uint8_t Peer_Address_Type /** 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use */;
  uint8_t Peer_Address[6] /** Public Device Address or Random Device Address of the device
to be added to the white list. */;
} Whitelist_Entry_t;
/** Documentation for Bonded_Device_Entry_t */
typedef struct Bonded_Device_Entry_t_s {
  uint8_t Address_Type /** 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use */;
  uint8_t Address[6] /** Public Device Address or Random Device Address of the device
to be added to the white list. */;
} Bonded_Device_Entry_t;
/**
  * @brief Put the device in non-discoverable mode. This command will disable the LL advertising and
put the device in standby state.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_non_discoverable(void);
/**
  * @brief Put the device in limited discoverable mode (as defined in Bluetooth Specification v.4.1,
Vol. 3, Part C, section 9.2.3). The device will be discoverable for maximum period of TGAP
(lim_adv_timeout) = 180 seconds (from errata). The advertising can be disabled at any time
by issuing @ref aci_gap_set_non_discoverable command.
The Adv_Interval_Min and Adv_Interval_Max parameters are optional. If both are set to 0,
the GAP will use default values for adv intervals for limited discoverable mode (250 ms
and 500 ms respectively).
To allow a fast connection, the host can set Local_Name, Service_Uuid_List,
Slave_Conn_Interval_Min and Slave_Conn_Interval_Max. If provided, these data will be 
inserted into the advertising packet payload as AD data. These parameters are optional
in this command. These values can be set in advertised data using GAP_Update_Adv_Data
command separately.
The total size of data in advertising packet cannot exceed 31 bytes.
With this command, the BLE Stack will also add automatically the following
standard AD types:
- AD Flags
- Power Level
When advertising timeout happens (i.e. limited discovery period has elapsed), controller generates
@ref aci_gap_limited_discoverable_event event. 
  * @param Advertising_Type 0x00 Connectable undirected advertising (ADV_IND) (default)
0x02 Scannable undirected advertising (ADV_SCAN_IND)
0x03 Non connectable undirected advertising (ADV_NONCONN_IND)
0x04 - 0xFF Reserved for future use
  * @param Advertising_Interval_Min Minimum advertising interval.
Range: 0x0020 to 0x4000
Time = N * 0.625 msec
Time Range: 20 ms to 10.24 sec
  * @param Advertising_Interval_Max Maximum advertising interval.
Range: 0x0020 to 0x4000
Time = N * 0.625 msec
Time Range: 20 ms to 10.24 sec
  * @param Own_Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Advertising_Filter_Policy 0x00 Allow Scan Request from Any, Allow Connect Request from Any (default).
0x01 Allow Scan Request from White List Only, Allow Connect Request from Any.
0x02 Allow Scan Request from Any, Allow Connect Request from White List Only.
0x03 Allow Scan Request from White List Only, Allow Connect Request from White List Only.
0x04 - 0xFF Reserved for future use.
  * @param Local_Name_Length Length of the Local name string in octets.
If length is set to 0x00, Local_Name parameter should not be used.
  * @param Local_Name Local name of the device.
This is an ASCII string without NULL character.
  * @param Service_Uuid_length Length of the Service Uuid List in octets.
If there is no service to be advertised, set this field to 0x00.
  * @param Service_Uuid_List This is the list of the UUIDs AD Types as defined in Volume 3,
Section 11.1.1 of GAP Specification.
  * @param Slave_Conn_Interval_Min Slave connection interval minimum value suggested by Peripheral.
If Slave_Conn_Interval_Min and Slave_Conn_Interval_Max are not 0x0000,
Slave Connection Interval Range AD structure will be added in advertising
data.
Connection interval is defined in the following manner:
connIntervalmin = Slave_Conn_Interval_Min x 1.25ms
Slave_Conn_Interval_Min range: 0x0006 to 0x0C80
Value of 0xFFFF indicates no specific minimum.
  * @param Slave_Conn_Interval_Max Slave connection interval maximum value suggested by Peripheral.
If Slave_Conn_Interval_Min and Slave_Conn_Interval_Max are not 0x0000,
Slave Connection Interval Range AD structure will be added in advertising
data.
Connection interval is defined in the following manner:
connIntervalmax = Slave_Conn_Interval_Max x 1.25ms
Slave_Conn_Interval_Max range: 0x0006 to 0x0C80
Value of 0xFFFF indicates no specific maximum.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_limited_discoverable(uint8_t Advertising_Type,
                                            uint16_t Advertising_Interval_Min,
                                            uint16_t Advertising_Interval_Max,
                                            uint8_t Own_Address_Type,
                                            uint8_t Advertising_Filter_Policy,
                                            uint8_t Local_Name_Length,
                                            uint8_t Local_Name[],
                                            uint8_t Service_Uuid_length,
                                            uint8_t Service_Uuid_List[],
                                            uint16_t Slave_Conn_Interval_Min,
                                            uint16_t Slave_Conn_Interval_Max);
/**
  * @brief Put the device in general discoverable mode (as defined in Bluetooth Specification v.4.1,
Vol. 3, Part C, section 9.2.4). The device will be discoverable until the host issues 
the @ref aci_gap_set_non_discoverable command. The Adv_Interval_Min and Adv_Interval_Max
parameters are optional. If both are set to 0, the GAP uses the default values for adv
intervals for general discoverable mode.
When using connectable undirected advertising events:
- Adv_Interval_Min = 30 ms 
- Adv_Interval_Max = 60 ms
When using non-connectable advertising events or scannable undirected advertising events:
- Adv_Interval_Min = 100 ms 
- Adv_Interval_Max = 150 ms 
Host can set the Local Name, a Service UUID list and the Slave Connection Interval Range.
If provided, these data will be inserted into the advertising packet payload as AD data.
These parameters are optional in this command. These values can be also set using
aci_gap_update_adv_data() separately.
The total size of data in advertising packet cannot exceed 31 bytes.
With this command, the BLE Stack will also add automatically the following standard
AD types:
- AD Flags
- TX Power Level
  * @param Advertising_Type 0x00 Connectable undirected advertising (ADV_IND) (default)
0x02 Scannable undirected advertising (ADV_SCAN_IND)
0x03 Non connectable undirected advertising (ADV_NONCONN_IND)
0x04 - 0xFF Reserved for future use
  * @param Advertising_Interval_Min Minimum advertising interval.
Range: 0x0020 to 0x4000
Time = N * 0.625 msec
Time Range: 20 ms to 10.24 sec
  * @param Advertising_Interval_Max Maximum advertising interval.
Range: 0x0020 to 0x4000
Time = N * 0.625 msec
Time Range: 20 ms to 10.24 sec
  * @param Own_Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Advertising_Filter_Policy 0x00 Allow Scan Request from Any, Allow Connect Request from Any (default).
0x01 Allow Scan Request from White List Only, Allow Connect Request from Any.
0x02 Allow Scan Request from Any, Allow Connect Request from White List Only.
0x03 Allow Scan Request from White List Only, Allow Connect Request from White List Only.
0x04 - 0xFF Reserved for future use.
  * @param Local_Name_Length Length of the Local name string in octets.
If length is set to 0x00, Local_Name parameter should not be used.
  * @param Local_Name Local name of the device.
This is an ASCII string without NULL character.
  * @param Service_Uuid_length Length of the Service Uuid List in octets.
If there is no service to be advertised, set this field to 0x00.
  * @param Service_Uuid_List This is the list of the UUIDs AD Types as defined in Volume 3,
Section 11.1.1 of GAP Specification.
  * @param Slave_Conn_Interval_Min Slave connection interval minimum value suggested by Peripheral.
If Slave_Conn_Interval_Min and Slave_Conn_Interval_Max are not 0x0000,
Slave Connection Interval Range AD structure will be added in advertising
data.
Connection interval is defined in the following manner:
connIntervalmin = Slave_Conn_Interval_Min x 1.25ms
Slave_Conn_Interval_Min range: 0x0006 to 0x0C80
Value of 0xFFFF indicates no specific minimum.
  * @param Slave_Conn_Interval_Max Slave connection interval maximum value suggested by Peripheral.
If Slave_Conn_Interval_Min and Slave_Conn_Interval_Max are not 0x0000,
Slave Connection Interval Range AD structure will be added in advertising
data.
Connection interval is defined in the following manner:
connIntervalmax = Slave_Conn_Interval_Max x 1.25ms
Slave_Conn_Interval_Max range: 0x0006 to 0x0C80
Value of 0xFFFF indicates no specific maximum.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_discoverable(uint8_t Advertising_Type,
                                    uint16_t Advertising_Interval_Min,
                                    uint16_t Advertising_Interval_Max,
                                    uint8_t Own_Address_Type,
                                    uint8_t Advertising_Filter_Policy,
                                    uint8_t Local_Name_Length,
                                    uint8_t Local_Name[],
                                    uint8_t Service_Uuid_length,
                                    uint8_t Service_Uuid_List[],
                                    uint16_t Slave_Conn_Interval_Min,
                                    uint16_t Slave_Conn_Interval_Max);
/**
  * @brief Set the device in direct connectable mode (as defined in Bluetooth Specification v.4.1,
Vol. 3, Part C, section 9.3.3). Device uses direct connectable mode to advertise using High Duty
cycle advertisement events or Low Duty cycle advertisement events and the address as
either what is specified in the Own Address Type parameter. The command specifies the type of the advertising used.
If the privacy is enabled, the Type parameter in reconnection address is used for advertising, otherwise the address
of the type specified in OwnAddrType is used.
The device will be in directed connectable mode only for 1.28 seconds. If no connection
is established within this duration, the device enters non discoverable mode and
advertising will have to be again enabled explicitly.
The controller generates a @ref hci_le_connection_complete_event event with the status set to
HCI_DIRECTED_ADV_TIMEOUT if the connection was not established and 0x00 if the
connection was successfully established.
  * @param Own_Address_Type 0x00: Public device address (default)
0x01: Random device address
  * @param Directed_Advertising_Type Type of directed advertising.
0x01: High Duty Cycle Directed Advertising,
0x04: Low Duty Cycle Directed Advertising
  * @param Direct_Address_Type 0x00: Public device address (default)
0x01: Random device address
  * @param Direct_Address Initiator Bluetooth address
  * @param Advertising_Interval_Min Minimum advertising interval.
Range: 0x0020 to 0x4000
Time = N * 0.625 msec
Time Range: 20 ms to 10.24 sec
  * @param Advertising_Interval_Max Maximum advertising interval.
Range: 0x0020 to 0x4000
Time = N * 0.625 msec
Time Range: 20 ms to 10.24 sec
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_direct_connectable(uint8_t Own_Address_Type,
                                          uint8_t Directed_Advertising_Type,
                                          uint8_t Direct_Address_Type,
                                          uint8_t Direct_Address[6],
                                          uint16_t Advertising_Interval_Min,
                                          uint16_t Advertising_Interval_Max);
/**
  * @brief Set the IO capabilities of the device. This command has to be given only when the device is
not in a connected state.

  * @param IO_Capability IO capability of the device:
0x00: 'IO_CAP_DISPLAY_ONLY',
0x01: 'IO_CAP_DISPLAY_YES_NO',
0x02: 'IO_CAP_KEYBOARD_ONLY',
0x03: 'IO_CAP_NO_INPUT_NO_OUTPUT',
0x04: 'IO_CAP_KEYBOARD_DISPLAY
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_io_capability(uint8_t IO_Capability);
/**
  * @brief Set the authentication requirements for the device. If the OOB_Enable is set to 0, the
following 16 octets of OOB_Data will be ignored on reception. This command has to be
given only when the device is not in a connected state.
  * @param MITM_Mode 0 = MITM protection not required,
1 = MITM protection required
  * @param OOB_Enable 0 = OOB data is not available,
1 = OOB data is available and specified in OOB_Data
  * @param OOB_Data Out-Of-Band data
  * @param Min_Encryption_Key_Size Minimum size of the encryption key to be used during the pairing process
  * @param Max_Encryption_Key_Size Maximum size of the encryption key to be used during the pairing process
  * @param Use_Fixed_Pin If set to 0x00, then during the pairing process
the application will not be requested for a pin (Fixed_Pin will be used).
If set to 0x01, then during pairing process if a
passkey is required the application will be
notified
  * @param Fixed_Pin Fixed pin to be used during pairing if MIMT protection is enabled.
Any random value between 0 to 999999
  * @param Bonding_Mode Only if bonding is enabled (0x01), the bonding
information is stored in flash
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_authentication_requirement(uint8_t MITM_Mode,
                                                  uint8_t OOB_Enable,
                                                  uint8_t OOB_Data[16],
                                                  uint8_t Min_Encryption_Key_Size,
                                                  uint8_t Max_Encryption_Key_Size,
                                                  uint8_t Use_Fixed_Pin,
                                                  uint32_t Fixed_Pin,
                                                  uint8_t Bonding_Mode);
/**
  * @brief Set the authorization requirements of the device. This command has to be given when connected
to a device if authorization is required to access services which require authorization.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Authorization_Enable 0x00: Authorization not required (default)
0x01: Authorization required. This enables the authorization in the device
and when a remote device tries to read/write a characeristic with authorization
requirements, the stack will send back an error response with
"Insufficient authorization" error code. After pairing is complete a
ACI_GAP_AUTHORIZATION_REQ_EVENT will be sent to the Host.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_authorization_requirement(uint16_t Connection_Handle,
                                                 uint8_t Authorization_Enable);
/**
  * @brief This command should be send by the host in response to @ref aci_gap_pass_key_req_event
event. The command parameter contains the pass key which will be used during the pairing
process.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Pass_Key Pass key that will be used during the pairing process. 
Must be a number between 0 and 999999.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_pass_key_resp(uint16_t Connection_Handle,
                                 uint32_t Pass_Key);
/**
  * @brief Authorize a device to access attributes. This command should be send by the host in
response to @ref aci_gap_authorization_req_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Authorize authorization response:
0x01 : Authorize (accept connection)
0x02 : Reject (reject connection)
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_authorization_resp(uint16_t Connection_Handle,
                                      uint8_t Authorize);
/**
  * @brief Initialize the GAP layer. Register the GAP service with the GATT.
All the standard GAP characteristics will also be added:
- Device Name
- Appearance
- Peripheral Preferred Connection Parameters (peripheral role only)
  * @param Role Bitmap of allowed roles:
0x01 : Peripheral
0x02 : Broadcaster
0x04 : Central
0x08 : Observer
  * @param privacy_enabled 0x00: Privacy is not enabled.
0x01: Privacy is enabled.
  * @param device_name_char_len Length of the device name characteristic
  * @param[out] Service_Handle Handle of the GAP service
  * @param[out] Dev_Name_Char_Handle Device Name Characteristic handle
  * @param[out] Appearance_Char_Handle Appearance Characteristic handle
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_init(uint8_t Role,
                        uint8_t privacy_enabled,
                        uint8_t device_name_char_len,
                        uint16_t *Service_Handle,
                        uint16_t *Dev_Name_Char_Handle,
                        uint16_t *Appearance_Char_Handle);
/**
  * @brief Put the device into non connectable mode. This mode does not support connection. The
privacy setting done in the @ref aci_gap_init command plays a role in deciding the valid 
parameters for this command.
  * @param Advertising_Event_Type 0x02 = Scannable undirected advertising (ADV_SCAN_IND)
0x03 = Non connectable undirected advertising (ADV_NONCONN_IND)
  * @param Own_Address_Type If Privacy is disabled, then the address can be
0x00: Public address
0x01: Static random address
If Privacy is enabled, then the address can be 
0x02 : Resolvable private address
0x03 : Non-resolvable private address
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_non_connectable(uint8_t Advertising_Event_Type,
                                       uint8_t Own_Address_Type);
/**
  * @brief Put the device into undirected connectable mode.
If privacy is enabled in the device, a resolvable private address is generated and used as the 
advertiser's address. If not, the address of the type specified in own_addr_type is used for
advertising.
  * @param Adv_Filter_Policy 0x00 Allow Scan Request from Any, Allow Connect Request from Any.
0x03 Allow Scan Request from White List Only, Allow Connect Request from White List Only.
  * @param Own_Address_Type If Privacy is disabled, then the address can be
0x00: Public address
0x01: Static random address
If Privacy is enabled, then the address can be 
0x02 : Resolvable private address
0x03 : Non-resolvable private address
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_undirected_connectable(uint8_t Adv_Filter_Policy,
                                              uint8_t Own_Address_Type);
/**
  * @brief Send a slave security request to the master.
This command has to be issued to notify the master of the security requirements of the slave.
The master may encrypt the link, initiate the pairing procedure, or reject the request.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Bonding 0x00 = No bonding,
0x01 = Bonding required
  * @param MITM_Protection 0 = MITM protection not required,
1 = MITM protection required
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_slave_security_req(uint16_t Connection_Handle,
                                      uint8_t Bonding,
                                      uint8_t MITM_Protection);
/**
  * @brief This command can be used to update the advertising data for a particular AD type. If the AD
type specified does not exist, then it is added to the advertising data. If the overall
advertising data length is more than 31 octets after the update, then the command is
rejected and the old data is retained.
  * @param AdvDataLen Length of AdvData in octets
  * @param AdvData Advertising data used by the device while advertising.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_update_adv_data(uint8_t AdvDataLen,
                                   uint8_t AdvData[]);
/**
  * @brief This command can be used to delete the specified AD type from the advertisement data if
present.
  * @param ADType One of the AD types like in Bluetooth specification (see volume 3, Part C, 11.1)
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_delete_ad_type(uint8_t ADType);
/**
  * @brief This command can be used to get the current security settings of the device.
  * @param[out] MITM_Mode 0 = MITM protection not required,
1 = MITM protection required
  * @param[out] Bonding_Mode Only if bonding is enabled (0x01), the bonding
information is stored in flash
  * @param[out] OOB_Enable 0 = OOB data is not available,
1 = OOB data is available and specified in OOB_Data
  * @param[out] Passkey_required 0x00 = Passkey not required,
0x01 = Fixed pin is present which is being used,
0x02 = Passkey required for pairing. An event will be generated when required.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_get_security_level(uint8_t *MITM_Mode,
                                      uint8_t *Bonding_Mode,
                                      uint8_t *OOB_Enable,
                                      uint8_t *Passkey_required);
/**
  * @brief It allows masking events from the GAP. The default configuration is all the events masked.
  * @param GAP_Evt_Mask 0x0000 No events specified,
0x0001 ACI_GAP_LIMITED_DISCOVERABLE_EVENT,
0x0002 ACI_GAP_PAIRING_COMPLETE_EVENT,
0x0004 ACI_GAP_PASS_KEY_REQ_EVENT,
0x0008 ACI_GAP_AUTHORIZATION_REQ_EVENT,
0x0010 ACI_GAP_SLAVE_SECURITY_INITIATED_EVENT,
0x0020 ACI_GAP_BOND_LOST_EVENT,
0x0080 ACI_GAP_PROC_COMPLETE_EVENT,
0x0100 ACI_L2CAP_CONNECTION_UPDATE_REQ_EVENT,
0x0200 ACI_L2CAP_CONNECTION_UPDATE_RESP_EVENT,
0x0400 ACI_L2CAP_PROC_TIMEOUT_EVENT,
0x0800 ACI_GAP_ADDR_NOT_RESOLVED_EVENT,
0xFFFF Default
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_event_mask(uint16_t GAP_Evt_Mask);
/**
  * @brief Add addresses of bonded devices into the controller's whitelist.
The command will return an error if there are no devices in the database or if it was  
unable to add the device into the whitelist.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_configure_whitelist(void);
/**
  * @brief Command the controller to terminate the connection.
A @ref hci_disconnection_complete_event event will be generated when the link is disconnected. It is important to leave an 100 ms blank window
before sending any new command (including system hardware reset), since immediately after @ref hci_disconnection_complete_event event,
system could save important information in non volatile memory.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Reason Authentication Failure error code (0x05), Other End Terminated Connection error codes (0x13-0x15),
Unsupported Remote Feature error code(0x1A) and Pairing with Unit Key Not Supported error code (0x29)
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_terminate(uint16_t Connection_Handle,
                             uint8_t Reason);
/**
  * @brief Clear the security database. All the devices in the security database will be removed.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_clear_security_db(void);
/**
  * @brief Allows the security manager to complete the pairing procedure and re-bond with the master.
This command should be given by the application when it receives the
ACI_GAP_BOND_LOST_EVENT if it wants the re-bonding to happen successfully. If this
command is not given on receiving the event, the bonding procedure will timeout.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_allow_rebond(uint16_t Connection_Handle);
/**
  * @brief Start the limited discovery procedure. The controller is commanded to start active scanning.
When this procedure is started, only the devices in limited discoverable mode are returned
to the upper layers.
The procedure is terminated when either the upper layers issue a command to terminate 
the procedure by issuing the command @ref aci_gap_terminate_gap_proc with the procedure 
code set to 0x01 or a timeout happens. When the procedure is terminated due to any of the 
above  reasons, @ref aci_gap_proc_complete_event event is returned with the procedure code
set to 0x01.
The device found when the procedure is ongoing is returned to the upper layers through the
event @ref hci_le_advertising_report_event.
  * @param LE_Scan_Interval This is defined as the time interval from when the Controller started
its last LE scan until it begins the subsequent LE scan.
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10240 msec
  * @param LE_Scan_Window Amount of time for the duration of the LE scan. LE_Scan_Window
shall be less than or equal to LE_Scan_Interval
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10.24 seconds
  * @param Own_Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Filter_Duplicates 0x00 Duplicate filtering disabled.
0x01 Duplicate filtering enabled.
0x02 - 0xFF Reserved for future use.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_start_limited_discovery_proc(uint16_t LE_Scan_Interval,
                                                uint16_t LE_Scan_Window,
                                                uint8_t Own_Address_Type,
                                                uint8_t Filter_Duplicates);
/**
  * @brief Start the general discovery procedure. The controller is commanded to start active
scanning. The procedure is terminated when  either the upper layers issue a command
to terminate the procedure by issuing the command @ref aci_gap_terminate_gap_proc
with the procedure code set to 0x02 or a timeout happens. When the procedure is
terminated due to any of the above reasons, @ref aci_gap_proc_complete_event event
is returned with the procedure code set to 0x02. The device found when the procedure
is ongoing is returned to @ref hci_le_advertising_report_event.
  * @param LE_Scan_Interval This is defined as the time interval from when the Controller started
its last LE scan until it begins the subsequent LE scan.
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10240 msec
  * @param LE_Scan_Window Amount of time for the duration of the LE scan. LE_Scan_Window
shall be less than or equal to LE_Scan_Interval
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10.24 seconds
  * @param Own_Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Filter_Duplicates 0x00 Duplicate filtering disabled.
0x01 Duplicate filtering enabled.
0x02 - 0xFF Reserved for future use.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_start_general_discovery_proc(uint16_t LE_Scan_Interval,
                                                uint16_t LE_Scan_Window,
                                                uint8_t Own_Address_Type,
                                                uint8_t Filter_Duplicates);
/**
  * @brief Start the name discovery procedure. A LE_Create_Connection call will be made to the
controller by GAP with the initiator filter policy set to "ignore whitelist and process
connectable advertising packets only for the specified device". Once a connection is
established, GATT procedure is started to read the device name characteristic. When the
read is completed (successfully or unsuccessfully), a @ref aci_gap_proc_complete_event
event is given to the upper layer. The event also contains the name of the device if the
device name was read successfully.
  * @param LE_Scan_Interval This is defined as the time interval from when the Controller started
its last LE scan until it begins the subsequent LE scan.
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10240 msec
  * @param LE_Scan_Window Amount of time for the duration of the LE scan. LE_Scan_Window
shall be less than or equal to LE_Scan_Interval
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10.24 seconds
  * @param Peer_Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Peer_Address Public Device Address or Random Device Address of the device
to be connected
  * @param Own_Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Conn_Interval_Min N = 0xXXXX    Minimum value for the connection event interval. This shall be less
than or equal to Conn_Interval_Max.
Range: 0x0006 to 0x0C80
Time = N * 1.25 msec
Time Range: 7.5 msec to 4 seconds.
0x0000 - 0x0005 and 0x0C81 - 0xFFFF Reserved for future use
  * @param Conn_Interval_Max N = 0xXXXX    Maximum value for the connection event interval. This shall be
greater than or equal to Conn_Interval_Min.
Range: 0x0006 to 0x0C80
Time = N * 1.25 msec
Time Range: 7.5 msec to 4 seconds.
0x0000 - 0x0005 and 0x0C81 - 0xFFFF Reserved for future use
  * @param Conn_Latency Slave latency for the connection in number of connection events.
Range: 0x0000 to 0x01F3
  * @param Supervision_Timeout N = 0xXXXX    Supervision timeout for the LE Link. (See [Vol 6] Part B, Section
4.5.2)
Range: 0x000A to 0x0C80
Time = N * 10 msec
Time Range: 100 msec to 32 seconds
0x0000 - 0x0009 and
0x0C81 - 0xFFFF Reserved for future use
  * @param Minimum_CE_Length Information parameter about the minimum length of connection
needed for this LE connection.
Range: 0x0000 - 0xFFFF
Time = N * 0.625 msec.
  * @param Maximum_CE_Length Information parameter about the maximum length of connection needed
for this LE connection.
Range: 0x0000 - 0xFFFF
Time = N * 0.625 msec.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_start_name_discovery_proc(uint16_t LE_Scan_Interval,
                                             uint16_t LE_Scan_Window,
                                             uint8_t Peer_Address_Type,
                                             uint8_t Peer_Address[6],
                                             uint8_t Own_Address_Type,
                                             uint16_t Conn_Interval_Min,
                                             uint16_t Conn_Interval_Max,
                                             uint16_t Conn_Latency,
                                             uint16_t Supervision_Timeout,
                                             uint16_t Minimum_CE_Length,
                                             uint16_t Maximum_CE_Length);
/**
  * @brief Start the auto connection establishment procedure. The devices specified are added to the
white list of the controller and a LE_Create_Connection call will be made to the controller by
GAP with the initiator filter policy set to "use whitelist to determine which advertiser to
connect to". When a command is issued to terminate the procedure by upper layer, a
LE_Create_Connection_Cancel call will be made to the controller by GAP.
The procedure is terminated when either a connection is successfully established with one of
the specified devices in the white list or the procedure is explicitly terminated by issuing
the command @ref aci_gap_terminate_gap_proc with the procedure code set to 0x08. A
@ref aci_gap_proc_complete_event event is returned with the procedure code set to 0x08.
  * @param LE_Scan_Interval This is defined as the time interval from when the Controller started
its last LE scan until it begins the subsequent LE scan.
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10240 msec
  * @param LE_Scan_Window Amount of time for the duration of the LE scan. LE_Scan_Window
shall be less than or equal to LE_Scan_Interval
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10.24 seconds
  * @param Own_Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Conn_Interval_Min N = 0xXXXX    Minimum value for the connection event interval. This shall be less
than or equal to Conn_Interval_Max.
Range: 0x0006 to 0x0C80
Time = N * 1.25 msec
Time Range: 7.5 msec to 4 seconds.
0x0000 - 0x0005 and 0x0C81 - 0xFFFF Reserved for future use
  * @param Conn_Interval_Max N = 0xXXXX    Maximum value for the connection event interval. This shall be
greater than or equal to Conn_Interval_Min.
Range: 0x0006 to 0x0C80
Time = N * 1.25 msec
Time Range: 7.5 msec to 4 seconds.
0x0000 - 0x0005 and 0x0C81 - 0xFFFF Reserved for future use
  * @param Conn_Latency Slave latency for the connection in number of connection events.
Range: 0x0000 to 0x01F3
  * @param Supervision_Timeout N = 0xXXXX    Supervision timeout for the LE Link. (See [Vol 6] Part B, Section
4.5.2)
Range: 0x000A to 0x0C80
Time = N * 10 msec
Time Range: 100 msec to 32 seconds
0x0000 - 0x0009 and
0x0C81 - 0xFFFF Reserved for future use
  * @param Minimum_CE_Length Information parameter about the minimum length of connection
needed for this LE connection.
Range: 0x0000 - 0xFFFF
Time = N * 0.625 msec.
  * @param Maximum_CE_Length Information parameter about the maximum length of connection needed
for this LE connection.
Range: 0x0000 - 0xFFFF
Time = N * 0.625 msec.
  * @param Num_of_Whitelist_Entries Number of devices that have to be added to the whitelist.
  * @param Whitelist_Entry See @ref Whitelist_Entry_t
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_start_auto_connection_establish_proc(uint16_t LE_Scan_Interval,
                                                        uint16_t LE_Scan_Window,
                                                        uint8_t Own_Address_Type,
                                                        uint16_t Conn_Interval_Min,
                                                        uint16_t Conn_Interval_Max,
                                                        uint16_t Conn_Latency,
                                                        uint16_t Supervision_Timeout,
                                                        uint16_t Minimum_CE_Length,
                                                        uint16_t Maximum_CE_Length,
                                                        uint8_t Num_of_Whitelist_Entries,
                                                        Whitelist_Entry_t Whitelist_Entry[]);
/**
  * @brief Start a general connection establishment procedure. The host enables scanning in the
controller with the scanner filter policy set to "accept all advertising packets" and from the
scanning results, all the devices are sent to the upper layer using the event
LE_Advertising_Report. The upper layer then has to select one of the devices to which it
wants to connect by issuing the command @ref aci_gap_create_connection. If privacy is
enabled, then either a private resolvable address or a non resolvable address, based on the
address type specified in the command is set as the scanner address but the gap create
connection always uses a private resolvable address if the general connection
establishment procedure is active.
The procedure is terminated when a connection is established or the upper layer terminates
the procedure by issuing the command @ref aci_gap_terminate_gap_proc with the procedure
code set to 0x10. On completion of the procedure a @ref aci_gap_proc_complete_event event
is generated with the procedure code set to 0x10.
  * @param LE_Scan_Type 0x00 Passive Scanning. No SCAN_REQ packets shall be sent.(default)
0x01 Active scanning. SCAN_REQ packets may be sent.
0x02 - 0xFF Reserved for future use
  * @param LE_Scan_Interval This is defined as the time interval from when the Controller started
its last LE scan until it begins the subsequent LE scan.
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10240 msec
  * @param LE_Scan_Window Amount of time for the duration of the LE scan. LE_Scan_Window
shall be less than or equal to LE_Scan_Interval
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10.24 seconds
  * @param Own_Address_Type If Privacy is disabled, then the address can be
0x00: Public address
0x01: Static random address
If Privacy is enabled, then the address can be 
0x02 : Resolvable private address
0x03 : Non-resolvable private address
  * @param Filter_Duplicates 0x00 Duplicate filtering disabled.
0x01 Duplicate filtering enabled.
0x02 - 0xFF Reserved for future use.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_start_general_connection_establish_proc(uint8_t LE_Scan_Type,
                                                           uint16_t LE_Scan_Interval,
                                                           uint16_t LE_Scan_Window,
                                                           uint8_t Own_Address_Type,
                                                           uint8_t Filter_Duplicates);
/**
  * @brief Start a selective connection establishment procedure. The GAP adds the specified device
addresses into white list and enables scanning in the controller with the scanner filter policy
set to "accept packets only from devices in whitelist". All the devices found are sent to the
upper layer by the event @ref hci_le_advertising_report_event. The upper layer then has to select one of
the devices to which it wants to connect by issuing the command @ref aci_gap_create_connection.
On completion of the procedure a @ref aci_gap_proc_complete_event event is generated with
the procedure code set to 0x20. The procedure is terminated when a connection is established
or the upper layer terminates the procedure by issuing the command
@ref aci_gap_terminate_gap_proc with the procedure code set to 0x20.
  * @param LE_Scan_Type 0x00 Passive Scanning. No SCAN_REQ packets shall be sent.(default)
0x01 Active scanning. SCAN_REQ packets may be sent.
0x02 - 0xFF Reserved for future use
  * @param LE_Scan_Interval This is defined as the time interval from when the Controller started
its last LE scan until it begins the subsequent LE scan.
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10240 msec
  * @param LE_Scan_Window Amount of time for the duration of the LE scan. LE_Scan_Window
shall be less than or equal to LE_Scan_Interval
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10.24 seconds
  * @param Own_Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Filter_Duplicates 0x00 Duplicate filtering disabled.
0x01 Duplicate filtering enabled.
0x02 - 0xFF Reserved for future use.
  * @param Num_of_Whitelist_Entries Number of devices that have to be added to the whitelist.
  * @param Whitelist_Entry See @ref Whitelist_Entry_t
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_start_selective_connection_establish_proc(uint8_t LE_Scan_Type,
                                                             uint16_t LE_Scan_Interval,
                                                             uint16_t LE_Scan_Window,
                                                             uint8_t Own_Address_Type,
                                                             uint8_t Filter_Duplicates,
                                                             uint8_t Num_of_Whitelist_Entries,
                                                             Whitelist_Entry_t Whitelist_Entry[]);
/**
  * @brief Start the direct connection establishment procedure. A LE_Create_Connection call will be
made to the controller by GAP with the initiator filter policy set to "ignore whitelist and
process connectable advertising packets only for the specified device". The procedure can
be terminated explicitly by the upper layer by issuing the command
@ref aci_gap_terminate_gap_proc. When a command is issued to terminate the
procedure by upper layer, a @ref hci_le_create_connection_cancel call will be made to the
controller by GAP.
On termination of the procedure, a @ref hci_le_connection_complete_event event is returned. The  
procedure can be explicitly terminated by the upper layer by issuing the command
@ref aci_gap_terminate_gap_proc with the procedure_code set to 0x40.
  * @param LE_Scan_Interval This is defined as the time interval from when the Controller started
its last LE scan until it begins the subsequent LE scan.
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10240 msec
  * @param LE_Scan_Window Amount of time for the duration of the LE scan. LE_Scan_Window
shall be less than or equal to LE_Scan_Interval
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10.24 seconds
  * @param Peer_Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Peer_Address Public Device Address or Random Device Address of the device
to be connected
  * @param Own_Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Conn_Interval_Min N = 0xXXXX    Minimum value for the connection event interval. This shall be less
than or equal to Conn_Interval_Max.
Range: 0x0006 to 0x0C80
Time = N * 1.25 msec
Time Range: 7.5 msec to 4 seconds.
0x0000 - 0x0005 and 0x0C81 - 0xFFFF Reserved for future use
  * @param Conn_Interval_Max N = 0xXXXX    Maximum value for the connection event interval. This shall be
greater than or equal to Conn_Interval_Min.
Range: 0x0006 to 0x0C80
Time = N * 1.25 msec
Time Range: 7.5 msec to 4 seconds.
0x0000 - 0x0005 and 0x0C81 - 0xFFFF Reserved for future use
  * @param Conn_Latency Slave latency for the connection in number of connection events.
Range: 0x0000 to 0x01F3
  * @param Supervision_Timeout N = 0xXXXX    Supervision timeout for the LE Link. (See [Vol 6] Part B, Section
4.5.2)
Range: 0x000A to 0x0C80
Time = N * 10 msec
Time Range: 100 msec to 32 seconds
0x0000 - 0x0009 and
0x0C81 - 0xFFFF Reserved for future use
  * @param Minimum_CE_Length Information parameter about the minimum length of connection
needed for this LE connection.
Range: 0x0000 - 0xFFFF
Time = N * 0.625 msec.
  * @param Maximum_CE_Length Information parameter about the maximum length of connection needed
for this LE connection.
Range: 0x0000 - 0xFFFF
Time = N * 0.625 msec.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_create_connection(uint16_t LE_Scan_Interval,
                                     uint16_t LE_Scan_Window,
                                     uint8_t Peer_Address_Type,
                                     uint8_t Peer_Address[6],
                                     uint8_t Own_Address_Type,
                                     uint16_t Conn_Interval_Min,
                                     uint16_t Conn_Interval_Max,
                                     uint16_t Conn_Latency,
                                     uint16_t Supervision_Timeout,
                                     uint16_t Minimum_CE_Length,
                                     uint16_t Maximum_CE_Length);
/**
  * @brief Terminate the specified GATT procedure. An @ref aci_gap_proc_complete_event event is
returned with the procedure code set to the corresponding procedure.
  * @param Procedure_Code 0x00 No events specified,
0x01 LIMITED_DISCOVERY_PROC,
0x02 GENERAL_DISCOVERY_PROC,
0x04 NAME_DISCOVERY_PROC,
0x08 AUTO_CONNECTION_ESTABLISHMENT_PROC,
0x10 GENERAL_CONNECTION_ESTABLISHMENT_PROC,
0x20 SELECTIVE_CONNECTION_ESTABLISHMENT_PROC,
0x40 DIRECT_CONNECTION_ESTABLISHMENT_PROC
0x80 OBSERVATION_PROC
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_terminate_gap_proc(uint8_t Procedure_Code);
/**
  * @brief Start the connection update procedure (only when role is Master). A @ref hci_le_connection_update is called.
On completion of the procedure, an @ref hci_le_connection_update_complete_event event is returned to
the upper layer.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Conn_Interval_Min N = 0xXXXX    Minimum value for the connection event interval. This shall be less
than or equal to Conn_Interval_Max.
Range: 0x0006 to 0x0C80
Time = N * 1.25 msec
Time Range: 7.5 msec to 4 seconds.
0x0000 - 0x0005 and 0x0C81 - 0xFFFF Reserved for future use
  * @param Conn_Interval_Max N = 0xXXXX    Maximum value for the connection event interval. This shall be
greater than or equal to Conn_Interval_Min.
Range: 0x0006 to 0x0C80
Time = N * 1.25 msec
Time Range: 7.5 msec to 4 seconds.
0x0000 - 0x0005 and 0x0C81 - 0xFFFF Reserved for future use
  * @param Conn_Latency Slave latency for the connection in number of connection events.
Range: 0x0000 to 0x01F3
  * @param Supervision_Timeout N = 0xXXXX    Supervision timeout for the LE Link. (See [Vol 6] Part B, Section
4.5.2)
Range: 0x000A to 0x0C80
Time = N * 10 msec
Time Range: 100 msec to 32 seconds
0x0000 - 0x0009 and
0x0C81 - 0xFFFF Reserved for future use
  * @param Minimum_CE_Length Information parameter about the minimum length of connection
needed for this LE connection.
Range: 0x0000 - 0xFFFF
Time = N * 0.625 msec.
  * @param Maximum_CE_Length Information parameter about the maximum length of connection needed
for this LE connection.
Range: 0x0000 - 0xFFFF
Time = N * 0.625 msec.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_start_connection_update(uint16_t Connection_Handle,
                                           uint16_t Conn_Interval_Min,
                                           uint16_t Conn_Interval_Max,
                                           uint16_t Conn_Latency,
                                           uint16_t Supervision_Timeout,
                                           uint16_t Minimum_CE_Length,
                                           uint16_t Maximum_CE_Length);
/**
  * @brief Send the SM pairing request to start a pairing process. The authentication requirements and
IO capabilities should be set before issuing this command using the
@ref aci_gap_set_io_capability and @ref aci_gap_set_authentication_requirement commands.
A @ref aci_gap_pairing_complete_event event is returned after the pairing process is completed.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Force_Rebond 0 : Pairing request is sent only if the device has not previously bonded
1 : Pairing request will be sent even if the device was previously bonded
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_send_pairing_req(uint16_t Connection_Handle,
                                    uint8_t Force_Rebond);
/**
  * @brief This command tries to resolve the address provided with the IRKs present in its database. If
the address is resolved successfully with any one of the IRKs present in the database, it
returns success and also the corresponding public/static random address stored with the
IRK in the database.
  * @param Address Address to be resolved
  * @param[out] Actual_Address The public or static random address of the peer device, distributed during pairing phase.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_resolve_private_addr(uint8_t Address[6],
                                        uint8_t Actual_Address[6]);
/**
  * @brief This command gets the list of the devices which are bonded. It returns the
number of addresses and the corresponding address types and values.
  * @param[out] Num_of_Addresses The number of bonded devices
  * @param[out] Bonded_Device_Entry See @ref Bonded_Device_Entry_t
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_get_bonded_devices(uint8_t *Num_of_Addresses,
                                      Bonded_Device_Entry_t Bonded_Device_Entry[]);
/**
  * @brief This command puts the device into broadcast mode. A privacy enabled device uses either a
resolvable private address or a non-resolvable private address as specified in the
Own_Addr_Type parameter of the command.
  * @param Advertising_Interval_Min Minimum advertising interval.
Range: 0x0020 to 0x4000
Time = N * 0.625 msec
Time Range: 20 ms to 10.24 sec
  * @param Advertising_Interval_Max Maximum advertising interval.
Range: 0x0020 to 0x4000
Time = N * 0.625 msec
Time Range: 20 ms to 10.24 sec
  * @param Advertising_Type 0x02 Scannable undirected advertising (ADV_SCAN_IND)
0x03 Non connectable undirected advertising (ADV_NONCONN_IND)
  * @param Own_Address_Type If Privacy is disabled, then the address can be
0x00: Public address
0x01: Static random address
If Privacy is enabled, then the address can be 
0x02 : Resolvable private address
0x03 : Non-resolvable private address
  * @param Adv_Data_Length Length of the advertising data in the advertising packet.
  * @param Adv_Data Advertising data used by the device while advertising.
  * @param Num_of_Whitelist_Entries Number of devices that have to be added to the whitelist.
  * @param Whitelist_Entry See @ref Whitelist_Entry_t
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_set_broadcast_mode(uint16_t Advertising_Interval_Min,
                                      uint16_t Advertising_Interval_Max,
                                      uint8_t Advertising_Type,
                                      uint8_t Own_Address_Type,
                                      uint8_t Adv_Data_Length,
                                      uint8_t Adv_Data[],
                                      uint8_t Num_of_Whitelist_Entries,
                                      Whitelist_Entry_t Whitelist_Entry[]);
/**
  * @brief Starts an Observation procedure, when the device is in Observer Role. The host enables
scanning in the controller. The advertising reports are sent to the upper layer using standard
LE Advertising Report Event. (See Bluetooth Core v4.1, Vol. 2, part E, Ch. 7.7.65.2, LE
Advertising Report Event.)
  * @param LE_Scan_Interval This is defined as the time interval from when the Controller started
its last LE scan until it begins the subsequent LE scan.
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10240 msec
  * @param LE_Scan_Window Amount of time for the duration of the LE scan. LE_Scan_Window
shall be less than or equal to LE_Scan_Interval
Range: 0x0004 to 0x4000
Time = N * 0.625 msec
Time Range: 2.5 msec to 10.24 seconds
  * @param LE_Scan_Type 0x00 Passive Scanning. No SCAN_REQ packets shall be sent.(default)
0x01 Active scanning. SCAN_REQ packets may be sent.
0x02 - 0xFF Reserved for future use
  * @param Own_Address_Type If Privacy is disabled, then the address can be
0x00: Public address
0x01: Static random address
If Privacy is enabled, then the address can be 
0x02 : Resolvable private address
0x03 : Non-resolvable private address
  * @param Filter_Duplicates 0x00 Duplicate filtering disabled.
0x01 Duplicate filtering enabled.
0x02 - 0xFF Reserved for future use.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_start_observation_proc(uint16_t LE_Scan_Interval,
                                          uint16_t LE_Scan_Window,
                                          uint8_t LE_Scan_Type,
                                          uint8_t Own_Address_Type,
                                          uint8_t Filter_Duplicates);
/**
  * @brief The command finds whether the device, whose address is specified in the command, is
bonded. If the device is using a resolvable private address and it has been bonded, then the
command will return BLE_STATUS_SUCCESS.
  * @param Peer_Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Peer_Address Address used by the peer device while advertising
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gap_is_device_bonded(uint8_t Peer_Address_Type,
                                    uint8_t Peer_Address[6]);
/**
     * @}
     */
    #endif /* __BLUENRG1_GAP_ACI_H__*/
