#include "gui.h"
uint16_t Adc_table[2048];
float32_t FFT_table[2048];
FATFS bmpfs[2]; 
FIL bmpfsrc, bmpfdst; 
FRESULT bmpres;

UINT LenthNumber;
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

int Screen_shot(unsigned short int x,\
                unsigned short int y,\
                unsigned short int Width,\
                unsigned short int Height,\
                unsigned char *filename)
{
	/* bmp  �ļ�ͷ 54���ֽ� */
	unsigned char header[54] =
	{
		0x42, 0x4d, 0, 0, 0, 0, 
		0, 0, 0, 0, 54, 0, 
		0, 0, 40,0, 0, 0, 
		0, 0, 0, 0, 0, 0, 
		0, 0, 1, 0, 24, 0, 
		0, 0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0, 
		0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 
		0, 0, 0
	};
	
	int i;
	int j;
	long file_size;     
	long width;
	long height;
	unsigned char r,g,b;	
	unsigned char tmp_name[30];
	unsigned int mybw;
	unsigned int read_data;
	char kk[4]={0,0,0,0};
	
	/* ��*�� +������ֽ� + ͷ����Ϣ */
	file_size = (long)Width * (long)Height * 3 + Height*(Width%4) + 54;		

	/* �ļ���С 4���ֽ� */
	header[2] = (unsigned char)(file_size &0x000000ff);
	header[3] = (file_size >> 8) & 0x000000ff;
	header[4] = (file_size >> 16) & 0x000000ff;
	header[5] = (file_size >> 24) & 0x000000ff;
	
	/* λͼ�� 4���ֽ� */
	width=Width;	
	header[18] = width & 0x000000ff;
	header[19] = (width >> 8) &0x000000ff;
	header[20] = (width >> 16) &0x000000ff;
	header[21] = (width >> 24) &0x000000ff;
	
	/* λͼ�� 4���ֽ� */
	height = Height;
	header[22] = height &0x000000ff;
	header[23] = (height >> 8) &0x000000ff;
	header[24] = (height >> 16) &0x000000ff;
	header[25] = (height >> 24) &0x000000ff;
	
	/* ��filename ����һ���ĸ�ʽ������ tmp_name */
	sprintf((char*)tmp_name,"0:%s.bmp",filename);
	
	/* ע��һ�����������߼���Ϊ0 */
	
	/* �½�һ���ļ� */
	bmpres = f_open( &SDFile , (char*)tmp_name, FA_CREATE_NEW | FA_WRITE );
	
	/* �½��ļ�֮��Ҫ�ȹر��ٴ򿪲���д�� */
	f_close(&SDFile);
		
	bmpres = f_open( &SDFile , (char*)tmp_name,  FA_OPEN_EXISTING | FA_WRITE);

	if ( bmpres == FR_OK )
	{    
		/* ��Ԥ�ȶ���õ�bmpͷ����Ϣд���ļ����� */
		bmpres = f_write(&SDFile, header,sizeof(unsigned char)*54, &mybw);		
		
		/* �����ǽ�ָ�����ڵ����ݶ�����д���ļ�����ȥ */
		for(i=0; i<Height; i++)					
		{
			if( !(Width%4) )				/* �պ���4�ֽڶ��� */
			{
				for(j=0; j<Width; j++)  
				{					
					read_data = LCD_ReadPoint(y+j, x+i);				
					
					r =  GETR_FROM_RGB16(read_data);
					g =  GETG_FROM_RGB16(read_data);
					b =  GETB_FROM_RGB16(read_data);

					bmpres = f_write(&SDFile, &b,sizeof(unsigned char), &mybw);
					bmpres = f_write(&SDFile, &g,sizeof(unsigned char), &mybw);
					bmpres = f_write(&SDFile, &r,sizeof(unsigned char), &mybw);
					//f_write(&SDFile, &read_data,sizeof(unsigned char), &mybw);
				}
			}
			else
			{
				for(j=0;j<Width;j++)
				{					
					read_data = LCD_ReadPoint(y+j, x+i);
					
					r =  GETR_FROM_RGB16(read_data);
					g =  GETG_FROM_RGB16(read_data);
					b =  GETB_FROM_RGB16(read_data);

					bmpres = f_write(&SDFile, &b,sizeof(unsigned char), &mybw);
					bmpres = f_write(&SDFile, &g,sizeof(unsigned char), &mybw);
					bmpres = f_write(&SDFile, &r,sizeof(unsigned char), &mybw);
				}
				/* ����4�ֽڶ�������Ҫ���� */	
				bmpres = f_write(&SDFile, kk,sizeof(unsigned char)*(Width%4), &mybw);
			}	
		}/* ������� */
		printf("SAVE OK!");
		f_close(&SDFile); 
		return 0;
	}
	else if ( bmpres == FR_EXIST )  //����ļ��Ѿ�����
	{
		return FR_EXIST;	 					//8
	}
	else/* ����ʧ�� */
	{
		printf("SAVE FAIL");
		return -1;
	}    
	
}
uint16_t LCD_RD_data(void)	
{	
	uint16_t R=0, G=0, B=0 ;	
	R = *(__IO uint16_t *)Bank1_LCD_D; 	  /*FIRST READ OUT DUMMY DATA*/
	R = *(__IO uint16_t *)Bank1_LCD_D;  	/*READ OUT RED DATA  */
	B = *(__IO uint16_t *)Bank1_LCD_D;  	/*READ OUT BLACK DATA*/
	G = *(__IO uint16_t *)Bank1_LCD_D;  	/*READ OUT GREEN DATA*/
	
    return (((R>>11)<<11) | ((G>>10)<<5) | (B>>11));
}

uint16_t LCD_GetPoint(uint16_t x , uint16_t y)
{
	LCD_SetCursor(x, y);
	LCD_ILI9341_CMD(0x2e);         /* ������ */
	return (LCD_RD_data());
}