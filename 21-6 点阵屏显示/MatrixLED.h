#ifndef __MATRIXLED_H__
#define __MATRIXLED_H__

extern 	unsigned char i;

sbit SCK = P2^2;                 
sbit SER = P2^3;                 
sbit RCK = P2^4;                

void MatrixLED_Init(void);
void MatrixLED_8_ShowColumn(unsigned char  Lie, unsigned char  HangData);
void MatrixLED_16_ShowColumn(unsigned char Lie, unsigned char H_HangData, unsigned char L_HangData);

#endif