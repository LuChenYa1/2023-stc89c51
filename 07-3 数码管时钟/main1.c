#include <REGX51.H>
#include "Timer0_Init.h"
#include "nixie.h"
#include "delay.h"

unsigned char s_g,s_s,f;       
unsigned char s=24;                  //，秒，分

void main ()
{
	Timer0_Init();
    while(1)
	{
	    nixie(7,17);         //分隔符
		nixie(4,17);         //分隔符
		
		nixie(5,s_g);        //显示s个位
		nixie(6,s_s);        //显示s十位
	}
}

void Timer0_Routine () interrupt 1
{
	static unsigned int T0count;     //静态局部变量，保证不会被重新赋值

	TL0 = 0x66;				         //确保中断时间不变
	TH0 = 0xFC;	
	T0count++;
	if(T0count == 1000)               
	{
		T0count=0;
		s--;
		if(s==0) s=24;
		s_g=s%10;
		s_s=s/10;
	}
}

