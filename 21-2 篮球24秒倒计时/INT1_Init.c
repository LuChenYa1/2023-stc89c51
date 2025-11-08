#include <REGF51RC.H>

void INT1_Init(void)
{
	//中断初始化
	EA=1; 
	EX1=1;
	IT1=1; 	
}

////外部中断函数模板
//void int1() interrupt 1
//{
//	
//}
