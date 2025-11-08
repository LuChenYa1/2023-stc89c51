#include <REGX51.H>
#include "delay.h"
#define MatrixLED_lie P0       //提高可读性，方便后期替换操作寄存器

typedef  unsigned char uchar;
extern int i;                  //变量名在头文件中定义要加extern，防止重定义，告诉系统这是同一个变量

//对位进行重命名，不能用_,要用^
sbit SER = P3^4;               //串行数据，一次赋值一位
sbit RCK = P3^5;               //寄存器时钟，存满8位后触发RCK=1，将八位数据并行输入到DH~DA（D7到D1）
sbit SCK = P3^6;               //串行时钟，每输入一位就触发该时钟将数据上移，一直移到最高位DH


/**
  * @brief    初始化寄存器时钟和串行时钟
  * @param    无
  * @retval   无
  */
void MatrixLED_Init()
	{
		SCK=0;        //SCK需要手动复位和开启
		RCK=0;        //RCK需要手动复位和开启
	}
	
	
/**
  * @brief  顺序将byte从高到低的数值赋值给SER,再传递给D7到D0
  * @param  一列显示的段码，1亮
  * @retval 无
  */
void _74HC595_SendByte(uchar byte)
{
	for( i=0;i<8;i++)
	{
		SER = byte & (0x80>>i);  
		SCK = 1;  //上移一位
		SCK = 0;  //复位
	}
	RCK = 1;      //并行输入8位
	RCK = 0;      //复位
	//不用自己清零SER，会有问题，直接再次赋值就可以
}


/**
  * @brief  在第几列显示对应段码
  * @param  列数，段码
  * @retval 无
  */

void MatrixLED_ShowColumn(uchar Column,Data)
{
	_74HC595_SendByte(Data);             //段选，第几行
	MatrixLED_lie=~(0x80>>Column);   //位选，第几列，0亮
	delay(1);
	MatrixLED_lie=0xff;
}