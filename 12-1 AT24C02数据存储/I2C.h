#ifndef __I2C_H__
#define __I2C_H__

//ºØ≥…¡˘øÈ∆¥Õº£¨’ŸªΩI2C
void I2C_Start(void);
void I2C_Stop(void);
void I2C_SendByte(unsigned char Byte);
unsigned char I2C_ReceiveByte(void);
void I2C_SendACK(unsigned char ACKBit);
unsigned char I2C_ReceiveACK(void);	
	
#endif