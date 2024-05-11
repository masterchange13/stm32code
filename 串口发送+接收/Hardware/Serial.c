#include "stm32f10x.h"
#include "stdio.h"
#include "stdarg.h"

uint8_t Serial_RxData;
uint8_t Serial_RxFlag;

void Serial_Init()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_TypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx  ;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStructure);

    // 使用中断接收数据
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);


    USART_Cmd(USART1, ENABLE);
}

void Serial_SendByte(uint8_t byte)
{
    USART_SendData(USART1, byte);
    // 等待发送完成
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);

}

void Serial_SendArr(uint8_t * arr, uint16_t len)
{
    uint16_t i;
    for(i = 0; i < len; i++){
        Serial_SendByte(arr[i]);
    }
}

void Serial_SendString(char * str)
{
    uint8_t i = 0;
    for(i = 0; str[i] != '\0'; i++){
        Serial_SendByte(str[i]);
    }
}

uint32_t Serial_Pow(uint32_t base, uint32_t exp)
{
    uint32_t result = 1;
    while(exp--){
        result *= base;
    }
    return result;
}

void Serial_SendNumber(uint32_t num, uint8_t len)
{
    uint8_t i;
    for (int i = 0; i < len; i++)
    {
        Serial_SendByte(num / Serial_Pow(10, len - i - 1) % 10 + '0');  
    }
    
}

// 把printf重定向，使用printf会调用SendByte函数
int fputc(int ch, FILE *f)
{
    Serial_SendByte((uint8_t)ch);
    return ch;
}

void Serial_Printf(char * str, ...)
{
    char String[100];
    va_list args;
    va_start(args, str);
    vsprintf(String, str, args);
    va_end(args);
    Serial_SendString(String);  
}

uint8_t Serial_GetRxFlag()
{
    if(Serial_RxFlag == 1){
        Serial_RxFlag = 0;
        return 1;
    }
    return 0;
}

uint8_t Serial_GetRxData()
{
    return Serial_RxData;
}

// 中断函数
void USART1_IRQHandler(void)
{
    if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
    {
        Serial_RxData = USART_ReceiveData(USART1);
        Serial_RxFlag = 1;        
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);

    }
}