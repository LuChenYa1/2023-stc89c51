#include <REGF51RC.H>
#include "Matrixkey.h"
#include "delay.h"
#include "Timer0_Init.h"
#include "LCD1602.h"

#define Start 1
#define Stop  0
#define uint8_t  unsigned char 
	
uint8_t MatrixKeyNum, Mode, Time_Mode = 0, Count, Flag_Act;
uint8_t State = 0, h = 23, f = 59, s = 56, i0;

//char code name[16] = {"Zhong Qian Hui "};
char i1 = 1, i2 = 2, i3 = 3, i4 = 4, i5 = 5, i6 = 6, i7 = 7, i8 = 8, i9 = 9, i10 = 10, i11 = 11, i12 = 12, i13 = 13, i14 = 14, i15 = 15, i16 = 16;

char code name[14][16] = {{"Zhong Qian Hui "}, {"hong Qian Hui Z"}, {"ong Qian Hui Zh"}, {"ng Qian Hui Zho"}, {"g Qian Hui Zhon"}
				, {" Qian Hui Zhong"}, {"Qian Hui Zhong "}, {"ian Hui Zhong Q"}, {"an Hui Zhong Qi"}, {"n Hui Zhong Qia"}, 
					{" Hui Zhong Qian"}, {"ui Zhong Qian H"}, {"i Zhong Qian Hu"}, {" Zhong Qian Hui"}};

void Show_Name(void);
void Show_Time(void);
void Show_TimeAct(void);				
void Get_Mode(void);
void TimeSet(uint8_t  *TimeKind, Value);
void Show_Second(void);
void Show_Minute(void);
void Show_Hour(void);
//void Show_NameAct(void);

