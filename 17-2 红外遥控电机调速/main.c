#include <REGX51.H>
#include "key.h"
#include "nixie.h"
#include "delay.h"
#include "Motor.h"
#include "IR.h"


unsigned char Command,Speed;

void main ()
{
	Motor_Init();
	IR_Init();
    while(1)
	{
		if(IR_GetDataFlag())          //调节挡位
		{
			Command=IR_GetCommand();
			if(Command==IR_0)Speed=0;
			if(Command==IR_1)Speed=1;
			if(Command==IR_2)Speed=2;			
			if(Command==IR_3)Speed=3;
		}
		nixie(8,Speed);
		if(Speed==0)Motor_SetSpeed(0); //根据挡位设置占空比
		if(Speed==1)Motor_SetSpeed(50);//占空比：高电平占整个周期的比值
		if(Speed==2)Motor_SetSpeed(75);
		if(Speed==3)Motor_SetSpeed(100);
	}
}


