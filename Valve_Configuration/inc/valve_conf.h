#ifndef _VALVE_CONF_H_
#define _VALVE_CONF_H_

#include "flash_mod.h"
#include "valve_registers.h"
#include "stdint.h"

typedef enum{
	CONFIG_NOT_PRESENT = 0,
	CONFIG_PRESENT = 1
}XDOM_ConfigStatus;

void XDOM_SetConfigured(void);

int XDOM_IsConfigured(void);

void WriteTestConfiguration(void);

uint8_t XDOM_SetRole(char* role, uint8_t size);

void XDOM_SetName(char* name, uint8_t size);

void XDOM_SetNameByteForm(uint8_t* name, uint8_t size);

void XDOM_SetSteps(uint8_t start_steps, uint8_t stop_steps);

uint8_t XDOM_GetStartSteps(void);

uint8_t XDOM_GetStopSteps(void);

uint32_t* XDOM_GetValveName(uint8_t* size);

uint32_t* XDOM_GetValveCpltName(uint8_t* size);

void XDOM_SetZone(uint8_t zone);

void XDOM_SetTime(uint8_t* time);

void XDOM_EraseConfigArea(void);

#endif
