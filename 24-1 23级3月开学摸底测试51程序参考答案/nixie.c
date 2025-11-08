#include <REGX51.H>
#include "delay.h"

typedef  unsigned char uchar;

uchar xianshi[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x00,0x40};
uchar nixie_Buf[9]={0,18,18,18,18,18,18,18,18};//显示数字缓存区（数组套数组）

/**
  * @brief  
  * @param  
  * @retval 
  */
void nixie(uchar location,number)
{
	nixie_Buf[location]=number;
}


/**
  * @brief  从左到右，对应87654321，显示指定的数字
  * @param  location，数字显示的位置
  * @param  number，  要显示的数字
  * @retval 无
  */
void nixie_xianshi(uchar location,number)
{
		P2_4 = 0;P2_3 = 0;P2_2 = 0;
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
		P0=xianshi[number];
		//下面的语句适用于显示多个数字，单个数字显示会有问题
//		delay(2);                              //消影，使上下两位数字显示留有时间间隔
//      P2=0x00;                               //延时200us
}


/**
  * @brief  
  * @param  
  * @retval 
  */
void nixie_Loop()
{
	static uchar i=1;

	nixie_xianshi(i,nixie_Buf[i]);
	i++;
	if(i == 9)i = 1;
}
