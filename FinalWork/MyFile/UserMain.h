#ifndef USERMAIN_H
#define USERMAIN_H
#include "stm32f4xx_hal.h"
#include "sys1.h"
void UserMain(void);
void STM324xG_LCD_Init(void);
uint16_t LCD_ReadReg(uint8_t LCD_Reg);
void LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue);
void LCD_WriteRAM(uint16_t RGB_Code);
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);
void LCD_WriteRAM_Prepare(void);
void LCD_Clear(uint16_t Color);
uint16_t LCD_ReadReg(uint8_t LCD_Reg);

#endif