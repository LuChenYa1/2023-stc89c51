#include <REGX51.H>
#include "delay.h"

void main()
{
	while(1)
	{
		P2_3=0;
		delay(100);
		P2_3=1;
		delay(100);
	}
}