#include "AutomaticDimming.h"
__IO uint16_t ADCValue;
float Previous=0;
void AutomaticDimming(void)
{
	char tryl[4]="adc";
	float kp=60,ki=10,kd=0.7,LightError;
	uint16_t temp=GetADCValue(),temp2;
	__IO uint16_t LightVaule=GetADCValue();
		if(LightVaule>=250)
		LightVaule=250;
	temp2=5000-LightVaule*20;
		if(temp2>Previous)
		{
		for(int i=Previous;i<=temp2;i++)
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,5000-i);
			//HAL_Delay(1);
		}
		else
		{
					for(int i=temp2;i<=Previous;i++)
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,5000-i);
			//HAL_Delay(1);
		}
		Previous=temp2;
		Lcd_Clear(WHITE);
}
uint16_t GetADCValue(void)
{
	return ADCValue;
}
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	if(hadc==&hadc1)
	{
		HAL_ADC_Start_DMA(&hadc1,(uint32_t*)&ADCValue,1);
	}
}