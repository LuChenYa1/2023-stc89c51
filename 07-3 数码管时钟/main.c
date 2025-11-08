//#include <REGX51.H>
//#include "Timer0_Init.h"
//#include "nixie.h"
//#include "delay.h"

//unsigned char ms_g,ms_s,ms_b,s_g,s_s,f;       
//unsigned char s=1,f=2;                  //，秒，分
//unsigned int ms=159;                    //毫秒
//void main ()
//{
//	Timer0_Init();
//    while(1)
//	{
//	    nixie(7,17);         //分隔符
//		nixie(4,17);         //分隔符
//		
//		nixie(1,ms_g);       //显示ms个位
//		nixie(2,ms_s);       //显示ms十位
//		nixie(3,ms_b);       //显示ms百位
//		nixie(5,s_g);        //显示s个位
//		nixie(6,s_s);        //显示s十位
//		nixie(8,f);          //显示分
//	}
//}

//void Timer0_Routine () interrupt 1
//{
//	static unsigned int T0count;     //静态局部变量，保证不会被重新赋值

//	TL0 = 0x66;				         //确保中断时间不变
//	TH0 = 0xFC;	
//	T0count++;
//	if(T0count == 10)               //1ms计数加一
//	{
//		T0count=0;
//		ms++;
//		if(ms==999)                  //毫秒 1000进位加一
//		{
//			ms=0;
//			s++;
//			if(s==59)                //秒 60位加一
//			{
//				s=0;
//				f++;
//				if(f==9)             //分到九清零
//				{
//					f=0;
//					ms=0;
//					s=0;
//				}
//			}
//		}
//		ms_g=ms%10;
//		ms_s=ms%100/10;
//		ms_b=ms/100;
//		s_g=s%10;
//		s_s=s/10;
//	}
//}

