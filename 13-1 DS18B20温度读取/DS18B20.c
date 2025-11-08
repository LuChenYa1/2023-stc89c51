#include <REGX51.H>
#include "OneWire.h"
 
 
#define DS18B20_SKIP_ROM  		0xCC
#define DS18B20_CONVERT_T 		0x44
#define DS18B20_READ_SCRATCHPAD 0xBE


/**
  * @brief  变换并更新温度
  * @param  无
  * @retval 无
  */
void DS18B20_Convert_T(void)
{
	OneWire_Init();
	OneWire_SendByte(DS18B20_SKIP_ROM);
	OneWire_SendByte(DS18B20_CONVERT_T);
}


/**
  * @brief  读取温度
  * @param  无
  * @retval 读取的温度值
  */
float DS18B20_Read_T(void)
{
	unsigned char TLSB,TMSB;//低位，高位
	int temp;//占两个字节
	float T; //实际温度值
	OneWire_Init();	
	OneWire_SendByte(DS18B20_SKIP_ROM);
	OneWire_SendByte(DS18B20_READ_SCRATCHPAD);
	TLSB=OneWire_ReceiveByte();
	TMSB=OneWire_ReceiveByte();
	temp=(TMSB<<8)|TLSB;
	T=temp/16.0;
	return T;
}