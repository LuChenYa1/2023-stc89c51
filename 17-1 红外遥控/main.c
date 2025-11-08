#include <REGX51.H>
#include "LCD1602.h"
#include "delay.h"
#include "IR.h"


unsigned int Time;
unsigned char Command;
unsigned char Address;
unsigned char Num;

void main ()
{
	LCD_Init();
	IR_Init(); 
	LCD_ShowString(1,1,"ADD COM Num");
	LCD_ShowString(2,1,"00  00  00 ");
    while(1)
	{
		if(IR_GetDataFlag()||IR_GetRepeatFlag())
		{
			Address=IR_GetAddress();
			Command=IR_GetCommand();
			
			LCD_ShowHexNum(2,1,Address,2);
			LCD_ShowHexNum(2,5,Command,2);	
			if(Command==IR_2)
			{
				Num++;
			}
			else if(Command==IR_VOL_MINUS)
			{
				Num--;
			}
			LCD_ShowNum(2,9,Num,3);
		}
	}
}

 
