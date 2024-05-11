#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
#include "CountSensor.h"

int main(void)
{
	
	OLED_Init();
	CountSensor_Init();
	
	OLED_ShowString(1, 3, "HelloWorld!");
	OLED_ShowString(2, 1, "Count:");
	
	while (1)
	{
		OLED_ShowNum(2, 7, CountSensor_Get(), 5 );
	}
}
