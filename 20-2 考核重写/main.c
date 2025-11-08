#include <REGX51.H>
#include "nixie.h"
#include "Timer0_Init.h"
#include "Key.h"
#include "UART.h"
#include "delay.h"
#include "stdio.h"


void nixie_Show();//显示当前所有时间

unsigned char hour=23,minute=59,second=56;//初始时间
unsigned char RunFlag,FlashFlag;//运行，闪烁
unsigned char TimeTypeSelect;//时间类型选择
unsigned char KeyNum;
char str[10];

void main ()
{	

	UART_Init();
	Timer0_Init();

    while(1)
	{
		nixie(6,17);
		nixie(3,17);
		KeyNum=Key();		
		if(KeyNum)
		{
			if(P2&0x01)//注意技巧：不能写P2&0X01==1，此条件永不成立
			{
     			P2&=0xfe;
			}
		    else if(~(P2&0x01))//D1翻转电平，这个if/else的顺序很重要，内容不能颠倒
			{
				P2|=0x01;
			}
		    
			if(KeyNum==1)//时间类型选择
			{
				TimeTypeSelect++;//0.1.2.3.4
				TimeTypeSelect%=5;
			}
			if(KeyNum==2)
			{
				if(TimeTypeSelect==1)//时加一
				{
					hour++;
					hour%=24;
				}
				if(TimeTypeSelect==2)//分加一
				{
					minute++;
					minute%=60;
				}
				if(TimeTypeSelect==3)//秒加一
				{
					second++;
					second%=60;
				}
			}
			if(KeyNum==3)
			{
				if(TimeTypeSelect==1)//时减一
				{
					hour--;
					if(hour==255)hour=23;
				}
				if(TimeTypeSelect==2)//分减一
				{
					minute--;
					if(minute==255)minute=59;
				}
				if(TimeTypeSelect==3)//秒减一
				{
					second--;
					if(second==255)second=59;
				}
				if(TimeTypeSelect==4)
				{
					hour=0;
					minute=0;
					second=0;
				}
			}
			if(KeyNum==4)
			{
				if(TimeTypeSelect==1)
				{
					hour=0;
				}
				if(TimeTypeSelect==2)
				{
					minute=0;
				}
				if(TimeTypeSelect==3)
				{
					second=0;
				}
				if(TimeTypeSelect==4)
				{
//					UART_SendByte(hour/10+0x30);
//					UART_SendByte(hour%10+0x30);
//					UART_SendByte(0x3a);//:
//					UART_SendByte(minute/10+0x30);
//					UART_SendByte(minute%10+0x30);
//					UART_SendByte(0x3a);
//					UART_SendByte(second/10+0x30);
//					UART_SendByte(second%10+0x30);
//					
//					UART_SendByte('\r');//\r
//					UART_SendByte('\n');//\n
					//sprintf(str,"%d:%d:%d\r\n",hour,minute,second);
					sprintf(str,"%d",123);
					Uart_SendString(str);
				}
			}
		}
		if(TimeTypeSelect==0)//0暂停
		{
			RunFlag=0;
			
			P2|=0xE0;
			P2&=0xfd;
			nixie_Show();
		}
		if(TimeTypeSelect==4)//4开始计时
		{
			RunFlag=1;
			P2|=0xE0;
			P2|=0x02;
			nixie_Show();
		}
		if(TimeTypeSelect==1)//1时闪烁
		{
			RunFlag=0;
			P2&=0xfd;
			if(FlashFlag==1)
			{
				P2&=0xDF;
				nixie(8,16);
				nixie(7,16);
				nixie(5,minute/10);
				nixie(4,minute%10);
				nixie(2,second/10);
				nixie(1,second%10);
			}
			else
			{
				P2|=0xE0;
				nixie_Show();
			}
		}
		if(TimeTypeSelect==2)//2分闪烁
		{
			RunFlag=0;
			if(FlashFlag==1)
			{
				P2&=0xBF;
				nixie(8,hour/10);
				nixie(7,hour%10);
				nixie(5,16);
				nixie(4,16);
				nixie(2,second/10);
				nixie(1,second%10);
			}
			else
			{
				P2|=0xE0;
				nixie_Show();
			}
		}
		if(TimeTypeSelect==3)//3秒闪烁
		{
			RunFlag=0;
			if(FlashFlag==1)
			{
				P2&=0x7F;
				nixie(8,hour/10);
				nixie(7,hour%10);
				nixie(5,minute/10);
				nixie(4,minute%10 );
				nixie(2,16);
				nixie(1,16);
			}
			else
			{
				P2|=0xE0;
				nixie_Show();
			}
		}
		

	}
}
 
void nixie_Show()//显示当前所有时间
{
		nixie(8,hour/10); 
		nixie(7,hour%10);
		nixie(5,minute/10);
		nixie(4,minute%10);
		nixie(2,second/10);
		nixie(1,second%10);
}
void Clock_Loop()
{
	if(RunFlag)
	{
		second++;
		if(second==60)
		{
			second=0;minute++;
			if(minute==60)
			{
				minute=0;
				hour++;
				if(hour==24)
				{
					hour=0;
				}
			}
		}
	}
}

void Timer0_Routine () interrupt 1
{
	static unsigned int T0count1,T0count2,T0count3,T0count4;     //静态局部变量，保证不会被重新赋值

	TL0 = 0x66;				         //确保中断时间不变
	TH0 = 0xFC;	
	T0count1++;
	if(T0count1 == 400)              //每隔1000毫秒进入if，灯亮灭变化
	{
		T0count1=0;
		Clock_Loop();
	}
	T0count2++;
	if(T0count2==1)//定时器扫描数码管
	{
		T0count2=0;
		nixie_Loop();
	}
	T0count3++;
	if(T0count3==250)//0.25秒闪烁
	{
		T0count3=0;
		FlashFlag=!FlashFlag;
	}
	T0count4++;
	if(T0count4==10)//定时器扫描按键
	{
		T0count4=0;
		Key_Loop();
	}
}




