#include <REGX51.H>
#include "Timer0_Init.h"
#include "Key.h"
#include "nixie.h"
#include "delay.h"
#include "AT24C02.h"

uchar KeyNum,temp;
uchar Min,Sec,MinSec;
uchar RunFlag;
void main ()
{
	Timer0_Init();
    while(1)
	{
		KeyNum = Key();      //中断函数不停地返回对应的按键值
		if(KeyNum==1)
		{
			RunFlag=!RunFlag;
		}
		if(KeyNum==2)
		{
			Min=0;
			Sec=0;
			MinSec=0;
		}
		if(KeyNum==3)//保存
		{
			AT24C02_WriteByte(0,Min);
			delay(5);
			AT24C02_WriteByte(1,Sec);
			delay(5);
			AT24C02_WriteByte(2,MinSec);
			delay(5);
		}
		if(KeyNum==4)
		{ 
			Min=AT24C02_ReadByte(0);
			Sec=AT24C02_ReadByte(1);
			MinSec=AT24C02_ReadByte(2);
		}
		nixie(8,Min/10); 
		nixie(7,Min%10); 
		nixie(6,18); 
		nixie(5,Sec/10); 
		nixie(4,Sec%10);
		nixie(3,18); 
		nixie(2,MinSec/10); 
		nixie(1,MinSec/10); 
	}
	 
}


void Clock_Loop(void)
{
	if(RunFlag)
	{
		MinSec++;
		if(MinSec==100)
		{
			MinSec=0;
			Sec++;
			if(Sec==60)
			{
				Sec=0;
				Min++;
				if(Min==60)
				{
					Min=0;
				}
			}
		}
	}
}
void Timer0_Routine () interrupt 1
{
	static unsigned int T0count1,T0count2,T0count3;     //静态局部变量，保证不会被重新赋值

	TL0 = 0x66;				         //确保中断时间不变
	TH0 = 0xFC;	
	T0count1++;
	if(T0count1 == 20)              //每隔20毫秒进入if，灯亮灭变化
	{
		T0count1=0;
		Key_Loop();
	}
	//定时器代替delay，其实质是将按键按下识别和数码管显示这些核心程序放到中断里，主函数负责收尾
	T0count2++;
	if(T0count2 == 2)               //每隔2毫秒进入if，灯亮灭变化
	{
		T0count2=0;
		nixie_Loop();
	}
	T0count3++;
	if(T0count3 ==10)               //每隔2毫秒进入if，灯亮灭变化
	{
		T0count3=0;
		Clock_Loop();
	}
}


