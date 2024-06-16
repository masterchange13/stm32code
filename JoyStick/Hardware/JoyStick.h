#ifndef __JOYSTICK_H
#define __JOYSTICK_H

#define GPIO_Time RCC_APB2Periph_GPIOB
#define GPIO_Port GPIOB
#define GPIO_PinX GPIO_Pin_1
#define GPIO_PinY GPIO_Pin_2

void HW504_Init();
uint8_t HW504_R_SW();
uint16_t HW504_R_X();
uint16_t HW504_R_Y();

#endif
