#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"

uint16_t ADValue;
float Volage;

int main(void)
{
	OLED_Init();
	AD_Init();

	OLED_ShowString(1, 1, "ADC:");
	OLED_ShowString(2, 1, "Volatge:0.00V");
	
	while (1)
	{
		ADValue = AD_GetValue();
		Volage = (float)ADValue * 3.3 / 4095;
		OLED_ShowNum(1, 9, ADValue, 4);
		OLED_ShowNum(2, 9, Volage, 1);
		OLED_ShowNum(2, 11, (uint16_t)(Volage * 100) % 100, 2);

		Delay_ms(100);
	}
}
