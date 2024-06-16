#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
#include "DHT11.h"

int main(void)
{
	
	OLED_Init();
	DHT11_Init();
	DHT11_start();
	uint8_t res[5];
	
	OLED_ShowString(1, 1, "temp:");
	OLED_ShowString(2, 1, "humi:");

	while (1)
	{
		Get_Tem_Humi_Data(res);
		
		OLED_ShowNum(1, 7, res[2] + res[3] / 10.0, 5);
		
		OLED_ShowNum(2, 7, res[0] + res[1] / 10.0, 5);
		
		
		Delay_ms(2);
	}
}
