#include "stm32f10x.h"

uint16_t MyDMA_Size;

void MyDMA_Init(uint32_t arrA, uint32_t arrB, uint16_t Size){

    MyDMA_Size = Size;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    DMA_InitTypeDef DMA_InitStructure;
    // DMA_DeInit(DMA1_Channel4);
    DMA_InitStructure.DMA_PeripheralBaseAddr = arrA; //
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
    DMA_InitStructure.DMA_MemoryBaseAddr = arrB;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = Size;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);

    DMA_Cmd(DMA1_Channel1, ENABLE);
    // DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);
}

void MyDMA_Transfer(void)
{
    DMA_Cmd(DMA1_Channel1, DISABLE);
    DMA_SetCurrDataCounter(DMA1_Channel1, MyDMA_Size);
    DMA_Cmd(DMA1_Channel1, ENABLE);

    // 检查是否转运完成
    while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
    DMA_ClearFlag(DMA1_FLAG_TC1);
}