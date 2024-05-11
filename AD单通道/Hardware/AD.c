#include "stm32f10x.h"

void AD_Init()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); // 使能ADC1时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    RCC_ADCCLKConfig(RCC_PCLK2_Div6); // ADC时钟频率为72MHz/6 = 12hz
    GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; // ADC专属模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);

    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; // 独立工作模式
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; // 右对齐
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // 无
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; // 单次转换模式
    ADC_InitStructure.ADC_ScanConvMode = DISABLE; // 单通道模式
    ADC_InitStructure.ADC_NbrOfChannel = 1; // 转换次数
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_Cmd(ADC1, ENABLE); // 使能ADC1

    // ADC校准
    ADC_ResetCalibration(ADC1); // 开始复位校准
    while(ADC_GetResetCalibrationStatus(ADC1) == SET); // 等待复位校准结束
    ADC_StartCalibration(ADC1); // 开始ADC校准
    while(ADC_GetCalibrationStatus(ADC1) == SET); // 等待校准结束

    // 如果使用连续转换，可以在下面使用一次,把转换模式换成连续转换
    // ADC_SoftwareStartConvCmd(ADC1, ENABLE); // 使能软件转换
}

uint16_t AD_GetValue(){
    // 如果使用连续转换，直接返回结果就行，下面两行不需要
    ADC_SoftwareStartConvCmd(ADC1, ENABLE); // 使能软件转换
    while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET); // 等待转换结束
    return ADC_GetConversionValue(ADC1); // 返回转换结果
}