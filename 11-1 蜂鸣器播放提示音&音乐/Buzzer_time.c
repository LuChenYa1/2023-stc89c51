#include <REGX51.H>
#include "delay.h" 
#include <INTRINS.H>


sbit Buzzer = P2^5;
unsigned int i;
void delay500us();


/**
  * @brief  控制蜂鸣器响铃时间
  * @param  时间（ms）
  * @retval 无
  */
void Buzzer_time (unsigned int xms)		//@11.0592MHz
{
	
	 for(i=0;i<xms*2;i++)
	{
		Buzzer= !Buzzer;
		delay500us();
	}
	
}

/**
  * @brief  蜂鸣器私有延时函数
  * @param  无
  * @retval 无
  */
void delay500us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 6;
	j = 93;
	do
	{
		while (--j);
	} while (--i);
}
