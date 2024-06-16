#include "stm32f10x.h"                  // Device header
#include "AD.h"
#include "OLED.h"
#include "Delay.h"
#include "Key.h"


void HW504_Init()
{
	AD_Init();
	RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	
}

uint8_t HW504_R_SW()
{
	GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12);
	
}

uint16_t HW504_R_X()
{
	uint16_t DataX = AD_GetValue(ADC_Channel_0);
	return DataX;
	
}

uint16_t HW504_R_Y()
{
	uint16_t DataY = AD_GetValue(ADC_Channel_1);
	return DataY;
	
}


