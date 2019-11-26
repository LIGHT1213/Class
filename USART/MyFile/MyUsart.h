#ifndef USART_H
#define USART_H
#include "stm32f4xx_hal.h"
#include "usart.h"
#include "stdio.h"
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif 

int fputc(int ch,FILE *f)
{
    uint8_t temp[1]={ch};
    //HAL_UART_Transmit(&huart1,temp,1,10);   
		//HAL_UART_Transmit(&huart2,temp,1,10);
    HAL_UART_Transmit(&huart3,temp,1,10);   
		HAL_UART_Transmit(&huart6,temp,1,10); 		
		return ch;
}


PUTCHAR_PROTOTYPE
{
	//HAL_UART_Transmit(&huart1,(uint8_t*)&ch,1,10);
	//HAL_UART_Transmit(&huart2,(uint8_t*)&ch,1,10);
	HAL_UART_Transmit(&huart3,(uint8_t*)&ch,1,10);
	HAL_UART_Transmit(&huart6,(uint8_t*)&ch,1,10);
	return ch;
}
#endif