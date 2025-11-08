#ifndef __DS1302_H__
#define __DS1302_H__

void DS1302_Init();
void DS1302_WriteByte(unsigned char command,Data);
unsigned char DS1302_ReadByte(unsigned char command); 
void DS1302_SetTime(void);
void DS1302_ReadTime(void);
extern unsigned char DS1302_Time[];

#endif
 