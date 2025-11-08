#include <REGX51.H>
#include "delay.h"
unsigned char xianshi[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x00, 0x40};
unsigned char nixie_Buf[9]={0,18,18,18,18,18,18,18,18};//显示数字缓存区（数组套数组）


/**
  * @brief  
  * @param  
  * @retval 
  */
void nixie(unsigned char location,number)
{
	nixie_Buf[location] = number;
}


/**
  * @brief  从左到右，对应87654321，显示指定的数字
  * @param  location，数字显示的位置
  * @param  number，  要显示的数字
  * @retval 无
  */
void nixie_xianshi(unsigned char location,number)
{
	P2 = 0x00;
	switch(location)
	{
		case 8:P2_5=1;P2_6=1;P2_7=1;break;//从左到右，对应87654321
		case 7:P2_5=1;P2_6=1;P2_7=0;break;
		case 6:P2_5=1;P2_6=0;P2_7=1;break;
		case 5:P2_5=1;P2_6=0;P2_7=0;break;
		case 4:P2_5=0;P2_6=1;P2_7=1;break;
		case 3:P2_5=0;P2_6=1;P2_7=0;break;
		case 2:P2_5=0;P2_6=0;P2_7=1;break;
		case 1:P2_5=0;P2_6=0;P2_7=0;break;
	}
	P0 = xianshi[number];
}

/**
  * @brief  
  * @param  
  * @retval 
  */
void nixie_Loop(void)
{
	static unsigned char i = 1;

	nixie_xianshi(i,nixie_Buf[i]);
	i++;
	if(i == 9)i = 1;
}


