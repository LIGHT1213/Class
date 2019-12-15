#include "SDCard.h"
void CheckSDCard(void)
{
			if(f_mount(&SDFatFS,(const TCHAR*)SDPath,1) != FR_OK)
		{
			printf("SdCard Mount Error : %d\r\n",f_mount(&SDFatFS,(const TCHAR*)SDPath,1));
		}
		else
		{
			printf("SDCard ok!");
		}
}