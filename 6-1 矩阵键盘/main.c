#include <REGX51.H>
#include <Matrixkey.h>
#include <LCD1602.h>
#include "nixie.h"

void main ()
{
	unsigned int KeyNum;
	LCD_Init();
	
	while(1)
	{
		KeyNum=Matrixkey();
		
		if(KeyNum)            //循环很快，要除去0对其他数字的干扰，函数还没来得及执行，KeyNum就会被赋值0
		{
			//LCD_ShowNum(1,1,KeyNum,2);
			nixie(1, KeyNum);
		}
	}
}

