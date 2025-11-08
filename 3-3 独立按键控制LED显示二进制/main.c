#include <REGX51.H>
#include "delay.h"
 
void main()
{
	unsigned char LEDNum = 0;        //不能放里面，会重定义
	while(1)
	{
		if(P3_1==0)
		{
			delay(20);
			while(P3_1==0);              //P3检验按键，P2负责亮灭
			delay(20);
			
			LEDNum++;                    //它的值是二进制，但由于0亮1灭，所以要取反值
			P2=~LEDNum;
		}
	}
}