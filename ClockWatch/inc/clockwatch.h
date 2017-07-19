#ifndef _CLOCKWATCH_H_
#define _CLOCKWATCH_H_

#define RTC_PERIOD_500ms		((32768-1)/2)
#define RTC_PERIOD_1000ms			32767

#include "BlueNRG1_rtc.h"
#include "misc.h"
#include "BlueNRG1_sysCtrl.h"
#include "hal_types.h"
#include "SDK_EVAL_Config.h"

/* Set the config date in the RTC */
void RTC_Clock_Init(RTC_DateTimeType initial_date);

/* Set the alert time */
void RTC_Clock_SetAlertTime(RTC_DateTimeType alert_date);

#endif
