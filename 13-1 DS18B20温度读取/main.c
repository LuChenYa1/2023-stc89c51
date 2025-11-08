#include <REGX51.H>
#include "LCD1602.h"
#include "DS18B20.h"
#include "delay.h"

unsigned char ACK;
float T;
void main ()
{
	DS18B20_Convert_T();
	delay(100);            //让下面的温度还没来得及转换完时，T显示此时的温度转换值
	LCD_Init();
	LCD_ShowString(1,1,"temperature:");
    while(1)
	{
		DS18B20_Convert_T();
		T=DS18B20_Read_T();
		if(T<0)
		{
			LCD_ShowString(2,1,"-");
			T=-T;
		}
		else
		{
			LCD_ShowString(2,1,"+");

		}
		LCD_ShowNum(2,2,T,3);
		LCD_ShowChar(2,5,'.');
		LCD_ShowNum(2,6,(unsigned long)(T*10000)%10000,4);
	}
}

