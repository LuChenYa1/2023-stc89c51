#include <REGX51.H>
#include "Timer1_Init.h"

sbit Motor = P1^0;       //PWM（DAC）运行口，1工作
unsigned char Compare;


void Motor_Init(void)
{
	Timer1_Init();
}


void Motor_SetSpeed(unsigned char Speed)
{
	Compare=Speed;
}
void Timer1_Routine () interrupt 1
{
	static unsigned int T1count;     //静态局部变量，保证不会被重新赋值

	TL1 = 0xA4;				         //确保中断时间不变,每隔100us进来一次
	TH1 = 0xFF;	
	T1count++;
	T1count%=100;                    //100us*10为一周期
	if(T1count<Compare)              //小于比较值时置高电平
	{
		Motor=1;//电机高电平转
	}
	else                             //大于比较值时置低电平
	{
		Motor=0;//电机低电平不转
	}
}

