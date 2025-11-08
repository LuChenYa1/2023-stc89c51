#include <REGX51.H>
#include "LCD1602.h"
#include "delay.h"


void main ()
{
	LCD_Init();
	LCD_ShowChar(1,1,'\\');    //显示中文钱符号，本质是反斜杠的码值在字模对照表中对应了‘钱’
	LCD_ShowChar(1,2,0x7e);    //字模对照表将一些常用的符号替换了原来的码值对照表，这里本来显示~，现在显示->
	LCD_ShowString(1,16,"asdhertyuadfdgf");
	LCD_ShowNum(1,5,234,3);
	LCD_ShowSignedNum(2,1,234,3);
	LCD_ShowHexNum(2,5,0x8e,2);
	LCD_ShowBinNum(2,8,0x8e,8);
	
    while(1)
	{
		LCD_WriteCommand(0x18);//向左移屏
		delay(200);            //保持显示
	}
}

