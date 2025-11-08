#include <REGX51.H>
#include "DS1302.h"
#include "LCD1602.h"
#include "Servo.h"
#include "Timer0_Init.h"

unsigned char DS1302_Time[]={24, 1, 19, 21, 15, 00, 5};
unsigned char JudgeDateTime = 20;

void main ()
{
	LCD_Init();
	DS1302_Init();
	Timer0_Init();
	
	LCD_ShowString(1,1,"  -  -  ");
	LCD_ShowString(2,1,"  :  :  ");
	LCD_ShowString(2,10,"J:");
	
	DS1302_SetTime();
	while (1)
 	{
		DS1302_ReadTime();
		LCD_ShowNum(1,1,DS1302_Time[0],2);   //显示年
		LCD_ShowNum(1,4,DS1302_Time[1],2);   //显示月
		LCD_ShowNum(1,7,DS1302_Time[2],2);   //显示日
		LCD_ShowNum(2,1,DS1302_Time[3],2);   //显示时
		LCD_ShowNum(2,4,DS1302_Time[4],2);   //显示分
		LCD_ShowNum(2,7,DS1302_Time[5],2);   //显示秒
		LCD_ShowNum(1,10,DS1302_Time[6],1);  //显示星期
		
		if(DS1302_Time[2] == JudgeDateTime)
		{
			JudgeDateTime += 1;
			if(JudgeDateTime == 32)JudgeDateTime = 1;
			if(DS1302_Time[2] % 2 == 1)
			{
				contral_0();
				contral_4();
				LCD_ShowString(1, 15, "OK");
			}
			else if(DS1302_Time[2] % 2 == 0)
			{
				contral_0();
				contral_4();
				LCD_ShowString(1, 15, "  ");
			}
			LCD_ShowNum(2, 12, JudgeDateTime, 2);
			LCD_ShowNum(1, 12, DS1302_Time[2], 2);
		}
	}
}
 