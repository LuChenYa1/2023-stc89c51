#include <REGX51.H>
#include "nixie.h"
#include "Timer0_Init.h"
#include "Key.h"
#include "UART.h"
#include "delay.h"

unsigned char knum;
unsigned char h=23,f=59,s=56,h_s,h_g,f_s,f_g,s_s,s_g;
unsigned char TimeSelect,Flag,Sign;
 
void main ()
{
	Timer0_Init();
	UART_Init();
	Sign=1;
    while(1)
	{
		nixie(3,10);
		nixie(6,10);
		if(TimeSelect==0)
		{
			nixie(1,h_s);
			nixie(2,h_g);	
			nixie(4,f_s);	
			nixie(5,f_g);
			nixie(7,s_s);
			nixie(8,s_g);
		}
		if(TimeSelect==1 && Flag==1){P2=~0x01;
		nixie(1,h_s);nixie(2,h_g);nixie(4,f_s);nixie(5,f_g);nixie(7,s_s);nixie(8,s_g);delay(100);}//灯闪烁
		if(TimeSelect==1 && Flag==0){P2=0xff;
		nixie(1,11 );nixie(2,11);nixie(4,f_s);nixie(5,f_g);nixie(7,s_s);nixie(8,s_g);}//时闪烁
		if(TimeSelect==2 && Flag==1){P2=~0x02;
		nixie(1,h_s);nixie(2,h_g);nixie(4,f_s);nixie(5,f_g);nixie(7,s_s);nixie(8,s_g);delay(100);}
		if(TimeSelect==2 && Flag==0){P2=0xff;
		nixie(1,h_s);nixie(2,h_g);nixie(4,11);nixie(5,11);nixie(7,s_s);nixie(8,s_g);}//分闪烁
		if(TimeSelect==3 && Flag==1){P2=~0x04;
		nixie(1,h_s);nixie(2,h_g);nixie(4,f_s);nixie(5,f_g);nixie(7,s_s);nixie(8,s_g);delay(100);}
		if(TimeSelect==3 && Flag==0){P2=0xff;
		nixie(1,h_s);nixie(2,h_g);nixie(4,f_s);nixie(5,f_g);nixie(7,11);nixie(8,11);} //秒闪烁
			
	    knum=Key();
		if(knum)
		{
			if(knum==1) 
			{
				TimeSelect++;
				TimeSelect%=4;
				
				if(TimeSelect==1&&TimeSelect==2&&TimeSelect==3)
				{
					 Sign=1;//停止计时
				}
				else
				{
					Sign=0;//开始计时
				}
			}
			if(knum==2)
			{
				if(TimeSelect==0)Sign=~Sign;
				if(TimeSelect==1)h++;//加一
				if(TimeSelect==2)f++;
				if(TimeSelect==3)s++;
			}
			if(knum==3)
			{
				if(TimeSelect==0)
				{
					h=0;f=0;s=0;//清零
					Sign=1;//暂停
				}
				if(TimeSelect==1)h--;//减一
				if(TimeSelect==2)f--;
				if(TimeSelect==3)s--;
			}
			if(knum==4)
			{
				if(TimeSelect==1)h=0;//对应变量清零
				if(TimeSelect==2)f=0;
				if(TimeSelect==3)s=0; 
				if(TimeSelect==0)//发送时间
				{
					UART_SendByte(h);
					UART_SendByte(0x3a);
					UART_SendByte(f);
					UART_SendByte(0x3a);
					UART_SendByte(s);
				}
			}
		}
		
	}
}

void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count1,T0Count2;
	TL0 = 0x66;		 
	TH0 = 0xFC;	
	if(Sign==0)
	{
		T0Count1++;
		if(T0Count1>=1000)
		{
			T0Count1=0;
			s++;
			if(s==60)
			{
				s=0;
				f++;
				if(f==60)
				{
					f=0;
					h++;
					if(h==24)
					{
						h=0;
					}
				}
			}
			h_s=h/10;
			h_g=h%10;
			f_s=f/10;
			f_g=f%10;
			s_s=s/10;
			s_g=s%10;
		}
	}
	T0Count2++;
	if(T0Count2==500)
	{
		T0Count2=0;
		Flag=~Flag;
	}
	 
}
 

