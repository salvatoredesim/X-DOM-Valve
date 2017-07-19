#include "bluenrg_interface.h"
#include "valve.h"
#include "valve_conf.h"
#include "protocol.h"

#ifndef DEBUG
#define DEBUG 1
#endif

#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

extern ValveStatus appStatus;
#define SENSOR_TIMER 1
static uint8_t sensorTimer_expired = FALSE;

/* RAM reserved to manage all the data stack according the number of links,
 * number of services, number of attributes and attribute value length
 */
NO_INIT(uint32_t dyn_alloc_a[TOTAL_BUFFER_SIZE(NUM_LINKS,NUM_GATT_ATTRIBUTES,NUM_GATT_SERVICES,ATT_VALUE_ARRAY_SIZE)>>2]);

/* FLASH reserved to store all the security database information and
 * and the server database information
 */
ALIGN(4)
SECTION(".noinit.stacklib_flash_data")
NOLOAD(const uint32_t stacklib_flash_data[TOTAL_FLASH_BUFFER_SIZE(FLASH_SEC_DB_SIZE, FLASH_SERVER_DB_SIZE)>>2]);
/* FLASH reserved to store: security root keys, static random address, public address */
ALIGN(4)
SECTION(".noinit.stacklib_stored_device_id_data")
NOLOAD(const uint8_t stacklib_stored_device_id_data[56]);

/* This structure contains memory and low level hardware configuration data for the device */
const BlueNRG_Stack_Initialization_t BlueNRG_Stack_Init_params = {
    (uint8_t*)stacklib_flash_data,
    FLASH_SEC_DB_SIZE,
    FLASH_SERVER_DB_SIZE,
    (uint8_t*)stacklib_stored_device_id_data,
    (uint8_t*)dyn_alloc_a,
    NUM_GATT_ATTRIBUTES,
    NUM_GATT_SERVICES,
    ATT_VALUE_ARRAY_SIZE,
    NUM_LINKS,
    CONFIG_TABLE
};

volatile uint8_t set_connectable = 1;

uint16_t connection_handle = 0;
uint8_t connInfo[20];

BOOL sensor_board = FALSE; // It is True if sensor boad has been detected

//int connected = FALSE;

extern uint16_t BLECharCmdHandle;
extern uint16_t BLECharAckHandle;

void BlueNRG_Interface_Init(uint8_t * mac_address){
	
	uint8_t ret;
	/* BlueNRG-1 stack init */
  ret = BlueNRG_Stack_Initialization(&BlueNRG_Stack_Init_params);
  if (ret != BLE_STATUS_SUCCESS) {
    PRINTF("Error in BlueNRG_Stack_Initialization() 0x%02x\r\n", ret);
    while(1);
  }
	else{
    PRINTF("Initializing... \r\n");
	}
}


uint8_t BlueNRG_Device_Peripheral_Init(uint8_t* mac_address){
  uint8_t ret;
  uint16_t service_handle, dev_name_char_handle, appearance_char_handle;
	
  uint8_t device_name[] = {'X','-','D','O','M','-','N','C'};
	
  /* Set the device public address */
  ret = aci_hal_write_config_data(CONFIG_DATA_PUBADDR_OFFSET, CONFIG_DATA_PUBADDR_LEN,
                                  mac_address);  
  if(ret != BLE_STATUS_SUCCESS) {
    //PRINTF("aci_hal_write_config_data() failed: 0x%02x\r\n", ret);
    return ret;
  }
  
  /* Set the TX power -2 dBm */
  aci_hal_set_tx_power_level(1, 4);
  
  /* GATT Init */
  ret = aci_gatt_init();
  if (ret != BLE_STATUS_SUCCESS) {
    //PRINTF("aci_gatt_init() failed: 0x%02x\r\n", ret);
    return ret;
  }
  
  /* GAP Init */
  ret = aci_gap_init(GAP_PERIPHERAL_ROLE, 0, 0x08, &service_handle, &dev_name_char_handle, &appearance_char_handle);
  if (ret != BLE_STATUS_SUCCESS) {
    //PRINTF("aci_gap_init() failed: 0x%02x\r\n", ret);
    return ret;
  }
 
  /* Update device name */

		ret = aci_gatt_update_char_value(service_handle, dev_name_char_handle, 0, sizeof(device_name), device_name);
  if(ret != BLE_STATUS_SUCCESS) {
    //PRINTF("aci_gatt_update_char_value() failed: 0x%02x\r\n", ret);
    return ret;
  }
  
  /* Set Authentication requirements */
  ret = aci_gap_set_authentication_requirement(MITM_PROTECTION_REQUIRED,
                                               OOB_AUTH_DATA_ABSENT,
                                               NULL,
                                               7,
                                               16,
                                               USE_FIXED_PIN_FOR_PAIRING,
                                               123456,
                                               NO_BONDING);
  if(ret != BLE_STATUS_SUCCESS) {
    PRINTF("aci_gap_set_authentication_requirement()failed: 0x%02x\r\n", ret);
    return ret;
  }
  Add_BLE_Interface_Service();
  PRINTF("BLE Stack Initialized with SUCCESS\n");

  return BLE_STATUS_SUCCESS;
}

