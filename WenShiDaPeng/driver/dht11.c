#include "dht11.h"

extern TIM_HandleTypeDef htim1;

DHT11_DATA DHT11_data;

void Delay_us(uint16_t us)
{
	uint16_t differ = 0xffff - us - 5;
	__HAL_TIM_SET_COUNTER(&htim1, differ);
	HAL_TIM_Base_Start(&htim1);
	
	while(differ < 0xffff - 5)
	{
		differ = __HAL_TIME_GET_COUNTER(&htim1);
	}
	HAL_TIM_Base_Stop(&htim1);
}

void DATA_OUTPUT(u8 flg)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = DATA_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(DATA_GPIO_Port, &GPIO_InitStruct);
	
	if(flg == 0){
		DATA_RESET();
	}else{
		DATA_SET();
	}
}

u8 DATA_INPUT()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	U8 flg = 0;
	
	GPIO_InitStruct.Pin = DATA_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	// GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	
	HAL_GPIO_Init(DATA_GPIO_Port, &GPIO_InitStruct);
	
	if(DATA_READ() == GPIO_PIN_RESET){
		flg = 0;
	}else{
		flg = 1;
	}
	
	return flg;
}

void DHT11_Read_Byte(void)
{
	u8 ReadDat = 0;
	u8 temp = 0;
	u8 retey = 0;
	u8 i = 0;
	
	for(i = 0; i < 8; ++i){
		while(DATA_READ() == 0 && retry < 100){
			Delay_us(1);
			retry ++;
		}
		retry = 0;
		Delay_us(40);
		
		if(DATA_READ() == 0){
			temp = 1;
		}else{
			temp = 0;
		}
		while(DATA_READ() == 1 && retry < 100){
			Delay_us(1);
			retry ++;
		}
		retry = 0;
		
		ReadDat<<=1;
		ReadDat |= temp;
	}
	
	return ReadDat;
}

u8 DHT11_Read(void)
{
	u8 retry = 0;
	u8 i = 0;
	
	DATA_OUTPUT(0);
	HAL_Delay(18);
	DATA_SET();
	Delay_us(20);
	
	DATA_INPUT();
	Delay_us(20);
	
	if(DATA_READ() == 0){
		while(DATA_READ() == 0 && retry < 100){
			Delay_us(1);
			retry ++;
		}
		retry = 0;
		
		while(DATA_READ() == 1 && retry < 100){
			Delay_us(1);
			retry ++;
		}
		retry = 0;
			
		for(i = 0; i < 5; ++i){
			DHT11_data.Data[i] = DHT11_Read_Byte();
		}
		Delay_us(50);
	}
	u32 sum = DHT11_data.Data[0] + DHT11_data.Data[1] + DHT11_data.Data[2] + DHT11_data.Data[3];

	if(sum == DHT11_data.Data[4]){
		DHT11_data.humidity = DHT11_data.Data[0];
		DHT11_data.temp = DHT11_data.Data[2];
		return 1;
	}else{
		return 0;
	}
}

void Test(void)
{
	if(DHT11_Read())
	{
		DHT11_data.index ++;
		if(DHT11_data.index >= 128){
			DHT11_data.index = 0;
		}
	
	}
}

void DHT11_Task(void)
{
	Test();
}