#include <REGX51.H>          //大写的好处是不用加sbit去定义要使用的变量
#include "Timer0_Init.h"
#include "Key.h"
#include <intrins.h>

unsigned char KeyNum,LEDMode;
void main ()
{
	P2=0xfe;
	Timer0_Init();
	
    while(1)
	{
	    KeyNum=Key();          //这个函数一旦不按下，就会返回0，不再进入下面的if,LEDMode就一直不变，灯一直往一个方向亮
		if(KeyNum)
		{
			if(KeyNum==1)
			{
				LEDMode++;
				if(LEDMode==2) //LEDMode在0和1之间变换，按一次变换一次
				{
					LEDMode=0;
				}
			}
		}
	}
}

void Timer0_Routine () interrupt 1
{
	static unsigned int T0count;

	TL0 = 0x66;				         //确保中断时间不变
	TH0 = 0xFC;	
	T0count++;
	if(T0count == 1000)              //每隔1000毫秒(1s)进入if
	{
		T0count=0;
		if(LEDMode==1)
		{
			P2=_crol_(P2,1);         //二进制数左移,注：有问题，不是右补零吗
		}
		if(LEDMode==0)
		{
			P2=_cror_(P2,1);         //二进制数右移
		}
	}
}

