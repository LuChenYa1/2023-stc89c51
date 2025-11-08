#include <REGX51.H>
#include "delay.h"
#include "UART.h"

uchar a;

void main ()               //波特率越低越稳定
{
	UART_Init();
    while(1)               // 只能传输十六进制数
	{
//		UART_SendByte(a);  
		UART_SendByte(0x66);
		a++;
	    delay(100);        //延时函数可以让数据无需复位就呈现正确值
	}		
	while(1);              //卡住程序，防止重新运行，很重要的一步
}

