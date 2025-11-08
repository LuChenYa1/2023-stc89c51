#include <REGX51.H>

 /**
  * @brief                 定时器初始化1ms，11.0592MHz
  * @param                 无
  * @retval                无
  */
void Timer1_Init()		    //1000us @11.0592MHz
{
	TMOD &= 0x0F;			//配置模式：打开定时器1；启用模式1；高四位不变，后四位清零
	TMOD |=0x10;            //最低位置1，高四位不变
	TL1 = 0x66;				//配置计数范围，确定中断时间,RC版频率不一样，差值对应时间不一样，是66不是18
	TH1 = 0xFC;				//设置定时初值
	TF1 = 0;				//标志位清零
	TR1 = 1;				//定时器1开始计数
	
	EA=1;                   //开启中断总开关
	ET1=1;                  //开启定时器1分开关
	PT1=0;                  //配置优先级 （0是最低）
	
}

//中断所执行程序模板

//void Timer1_Routine () interrupt 3
//{
//	static unsigned int T1count;     //静态局部变量，保证不会被重新赋值

//	TL1 = 0x66;				         //确保中断时间不变
//	TH1 = 0xFC;	
//	T1count++;
//	if(T1count == 1000)              //每隔1000毫秒进入if，灯亮灭变化
//	{
//		T1count=0;
//		//P2_0=~P2_0;
//	}
//}


