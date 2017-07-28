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

void XDOM_SetSteps(uint32_t start_steps, uint32_t stop_steps){
		uint8_t start_1_byte = (uint8_t) start_steps;
		uint8_t start_2_byte = (uint8_t) ((start_steps & 0x0000FF00) >> 8) ;
		uint8_t start_3_byte = (uint8_t) ((start_steps & 0x00FF0000) >> 16) ;
		uint8_t start_4_byte = (uint8_t) ((start_steps & 0xFF000000) >> 24) ;
	
	
		uint8_t stop_1_byte = (uint8_t) stop_steps;
		uint8_t stop_2_byte = (uint8_t) ((stop_steps & 0x0000FF00) >> 8) ;
		uint8_t stop_3_byte = (uint8_t) ((stop_steps & 0x00FF0000) >> 16) ;
		uint8_t stop_4_byte = (uint8_t) ((stop_steps & 0xFF000000) >> 24) ;
	
		FLASH_MOD_WriteByte(ADDRESS_START_STEPS,start_1_byte);
		FLASH_MOD_WriteByte(ADDRESS_START_STEPS+1,start_2_byte);
		FLASH_MOD_WriteByte(ADDRESS_START_STEPS+2,start_3_byte);
		FLASH_MOD_WriteByte(ADDRESS_START_STEPS+3,start_4_byte);
	
		FLASH_MOD_WriteByte(ADDRESS_STOP_STEPS,stop_1_byte);
		FLASH_MOD_WriteByte(ADDRESS_STOP_STEPS+1,stop_2_byte);
		FLASH_MOD_WriteByte(ADDRESS_STOP_STEPS+2,stop_3_byte);
		FLASH_MOD_WriteByte(ADDRESS_STOP_STEPS+3,stop_4_byte);
}

void XDOM_SetActualStartSteps(uint32_t start_steps){
		uint8_t start_1_byte = (uint8_t) start_steps;
		uint8_t start_2_byte = (uint8_t) ((start_steps & 0x0000FF00) >> 8) ;
		uint8_t start_3_byte = (uint8_t) ((start_steps & 0x00FF0000) >> 16) ;
		uint8_t start_4_byte = (uint8_t) ((start_steps & 0xFF000000) >> 24) ;
	
		FLASH_MOD_WriteByte(ADDRESS_ACTUAL_START_STEPS,start_1_byte);
		FLASH_MOD_WriteByte(ADDRESS_ACTUAL_START_STEPS+1,start_2_byte);
		FLASH_MOD_WriteByte(ADDRESS_ACTUAL_START_STEPS+2,start_3_byte);
		FLASH_MOD_WriteByte(ADDRESS_ACTUAL_START_STEPS+3,start_4_byte);
}

void XDOM_SetActualStopSteps(uint32_t stop_steps){
		uint8_t start_1_byte = (uint8_t) stop_steps;
		uint8_t start_2_byte = (uint8_t) ((stop_steps & 0x0000FF00) >> 8) ;
		uint8_t start_3_byte = (uint8_t) ((stop_steps & 0x00FF0000) >> 16) ;
		uint8_t start_4_byte = (uint8_t) ((stop_steps & 0xFF000000) >> 24) ;
	
		FLASH_MOD_WriteByte(ADDRESS_ACTUAL_STOP_STEPS,start_1_byte);
		FLASH_MOD_WriteByte(ADDRESS_ACTUAL_STOP_STEPS+1,start_2_byte);
		FLASH_MOD_WriteByte(ADDRESS_ACTUAL_STOP_STEPS+2,start_3_byte);
		FLASH_MOD_WriteByte(ADDRESS_ACTUAL_STOP_STEPS+3,start_4_byte);
}

uint32_t XDOM_GetStartSteps(){
	
	uint8_t step_1_byte = FLASH_MOD_ReadByte(ADDRESS_START_STEPS);
	uint8_t step_2_byte = FLASH_MOD_ReadByte(ADDRESS_START_STEPS+1);
	uint8_t step_3_byte = FLASH_MOD_ReadByte(ADDRESS_START_STEPS+2);
	uint8_t step_4_byte = FLASH_MOD_ReadByte(ADDRESS_START_STEPS+3);
	return (step_1_byte | (step_2_byte << 8) | (step_3_byte << 16) | (step_4_byte << 24));
}


uint32_t XDOM_GetActualStartSteps(){
	
	uint8_t step_1_byte = FLASH_MOD_ReadByte(ADDRESS_ACTUAL_START_STEPS);
	uint8_t step_2_byte = FLASH_MOD_ReadByte(ADDRESS_ACTUAL_START_STEPS+1);
	uint8_t step_3_byte = FLASH_MOD_ReadByte(ADDRESS_ACTUAL_START_STEPS+2);
	uint8_t step_4_byte = FLASH_MOD_ReadByte(ADDRESS_ACTUAL_START_STEPS+3);
	return (step_1_byte | (step_2_byte << 8) | (step_3_byte << 16) | (step_4_byte << 24));
}

uint32_t XDOM_GetStopSteps(){
	
	uint8_t step_1_byte = FLASH_MOD_ReadByte(ADDRESS_STOP_STEPS);
	uint8_t step_2_byte = FLASH_MOD_ReadByte(ADDRESS_STOP_STEPS+1);
	uint8_t step_3_byte = FLASH_MOD_ReadByte(ADDRESS_STOP_STEPS+2);
	uint8_t step_4_byte = FLASH_MOD_ReadByte(ADDRESS_STOP_STEPS+3);
	return (step_1_byte | (step_2_byte << 8) | (step_3_byte << 16) | (step_4_byte << 24));
}

uint32_t XDOM_GetActualStopSteps(){
	
	uint8_t step_1_byte = FLASH_MOD_ReadByte(ADDRESS_ACTUAL_STOP_STEPS);
	uint8_t step_2_byte = FLASH_MOD_ReadByte(ADDRESS_ACTUAL_STOP_STEPS+1);
	uint8_t step_3_byte = FLASH_MOD_ReadByte(ADDRESS_ACTUAL_STOP_STEPS+2);
	uint8_t step_4_byte = FLASH_MOD_ReadByte(ADDRESS_ACTUAL_STOP_STEPS+3);
	return (step_1_byte | (step_2_byte << 8) | (step_3_byte << 16) | (step_4_byte << 24));
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
