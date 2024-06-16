#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
#include "DHT11.h"
#include "stdio.h"

int main(void)
{
	
	char str[20];
	
	OLED_Init();
//	DHT11_Init();
//	DHT11_start();
	uint8_t DHT_Buffer[5];
	
//	OLED_ShowString(1, 1, "temp:");
//	OLED_ShowString(2, 1, "humi:");
	
//	DHT_Start();

	while (1)
	{
		DHT_Get_Temp_Humi_Data(DHT_Buffer);
		
//		OLED_ShowNum(1, 7, DHT_Buffer[2] + DHT_Buffer[3] / 10.0, 5);
//		
//		OLED_ShowNum(2, 7, DHT_Buffer[0] + DHT_Buffer[1] / 10.0, 5);
		
		
		sprintf(str,"Temp:%d.%d",DHT_Buffer[2],DHT_Buffer[3]);
		OLED_ShowString(1,4, str);
		sprintf(str,"Humi:%d.%d",DHT_Buffer[0],DHT_Buffer[1]);
		OLED_ShowString(2,4,str);
		
		
		Delay_ms(2000);
	}
}
