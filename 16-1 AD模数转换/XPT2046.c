#include <REGX51.H>
#include "delay.h"
 
sbit XPT2046_CS = P3^5;
sbit XPT2046_DCLK = P3^6;
sbit XPT2046_DIN = P3^4;
sbit XPT2046_DOUT = P3^7;

/**
  * @brief  读取电压经A/D转换后的值
  * @param  Command:命令字，读取哪个类型
  * @retval ADValue：读取的值
  */
unsigned int XPT2046_ReadAD (unsigned char Command)
{
	unsigned int ADValue=0;
	unsigned char i;
	XPT2046_DCLK=0;
	XPT2046_CS=0;
	//写入命令字
	for(i=0;i<8;i++)
	{
		XPT2046_DIN=Command&(0x80>>i);
		XPT2046_DCLK=1;
		XPT2046_DCLK=0;
	}
	//读取数据
	for(i=0;i<16;i++)
	{
		XPT2046_DCLK=1;
		XPT2046_DCLK=0;
		if(XPT2046_DOUT)ADValue|=(0x8000>>i);
	}
	XPT2046_CS=1;
	if(Command&0x08)
	{
		return ADValue>>8;//8位分辨率，前8位有用，后八位为0；数值被放大了2^8倍，故需要右移才能显示真实数值0^255
	}
	else
	{
		return ADValue>>4;
	}
}
