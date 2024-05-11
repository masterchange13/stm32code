#ifndef __SERIAL_H
#define __SERIAL_H

#include "stdio.h"

void Serial_Init();
void Serial_SendByte(uint8_t byte);
void Serial_SendArr(uint8_t * arr, uint16_t len);
void Serial_SendString(char * str);
void Serial_SendNumber(uint32_t num, uint8_t len);
void Serial_Printf(char * str, ...);

#endif
