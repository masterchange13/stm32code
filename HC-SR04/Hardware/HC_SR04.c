#include "stm32f10x.h"  
#include "HC_SR04.h"
#include "Delay.h"
#include "Timer.h"

void HC_SR_Init(void)
{
	init_timer();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct_Trig;
	GPIO_InitStruct_Trig.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct_Trig.GPIO_Pin = GPIO_Pin_Trig;
	GPIO_InitStruct_Trig.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitTypeDef GPIO_InitStruct_Echo;
	GPIO_InitStruct_Echo.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct_Echo.GPIO_Pin = GPIO_Pin_Echo;
	GPIO_InitStruct_Echo.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &GPIO_InitStruct_Trig);
	GPIO_Init(GPIOB, &GPIO_InitStruct_Echo);
	
}

float get_distance(void)
{
	// start
	GPIO_SetBits(GPIO_Port, GPIO_Pin_Trig);
	Delay_us(15);
	GPIO_ResetBits(GPIO_Port, GPIO_Pin_Trig);
	
	// delay to sub inner impact
	Delay_ms(10);
	
	Timer_on();
	while(GPIO_ReadInputDataBit(GPIO_Port, GPIO_Pin_Echo));
	Timer_off();
	
	// get distance
	float t = Timer_Get_Time();
	float c = 340.0;
	float distance = t * c / 2;
	
	return distance;
}
