#include <REGX51.H>
#include "delay.h"

void main()
{
	while(1)
	{
		P2=0xfe; //1111 1110
		delay (50);
		P2=0xfd; //1111 1101
		delay (50);
		P2=0xfb; //1111 1011
		delay (50);
		P2=0xf7; //1111 0111
		delay (50);
		P2=0xef; //1110 1111
		delay (50);
		P2=0xdf; //1101 1111
		delay (50);
		P2=0xbf; //1011 1111
		delay (50);
		P2=0x7f; //0111 1111
		delay (50);
	}
}