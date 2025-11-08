#include <REGX51.H>
#include "delay.h"
#include "key.h"
#include "LCD1602.h"
#include "AT24C02.h"
#include "DS18B20.h"
#include "Timer0_Init.h"
 
float T,TShow;
char THigh,TLow;
unsigned char KeyNum;

void main ()
{
	Timer0_Init();
	THigh=AT24C02_ReadByte(0);
	TLow=AT24C02_ReadByte(1);
	if(THigh>125||TLow<-55||THigh<TLow)
	{
		THigh=30;
		TLow=15;
	}
	LCD_Init();
	LCD_ShowString(1,1,"T:");
	LCD_ShowString(2,1,"TH:");//温度上限
	LCD_ShowString(2,9,"TL:");//温度下限
	LCD_ShowSignedNum(2,4,THigh,3);
	LCD_ShowSignedNum(2,12,TLow,3);	

    while(1)
	{
		KeyNum=Key();
		/************显示温度**************/
		DS18B20_Convert_T();//更新
		T=DS18B20_Read_T(); //读取
		if(T<0)
		{
			LCD_ShowChar(1,3,'-');
			TShow=-T;
		}
		else
		{
			LCD_ShowChar(1,3,'+');
			TShow=T;			
		}
		LCD_ShowNum(1,4,TShow,3);
		LCD_ShowString(1,7,".");
		LCD_ShowNum(1,8,(unsigned long)(TShow*100)%100,2);
		/***********************************/
		
		/***********阈值调整及显示**********/
		if(KeyNum)
		{
			if(KeyNum==1)
			{
				THigh++;
				if(THigh>=125)THigh=125;
			}
			if(KeyNum==2)
			{
				THigh--;
				if(THigh<=TLow)THigh++;
			}
			if(KeyNum==3)
			{
				TLow++;
				if(TLow>=THigh)TLow--;
			}
			if(KeyNum==4)
			{
				TLow--;
				if(TLow==-55)TLow=-55;
			}		
		}
		LCD_ShowSignedNum(2,4,THigh,3);
		LCD_ShowSignedNum(2,12,TLow,3);	

		AT24C02_WriteByte(0,THigh);
		delay(5);
		AT24C02_WriteByte(1,TLow);
		delay(5);
		
		/***********************************/
		/********判断温度是否超过阈值*******/
		if(T>THigh)
		{
			LCD_ShowString(1,12,"OV:H");
		}
		else if(T<TLow)
		{
			LCD_ShowString(1,12,"OV:L");
		}
		else
		{
			LCD_ShowString(1,12,"    ");
		}
	}
}



void Timer0_Routine () interrupt 1
{
	static unsigned int T0count;     //静态局部变量，保证不会被重新赋值

	TL0 = 0x66;				         //确保中断时间不变
	TH0 = 0xFC;	
	T0count++;
	if(T0count == 20)                //每隔20毫秒进入if，灯亮灭变化
	{
		T0count=0;
		Key_Loop();
	}
}


