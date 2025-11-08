#include <REGX51.H>
#include <INTRINS.H>

unsigned char ACKBit;
sbit OneWire_DQ = P3^7;


/**
  * @brief  初始化，开始执行读写操作
  * @param  无
  * @retval 0应答，1非应答
  */
unsigned char OneWire_Init(void)
{
	unsigned char ACKBit;
	unsigned char i;
	OneWire_DQ=1;
	OneWire_DQ=0;
	i = 227;while (--i);//延时500us：主线拉低至少480us
	OneWire_DQ=1;       //释放置一
	i = 30;while (--i); //延时70us：置一等待15~60us后，从机才会响应，为确保从机在置一时响应，延时比60长
	ACKBit=OneWire_DQ;
	i = 227;while (--i);//延时500us:保证时长
	return ACKBit;
}


/**
  * @brief  主机向从机发送一位
  * @param  Bit，要发送的位的值（0/1）
  * @retval 无
  */
void OneWire_SendBit(unsigned char Bit)
{
	unsigned char i;
	OneWire_DQ=0;               //拉低
	_nop_();i = 4;while (--i);  //延时10us,去掉函数头调用的4us，设定14us，实际运行10us
	OneWire_DQ=Bit;             //将要输入的值写进去
	i = 23;while (--i);         //延时50us
	OneWire_DQ=1;               //释放
}


/**
  * @brief  主机接收从机发来的一位的值
  * @param  无
  * @retval 返回一位的值
  */
unsigned char OneWire_ReceiveBit(void)
{
	unsigned char Bit,i;
	OneWire_DQ=0;              //拉低
	_nop_();i = 1;while (--i); //延时5us
	OneWire_DQ=1;               //释放
    _nop_();i = 1;while (--i); //延时5us
	Bit=OneWire_DQ;            //查看从机发送过来的值
	i = 23;while (--i);        //延时50us
	//主机不释放，由从机负责释放
	return Bit;
}

/**
  * @brief  主机发送一个字节
  * @param  Byte，要发送的字节的值
  * @retval 无
  */
void OneWire_SendByte(unsigned char Byte)
{
	unsigned char j;
	for(j=0;j<8;j++)
	{
		OneWire_SendBit(Byte&(0x01<<j));
	}
}


/**
  * @brief  主机接收一个字节
  * @param  无
  * @retval 返回接收的字节的值
  */
unsigned char OneWire_ReceiveByte(void)
{
	unsigned char j;
	unsigned char Byte=0x00;
	for(j=0;j<8;j++)
	{
		if(OneWire_ReceiveBit()){Byte|=(0x01<<j);}
	}
	return Byte;
}






