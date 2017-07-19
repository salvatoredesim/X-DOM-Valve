#ifndef _BLUENRG_INTERFACE_H
#define _BLUENRG_INTERFACE_H

#include "bluenrg_configuration.h"
#include "bluenrg1_stack.h"
#include "ble_status.h"
#include "ble_const.h" 
#include "stdint.h"
#include "bluenrg_services.h"
#include "BlueNRG1_it.h"
#include "BlueNRG1_conf.h"

#include "SDK_EVAL_Config.h"
#include "ULN2003.h"

/* Initialize the BLE Interface */
void BlueNRG_Interface_Init(uint8_t * mac_address);

/* Setup the BlueNRG device */
uint8_t BlueNRG_Device_Peripheral_Init(uint8_t * mac_address);

/* Make the device connectable */
void BlueNRG_SetConnectable(void);

#endif
