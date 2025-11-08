#include <REGX51.H>

 /**
  * @brief                 定时器初始化0.5ms,11.0592MHz.0592MHz
  * @param                 无
  * @retval                无
  */
void Timer0_Init()		    //1000us @11.0592MHz
{
	TMOD &= 0xF0;			//配置模式：打开定时器0;启用模式1;高四位不变，后四位清零
	TMOD |=0x01;            //最低位置1,高四位不变继承前人原有的工作模式    
	TL0 = 0x33;				//配置计数范围，确定中断时间500us
	TH0 = 0xFE;				//设置定时初值
	TF0 = 0;				//标志位清零
	TR0 = 1;				//定时器0开始计数
	
	EA=1;                   //开启中断总开关
	ET0=1;                  //开启定时器0分开关
	PT0=0;                  //配置优先级  (0是最低)
	
}

//定时中断函数

//void Timer0_Routine () interrupt 1
//{
//	static unsigned int T0count;     //静态局部变量

//	TL0 = 0x66;				         //重新赋初值
//	TH0 = 0xFC;	
//	T0count++;
//	if(T0count == 1000)              //1ms * 1000 = 1s
//	{
//		T0count=0;
//		//P2_0=~P2_0;
//	}
//}


