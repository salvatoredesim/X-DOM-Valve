#include "valve.h"

uint8_t isStartReached = 0;
uint8_t isEndReached = 0;

ValveStatus appStatus = INITIAL_CALIBRATION;
ValveRole valveRole = UNKNOWN_ROLE;

extern uint32_t steps_open_done;
extern uint32_t steps_close_done;

#ifndef DEBUG
#define DEBUG 1
#endif

#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

void Activate_Peripheral(){
			PRINTF("Activating BLE Interface... \r\n");
			
			/* BlueNRG-1 stack init */
			uint8_t bdaddr[] = {0x12, 0x34, 0x00, 0xE1, 0x80, 0x02};
			BlueNRG_Interface_Init(bdaddr);	
			
			/* Initializing device as peripheral */
			BlueNRG_Device_Peripheral_Init(bdaddr);
		
			/* Application Tick */
			BlueNRG_SetConnectable();
			
}

void PrintConfiguration(){
			uint8_t size_name;
			uint8_t* address_name = (uint8_t*) XDOM_GetValveName(&size_name);
			uint8_t valve_name[size_name];
	
			Osal_MemCpy(valve_name,address_name,size_name);
			int i = 0;
			
			PRINTF("\r\n");
			PRINTF("------------------------------------------------------ \r\n");
			PRINTF("Address Valve Name: 0x%x \r\n", ADDRESS_INITIAL_NAME);
			PRINTF("Valve Name:");
			while(i < size_name){
					PRINTF("%c", valve_name[i]);
					i++;
			}
			PRINTF("\r\n");
			PRINTF("------------------------------------------------------ \r\n");
			
			
			PRINTF("\r\n");
			PRINTF("------------------------------------------------------ \r\n");
			PRINTF("Address Zone: 0x%x \r\n", ADDRESS_ZONE);
			uint8_t zone = FLASH_MOD_ReadByte(ADDRESS_ZONE);
			PRINTF("Zone: %d \r\n",zone);
			PRINTF("------------------------------------------------------ \r\n");
			
			PRINTF("\r\n");
			PRINTF("------------------------------------------------------ \r\n");
			PRINTF("Address Time: 0x%x \r\n", ADDRESS_TIME);
			uint8_t time[TIME_SIZE];
			Osal_MemCpy(time,(uint8_t*)(ADDRESS_TIME),TIME_SIZE);
			
			PRINTF("%d/%d/%d - %d:%d:%d \r\n",time[0],time[1],time[2],time[3],time[4],time[5]);
				
			PRINTF("------------------------------------------------------ \r\n");
			
}

void Valve_APP(){
	switch(appStatus){
		
		case INITIAL_CALIBRATION:
			if(XDOM_IsConfigured()){
				PRINTF("Calibrating Valve Motor... \r\n");
				Calibrate();
				PRINTF("Calibration Complete. \r\n");
			}
				appStatus = READ_CONFIGURATION;
			break;
		
		case READ_CONFIGURATION:{
				if(!XDOM_IsConfigured()){
					PRINTF("Loading configuration. \r\n");
					PrintConfiguration();
					appStatus = PERIPHERAL;
					
				}else{
					PRINTF("Device not configured. \r\n");
					appStatus = NOT_CONFIGURED;
				}
			break;
		}
		
		case NOT_CONFIGURED:{
			
			Activate_Peripheral();
			appStatus = IDLE;

			break;
		}
		
		case PERIPHERAL:
			
			Activate_Peripheral();
			appStatus = IDLE;
			break;
		
		case AUTHONOMOUS:
			break;
		
		case IDLE:
			/* BLE Stack Tick */
			BTLE_StackTick();
			break;
	}
}

void Calibrate(){
	
		uint32_t open_steps = 0;
		uint32_t close_steps = 0;
	
		while(!isEndReached){
					ULN2003_STEP(CLOCKWISE);
					close_steps++;
		}
		isEndReached = 0;
		
		while(!isStartReached){
					ULN2003_STEP(ANTICLOCKWISE);
					open_steps++;
		}

		ULN2003_StopAll();
		
		PRINTF("Steps to open valve: 0x%02x \r\n",open_steps);
		PRINTF("Steps to close valve: 0x%02x \r\n",close_steps);
		isStartReached = 0;	
		
		// TEST VALUES
		open_steps = 0x0100;
		close_steps = open_steps;
		
		PRINTF("Test Steps to open valve written in memory: %x \r\n",open_steps);
		PRINTF("Test Steps to close valve written in memory: %x \r\n",close_steps);
		
		XDOM_SetSteps(open_steps,close_steps);
		
		// Set the default positions
		steps_open_done = open_steps;
		steps_close_done = 0;
		
		PRINTF("Step stored in memory: START %x STOP %x \r\n",XDOM_GetStartSteps(),XDOM_GetStopSteps());
}
