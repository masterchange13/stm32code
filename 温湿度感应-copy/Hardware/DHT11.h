#ifndef __DHT11_H
#define __DHT11_H

#include "stm32f10x.h"  

#define DHT_GPIO_PORT		GPIOB
#define DHT_GPIO_PIN		GPIO_Pin_15
#define DHT_RCC_PORT		RCC_APB2Periph_GPIOB

void DHT_GPIO_Init(GPIOMode_TypeDef Mode);
uint8_t DHT_Start(void);
uint8_t DHT_Get_Temp_Humi_Data(uint8_t buffer[]);

#endif
