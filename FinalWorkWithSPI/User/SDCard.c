#include "SDCard.h"
void CheckSDCard(void)
{
			if(f_mount(&SDFatFS,(const TCHAR*)SDPath,1) != FR_OK)
		{
			printf("SdCard Mount Error : %d\r\n",f_mount(&SDFatFS,(const TCHAR*)SDPath,1));
			printf("Please reboot system!!!\r\n");
			while(1)
			{}
		}
		else
		{
			printf("SDCard ok!\r\n");
		}
}