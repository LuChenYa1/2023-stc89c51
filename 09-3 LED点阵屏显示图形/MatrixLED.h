#ifndef __MATRIXLED_H__
#define __MATRIXLED_H__
typedef  unsigned char uchar;
int i;
//对位进行重命名，不能用_,要用^
sbit SER = P3^4;                 //串行数据，一次赋值一位
sbit RCK = P3^5;                 //寄存器时钟，存满8位后触发RCK=1，将八位数据并行输入到DH~DA（D7到D1）
sbit SCK = P3^6;                 //串行时钟，每输入一位就触发该时钟将数据上移，一直移到最高位DH

void MatrixLED_Init();
void _74HC595_SendByte(uchar byte);
void MatrixLED_ShowColumn(uchar Column,Data);
#endif