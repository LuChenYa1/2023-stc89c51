#include <REGX51.H>
#include "nixie.h"
#include "delay.h"
 
void main()             
{
	while(1)
	{
		nixie(8,1);
		nixie(7,2);
		nixie(6,3);
		nixie(5,7);
		nixie(4,5);
		nixie(3,8);
	}
}