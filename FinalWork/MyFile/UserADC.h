#ifndef USER_ADC_H_
#define USER_ADC_H_


#include "main.h"
#include "adc.h"
#include "tim.h"

void User_AdcInit(void);

void User_AdcStartBlokingMode(uint16_t* ArrayAddress,uint16_t  Lenth);

void User_AdcStop(void);




#endif