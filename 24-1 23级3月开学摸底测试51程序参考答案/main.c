#include <REGX51.H>
#include "Matrixkey.h"
#include "Timer0_Init.h"
#include "delay.h"
#include "nixie.h"
#include "Key.h"

sbit LED1 = P2^0;

unsigned char KeyNum, Nixie_Num = 6, Hour = 23, MatrixKeyNum, Matrix_Value = 0, Count = 0;   			  

void main ()
{
	Timer0_Init();
	
	while(1)
	{
		KeyNum = Key();					//不断循环扫描四个独立按键是否按下
		if(KeyNum)
		{
			if(KeyNum == 1)LED1 = !LED1;//题1：按键1控制灯的亮灭
			
			if(KeyNum == 2)				//题2：按键2控制数字减1
			{
				if(Nixie_Num == 0)Nixie_Num = 10;//越界判断
				Nixie_Num--;			//“6”加加
			}
			
			if(KeyNum == 3)				//题2：按键3控制数字加1
			{
				Nixie_Num++;			//“6”减减
				if(Nixie_Num == 10)Nixie_Num = 0;//越界判断
			}
		}
		
		MatrixKeyNum = Matrixkey();		//题4：不断循环扫描矩阵键盘是否按下
		if(MatrixKeyNum)                            	  
		{ 
			if(MatrixKeyNum <= 10)		//按键S1到S10分别代表数字1到9到0             	  	  
			{
				if(Count < 2)     		//目标是输入两位数字，Count用于计按下次数，按下两次后停止Matrix_Value的增加               
				{
					Matrix_Value *= 10;                 
					Matrix_Value += MatrixKeyNum % 10; //每按一次，计数加一         
					Count++;                      
				}
			}
				
			if(MatrixKeyNum == 13)		//按键S13确认输入完成                    
			{
				Hour = Matrix_Value;	//转存输入的值到“hour”中，方便原变量清零
				Count = 0;		  		//此时可将按下次数清零，准备下次输入
				Matrix_Value = 0; 		//值清零，准备下次从0开始输入
			}
		}	
		
		nixie(1,Nixie_Num);				//将按键控制的数字“6”变化后的值显示出来
		
		nixie(8, Hour/10);				//数码管特性，函数只能控制一位数字的显示，所以要写两次
		nixie(7, Hour%10);				//取余、取整
		nixie(6, 17);                   //题3：动态数码管显示
		nixie(5, 2);
		nixie(4, 9);
		nixie(3, 17);
		nixie(2, 5);
	}
}

void Timer0_Routine () interrupt 1
{
	static unsigned int T0count1,T0count2;     

	TL0 = 0x66;				        
	TH0 = 0xFC;	
	
	T0count1++;
	if(T0count1 == 20)              
	{
		T0count1=0;
		Key_Loop();
	}

	T0count2++;
	if(T0count2 == 2)               
	{
		T0count2=0;
		nixie_Loop();
	}
}
