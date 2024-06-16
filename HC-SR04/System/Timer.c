#include "stm32f10x.h"  
#include "Delay.h"

unsigned int Y_Out_Counter;//溢出时间增量(也就是计数器溢出的次数)

// 定时器初始化函数
void init_timer(void) {
    // 使能TIM2时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // 配置定时器参数
    TIM_TimeBaseInitTypeDef timerInitStructure;
    timerInitStructure.TIM_Prescaler = 16000 - 1; // 预分频器
    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数模式
    timerInitStructure.TIM_Period = 1000 - 1; // 自动重装载值
    timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; // 时钟分频
    timerInitStructure.TIM_RepetitionCounter = 0; // 重复计数器
    TIM_TimeBaseInit(TIM2, &timerInitStructure);
}

void Timer_on(void)
{
	TIM_SetCounter(TIM2,0);//计数值清零(解除干扰)
	Y_Out_Counter = 0;//定时器还没使能，溢出值始终为0
	TIM_Cmd(TIM2,ENABLE);
}

void Timer_off(void)
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

// 获取计算器的计数值并转换为时间
float Timer_Get_Time(void) {
    unsigned int totalCounts;
    float time;
    
    // 计算总的计数值
    totalCounts = Y_Out_Counter * 1000 + TIM_GetCounter(TIM2);
    
    // 将计数值转换为时间（单位：秒）
    time = totalCounts * (1.0 / 4500.0);
    
    TIM_SetCounter(TIM2, 0); // 计数值清零
    Y_Out_Counter = 0; // 重置溢出计数
    
    return time; // 返回时间值
}
