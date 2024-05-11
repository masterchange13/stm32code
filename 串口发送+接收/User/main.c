#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

uint8_t RxData;

int main(void)
{
	OLED_Init();

	Serial_Init();

	while (1)
	{
		// 使用查询接收
		// if(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET){
		// 	RxData = USART_ReceiveData(USART1);
		// 	OLED_ShowHexNum(1, 1, RxData, 2);
		// }


		// 使用中断
		if(Serial_GetRxFlag() == 1)
		{
			RxData = Serial_GetRxData();
			Serial_SendByte(RxData);
			OLED_ShowHexNum(1, 1, RxData, 2);
		}
	}
}
