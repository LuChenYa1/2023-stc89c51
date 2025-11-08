#include <REGX51.H>
#include "DS1302.h"
#include "LCD1602.h"
 
unsigned char DS1302_Time[]={24, 1, 19, 14, 40, 55, 5};

void main ()
{
	LCD_Init();
	DS1302_Init();
	
	LCD_ShowString(1,1,"  -  -  ");
	LCD_ShowString(2,1,"  :  :  ");
    //DS1302_WriteByte(0x80,0x08); 
	//输入的是十六进制，以BCD码形式存储进芯片，
	//BCD码本质是十进制的十位和个位，不接受大于九的单位数，	
	//因此带字母的十六进制无法转成BCD码，数据存入失败显示芯片默认值
	//芯片将BCD码以十六进制形式返回IO线
	//用四位二进制数表示一位十进制数
	//BCD芯片内自增：0x09、0x10、0x11、0x12，
	//将其转为十六进制为：0x09、0x10、0x11、0x12
	//实际上转成十进制由9突变成了16、17、18、、、
	//显示数字时用的是十进制
	
	DS1302_SetTime();
	while (1)
 	{
		DS1302_ReadTime();
		LCD_ShowNum(1,1,DS1302_Time[0],2);   //显示年
		LCD_ShowNum(1,4,DS1302_Time[1],2);   //显示月
		LCD_ShowNum(1,7,DS1302_Time[2],2);   //显示日
		LCD_ShowNum(2,1,DS1302_Time[3],2);   //显示时
		LCD_ShowNum(2,4,DS1302_Time[4],2);   //显示分
		LCD_ShowNum(2,7,DS1302_Time[5],2);   //显示秒
		LCD_ShowNum(1,12,DS1302_Time[6],1);  //显示星期
	}
}
 