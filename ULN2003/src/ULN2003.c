/*
 * ULN2003.c
 *
 *  Created on: 09 giu 2017
 *      Author: Salvatore
 */
#include "ULN2003.h"
#include "clock.h"
#include "misc.h"

void ULN2003_Init(void){
	Clock_Init();
	
	GPIO_InitType GPIO_InitStructure;

	/* Enable the GPIO Clock */
	SysCtrl_PeripheralClockCmd(CLOCK_PERIPH_GPIO, ENABLE);

	/* Configure the Valve pins */
	GPIO_InitStructure.GPIO_Pin = IN3 | IN2 | IN1
			| GPIO_Pin_6 | IN4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Output;
	GPIO_InitStructure.GPIO_Pull = ENABLE;
	GPIO_InitStructure.GPIO_HighPwr = ENABLE;
	GPIO_Init(&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = INT_START_PIN | INT_STOP_PIN ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Input;
	GPIO_InitStructure.GPIO_Pull = DISABLE;
	GPIO_InitStructure.GPIO_HighPwr = DISABLE;
	GPIO_Init(&GPIO_InitStructure);
	
  GPIO_EXTIConfigType GPIO_EXTIStructure;
  NVIC_InitType NVIC_InitStructure;

  /* Set the GPIO interrupt priority and enable it */
  NVIC_InitStructure.NVIC_IRQChannel = GPIO_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = LOW_PRIORITY;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  /* Configures EXTI line */
  GPIO_EXTIStructure.GPIO_Pin = INT_START_PIN;
  GPIO_EXTIStructure.GPIO_IrqSense = GPIO_IrqSense_Edge;
  GPIO_EXTIStructure.GPIO_Event = GPIO_Event_High;
  GPIO_EXTIConfig(&GPIO_EXTIStructure);
	
  GPIO_EXTIStructure.GPIO_Pin = INT_STOP_PIN;
  GPIO_EXTIStructure.GPIO_IrqSense = GPIO_IrqSense_Edge;
  GPIO_EXTIStructure.GPIO_Event = GPIO_Event_Low;
  GPIO_EXTIConfig(&GPIO_EXTIStructure);

  /* Clear pending interrupt */
  GPIO_ClearITPendingBit(INT_START_PIN);
  GPIO_ClearITPendingBit(INT_STOP_PIN );
  //GPIO_ClearITPendingBit(INT_STOP_PIN);
  
  /* Enable the interrupt */
  GPIO_EXTICmd(INT_START_PIN, ENABLE);
  GPIO_EXTICmd(INT_STOP_PIN, ENABLE);
  //GPIO_EXTICmd(INT_STOP_PIN, ENABLE);
}

void ULN2003_TestSequence(uint8_t spin, uint8_t type_rotation){
  for(int i = 0; i < spin; i++){
      for(int j = 0; j < 64; j++){
        ULN2003_STEP(type_rotation);
      }
  }

  GPIO_WriteBit(IN1, Bit_RESET);
  GPIO_WriteBit(IN2, Bit_RESET);
  GPIO_WriteBit(IN3, Bit_RESET);
  GPIO_WriteBit(IN4, Bit_RESET);

}

void ULN2003_StopAll(){
  GPIO_WriteBit(IN1, Bit_RESET);
  GPIO_WriteBit(IN2, Bit_RESET);
  GPIO_WriteBit(IN3, Bit_RESET);
  GPIO_WriteBit(IN4, Bit_RESET);
}

void ULN2003_STEP(uint8_t type_rotation){
	for (int i = 0; i < 8; i++) {
		switch (type_rotation) {
		case ANTICLOCKWISE: {
			GPIO_WriteBit(IN1, Bit_RESET);
			GPIO_WriteBit(IN2, Bit_RESET);
			GPIO_WriteBit(IN3, Bit_RESET);
			GPIO_WriteBit(IN4, Bit_SET);

			Clock_Wait(1);

			GPIO_WriteBit(IN1, Bit_RESET);
			GPIO_WriteBit(IN2, Bit_RESET);
			GPIO_WriteBit(IN3, Bit_SET);
			GPIO_WriteBit(IN4, Bit_SET);

			Clock_Wait(1);

			GPIO_WriteBit(IN1, Bit_RESET);
			GPIO_WriteBit(IN2, Bit_RESET);
			GPIO_WriteBit(IN3, Bit_SET);
			GPIO_WriteBit(IN4, Bit_RESET);

			Clock_Wait(1);

			GPIO_WriteBit(IN1, Bit_RESET);
			GPIO_WriteBit(IN2, Bit_SET);
			GPIO_WriteBit(IN3, Bit_SET);
			GPIO_WriteBit(IN4, Bit_RESET);

			Clock_Wait(1);

			GPIO_WriteBit(IN1, Bit_RESET);
			GPIO_WriteBit(IN2, Bit_SET);
			GPIO_WriteBit(IN3, Bit_RESET);
			GPIO_WriteBit(IN4, Bit_RESET);

			Clock_Wait(1);

			GPIO_WriteBit(IN1, Bit_SET);
			GPIO_WriteBit(IN2, Bit_SET);
			GPIO_WriteBit(IN3, Bit_RESET);
			GPIO_WriteBit(IN4, Bit_RESET);

			Clock_Wait(1);

			GPIO_WriteBit(IN1, Bit_SET);
			GPIO_WriteBit(IN2, Bit_RESET);
			GPIO_WriteBit(IN3, Bit_RESET);
			GPIO_WriteBit(IN4, Bit_RESET);

			Clock_Wait(1);

			GPIO_WriteBit(IN1, Bit_SET);
			GPIO_WriteBit(IN2, Bit_RESET);
			GPIO_WriteBit(IN3, Bit_RESET);
			GPIO_WriteBit(IN4, Bit_SET);

			Clock_Wait(1);
		}
			break;
		case CLOCKWISE:

		{
			GPIO_WriteBit(IN1, Bit_SET);
			GPIO_WriteBit(IN2, Bit_RESET);
			GPIO_WriteBit(IN3, Bit_RESET);
			GPIO_WriteBit(IN4, Bit_RESET);

			Clock_Wait(1);

			GPIO_WriteBit(IN1, Bit_SET);
			GPIO_WriteBit(IN2, Bit_SET);
			GPIO_WriteBit(IN3, Bit_RESET);
			GPIO_WriteBit(IN4, Bit_RESET);

			Clock_Wait(1);

			GPIO_WriteBit(IN1, Bit_RESET);
			GPIO_WriteBit(IN2, Bit_SET);
			GPIO_WriteBit(IN3, Bit_RESET);
			GPIO_WriteBit(IN4, Bit_RESET);

			Clock_Wait(1);

			GPIO_WriteBit(IN1, Bit_RESET);
			GPIO_WriteBit(IN2, Bit_SET);
			GPIO_WriteBit(IN3, Bit_SET);
			GPIO_WriteBit(IN4, Bit_RESET);

			Clock_Wait(1);

			GPIO_WriteBit(IN1, Bit_RESET);
			GPIO_WriteBit(IN2, Bit_RESET);
			GPIO_WriteBit(IN3, Bit_SET);
			GPIO_WriteBit(IN4, Bit_RESET);

			Clock_Wait(1);

			GPIO_WriteBit(IN1, Bit_RESET);
			GPIO_WriteBit(IN2, Bit_RESET);
			GPIO_WriteBit(IN3, Bit_SET);
			GPIO_WriteBit(IN4, Bit_SET);

			Clock_Wait(1);

			GPIO_WriteBit(IN1, Bit_RESET);
			GPIO_WriteBit(IN2, Bit_RESET);
			GPIO_WriteBit(IN3, Bit_RESET);
			GPIO_WriteBit(IN4, Bit_SET);

			Clock_Wait(1);

			GPIO_WriteBit(IN1, Bit_SET);
			GPIO_WriteBit(IN2, Bit_RESET);
			GPIO_WriteBit(IN3, Bit_RESET);
			GPIO_WriteBit(IN4, Bit_SET);

			Clock_Wait(1);
		}
			break;
		default:
			break;
		}
	}
}
