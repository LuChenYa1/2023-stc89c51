#include <REGX51.H>
#include "DS1302.h"
#include "LCD1602.h"
#include "Key.h"
#include "Timer0_Init.h"
 

unsigned char KeyNum,MODE,TimeTypeSelect,FlashFlag;
char DS1302_Time[]={23,4,4,11,20,55,2};
//unsigned char i,j;//循环控制变量，但失败了

void TimeSet();//调整时间函数声明

void main ()
{
	LCD_Init();
	Timer0_Init();
	DS1302_Init();
	
	LCD_ShowString(1,1,"  -  -  ");
	LCD_ShowString(2,1,"  :  :  ");
	
    DS1302_SetTime(); //设置时间
	while (1)
 	{
		KeyNum=Key();
    	if(KeyNum)
		{
			if(KeyNum==1)  //按键一的功能是转换调整模式1和显示模式0
			{
				if(MODE==0)MODE=1;
				else if(MODE==1)
				{
					MODE=0; 
					DS1302_SetTime();//显示数值更新后的时间
				}
			}
		}
		switch(MODE)
		{
			case 0:DS1302_ShowTime();break;
			//DS1302_SetTime();放在这里会使时间不断被刷新为同一个值，导致时间不会变化
			case 1:TimeSet();break;//调整时间
		}
	}
}
void TimeSet()
{
	if(KeyNum==2)//按键2的功能是转换要调整的数据类型
	{
		TimeTypeSelect++;
		TimeTypeSelect%=6;
	}
	LCD_ShowNum(2,10,TimeTypeSelect,2);
	LCD_ShowNum(2,15,FlashFlag,2);
	if(KeyNum==3)//按键3对要修改的数据进行增加操作
	{
		DS1302_Time[TimeTypeSelect]++;
		/***********防止时间越界*******************/
		if(DS1302_Time[0]==100)DS1302_Time[0]=0;
		if(DS1302_Time[1]==13)DS1302_Time[1]=1;
		
		/************天数判断**********************/
		if(DS1302_Time[1]==1||DS1302_Time[1]==3
		||DS1302_Time[1]==5||DS1302_Time[1]==7||DS1302_Time[1]==8
		||DS1302_Time[1]==10||DS1302_Time[1]==12 )
		{
			if(DS1302_Time[2]==32)DS1302_Time[2]=1;
		}
		if(DS1302_Time[1]==4||DS1302_Time[1]==6
		||DS1302_Time[1]==9||DS1302_Time[1]==11)
		{
			if(DS1302_Time[2]==31)DS1302_Time[2]=1;
		}
		/************二月天数判断*******************/
		if(DS1302_Time[1]==2)
		{
			if(DS1302_Time[0]%4==0)if(DS1302_Time[2]==30)DS1302_Time[2]=1;//闰年
			if(DS1302_Time[0]%4!=0)if(DS1302_Time[2]==29)DS1302_Time[2]=1;//非闰年
		}
		/************调整时、分、秒、星期***********/
		if(DS1302_Time[3]==24)DS1302_Time[3]=0;
		if(DS1302_Time[4]==60)DS1302_Time[4]=0;
		if(DS1302_Time[5]==60)DS1302_Time[5]=0;
		if(DS1302_Time[6]==8)DS1302_Time[6]=1;
	}
	if(KeyNum==4)//按键4对要修改的数据进行减少操作
	{
		DS1302_Time[TimeTypeSelect]--;
		/**********防止时间越界********************/
		if(DS1302_Time[0]<0)DS1302_Time[0]=100;
		if(DS1302_Time[1]<1)DS1302_Time[1]=12;
		
		/************天数判断**********************/
		if(DS1302_Time[1]==1||DS1302_Time[1]==3
		||DS1302_Time[1]==5||DS1302_Time[1]==7||DS1302_Time[1]==8
		||DS1302_Time[1]==10||DS1302_Time[1]==12 )
		{
			if(DS1302_Time[2]<1)DS1302_Time[2]=31;
		}
		if(DS1302_Time[1]==4||DS1302_Time[1]==6
		||DS1302_Time[1]==9||DS1302_Time[1]==11)
		{
			if(DS1302_Time[2]<1)DS1302_Time[2]=30;
		}
		/************二月天数判断******************/
		if(DS1302_Time[1]==2)
		{
			if(DS1302_Time[0]%4==0)//闰年
			{
				if(DS1302_Time[2]<1)DS1302_Time[2]=29;
				if(DS1302_Time[2]>29)DS1302_Time[2]=1;
			}
			if(DS1302_Time[0]%4!=0)//非闰年
			{
				if(DS1302_Time[2]<1)DS1302_Time[2]=28;
				if(DS1302_Time[2]>28)DS1302_Time[2]=1;
			}
		}
		/************调整时、分、秒、星期***********/
		if(DS1302_Time[3]<0)DS1302_Time[3]=23;
		if(DS1302_Time[4]<0)DS1302_Time[4]=59;
		if(DS1302_Time[5]<0)DS1302_Time[5]=59;
		if(DS1302_Time[6]<1)DS1302_Time[6]=7;
	}
	/*************想利用循环实现闪烁效果，但失败了********/
//	for(j=1;j<3;j++)
//	{
//		 for(i=0;i<3;i++)
//		{
//			if(TimeSelect==i && FlashFlag==1) LCD_ShowString(j,1+3i,"  ");
//			else LCD_ShowNum(j,1+3i,DS1302_Time[i],2);
//		}
//	}
	/*****************达到闪烁效果********************/
	if(TimeTypeSelect==0&&FlashFlag==1)LCD_ShowString(1,1,"  ");
	else LCD_ShowNum(1,1,DS1302_Time[0],2);  //显示年
	if(TimeTypeSelect==1&&FlashFlag==1)LCD_ShowString(1,4,"  ");
	else LCD_ShowNum(1,4,DS1302_Time[1],2);  //显示月
	if(TimeTypeSelect==2&&FlashFlag==1)LCD_ShowString(1,7,"  ");
	else LCD_ShowNum(1,7,DS1302_Time[2],2);  //显示日
	if(TimeTypeSelect==3&&FlashFlag==1)LCD_ShowString(2,1,"  ");
	else LCD_ShowNum(2,1,DS1302_Time[3],2);  //显示时
	if(TimeTypeSelect==4&&FlashFlag==1)LCD_ShowString(2,4,"  ");
	else LCD_ShowNum(2,4,DS1302_Time[4],2);  //显示分
	if(TimeTypeSelect==5&&FlashFlag==1)LCD_ShowString(2,7,"  ");
	else LCD_ShowNum(2,7,DS1302_Time[5],2);  //显示秒
	if(TimeTypeSelect==6&&FlashFlag==1)LCD_ShowString(2,12,"  ");
	else LCD_ShowNum(1,12,DS1302_Time[6],1);  //显示星期
	if(TimeTypeSelect==6&&FlashFlag==1)LCD_ShowString(1,12,"  ");
	else LCD_ShowNum(1,12,DS1302_Time[6],1);  //显示星期
}


/**************每隔0.5秒闪烁一次************/
void Timer0_Routine () interrupt 1
{
	static unsigned int T0count;     //静态局部变量，保证不会被重新赋值

	TL0 = 0x66;				         //确保中断时间不变
	TH0 = 0xFC;	
	T0count++;
	if(T0count == 500)              //每隔500微秒进入if，灯亮灭变化
	{
		T0count=0;
		FlashFlag=!FlashFlag;
	}
}