void main ()
{
//	nixie(8, 16);//硬件bug消除
	Timer0_Init();
	LCD_Init();
	LCD_ShowString(1, 1, "Zhong Qian Hui");
    while(1)
	{
		Get_Mode();//得到按键对应模式
		Show_Time();
		if(MatrixKeyNum == 15)Flag_Act = !Flag_Act;
//		if(Flag_Act == 0)Show_Name();//静态显示名字
//		else if(Flag_Act == 1)Show_NameAct();//动态显示名字
		if(Flag_Act == 0)Show_Time();//静态显示时间
		else if(Flag_Act == 1)Show_TimeAct();//动态显示时间
		
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
void TimeSet(uint8_t  *TimeKind, Value)
{
	if(Time_Mode == 1 || Time_Mode == 3 || Time_Mode == 5)*TimeKind = *TimeKind % 10 + Value * 10;
	else if(Time_Mode == 2 || Time_Mode == 4 || Time_Mode == 6)*TimeKind = *TimeKind / 10 *10 + Value;
}


//定时中断
void Timer0_Routine () interrupt 1
{
	static unsigned int T0count1, T0count2, T0count3;     //静态局部变量，保证不会被重新赋值

	TL0 = 0x66;				          //确保中断时间不变
	TH0 = 0xFC;	
	T0count1++;
	if(T0count1 == 700)               //每隔1秒进入if，灯亮灭变化
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
	if(T0count2 == 20)//定时器扫描矩阵键盘
	{
		T0count2 = 0;
		MatrixKey_Loop();
	}
	T0count3 ++;
	if(T0count3 == 700)
	{
		T0count3 = 0;
//		if(Flag_Act == 1)i0 ++;
//		i0 %= 14;
		i1--;i2--;i3--;i4--;i5--;i6--;i7--;i8--;i9--;i10--;i11--;i12--;i13--;i14--;i15--;i16--;
		if(i1 == 0)i1 = 16;
		if(i2 == 0)i2 = 16;
		if(i3 == 0)i3 = 16;
		if(i4 == 0)i4 = 16;
		if(i5 == 0)i5 = 16;
		if(i6 == 0)i6 = 16;
		if(i7 == 0)i7 = 16;
		if(i8 == 0)i8 = 16;
		if(i9 == 0)i9 = 16;
		if(i10 == 0)i10 = 16;
		if(i11 == 0)i11 = 16;
		if(i12 == 0)i12 = 16;
		if(i13 == 0)i13 = 16;
		if(i14 == 0)i14 = 16;
		if(i15 == 0)i15 = 16;
		if(i16 == 0)i16 = 16;
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
	//else if(MatrixKeyNum == 10)Mode = 10;//该句不能加
	else if(MatrixKeyNum == 11)Mode = 11;
	else if(MatrixKeyNum == 12)Mode = 12;
	else if(MatrixKeyNum == 13)Mode = 13;
	else if(MatrixKeyNum == 14)Mode = 14;
	else if(MatrixKeyNum == 15)Mode = 15;
	else if(MatrixKeyNum == 16)Mode = 0;
}


void Show_Name(void)
{
	LCD_ShowString(1, 1, "Zhong Qian Hui ");
}


//滚屏显示名字
void Show_NameAct(void)
{
	//动态显示名字
	LCD_ShowString(1,1, name[i0]);
//	LCD_ShowString(1,1, "                ");
//	LCD_ShowChar(1, i1, ' ');
//	LCD_ShowChar(1, i1, name[0]);
//	LCD_ShowChar(1, i2, ' ');
//	LCD_ShowChar(1, i2, name[1]);
//	LCD_ShowChar(1, i3, ' ');
//	LCD_ShowChar(1, i3, name[2]);
//	LCD_ShowChar(1, i4, ' ');
//	LCD_ShowChar(1, i4, name[3]);
//	LCD_ShowChar(1, i5, ' ');
//	LCD_ShowChar(1, i5, name[4]);
//	LCD_ShowChar(1, i6, ' ');
//	LCD_ShowChar(1, i6, name[5]);
//	LCD_ShowChar(1, i7, ' ');
//	LCD_ShowChar(1, i7, name[6]);
//	LCD_ShowChar(1, i8, ' ');
//	LCD_ShowChar(1, i8, name[7]);
//	LCD_ShowChar(1, i9, ' ');
//	LCD_ShowChar(1, i9, name[8]);
//	LCD_ShowChar(1, i10, ' ');
//	LCD_ShowChar(1, i10, name[9]);
//	LCD_ShowChar(1, i11, ' ');
//	LCD_ShowChar(1, i11, name[10]);
//	LCD_ShowChar(1, i12, ' ');
//	LCD_ShowChar(1, i12, name[11]);
//	LCD_ShowChar(1, i13, ' ');
//	LCD_ShowChar(1, i13, name[12]);
//	LCD_ShowChar(1, i14, ' ');
//	LCD_ShowChar(1, i14, name[13]);
//	LCD_ShowChar(1, i15, ' ');
//	LCD_ShowChar(1, i15, name[14]);
//	LCD_ShowChar(1, i16, ' ');
//	LCD_ShowChar(1, i16, name[15]);
}

void Show_TimeAct(void)
{
	LCD_ShowChar(2, i1, ' ');
	LCD_ShowNum(2, i1, h/10, 1);
	LCD_ShowChar(2, i2, ' ');
	LCD_ShowNum(2, i2, h%10, 1);
	LCD_ShowChar(2, i3, ' ');
	LCD_ShowChar(2, i3, '-');//显示分隔号
	LCD_ShowChar(2, i4, ' ');
	LCD_ShowNum(2, i4, f/10, 1);
	LCD_ShowChar(2, i5, ' ');
	LCD_ShowNum(2, i5, f%10, 1);
	LCD_ShowChar(2, i6, ' ');
	LCD_ShowChar(2, i6, '-');
	LCD_ShowChar(2, i7, ' ');
	LCD_ShowNum(2, i7, s/10, 1);
	//LCD_ShowChar(2, i8, ' ');
	LCD_ShowNum(2, i8, s%10, 1);
	LCD_ShowChar(2, i9, ' ');
	LCD_ShowChar(2, i10, ' ');
	LCD_ShowChar(2, i11, ' ');
	LCD_ShowChar(2, i12, ' ');
	LCD_ShowChar(2, i13, ' ');
	LCD_ShowChar(2, i14, ' ');
	LCD_ShowChar(2, i15, ' ');
	LCD_ShowChar(2, i16, ' ');
}	


//显示时间
void Show_Time(void)
{
	LCD_ShowChar(2, 3, '-');//显示分隔号
	LCD_ShowChar(2, 6, '-');
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
			Count %= 3;
			if(Count < 2)Show_Hour();
			else 
			{
				 LCD_ShowString(2, 1, "  ");
			}
			Show_Minute();
			Show_Second();
		}
		 if(Time_Mode == 3 || Time_Mode == 4)//分闪烁
		{
			Count ++;
			Count %= 3;
			if(Count < 2)Show_Minute();
			else 
			{
				LCD_ShowString(2, 4, "  ");
			}
			Show_Hour();
			Show_Second();
		}
		if(Time_Mode == 5 || Time_Mode == 6)//秒闪烁
		{
			Count ++;
			Count %= 3;
			if(Count < 2)Show_Second();
			else 
			{
				LCD_ShowString(2, 7, "  ");
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
	LCD_ShowNum(2, 1, h, 2);	
}

void Show_Minute(void)
{
	LCD_ShowNum(2, 4, f, 2);
}

void Show_Second(void)
{
	LCD_ShowNum(2, 7, s, 2);
}   
            