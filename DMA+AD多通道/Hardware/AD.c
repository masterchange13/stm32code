#include "stm32f10x.h"

uint16_t AD_Value[4];

void AD_Init()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); // 使能ADC1时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    RCC_ADCCLKConfig(RCC_PCLK2_Div6); // ADC时钟频率为72MHz/6 = 12hz
    GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; // ADC专属模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);

    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; // 独立工作模式
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; // 右对齐
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 无
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; // 单次转换模式
    ADC_InitStructure.ADC_ScanConvMode = ENABLE; // 单通道模式
    ADC_InitStructure.ADC_NbrOfChannel = 4; // 转换次数
    ADC_Init(ADC1, &ADC_InitStructure);

    DMA_InitTypeDef DMA_InitStructure;
    // DMA_DeInit(DMA1_Channel4);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR; //
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&AD_Value;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = 4;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);

    DMA_Cmd(DMA1_Channel1, ENABLE);
    // 开启ADC到DMA的输出
    ADC_DMACmd(ADC1, ENABLE);
    ADC_Cmd(ADC1, ENABLE); // 使能ADC1

    // ADC校准
    ADC_ResetCalibration(ADC1); // 开始复位校准
    while(ADC_GetResetCalibrationStatus(ADC1) == SET); // 等待复位校准结束
    ADC_StartCalibration(ADC1); // 开始ADC校准
    while(ADC_GetCalibrationStatus(ADC1) == SET); // 等待校准结束

    ADC_SoftwareStartConvCmd(ADC1, ENABLE); // 使能软件转换
}

// void AD_GetValue(void){
//     DMA_Cmd(DMA1_Channel1, DISABLE);
//     DMA_SetCurrDataCounter(DMA1_Channel1, 4);
//     DMA_Cmd(DMA1_Channel1, ENABLE);


//     // 检查是否转运完成
//     while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
//     DMA_ClearFlag(DMA1_FLAG_TC1);
// }