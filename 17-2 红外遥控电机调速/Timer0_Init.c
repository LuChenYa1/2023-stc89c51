#include <REGX51.H>

 /**
  * @brief                 改装计数器，计算程序运行时间
  * @param                 无
  * @retval                无
  */
void Timer0_Init()		    //1000us @11.0592MHz
{
	TMOD &= 0xF0;			//配置模式：打开定时器0；启用模式1；高四位不变，后四位清零
	TMOD |=0x01;            //最低位置1，高四位不变
	TL0 = 0;				 
	TH0 = 0;				//设置计数初值
	TF0 = 0;				//标志位清零
	TR0 = 0;				//暂时停止计数
}



 /**
  * @brief  设置计数初值
  * @param  十六位初值
  * @retval 无
  */
void Timer0_SetCounter(unsigned int Value)
{
	TH0=Value/256;
	TL0=Value%256;
}



/**
  * @brief  得到当前计数
  * @param  无
  * @retval 计数值
  */
unsigned int Timer0_GetCounter(void)
{
	return (TH0<<8)|TL0;
}



/**
  * @brief  开始计数
  * @param  Flag:置一则运行，置零停止计数
  * @retval 无
  */
void Timer0_Run(unsigned char Flag)
{
	TR0=Flag;
}






