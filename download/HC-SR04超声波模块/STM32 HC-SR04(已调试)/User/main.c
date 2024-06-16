#include "stm32f10x.h"                  // Device header
#include "TIMER.H"
#include "HC-SR04.H"
#include "OLED.H"
#include "Delay.h"

float L;

int main(void)
{
	OLED_Init();
	HC_SR04_Init();
	
	OLED_ShowString(1,1,"Length:00.0");

	while(1)
  {
		L=HC_SR04_GetLenght();
		OLED_ShowNum(1,8,(int)L,2); //整数
		OLED_ShowNum(1,11,(int)(L*10)%10,1);//取出小数一位11.15
		Delay_ms(500);

	
	}
}
