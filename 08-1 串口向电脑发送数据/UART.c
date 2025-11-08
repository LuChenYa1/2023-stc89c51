#include <REGX51.H>

typedef  unsigned char uchar;
/**
  * @brief  设置串口模式
  * @param  无
  * @retval 无
  */
void UART_Init(void)      //4800bps@11.0592MHz
{
	                      //0x50比0x40多了REN=1,允许接收数据
	SCON = 0x50;          //串口模式1（常用），八位数据，可变波特率，和定时器模式2（八位自动重装）不是一个东西
	PCON |=0x80;          //最高位置一，其他位不变，波特率加倍（本来是为了减小误差，但这里已经无误差，可不加倍）
	//	AUXR &= 0xBF;	  //高级功能，该型号单片机没有	
	//	AUXR &= 0xFE;	  //调12T和定时器1
	TMOD &=0x0F;          //高四位清零，低四位不变，调定时器1
    TMOD |=0x20;          //调定时器1的模式二，八位自动重装模式
	TL1=0xF4;             //设置定时初值
	TH1=0xF4;             //设定定时器重装值
	ET1=0;                //禁止定时器1中断，只提供定时功能，中断没有用
	TR1=1;                //启动定时器
}

/**
  * @brief  由串口向电脑发送一个数字
  * @param  数字字符
  * @retval 无
  */
void UART_SendByte(uchar byte)
{
	SBUF=byte;
	while(TI==0);
	TI=0;                  //一旦发送，立即软件复位
}