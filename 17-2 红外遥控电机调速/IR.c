#include <REGX51.H>
#include "Timer0_Init.h"
#include "Int0.h"

//红外光线经处理传进单片机内部，变成方波信号，其下降沿能被读取并触发外部中断
unsigned char IR_State;//状态:空闲、预启动、数据解码
unsigned int  IR_Time; //时间计数

unsigned char IR_RepeatFlag;//重复标志位
unsigned char IR_Data[4];//数据
unsigned char IR_pData;//数据位数

unsigned char IR_Address;//地址码
unsigned char IR_Command;//命令码
unsigned char IR_DataFlag;////数据完毕标志位



/**
  * @brief  红外线解码初始化
  * @param  无
  * @retval 无
  */
void IR_Init()
{
	Timer0_Init();
	Int0_Init();
}



/**
  * @brief  得到重复标志位
  * @param  无
  * @retval IR_RepeatFlag：1为重复信号，0为非重复信号
  */
unsigned char IR_GetRepeatFlag(void)
{
	if(IR_RepeatFlag)
	{
		IR_RepeatFlag=0;
		return 1;
	}
	return 0;
}



/**
  * @brief  得到数据解码标志位
  * @param  无
  * @retval IR_DataFlag：1为数据解码完毕，0为正在解码或非解码
  */
unsigned char IR_GetDataFlag(void)
{
	if(IR_DataFlag)
	{
		IR_DataFlag=0;
		return 1;
	}
	return 0;
}



/**
  * @brief  得到红外方波信号的地址码
  * @param  无
  * @retval IR_Address：地址码
  */
unsigned char IR_GetAddress(void)
{
	return IR_Address;
}



/**
  * @brief  得到红外方波信号的命令码
  * @param  无
  * @retval IR_Command：命令码
  */
unsigned char IR_GetCommand(void)
{
	return IR_Command;
}



//外部中断执行函数：下降沿触发
void Int0_Routine(void)  interrupt 0
{
	 if(IR_State==0)//空闲状态，刚开始接收到下降沿
	 { 
		 Timer0_SetCounter(0);
		 Timer0_Run(1);//开始计算两个下降沿的间隔时间
		 IR_State=1;
	 }
	 
	 else if(IR_State==1)//预启动状态:判断接下来是重复空闲还是开始解码
	 { 
		 P2=~0x01;
		 IR_Time=Timer0_GetCounter();
		 Timer0_SetCounter(0);
		 
		 if(IR_Time<13500+500 && IR_Time>13500-500)     //开始信号：信号解码成数据
		 {  
			IR_State=2;
		 }
		 
		 else if(IR_Time<11250+500 && IR_Time>11250-500)//重复信号：重复发空值，那就是空闲
		 {
			 IR_RepeatFlag=1;//重复标志位
			 IR_State=0;
			 Timer0_Run(0);//停止计数
		 }
		 
		 else//以防解码出错
		 {
			IR_State=1; 
		 }
	 }
	 else if(IR_State==2)//开始解码
	 {
		 IR_Time=Timer0_GetCounter();//数据信号
		 Timer0_SetCounter(0);
		 
		 if(IR_Time<1120+500 && IR_Time>1120-500)//逻辑0
		 {
			 IR_Data[IR_pData/8] &= ~(0x01<<(IR_pData%8));
			 IR_pData++;
		 }
		 else if(IR_Time<2250+500 && IR_Time>2250-500)//逻辑1
		 {
			 IR_Data[IR_pData/8] |= (0x01<<(IR_pData%8));
			 IR_pData++;
		 }
		 else
		 {
			 IR_pData=0;
			 IR_State=1;
		 }
		 if(IR_pData==32)//4个字节数据传输完毕
		 {
			 IR_pData=0;
			 if(IR_Data[0]==~IR_Data[1]&&IR_Data[2]==~IR_Data[3])//地址+反码+命令+反码
			 {
				 IR_Address=IR_Data[0];
				 IR_Command=IR_Data[2];
				 IR_DataFlag=1;//数据完毕标志位
			 }
			 IR_State=0;   //一串数据信号解码完毕
			 Timer0_Run(0);//停止计数
		 }
	 }
}

