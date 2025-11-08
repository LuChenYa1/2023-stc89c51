#include <REGX51.H>

typedef  unsigned char uchar;


/**
  * @brief  设置串口接收模式，也能发送
  * @param  无
  * @retval 无
  */
void UART_Init(void)      //9600bps@11.0592MHz
{
	                      //0x50比0x40多了REN=1,允许接收数据
	SCON = 0x50;          //串口模式1（常用），八位数据，可变波特率，和定时器模式2（八位自动重装）不是一个东西
	PCON |=0x80;          //最高位置一，其他位不变，波特率加倍（本来是为了减小误差，但这里已经无误差，可不加倍）
	//	AUXR &= 0xBF;	  //高级功能，该型号单片机没有	
	//	AUXR &= 0xFE;	  //调12T和定时器1
	TMOD &=0x0F;          //高四位清零，低四位不变，调定时器1
    TMOD |=0x20;          //调定时器1的模式二，八位自动重装模式
	TL1=0xFA;             //设置定时初值
	TH1=0xFA;             //设定定时器重装值
	ET1=0;                //禁止定时器1中断，只提供定时功能，中断没有用
	TR1=1;                //启动定时器
	//独属于需要接受数据的时候的配置
   	EA=1;                 //开启中断总开关
	ES=1;                 //开启串口中断
}
//定时器1中断的触发条件是时间到了，定时结束，定时器1用来配置波特率，没有必要开启中断
//串口中断的触发条件是接收数据或者发送数据



/**
  * @brief  由串口向电脑发送一个数字
  * @param  数字字符
  * @retval 无
  */
void UART_SendByte(uchar byte)
{
	SBUF=byte;                    //SBUF有两个，一个是发送区，一个是接受区，空间不一样，但占用同一个地址
	while(TI==0);
	TI=0;                         //一旦发送，立即软件复位
}

void Uart_SendString(unsigned char *String)
{
	unsigned char i = 0;
	ES=0;
	for(i = 0;String[i]!='\0';i++)
	{
		SBUF=String[i]; 
		while(TI==0); 
		TI=0; 
	}
	ES=1;
}

 /**
  * @brief  串口中断函数模板
  * @param  无
  * @retval 无
  */
//void UART_Routine()   interrupt 4 //串口中断对应中断号
//{
//	if(RI==1)                     //发送和接收中断占用的是一个通道，都会触发中断函数，加if判断防止误触
//	{
//		RI=0;                     //（手动）软件复位
//	}
//}

