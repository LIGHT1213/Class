#include "UserMain.h"
extern uint16_t Adc_table[2048];
void UserMain()
{
	TFTLCD_Init();
	HAL_ADC_Init(&hadc1);
	
	HAL_TIM_PWM_Init(&htim4);
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);
	HAL_TIM_Base_Start_IT(&htim2);
	User_AdcInit();
	Lcd_Clear(WHITE);
//	User_AdcStartBlokingMode(Adc_table,2048);
//	for(int i=0;i<=2046;i++)
//	{
//		printf("%d\r\n",Adc_table[i]);
//	}
	//printf("AT+NAMELightBlueTooth");
	//__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,i*10);
	while(1)
	{
		//LCD_ShowString(30,50,200,16,16,"STM32F4");	
		//LCD_ShowString(50,50,200,16,16,"adc");
		//AutomaticDimming();
		//LCD_OUTPUT_Float(50,50,"50",30.2);
		//HAL_Delay(100);
		//Gui_DrawLine(20,40,100,200,RED);
		//Lcd_Clear(RED);
		OUTPUT_Fre();
		LCD_OUTPUT_Wave();
		HAL_Delay(1000);
		LCD_OUTPUT_FFT();
		
		//KeyShow_LCD();
		//printf("123");
	}
}