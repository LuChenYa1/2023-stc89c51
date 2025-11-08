#include <REGX51.H>
#include "delay.h"

unsigned char xianshi[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x00,0x40};
unsigned char nixie_Buf[9]={0,16,16,16,16,16,16,16,16};

void nixie(unsigned char location,number)
{
	nixie_Buf[location]=number;
}
void nixie_xianshi(unsigned char location,number)
{
		//P2=0x00;//这一句放前面能有效解决残影问题
		switch(location)
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
	   // P2 = (P2&0xE3)|((location-1)<<2);
		P0=xianshi[number];
		delay100us(4);                              //消影，使上下两位数字显示留有时间间隔
		                                            //定时器扫描数码管，不加任何延时,会让数码管响应更快
													//但是去掉延时，数码管无法动态显示
}

void nixie_Loop()
{
	static unsigned char i=1;
	nixie_xianshi(i,nixie_Buf[i]);
	i++;
	if(i==9)i=1;
}
