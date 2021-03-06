/*
* 本工程FFT相关函数 变量的实现都在这个文件
*/

#include "User_FFT.h"
#include "User_adc.h"
#include "arm_math.h"
#include "gui.h"
#include "stdlib.h"
#include "stdio.h"
#include "spi.h"
#define LEN 1024
float Array_Fre[2048];
extern uint8_t command;
int i=0;
	int temp=0;
	int tempi=0;
	int temp2=0;
	int tempi2=0;
	int temp3=0;
	int tempi3=0;
extern Pair* generate_data();
/*
* 该函数会从ADC以阻塞模式 2048Hz采样率采2048个点 然后进行rFFT 最终输出每个点的模长
*/
void User_FastRfft2048BlokingMode(float32_t* MagOutPosition)
{
	//ADC采样结果存放在这里
	uint16_t adc_input[2048] = {0};
	//2048个实部的输入数组
	float32_t realval[2048] = {0};
	float32_t fftoutput[2048] = {0};
	//快速FFT表结构体
	arm_rfft_fast_instance_f32 S;
	
	//2048输入点2048Hz rFFT查表结构体初始化
	arm_rfft_2048_fast_init_f32(&S);
	
	User_AdcStartBlokingMode(adc_input,2048);
	
	//将ADC采集到的数据从DMA缓冲区取到准备FFT的位置
	for(uint16_t input = 0;input < 2048;input ++)
	{
		realval[input] = (3.3 * (float)adc_input[input]) / (float)4095;
	}
	
	//FFT运算函数 最后的 0 代表是正fft
	arm_rfft_fast_f32(&S,realval,fftoutput,0);
	//求模长
	arm_cmplx_mag_f32(fftoutput,MagOutPosition,1024);
	
	
}



void OUTPUT_Fre(void)
{
	uint8_t line =0;
	float Array_Fre[2048];
	User_FastRfft2048BlokingMode(Array_Fre);
//	Pair* m_data = generate_data();
//	sort(m_data);
//print_data(m_data);
	for(uint16_t i =1;i<1024;i++)
	{
	if(Array_Fre[i]>=temp)
	{
		temp=Array_Fre[i];
		tempi=i;
	}
	//printf("%f\r\n",Array_Fre[i]);
	
	}
		for(uint16_t i =1;i<1024;i++)
	{
	if(Array_Fre[i]>=temp2 && (i<=tempi-10 || i>=tempi+10))
	{
		temp2=Array_Fre[i];
		tempi2=i;
	}
	//printf("%f\r\n",Array_Fre[i]);
	
	}
			for(uint16_t i =1;i<1024;i++)
	{
	if(Array_Fre[i]>=temp3 && (i<=tempi-10 || i>=tempi+10) && (i<=tempi2-10 || i>=tempi2+10))
	{
		temp3=Array_Fre[i];
		tempi3=i;
	}
	//printf("%f\r\n",Array_Fre[i]);
	
	}
		LCD_OUTPUT_Float(0,0,"AMP",temp*2.2);
		LCD_OUTPUT_Float(140,0,"FRE",tempi);
		LCD_OUTPUT_Float(0,20,"AMP",temp2*2);
		LCD_OUTPUT_Float(140,20,"FRE",tempi2);
		LCD_OUTPUT_Float(0,40,"AMP",temp3*2);
		LCD_OUTPUT_Float(140,40,"FRE",tempi3);
	SaveDataToSDCard();
	
//	for(uint16_t i=0;i<=1023;i++)
//	{
//	}
}
void SaveDataToSDCard(void)
{
		unsigned int mybw;
		double print;
		char last[9]="";
		print=tempi;
		float2str(print,3,last);
		printf("%s",last);
		if(f_stat("data.txt",NULL) != FR_OK)
		{
			printf("data.txt not found ,data.txt Will Be Create \r\n");
			f_open( &SDFile , "0:/data.txt", FA_CREATE_NEW | FA_WRITE );
			f_close(&SDFile);
			printf("data write soon\r\n");
			f_open( &SDFile , "0:/data.txt", FA_CREATE_ALWAYS | FA_WRITE );
			f_write(&SDFile, (TCHAR*)last,sizeof(char[9]), &mybw);
			i++;
			printf("data write ok\r\n");
			f_close(&SDFile);
		}
		else if(f_stat("data.txt",NULL) == FR_OK)
		{
			printf("data write soon\r\n");
			f_open( &SDFile , "0:/data.txt", FA_CREATE_ALWAYS | FA_WRITE );
			f_lseek(&SDFile,i*9);
			f_write(&SDFile, (TCHAR*)last,sizeof(char[9]), &mybw);
			i++;
			printf("data write ok\r\n");
			f_close(&SDFile);
			
		}
}
void ShowNumInSD(void)
{
		unsigned char String[100];
	unsigned char String1[]={"can't find data.txt!!!!"};
	if(f_stat("data.txt",NULL) == FR_OK)
	{
	f_open( &SDFile , "0:/data.txt", FA_READ );
	f_gets((TCHAR*)String,100,&SDFile);
	f_close(&SDFile);
	Gui_DrawFont_GBK16(1,120,BLACK,WHITE,String);
	}
	else
	{
		Lcd_Clear(RED);
		Gui_DrawFont_GBK16(50,120,BLACK,RED,String1);
	}
}
void DeleteFile(void)
{
		unsigned char String1[]={"can't find data.txt!!!!"};
		unsigned char String2[]={"DELETE OK!"};
		if(f_stat("data.txt",NULL) == FR_OK)
		{
			f_unlink("data.txt");
			Gui_DrawFont_GBK16(50,120,BLACK,RED,String2);
			HAL_Delay(2000);
			Lcd_Clear(WHITE);
			command='4';
		}
		else if(f_stat("data.txt",NULL) != FR_OK)
		{
			Gui_DrawFont_GBK16(50,120,BLACK,RED,String1);
			HAL_Delay(2000);
			Lcd_Clear(WHITE);
			command='4';
		}
}
char * float2str(float val, int precision, char *buf)
{
    char *cur, *end;
    
    sprintf(buf, "%.6f", val);
    if (precision < 6) {
        cur = buf + strlen(buf) - 1;
        end = cur - 6 + precision; 
        while ((cur > end) && (*cur == '0')) {
            *cur = '\0';
            cur--;
        }
    }
    
    return buf;
}
void print_data(Pair *data) {
	for (int i = 0; i < LEN; ++i) {
		printf("%f\r\n",data[i].value);
		
	}
//		for (int i = 0; i < LEN; ++i) {
//		printf("%f\r\n",Array_Fre[i]);
//		
//	}
}
Pair* generate_data() {
	Pair* m_data = (Pair*)malloc(sizeof(Pair)*LEN);
	for (int i = 0; i < 1024; ++i) {
		m_data[i].key = i;
		m_data[i].value = Array_Fre[i];
	}
	return m_data;
}
int compare(int a, int b) {
	return a > b ? 1 : (a == b) ? 0 : -1;
}
void sort(Pair* a) {
	int j, i;
	Pair key;
	for (j = 1; j < LEN; ++j)
	{
		key = a[j];
		for (i = j - 1; i >= 0; --i)
		{
			if (compare(a[i].value,key.value)==1)
			{
				break;
			}
			a[i + 1] = a[i];
		}
		a[i + 1] = key;
	}
}

