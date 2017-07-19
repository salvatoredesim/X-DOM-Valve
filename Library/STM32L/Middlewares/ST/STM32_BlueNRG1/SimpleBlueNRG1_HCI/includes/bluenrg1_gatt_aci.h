#ifndef __BLUENRG1_GATT_ACI_H__
#define __BLUENRG1_GATT_ACI_H__


/**
  ******************************************************************************
  * @file    bluenrg1_gatt_aci.h
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
/** Documentation for Service_UUID_t */
typedef union Service_UUID_t_s {
  uint16_t Service_UUID_16 /** 16-bit UUID */;
  uint8_t Service_UUID_128[16] /** 128-bit UUID */;
} Service_UUID_t;
/** Documentation for Include_UUID_t */
typedef union Include_UUID_t_s {
  uint16_t Include_UUID_16 /** 16-bit UUID */;
  uint8_t Include_UUID_128[16] /** 128-bit UUID */;
} Include_UUID_t;
/** Documentation for Char_UUID_t */
typedef union Char_UUID_t_s {
  uint16_t Char_UUID_16 /** 16-bit UUID */;
  uint8_t Char_UUID_128[16] /** 128-bit UUID */;
} Char_UUID_t;
/** Documentation for Char_Desc_Uuid_t */
typedef union Char_Desc_Uuid_t_s {
  uint16_t Char_UUID_16 /** 16-bit UUID */;
  uint8_t Char_UUID_128[16] /** 128-bit UUID */;
} Char_Desc_Uuid_t;
/** Documentation for UUID_t */
typedef union UUID_t_s {
  uint16_t UUID_16 /** 16-bit UUID */;
  uint8_t UUID_128[16] /** 128-bit UUID */;
} UUID_t;
/** Documentation for Handle_Entry_t */
typedef struct Handle_Entry_t_s {
  uint16_t Handle /** The handles for which the attribute value has to be read */;
} Handle_Entry_t;
/**
  * @brief Initialize the GATT layer for server and client roles. 
It adds also the GATT service with Service Changed Characteristic. 
Until this command is issued the GATT channel will not process any commands even if the 
connection is opened. This command has to be given before using any of the GAP features. 
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_init(void);
/**
  * @brief Add a service to GATT Server. When a service is created in the server, the host needs to
reserve the handle ranges for this service using Max_Attribute_Records parameter. This
parameter specifies the maximum number of attribute records that can be added to this
service (including the service attribute, include attribute, characteristic attribute,
characteristic value attribute and characteristic descriptor attribute). Handle of the created
service is returned in command complete event. Service declaration is taken from the service pool. 
The attributes for characteristics and descriptors are allocated from the attribute pool.
  * @param Service_UUID_Type 0x01 = 16-bit UUID,
0x02 = 128-bit UUID
  * @param Service_UUID See @ref Service_UUID_t
  * @param Service_Type 0x01 = Primary Service,
0x02 = Secondary Service
  * @param Max_Attribute_Records Maximum number of attribute records that can be added to this service
  * @param[out] Service_Handle Handle of the Service.
When this service is added to the server, a handle is allocated by the server to this service. 
Server also allocates a range of handles for this service from serviceHandle to <serviceHandle + max_attr_records>
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_add_service(uint8_t Service_UUID_Type,
                                Service_UUID_t *Service_UUID,
                                uint8_t Service_Type,
                                uint8_t Max_Attribute_Records,
                                uint16_t *Service_Handle);
/**
  * @brief Include a service given by Include_Start_Handle and Include_End_Handle to another 
service given by Service_Handle. Attribute server creates an INCLUDE definition 
attribute and return the handle of this attribute in Included_handle.
  * @param Service_Handle Handle of the Service to which another service has to be included.
  * @param Include_Start_Handle Start Handle of the Service which has to be included in service
  * @param Include_End_Handle End Handle of the Service which has to be included in service
  * @param Include_UUID_Type 0x01 = 16-bit UUID,
0x02 = 128-bit UUID
  * @param Include_UUID See @ref Include_UUID_t
  * @param[out] Include_Handle Handle of the include declaration
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_include_service(uint16_t Service_Handle,
                                    uint16_t Include_Start_Handle,
                                    uint16_t Include_End_Handle,
                                    uint8_t Include_UUID_Type,
                                    Include_UUID_t *Include_UUID,
                                    uint16_t *Include_Handle);
/**
  * @brief Add a characteristic to a service.
  * @param Service_Handle Handle of the Service to which the characteristic will be added
  * @param Char_UUID_Type 0x01 = 16-bit UUID,
0x02 = 128-bit UUID
  * @param Char_UUID See @ref Char_UUID_t
  * @param Char_Value_Length Maximum length of the characteristic value.
  * @param Char_Properties Characteristic Properties like defined in Volume 3, section 3.3.1.1 of Bluetooth Specification 4.0.
0x01: Broadcast,
0x02: Read,
0x04: Write w/o Resp.,
0x08: Write,
0x10: Notify,
0x20: Indicate,
0x40: Authenticated Signed Writes,
0x80: Extended Proproperties
  * @param Security_Permissions 0x00: None,
0x01: AUTHEN_READ (Need authentication to read),
0x02: AUTHOR_READ (Need authorization to read),
0x04: ENCRY_READ (link should be encrypted to read),
0x08: AUTHEN_WRITE (need authentication to write),
0x10: AUTHOR_WRITE (need authorization to write),
0x20: ENCRY_WRITE (link should be encrypted to write)
  * @param GATT_Evt_Mask 0x00 = GATT_DONT_NOTIFY_EVENTS,
0x01 = GATT_NOTIFY_ATTRIBUTE_WRITE,
0x02 = GATT_NOTIFY_WRITE_REQ_AND_WAIT_FOR_APPL_RESP,
0x04 = GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP
  * @param Enc_Key_Size Minimum encryption key size required to read the characteristic
range : 0x07 to 0x10
  * @param Is_Variable 0x00: The attribute has a fixed length value field
0x01: The attribute has a variable length value field
  * @param[out] Char_Handle Handle of the Characteristic that has been added. 
It is the handle of the characteristic declaration. 
The attribute that holds the characteristic value is allocated at the next handle, 
followed by the Client Characteristic Configuration descriptor if the characteristic 
has CHAR_PROP_NOTIFY or CHAR_PROP_INDICATE properties.
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_add_char(uint16_t Service_Handle,
                             uint8_t Char_UUID_Type,
                             Char_UUID_t *Char_UUID,
                             uint16_t Char_Value_Length,
                             uint8_t Char_Properties,
                             uint8_t Security_Permissions,
                             uint8_t GATT_Evt_Mask,
                             uint8_t Enc_Key_Size,
                             uint8_t Is_Variable,
                             uint16_t *Char_Handle);
/**
  * @brief Add a characteristic descriptor to a service.
  * @param Service_Handle Handle of service to which the characteristic belongs
  * @param Char_Handle Handle of the characteristic to which description has to be added
  * @param Char_Desc_Uuid_Type 0x01 = 16-bit UUID,
0x02 = 128-bit UUID
  * @param Char_Desc_Uuid See @ref Char_Desc_Uuid_t
  * @param Char_Desc_Value_Max_Len The maximum length of the descriptor value
  * @param Char_Desc_Value_Length Current Length of the characteristic descriptor value
  * @param Char_Desc_Value Value of the characteristic description
  * @param Security_Permissions 0x00: None,
0x01: AUTHEN_READ (Need authentication to read),
0x02: AUTHOR_READ (Need authorization to read),
0x04: ENCRY_READ (link should be encrypted to read),
0x08: AUTHEN_WRITE (need authentication to write),
0x10: AUTHOR_WRITE (need authorization to write),
0x20: ENCRY_WRITE (link should be encrypted to write)
  * @param Access_Permissions 0x00: None,
0x01: READ,
0x02: WRITE,
0x04: WRITE_WO_RESP,
0x08: SIGNED_WRITE
  * @param GATT_Evt_Mask 0x00 = GATT_DONT_NOTIFY_EVENTS,
0x01 = GATT_NOTIFY_ATTRIBUTE_WRITE,
0x02 = GATT_NOTIFY_WRITE_REQ_AND_WAIT_FOR_APPL_RESP,
0x04 = GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP
  * @param Enc_Key_Size Minimum encryption key size required to read the characteristic
range : 0x07 to 0x10
  * @param Is_Variable 0x00: The attribute has a fixed length value field
0x01: The attribute has a variable length value field
  * @param[out] Char_Desc_Handle Handle of the characteristic descriptor
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_add_char_desc(uint16_t Service_Handle,
                                  uint16_t Char_Handle,
                                  uint8_t Char_Desc_Uuid_Type,
                                  Char_Desc_Uuid_t *Char_Desc_Uuid,
                                  uint8_t Char_Desc_Value_Max_Len,
                                  uint8_t Char_Desc_Value_Length,
                                  uint8_t Char_Desc_Value[],
                                  uint8_t Security_Permissions,
                                  uint8_t Access_Permissions,
                                  uint8_t GATT_Evt_Mask,
                                  uint8_t Enc_Key_Size,
                                  uint8_t Is_Variable,
                                  uint16_t *Char_Desc_Handle);
/**
  * @brief Update a characteristic value in a service. 
If notifications (or indications) are enabled on that characteristic, 
a notification (or indication) will be sent to the client after sending 
this command to the BlueNRG. The command is queued into the BlueNRG command queue. 
If the buffer is full, because previous commands could not be still processed,
the function will return BLE_STATUS_INSUFFICIENT_RESOURCES. This will happen 
if notifications (or indications) are enabled and the application calls 
@ref aci_gatt_update_char_value at an higher rate than what is allowed by the link. 
Throughput on BLE link depends on connection interval and connection length 
parameters (decided by the master, see aci_l2cap_connection_parameter_update_request() 
for more info on how to suggest new connection parameters from a slave). If the 
application does not want to lose notifications because BlueNRG buffer becomes full, 
it has to retry again till the function returns BLE_STATUS_SUCCESS or any other error code.
  * @param Service_Handle Handle of service to which the characteristic belongs
  * @param Char_Handle Handle of the characteristic
  * @param Val_Offset The offset from which the attribute value has to be updated. 
If this is set to 0 and the attribute value is of variable length, then the length of the attribute will be set to the Char_Value_Length. 
If the Val_Offset is set to a value greater than 0, then the length of the attribute will be set to the maximum length as 
specified for the attribute while adding the characteristic.
  * @param Char_Value_Length Length of the characteristic value in octets
  * @param Char_Value Characteristic value
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_update_char_value(uint16_t Service_Handle,
                                      uint16_t Char_Handle,
                                      uint8_t Val_Offset,
                                      uint8_t Char_Value_Length,
                                      uint8_t Char_Value[]);
/**
  * @brief Delete the specified characteristic from the service.
  * @param Serv_Handle Handle of service to which the characteristic belongs
  * @param Char_Handle Handle of the characteristic which has to be deleted
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_del_char(uint16_t Serv_Handle,
                             uint16_t Char_Handle);
/**
  * @brief Delete the specified service from the GATT server database.
  * @param Serv_Handle Handle of the service to be deleted
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_del_service(uint16_t Serv_Handle);
/**
  * @brief Delete the Include definition from the service.
  * @param Serv_Handle Handle of the service to which the include service belongs
  * @param Include_Handle Handle of the included service which has to be deleted
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_del_include_service(uint16_t Serv_Handle,
                                        uint16_t Include_Handle);
/**
  * @brief Mask events from the GATT. The default configuration is all the events masked.
  * @param GATT_Evt_Mask 0x00000001: ACI_GATT_ATTRIBUTE_MODIFIED_EVENT
0x00000002: ACI_GATT_PROC_TIMEOUT_EVENT
0x00000004: ACI_ATT_EXCHANGE_MTU_RESP_EVENT
0x00000008: ACI_ATT_FIND_INFO_RESP_EVENT
0x00000010: ACI_ATT_FIND_BY_TYPE_VALUE_RESP_EVENT
0x00000020: ACI_ATT_READ_BY_TYPE_RESP_EVENT
0x00000040: ACI_ATT_READ_RESP_EVENT
0x00000080: ACI_ATT_READ_BLOB_RESP_EVENT
0x00000100: ACI_ATT_READ_MULTIPLE_RESP_EVENT
0x00000200: ACI_ATT_READ_BY_GROUP_TYPE_RESP_EVENT
0x00000800: ACI_ATT_PREPARE_WRITE_RESP_EVENT
0x00001000: ACI_ATT_EXEC_WRITE_RESP_EVENT
0x00002000: ACI_GATT_INDICATION_EVENT
0x00004000: ACI_GATT_NOTIFICATION_EVENT
0x00008000: ACI_GATT_ERROR_RESP_EVENT
0x00010000: ACI_GATT_PROC_COMPLETE_EVENT
0x00020000: ACI_GATT_DISC_READ_CHAR_BY_UUID_RESP_EVENT
0x00040000: ACI_GATT_TX_POOL_AVAILABLE_EVENT
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_set_event_mask(uint32_t GATT_Evt_Mask);
/**
  * @brief Perform an ATT MTU exchange procedure.
When the ATT MTU exchange procedure is completed, a @ref aci_att_exchange_mtu_resp_event
event is generated. A @ref aci_gatt_proc_complete_event event is also generated
to indicate the end of the procedure.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_exchange_config(uint16_t Connection_Handle);
/**
  * @brief Send a Find Information Request.
This command is used to obtain the mapping of attribute handles with their associated
types. The responses of the procedure are given through the 
@ref aci_att_find_info_resp_event event. The end of the procedure is indicated by
a @ref aci_gatt_proc_complete_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Start_Handle First requested handle number
  * @param End_Handle Last requested handle number
  * @retval Value indicating success or error code.
*/
tBleStatus aci_att_find_info_req(uint16_t Connection_Handle,
                                 uint16_t Start_Handle,
                                 uint16_t End_Handle);
