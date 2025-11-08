#include <REGF51RC.H>

void INT0_Init(void)
{
	//中断初始化
	EA=1; 
	EX0=1;
	IT0=1; 	
}

////外部中断函数模板
//void int0_Routine() interrupt 0
//{
//	
//}
