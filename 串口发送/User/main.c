#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"

int main(void)
{
	OLED_Init();

	Serial_Init();

	// 传输字节数据
	// Serial_SendByte(0x41);

	// 传输数组
	// uint8_t MyArr[] = {0x41, 0x42, 0x43, 0x44};
	// Serial_SendArr(MyArr, 4);

	// 传输字符串
	// Serial_SendString("Hello World!");

	// 发送数字
	// Serial_SendNumber(12345, 5);

	// printf
	// printf("num = %d\n", 666);

	// 把要输出的东西送到String, 把String打印出来
	// char String[100];
	// sprintf(String, "num = %d\n", 666);
	// Serial_SendString(String);

	Serial_Printf("num = %d\n", 666);

	while (1)
	{
		
	}
}