/**
  * @brief Send a Find By Type Value Request
The Find By Type Value Request is used to obtain the handles of attributes that
have a given 16-bit UUID attribute type and a given attribute value.
The responses of the procedure are given through the @ref aci_att_find_by_type_value_resp_event event.
The end of the procedure is indicated by a @ref aci_gatt_proc_complete_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Start_Handle First requested handle number
  * @param End_Handle Last requested handle number
  * @param UUID 2 octet UUID to find (little-endian)
  * @param Attribute_Val_Length Length of attribute value (maximum value is ATT_MTU - 7).
  * @param Attribute_Val Attribute value to find
  * @retval Value indicating success or error code.
*/
tBleStatus aci_att_find_by_type_value_req(uint16_t Connection_Handle,
                                          uint16_t Start_Handle,
                                          uint16_t End_Handle,
                                          uint16_t UUID,
                                          uint8_t Attribute_Val_Length,
                                          uint8_t Attribute_Val[]);
/**
  * @brief Send a Read By Type Request.
The Read By Type Request is used to obtain the values of attributes where the attribute
type is known but the handle is not known.
The responses of the procedure are given through the @ref aci_att_read_by_type_resp_event event.
The end of the procedure is indicated by a @ref aci_gatt_proc_complete_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Start_Handle First requested handle number
  * @param End_Handle Last requested handle number
  * @param UUID_Type 0x01 = 16-bit UUID,
0x02 = 128-bit UUID
  * @param UUID See @ref UUID_t
  * @retval Value indicating success or error code.
*/
tBleStatus aci_att_read_by_type_req(uint16_t Connection_Handle,
                                    uint16_t Start_Handle,
                                    uint16_t End_Handle,
                                    uint8_t UUID_Type,
                                    UUID_t *UUID);
