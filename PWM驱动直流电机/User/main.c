#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"

uint8_t KeyNum;
int8_t speed;
 
int main(void)
{	
	OLED_Init();
	Motor_Init();
	
//	Motor_SetSpeed(50); 
	OLED_ShowString(1, 1, "speed:");
	
	while (1)
	{
		KeyNum = Key_GetNum();
		if(KeyNum == 1)
		{
			speed += 20;
			if(speed > 100){
				speed = -100;
			}
		}
		Motor_SetSpeed(speed);
		OLED_ShowSignedNum(1, 7, speed, 3);
	}
}
