#ifndef __DHT11_H__
#define __DHT11_H__

#include "main.h"

#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned int	

// 数据引脚
#define DATA_SET() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)
#define DATA_RESET() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)

#define DATA_READ() HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4);

#define DATA_Pin     	GPIO_PIN_7
#define DATA_GPIO_Port 	GPIOA

typedef struct{
	u8 DATA[5];
	u8 index;
	u8 temp;
	u8 humidity;
}DHT11_DATA;

extern DHT11_DATA DHT11_data;

void DHT11_Task(void);

#endif
