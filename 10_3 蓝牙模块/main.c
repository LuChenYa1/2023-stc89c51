#include <REGX51.H>
#include "nixie.h"
#include "UART.h"
#include "delay.h"
unsigned char Lab,a;
void main ()
{
	UART_Init();
    while (1)
	{
		switch(Lab)
		{
			case 1:nixie(8,1);break;
			case 2:nixie(7,2);break;
			case 3:nixie(6,3);break;
			case 4:nixie(5,4);break;
			case 5:nixie(4,5);break;
			case 6:nixie(3,6);break;
			case 7:nixie(2,7);break;
			case 8:nixie(1,8);break;
		}
	}
}


void UART_Routine()   interrupt 4 //串口中断对应中断号
{
	if(RI==1)                     //发送和接收中断占用的是一个通道，都会触发中断函数，加if判断防止误触
	{
		RI=0;                     //（手动）软件复位
		a=SBUF;
		if(a==0x01)Lab=1;
		if(a==0x02)Lab=2;
		if(a==0x03)Lab=3;
		if(a==0x04)Lab=4;
		if(a==0x05)Lab=5;
		if(a==0x06)Lab=6;
		if(a==0x07)Lab=7;
		if(a==0x08)Lab=8;
		UART_SendByte(a);
	}
}
 



