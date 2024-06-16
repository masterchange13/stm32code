#include "stm32f10x.h"                  // Device header

void AD_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);		//开启ADC1内部时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		//开启GPIOA内部时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);	//12Mz, 配置ADC分频（*2、*4、6、8）
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入，ADC专属
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;		//工作模式，独立
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;		//数据对齐，右对齐
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;		//外部触发源选择，此处为不使用外部触发,使用软件触发
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;		//连续或单次模式，ENABLE为连续
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;		//扫描或单次，ENABLE为扫描		
	ADC_InitStructure.ADC_NbrOfChannel = 1;		//0——16，通道数目
	ADC_Init(ADC1, &ADC_InitStructure);	//初始化ADC
	
	ADC_Cmd(ADC1, ENABLE);		//开启ADC电源
	
	ADC_ResetCalibration(ADC1);		//复位校准
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);	//等待校准完成
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == SET);
}

uint16_t AD_GetValue(uint8_t ADC_Channel)
{
	ADC_RegularChannelConfig(ADC1, ADC_Channel, 1, ADC_SampleTime_55Cycles5);		//ADC_Channel_0，通道0，对应PA0， “1”代表序列1，ADC_SampleTime_55Cycles5代表采样时间55.5*ADCCLK(T)
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//软件触发ADC转换
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);		//等待转换完成
	return ADC_GetConversionValue(ADC1);		//获取转换值
	  
}
