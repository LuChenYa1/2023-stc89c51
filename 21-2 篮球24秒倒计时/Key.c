#include <REGX51.H>
#include "delay.h"
#include <intrins.h>

typedef unsigned char uchar;

uchar Scan_KeyNum;

/**
  * @brief  按下第几个按键，就返回对应的值
  * @param  无
  * @retval 按键值
  */
int Key_GetState(void)
{
	uchar KeyNum=0;
	if(P3_4==0){KeyNum=1;}
	if(P3_5==0){KeyNum=2;}
	if(P3_6==0){KeyNum=3;}
	if(P3_7==0){KeyNum=4;}
	
	return KeyNum;
}


/**
  * @brief  中断时执行的函数，功能是检测按键落下并返回相应的值，
			去除了原来的delay和死循环
  * @param  无
  * @retval 无
  */
void Key_Loop(void)
{
	static uchar laststate,nowstate;
	laststate=nowstate;
	nowstate=Key_GetState();
	
	if(laststate==1&&nowstate==0)//更换10位置可以按下即变，不需松手
	{
		Scan_KeyNum=1;	
	}
	if(laststate==2&&nowstate==0)
	{
		Scan_KeyNum=2;	
	}
	if(laststate==3&&nowstate==0)
	{
		Scan_KeyNum=3;	
	}
	if(laststate==4&&nowstate==0)
	{
		Scan_KeyNum=4;	
	}
}


/**
  * @brief  返回按键键码
  * @param  无
  * @retval 键码
  */
unsigned char Key(void)
{
	uchar temp;
	temp = Scan_KeyNum;     //返回按键值前对Scan_KeyNum清零,防止不按下时返回原值
	Scan_KeyNum = 0;
	return temp;
}
