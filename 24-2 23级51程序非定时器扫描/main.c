#include <REGX51.H>
#include "Matrixkey.h"
#include "delay.h"
#include "nixie.h"
#include "Key.h"

sbit LED1 = P2^0;
//#define LED1 P2^0

unsigned char KeyNum, Nixie_Num = 6, MatrixKeyNum,
			  Hour = 23, Matrix_Value, Count = 0;   			  

void main ()
{

	while(1)
	{
		//数码管显示
		nixie(1, Nixie_Num);				
		nixie(8, Hour/10);				
		nixie(7, Hour%10);				
		nixie(6, 17);//-                   
		nixie(5, 2);
		nixie(4, 9);
		nixie(3, 17);//-
		nixie(2, 5);
		
		//独立按键判断
		KeyNum = Key();					
		if(KeyNum)
		{
			if(KeyNum == 1)LED1 = !LED1;~
			//~1001 = 0110
			//!(真事件) = 假事件
			//!(1001) = 0
			
			if(KeyNum == 2)				
			{
				if(Nixie_Num == 0)Nixie_Num = 9;
				else Nixie_Num--;//加else， 改9
			}
			
			if(KeyNum == 3)				
			{
				Nixie_Num++;			
				if(Nixie_Num == 10)Nixie_Num = 0;
			}
		}
		
		
		//矩阵键盘判断
		MatrixKeyNum = Matrixkey();	
		
		if(MatrixKeyNum)                            	  
		{ 
			if(MatrixKeyNum <= 10)//按键功能分区		      	  	  
			{
				if(Count < 2)     		          
				{
					Matrix_Value *= 10;                 
					Matrix_Value += MatrixKeyNum % 10; 
					Count++; 
					//nixie();
				}
			}
				
			else if(MatrixKeyNum == 13)		         
			{
				Hour = Matrix_Value;	
				Count = 0;//为下一次输入做准备  		
				Matrix_Value = 0; 		
			}
		}	
	}
}
