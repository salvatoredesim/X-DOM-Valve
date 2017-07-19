#include "bluenrg_services.h"

/* UUIDS */
Service_UUID_t service_uuid;
Char_UUID_t char_uuid;
Char_UUID_t char_ack_uuid;

uint16_t BLEServHandle, BLECharCmdHandle;
uint16_t BLECharAckHandle;

tBleStatus Add_BLE_Interface_Service(void)
{
  tBleStatus ret;
  uint8_t uuid[16];

  COPY_ACC_SERVICE_UUID(uuid);
	
  Osal_MemCpy(&service_uuid.Service_UUID_128, uuid, 16);
  ret = aci_gatt_add_service(UUID_TYPE_128,  &service_uuid, PRIMARY_SERVICE, 22, &BLEServHandle);
  if (ret != BLE_STATUS_SUCCESS) goto fail;    

  COPY_FREE_FALL_UUID(uuid);
  Osal_MemCpy(&char_uuid.Char_UUID_128, uuid, 16);
  
  ret =  aci_gatt_add_char(BLEServHandle, UUID_TYPE_128, &char_uuid, 20, CHAR_PROP_WRITE_WITHOUT_RESP, ATTR_PERMISSION_NONE, GATT_NOTIFY_ATTRIBUTE_WRITE,
                           16, 1, &BLECharCmdHandle);
  if (ret != BLE_STATUS_SUCCESS) goto fail;
  
  COPY_ACK_UUID(uuid);
  Osal_MemCpy(&char_ack_uuid.Char_UUID_128, uuid, 16);
  ret =  aci_gatt_add_char(BLEServHandle, UUID_TYPE_128, &char_ack_uuid, 2, CHAR_PROP_READ, ATTR_PERMISSION_NONE, GATT_NOTIFY_READ_REQ_AND_WAIT_FOR_APPL_RESP,
                           16, 0, &BLECharAckHandle);
  if (ret != BLE_STATUS_SUCCESS) goto fail;

  //PRINTF("Service ACC added. Handle 0x%04X, Free fall Charac handle: 0x%04X, Acc Charac handle: 0x%04X\n",accServHandle, freeFallCharHandle, accCharHandle);	
  return BLE_STATUS_SUCCESS; 

 fail:
  //PRINTF("Error while adding ACC service.\n");
  return BLE_STATUS_ERROR ;
    
}
