#include <REGX51.H>
#include "delay.h"

unsigned  char Keynum;

unsigned char Key(void)
{
	Keynum=0;
	if(P3_1==0){delay(20);while(P3_1==0);delay(20);Keynum=1;}
	if(P3_0==0){delay(20);while(P3_0==0);delay(20);Keynum=2;}
	if(P3_2==0){delay(20);while(P3_2==0);delay(20);Keynum=3;}
	if(P3_3==0){delay(20);while(P3_3==0);delay(20);Keynum=4;}
	
	return Keynum;
}