#include <REGX51.H>
#include "Matrixkey.h"
#include "UART.h"
#include "nixie.h"
#include "Timer0_Init.h"

#define LED P2
unsigned char KeyNum;
unsigned char a,b,c; 

void main ()
{
	UART_Init();
	Timer0_Init();
    while(1)
	{
		KeyNum=Matrixkey(); 
		if(KeyNum)
		{
			if(KeyNum==1)
			{
				LED=~0x01;
				a++;
				UART_SendByte(0x09);
				if(a==100)a=0;
			}
			if(KeyNum==2)
			{
				LED=~0x02;
				a--;
				if(a==255)a=99;
			}
            if(KeyNum==3)LED=0x03;
		    if(KeyNum==4)LED=0x04;
			if(KeyNum==5)
			{
				LED=0x05;
				b++;
				if(b==100)b=0;
			}
			if(KeyNum==6)
			{
				LED=0x06;
				b--;
				if(b==255)b=99;
			}
			if(KeyNum==7)LED=0x07;
			if(KeyNum==8)LED=0x08;
			if(KeyNum==9)
			{
				LED=0x09;
				c++;
				if(c==100)c=0;
			}
			if(KeyNum==10)
			{
				LED=0x0a;
				c--;
				if(c==255)c=99;
			}
			if(KeyNum==11)LED=0x0b;
			if(KeyNum==12)LED=0x0c;
			if(KeyNum==13)LED=0x0d;
			if(KeyNum==14)LED=0x0e;
			if(KeyNum==15)LED=0x0f;
			if(KeyNum==16)
			{
				LED=0x10;
				a=0;
				b=0;
				c=0;
			}				
		}
		nixie(6,17);
		nixie(3,17);
		nixie(8,a/10);
		nixie(7,a%10);
		nixie(5,b/10);
		nixie(4,b%10);
		nixie(2,c/10);
		nixie(1,c%10);
	}
}




void UART_Routine()   interrupt 4 //串口中断对应中断号
{
	if(RI==1)                     //发送和接收中断占用的是一个通道，都会触发中断函数，加if判断防止误触
	{
		UART_SendByte(SBUF);
		RI=0;                     //（手动）软件复位
	}
}


void Timer0_Routine () interrupt 1
{
	static unsigned int T0count1,T0count2;     //静态局部变量，保证不会被重新赋值

	TL0 = 0x66;				         //确保中断时间不变
	TH0 = 0xFC;	
	T0count1++;
	if(T0count1 == 20)              //每隔20毫秒进入if，灯亮灭变化
	{
		T0count1=0;
		Matrixkey_Loop();
	}
	//定时器代替delay，其实质是将按键按下识别和数码管显示这些核心程序放到中断里，主函数负责收尾
	T0count2++;
	if(T0count2 == 5)              //每隔20毫秒进入if，灯亮灭变化
	{
		T0count1=0;
		 //if(KeyNum==1)LED=0x01;
	}
}



