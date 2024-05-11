#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
#include "Timer.h"

uint16_t Num = 0;

int main(void)
{

	OLED_Init();
	Timer_Init();
	
	OLED_ShowString(1, 3, "HelloWorld!");

	while (1)
	{
		OLED_ShowNum(2, 1, Num, 5);
		OLED_ShowNum(3, 1, TIM_GetCounter(TIM2), 5);
	}
}

void TIM2_IRQHandler(void)
{
	if( TIM_GetITStatus(TIM2, TIM_IT_Update) == SET ){
		Num++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
