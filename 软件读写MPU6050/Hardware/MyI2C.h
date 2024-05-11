#ifndef __MYI2C_H
#define __MYI2C_H

void MyI2C_W_SCL(uint8_t BitValue);
void MyI2C_W_SDA(uint8_t BitValue);
uint8_t MyI2C_R_SDA(void);
void MyI2C_Init(void); // 初始化I2C总线
void MyI2C_Start(void); // 发送I2C起始信号
void MyI2C_Stop(void); // 发送I2C停止信号
void MyI2C_SendByte(uint8_t Byte); // 发送一个字节数据
uint8_t MyI2C_ReceiveByte(void); // 读取一个字节数据
void MyI2C_SendAck(uint8_t Byte); // 发送一个字节数据
uint8_t MyI2C_ReceiveAck(void); // 读取一个字节数据


#endif
