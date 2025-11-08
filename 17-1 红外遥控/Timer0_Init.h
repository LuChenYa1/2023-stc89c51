#ifndef __TIMER0_INIT_H__
#define __TIMER0_INIT_H__

void Timer0_Init();//初始化
void Timer0_SetCounter(unsigned int Value);//计数初值，一般是0
unsigned int Timer0_GetCounter(void);//得到当前计数
void Timer0_Run(unsigned char Flag);//开始计数
 
#endif