#include <REGF51RC.H>
#include "Matrixkey.h"
#include "delay.h"
#include "nixie.h"
#include "Timer0_Init.h"

#define Start 1
#define Stop  0
#define uint8_t  unsigned char 
uint8_t MatrixKeyNum, Mode, Time_Mode = 0, Count, NewState, OldState;
uint8_t State = 0, h = 23, f = 59, s = 56;
void Show0_F(void);
void Show_Time(void);
void Get_Mode(void);
void TimeSet(uint8_t  *TimeMode, Value);
void Show_Second(void);
void Show_Minute(void);
void Show_Hour(void);

void main ()
{
	nixie(8, 16);//硬件bug消除
	Timer0_Init();
    while(1)
	{
		Get_Mode();//得到按键对应模式
		//Show_Time();//显示时间
		Show0_F();
		if(MatrixKeyNum == 10)State = !State;//按下一瞬间控制启停
		if(State == Stop)//进入暂停模式
		{
			if(MatrixKeyNum == 14)//选择要设置时间的位
			{
				Time_Mode ++;
				if(Time_Mode == 7)Time_Mode = 1;
			}
			//以下语句不能放在上面的if判断中，因为当时的Mode = 10,不满足条件，无法设置时间
			if(Time_Mode == 1 || Time_Mode == 2)//设置时
			{
			 	if(Mode < 10)TimeSet(&h, Mode); 
			}
			else if(Time_Mode == 3 || Time_Mode == 4)//设置分
			{
				if(Mode < 10)TimeSet(&f, Mode);
			}
			else if(Time_Mode == 5 || Time_Mode == 6)//设置秒
			{
				if(Mode < 10)TimeSet(&s, Mode);
			}
			//判断时间是否越界
			if(h > 23)
			{
				h = 0; Mode = 0;//特例：刷新键值，防止小时的个位显示原来的值
			}
			if(f >= 60)f = 0;
			if(s >= 60)s = 0;
		}
	}
}

//根据数字按键设置时间
void TimeSet(uint8_t  *TimeMode, Value)
{
	if(Time_Mode == 1 || Time_Mode == 3 || Time_Mode == 5)*TimeMode = *TimeMode % 10 + Value * 10;
	else if(Time_Mode == 2 || Time_Mode == 4 || Time_Mode == 6)*TimeMode = *TimeMode / 10 *10 + Value;
}


//定时中断
void Timer0_Routine () interrupt 1
{
	static unsigned int T0count1, T0count2;     //静态局部变量，保证不会被重新赋值

	TL0 = 0x66;				          //确保中断时间不变
	TH0 = 0xFC;	
	T0count1++;
	if(T0count1 == 900)               //每隔1秒进入if，灯亮灭变化
	{
		T0count1 = 0;                 //这一句不小心被删掉了，导致浪费时间找bug
		if(State == Start)
		{
			if(Mode == 11)//顺计时
			{
				s ++;
				if(s == 60)
				{
					s = 0;
					f ++;
					if(f == 60)
					{
						f = 0;
						h ++;
						if(h == 24) h = 0;
					}
				}
			}
			else if(Mode == 12)//倒计时
			{
				s--;
				if(s == 255)
				{
					s = 59;
					f--;
					if(f == 255)
					{
						f = 59;
						h--;
						if(h == 255)h = 23;
					}
				}				
			}
			else if(Mode == 13)//清零
			{
				h = 0; f = 0; s = 0;
			}
		}
		
	}
	T0count2 ++;
	if(T0count2 == 20)
	{
		T0count2 = 0;
		MatrixKey_Loop();
	}
}

//由按键得到模式，不被刷新为0
void Get_Mode(void)
{
	MatrixKeyNum = MatrixKey();
	if(MatrixKeyNum == 1)Mode = 1;
	else if(MatrixKeyNum == 2)Mode = 2;
	else if(MatrixKeyNum == 3)Mode = 3;
	else if(MatrixKeyNum == 4)Mode = 4;
	else if(MatrixKeyNum == 5)Mode = 5;
	else if(MatrixKeyNum == 6)Mode = 6;
	else if(MatrixKeyNum == 7)Mode = 7;
	else if(MatrixKeyNum == 8)Mode = 8;
	else if(MatrixKeyNum == 9)Mode = 9;
	//else if(MatrixKeyNum == 10)Mode = 10;
	else if(MatrixKeyNum == 11)Mode = 11;
	else if(MatrixKeyNum == 12)Mode = 12;
	else if(MatrixKeyNum == 13)Mode = 13;
	else if(MatrixKeyNum == 14)Mode = 14;
	else if(MatrixKeyNum == 15)Mode = 15;
	else if(MatrixKeyNum == 16)Mode = 0;
}

//显示时间
void Show_Time(void)
{
	nixie(3, 17);//显示分隔号
	nixie(6, 17);
	if(State == Start)//运行模式正常显示时间
	{
		Show_Hour();
		Show_Minute();
		Show_Second();
	}
	else if(State == Stop)//达到闪烁效果
	{
		if(Time_Mode == 1 || Time_Mode == 2)//时闪烁
		{
			Count ++;
			Count %= 16;
			if(Count > 10)Show_Hour();
			else 
			{
				nixie(1, 16);
				nixie(2, 16);
			}
			Show_Minute();
			Show_Second();
		}
		 if(Time_Mode == 3 || Time_Mode == 4)//分闪烁
		{
			Count ++;
			Count %= 16;
			if(Count > 10)Show_Minute();
			else 
			{
				nixie(3, 16);
				nixie(4, 16);
			}
			Show_Hour();
			Show_Second();
		}
		if(Time_Mode == 5 || Time_Mode == 6)//秒闪烁
		{
			Count ++;
			Count %= 16;
			if(Count < 10)Show_Second();
			else 
			{
				nixie(5, 16);
				nixie(6, 16);
			}
			Show_Hour();
			Show_Minute();
		}
		if(Time_Mode == 0)
		{
			Show_Hour();
			Show_Minute();
			Show_Second();
		}
	}
}

//显示时间代码封装
void Show_Hour(void)
{
	nixie(1, h /10);
	nixie(2, h % 10);	
}

void Show_Minute(void)
{
	nixie(4, f /10);
	nixie(5, f % 10);	
}

void Show_Second(void)
{
	nixie(7, s /10);
	nixie(8, s % 10);	
}

//由对应按键显示0~F
void Show0_F(void)
{
	if(Mode == 1)nixie(1, 1);
	else if(Mode == 2)nixie(1, 2);
	else if(Mode == 3)nixie(1, 3);
	else if(Mode == 4)nixie(1, 4);
	else if(Mode == 5)nixie(1, 5);
	else if(Mode == 6)nixie(1, 6);
	else if(Mode == 7)nixie(1, 7);
	else if(Mode == 8)nixie(1, 8);
	else if(Mode == 9)nixie(1, 9);
	else if(Mode == 10)nixie(1, 10);
	else if(Mode == 11)nixie(1, 11);
	else if(Mode == 12)nixie(1, 12);
	else if(Mode == 13)nixie(1, 13);
	else if(Mode == 14)nixie(1, 14);
	else if(Mode == 15)nixie(1, 15);
	else if(Mode == 16)nixie(1, 0);
}           
            
            