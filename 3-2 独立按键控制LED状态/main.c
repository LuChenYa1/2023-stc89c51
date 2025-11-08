#include <REGX51.H>
#include "delay.h"
void main ()
{
	while(1)
	{
		if(P3_1==0)
		{
			delay(20);      //按下防抖  抖动时间为5~10ms
			while(P3_1==0); //判断是否松开
			delay(20);      //松开防抖
			P2_0=~P2_0;     //==0
		}
	}
	
}