/*
 * ULN2003.h
 *
 *  Created on: 09 giu 2017
 *      Author: Salvatore
 */

#ifndef ULN2003_H_
#define ULN2003_H_

#include "BlueNRG1.h"
#include "BlueNRG1_sysCtrl.h"
#include "BlueNRG1_gpio.h"

#define IN1 GPIO_Pin_3
#define IN2 GPIO_Pin_2
#define IN3 GPIO_Pin_0
#define IN4 GPIO_Pin_1

#define INT_START_PIN	GPIO_Pin_12
#define INT_STOP_PIN 	GPIO_Pin_13

enum{
  CLOCKWISE = 0,
  ANTICLOCKWISE = 1
};

void ULN2003_Init(void);
/* Test sequence */
void ULN2003_TestSequence(uint8_t spin, uint8_t type_rotation);

/* Make a step in clockwise or anti clockwise orientation */
void ULN2003_STEP(uint8_t type_rotation);

void SdkDelayMs(volatile uint32_t lTimeMs);
#endif /* ULN2003_H_ */
