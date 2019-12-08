/*
* ???FFT???? ???????????
*/

#include "UserFFT.h"
#define LEN 1024
float Array_Fre[2048];
extern Pair* generate_data();
/*
* ?????ADC????? 2048Hz????2048?? ????rFFT ??????????
*/
void User_FastRfft2048BlokingMode(float32_t* MagOutPosition)
{
	//ADC?????????
	uint16_t adc_input[2048] = {0};
	//2048????????
	float32_t realval[2048] = {0};
	float32_t fftoutput[2048] = {0};
	//??FFT????
	arm_rfft_fast_instance_f32 S;
	
	//2048???2048Hz rFFT????????
	arm_rfft_2048_fast_init_f32(&S);
	
	User_AdcStartBlokingMode(adc_input,2048);
	
	//?ADC???????DMA???????FFT???
	for(uint16_t input = 0;input < 2048;input ++)
	{
		realval[input] = (3.3 * (float)adc_input[input]) / (float)4095;
	}
	
	//FFT???? ??? 0 ????fft
	arm_rfft_fast_f32(&S,realval,fftoutput,0);
	//???
	arm_cmplx_mag_f32(fftoutput,MagOutPosition,1024);
	
	
}



void OUTPUT_Fre(void)
{
	uint8_t line =0;
	int temp=0;
	int tempi=0;
	int temp2=0;
	int tempi2=0;
	int temp3=0;
	int tempi3=0;
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
			LCD_OUTPUT_Float(0,0,"AMP:",temp*2.2);
		LCD_OUTPUT_Float(140,0,"FRE:",tempi);
				LCD_OUTPUT_Float(0,20,"AMP:",temp2*2);
		LCD_OUTPUT_Float(140,20,"FRE:",tempi2);
					LCD_OUTPUT_Float(0,40,"AMP:",temp3*2);
		LCD_OUTPUT_Float(140,40,"FRE:",tempi3);
//	for(uint16_t i=0;i<=1023;i++)
//	{
//	}
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

