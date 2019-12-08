#ifndef __GUI_H
#define __GUI_H
#include "UserADC.h"
#include "ILI93xx.h"
#include "stm32f4xx_hal.h"
#include "UserFFT.h"
void LCD_OUTPUT_Wave(void);
void LCD_OUTPUT_FFT(void);
void Lcd_Clear(uint16_t Color);               

#endif