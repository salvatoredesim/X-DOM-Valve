#ifndef __BLUENRG1_HCI_LE_H__
#define __BLUENRG1_HCI_LE_H__


/**
  ******************************************************************************
  * @file    bluenrg1_hci_le.h
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
/**
  * @brief The @ref hci_disconnect is used to terminate an existing connection. The
Connection_Handle command parameter indicates which connection is to be
disconnected. The Reason command parameter indicates the reason for ending
the connection. The remote Controller will receive the Reason command
parameter in the @ref hci_disconnection_complete_event event. All synchronous connections
on a physical link should be disconnected before the ACL connection on the
same physical connection is disconnected.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.1.6)
It is important to leave an 100 ms blank window before sending any new command (including system hardware reset),
since immediately after @ref hci_disconnection_complete_event event, system could save important information in non volatile memory.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Reason Authentication Failure error code (0x05), Other End Terminated Connection error codes (0x13-0x15),
Unsupported Remote Feature error code(0x1A) and Pairing with Unit Key Not Supported error code (0x29)
  * @retval Value indicating success or error code.
*/
tBleStatus hci_disconnect(uint16_t Connection_Handle,
                          uint8_t Reason);
/**
  * @brief This command will obtain the values for the version information for the remote
device identified by the Connection_Handle parameter. The Connection_Handle
must be a Connection_Handle for an ACL or LE connection.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.1.23)
  * @param Connection_Handle Specifies which Connection_Handle's version information to get.
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @retval Value indicating success or error code.
*/
tBleStatus hci_read_remote_version_information(uint16_t Connection_Handle);
/**
  * @brief The Set_Event_Mask command is used to control which events are generated
by the HCI for the Host.

If the bit in the Event_Mask is set to a one, then the
event associated with that bit will be enabled. For an LE Controller, the LE
Meta Event bit in the Event_Mask shall enable or disable all LE events in the
LE Meta Event (see Section 7.7.65). The Host has to deal with each event that
occurs. The event mask allows the Host to control how much it is interrupted.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.3.1)
  * @param Event_Mask 0x0000000000000000 No events specified
0x0000000000000001 Inquiry Complete Event
0x0000000000000002 Inquiry Result Event
0x0000000000000004 Connection Complete Event
0x0000000000000008 Connection Request Event
0x0000000000000010 Disconnection Complete Event
0x0000000000000020 Authentication Complete Event
0x0000000000000040 Remote Name Request Complete Event
0x0000000000000080 Encryption Change Event
0x0000000000000100 Change Connection Link Key Complete Event
0x0000000000000200 Master Link Key Complete Event
0x0000000000000400 Read Remote Supported Features Complete Event
0x0000000000000800 Read Remote Version Information Complete Event
0x0000000000001000 QoS Setup Complete Event
0x0000000000002000 Reserved
0x0000000000004000 Reserved
0x0000000000008000 Hardware Error Event
0x0000000000010000 Flush Occurred Event
0x0000000000020000 Role Change Event
0x0000000000040000 Reserved
0x0000000000080000 Mode Change Event
0x0000000000100000 Return Link Keys Event
0x0000000000200000 PIN Code Request Event
0x0000000000400000 Link Key Request Event
0x0000000000800000 Link Key Notification Event
0x0000000001000000 Loopback Command Event
0x0000000002000000 Data Buffer Overflow Event
0x0000000004000000 Max Slots Change Event
0x0000000008000000 Read Clock Offset Complete Event
0x0000000010000000 Connection Packet Type Changed Event
0x0000000020000000 QoS Violation Event
0x0000000040000000 Page Scan Mode Change Event [deprecated]
0x0000000080000000 Page Scan Repetition Mode Change Event
0x0000000100000000 Flow Specification Complete Event
0x0000000200000000 Inquiry Result with RSSI Event
0x0000000400000000 Read Remote Extended Features Complete Event
0x0000000800000000 Reserved
0x0000001000000000 Reserved
0x0000002000000000 Reserved
0x0000004000000000 Reserved
0x0000008000000000 Reserved
0x0000010000000000 Reserved
0x0000020000000000 Reserved
0x0000040000000000 Reserved
0x0000080000000000 Synchronous Connection Complete Event
0x0000100000000000 Synchronous Connection Changed Event
0x0000200000000000 Sniff Subrating Event
0x0000400000000000 Extended Inquiry Result Event
0x0000800000000000 Encryption Key Refresh Complete Event
0x0001000000000000 IO Capability Request Event
0x0002000000000000 IO Capability Request Reply Event
0x0004000000000000 User Confirmation Request Event
0x0008000000000000 User Passkey Request Event
0x0010000000000000 Remote OOB Data Request Event
0x0020000000000000 Simple Pairing Complete Event
0x0040000000000000 Reserved
0x0080000000000000 Link Supervision Timeout Changed Event
0x0100000000000000 Enhanced Flush Complete Event
0x0200000000000000 Reserved
0x0400000000000000 User Passkey Notification Event
0x0800000000000000 Keypress Notification Event
0x1000000000000000 Remote Host Supported Features Notification Event
0x2000000000000000 LE Meta-Event
0xC000000000000000 Reserved for future use
0x00001FFFFFFFFFFF Default
  * @retval Value indicating success or error code.
*/
tBleStatus hci_set_event_mask(uint8_t Event_Mask[8]);
/**
  * @brief The Reset command will reset the Link Layer on an LE
Controller.

The Reset command shall not affect the used HCI transport layer since the HCI transport
layers may have reset mechanisms of their own. After the reset is completed,
the current operational state will be lost, the Controller will enter standby mode
and the Controller will automatically revert to the default values for the parameters
for which default values are defined in the specification.
Note: The Reset command will not necessarily perform a hardware reset. This
is implementation defined. 
The Host shall not send additional HCI commands before the Command Complete
event related to the Reset command has been received.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.3.2)
  * @retval Value indicating success or error code.
*/
tBleStatus hci_reset(void);
/**
  * @brief This command reads the values for the Transmit_Power_Level parameter for
the specified Connection_Handle. The Connection_Handle shall be a Connection_Handle
for an ACL connection.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.3.35)
  * @param Connection_Handle Specifies which Connection_Handle's Transmit Power Level setting to
read.
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Type 0x00 Read Current Transmit Power Level.
0x01 Read Maximum Transmit Power Level.
0x02-0xFF Reserved
  * @param[out] Transmit_Power_Level Size: 1 Octet (signed integer)
Range: -30 <= N <= 20
Units: dBm
  * @retval Value indicating success or error code.
*/
tBleStatus hci_read_transmit_power_level(uint16_t Connection_Handle,
                                         uint8_t Type,
                                         uint8_t *Transmit_Power_Level);
