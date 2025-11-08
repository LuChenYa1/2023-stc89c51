#include <REGX51.H>


void Int0_Init(void)
{
	IT0=1; //外部中断Int0，触发条件：P3^2下降沿(独立按键K3)
	//Int0=0:触发条件为低电平，按下K3不松手则一直触发中断
	IE0=0; //中断标志位，未溢出置0
	EX0=1; //打开外部中断Int0
	EA=1;  //打开总中断
	PX0=1; //设置较高优先级
}

//外部中断执行函数
//void Int0_Routine(void)  interrupt 0
//{
//	i++;
//}
