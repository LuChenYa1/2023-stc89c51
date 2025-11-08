#include <REGX51.H>
#include "delay.h"

#define uint8_t unsigned char
sbit PWM_Servo = P3^0;

uint8_t Angle;

void contral_0(void)
{
	Angle = 0;   
	Delay_ms(500);
}
void contral_4(void)
{
	Angle = 4;   
	Delay_ms(500);
}void contral_1(void)
{
	Angle = 1;   
	Delay_ms(200);
}

//定时中断函数
void Timer0_Routine () interrupt 1
{
	static unsigned int T0count1;//静态局部变量

	TL0 = 0x33;				     //重新赋初值
	TH0 = 0xFE;	
	
	//舵机转动
	T0count1++;
	if(T0count1 == 40)           //0.5ms * 40 = 20ms
	{
		T0count1 = 0;
	}
	if(T0count1 <= Angle)
	{
		 PWM_Servo = 1;
	}
	else
	{
		 PWM_Servo = 0;
	}
}
	
