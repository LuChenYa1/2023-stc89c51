#include <REGX51.H>
#include "MatrixKey.h"
#include "delay.h"

#define uint8_t unsigned char
sbit PWM_Servo = P0^7;

uint8_t Angle;

void contral_0(void)
{
	Angle = 0;   
	Delay_ms(20);
}
void contral_4(void)
{
	Angle = 4;   
	Delay_ms(20);
}void contral_1(void)
{
	Angle = 1;   
	Delay_ms(20);
}

//定时中断函数
void Timer0_Routine () interrupt 1
{
	static unsigned int T0count1, T0count2;//静态局部变量

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
	//定时器扫描矩阵键盘
	T0count2++;
	if(T0count2 == 100)           //0.5ms * 100 = 50ms
	{
		T0count2 = 0;
		MatrixKey_Loop();
	}
}
	
