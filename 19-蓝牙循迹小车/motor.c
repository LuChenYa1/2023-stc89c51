#include <REGX51.H>

//00制动
sbit left1 = P0^7;//10反转
sbit left2 = P0^6;//01正转
sbit right1 = P0^5;//10反转
sbit right2 = P0^4;//01正转

void Left_go()//左轮往前
{
	left1 = 0;
	left2 = 1;
}
void Left_back()//左轮往后
{
	left1 = 1;
	left2 = 0;
}
void Left_stop()//左轮停止
{
	left1 = 0;
	left2 = 0;
}
void Right_go()//右轮往前
{
	right1 = 0;
	right2 = 1;
}
void Right_back()//右轮往后
{
	right1 = 1;
	right2 = 0;
}
void Right_stop()//右轮停止
{
	right1 = 0;
	right2 = 0;
}


