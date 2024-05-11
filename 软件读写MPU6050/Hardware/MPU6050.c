#include "stm32f10x.h"
#include "MyI2C.h"
#include "MPU6050_Reg.h"

#define MPU6050_ADDRESS 0xD0 // MPU6050的I2C地址

void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data){
    MyI2C_Start();
    MyI2C_SendByte(MPU6050_ADDRESS);
    MyI2C_ReceiveAck();
    MyI2C_SendByte(RegAddress);
    MyI2C_ReceiveAck();
    MyI2C_SendByte(RegAddress);
    MyI2C_ReceiveAck();
    MyI2C_Stop();
}

uint8_t MPU6050_ReadReg(uint8_t RegAddress){

    uint8_t Data;

    MyI2C_Start();
    MyI2C_SendByte(MPU6050_ADDRESS);
    MyI2C_ReceiveAck();
    MyI2C_SendByte(RegAddress);
    MyI2C_ReceiveAck();

    MyI2C_Start();
    MyI2C_SendByte(MPU6050_ADDRESS | 0x01); // 读模式
    MyI2C_ReceiveAck();
    MyI2C_ReceiveByte();    
    MyI2C_SendAck(1);
    MyI2C_Stop();

    return Data;
}

void MPU6050_Init(void){
    MyI2C_Init();
    MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01); // 解除睡眠
    MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00); // 六轴不待机
    MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09); // 采样分频10
    MPU6050_WriteReg(MPU6050_CONFIG, 0x06); // 滤波值最大
    MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18); // 陀螺仪加速度计选择最大量程
    MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18 ); 

}

void MPU6050_GetData(int16_t *Accel_X, int16_t *Accel_Y, int16_t *Accel_Z, int16_t *Gyro_X, int16_t *Gyro_Y, int16_t *Gyro_Z){
    uint8_t DataH, DataL;

    DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
    *Accel_X = (DataH << 8) | DataL;

    DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
    *Accel_Y = (DataH << 8) | DataL;

    DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
    *Accel_Z = (DataH << 8) | DataL;

    DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
    *Gyro_X = (DataH << 8) | DataL;

    DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
    *Gyro_Y = (DataH << 8) | DataL;

    DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
    *Gyro_Z = (DataH << 8) | DataL;

}