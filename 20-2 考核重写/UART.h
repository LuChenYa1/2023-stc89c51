#ifndef __UART_H__
#define __UART_H__
typedef  unsigned char uchar;//头文件里也要写
void UART_Init(void);
void UART_SendByte(uchar byte);
void Uart_SendString(unsigned char *String);

#endif