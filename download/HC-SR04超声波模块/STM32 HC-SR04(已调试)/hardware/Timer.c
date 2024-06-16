#include "stm32f10x.h"                  // Device header
#include "Delay.h"

unsigned int Y_Out_Counter;//溢出时间增量(也就是计数器溢出的次数)

//定时器开
void Timer_On(void)
{
	TIM_SetCounter(TIM2,0);//计数值清零(解除干扰)
	Y_Out_Counter = 0;//定时器还没使能，溢出值始终为0
	TIM_Cmd(TIM2,ENABLE);
}

//定时器关
void Timer_Off(void)
{
	TIM_Cmd(TIM2,DISABLE);//关闭定时器
}

//定时中断 用于计算溢出次数
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)//中断标志判断
	{
		Y_Out_Counter++;//自增
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//清除中断标志
	}
}

//获取计算器的计数值
int Timer_Get_Counter(void)
{
	unsigned int T;
	T=Y_Out_Counter*100;//重装值100，每溢出一次，进入定时中断一次，因此，溢出计数值=溢出次数*重装值
	T=T+TIM_GetCounter(TIM2);//总的计数值=溢出次数*重装值+最后一次没有到溢出值的计数
	TIM_SetCounter(TIM2,0);//计数值清零
	Delay_ms(50);
	return T;
}