/**
  * @brief Send a Read By Group Type Request. 
The Read By Group Type Request is used to obtain the values of grouping attributes where
the attribute type is known but the handle is not known. Grouping attributes are defined 
at GATT layer. The grouping attribute types are: "Primary Service", "Secondary Service" 
and "Characteristic". 
The responses of the procedure are given through the @ref aci_att_read_by_group_type_resp_event event. 
The end of the procedure is indicated by a @ref aci_gatt_proc_complete_event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Start_Handle First requested handle number
  * @param End_Handle Last requested handle number
  * @param UUID_Type 0x01 = 16-bit UUID,
0x02 = 128-bit UUID
  * @param UUID See @ref UUID_t
  * @retval Value indicating success or error code.
*/
tBleStatus aci_att_read_by_group_type_req(uint16_t Connection_Handle,
                                          uint16_t Start_Handle,
                                          uint16_t End_Handle,
                                          uint8_t UUID_Type,
                                          UUID_t *UUID);
/**
  * @brief Send a Prepare Write Request.
The Prepare Write Request is used to request the server to prepare to write the value of an attribute. 
The responses of the procedure are given through the @ref aci_att_prepare_write_resp_event event. 
The end of the procedure is indicated by a @ref aci_gatt_proc_complete_event. 
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Attr_Handle Handle of the attribute to be written
  * @param Val_Offset The offset of the first octet to be written
  * @param Attribute_Val_Length Length of attribute value (maximum value is ATT_MTU - 5).
  * @param Attribute_Val The value of the attribute to be written
  * @retval Value indicating success or error code.
*/
tBleStatus aci_att_prepare_write_req(uint16_t Connection_Handle,
                                     uint16_t Attr_Handle,
                                     uint16_t Val_Offset,
                                     uint8_t Attribute_Val_Length,
                                     uint8_t Attribute_Val[]);
