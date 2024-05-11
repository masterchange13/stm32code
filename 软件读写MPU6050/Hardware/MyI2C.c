#include "stm32f10x.h"
#include "Delay.h"

void MyI2C_W_SCL(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_10, BitValue);
	Delay_us(10);
}

void MyI2C_W_SDA(uint8_t BitValue)
{
	GPIO_WriteBit(GPIOB, GPIO_Pin_11, BitValue);
	Delay_us(10);
}

uint8_t MyI2C_R_SDA(void)
{
	uint8_t BitValue;
	BitValue = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11);
	Delay_us(10);
}

void MyI2C_Init(void) // 初始化I2C总线
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_SetBits(GPIOA, GPIO_Pin_10 | GPIO_Pin_11);
}

void MyI2C_Start(void) // 发送I2C起始信号
{
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(0);
}

void MyI2C_Stop(void) // 发送I2C停止信号
{
	MyI2C_W_SDA(0);
	MyI2C_W_SCL(1);
	MyI2C_W_SDA(1);
}

void MyI2C_SendByte(uint8_t Byte) // 发送一个字节数据
{
	for (int i = 0; i < 8; i++)
	{
		/* code */
		MyI2C_W_SDA(Byte & 0x80 >> i);
		MyI2C_W_SCL(1);
		MyI2C_W_SCL(0);
	}
}

uint8_t MyI2C_ReceiveByte(void) // 读取一个字节数据
{
	uint8_t Byte = 0;
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	for (int i = 0; i < 8; i++)
	{
		MyI2C_W_SCL(1);
		/* code */
		if (MyI2C_R_SDA() == 1)
		{
			/* code */
			Byte |= 0x80 >> i;
		}
		MyI2C_W_SCL(0);
	}
	return Byte;
}

void MyI2C_SendAck(uint8_t Byte) // 发送一个字节数据
{
	/* code */
	MyI2C_W_SDA(Byte & 0x80);
	MyI2C_W_SCL(1);
	MyI2C_W_SCL(0);
}

uint8_t MyI2C_ReceiveAck(void) // 读取一个字节数据
{
	uint8_t Byte = 0;
	MyI2C_W_SDA(1);
	MyI2C_W_SCL(1);
	/* code */
	if (MyI2C_R_SDA() == 1)
	{
		/* code */
		Byte |= 0x80;
	}
	MyI2C_W_SCL(0);
	return Byte;
}