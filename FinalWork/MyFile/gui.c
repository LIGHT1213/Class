#include "gui.h"
uint16_t Adc_table[2048];
float FFT_table[2048];
int LastX_Wave=0,LastY_Wave=120;
int LastX_FFT=20,LastY_FFT=200;
void LCD_OUTPUT_Wave(void)
{
		User_AdcStartBlokingMode(Adc_table,2048);
		for(uint16_t counter = 0;counter < 2048;counter ++)
		{
			//printf("%f\r\n",(109*(3.3*Adc_table[counter]/4095)-100));
			if(counter<2040)
			{
			if(counter%12==0)
			{
				int temp;
				temp=counter/6;
				Gui_DrawLine(LastX_Wave,LastY_Wave,temp,(int)(80*(3.3*Adc_table[counter]/4095)+70) ,RED);
				LastX_Wave=temp;
				LastY_Wave=(80*(3.3*Adc_table[counter]/4095)+70);
				HAL_Delay(10);
			}
			}
			else
			{
				HAL_Delay(1000);
				LastX_Wave=0;
				LastY_Wave=120;
				Lcd_Clear(WHITE);
				
			}
		}
		
}
void LCD_OUTPUT_FFT(void)
{
	
	User_FastRfft2048BlokingMode(FFT_table);
	//User_AdcStartBlokingMode(Adc_table,2048);
	for(uint16_t counter = 1;counter < 1024;counter ++)
	{
			if(counter<1020)
			{
			if(counter%4==0)
			{
				int temp;
				temp=20+(counter/4);
				Gui_DrawLine(LastX_FFT,LastY_FFT,temp,200-((int)((FFT_table[counter])/2)) ,BLACK);
				LastX_FFT=temp;
				LastY_FFT=200-((FFT_table[counter])/35);
				HAL_Delay(10);
			}
			}
			else
			{
				HAL_Delay(1000);
				LastX_FFT=20;
				LastY_FFT=200;
				Lcd_Clear(WHITE);
				
			}
	}
}

