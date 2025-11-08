#include <REGX51.H>
#include "LCD1602.h"
#include "delay.h"
#include "XPT2046.h"
#include "Key.h"

unsigned int ADValue;
void main ()
{
	LCD_Init();
	LCD_ShowString(1,1,"UR  TR  LR");
	
    while(1)
	{
		ADValue=XPT2046_ReadAD(XPT2046_XP_8);
		LCD_ShowNum(2,1,ADValue,3);
		ADValue=XPT2046_ReadAD(XPT2046_YP_8);
		LCD_ShowNum(2,5,ADValue,3);
		ADValue=XPT2046_ReadAD(XPT2046_VBAT_8);
		LCD_ShowNum(2,9,ADValue,3);
		delay(10);
	}
}


