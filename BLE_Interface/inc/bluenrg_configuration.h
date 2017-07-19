#ifndef _SENSORDEMO_CONFIG_H_
#define _SENSORDEMO_CONFIG_H_

#include "compiler.h"

/* This file contains all the information needed to init the BlueNRG-1 stack. 
 * These constants and variables are used from the BlueNRG-1 stack to reserve RAM and FLASH 
 * according the application requests
 */

#ifndef NULL
  #define NULL      (void *) 0
#endif

/* Default number of link */
#define MIN_NUM_LINK            1
/* Default number of GAP and GATT services */
#define DEFAULT_NUM_GATT_SERVICES   2
/* Default number of GAP and GATT attributes */
#define DEFAULT_NUM_GATT_ATTRIBUTES 9

#if defined (ST_OTA_LOWER_APPLICATION) || defined (ST_OTA_HIGHER_APPLICATION)
/* Number of services requests from the Sensor demo */
#define NUM_APP_GATT_SERVICES (2 + 1) /* 2 Sensor services + 1 OTA service */

/* Number of attributes requests from the chat demo */
#define NUM_APP_GATT_ATTRIBUTES (15 + 9) /* 15 attributes x BLE Sensor demo services characteristics + 9 for OTA Service characteristics */

#else /* NO OTA Service is required */

/* Number of services requests from the sensor demo */
#define NUM_APP_GATT_SERVICES 2

/* Number of attributes requests from the sensor demo */
#define NUM_APP_GATT_ATTRIBUTES 15
#endif

/* Number of links needed for the demo: 1
 * Only 1 the default
 */
#define NUM_LINKS               (MIN_NUM_LINK)

/* Number of GATT attributes needed for the sensor demo. */
#define NUM_GATT_ATTRIBUTES     (DEFAULT_NUM_GATT_ATTRIBUTES + NUM_APP_GATT_ATTRIBUTES)

/* Number of GATT services needed for the sensor demo. */
#define NUM_GATT_SERVICES       (DEFAULT_NUM_GATT_SERVICES + NUM_APP_GATT_SERVICES)

/* Array size for the attribute value for OTA service */
#if defined (ST_OTA_LOWER_APPLICATION) || defined (ST_OTA_HIGHER_APPLICATION)
#define OTA_ATT_VALUE_ARRAY_SIZE  (119)    /* OTA service is used: 4 characteristics (1 notify property) */
#else
#define OTA_ATT_VALUE_ARRAY_SIZE (0)       /* No OTA service is used */
#endif

/* Array size for the attribute value */
#ifndef SENSOR_EMULATION
#define ATT_VALUE_ARRAY_SIZE    (43 + 106  + OTA_ATT_VALUE_ARRAY_SIZE) //(GATT + GAP) = 43 (Device Name: BlueNRG) + Acceleration (Acceleration (27) + Free Fall (21) characteristics) +  Environmental Sensor (Temperature (28), Pressure (29)  characteristics)  Services
#else
#define ATT_VALUE_ARRAY_SIZE    (43 + 106 + 28 + OTA_ATT_VALUE_ARRAY_SIZE) //(GATT + GAP) = 43 (Device Name: BlueNRG) + Acceleration (Acceleration (27) + Free Fall (21) characteristics) +  Environmental Sensor (Temperature (28) , Pressure (29), Humidity (28) characteristics)  Services
#endif 

/* Flash security database size */
#define FLASH_SEC_DB_SIZE       (0x400)

/* Flash server database size */
#define FLASH_SERVER_DB_SIZE    (0x400)

/* Maximum duration of the connection event */
#define MAX_CONN_EVENT_LENGTH 0xFFFFFFFF

/* Sleep clock accuracy in Slave mode 100 ppm */
#define SLAVE_SLEEP_CLOCK_ACCURACY 100

/* Sleep clock accuracy in Master mode 100 ppm */
#define MASTER_SLEEP_CLOCK_ACCURACY 3

/* Low Speed Oscillator source */
#if (LS_SOURCE == LS_SOURCE_INTERNAL_RO)
#define LOW_SPEED_SOURCE  1 // Internal RO
#else
#define LOW_SPEED_SOURCE  0 // External 32 KHz
#endif

/* High Speed start up time */
#define HS_STARTUP_TIME 0x0107 // 642 us

/* Low level hardware configuration data for the device */
#define CONFIG_TABLE            \
{                               \
  NULL,          \
  MAX_CONN_EVENT_LENGTH,        \
  SLAVE_SLEEP_CLOCK_ACCURACY,   \
  MASTER_SLEEP_CLOCK_ACCURACY,  \
  LOW_SPEED_SOURCE,             \
  HS_STARTUP_TIME               \
}

#define  ADV_INTERVAL_MIN_MS  1000
#define  ADV_INTERVAL_MAX_MS  1200


#endif // _SENSORDEMO_CONFIG_H_
