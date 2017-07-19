#ifndef _VALVE_H_
#define _VALVE_H_

#include "valve_conf.h"
#include "bluenrg_interface.h"
#include "stdint.h"
#include "ULN2003.h"

typedef enum{
	INITIAL_CALIBRATION,
	READ_CONFIGURATION,
	NOT_CONFIGURED,
	PERIPHERAL,
	AUTHONOMOUS,
	IDLE
}ValveStatus;

typedef enum{
	UNKNOWN_ROLE,
	CONTROLLED_ROLE,
	AUTHONOMOUS_ROLE
}ValveRole;

/* Calibrate the valve */
void Calibrate(void);

/* FSM Valve */
void Valve_APP(void);

#endif
