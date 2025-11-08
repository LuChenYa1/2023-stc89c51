#include <REGX51.H>

sbit LED =P2^1;

void delay(unsigned char i)
{
	while(i--);
}


void main ()
{
	unsigned char Time,i;
    while(1)
	{
		for(Time=0;Time<100;Time++)
		{
			for(i=0;i<20;i++)
			{
				LED=0;
				delay(Time);
				LED=1;
				delay(100-Time);
			}
		}
		
		for(Time=100;Time>0;Time--)
		{
			for(i=0;i<20;i++)
			{
				LED=0;
				delay(Time);
				LED=1;
				delay(100-Time);
			}
		}
	}
}

