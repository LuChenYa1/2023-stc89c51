#ifndef __UART_H__
#define __UART_H__
typedef  unsigned char uint8_t;//头文件里也要写
void UART_Init(void);
void UART_SendByte(uint8_t byte);
void UART_SendString(uint8_t *String);

#endif