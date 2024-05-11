#include "stm32f10x.h"                  // Device header

void delay(){
	for(int i = 0; i < 1000000;){
		++i;
	}
	return ;
}

//?????,??
void delay_us(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=10;  //????
      while(i--) ;    
   }
}
//??????
void delay_ms(u16 time)
{    
   u16 i=0;  
   while(time--)
   {
      i=12000;  //????
      while(i--) ;    
   }
}

int main(void){
//	RCC->APB2ENR = 0x00000010;
//	GPIOC->CRH = 0x00300000;
//	GPIOC->ODR = 0x00002000;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOC, &GPIO_InitStructure);
//	GPIO_SetBits(GPIOC, GPIO_Pin_13);
//	
//	
	GPIO_ResetBits(GPIOA, GPIO_Pin_13); 
	while(1){
		GPIO_Init(GPIOC, &GPIO_InitStructure);
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		delay_ms(10);
		GPIO_ResetBits(GPIOA, GPIO_Pin_13); 
		delay_ms(10);
	}
	return 0;
}