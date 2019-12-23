#include "main.h"
#include "spi.h"
#include "gpio.h"
#include "gui.h"

#include "User_adc.h"
#include "User_Uart.h"
#include "User_FFT.h"
#include "gui.h"
#include "SDCard.h"



float32_t aaa[2048];
uint8_t command;
void Systeminit(void);
void KeyChoose(void);
uint8_t UserMessage[]={"Welcome to digital oscilloscope"};
uint8_t UserMessage1[]={"Send 1 to view the waveform"};
uint8_t UserMessage2[]={"Send 2 to view historical amplitude"};
uint8_t UserMessage3[]={"Send 3 to delete file"};
void User_main(void)
{
	int i=0;
	float Adc_table[2048];
	int LastX=0,LastY=100;
	Systeminit();
	HAL_Delay(500);
	while(1)
	{
		//printf("%d",sizeof(char[9]));
		KeyChoose();
//		OUTPUT_Fre();
//		LCD_OUTPUT_Wave();
//		Lcd_Clear(WHITE);
//		LCD_OUTPUT_FFT();
	}
	
}




void Systeminit(void)
{
	//用户ADC1+TIM3+DMA初始化
	User_AdcInit();
	CheckSDCard();
	HAL_UART_Receive_IT(&huart1,&command,1);
	Gui_DrawFont_GBK16(40,104,BLACK,WHITE,UserMessage);
	HAL_Delay(2000);
	Lcd_Clear(WHITE);
	Gui_DrawFont_GBK16(30,15,BLACK,WHITE,UserMessage1);
	Gui_DrawFont_GBK16(30,40,BLACK,WHITE,UserMessage2);
	Gui_DrawFont_GBK16(30,65,BLACK,WHITE,UserMessage3);
}

void KeyChoose(void)
{
	if(command=='1')
	{
		Lcd_Clear(WHITE);
		Gui_DrawLine(1,65,320,65,BLACK);
		Gui_DrawLine(1,120,320,120,BLACK);
		Gui_DrawLine(1,175,320,175,BLACK);
		Gui_DrawLine(85,1,85,240,BLACK);
		Gui_DrawLine(160,1,160,240,BLACK);
		Gui_DrawLine(235,1,235,240,BLACK);
		//POINT_COLOR=RED;
		OUTPUT_Fre();
		LCD_OUTPUT_Wave();
		//HAL_Delay(500);
		//OUTPUT_Fre();
		LCD_OUTPUT_FFT();
		command='1';
	}
	else if(command=='2')
	{
		ShowNumInSD();
		//Screen_shot(0,0,320,240,"/myscreen7");
	//SaveToSDcard();
		//command='2';
	}
	else if(command=='3')
	{
		DeleteFile();
	}
	else if(command=='4')
	{
	Gui_DrawFont_GBK16(30,15,BLACK,WHITE,UserMessage1);
	Gui_DrawFont_GBK16(30,40,BLACK,WHITE,UserMessage2);
	Gui_DrawFont_GBK16(30,65,BLACK,WHITE,UserMessage3);
	}
}