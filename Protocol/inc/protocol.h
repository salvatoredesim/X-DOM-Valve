#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#include "stdint.h"
#include "valve_conf.h"
#include "ULN2003.h"
#include "ble_status.h"
#include "bluenrg1_api.h"

/* Define source/destinations of the message */
#define PARENT				0x00
#define APP						0x01

/* Define main message types */
#define RESET 				0x00
#define	INIT_DATA			0x01
#define	OPEN					0x02
#define CLOSE					0x03
#define	STOP_CMD			0x04

/* Define subtypes */
#define STEP					0x01
#define FULL					0x02
#define QUARTER				0x03
#define HALF					0x04


/* Lets define a TLV structure */
/* TAGS */
#define	NAME_VALVE		0x00
#define ZONE_NAME			0x01
#define	TIME_CLOCK		0x02

/* Parse the received message */
void ParseMessage(uint8_t Attr_Data[], uint8_t Attr_Data_Length);

void XDOM_Configure(uint8_t Payload_Data[], uint8_t size);

void XDOM_Open_Close(uint8_t Payload_Data[], uint8_t size,uint8_t command, uint8_t orientation);

void XDOM_Open_Close_Steps(uint8_t command,uint8_t orientation, uint8_t steps_needed);

void XDOM_LoadStatus(void);

#endif
