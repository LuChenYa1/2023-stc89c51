#include <REGX51.H>
#include "MatrixLED.h"

void main ()
{
	void MatrixLED_Init();
 
	while (1)
	{
		MatrixLED_ShowColumn(0,0x3c);
		MatrixLED_ShowColumn(1,0x42);
		MatrixLED_ShowColumn(2,0xad);
		MatrixLED_ShowColumn(3,0x83);
		MatrixLED_ShowColumn(4,0x83);
		MatrixLED_ShowColumn(5,0xad);
		MatrixLED_ShowColumn(6,0x42);
		MatrixLED_ShowColumn(7,0x3c);
	}
}