/**
  * @brief This command reads the values for the version information for the local Controller.
The HCI Version information defines the version information of the HCI layer.
The LMP/PAL Version information defines the version of the LMP or PAL. The
Manufacturer_Name information indicates the manufacturer of the local device.
The HCI Revision and LMP/PAL Subversion are implementation dependent.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.4.1)
  * @param[out] HCI_Version See Bluetooth Assigned Numbers (https://www.bluetooth.org/en-us/specification/assigned-numbers)
  * @param[out] HCI_Revision Revision of the Current HCI in the BR/EDR Controller.
  * @param[out] LMP_PAL_Version Version of the Current LMP or PAL in the Controller.
See Bluetooth Assigned Numbers (https://www.bluetooth.org/en-us/specification/assigned-numbers)
  * @param[out] Manufacturer_Name Manufacturer Name of the BR/EDR Controller.
See Bluetooth Assigned Numbers (https://www.bluetooth.org/en-us/specification/assigned-numbers)
  * @param[out] LMP_PAL_Subversion Subversion of the Current LMP or PAL in the Controller. This value is
implementation dependent.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_read_local_version_information(uint8_t *HCI_Version,
                                              uint16_t *HCI_Revision,
                                              uint8_t *LMP_PAL_Version,
                                              uint16_t *Manufacturer_Name,
                                              uint16_t *LMP_PAL_Subversion);
/**
  * @brief This command reads the list of HCI commands supported for the local Controller.
This command shall return the Supported_Commands configuration parameter.
It is implied that if a command is listed as supported, the feature underlying
that command is also supported.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.4.2)
  * @param[out] Supported_Commands Bit mask for each HCI Command. If a bit is 1, the Controller supports the
corresponding command and the features required for the command.
Unsupported or undefined commands shall be set to 0.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_read_local_supported_commands(uint8_t Supported_Commands[64]);
/**
  * @brief This command requests a list of the supported features for the local 
Controller. This command will return a list of the LMP features. For details see
Part C, Link Manager Protocol Specification on page 227.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.4.3)
  * @param[out] LMP_Features Bit Mask List of LMP features.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_read_local_supported_features(uint8_t LMP_Features[8]);
/**
  * @brief On an LE Controller, this command shall read the Public Device Address as
defined in [Vol 6] Part B, Section 1.3, Device Address. If this Controller does
not have a Public Device Address, the value 0x000000000000 shall be
returned.
On an LE Controller, the public address shall be the same as the
BD_ADDR.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.4.6)
  * @param[out] BD_ADDR BD_ADDR ( Bluetooth Device Address) of the Device.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_read_bd_addr(uint8_t BD_ADDR[6]);
/**
  * @brief This command reads the Received Signal Strength Indication (RSSI) value from
a Controller.
For an LE transport, a Connection_Handle is used as the Handle command
parameter and return parameter. The meaning of the RSSI metric is an absolute
receiver signal strength value in dBm to +/- 6 dB accuracy. If the RSSI cannot
be read, the RSSI metric shall be set to 127.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.5.4)
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param[out] RSSI BR/EDR
Range: -128 =< N <= 127 (signed integer)
Units: dB
AMP:
Range: AMP type specific (signed integer)
Units: dBm
LE:
Range: -127 to 20, 127 (signed integer)
Units: dBm
  * @retval Value indicating success or error code.
*/
tBleStatus hci_read_rssi(uint16_t Connection_Handle,
                         uint8_t *RSSI);
