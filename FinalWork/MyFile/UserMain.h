#ifndef USERMAIN_H
#define USERMAIN_H
#include "adc.h"
#include "stm32f4xx_hal.h"
#include "AutomaticDimming.h"
#include "ILI93xx.h"
#include "tim.h"
#include "UserFFT.h"
#include "gui.h"
#include "UserADC.h"
#include "KeyPad.h"
#include "stdio.h"
#include "My_uart.h"
#include "SDCard.h"
void UserMain(void);
void KeyChoose(void);
#endif