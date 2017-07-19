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

#define IMPLEMENTED_INT_LINES		0

uint8_t type_message;
uint8_t payload_size;

uint8_t operation_pending = 0;
uint8_t name_conf = 0, zone_conf = 0, time_conf = 0;
uint8_t stop_flag = 0;

extern uint8_t isStartReached;
extern uint8_t isEndReached;

extern uint16_t BLEServHandle;
extern uint16_t BLECharAckHandle;

void ExtractPayload(uint8_t Attr_Data[], uint8_t* payload, uint8_t size){
		Osal_MemCpy(payload,Attr_Data+3,size);
}

void ParseMessage(uint8_t Attr_Data[], uint8_t Attr_Data_Length){
	
	PRINTF("Command Received: ");
		int i = 0;
		while(i < Attr_Data_Length){
			PRINTF("0x%02x ", Attr_Data[i]);
			i++;
		}
		PRINTF("\r\n");
				
		type_message = Attr_Data[1]; 
		payload_size = Attr_Data[2];
		
		uint8_t payload[payload_size];
		
		Osal_MemSet(payload,0x00,payload_size);
		
		ExtractPayload(Attr_Data,payload,payload_size);
		
		switch(type_message){
			case RESET:{
				PRINTF("You performed a RESET \r\n");
				XDOM_EraseConfigArea();
				name_conf = 0;
				zone_conf = 0;
				time_conf = 0;
			}
				break;
			case INIT_DATA:
				if(XDOM_IsConfigured()){
				PRINTF("You performed a INIT_DATA \r\n");
				XDOM_Configure(payload,payload_size);
				}
				break;
			case OPEN:
			{
				PRINTF("You performed a OPEN \r\n");
				operation_pending = 1;
				XDOM_Open_Close(payload,payload_size,type_message,CLOCKWISE);
				operation_pending = 0;
				break;
			}
			case CLOSE:
				PRINTF("You performed a CLOSE \r\n");
				operation_pending = 1;
				XDOM_Open_Close(payload,payload_size,type_message,ANTICLOCKWISE);
				operation_pending = 0;
				break;
			case STOP_CMD:
				if(operation_pending){
					PRINTF("You performed a STOP \r\n");
					stop_flag = 1;
				}
				break;
			default:
				PRINTF("Unknown command. \r\n");
			break;
		}
		
}

void XDOM_Configure(uint8_t Payload_Data[], uint8_t size){
		int i = 0;
		while(i < size){
				uint8_t TAG = Payload_Data[i];
				uint8_t LEN = Payload_Data[i+1];
				uint8_t TAG_DATA[LEN];
				
				Osal_MemSet(TAG_DATA,0x00,LEN);
				Osal_MemCpy(TAG_DATA,Payload_Data+i+2,LEN);
			
				switch(TAG){
					case NAME_VALVE:{
						XDOM_SetNameByteForm(TAG_DATA,LEN);
						name_conf = 1;
						break;
					}
					case ZONE_NAME:{
						XDOM_SetZone(TAG_DATA[0]);
						zone_conf = 1;
						break;
					}
					case TIME_CLOCK:{
						XDOM_SetTime(TAG_DATA);
						time_conf = 1;
						break;
					}
				}
				
				i = i + 2 + LEN;
		
		}
		
		if((name_conf) && (zone_conf) && (time_conf)){
			XDOM_SetConfigured();
		}
}

void XDOM_Open_Close(uint8_t Payload_Data[], uint8_t size, uint8_t command, uint8_t orientation){
	int i = 0;
	while(i < size){
			uint8_t TAG = Payload_Data[i];
			uint8_t LEN = Payload_Data[i+1];
			uint8_t TAG_DATA[LEN];
			Osal_MemSet(TAG_DATA,0x00,LEN);
			Osal_MemCpy(TAG_DATA,Payload_Data+i+2,LEN);
			
			switch(TAG){
				case FULL:{
					uint16_t steps;
					if(command == OPEN){
						steps = XDOM_GetStartSteps();
					}
					else{
						steps = XDOM_GetStopSteps();
					}
					XDOM_Open_Close_Steps(command,orientation,steps);
					break;
				}
				case STEP:
					break;
				case HALF:
					break;
				case QUARTER:
					break;
				
			}
			i = i + 2 + LEN;
	}
	
}
 
uint16_t steps_open_done = 0;
uint16_t steps_close_done = 0;

void XDOM_Open_Close_Steps(uint8_t command,uint8_t orientation, uint8_t steps_needed){
		uint16_t step_to_open;
		uint16_t step_to_close;
		uint8_t steps_to_do;
		uint16_t steps = 0;
#if IMPLEMENTED_INT_LINES
		if((command == OPEN) && !isEndReached){
#else
		if(command == OPEN){
#endif
			step_to_open = steps_needed;
			PRINTF("Performing %x open steps... \r\n",step_to_open);

			if(steps_open_done == step_to_open){
				steps = 0;
				steps_to_do = step_to_open;
			}
			else{
				steps_to_do = step_to_open - steps_open_done;
				steps = steps_open_done;
			}
			
			while((steps < steps_to_do) && !stop_flag){
				ULN2003_STEP(orientation);
				steps++;
			}
			steps_open_done = steps;
		}

#if IMPLEMENTED_INT_LINES		
		if((command == CLOSE) && !isStartReached){
#else
		if(command == CLOSE){
#endif
			step_to_close = steps_needed;
			PRINTF("Performing %x close steps... \r\n",step_to_close);
			
			if(steps_close_done == step_to_close) {
				steps = 0;
				steps_to_do = step_to_close;
			}
			else{
				steps_to_do = step_to_close - steps_close_done;
				steps = steps_close_done;
			}
			
			while((steps < steps_to_do) && !stop_flag){
				ULN2003_STEP(orientation);
				steps++;
			}
			steps_close_done = steps;
		}
		stop_flag = 0;
		

}
