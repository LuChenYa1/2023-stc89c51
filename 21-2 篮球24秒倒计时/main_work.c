#include <REGF51RC.H>
#include "Timer0_Init.h"
#include "nixie.h"
#include "Key.h"

typedef unsigned char uint8_t;
#define  FirstTimeSet0  if(NewMode != OldMode)Time_24 = 0  //刚刚重新按下该按键时，对时间重新赋值，连续按下时不再变化

uint8_t Time_24 = 0;
uint8_t KeyNum, Mode, NewMode, OldMode, Flag_0;
unsigned char Set_Mode(void);
void Get_Mode(void);
void Show_Time(uint8_t time);

void main()
{
	Timer0_Init();
	while(1)
	{
		Get_Mode();
		if(Mode == 1)//顺计时
		{
			Show_Time(Time_24);
			Flag_0 = 1;
		}
		else if(Mode == 2)//倒计时
		{
			if(NewMode != OldMode)Time_24 = 24 - Time_24;
			Show_Time(24 - Time_24);
			Flag_0 = 1;
		}
		else if(Mode == 3)//归零且暂停
		{
			FirstTimeSet0;
			Flag_0 = 0;
			Show_Time(Time_24);
		}
		else if(Mode == 4)//回表24且暂停
		{
			FirstTimeSet0;
			Flag_0 = 0;
			Show_Time(24 - Time_24);
		}
	}
}


//定时中断函数
void Timer0_Routine () interrupt 1
{
	static unsigned int T0count;     //静态局部变量，保证不会被重新赋值

	TL0 = 0x66;				         //确保中断时间不变
	TH0 = 0xFC;	
	T0count++;
	Key_Loop();
	
	if(T0count == 1000)              //每隔1秒进入if，灯亮灭变化
	{
		T0count = 0;
		if(Flag_0 == 1)              //启停
		{
			Time_24 ++;				 //时间一直从0增加到24，循环该过程
			Time_24 %= 25; 
		}
	}
}


//扫描得到新老模式值
void Get_Mode (void)
{
	OldMode = Mode;
	NewMode = Set_Mode();
}


//根据按键设置模式
unsigned char Set_Mode(void)
{
	KeyNum = Key();
	if(KeyNum == 1)Mode = 1;      //按键按下即转换模式
	else if(KeyNum == 2)Mode = 2;
	else if(KeyNum == 3)Mode = 3;
	else if(KeyNum == 4)Mode = 4;
	return Mode;
}

//显示函数
void Show_Time(uint8_t time)
{
	nixie(1, time / 10);
	nixie(2, time % 10);
}
