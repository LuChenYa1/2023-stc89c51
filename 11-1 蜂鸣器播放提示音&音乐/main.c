#include <REGX51.H>
#include "Key.h"
#include "nixie.h"
#include "Buzzer_time.h"


unsigned char KeyNum;
 
void main ()
{
	while(1)
	{
		KeyNum=Key();
		if(KeyNum)
		{
			Buzzer_time(10);
			nixie(8,KeyNum);
		}
	}
}

