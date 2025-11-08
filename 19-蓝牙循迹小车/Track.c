#include <REGX51.H>
#include "car.h"
#include "INTRINS.h"
sbit Right  = P2^0; 
sbit Centure= P2^1;
sbit Left   = P2^2;

#define BLACK 1
#define WHITE 0

//charState;


/**
  * @brief  读取当前状态码
  * @param  无
  * @retval 状态码：State
  */
void read_sensor_values()
{
//	if(Right == WHITE&&Centure == BLACK&&Left == WHITE)State = 0;//直线
//	if(Right == BLACK&&Centure == WHITE&&Left == BLACK)State = 0;//直线
//	if(Right == BLACK&&Centure == WHITE&&Left == WHITE)State = 1;//右偏
//	if(Right == BLACK&&Centure == BLACK&&Left == WHITE)State = 1;//右偏
//	if(Right == WHITE&&Centure == WHITE&&Left == BLACK)State = -1;//左偏
//	if(Right == WHITE&&Centure == BLACK&&Left == BLACK)State = -1;//左偏
//	if(Right == WHITE&&Centure == WHITE&&Left == WHITE)State =  2;//停止
//	return State;
	
	if(Right == WHITE&&Centure == BLACK&&Left == WHITE) 
	{
		Car_Go();
	}       //直线
	if(Right == BLACK&&Centure == WHITE&&Left == BLACK)
	{
		Car_Go();
	}		//直线
	/****************************************************/
	
	if(Right == BLACK&&Centure == WHITE&&Left == WHITE)
	{
//		Car_Back();
//		delay(10);
		Car_RightGo();
		if(Right == WHITE&&Centure == WHITE&&Left == WHITE)	Car_Go();
	}		//右偏
	if(Right == BLACK&&Centure == BLACK&&Left == WHITE)
	{
		Car_RightGo();
		if(Right == WHITE&&Centure == WHITE&&Left == WHITE)	Car_Go();
	}		//右偏
	/****************************************************/
	
	if(Right == WHITE&&Centure == WHITE&&Left == BLACK)
	{
		Car_LeftGo();
		if(Right == WHITE&&Centure == WHITE&&Left == WHITE)	Car_Go();
	}		//左偏
	if(Right == WHITE&&Centure == BLACK&&Left == BLACK)
	{	
		Car_LeftGo();
		if(Right == WHITE&&Centure == WHITE&&Left == WHITE)	Car_Go();
	}		//左偏
	/***************************************************/
	//直角左拐、直角右拐，三路不行
	if(Right == WHITE&&Centure == WHITE&&Left == WHITE)Car_Stop(); //停止
}


// /**
//   * @brief  均值滤波，减少误差
//   * @param  无
//   * @retval State_average
//   */
//   charget_average()
//{
//	floatState_sum,State_average;
//	charState_i[5],i,result;
//	for(i=0;i<5;i++)
//	{
//		State_i[i] = read_sensor_values();
//	}
//	for(i=0;i<5;i++)
//	{
//		State_sum += State_i[i];
//	}
//	State_average = State_sum/5;
//	if(-0.5 < State_average && State_average <= 0.5) result = 0;
//	if( 0.5 < State_average && State_average <= 1.5) result = 1;
//	if(-1.5 < State_average && State_average <= -0.5)result = -1;
//	if( 1.5 < State_average && State_average <= 2)   result = 2;
//	return result;
//}

