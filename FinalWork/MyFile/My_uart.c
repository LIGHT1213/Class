#include "My_Uart.h"

#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif 
extern uint8_t command;
int fputc(int ch,FILE *f)
{
    uint8_t temp[1]={ch};
    HAL_UART_Transmit(&huart1,temp,1,10);   
		return ch;
}


PUTCHAR_PROTOTYPE
{
	HAL_UART_Transmit(&huart1,(uint8_t*)&ch,1,10);
	return ch;
}

void HAL_UART_RxCpltCallback (UART_HandleTypeDef * huart) 
{
	if(huart->Instance == USART1)
	{
		HAL_UART_Receive_IT(&huart1,&command,1);
	}
}