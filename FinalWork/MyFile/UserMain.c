#include "UserMain.h"
extern uint16_t Adc_table[2048];
uint8_t command;
uint8_t UserMessage[]={"Welcome to digital oscilloscope"};
uint8_t UserMessage1[]={"Send 1 to view the waveform"};
uint8_t UserMessage2[]={"Send 2 to view historical amplitude"};
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
	Lcd_Clear(RED);
	LCD_ShowString(40,104,320,16,16,UserMessage);
	HAL_Delay(2000);
	Lcd_Clear(WHITE);
	CheckSDCard();
	LCD_ShowString(30,15,320,16,16,UserMessage1);
	LCD_ShowString(30,40,320,16,16,UserMessage2);	
	while(1)
	{
		KeyChoose();
//		LCD_DrawLine(10,10,10,230);
//		LCD_DrawLine(10,230,310,230);
//		LCD_DrawLine(310,230,310,10);
//		LCD_DrawLine(10,10,310,10);
	}
}
void KeyChoose(void)
{
	if(command=='1')
	{
		Lcd_Clear(WHITE);
		LCD_DrawLine(1,65,320,65);
		LCD_DrawLine(1,120,320,120);
		LCD_DrawLine(1,175,320,175);
		LCD_DrawLine(85,1,85,240);
		LCD_DrawLine(160,1,160,240);
		LCD_DrawLine(235,1,235,240);
		POINT_COLOR=RED;
		OUTPUT_Fre();
		LCD_OUTPUT_Wave();
		//HAL_Delay(500);
		OUTPUT_Fre();
		LCD_OUTPUT_FFT();
		command='1';
	}
	else if(command=='2')
	{
		//Screen_shot(0,0,320,240,"/myscreen7");
	//SaveToSDcard();
		//command='2';
	}
}