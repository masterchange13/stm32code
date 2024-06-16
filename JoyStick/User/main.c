#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
#include "JoyStick.h"

int main(void)
{
	
	LED_Init();
	LED1_ON();
	
	OLED_Init();
	OLED_ShowString(1, 1, "x:");
	OLED_ShowString(2, 1, "y:");
	
	while (1)
	{
		uint16_t dataX = HW504_R_X();
		uint16_t dataY = HW504_R_Y();
		
		OLED_ShowNum(1, 5, dataX, 2);
		OLED_ShowNum(2, 5, dataY, 2);
		
		if(HW504_R_SW()){
			OLED_ShowString(3, 1, "squeeze");
		}
	}
}
