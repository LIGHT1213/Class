#include "UserMain.h"
extern uint16_t Adc_table[2048];
uint8_t command;
void UserMain()
{
	uint16_t temp;
	TFTLCD_Init();
	HAL_ADC_Init(&hadc1);
	HAL_UART_Receive_IT(&huart1,&command,1);
	HAL_TIM_PWM_Init(&htim4);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
	HAL_TIM_Base_Start_IT(&htim2);
	User_AdcInit();
	Lcd_Clear(WHITE);
	CheckSDCard();
	LCD_ShowNum(0,0,1,1,12);
	LCD_ShowNum(308,0,2,1,12);
	LCD_ShowNum(0,230,3,1,12);
	LCD_ShowNum(308,230,4,1,12);
	while(1)
	{
for(int i=0;i<=320;i++)
		for(int j=0;j<=240;j++)
		{
			LCD_DrawPoint(i,j);
		}
		//LCD_DrawPoint(1,1);
		//SaveToSDcard();
		KeyChoose();
//		OUTPUT_Fre();
//		LCD_OUTPUT_Wave();
//		HAL_Delay(1000);
//		LCD_OUTPUT_FFT();
	}
}
void KeyChoose(void)
{
	if(command=='1')
	{
		OUTPUT_Fre();
		LCD_OUTPUT_Wave();
		HAL_Delay(1000);
		LCD_OUTPUT_FFT();
		//command='1';
	}
	else if(command=='2')
	{
		Screen_shot(0,0,320,240,"/myscreen7");
	//SaveToSDcard();
		//command='2';
	}
}