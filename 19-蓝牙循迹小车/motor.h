#ifndef __MOTOR_H__
#define __MOTOR_H__

void Left_go();//左轮往前
void Left_back();//左轮往后
void Left_stop();//左轮停止
void Right_go();//右轮往前
void Right_back();//右轮往后
void Right_stop();//右轮停止
sbit left1 = P0^7;//10反转
sbit left2 = P0^6;//01正转
sbit right1 = P0^5;//10反转
sbit right2 = P0^4;//01正转

#endif