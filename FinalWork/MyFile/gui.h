#ifndef __GUI_H
#define __GUI_H
#include "UserADC.h"
#include "ILI93xx.h"
#include "stm32f4xx_hal.h"
#include "UserFFT.h"
#include "SDCard.h"
#define GETR_FROM_RGB16(RGB565)  ((unsigned char)(( ((unsigned short int )RGB565) >>11)<<3))		  			//返回8位 R
#define GETG_FROM_RGB16(RGB565)  ((unsigned char)(( ((unsigned short int )(RGB565 & 0x7ff)) >>5)<<2)) 	//返回8位 G
#define GETB_FROM_RGB16(RGB565)  ((unsigned char)(( ((unsigned short int )(RGB565 & 0x1f))<<3)))       	//返回8位 B
#define Bank1_LCD_C    ((u32)0x6C000000)	   //Disp Reg ADDR
#define Bank1_LCD_D    ((u32)0x6D000000)       //Disp Data ADDR       // A23 PE2
#define LCD_ILI9341_CMD(index)       LCD_WR_REG(index)
#define LCD_WR_REG(index)    ((*(__IO u16 *) (Bank1_LCD_C)) = ((u16)index))
void LCD_OUTPUT_Wave(void);
void LCD_OUTPUT_FFT(void);
void Lcd_Clear(uint16_t Color);               
void SaveToSDcard(void);
uint16_t LCD_GetPoint(uint16_t x , uint16_t y);
int Screen_shot(unsigned short int x,\
                unsigned short int y,\
                unsigned short int Width,\
                unsigned short int Height,\
                unsigned char *filename);
#endif