#include <REGX51.H>
#include "Timer1_Init.h"
#include "delay.h"
#include "buzzer.h"


unsigned int FreqSelect,MusicSelect;//频率选择位、乐谱序列选择位
#define SPEED 700  //以四分音符为基准 
sbit Buzzer = P2^5;//驱动芯片里对应蜂鸣器的IO口


void main ()
{
	Timer1_Init();//定时器初始化
	while(1)
	{
//		if(Music_skycity[MusicSelect]!=0xff)   //0xff是乐谱结束标志位
//		{
//			FreqSelect=Music_skycity[MusicSelect];
//			MusicSelect++;
//			delay(SPEED/32*Music_skycity[MusicSelect]);//音时
//			MusicSelect++;
//			TR1=0;             //定时暂停，让两个音之间有停顿
//			delay(5);
//			TR1=1;
//		}
//		else                    //终止音乐
//		{
//			TR1=0;            
//			while(1);
//		}
		if(Music_qifengle[MusicSelect]!=0xff)   //0xff是乐谱结束标志位
		{
			FreqSelect=Music_qifengle[MusicSelect];
			MusicSelect++;
			delay(SPEED/32*Music_qifengle[MusicSelect]);//音时
			MusicSelect++;
			TR1=0;             //定时暂停，让两个音之间有停顿
			delay(5);
			TR1=1;
		}
		else                    //终止音乐
		{
			TR1=0;            
			while(1);
		}
	}
}



//中断所执行程序模板

void Timer1_Routine () interrupt 3
{
	if(Freq[FreqSelect])             //频率不为0时允许蜂鸣演奏
	{
		TL1 = Freq[FreqSelect]%256;	 //初始化中的值仅存在一次，这里的TL0和TH0才是持续存在的定时周期
		TH1 = Freq[FreqSelect]/256;	
		Buzzer=!Buzzer;
	}
	 
}
