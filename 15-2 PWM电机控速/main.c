#include <REGX51.H>
#include "key.h"
#include "nixie.h"
#include "delay.h"
#include "Timer0_Init.h"

sbit Motor = P1^0;       //PWM（DAC）运行口，1工作

unsigned char KeyNum,Speed;
unsigned char Compare;
void main ()
{
	Timer0_Init();
	 
    while(1)
	{
		KeyNum=Key();
		 
		if(KeyNum==1)          //调节挡位
		{
			Speed++;
			Speed%=4;
		}
		nixie(8,Speed);
		if(Speed==0)Compare=0; //根据挡位设置占空比
		if(Speed==1)Compare=50;//占空比：高电平占整个周期的比值
		if(Speed==2)Compare=75;
		if(Speed==3)Compare=100;
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
		Motor=1;//电机高电平转
	}
	else                             //大于比较值时置低电平
	{
		Motor=0;//电机低电平不转
	}
}


