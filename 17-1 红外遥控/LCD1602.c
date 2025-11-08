#include <REGX51.H>

sbit LCD_RS=P2^6;
sbit LCD_RW=P2^5;
sbit LCD_EN=P2^7;

#define LCD_DataPort P0

/**
  * @brief  独有延时函数
  * @param  无
  * @retval 无
  */
void LCD_delay()		//@11.0592MHz  1ms
{
	unsigned char i, j;

	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
}


/**
  * @brief  向LCD1602输入命令
  * @param  Command，命令字
  * @retval 无
  */
void LCD_WriteCommand(unsigned char Command)
{
	LCD_RS=0;            //指令选择位
	LCD_RW=0;            //写模式
	LCD_DataPort=Command;//输入数据
	LCD_EN=1;            //使能
	LCD_delay();         //缓冲时间
	LCD_EN=0;            //下降沿写入数据
	LCD_delay();         //缓冲时间
}


/**
  * @brief  向LCD1602输入数据并自动显示
  * @param  Data，输入的数据
  * @retval 无
  */
void LCD_WriteData(unsigned char Data)
{
	LCD_RS=1;            //数据选择位
	LCD_RW=0;            //写模式  
	LCD_DataPort=Data;   //输入数据
	LCD_EN=1;            //使能
	LCD_delay();             //缓冲时间
	LCD_EN=0;            //下降沿写入数据
	LCD_delay();              //缓冲时间
}


/**
  * @brief  初始化，写入相应命令
  * @param  无
  * @retval 无
  */
void LCD_Init(void)
{
	LCD_WriteCommand(0x38);//八位数据，两行，5*7
	LCD_WriteCommand(0x0C);//显示开，光标关，闪烁关
	LCD_WriteCommand(0x06);//光标自动加一
	LCD_WriteCommand(0x01);//清屏
}


/**
  * @brief  根据行和列确定光标位置
  * @param  Line, Column：行，列
  * @retval 无
  */
void LCD_SetCursor(unsigned char Line,unsigned char Column)
{
	if(Line==1)
	{
		LCD_WriteCommand(0x80|(Column-1));
	}
	else
	{
		LCD_WriteCommand(0x80|(Column-1)+0x40);		
	}
}


/**
  * @brief  在指定的位置上显示一个字符
  * @param  Line，Column ，Char：行，列，字符
  * @retval 无
  */
void LCD_ShowChar(unsigned char Line,unsigned char Column,unsigned char Char)
{
	LCD_SetCursor(Line,Column);
	LCD_WriteData(Char);
}


/**
  * @brief  从指定的位置开始显示字符串
  * @param  Line,Column,String[]:行，列，字符串
  * @retval 无
  */
void LCD_ShowString(unsigned char Line,unsigned char Column,unsigned char String[])
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=0;String[i]!='\0';i++)//将字符串当成字符数组，挨个显示出来
	{
		LCD_WriteData(String[i]);
	}
}


/**
  * @brief  求X的Y次方
  * @param  X，Y
  * @retval 返回结果
  */
int LCD_Pow(int X,int Y)
{
	unsigned char i;
	int Result=1;
	for(i=0;i<Y;i++)
	{
		Result*=X;
	}
	return Result;
}


/**
  * @brief  在指定位置上显示数字并限制总宽度
  * @param  Line,Column,Number,Length：行，列，数字，长度
  * @retval 无
  */
void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		LCD_WriteData('0'+Number/LCD_Pow(10,i-1)%10);
	}
}


/**
  * @brief  在指定位置上显示有符号的数字 
  * @param  Line,Column,Number,Length：行，列，数字，长度
  * @retval 无
  */
void LCD_ShowSignedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length)
{
	unsigned char i,Number1;
	LCD_SetCursor(Line,Column);
	if(Number>=0)
	{
		LCD_ShowChar(Line,Column,'+');
		Number1=Number;
		for(i=Length;i>0;i--)
		{
			LCD_WriteData('0'+Number1/LCD_Pow(10,i-1)%10);
		}
	}
	else
	{
		LCD_ShowChar(Line,Column,'-');
		Number1=-Number;
		for(i=Length;i>0;i--)
		{
			LCD_WriteData('0'+Number1/LCD_Pow(10,i-1)%10);
		}
	}
}



/**
  * @brief  在指定位置上显示数字的十六进制形式 
  * @param  Line,Column,Number,Length：行，列，数字，长度
  * @retval 无
  */
void LCD_ShowHexNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length)
{
	unsigned char i;
	unsigned char SingleNumber;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		SingleNumber=Number/LCD_Pow(16,i-1)%16;
		if(SingleNumber<10)
		{
			LCD_WriteData('0'+SingleNumber);			
		}
		else
		{
			LCD_WriteData('A'+SingleNumber-10);
		}
	}
}


/**
  * @brief  在指定位置上显示数字的二进制形式 
  * @param  Line,Column,Number,Length：行，列，数字，长度
  * @retval 无
  */
void LCD_ShowBinNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		LCD_WriteData('0'+Number/LCD_Pow(2,i-1)%2);
	}
}

