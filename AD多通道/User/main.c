#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"

uint16_t AD0, AD1, AD2, AD3;

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
		AD0 = AD_GetValue(ADC_Channel_0);
		AD1 = AD_GetValue(ADC_Channel_1);
		AD2 = AD_GetValue(ADC_Channel_2);
		AD3 = AD_GetValue(ADC_Channel_3);

		OLED_ShowNum(1, 6, AD0, 4);
		OLED_ShowNum(2, 6, AD1, 4);
		OLED_ShowNum(3, 6, AD2, 4);
		OLED_ShowNum(4, 6, AD3, 4);

		Delay_ms(100);
	}
}
