#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"

int main(void)
{
	OLED_Init();
	AD_Init();

	OLED_ShowString(1, 1, "ADC0:");
	OLED_ShowString(2, 1, "ADC1:");
	OLED_ShowString(3, 1, "ADC2:");
	OLED_ShowString(4, 1, "ADC3:");
	
	while (1)
	{
		// 单次转换需要使用，循环扫描+连续不需要使用
		// AD_GetValue(); 

		OLED_ShowNum(1, 6, AD_Value[0], 4);
		OLED_ShowNum(2, 6, AD_Value[1], 4);
		OLED_ShowNum(3, 6, AD_Value[2], 4);
		OLED_ShowNum(4, 6, AD_Value[3], 4);

		Delay_ms(100);
	}
}