/**
  * @brief The LE_Set_Event_Mask command is used to control which LE events are
generated by the HCI for the Host. If the bit in the LE_Event_Mask is set to a
one, then the event associated with that bit will be enabled. The Host has to
deal with each event that is generated by an LE Controller. The event mask
allows the Host to control which events will interrupt it.
For LE events to be generated, the LE Meta-Event bit in the Event_Mask shall
also be set. If that bit is not set, then LE events shall not be generated, regardless
of how the LE_Event_Mask is set.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.1)
  * @param LE_Event_Mask 0x0000000000000000 No LE events specified
0x0000000000000001 LE Connection Complete Event
0x0000000000000002 LE Advertising Report Event
0x0000000000000004 LE Connection Update Complete Event
0x0000000000000008 LE Read Remote Used Features Complete Event
0x0000000000000010 LE Long Term Key Request Event
0x000000000000001F Default
0xFFFFFFFFFFFFFE0 Reserved for future use
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_set_event_mask(uint8_t LE_Event_Mask[8]);
/**
  * @brief The LE_Read_Buffer_Size command is used to read the maximum size of the
data portion of HCI LE ACL Data Packets sent from the Host to the Controller.
The Host will segment the data transmitted to the Controller according to these
values, so that the HCI Data Packets will contain data with up to this size. The
LE_Read_Buffer_Size command also returns the total number of HCI LE ACL
Data Packets that can be stored in the data buffers of the Controller. The
LE_Read_Buffer_Size command must be issued by the Host before it sends
any data to an LE Controller (see Section 4.1.1).
If the Controller returns a length value of zero, the Host shall use the
Read_Buffer_Size command to determine the size of the data buffers
Note: Both the Read_Buffer_Size and LE_Read_Buffer_Size commands may
return buffer length and number of packets parameter values that are nonzero.
The HC_LE_ACL_Data_Packet_Length return parameter shall be used to
determine the size of the L2CAP PDU segments contained in ACL Data
Packets, which are transferred from the Host to the Controller to be broken up
into packets by the Link Layer. Both the Host and the Controller shall support
command and event packets, where the data portion (excluding header)
contained in the packets is 255 octets in size. The
HC_Total_Num_LE_ACL_Data_Packets return parameter contains the total
number of HCI ACL Data Packets that can be stored in the data buffers of the
Controller. The Host determines how the buffers are to be divided between
different Connection Handles.
Note: The HC_LE_ACL_Data_Packet_Length return parameter does not
include the length of the HCI Data Packet header.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.2)
  * @param[out] HC_LE_ACL_Data_Packet_Length 0x0000 No dedicated LE Buffer - use Read_Buffer_Size command.
0x0001 - 0xFFFF Maximum length (in octets) of the data portion of each HCI ACL Data
Packet that the Controller is able to accept.
  * @param[out] HC_Total_Num_LE_ACL_Data_Packets 0x00 No dedicated LE Buffer - use Read_Buffer_Size command.
0x01 - 0xFF Total number of HCI ACL Data Packets that can be stored in the data
buffers of the Controller.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_read_buffer_size(uint16_t *HC_LE_ACL_Data_Packet_Length,
                                   uint8_t *HC_Total_Num_LE_ACL_Data_Packets);
/**
  * @brief This command requests the list of the supported LE features for the Controller.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.3)
  * @param[out] LE_Features Bit Mask List of LE features.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_read_local_supported_features(uint8_t LE_Features[8]);
/**
  * @brief The LE_Set_Random_Address command is used by the Host to set the LE
Random Device Address in the Controller (see [Vol 6] Part B, Section 1.3).
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.4)
  * @param Random_Address Random Device Address
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_set_random_address(uint8_t Random_Address[6]);
/**
  * @brief The LE_Set_Advertising_Parameters command is used by the Host to set the
advertising parameters.
The Advertising_Interval_Min shall be less than or equal to the Advertising_Interval_Max.
The Advertising_Interval_Min and Advertising_Interval_Max
should not be the same value to enable the Controller to determine the best
advertising interval given other activities.
For high duty cycle directed advertising, i.e. when Advertising_Type is 0x01
(ADV_DIRECT_IND, high duty cycle), the Advertising_Interval_Min and Advertising_Interval_Max
parameters are not used and shall be ignored.
The Advertising_Type is used to determine the packet type that is used for
advertising when advertising is enabled.
The Advertising_Interval_Min and Advertising_Interval_Max shall not be set to
less than 0x00A0 (100 ms) if the Advertising_Type is set to 0x02 (ADV_SCAN_IND)
or 0x03 (ADV_NONCONN_IND). The Own_Address_Type determines
if the advertising packets are identified with the Public Device Address of
the device, or a Random Device Address as written by the LE_Set_Random_Address
command.
If directed advertising is performed, i.e. when Advertising_Type is set to 0x01
(ADV_DIRECT_IND, high duty cycle) or 0x04 (ADV_DIRECT_IND, low duty
cycle mode), then the Direct_Address_Type and Direct_Address shall be valid,
otherwise they shall be ignored by the Controller and not used.
The Advertising_Channel_Map is a bit field that indicates the advertising channels
that shall be used when transmitting advertising packets. At least one
channel bit shall be set in the Advertising_Channel_Map parameter.
The Advertising_Filter_Policy parameter shall be ignored when directed advertising
is enabled.
The Host shall not issue this command when advertising is enabled in the Controller;
if it is the Command Disallowed error code shall be used.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.5)
  * @param Advertising_Interval_Min Minimum advertising interval.
Range: 0x0020 to 0x4000
Time = N * 0.625 msec
Time Range: 20 ms to 10.24 sec
  * @param Advertising_Interval_Max Maximum advertising interval.
Range: 0x0020 to 0x4000
Time = N * 0.625 msec
Time Range: 20 ms to 10.24 sec
  * @param Advertising_Type 0x00 Connectable undirected advertising (ADV_IND) (default)
0x01 Connectable directed advertising (ADV_DIRECT_IND)
0x02 Scannable undirected advertising (ADV_SCAN_IND)
0x03 Non connectable undirected advertising (ADV_NONCONN_IND)
0x04 - 0xFF Reserved for future use
  * @param Own_Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Direct_Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Direct_Address Public Device Address or Random Device Address of the device
to be connected
  * @param Advertising_Channel_Map 00000000b Reserved for future use
xxxxxxx1b Enable channel 37 use
xxxxxx1xb Enable channel 38 use
xxxxx1xxb Enable channel 39 use
00000111b Default (all channels enabled)
  * @param Advertising_Filter_Policy 0x00 Allow Scan Request from Any, Allow Connect Request from Any (default).
0x01 Allow Scan Request from White List Only, Allow Connect Request from Any.
0x02 Allow Scan Request from Any, Allow Connect Request from White List Only.
0x03 Allow Scan Request from White List Only, Allow Connect Request from White List Only.
0x04 - 0xFF Reserved for future use.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_set_advertising_parameters(uint16_t Advertising_Interval_Min,
                                             uint16_t Advertising_Interval_Max,
                                             uint8_t Advertising_Type,
                                             uint8_t Own_Address_Type,
                                             uint8_t Direct_Address_Type,
                                             uint8_t Direct_Address[6],
                                             uint8_t Advertising_Channel_Map,
                                             uint8_t Advertising_Filter_Policy);
/**
  * @brief The LE_Read_Advertising_Channel_Tx_Power command is used by the Host
to read the transmit power level used for LE advertising channel packets.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.6)
  * @param[out] Transmit_Power_Level Size: 1 Octet (signed integer)
Range: -20 <= N <= 10
Units: dBm
Accuracy: +/- 4 dBm
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_read_advertising_channel_tx_power(uint8_t *Transmit_Power_Level);
/**
  * @brief The LE_Set_Advertising_Data command is used to set the data used in advertising
packets that have a data field.
Only the significant part of the Advertising_Data is transmitted in the advertising
packets, as defined in [Vol 3] Part C, Section 11.,
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.7)
  * @param Advertising_Data_Length The number of significant octets in the following data field
  * @param Advertising_Data 31 octets of data formatted as defined in [Vol 3] Part
C, Section 11.
All octets zero (default).
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_set_advertising_data(uint8_t Advertising_Data_Length,
                                       uint8_t Advertising_Data[31]);
/**
  * @brief This command is used to provide data used in Scanning Packets that have a
data field.
Only the significant part of the Scan_Response_Data is transmitted in the
Scanning Packets, as defined in [Vol 3] Part C, Section 11.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.8)
  * @param Scan_Response_Data_Length The number of significant octets in the following data field
  * @param Scan_Response_Data 31 octets of data formatted as defined in [Vol 3] Part
C, Section 11.
All octets zero (default).
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_set_scan_response_data(uint8_t Scan_Response_Data_Length,
                                         uint8_t Scan_Response_Data[31]);
/**
  * @brief The LE_Set_Advertise_Enable command is used to request the Controller to
start or stop advertising. The Controller manages the timing of advertisements
as per the advertising parameters given in the LE_Set_Advertising_Parameters
command.
The Controller shall continue advertising until the Host issues an LE_Set_Advertise_Enable
command with Advertising_Enable set to 0x00 (Advertising is
disabled) or until a connection is created or until the Advertising is timed out
due to high duty cycle Directed Advertising. In these cases, advertising is then
disabled.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.9)
  * @param Advertising_Enable 0x00 Advertising is disabled (default)
0x01 Advertising is enabled.
0x02 - 0xFF Reserved for future use
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_set_advertise_enable(uint8_t Advertising_Enable);
/**
  * @brief The LE_Set_Scan_Parameters command is used to set the scan parameters.
The LE_Scan_Type parameter controls the type of scan to perform.
The LE_Scan_Interval and LE_Scan_Window parameters are recommendations
from the Host on how long (LE_Scan_Window) and how frequently
(LE_Scan_Interval) the Controller should scan (See [Vol 6] Part B, Section
4.5.3). The LE_Scan_Window parameter shall always be set to a value smaller
or equal to the value set for the LE_Scan_Interval parameter. If they are set to
the same value scanning should be run continuously.
The Own_Address_Type parameter determines the address used (Public or
Random Device Address) when performing active scan.
The Host shall not issue this command when scanning is enabled in the Controller;
if it is the Command Disallowed error code shall be used.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.10)
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
  * @param Scanning_Filter_Policy 0x00 Accept all advertisement packets (default).
Directed advertising packets which are not addressed for this device
shall be ignored.
0x01 Ignore advertisement packets from devices not in the White List Only.
Directed advertising packets which are not addressed for this device
shall be ignored.
0x02 - 0xFF Reserved for future use.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_set_scan_parameters(uint8_t LE_Scan_Type,
                                      uint16_t LE_Scan_Interval,
                                      uint16_t LE_Scan_Window,
                                      uint8_t Own_Address_Type,
                                      uint8_t Scanning_Filter_Policy);
/**
  * @brief The LE_Set_Scan_Enable command is used to start scanning. Scanning is
used to discover advertising devices nearby.
The Filter_Duplicates parameter controls whether the Link Layer shall filter
duplicate advertising reports to the Host, or if the Link Layer should generate
advertising reports for each packet received.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.11)
  * @param LE_Scan_Enable 00x00 Scanning disabled.
0x01 Scanning enabled.
0x02 - 0xFF Reserved for future use.
  * @param Filter_Duplicates 0x00 Duplicate filtering disabled.
0x01 Duplicate filtering enabled.
0x02 - 0xFF Reserved for future use.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_set_scan_enable(uint8_t LE_Scan_Enable,
                                  uint8_t Filter_Duplicates);
/**
  * @brief TBD
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
  * @param Initiator_Filter_Policy 0x00 White list is not used to determine which advertiser to connect to.
Peer_Address_Type and Peer_Address shall be used.
0x01 White list is used to determine which advertiser to connect to.
Peer_Address_Type and Peer_Address shall be ignored.
0x02 - 0xFF Reserved for future use.
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
tBleStatus hci_le_create_connection(uint16_t LE_Scan_Interval,
                                    uint16_t LE_Scan_Window,
                                    uint8_t Initiator_Filter_Policy,
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
  * @brief The LE_Create_Connection_Cancel command is used to cancel the LE_Create_Connection
command. This command shall only be issued after the
LE_Create_Connection command has been issued, a Command Status event
has been received for the LE Create Connection command and before the LE
Connection Complete event.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.13)
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_create_connection_cancel(void);
/**
  * @brief The LE_Read_White_List_Size command is used to read the total number of
white list entries that can be stored in the Controller.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.14)
  * @param[out] White_List_Size 0x01 - 0xFF Total number of white list entries that can be stored in the Controller.
0x00 Reserved for future use
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_read_white_list_size(uint8_t *White_List_Size);
/**
  * @brief The LE_Clear_White_List command is used to clear the white list stored in the
Controller.
This command can be used at any time except when:
- the advertising filter policy uses the white list and advertising is enabled.
- the scanning filter policy uses the white list and scanning is enabled.
- the initiator filter policy uses the white list and an LE_Create_Connection
command is outstanding.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.15)
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_clear_white_list(void);
/**
  * @brief The LE_Add_Device_To_White_List command is used to add a single device
to the white list stored in the Controller.
This command can be used at any time except when:
- the advertising filter policy uses the white list and advertising is enabled.
- the scanning filter policy uses the white list and scanning is enabled.
- the initiator filter policy uses the white list and a create connection command
is outstanding.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.16)
  * @param Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Address Public Device Address or Random Device Address of the device
to be added to the white list.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_add_device_to_white_list(uint8_t Address_Type,
                                           uint8_t Address[6]);
/**
  * @brief The LE_Remove_Device_From_White_List command is used to remove a single
device from the white list stored in the Controller.
This command can be used at any time except when:
- the advertising filter policy uses the white list and advertising is enabled.
- the scanning filter policy uses the white list and scanning is enabled.
- the initiator filter policy uses the white list and a create connection command
is outstanding.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.17)
  * @param Address_Type 0x00 Public Device Address
0x01 Random Device Address
0x02 - 0xFF Reserved for future use
  * @param Address Public Device Address or Random Device Address of the device
to be removed from the white list.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_remove_device_from_white_list(uint8_t Address_Type,
                                                uint8_t Address[6]);
/**
  * @brief The LE_Connection_Update command is used to change the Link Layer connection
parameters of a connection. This command is supported only on master side.
The Conn_Interval_Min and Conn_Interval_Max parameters are used to define
the minimum and maximum allowed connection interval. The Conn_Interval_Min
parameter shall not be greater than the Conn_Interval_Max parameter.
The Conn_Latency parameter shall define the maximum allowed connection
latency.
The Supervision_Timeout parameter shall define the link supervision timeout
for the LE link. The Supervision_Timeout in milliseconds shall be larger than (1
+ Conn_Latency) * Conn_Interval_Max * 2, where Conn_Interval_Max is given
in milliseconds.
The Minimum_CE_Length and Maximum_CE_Length are information parameters
providing the Controller with a hint about the expected minimum and maximum
length of the connection events. The Minimum_CE_Length shall be less
than or equal to the Maximum_CE_Length.
The actual parameter values selected by the Link Layer may be different from
the parameter values provided by the Host through this command.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.18)
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
tBleStatus hci_le_connection_update(uint16_t Connection_Handle,
                                    uint16_t Conn_Interval_Min,
                                    uint16_t Conn_Interval_Max,
                                    uint16_t Conn_Latency,
                                    uint16_t Supervision_Timeout,
                                    uint16_t Minimum_CE_Length,
                                    uint16_t Maximum_CE_Length);
/**
  * @brief The LE_Set_Host_Channel_Classification command allows the Host to specify
a channel classification for data channels based on its "local information". This
classification persists until overwritten with a subsequent LE_Set_Host_Channel_Classification
command or until the Controller is reset using the Reset
command (see [Vol 6] Part B, Section 4.5.8.1).
If this command is used, the Host should send it within 10 seconds of knowing
that the channel classification has changed. The interval between two successive
commands sent shall be at least one second.
This command shall only be used when the local device supports the Master
role.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.19)
  * @param LE_Channel_Map This parameter contains 37 1-bit fields.
The nth such field (in the range 0 to 36) contains the value for the
link layer channel index n.
Channel n is bad = 0.
Channel n is unknown = 1.
The most significant bits are reserved and shall be set to 0.
At least one channel shall be marked as unknown.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_set_host_channel_classification(uint8_t LE_Channel_Map[5]);
/**
  * @brief The LE_Read_Channel_Map command returns the current Channel_Map for
the specified Connection_Handle. The returned value indicates the state of the
Channel_Map specified by the last transmitted or received Channel_Map (in a
CONNECT_REQ or LL_CHANNEL_MAP_REQ message) for the specified
Connection_Handle, regardless of whether the Master has received an
acknowledgement.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.20)
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param[out] LE_Channel_Map This parameter contains 37 1-bit fields.
The nth such field (in the range 0 to 36) contains the value for the
link layer channel index n.
Channel n is unused = 0.
Channel n is used = 1.
The most significant bits are reserved and shall be set to 0.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_read_channel_map(uint16_t Connection_Handle,
                                   uint8_t LE_Channel_Map[5]);
/**
  * @brief This command requests a list of the used LE features from the remote device.
This command shall return a list of the used LE features. For details see [Vol 6]
Part B, Section 4.6.
This command may be issued on both the master and slave.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.21)
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_read_remote_used_features(uint16_t Connection_Handle);
/**
  * @brief The LE_Encrypt command is used to request the Controller to encrypt the
Plaintext_Data in the command using the Key given in the command and
returns the Encrypted_Data to the Host. The AES-128 bit block cypher is
defined in NIST Publication FIPS-197 (http://csrc.nist.gov/publications/fips/
fips197/fips-197.pdf).
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.22)
  * @param Key 128 bit key for the encryption of the data given in the command.
  * @param Plaintext_Data 128 bit data block that is requested to be encrypted.
  * @param[out] Encrypted_Data 128 bit encrypted data block.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_encrypt(uint8_t Key[16],
                          uint8_t Plaintext_Data[16],
                          uint8_t Encrypted_Data[16]);
/**
  * @brief The LE_Rand command is used to request the Controller to generate 8 octets
of random data to be sent to the Host. The Random_Number shall be generated
according to [Vol 2] Part H, Section 2 if the LE Feature (LL Encryption) is
supported.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.23)
  * @param[out] Random_Number Random Number
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_rand(uint8_t Random_Number[8]);
/**
  * @brief The LE_Start_Encryption command is used to authenticate the given encryption
key associated with the remote device specified by the connection handle,
and once authenticated will encrypt the connection. The parameters are as
defined in [Vol 3] Part H, Section 2.4.4.
If the connection is already encrypted then the Controller shall pause connection
encryption before attempting to authenticate the given encryption key, and
then re-encrypt the connection. While encryption is paused no user data shall
be transmitted.
On an authentication failure, the connection shall be automatically disconnected
by the Link Layer. If this command succeeds, then the connection shall
be encrypted.
This command shall only be used when the local device's role is Master.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.24)
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Random_Number 64 bit random number.
  * @param Encrypted_Diversifier 16 bit encrypted diversifier.
  * @param Long_Term_Key 128 bit long term key.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_start_encryption(uint16_t Connection_Handle,
                                   uint8_t Random_Number[8],
                                   uint16_t Encrypted_Diversifier,
                                   uint8_t Long_Term_Key[16]);
/**
  * @brief The LE_Long_Term_Key_Request_Reply command is used to reply to an LE
Long Term Key Request event from the Controller, and specifies the
Long_Term_Key parameter that shall be used for this Connection_Handle. The
Long_Term_Key is used as defined in [Vol 6] Part B, Section 5.1.3.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.25)
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Long_Term_Key 128 bit long term key.
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_long_term_key_request_reply(uint16_t Connection_Handle,
                                              uint8_t Long_Term_Key[16]);
/**
  * @brief The LE_Long_Term_Key_Request_Negative_Reply command is used to reply
to an LE Long Term Key Request event from the Controller if the Host cannot
provide a Long Term Key for this Connection_Handle.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.26)
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_long_term_key_requested_negative_reply(uint16_t Connection_Handle);
/**
  * @brief The LE_Read_Supported_States command reads the states and state combinations
that the link layer supports. See [Vol 6] Part B, Section 1.1.1.
LE_States is an 8-octet bit field. If a bit is set to 1 then this state or state combination
is supported by the Controller. Multiple bits in LE_States may be set to 1
to indicate support for multiple state and state combinations.
All the Advertising type with the Initiate State combinations shall be set only if
the corresponding Advertising types and Master Role combination are set.
All the Scanning types and the Initiate State combinations shall be set only if
the corresponding Scanning types and Master Role combination are set.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.27)
  * @param[out] LE_States 0x0000000000000000
Reserved for future use
(No state combinations supported).
0x0000000000000001 Non-connectable Advertising State supported.
0x0000000000000002 Scannable Advertising State supported.
0x0000000000000004 Connectable Advertising State supported.
0x0000000000000008 Directed Advertising State supported.
0x0000000000000010 Passive Scanning State supported.
0x0000000000000020 Active Scanning State supported.
0x0000000000000040
Initiating State supported.
Connection State in the Master Role supported is also supported.
0x0000000000000080 Connection State in the Slave Role supported.
0x0000000000000100
Non-connectable Advertising State and Passive Scanning State combination
supported.
0x0000000000000200
Scannable Advertising State and Passive Scanning State combination supported.
0x0000000000000400
Connectable Advertising State and Passive Scanning State combination
supported.
0x0000000000000800
Directed Advertising State and Passive Scanning State combination supported.
0x0000000000001000
Non-connectable Advertising State and Active Scanning State combination
supported.
0x0000000000002000
Scannable Advertising State and Active Scanning State combination supported.
0x0000000000004000
Connectable Advertising State and Active Scanning State combination supported.
0x0000000000008000
Directed Advertising State and Active Scanning State combination supported.
0x0000000000010000
Non-connectable Advertising State and Initiating State combination supported.
0x0000000000020000 Scannable Advertising State and Initiating State combination supported
0x0000000000040000 Non-connectable Advertising State and Master Role combination supported.
0x0000000000080000 Scannable Advertising State and Master Role combination supported.
0x0000000000100000 Non-connectable Advertising State and Slave Role combination supported.
0x0000000000200000 Scannable Advertising State and Slave Role combination supported.
0x0000000000400000 Passive Scanning State and Initiating State combination supported.
When the LE_Read_Supported_States command has completed, a Command
Complete event will be generated.
0x0000000000800000 Active Scanning State and Initiating State combination supported.
0x0000000001000000 Passive Scanning State and Master Role combination supported.
0x0000000002000000 Active Scanning State and Master Role combination supported.
0x0000000004000000 Passive Scanning state and Slave Role combination supported.
0x0000000008000000 Active Scanning state and Slave Role combination supported.
0x0000000010000000
Initiating State and Master Role combination supported.
Master Role and Master Role combination is also supported.
0xFFFFFFFFE0000000 Reserved for future use
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_read_supported_states(uint8_t LE_States[8]);
/**
  * @brief This command is used to start a test where the DUT receives test reference
packets at a fixed interval. The tester generates the test reference packets.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.28)
  * @param RX_Frequency N = (F - 2402) / 2
Range: 0x00 - 0x27. Frequency Range : 2402 MHz to 2480 MHz
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_receiver_test(uint8_t RX_Frequency);
/**
  * @brief This command is used to start a test where the DUT generates test reference
packets at a fixed interval. The Controller shall transmit at maximum power.
An LE Controller supporting the LE_Transmitter_Test command shall support
Packet_Payload values 0x00, 0x01 and 0x02. An LE Controller may support
other values of Packet_Payload.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.29)
  * @param TX_Frequency N = (F - 2402) / 2
Range: 0x00 - 0x27. Frequency Range : 2402 MHz to 2480 MHz
  * @param Length_Of_Test_Data 0x00-0x25 Length in bytes of payload data in each packet
0x26-0xFF Reserved for future use
  * @param Packet_Payload 0x00 Pseudo-Random bit sequence 9
0x01 Pattern of alternating bits '11110000'
0x02 Pattern of alternating bits '10101010'
0x03 Pseudo-Random bit sequence 15
0x04 Pattern of All '1' bits
0x05 Pattern of All '0' bits
0x06 Pattern of alternating bits '00001111'
0x07 Pattern of alternating bits '0101'
0x08-0xFF Reserved for future use
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_transmitter_test(uint8_t TX_Frequency,
                                   uint8_t Length_Of_Test_Data,
                                   uint8_t Packet_Payload);
/**
  * @brief This command is used to stop any test which is in progress. The Number_Of_Packets
for a transmitter test shall be reported as 0x0000. The Number_Of_Packets
is an unsigned number and contains the number of received
packets.
(See Bluetooth Specification v.4.1, Vol. 2, Part E, 7.8.30)
  * @param[out] Number_Of_Packets Number of packets received
  * @retval Value indicating success or error code.
*/
tBleStatus hci_le_test_end(uint16_t *Number_Of_Packets);
/**
     * @}
     */
    #endif /* __BLUENRG1_HCI_LE_H__*/
