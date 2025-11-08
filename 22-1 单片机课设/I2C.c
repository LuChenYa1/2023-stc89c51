#include <REGX51.H>

sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;


/**
  * @brief  I2C开始
  * @param  无
  * @retval 无
  */
void I2C_Start(void) 
{
	I2C_SCL=1;
	I2C_SDA=1;
	I2C_SDA=0;
	I2C_SCL=0;//和后面的发送阶段进行衔接
}


/**
  * @brief  I2C结束
  * @param  无
  * @retval 无
  */
void I2C_Stop(void)
{
	I2C_SDA=0;
	I2C_SCL=1;//置1表示断开，此时对电路无影响
	I2C_SDA=1;//结束时要释放
}


/**
  * @brief  I2C发送一个字节
  * @param  Byte，要发送的字节数据
  * @retval 无
  */
void I2C_SendByte(unsigned char Byte)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		I2C_SDA=Byte&(0x80>>i);
		I2C_SCL=1;//指令周期大于数据上传周期
		I2C_SCL=0;
	}
}


/**
  * @brief  I2C接收一个字节
  * @param  无
  * @retval Byte，接收到的字节值
  */
unsigned char I2C_ReceiveByte(void)
{
	unsigned char i,Byte=0x00;
	I2C_SDA=1;//接收前预处理，释放SDA
	for(i=0;i<8;i++)
	{
		I2C_SCL=1;
		if(I2C_SDA){Byte|=(0x80>>i);}	
		I2C_SCL=0;
	}
	return Byte;
}


/**
  * @brief  I2C发送应答，0为应答，1为非应答 
  * @param  ACKBit，要发送的应答位
  * @retval 无
  */
void I2C_SendACK(unsigned char ACKBit)
{
	I2C_SDA=ACKBit;
	I2C_SCL=1;
	I2C_SCL=0;
}


/**
  * @brief  I2C接收应答（0/1）
  * @param  无
  * @retval ACKBit，接收到的应答位
  */
unsigned char I2C_ReceiveACK(void)
{
	unsigned char ACKBit;
	I2C_SDA=1;//接收前释放SDA
	I2C_SCL=1;
	ACKBit=I2C_SDA;//将接收到的应答值赋给ACKBit
	I2C_SCL=0;
	return ACKBit;
}
