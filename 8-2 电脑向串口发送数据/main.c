#include <REGX51.H>
#include "delay.h"
#include "UART.h"

uchar a;

void main ()                      //波特率越低越稳定
{
	UART_Init();
    
	while(1);                     //卡住程序，防止重新运行，很重要的一步
}


void UART_Routine()   interrupt 4 //串口中断对应中断号
{
	if(RI==1)                     //发送和接收中断占用的是一个通道，都会触发中断函数，加if判断防止误触
	{
		P2=~SBUF;
		UART_SendByte(SBUF);  
		RI=0;                     //（手动）软件复位
	}
}

