#include <REGX51.H>
#include "delay.h"
#define MatrixLED_lie P0       //提高可读性，方便后期替换操作寄存器

#define uint8_t unsigned char 

//对位进行重命名，不能用_,要用^
sbit SCK = P2^2;               //串行数据，一次赋值一位
sbit SER = P2^3;               //寄存器时钟，存满8位后触发RCK=1，将八位数据并行输入到DH~DA（D7到D1）
sbit RCK = P2^4;               //串行时钟，每输入一位就触发该时钟将数据上移，一直移到最高位DH


/**
  * @brief    初始化寄存器时钟和串行时钟
  * @param    无
  * @retval   无
  */
void MatrixLED_Init(void)
{
	SCK=0;        //SCK需要手动复位和开启
	RCK=0;        //RCK需要手动复位和开启
}
	
	
/**
  * @brief  两个595级联，一次性传输两字节数据
  * @brief  顺序将byte从高到低的数值赋值给SER,再传递给D7到D0,D15~D8
  * @param  一次只有一行亮，列高行低，列为十进制（易读）
  * @retval 无
  */
void MatrixLED_8_ShowColumn(unsigned char Lie, unsigned char  HangData)
{
	unsigned char i;
	
	for(i=0;i<8;i++)
	{
		SER = !(HangData & (0x80>>i));  
		SCK = 1;  //上移一位
		SCK = 0;  //复位
	}
	for(i=0;i<8;i++)
	{
		SER = (0x01 << (Lie-1)) & (0x80>>i);  
		SCK = 1;  //上移一位
		SCK = 0;  //复位
	}
	RCK = 1;      //并行输入8位
	RCK = 0;      //复位
	//不用自己清零SER，会有问题，直接再次赋值就可以
	//	Delay_ms(1);
}


/**
  * @brief  四个595级联，一次性传输四字节数据
  * @brief  顺序将byte从高到低的数值赋值给SER
  * @param  一次只有一行亮，列高行低，列为十进制（易读）
  * @retval 无
  */
void MatrixLED_16_ShowColumn(unsigned char Lie, unsigned char H_HangData, unsigned char L_HangData)
{
	unsigned char i;
	
	for(i=0;i<8;i++)//第4组数据，行的高八位
	{
		SER = !(H_HangData & (0x80>>i));  
		SCK = 1;  //上移一位
		SCK = 0;  //复位
	}
	for(i=0;i<8;i++)//第3组数据，行的低八位
	{
		SER = !(L_HangData & (0x80>>i));  
		SCK = 1;  //上移一位
		SCK = 0;  //复位
	}
	for(i=0;i<8;i++)//第2组数据，列的高八位
	{
		if(Lie > 8 && Lie < 16)SER = (0x01 << ((Lie % 8)-1)) & (0x80>>i);  
		else if(Lie == 16)SER = (0x01 << (8-1)) & (0x80>>i);
		else SER = (0x00) & (0x80>>i);  
		SCK = 1;  //上移一位
		SCK = 0;  //复位
	}
	for(i=0;i<8;i++)//第1组数据，列的低八位
	{
		if(Lie < 8)SER = (0x01 << ((Lie % 8)-1)) & (0x80>>i); 
		else if(Lie == 8)SER = (0x01 << (8-1)) & (0x80>>i); 
		else SER = (0x00) & (0x80>>i);
		SCK = 1;  //上移一位
		SCK = 0;  //复位
	}
	RCK = 1;      //并行输入8位
	RCK = 0;      //复位
	//不用自己清零SER，会有问题，直接再次赋值就可以
	//Delay_ms(1);
}

