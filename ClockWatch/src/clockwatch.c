#include "clockwatch.h"

RTC_DateTimeType RTC_DateTime;
uint8_t isClockReached;

void RTC_Timer_Configuration(void)
{
  RTC_InitType RTC_Init_struct;
  NVIC_InitType NVIC_InitStructure;
	
  SysCtrl_PeripheralClockCmd(CLOCK_PERIPH_RTC, ENABLE);
	
  RTC_Init_struct.RTC_operatingMode = RTC_TIMER_PERIODIC;    /**< Periodic RTC mode */
  RTC_Init_struct.RTC_PATTERN_SIZE = 1 - 1;                  /**< Pattern size set to 1 */
  RTC_Init_struct.RTC_TLR1 = RTC_PERIOD_500ms;               /**< Enable 0.5s timer period */
  RTC_Init_struct.RTC_PATTERN1 = 0x00;                       /**< RTC_TLR1 selected for time generation */
  RTC_Init(&RTC_Init_struct);
  
  /* Enable RTC Timer interrupt*/
  RTC_IT_Config(RTC_IT_TIMER, ENABLE);
  RTC_IT_Clear(RTC_IT_TIMER);

  /** Delay between two write in RTC0->TCR register has to be
   *  at least 3 x 32k cycle + 2 CPU cycle. For that reason it
   *  is neccessary to add the delay. 
   */
  for (volatile uint16_t i=0; i<300; i++) {
    __asm("NOP");
  }
  
  /* Set the RTC_IRQn interrupt priority and enable it */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = LOW_PRIORITY;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* Enable RTC */
  RTC_Cmd(ENABLE);
}

void RTC_Clock_Init(RTC_DateTimeType initial_date){
	
	/* Start the sysTimer */
	RTC_Timer_Configuration();
	
	/* Set the initial date and time */
	RTC_DateTime.Second = initial_date.Second;
	RTC_DateTime.Minute = initial_date.Minute;
	RTC_DateTime.Hour = initial_date.Hour;
	
	RTC_DateTime.WeekDay = initial_date.WeekDay;
	RTC_DateTime.MonthDay = initial_date.MonthDay;
	RTC_DateTime.Month = initial_date.Month;
	RTC_DateTime.Year = initial_date.Year;
	
	RTC_SetTimeDate(&RTC_DateTime);
	
}

void RTC_Clock_SetAlertTime(RTC_DateTimeType alert_date){
	/* Set the alert date and time */
	RTC_DateTime.Second = alert_date.Second;
	RTC_DateTime.Minute = alert_date.Minute;
	RTC_DateTime.Hour = alert_date.Hour;
	
	RTC_DateTime.WeekDay = alert_date.WeekDay;
	RTC_DateTime.MonthDay = alert_date.MonthDay;
	RTC_DateTime.Month = alert_date.Month;
	RTC_DateTime.Year = alert_date.Year;
	
	RTC_SetMatchTimeDate(&RTC_DateTime);
	
	/* Enable interrupts */
	RTC_IT_Config(RTC_IT_CLOCKWATCH, ENABLE);
	RTC_IT_Clear(RTC_IT_CLOCKWATCH);
	
	/* Enable the watch */
	RTC_ClockwatchCmd(ENABLE);
}

void RTC_Handler(void){
		if(SET == RTC_IT_Status(RTC_IT_TIMER))
  {
    /* Clear pending interrupt flag */ 
    RTC_IT_Clear(RTC_IT_TIMER);
    
    SdkEvalLedToggle(LED3);
    
    /* Read present date and time information */
    RTC_GetTimeDate(&RTC_DateTime);
  }
  
  if(SET == RTC_IT_Status(RTC_IT_CLOCKWATCH ))
  {
    /* Clear pending interrupt flag */ 
    RTC_IT_Clear(RTC_IT_CLOCKWATCH);
    
    SdkEvalLedToggle(LED2);
		
		/* Signal that a timezone is reached and load the next phase */
		switch(isClockReached){
			case 0:
				isClockReached = 1;
				break;
			case 1:
				isClockReached = 2;
				break;
			case 2:
				isClockReached = 3;
				break;
			case 3:
				isClockReached = 0;
				break;
			default:
				break;
		}
  }
}
