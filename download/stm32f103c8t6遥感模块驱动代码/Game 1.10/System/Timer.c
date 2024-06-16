#include "stm32f10x.h"                  // Device header
#include "Game.h"

extern uint8_t SW;
extern uint16_t X, Y;
uint32_t u = 0, p = 0, n = 0, r = 0, m = 0;

extern struct Human
{
	uint8_t Life;
	uint8_t Mode;
	uint32_t Num, j;
	uint8_t x, y;
	uint8_t CD, o, action, point, CD1;
	
}Human1;

extern struct enemy
{
	uint8_t Life;
	uint8_t Mode;
	uint8_t Num, j;
	uint8_t x, y, CD;
}enemy1, enemy2;


void Timer_Init()
{
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	//选择APB1总线下的定时器Timer2
	
	TIM_InternalClockConfig(TIM2);		//TIM2使用内部时钟
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;		//计数模式，此处为向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 80 - 1;		//ARR 10000 = 1S
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;		//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;		//高级计时器特有，重复计数
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);		//使能中断
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;		//中断通道选择
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;		//优先级，同上
	
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2, ENABLE);		//打开定时器
}

void TIM2_IRQHandler()		//定时器2的中断函数，不懂直接套用
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		enemy1.Num ++;
		enemy1.j ++;	
		enemy2.Num ++;
		enemy2.j ++;			
		if (Human1.o == 0)
		{
			u ++;
			if (u > 200)
			{
				u = 0;
				Human1.o = 1;
				Human1.CD = 0;
			}
		}
		
		//enemy1
		
		if (enemy1.Num % 3 == 0)
		{
			enemy1.Num = 0;
			if(enemy1.x >= Human1.x)
			{
				enemy1.x --;
			}
			else if(enemy1.x < Human1.x)
			{
				enemy1.x ++;
			}
		
		}
		if (enemy1.j > 40)
		{
			enemy1.j = 0;
			if(enemy1.y > Human1.y)
			{
				enemy1.y --;
			}
			else if(enemy1.y < Human1.y)
			{
				enemy1.y ++;
			}
			else
			{
				enemy1.y = enemy1.y;
			}
		}
		if (enemy1.CD == 1 && enemy1.Life <= 0)
		{
			enemy1.Life = 1;
			enemy1.x = 100;
			enemy1.y = 3;
			enemy1.CD = 0;
			
		}
		if (enemy1.CD == 0)
		{
			n ++;
			if (n % 500 == 0)
			{
				enemy1.CD = 1;
				n = 0;
			}
		}	

		//enemy2
		
		if (enemy2.Num % 5 == 0)
		{
			enemy2.Num = 0;
			if(enemy2.x >= Human1.x)
			{
				enemy2.x --;
			}
			else if(enemy2.x < Human1.x)
			{
				enemy2.x ++;
			}
		
		}
		if (enemy2.j > 60)
		{
			enemy2.j = 0;
			if(enemy2.y > Human1.y)
			{
				enemy2.y --;
			}
			else if(enemy2.y < Human1.y)
			{
				enemy2.y ++;
			}
			else
			{
				enemy2.y = enemy2.y;
			}
		}
		if (enemy2.CD == 1 && enemy2.Life <= 0)
		{
			p ++;
			if (p % 500 == 0)
			{
				p = 0;
				enemy2.Life = 1;
				enemy2.x = 10;
				enemy2.y = 3;
				enemy2.CD = 0;
			}
		}
		if (enemy2.CD == 0)
		{
			r ++;
			if (r % 1000 == 0)
			{
				enemy2.CD = 1;
				r = 0;
			}
		}				
		
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);		//清空标志位
	}
}
