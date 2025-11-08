#include <REGX51.H>
#include "car.h"
#include "Timer0_Init.h"
#include "Track.h"
#include "chaoshengbo.H"
#include "delay.h"

void main ()
{
	Timer0_Init();
//  contral_0();
    while(1)
	{ 
		contral_1();
		contral_4();
//		read_sensor_values();
//		system_xunji();
	}
}

 
 