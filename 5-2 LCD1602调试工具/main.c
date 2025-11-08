#include <REGX51.H>
#include "LCD1602.h"
#include "delay.h"
void main()
{
	int result;
	LCD_Init();
	while(1)
	{
		result++;
		LCD_ShowNum(1,1,result,4);
		delay(200);
	}

	LCD_ShowChar(1,1,'B');
//	LCD_ShowString(1,2,"hello");
//	LCD_ShowNum(1,7,123,2);       //位数从后往前读
//	LCD_ShowHexNum(1,9,0x7d,2);
//	LCD_ShowBinNum(2,1,0x01,8);   //输入十六进制，输出二进制
}