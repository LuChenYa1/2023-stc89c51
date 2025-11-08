#include <REGX51.H>
#include "delay.h"

void main()
{
	unsigned char LEDNum=0;     //不能放里面，会重定义
	P2=~0X01;
	while(1)
	{
		if(P3_1==0)
		{
			delay(20);
			while(P3_1==0);
			delay(20);
			LEDNum++;
			if(LEDNum==8)
			{
				LEDNum=0;
			}
			P2=~(0x01<<LEDNum);
			//P2=~((~P2)<<1);  该句行不通，一直左移超出了8位的范围
		}
		if(P3_0==0)
		{
			delay(20);
			while(P3_0==0);
			delay(20);
			if(LEDNum==0)
			{
				LEDNum=7;
			}
			else
			LEDNum--;                   //位移减少一位
			P2=~(0x01<<LEDNum);         //二进制位运算，取反值
			//P2=~((~P2)>>1);  该句行不通，一直右移超出了8位的范围

		}
	}
}