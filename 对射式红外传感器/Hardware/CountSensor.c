#include "stm32f10x.h"                  // Device header

uint16_t CountSensor_Count = 0;

void CountSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructrue;
	GPIO_InitStructrue.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructrue.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructrue.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructrue);
	
	// AFIO
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);
	
	//EXTI
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
	// NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
}

// �жϺ��������ж��Ժ���д��������ǹ̶���
void EXTI15_10_IRQHandler(void)
{
	// ��ȡ��־λ
	if( EXTI_GetITStatus(EXTI_Line14) == SET)
	{
		CountSensor_Count++;
		// �����־λ��������ظ�ִ���жϣ�����
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
}

uint16_t CountSensor_Get(void)
{
	return CountSensor_Count;
}

