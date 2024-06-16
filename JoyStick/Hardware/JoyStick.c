#include "stm32f10x.h"
#include "JoyStick.h"
#include "AD.h"

/**************
ӽޅlޓú

VRX - A0

VRY - A1

SW - PB12

3.3V- 3.3V

GND - GND

by: ǕǕͨͨ

***************/


void JoyStick_Init(void)
{
	AD_Init();
	
	RCC_APB2PeriphClockCmd(GPIO_Time, ENABLE);
	
//	// init X
//	GPIO_InitTypeDef GPIO_InitStructX;
//	GPIO_InitStructX.GPIO_Mode = GPIO_Mode_IPU;
//	GPIO_InitStructX.GPIO_Pin = GPIO_PinX;
//	GPIO_InitStructX.GPIO_Speed = GPIO_Speed_50MHz;
//	
//	// init Y
//	GPIO_InitTypeDef GPIO_InitStructY;
//	GPIO_InitStructY.GPIO_Mode = GPIO_Mode_IPU;
//	GPIO_InitStructY.GPIO_Pin = GPIO_PinY;
//	GPIO_InitStructY.GPIO_Speed = GPIO_Speed_50MHz;
//	
//	GPIO_Init(GPIO_Port, &GPIO_InitStructX);
//	GPIO_Init(GPIO_Port, &GPIO_InitStructY);
	
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
}


uint8_t HW504_R_SW()
{
	uint8_t res = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12);
	return res;
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

