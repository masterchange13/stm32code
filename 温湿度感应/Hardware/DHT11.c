//#include "stm32f10x.h"
//#include "Delay.h"
//#include "DHT11.h"

//#define DHT11_Pin GPIO_Pin_15

//void DHT11_Init(void)
//{
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
//	
//	GPIO_InitTypeDef GPIO_InitStruect = {0};
//	GPIO_InitStruect.GPIO_Pin = DHT11_Pin;
//	GPIO_InitStruect.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStruect.GPIO_Speed = GPIO_Speed_50MHz;
//	
//	GPIO_Init(GPIOB, &GPIO_InitStruect);
//}

//void DHT11_start(void)
//{
//	// 拉低电平启动
//	GPIO_ResetBits(GPIOB, DHT11_Pin);		//输出20ms低电平后拉高
//	Delay_ms(20);
//	
//	GPIO_SetBits(GPIOB, DHT11_Pin);
//	Delay_us(20);

//}

//// receive data
//// 接下来开始传输信号
//uint8_t DHT11_Get_Byte_Data()
//{
//	uint8_t temp;
//	while(!GPIO_ReadInputDataBit(GPIOB, DHT11_Pin));
//	Delay_us(28);
////	GPIO_ResetBits(GPIOB, DHT11_Pin);
////	Delay_us(83);
////	
////	GPIO_SetBits(GPIOB, DHT11_Pin);
////	Delay_us(87);
//	
//	GPIO_ReadInputDataBit(GPIOB,DHT11_Pin) ? (temp |= 0x01) : (temp &= ~0x01);
//	while(GPIO_ReadInputDataBit(GPIOB,DHT11_Pin));
//	
//	return temp;
//}

//uint8_t Get_Tem_Humi_Data(uint8_t res[])
//{
////	uint8_t res[5];
//	
//	DHT11_start();
//	
//	res[0] = DHT11_Get_Byte_Data();
//	res[1] = DHT11_Get_Byte_Data();
//	res[2] = DHT11_Get_Byte_Data();
//	res[3] = DHT11_Get_Byte_Data();
//	res[4] = DHT11_Get_Byte_Data();
//	
//	if(res[0] + res[1] + res[2] + res[3] == res[4]){
//		return 1;
//	}else{
//		return 0;
//	}
//}








#include "DHT11.h"
#include "Delay.h"

#define DHT11_Pin GPIO_Pin_15
#define DHT11_PORT GPIOB

void DHT11_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.GPIO_Pin = DHT11_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(DHT11_PORT, &GPIO_InitStruct);
}

void DHT11_start(void) {
    GPIO_ResetBits(DHT11_PORT, DHT11_Pin);  // 拉低电平启动
    Delay_ms(18);                           // 至少18ms低电平
    GPIO_SetBits(DHT11_PORT, DHT11_Pin);    // 拉高电平
    Delay_us(30);                           // 20-40us高电平
}

uint8_t DHT11_ReadBit(void) {
    uint8_t bit = 0;
    while (!GPIO_ReadInputDataBit(DHT11_PORT, DHT11_Pin));  // 等待高电平
    Delay_us(30);  // 等待30us
    if (GPIO_ReadInputDataBit(DHT11_PORT, DHT11_Pin)) {
        bit = 1;
    }
    while (GPIO_ReadInputDataBit(DHT11_PORT, DHT11_Pin));  // 等待低电平
    return bit;
}

uint8_t DHT11_Get_Byte_Data(void) {
    uint8_t i, byte = 0;
    for (i = 0; i < 8; i++) {
        byte <<= 1;
        byte |= DHT11_ReadBit();
    }
    return byte;
}

uint8_t Get_Tem_Humi_Data(uint8_t res[]) {
    uint8_t data[5] = {0};
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // 启动信号
    // DHT11_start();

    // 配置为输入模式
    GPIO_InitStruct.GPIO_Pin = DHT11_Pin;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(DHT11_PORT, &GPIO_InitStruct);

    // 等待DHT11的响应信号
    Delay_us(80);  // 等待80us
    if (GPIO_ReadInputDataBit(DHT11_PORT, DHT11_Pin) != 0) return 1;
    Delay_us(80);  // 等待80us
    if (GPIO_ReadInputDataBit(DHT11_PORT, DHT11_Pin) != 1) return 1;
    Delay_us(80);  // 等待80us

    // 读取数据
    for (int i = 0; i < 5; i++) {
        data[i] = DHT11_Get_Byte_Data();
    }

    // 校验数据
    if (data[0] + data[1] + data[2] + data[3] != data[4]) return 1;

    // 提取温度和湿度数据
    res[0] = data[0];  // 湿度整数部分
    res[1] = data[1];  // 湿度小数部分
    res[2] = data[2];  // 温度整数部分
    res[3] = data[3];  // 温度小数部分
    res[4] = data[4];  // 校验和

    return 0;
}
