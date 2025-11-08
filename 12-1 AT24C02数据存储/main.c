#include <REGX51.H>
#include <LCD1602.h>
#include "key.h"
#include "AT24C02.h"
#include "delay.h"


unsigned char Num,KeyNum,Data;
void main ()
{
	LCD_Init();

	while(1)
	{
		KeyNum=Key();
		if(KeyNum)
		{
			if(KeyNum==1)
			{
				Num++;
				LCD_ShowNum(1,1,Num,2);
			}
			if(KeyNum==2)
			{
				Num--;
				LCD_ShowNum(1,1,Num,2);
			}
			if(KeyNum==3)
			{
				AT24C02_WriteByte(0,Num%256);
				delay(5);
				AT24C02_WriteByte(1,Num/256);
				delay(5);
				LCD_ShowString(1,9,"Write Ok!");
				delay(100);
				LCD_ShowString(1,9,"         ");
			}
			if(KeyNum==4)
			{
				Num=AT24C02_ReadByte(0);
				Num|=AT24C02_ReadByte(1)<<8;
				LCD_ShowNum(1,1,Num,2);
				LCD_ShowString(1,9,"Read Ok!");
				delay(100);
				LCD_ShowString(1,9,"        ");
			}
		}
	}
}
  



