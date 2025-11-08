#include <REGX51.H>
#include "delay.h"


void main()
{
	while(1)
	{
		if(P3_0==0 && P3_1==0)    // ����ͬʱ����     
		{
			delay(20);
			while(P3_0 == 0&&P3_1 == 0);
			delay(20);
			P2_0=~P2_0;
			P2_1=~P2_1;
		}
		else if(P3_2 == 0)
		{
			delay(20);
			while(P3_0 == 0);
			delay(20);
			P2_7 = ~P2_7;
		}
	}
}
