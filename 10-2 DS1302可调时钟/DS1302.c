#include <REGX51.H>
#include "LCD1602.h"

unsigned char i;
unsigned char Data;
extern char DS1302_Time[];
	
sbit DS1302_CE=P3^5;
sbit DS1302_IO=P3^4;  //这里的IO口有点类似SER（串行数据）
sbit DS1302_SCLK=P3^6;

#define DS1302_YEAR    0x8c
#define DS1302_MONTH   0x88
#define DS1302_DATE    0x86
#define DS1302_HOUR    0x84
#define DS1302_MINUTE  0x82
#define DS1302_SECOND  0x80
#define DS1302_DAY     0x8a
#define DS1302_WP      0X8e


 /**
  * @brief  初始化，使能关，串行时钟关
  * @param  无
  * @retval 无
  */
void DS1302_Init()
{
	DS1302_CE=0;
	DS1302_SCLK=0;
}
/**
  * @brief  下达写命令，向芯片写入数据
  * @param  命令字，数据
  * @retval 无
  */

void DS1302_WriteByte(unsigned char command,Data)
{
	DS1302_CE=1;                     //开

	for(i=0;i<8;i++)                 //命令字
	{
		DS1302_IO=command&(0x01<<i); //按位写入命令
		DS1302_SCLK=1;               //置一，上移沿存入数据
		DS1302_SCLK=0;               //复位
	}
	
	for(i=0;i<8;i++)                 //写入数据
	{
		DS1302_IO=Data&(0x01<<i);    //按位写入数据
		DS1302_SCLK=1;               //置一，上移沿存入数据
		DS1302_SCLK=0;               //复位
	}
	
	DS1302_CE=0;                     //关
}

/**
  * @brief  读取数据
  * @param  命令字
  * @retval 从芯片中读取的数据
  */
//读的部分是时钟芯片的事，只要定义变量去装着它就行
 
unsigned char DS1302_ReadByte(unsigned char command) 
{
	DS1302_CE=1;                     //开
	Data=0x00;                       //用于承载读取的值
	command|=0x01;
	for(i=0;i<8;i++)                 //命令字
	{
		DS1302_IO=command&(0x01<<i); //按位写入命令
		DS1302_SCLK=0;               //复位
		//先0后一防止IO越界进行读取
		DS1302_SCLK=1;               //置一，上移沿存入数据
	}
			
	 for(i=0;i<8;i++)                 //写入数据
	{
		DS1302_SCLK=1;               //置一，上移沿存入数据
		DS1302_SCLK=0;               //复位,IO地址进位，芯片内的值被读取进入IO线
		if(DS1302_IO)Data|=(0x01<<i);//IO该位为一，则Data该位也为一
	}
	
    DS1302_IO=0;                     //读取完毕，进行数据清空，防止数据遗留，对下次结果造成干扰，虽然没看懂
	DS1302_CE=0;                     //关
	return Data;
}

/**
  * @brief  将设置好的时间数组传递到DS1302时钟芯片内部
  * @param  无
  * @retval 无
  */
void DS1302_SetTime(void)
{
	DS1302_WriteByte(DS1302_WP,0x00);  //关闭写保护
	DS1302_WriteByte(DS1302_YEAR,DS1302_Time[0]/10*16+DS1302_Time[0]%10);
	DS1302_WriteByte(DS1302_MONTH,DS1302_Time[1]/10*16+DS1302_Time[1]%10);
	DS1302_WriteByte(DS1302_DATE,DS1302_Time[2]/10*16+DS1302_Time[2]%10);
	DS1302_WriteByte(DS1302_HOUR,DS1302_Time[3]/10*16+DS1302_Time[3]%10);
	DS1302_WriteByte(DS1302_MINUTE,DS1302_Time[4]/10*16+DS1302_Time[4]%10);
	DS1302_WriteByte(DS1302_SECOND,DS1302_Time[5]/10*16+DS1302_Time[5]%10);
	DS1302_WriteByte(DS1302_DAY,DS1302_Time[6]/10*16+DS1302_Time[6]%10);
	DS1302_WriteByte(DS1302_WP,0x80);  //打开写保护
}

/**
  * @brief  将芯片内部的时间传递到时间数组里
  * @param  无
  * @retval 无
  */
void DS1302_ReadTime(void)
{
	unsigned char temp;
	temp=DS1302_ReadByte(DS1302_YEAR);
	DS1302_Time[0]=temp/16*10+temp%16;
	
	temp=DS1302_ReadByte(DS1302_MONTH);
	DS1302_Time[1]=temp/16*10+temp%16;
	
	temp=DS1302_ReadByte(DS1302_DATE);
	DS1302_Time[2]=temp/16*10+temp%16;
	
	temp=DS1302_ReadByte(DS1302_HOUR);
	DS1302_Time[3]=temp/16*10+temp%16;
	
	temp=DS1302_ReadByte(DS1302_MINUTE);
	DS1302_Time[4]=temp/16*10+temp%16;
	
	temp=DS1302_ReadByte(DS1302_SECOND);
	DS1302_Time[5]=temp/16*10+temp%16;	 
	
	temp=DS1302_ReadByte(DS1302_DAY);
	DS1302_Time[6]=temp/16*10+temp%16;	 
}
/**
  * @brief  显示时间
  * @param  无
  * @retval 无
  */
void DS1302_ShowTime()
{
	DS1302_ReadTime();//读取时间
	LCD_ShowNum(1,1,DS1302_Time[0],2);   //显示年
	LCD_ShowNum(1,4,DS1302_Time[1],2);   //显示月
	LCD_ShowNum(1,7,DS1302_Time[2],2);   //显示日
	LCD_ShowNum(2,1,DS1302_Time[3],2);   //显示时
	LCD_ShowNum(2,4,DS1302_Time[4],2);   //显示分
	LCD_ShowNum(2,7,DS1302_Time[5],2);   //显示秒
	LCD_ShowNum(1,12,DS1302_Time[6],1);  //显示星期
}
 