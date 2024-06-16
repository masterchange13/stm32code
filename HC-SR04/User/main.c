#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
#include "HC_SR04.h"
#include "stdio.h"

int main(void)
{
	HC_SR_Init();
	
	OLED_Init();
//	OLED_ShowString(1, 2, "distance is :");
	
	float distance = 0;
	char buffer[20];
	
	while (1)
	{
		distance = get_distance();
		
		// 将浮点数转换为字符串
        sprintf(buffer, "dis: %.3f", distance);
//		OLED_ShowString(2, 14, &(char)distance);
		OLED_ShowString(1, 2, buffer);
		
		Delay_ms(2);
	}
}
