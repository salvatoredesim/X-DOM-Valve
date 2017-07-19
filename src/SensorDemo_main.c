/******************** (C) COPYRIGHT 2015 STMicroelectronics ********************
* File Name          : SensorDemo_main.c
* Author             : AMS - VMA RF Application team
* Version            : V1.1.0
* Date               : 15-January-2016
* Description        : BlueNRG-1 Sensor Demo main file 
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/
/** @addtogroup BlueNRG1_demonstrations_applications
 * BlueNRG-1 SensorDemo \see SensorDemo_main.c for documentation.
 *
 *@{
 */

/** @} */
/** \cond DOXYGEN_SHOULD_SKIP_THIS
 */
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "BlueNRG1_it.h"
#include "BlueNRG1_conf.h"
#include "SDK_EVAL_Config.h"
#include "sleep.h"
#include "OTA_btl.h"  
#include "bluenrg_interface.h"
#include "flash_mod.h"
#include "ULN2003.h"
#include "clockwatch.h"
#include "valve.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#ifndef DEBUG
#define DEBUG 1
#endif

#if DEBUG
#include <stdio.h>
#define PRINTF(...) printf(__VA_ARGS__)
#else
#define PRINTF(...)
#endif

#define BLE_SENSOR_VERSION_STRING "1.0.0" 

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
uint8_t isTMREnabled = 0;
int main(void) 
{
  uint8_t ret;

  /* System Init */
  SystemInit();
  
  /* Identify BlueNRG1 platform */
  SdkEvalIdentification();

  /* Configure I/O communication channel */
  SdkEvalComUartInit(UART_BAUDRATE);
	
  SdkEvalLedInit(LED1); //Activity led 
  SdkEvalLedInit(LED2);
  SdkEvalLedInit(LED3); //Error led 
		
  PRINTF("X-DOM Valve DEBUG Monitor \r\n"); 
  PRINTF("---------------------------------------------------------- \r\n"); 
	
	//WriteTestConfiguration();
	
	PRINTF("Initializing Valve Motor... \r\n"); 
	ULN2003_Init();

  PRINTF("Valve Motor initialized. \r\n"); 
	
	//Valve_APP();
	
  /* BlueNRG-1 stack init */
  //uint8_t bdaddr[] = {0x12, 0x34, 0x00, 0xE1, 0x80, 0x02};
  //BlueNRG_Interface_Init(bdaddr);
	/*
	RTC_DateTimeType date;
	
	date.Second = 0;
	date.Minute = 0;
	date.Hour = 12;
	date.WeekDay = 1;
	date.MonthDay = 1;
	date.Month = 1;
	date.Year = 2014;
	
	
	RTC_Clock_Init(date);
	
	RTC_DateTimeType dateMatch;
	
	dateMatch.Hour = 12;
	dateMatch.Minute = 0;
	dateMatch.Second = 10;
	dateMatch.WeekDay = 1;
	dateMatch.MonthDay = 1;
	dateMatch.Month = 1;
	dateMatch.Year = 2014;
	
	RTC_Clock_SetAlertTime(dateMatch);
	*/

	//FLASH_EraseAddress(0x10055000);
	//FLASH_ProgramWord(0x10055000,0x80CAF0A1);
	//FLASH_ProgramWord(0x10055004,0xC1AFE180);
	//FLASH_MOD_WriteByte(0x1005000, 0xFC);
	//FLASH_MOD_WriteByte(0x1005001, 0xFC);
	//FLASH_MOD_WriteByte(0x1005006, 0xCA);
	//FLASH_ProgramWord(0x1005A000,0x000000D0);
  /* Application demo Led Init */
  SdkEvalLedOn(LED1);
  SdkEvalLedOff(LED3);

	
  /* Sensor Device Init */
  //ret = Sensor_DeviceInit();
  //if (ret != BLE_STATUS_SUCCESS) {
    //SdkEvalLedOn(LED3);
    //while(1);
  //}
 
#if ST_USE_OTA_SERVICE_MANAGER_APPLICATION
  /* Initialize the button */
  SdkEvalPushButtonInit(BUTTON_1); 
#endif /* ST_USE_OTA_SERVICE_MANAGER_APPLICATION */
  while(1)
  {
		Valve_APP();
    /* BLE Stack Tick */
    //BTLE_StackTick();

    /* Application Tick */
    //APP_Tick();
    
    /* Power Save management */
    //BlueNRG_Sleep(SLEEPMODE_WAKETIMER, 0, 0, 0);
		
#if ST_OTA_FIRMWARE_UPGRADE_SUPPORT
    /* Check if the OTA firmware upgrade session has been completed */
    if (OTA_Tick() == 1)
    {
      /* Jump to the new application */
      OTA_Jump_To_New_Application();
    }
#endif /* ST_OTA_FIRMWARE_UPGRADE_SUPPORT */

#if ST_USE_OTA_SERVICE_MANAGER_APPLICATION
    if (SdkEvalPushButtonGetState(BUTTON_1) == RESET)
    {
      OTA_Jump_To_Service_Manager_Application();
    }
#endif /* ST_USE_OTA_SERVICE_MANAGER_APPLICATION */
  }/* while (1) */
}

#ifdef USE_FULL_ASSERT
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    
    /* Infinite loop */
    while (1)
    {}
}
#endif

/******************* (C) COPYRIGHT 2015 STMicroelectronics *****END OF FILE****/
/** \endcond
 */