void BlueNRG_SetConnectable(){
	
		uint8_t ret;
		uint8_t local_name[] = {AD_TYPE_COMPLETE_LOCAL_NAME,'X','-','D','O','M','-','N','C'}; 

#if ST_OTA_FIRMWARE_UPGRADE_SUPPORT
		hci_le_set_scan_response_data(18,BTLServiceUUID4Scan); 
#else
		hci_le_set_scan_response_data(0,NULL);
#endif /* ST_OTA_FIRMWARE_UPGRADE_SUPPORT */ 
  //PRINTF("Set General Discoverable Mode.\n");
		
		if(!XDOM_IsConfigured()){
			uint8_t size_name;
			uint8_t* dev_name = (uint8_t*) XDOM_GetValveCpltName(&size_name);	
			
			ret = aci_gap_set_discoverable(ADV_IND,
                                (ADV_INTERVAL_MIN_MS*1000)/625,(ADV_INTERVAL_MAX_MS*1000)/625,
                                 STATIC_RANDOM_ADDR, NO_WHITE_LIST_USE,
                                 size_name, dev_name, 0, NULL, 0, 0); 
		}
		else{
			ret = aci_gap_set_discoverable(ADV_IND,
                                (ADV_INTERVAL_MIN_MS*1000)/625,(ADV_INTERVAL_MAX_MS*1000)/625,
                                 STATIC_RANDOM_ADDR, NO_WHITE_LIST_USE,
                                 sizeof(local_name), local_name, 0, NULL, 0, 0); 
		}
		if(ret == BLE_STATUS_SUCCESS)
			PRINTF("Valve BLE Interface Discoverable. \r\n");
}

/* ***************** BlueNRG-1 Stack Callbacks ********************************/

/*******************************************************************************
 * Function Name  : hci_le_connection_complete_event.
 * Description    : This event indicates that a new connection has been created.
 * Input          : See file bluenrg1_events.h
 * Output         : See file bluenrg1_events.h
 * Return         : See file bluenrg1_events.h
 *******************************************************************************/
void hci_le_connection_complete_event(uint8_t Status,
                                      uint16_t Connection_Handle,
                                      uint8_t Role,
                                      uint8_t Peer_Address_Type,
                                      uint8_t Peer_Address[6],
                                      uint16_t Conn_Interval,
                                      uint16_t Conn_Latency,
                                      uint16_t Supervision_Timeout,
                                      uint8_t Master_Clock_Accuracy)
{ 
  connection_handle = Connection_Handle;
  PRINTF("Valve connected. \r\n");
	int i = 0;
	PRINTF("Address: ");
	while(i < 6){
		PRINTF("0x%02x ",Peer_Address[i]);
		i++;
	}
	PRINTF(" \r\n");
#if UPDATE_CONN_PARAM    
  l2cap_request_sent = FALSE;
  Timer_Set(&l2cap_req_timer, CLOCK_SECOND*2);
#endif
    
}/* end hci_le_connection_complete_event() */

/*******************************************************************************
 * Function Name  : hci_disconnection_complete_event.
 * Description    : This event occurs when a connection is terminated.
 * Input          : See file bluenrg1_events.h
 * Output         : See file bluenrg1_events.h
 * Return         : See file bluenrg1_events.h
 *******************************************************************************/
void hci_disconnection_complete_event(uint8_t Status,
                                      uint16_t Connection_Handle,
                                      uint8_t Reason)
{
	connection_handle = 0;
  PRINTF("Valve disconnected. \r\n");
	BlueNRG_SetConnectable();
	appStatus = INITIAL_CALIBRATION;
	SdkEvalLedOff(LED3);
  
  //SdkEvalLedOff(LED3);//activity led 
}/* end hci_disconnection_complete_event() */


/*******************************************************************************
 * Function Name  : aci_gatt_read_permit_req_event.
 * Description    : This event is given when a read request is received
 *                  by the server from the client.
 * Input          : See file bluenrg1_events.h
 * Output         : See file bluenrg1_events.h
 * Return         : See file bluenrg1_events.h
 *******************************************************************************/
void aci_gatt_read_permit_req_event(uint16_t Connection_Handle,
                                    uint16_t Attribute_Handle,
                                    uint16_t Offset)
{
	if(Attribute_Handle == BLECharAckHandle +1){
		XDOM_LoadStatus();
		PRINTF("READ Event generated. \r\n");
		aci_gatt_allow_read(connection_handle);
	}
  //Read_Request_CB(Attribute_Handle);    
}

/*******************************************************************************
 * Function Name  : HAL_VTimerTimeoutCallback.
 * Description    : This function will be called on the expiry of 
 *                  a one-shot virtual timer.
 * Input          : See file bluenrg1_stack.h
 * Output         : See file bluenrg1_stack.h
 * Return         : See file bluenrg1_stack.h
 *******************************************************************************/
void HAL_VTimerTimeoutCallback(uint8_t timerNum)
{
  if (timerNum == SENSOR_TIMER) {
    sensorTimer_expired = TRUE;
  }
}

/*******************************************************************************
 * Function Name  : aci_gatt_attribute_modified_event.
 * Description    : This event occurs when an attribute is modified.
 * Input          : See file bluenrg1_events.h
 * Output         : See file bluenrg1_events.h
 * Return         : See file bluenrg1_events.h
 *******************************************************************************/
void aci_gatt_attribute_modified_event(uint16_t Connection_Handle,
                                       uint16_t Attr_Handle,
                                       uint16_t Offset,
                                       uint8_t Attr_Data_Length,
                                       uint8_t Attr_Data[])
{
	if(Attr_Handle == BLECharCmdHandle +1)
	{
		ParseMessage(Attr_Data,Attr_Data_Length);
		
		//SdkEvalLedToggle(LED2);
		//ULN2003_TestSequence(1,CLOCKWISE);
	}else{
		SdkEvalLedOn(LED3);
	}
#if ST_OTA_FIRMWARE_UPGRADE_SUPPORT
  OTA_Write_Request_CB(Attr_Handle, Attr_Data_Length, Attr_Data);
#endif /* ST_OTA_FIRMWARE_UPGRADE_SUPPORT */ 
}
