#include <REGX51.H>
#include "car.h"
#include "UART.h"
#include "Timer0_Init.h"
#include "Track.h"
#include "motor.h"

unsigned char BlueToothValue,RunFlag;
char Result;
void main ()
{
//	UART_Init();
//	Timer0_Init();

    while(1)
	{ 
//		if(RunFlag ==1)
//		{
//			read_sensor_values();
//		}
		ENB = 1;
		left1 = 0;
		left2 = 1;
	}
}

 
void UART_Routine()   interrupt 4  
{
	if(RI==1)                      
	{
		RI=0;                     //手动复位 
		BlueToothValue=SBUF;
		UART_SendByte(BlueToothValue);
		switch(BlueToothValue)
		{
 			case 0x01:RunFlag = 1;break;//开始循迹,停止蓝牙
			case 0x02:RunFlag = 2;Car_Stop();break;//停止循迹，开始蓝牙
//			case 0x03: 
//			case 0x04: 
//			case 0x05: 
			
			case 0x07:Car_Go();break;
			case 0x08:Car_LeftGo();break;
			case 0x09:Car_Stop();break;
			case 0x10:Car_RightGo();break;
			case 0x11:Car_Back();break;
		} 
	}
}

 