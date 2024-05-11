#ifndef __COUNT_SENSOR_H
#define __COUNTSENSOR_H

void CountSensor_Init(void);

// 不需要调用，会自动调用,库函数声明了
// void EXTI15_10_IRQHandler(void)

uint16_t CountSensor_Get(void);


#endif
 