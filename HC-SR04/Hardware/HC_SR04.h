#ifndef __HC_SR04_H
#define __HC_SR04_H

#include "stm32f10x.h"  

#define GPIO_Port GPIOB
#define GPIO_Pin_Trig GPIO_Pin_12
#define GPIO_Pin_Echo GPIO_Pin_13

void HC_SR_Init(void);
float get_distance(void);

#endif
