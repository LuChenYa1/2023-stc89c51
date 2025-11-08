#ifndef __CAR_H__
#define __CAR_H__

void Car_Go();//向前直行
void Car_Back();//向后直行
void Car_Stop();//停止
void Car_LeftGo();//原地向前左拐
void Car_RightGo();//原地向前右拐
void Car_LeftBack();//原地向后左拐
void Car_RightBack();//原地向后右拐

void contral_0(void);
void contral_1(void);
void contral_4(void);
void contral(void);
void system(void);
void system_xunji(void);

extern unsigned char angle;

#endif