
#ifndef USER_FFT_H_
#define USER_FFT_H_

#include "UserADC.h"
#include "arm_math.h"
#include "gui.h"
#include "stdlib.h"
#include "stdio.h"
typedef struct {
	int key;
	float value;
}Pair;
void User_FastRfft2048BlokingMode(float32_t* MagOutPosition);
int compare(int a, int b);
void sort(Pair* a);
Pair* generate_data();
void OUTPUT_Fre(void);
void OUTPUT_amp(void);
void print_data(Pair *data);
#endif
