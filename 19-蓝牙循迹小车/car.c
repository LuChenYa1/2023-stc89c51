#include <REGX51.H>
#include "Timer0_Init.h"
#include "motor.h"

//转向用制动调节，速度用使能调节
//1使能
sbit ENA = P0^2;//right
sbit ENB = P0^3;//left

unsigned char Speed_A,Speed_B;
void Car_Go()//向前直行
{
	Speed_A = 20;Speed_B = 20;
	Left_go();
	Right_go();
}

void Car_Back()//向后直行
{
	Speed_A = 20;Speed_B = 20;
	Left_back();
    Right_back();
}

void Car_Stop()//停止
{
	Speed_A = 0;Speed_B = 0;
	Left_stop();
	Right_stop();
}

void Car_LeftGo()//原地向前左拐
{
	Speed_A = 50;Speed_B =20;
	//Left_stop();
	Left_back();
	Right_go();
}

void Car_RightGo()//原地向前右拐
{
	Speed_B = 50;Speed_A=20;
	//Right_stop();
	Right_back();
	Left_go();
}

void Car_LeftBack()//原地向后左拐
{
	Speed_A = 50;Speed_B =20;
	Left_go();//Left_stop();
	Right_back();
}

void Car_RightBack()//原地向后右拐
{
	Speed_B = 50;Speed_A = 20;
	Right_go();		//Right_stop();
	Left_back();
}

void Timer0_Routine () interrupt 1
{
	static unsigned int T0count1,T0count2;      

	TL0 = 0xA4;				         //Ensure that the interrupt time is constant
	TH0 = 0xFF;	
	//Adjust the speed of the right wheel
	T0count1++;
	if(T0count1 == 100)              //Come in every 100 微秒
	{
		T0count1=0;
	}
	if(T0count1 <= Speed_A)
	{
		ENA = 1;
		//ENB = 1;
	}
	else
	{
		ENA = 0;
		//ENB = 0;
	}
	T0count2++;
	if(T0count2 == 100)              //Come in every 100 微秒
	{
		T0count2=0;
	}
	if(T0count2 <= Speed_B)
	{
		ENB = 1;
	}
	else
	{
		ENB = 0;
	}

}




