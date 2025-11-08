#include <REGX51.H>
#include "key.h"
#include "nixie.h"
#include "delay.h"
#include "Timer0_Init.h"

sbit DA = P2^1;       //PWM（DAC）运行口，1工作,操作了一个DAC模块内置的灯

unsigned char i;
unsigned char Compare;

void main ()
{
	Timer0_Init();
	 
    while(1)
	{
		 for(i=0;i<100;i++)
		{
			Compare=i;//设置亮度从0到100
			delay(1);
		}
		 for(i=100;i>0;i--)
		{
			Compare=i;//设置亮度从100到0
			delay(1);
		}
	}
}

void Timer0_Routine () interrupt 1
{
	static unsigned int T0count;     //静态局部变量，保证不会被重新赋值

	TL0 = 0xA4;				         //确保中断时间不变,每隔100us进来一次
	TH0 = 0xFF;	
	T0count++;
	T0count%=100;                    //100us*10为一周期
	if(T0count<Compare)              //小于比较值时置高电平
	{
		DA=1;                        //亮
	}
	else                             //大于比较值时置低电平
	{
		DA=0;                        //灭
	}
}


