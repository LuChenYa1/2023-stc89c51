#include <REGX51.H>
#include "delay.h"
unsigned char xianshi[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x00,0x40};

void nixie(unsigned char location,number)
{
		switch( location)
		{
			case 8:P2_4=1;P2_3=1;P2_2=1;break;//从左到右，对应87654321
			case 7:P2_4=1;P2_3=1;P2_2=0;break;
			case 6:P2_4=1;P2_3=0;P2_2=1;break;
			case 5:P2_4=1;P2_3=0;P2_2=0;break;
			case 4:P2_4=0;P2_3=1;P2_2=1;break;
			case 3:P2_4=0;P2_3=1;P2_2=0;break;
			case 2:P2_4=0;P2_3=0;P2_2=1;break;
			case 1:P2_4=0;P2_3=0;P2_2=0;break;
		}
		P0=xianshi[number];
		
		/********下面的语句在该项目要注释掉，防止显示消失*******/
//		delay(2);                              //消影，使上下两位数字显示留有时间间隔
//		P2=0x00;                               //延时200us,这里用到的是另一个delay函数
}
