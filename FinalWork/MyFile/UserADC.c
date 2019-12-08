
#include "UserADC.h"

void User_AdcInit(void)
{
	HAL_ADC_Init(&hadc2);
	HAL_TIM_Base_Init(&htim3);
	HAL_TIM_Base_Start(&htim3);
}


void User_AdcStartBlokingMode(uint16_t* ArrayAddress,
															uint16_t  Lenth
														 )
{
	HAL_ADC_Start_DMA(&hadc2,(uint32_t*)ArrayAddress,Lenth);
	HAL_Delay(1005);
	User_AdcStop(); 
}

void User_AdcStop(void)
{
	HAL_ADC_Stop_DMA(&hadc2);
}
