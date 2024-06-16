//#ifndef __DHT11_H
//#define __DHT11_H

//void DHT11_Init(void);
//void DHT11_start(void);
//uint8_t DHT11_Get_Byte_Data();
//uint8_t Get_Tem_Humi_Data(uint8_t res[]);

//#endif




#ifndef __DHT11_H
#define __DHT11_H

#include "stm32f10x.h"  // 包含必要的头文件

void DHT11_Init(void);
void DHT11_start(void);
uint8_t DHT11_Get_Byte_Data(void);
uint8_t Get_Tem_Humi_Data(uint8_t res[]);

#endif // __DHT11_H
