#include <REGX51.H>
#include "delay.h"
#include "car.h"

sbit Trig = P1^7;
sbit Echo = P1^6;

unsigned char sum;//三个方向距离

unsigned char chaoshengbo ()//@11.0592MHz
{
//	T2MOD = 0;		//初始化定时器2 
//	T2CON = 0;		 
//	TL2 = 0;		 //设置定时初值，便于计数
//	TH2 = 0;		 
//	RCAP2L = 0;		 //设置定时重载值
//	RCAP2H = 0;	
	
	TMOD = 0x11;
	TL1 = 0;
	TH1 = 0;

	Trig = 1;        //发出脉冲
	delay20us();     //持续20us
	Trig = 0;
	
	while(!Echo);    //接收返回脉冲
	TR1 = 1;      	 //开始计数
	while(Echo);     //返回脉冲结束
	TR1 = 0;		 //停止计数
	
	sum = ((TH1*256+TL1)*0.034/2)+1;//单位cm
	return sum;
}



