#ifndef __AutomaticDimming_H
#define __AutomaticDimming_H
#include "adc.h"
#include "tim.h"
#include "stm32f4xx_hal.h"
#include "ILI93xx.h"
void AutomaticDimming(void);
uint16_t GetADCValue(void);
#endif