/**
  * @brief Send an Execute Write Request.
The Execute Write Request is used to request the server to write or cancel the write 
of all the prepared values currently held in the prepare queue from this client. 
The result of the procedure is given through the @ref aci_att_exec_write_resp_event event. 
The end of the procedure is indicated by a @ref aci_gatt_proc_complete_event event. 
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Execute 0x00 = Cancel all prepared writes 
0x01 = Immediately write all pending prepared values
  * @retval Value indicating success or error code.
*/
tBleStatus aci_att_execute_write_req(uint16_t Connection_Handle,
                                     uint8_t Execute);
/**
  * @brief Start the GATT client procedure to discover all primary services on the server.
The responses of the procedure are given through the @ref aci_att_read_by_group_type_resp_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_disc_all_primary_services(uint16_t Connection_Handle);
/**
  * @brief Start the procedure to discover the primary services of the specified UUID on the server.
The responses of the procedure are given through the @ref aci_att_find_by_type_value_resp_event event.
The end of the procedure is indicated by a @ref aci_gatt_proc_complete_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param UUID_Type 0x01 = 16-bit UUID,
0x02 = 128-bit UUID
  * @param UUID See @ref UUID_t
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_disc_primary_service_by_uuid(uint16_t Connection_Handle,
                                                 uint8_t UUID_Type,
                                                 UUID_t *UUID);
/**
  * @brief Start the procedure to find all included services.
The responses of the procedure are given through the @ref aci_att_read_by_type_resp_event event.
The end of the procedure is indicated by a @ref aci_gatt_proc_complete_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Start_Handle Start attribute handle of the service
  * @param End_Handle End attribute handle of the service
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_find_included_services(uint16_t Connection_Handle,
                                           uint16_t Start_Handle,
                                           uint16_t End_Handle);
/**
  * @brief Start the procedure to discover all the characteristics of a given service.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
Before procedure completion the response packets are given through
@ref aci_att_read_by_type_resp_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Start_Handle Start attribute handle of the service
  * @param End_Handle End attribute handle of the service
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_disc_all_char_of_service(uint16_t Connection_Handle,
                                             uint16_t Start_Handle,
                                             uint16_t End_Handle);
/**
  * @brief Start the procedure to discover all the characteristics specified by a UUID.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
Before procedure completion the response packets are given through
@ref aci_gatt_disc_read_char_by_uuid_resp_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Start_Handle Start attribute handle of the service
  * @param End_Handle End attribute handle of the service
  * @param UUID_Type 0x01 = 16-bit UUID,
0x02 = 128-bit UUID
  * @param UUID See @ref UUID_t
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_disc_char_by_uuid(uint16_t Connection_Handle,
                                      uint16_t Start_Handle,
                                      uint16_t End_Handle,
                                      uint8_t UUID_Type,
                                      UUID_t *UUID);
/**
  * @brief Start the procedure to discover all characteristic descriptors on the server.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
Before procedure completion the response packets are given through
@ref aci_att_find_info_resp_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Char_Handle Handle of the characteristic value
  * @param End_Handle End handle of the characteristic
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_disc_all_char_desc(uint16_t Connection_Handle,
                                       uint16_t Char_Handle,
                                       uint16_t End_Handle);
/**
  * @brief Start the procedure to read the attribute value.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
Before procedure completion the response packet is given through @ref aci_att_read_resp_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Attr_Handle Handle of the characteristic to be read
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_read_char_value(uint16_t Connection_Handle,
                                    uint16_t Attr_Handle);
/**
  * @brief Start the procedure to read all the characteristics specified by the UUID.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
Before procedure completion the response packets are given through
@ref aci_gatt_disc_read_char_by_uuid_resp_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Start_Handle Starting handle of the range to be searched
  * @param End_Handle End handle of the range to be searched
  * @param UUID_Type 0x01 = 16-bit UUID,
0x02 = 128-bit UUID
  * @param UUID See @ref UUID_t
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_read_using_char_uuid(uint16_t Connection_Handle,
                                         uint16_t Start_Handle,
                                         uint16_t End_Handle,
                                         uint8_t UUID_Type,
                                         UUID_t *UUID);
/**
  * @brief Start the procedure to read a long characteristic value.
the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
Before procedure completion the response packets are given through @ref aci_att_read_blob_resp_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Attr_Handle Handle of the characteristic to be read
  * @param Val_Offset Offset from which the value needs to be read
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_read_long_char_value(uint16_t Connection_Handle,
                                         uint16_t Attr_Handle,
                                         uint16_t Val_Offset);
/**
  * @brief Start a procedure to read multiple characteristic values from a server.
This sub-procedure is used to read multiple Characteristic Values from a server when the
client knows the Characteristic Value Handles.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
Before procedure completion the response packets are given through
@ref aci_att_read_multiple_resp_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Number_of_Handles The number of handles for which the value has to be read
  * @param Handle_Entry See @ref Handle_Entry_t
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_read_multiple_char_value(uint16_t Connection_Handle,
                                             uint8_t Number_of_Handles,
                                             Handle_Entry_t Handle_Entry[]);
/**
  * @brief Start the procedure to write a long characteristic value.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
During the procedure, @ref aci_att_prepare_write_resp_event and @ref aci_att_exec_write_resp_event
events are raised.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Attr_Handle Handle of the characteristic to be written
  * @param Attribute_Val_Length Length of the value to be written
  * @param Attribute_Val Value to be written
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_write_char_value(uint16_t Connection_Handle,
                                     uint16_t Attr_Handle,
                                     uint8_t Attribute_Val_Length,
                                     uint8_t Attribute_Val[]);
/**
  * @brief Start the procedure to write a long characteristic value.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
During the procedure, @ref aci_att_prepare_write_resp_event and @ref aci_att_exec_write_resp_event
events are raised.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Attr_Handle Handle of the attribute to be written
  * @param Val_Offset Offset at which the attribute has to be written
  * @param Attribute_Val_Length Length of the value to be written
  * @param Attribute_Val Value to be written
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_write_long_char_value(uint16_t Connection_Handle,
                                          uint16_t Attr_Handle,
                                          uint16_t Val_Offset,
                                          uint8_t Attribute_Val_Length,
                                          uint8_t Attribute_Val[]);
/**
  * @brief Start the procedure to write a characteristic reliably.
When the procedure is completed, a  @ref aci_gatt_proc_complete_event event is generated.
During the procedure, @ref aci_att_prepare_write_resp_event and @ref aci_att_exec_write_resp_event
events are raised.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Attr_Handle Handle of the attribute to be written
  * @param Val_Offset Offset at which the attribute has to be written
  * @param Attribute_Val_Length Length of the value to be written
  * @param Attribute_Val Value to be written
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_write_char_reliable(uint16_t Connection_Handle,
                                        uint16_t Attr_Handle,
                                        uint16_t Val_Offset,
                                        uint8_t Attribute_Val_Length,
                                        uint8_t Attribute_Val[]);
/**
  * @brief Start the procedure to write a long characteristic descriptor.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
During the procedure, @ref aci_att_prepare_write_resp_event and @ref aci_att_exec_write_resp_event
events are raised.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Attr_Handle Handle of the attribute to be written
  * @param Val_Offset Offset at which the attribute has to be written
  * @param Attribute_Val_Length Length of the value to be written
  * @param Attribute_Val Value to be written
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_write_long_char_desc(uint16_t Connection_Handle,
                                         uint16_t Attr_Handle,
                                         uint16_t Val_Offset,
                                         uint8_t Attribute_Val_Length,
                                         uint8_t Attribute_Val[]);
/**
  * @brief Start the procedure to read a long characteristic value.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is
generated. Before procedure completion the response packets are given through
@ref aci_att_read_blob_resp_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Attr_Handle Handle of the characteristic descriptor
  * @param Val_Offset Offset from which the value needs to be read
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_read_long_char_desc(uint16_t Connection_Handle,
                                        uint16_t Attr_Handle,
                                        uint16_t Val_Offset);
/**
  * @brief Start the procedure to write a characteristic descriptor.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Attr_Handle Handle of the attribute to be written
  * @param Attribute_Val_Length Length of the value to be written
  * @param Attribute_Val Value to be written
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_write_char_desc(uint16_t Connection_Handle,
                                    uint16_t Attr_Handle,
                                    uint8_t Attribute_Val_Length,
                                    uint8_t Attribute_Val[]);
/**
  * @brief Start the procedure to read the descriptor specified.
When the procedure is completed, a @ref aci_gatt_proc_complete_event event is generated.
Before procedure completion the response packet is given through @ref aci_att_read_resp_event event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Attr_Handle Handle of the descriptor to be read
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_read_char_desc(uint16_t Connection_Handle,
                                   uint16_t Attr_Handle);
/**
  * @brief Start the procedure to write a characteristic value without waiting for any response from the
server. No events are generated after this command is executed.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Attr_Handle Handle of the attribute to be written
  * @param Attribute_Val_Length Length of the value to be written (maximum value is ATT_MTU - 3)
  * @param Attribute_Val Value to be written
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_write_without_resp(uint16_t Connection_Handle,
                                       uint16_t Attr_Handle,
                                       uint8_t Attribute_Val_Length,
                                       uint8_t Attribute_Val[]);
/**
  * @brief Start a signed write without response from the server.
The procedure is used to write a characteristic value with an authentication signature without waiting
for any response from the server. It cannot be used when the link is encrypted.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Attr_Handle Handle of the attribute to be written
  * @param Attribute_Val_Length Length of the value to be written (up to ATT_MTU - 13)
  * @param Attribute_Val Value to be written
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_signed_write_without_resp(uint16_t Connection_Handle,
                                              uint16_t Attr_Handle,
                                              uint8_t Attribute_Val_Length,
                                              uint8_t Attribute_Val[]);
/**
  * @brief Allow application to confirm indication. This command has to be sent when the application
receives the event @ref aci_gatt_indication_event.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_confirm_indication(uint16_t Connection_Handle);
/**
  * @brief Allow or reject a write request from a client.
This command has to be sent by the application when it receives the
@ref aci_gatt_write_permit_req_event. If the write can be allowed, then the status and error
code has to be set to 0. If the write cannot be allowed, then the status has to be set to 1 and
the error code has to be set to the error code that has to be passed to the client.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @param Attr_Handle Handle of the attribute that was passed in the event EVT_BLUE_GATT_WRITE_PERMIT_REQ
  * @param Write_status 0x00 = The value can be written to the attribute specified by attr_handle,
0x01 = The value cannot be written to the attribute specified by the attr_handle
  * @param Error_Code The error code that has to be passed to the client in case the write has to be rejected
  * @param Attribute_Val_Length Length of the value to be written as passed in the event EVT_BLUE_GATT_WRITE_PERMIT_REQ
  * @param Attribute_Val Value as passed in the event EVT_BLUE_GATT_WRITE_PERMIT_REQ
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_write_resp(uint16_t Connection_Handle,
                               uint16_t Attr_Handle,
                               uint8_t Write_status,
                               uint8_t Error_Code,
                               uint8_t Attribute_Val_Length,
                               uint8_t Attribute_Val[]);
/**
  * @brief Allow the GATT server to send a response to a read request from a client.
The application has to send this command when it receives the
@ref aci_gatt_read_permit_req_event or @ref aci_gatt_read_multi_permit_req_event. This
command indicates to the stack that the response can be sent to the client. So if the
application wishes to update any of the attributes before they are read by the client, it has to
update the characteristic values using the @ref aci_gatt_update_char_value and then give
this command. The application should perform the required operations within 30 seconds.
Otherwise the GATT procedure will be timeout.
  * @param Connection_Handle Connection handle for which the command is given. 
Range: 0x0000-0x0EFF (0x0F00 - 0x0FFF Reserved for future use)
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_allow_read(uint16_t Connection_Handle);
/**
  * @brief This command sets the security permission for the attribute handle specified. Currently the
setting of security permission is allowed only for client configuration descriptor.
  * @param Serv_Handle Handle of the service which contains the attribute whose security permission has to be modified
  * @param Attr_Handle Handle of the attribute whose security permission has to be modified
  * @param Security_Permissions 0x00: None,
0x01: AUTHEN_READ (Need authentication to read),
0x02: AUTHOR_READ (Need authorization to read),
0x04: ENCRY_READ (link should be encrypted to read),
0x08: AUTHEN_WRITE (need authentication to write),
0x10: AUTHOR_WRITE (need authorization to write),
0x20: ENCRY_WRITE (link should be encrypted to write)
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_set_security_permission(uint16_t Serv_Handle,
                                            uint16_t Attr_Handle,
                                            uint8_t Security_Permissions);
/**
  * @brief This command sets the value of the descriptor specified by charDescHandle.
  * @param Serv_Handle Handle of the service which contains the characteristic descriptor
  * @param Char_Handle Handle of the characteristic which contains the descriptor
  * @param Char_Desc_Handle Handle of the descriptor whose value has to be set
  * @param Val_Offset Offset from which the descriptor value has to be updated
  * @param Char_Desc_Value_Length Length of the descriptor value
  * @param Char_Desc_Value Descriptor value
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_set_desc_value(uint16_t Serv_Handle,
                                   uint16_t Char_Handle,
                                   uint16_t Char_Desc_Handle,
                                   uint16_t Val_Offset,
                                   uint8_t Char_Desc_Value_Length,
                                   uint8_t Char_Desc_Value[]);
/**
  * @brief Reads the value of the attribute handle specified from the local GATT database.
  * @param Attr_Handle Handle of the attribute to read
  * @param Offset Offset from which the value needs to be read
  * @param Value_Length_Requested Maximum number of octets to be returned as attibute value
  * @param[out] Length Length of the attribute value
  * @param[out] Value_Length Length in octets of the Value parameter
  * @param[out] Value Attribute value
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_read_handle_value(uint16_t Attr_Handle,
                                      uint16_t Offset,
                                      uint16_t Value_Length_Requested,
                                      uint16_t *Length,
                                      uint16_t *Value_Length,
                                      uint8_t Value[]);
/**
  * @brief This command is a more flexible version of @ref aci_gatt_update_char_value
                      to support update of long attribute up to 512 bytes and indicate selectively the generation of Indication/Notification.
  * @param Service_Handle Handle of service to which the characteristic belongs
  * @param Char_Handle Handle of the characteristic
  * @param Update_Type Allow Notification or Indication generation, if enabled in the client configuration descriptor
  * @param Char_Length Total length of the characteristic value.
                                                  In case of a variable size characteristic, this field specifies the new length of the characteristic value after the update; in case of fixed length characteristic this field is ignored.
  * @param Value_Offset The offset from which the attribute value has to be updated.
  * @param Value_Length Length of the Update_Value parameter in octets
  * @param Value Updated characteristic value
  * @retval Value indicating success or error code.
*/
tBleStatus aci_gatt_update_char_value_ext(uint16_t Service_Handle,
                                          uint16_t Char_Handle,
                                          uint8_t Update_Type,
                                          uint16_t Char_Length,
                                          uint16_t Value_Offset,
                                          uint8_t Value_Length,
                                          uint8_t Value[]);
/**
     * @}
     */
    #endif /* __BLUENRG1_GATT_ACI_H__*/