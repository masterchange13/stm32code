#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "HW504.h"

uint16_t X, Y;
uint8_t SW;

int main(void)
{
	OLED_Init();
	HW504_Init();
	OLED_ShowString(1, 1, "X:");
	OLED_ShowString(2, 1, "Y:");
	OLED_ShowString(3, 1, "SW:");
	
	while (1)
	{
		X = HW504_R_X();
		SW = HW504_R_SW();
		Y = HW504_R_Y();
		
		OLED_ShowNum(1,3, X, 4);
		OLED_ShowNum(2,3, Y, 4);
		OLED_ShowNum(3,5, SW, 1);
		
		Delay_ms(100);
		
	}
}
