//#include<REGX51.h>
//#include<stdio.h>
//#include "delay.h"

//#define uchar unsigned char
//#define uint unsigned int
//	
//////程序二：外部中断实现单按键控制单LED
////void main()
////{
////	//中断初始化
////	EA=1; 
////	IT0=1; 
////	EX0=1; 
////  P0 = ~0x00; 
////	while(1)
////	{
////		 
////	}
////}
////void int0() interrupt 0
////{
////	static uint b = 0;
////	P0 = ~ ( 0x01 << b );
////	b++;
////	b %= 4; 
////}

////程序四：外部中断结合与门实现多按键控制多LED
//uchar Light1[4] = {~0x01, ~0x02, ~0x04, ~0x08};//模式一
//uchar Light2[4] = {~0x01, ~0x03, ~0x07, ~0x0A};//模式二
//uchar i = 0;
//uchar MODE = 0;

//void main()
//{
//	//中断初始化
//	EA=1; 
//	IT0=1; 
//	EX0=1; 
//    P0 = ~0x00;
//	//主循环
//	while(1)
//	{
//		if(MODE == 1)//实现跑马灯
//		{
//			while(i < 4)
//			{
//				P0 = Light1[i];
//				i++;
//				delay_ms(20);
//			}
//		}
//		else  if(MODE == 2)//灯按顺序依次点亮
//		{
//			while(i < 4)
//			{
//				P0 = Light2[i];
//				i++;
//				delay_ms(50);
//			}
//		}
//		i = 0;//退出模式时要清零i，方便进入模式后继续跑马灯，该句不能放在while（i < 4）内部
//	}
//}
//void int0() interrupt 0
//{
//	if(P3_3 == 0)//不同的按键，切换不同的模式
//	{
//		MODE = 1;
//	}
//	if(P3_4 == 0)
//	{
//		MODE = 2;
//	}
//	if(P3_5 == 0)
//	{
//		MODE = 3;
//		P0 = ~0x09;//这里简写，亮个灯就行
//	}
//	if(P3_6 == 0)
//	{
//		MODE = 4;
//		P0 = ~0x06;//这里简写，亮个灯就行
//	}
//}
