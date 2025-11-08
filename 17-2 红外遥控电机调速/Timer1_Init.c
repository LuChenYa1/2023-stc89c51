#include <REGX51.H>

 /**
  * @brief                 定时器初始化1ms，11.0592MHz
  * @param                 无
  * @retval                无
  */
void Timer1_Init()		    //100us @11.0592MHz
{
	TMOD &= 0x0F;			//配置模式：打开定时器1；启用模式1：后四位不变，高四位清零
	TMOD |=0x10;            //最低位置1，低四位不变，继承前人原有的工作模式
	
	TL1 = 0xA4;				//设置定时初值 
	TH1 = 0xFF;				 

	TF1 = 0;				//标志位清零
	TR1 = 1;				//定时器1开始计数
	
	EA=1;                   //开启中断总开关
	ET1=1;                  //开启定时器1分开关
	PT1=0;                  //配置优先级 （0是最低）
	
}

//中断执行程序模板

//void Timer1_Routine () interrupt 3
//{
//	static unsigned int T1count;     //静态局部变量，保证不会被重新赋值

//	TL1 = 0x66;				         //确保中断时间不变
//	TH1 = 0xFC;	
//	T1count++;
//	if(T1count == 1000)              //每隔1000微秒进入if，灯亮灭变化
//	{
//		T1count=0;
//		//P2_0=~P2_0;
//	}
//}


