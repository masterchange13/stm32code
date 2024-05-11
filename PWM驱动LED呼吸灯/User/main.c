#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
#include "PWM.h"

uint8_t i;

int main(void)
{	
	OLED_Init();
	PWM_Init();
	
	while (1)
	{
		for(int i = 0; i < 100; ++i)
		{
			PWM_SetCompare1(i);
			Delay_ms(20);
		}
		for(int i = 100; i >= 0; --i)
		{
			PWM_SetCompare1(i);
			Delay_ms(20);
		}
	}
}
