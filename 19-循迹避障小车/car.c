#include <REGX51.H>
#include "Timer0_Init.h"
#include "motor.h"
#include "chaoshengbo.h"
#include "delay.h"


//转向用制动调节，速度用使能调节
//1使能
sbit ENA = P0^2;//right
sbit ENB = P0^3;//left
unsigned char T0count3;

//舵机模块
unsigned char Targetdistance = 30;//30cm限制距离
unsigned char distance1,distance2,distance3;//三个方向距离
unsigned char angle;
sbit PWM = P0^7;//1~5转动角度代码

unsigned char Speed_A,Speed_B;//速度满20
void Car_Go()//向前直行
{
	Speed_A = 4;Speed_B = 4;
	Left_go();
	Right_go();
}

void Car_Back()//向后直行
{
	Speed_A = 4;Speed_B = 4;
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
	Speed_A = 10;Speed_B = 6;
	//Left_stop();
	Left_back();
	Right_go();
}

void Car_RightGo()//原地向前右拐
{
	Speed_B = 10;Speed_A = 6;
	//Right_stop();
	Right_back();
	Left_go();
}

void Car_LeftBack()//原地向后左拐
{
	Speed_A = 10;Speed_B = 5;
	Left_go();//Left_stop();
	Right_back();
}

void Car_RightBack()//原地向后右拐
{
	Speed_B = 10;Speed_A = 5;
	Right_go();		//Right_stop();
	Left_back();
}

void Timer0_Routine () interrupt 1
{
	static unsigned int T0count1,T0count2;      

	TL0 = 0x33;				         //Ensure that the interrupt time is constant
	TH0 = 0xFE;	
	//Adjust the speed of the right wheel
	T0count1++;
	if(T0count1 == 20)              //Come in every 500 微秒，共10ms
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
	
	//Adjust the speed of the left wheel
	T0count2++;
	if(T0count2 == 20)              //Come in every 500 微秒
	{
		T0count2 = 0;
	}
	if(T0count2 <= Speed_B)
	{
		ENB = 1;
	}
	else
	{
		ENB = 0;
	}
	
//舵机转动角度控制
	T0count3++;
	if(T0count3 == 40)              //Come in every 500 微秒
	{
		T0count3 = 0;
	}
	if(T0count3 <= angle)
	{
		 PWM = 1;
	}
	else
	{
		 PWM = 0;
	}
}

void contral_0(void)//0右90，1右45，2中间，3左45，4左90，
{
	angle = 0;   //转动90度
	delay(100);
}
void contral_4(void)//0右90，1右45，2中间，3左45，4左90，
{
	angle = 4;   //转动90度
	delay(100);
}void contral_1(void)//0右90，1右45，2中间，3左45，4左90，
{
	angle = 1;   //转动90度
	delay(100);
}


void contral(void)
{
	T0count3 = 0;
	angle = 3;   //左转动45度
	delay(400);
	distance1 = chaoshengbo();
	
	T0count3 = 0;
	angle = 1;   //右转动45度
	delay(400);
	distance2 = chaoshengbo();
	contral_0();
}

void system(void)
{
	Car_Go();
	distance3 = chaoshengbo();
	if(distance3 <= Targetdistance)
	{
		Car_Stop();
		delay(200);
		contral();
		if(distance1 >= distance2)
		{
			Car_LeftGo();
			delay(30);
			Car_Stop();
			delay(100);
			Car_Go();
		}
		else 
		{
			Car_RightGo();
			delay(30);
			Car_Stop();
			delay(100);
			Car_Go();
		}
	}
	else
	{
		Car_Go();		
	}
}


void system_xunji(void)
{
	//Car_Go();
	contral_0();
	distance3 = chaoshengbo();
	if(distance3 <= Targetdistance)
	{
		Car_Stop();
		delay(200);
		contral();
		if(distance1 >= distance2)
		{
			Car_LeftGo();
			delay(25);
			Car_Stop();
			delay(100);
			Car_Go();
			delay(25);
			Car_RightGo();
			delay(25);
			Car_Go();
			delay(25);
		}
		else 
		{
			Car_RightGo();
			delay(25);
			Car_Stop();
			delay(100);
			Car_Go();
			delay(25);
			Car_LeftGo();
			delay(25);
			Car_Go();
			delay(25);
		}
	}
	else
	{
		Car_Go();		
	}
}






