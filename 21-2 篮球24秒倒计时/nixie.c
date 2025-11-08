#include <REGX51.H>
#include "delay.h"
unsigned char xianshi[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,
						 0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E,
						 0xFF};
void nixie(unsigned char location,number)
{
		switch( location)
		{
			case 1:P1_0 = 1;P1_1 = 0;break;//位选
			case 2:P1_0 = 0;P1_1 = 1;break;
		}
		P0=xianshi[number];                //段选
		delay_ms(1);                       //消影，使上下两位数字显示留有时间间隔
		                         
		P0 = 0xFF;							//防止对下一次显示造成影响
}
