#include <REGX51.H>
#include "I2C.h"

#define AT24C02_ADDRESS 0xA0

/**
  * @brief  向AT24C02存储器中写入数据 
  * @param  WORD_ADDRESS，要写入的字节空间的位置
  * @param  Data，要写入的数据
  * @retval 无
  */
void AT24C02_WriteByte(unsigned char WORD_ADDRESS,Data)
{
	I2C_Start();                  //开始
	I2C_SendByte(AT24C02_ADDRESS);//对AT24C02发送写命令
	I2C_ReceiveACK();             //接收应答
	I2C_SendByte(WORD_ADDRESS);   //指定要写入的字地址
	I2C_ReceiveACK();             //接收应答
	I2C_SendByte(Data);           //向EEPROM存储器发送数据
	I2C_ReceiveACK();             //接收应答
	I2C_Stop();                   //停止
}
 

/**
  * @brief  从存储器中读取数据
  * @param  WORD_ADDRESS，要读取的字节的位置
  * @retval 数据的值，写入的数据是什么形式，读出来的就是什么形式
  */
unsigned char AT24C02_ReadByte(unsigned char WORD_ADDRESS)
{
	unsigned char Data;
	/**********指定地址*********/
	
	I2C_Start();                      //开始
	I2C_SendByte(AT24C02_ADDRESS);    //发送写命令 
	I2C_ReceiveACK();                 //接收应答
	I2C_SendByte(WORD_ADDRESS);       //确定目标空间位置
	I2C_ReceiveACK();                 //没有停止函数，因为是同一个数据帧
	
	/***************************/
	
	I2C_Start();                       //开始
	I2C_SendByte(AT24C02_ADDRESS|0x01);//发送读命令
	I2C_ReceiveACK();                  //接收应答
	Data = I2C_ReceiveByte();          //得到读取的字节数据
	I2C_SendACK(1);                    //发送应答，这里一般为1（非应答）
	I2C_Stop();                        //停止
	
	/***************************/
	
	return Data;
}