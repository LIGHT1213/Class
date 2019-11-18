#include "inter.h"
#include "gpio.h"
#include "tim.h"

void shining(void)
{
		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,0);
		HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,0);
		HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,0);
		HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,0);
		while(1){
			
		HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
		HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
		HAL_GPIO_TogglePin(LED3_GPIO_Port,LED3_Pin);
		HAL_GPIO_TogglePin(LED4_GPIO_Port,LED4_Pin);
		MyDelay(1000);
		}

}
void runing(void)
{
	while(1)
	{
		HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_8);
		HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_9);
		MyDelay(2000);
		HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_8);
		HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_9);
		MyDelay(2000);
		HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_9);
		HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_10);
		MyDelay(2000);
		HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_9);
		HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_10);
		MyDelay(2000);
		HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_10);
		HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_7);
		MyDelay(2000);
		HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_10);
		HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_7);
	}
}
void MyDelay(uint16_t ms)
{
	uint16_t temp=0;
	HAL_TIM_Base_Start(&htim1);
	TIM1->CNT=0;
	while(temp<=ms)
	{
	if(TIM1->CNT == 1000)
	{
		temp++;
		TIM1->CNT=0;
	}
	}
	HAL_TIM_Base_Stop(&htim1);
	TIM1->CNT=0;
}