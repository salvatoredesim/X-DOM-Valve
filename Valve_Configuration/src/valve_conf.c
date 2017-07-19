#include "valve_conf.h"
#include "stdint.h"
#include "osal.h"

#ifndef DEBUG
#define DEBUG 1
#endif

#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

int XDOM_IsConfigured(){
	
		/* Encoded value of CONFIGURED */
		uint8_t X_DOM_ConfigValue[10] = {0x43, 0x4f, 0x4e, 0x46, 0x49, 0x47, 0x55, 0x52, 0x45, 0x44};
		uint8_t X_DOM_ReadValue[10];
		
		/* Read the value in Flash and compares with the default configured value */
		Osal_MemCpy(X_DOM_ReadValue,(uint8_t*)ADDRESS_CONFIGURED,10);
		return Osal_MemCmp(X_DOM_ConfigValue,X_DOM_ReadValue,10);
}

uint8_t XDOM_SetRole(char* role, uint8_t size){
		
		/* Two possible roles */
		char* X_DOM_Peripheral_Role = "peripheral";
		char* X_DOM_Authonomous_Role = "authonomous";
		
		if(!Osal_MemCmp(X_DOM_Peripheral_Role,role,size) || !Osal_MemCmp(X_DOM_Authonomous_Role,role,size)){
			FLASH_MOD_WriteCharBurst(ADDRESS_ROLE, role,size);
			return 0;
		}else
			return 1;
}

void XDOM_SetConfigured(){
		uint8_t X_DOM_ConfigValue[10] = {0x43, 0x4f, 0x4e, 0x46, 0x49, 0x47, 0x55, 0x52, 0x45, 0x44};
		FLASH_MOD_WriteByteBurst(ADDRESS_CONFIGURED,X_DOM_ConfigValue,10);
}

void XDOM_SetSteps(uint8_t start_steps, uint8_t stop_steps){
		FLASH_MOD_WriteByte(ADDRESS_START_STEPS,start_steps);
		FLASH_MOD_WriteByte(ADDRESS_STOP_STEPS,stop_steps);
}

uint8_t XDOM_GetStartSteps(){
	return FLASH_MOD_ReadByte(ADDRESS_START_STEPS);
}

uint8_t XDOM_GetStopSteps(){
	return FLASH_MOD_ReadByte(ADDRESS_STOP_STEPS);
}

void XDOM_SetNotConfigured(){
		uint8_t X_DOM_ConfigValue[10] = {0xFF, 0x4f, 0x4e, 0x46, 0x49, 0x47, 0x55, 0x52, 0x45, 0x44};
		FLASH_MOD_WriteByteBurst(ADDRESS_CONFIGURED,X_DOM_ConfigValue,10);
}

void XDOM_SetName(char* name, uint8_t size){
		FLASH_MOD_WriteByte(ADDRESS_INITIAL_NAME,size+1);
		FLASH_MOD_WriteByte(ADDRESS_INITIAL_NAME+1,0x09);
		FLASH_MOD_WriteCharBurst(ADDRESS_INITIAL_NAME+2,name,size);
}


void XDOM_SetNameByteForm(uint8_t* name, uint8_t size){
		FLASH_MOD_WriteByte(ADDRESS_INITIAL_NAME,size+1);
		FLASH_MOD_WriteByte(ADDRESS_INITIAL_NAME+1,0x09);
		FLASH_MOD_WriteByteBurst(ADDRESS_INITIAL_NAME+2,name,size);
}

uint32_t* XDOM_GetValveName(uint8_t* size){
	*size = FLASH_MOD_ReadByte(ADDRESS_INITIAL_NAME)-1;
	return (uint32_t*) (ADDRESS_INITIAL_NAME+2);
}

uint32_t* XDOM_GetValveCpltName(uint8_t* size){
	*size = FLASH_MOD_ReadByte(ADDRESS_INITIAL_NAME);
	return (uint32_t*) (ADDRESS_INITIAL_NAME+1);
}

void XDOM_SetZone(uint8_t zone){
		FLASH_MOD_WriteByte(ADDRESS_ZONE,zone);
}

void XDOM_SetTime(uint8_t* time){
		FLASH_MOD_WriteByteBurst(ADDRESS_TIME,time,6);
}

void WriteTestConfiguration(){
		XDOM_SetRole("peripheral",10);
		XDOM_SetName("X-DOM-V01",9);
		XDOM_SetConfigured();
}

void XDOM_EraseConfigArea(){
		FLASH_EraseAddress(ADDRESS_CONFIGURED);
}
