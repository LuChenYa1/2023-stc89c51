//#include <REGX51.H>
//#include <LCD1602.h>
//#include <Timer0_Init.h>

//unsigned char sec=52,min=59,hour=23;  //ʱ����
//void main()
//{
//	Timer0_Init();           //��������
//	LCD_Init();
//	while(1)
//	{
//		LCD_ShowString(1,1,"Clock:");
//		LCD_ShowNum(2,1,hour,2);
//		LCD_ShowChar(2,3,':');
//		LCD_ShowNum(2,4,min,2);
//		LCD_ShowChar(2,6,':');
//		LCD_ShowNum(2,7,sec,2);
//	}
//	
//}

//void Timer0_Routine () interrupt 1   //�ж�ִ�к���ʱ��Ҫ��϶̣�����̫��
//{
//	static unsigned int T0count;     //��̬�ֲ���������֤���ᱻ���¸�ֵ

//	TL0 = 0x66;				         //ȷ���ж�ʱ�䲻��
//	TH0 = 0xFC;	
//	T0count++;
//	
//	if(T0count == 1000)              //ÿ��1000���룬������仯
//	{
//		T0count=0;                   
//		sec++;
//		if(sec==60)                  //��60��һ
//		{
//			sec=0;
//			min++;
//			if(min==60)
//			{
//				min=0;
//				hour++;
//				if(hour==24)
//				{
//					hour=0;
//				}
//			}
//		}		
//	}
//}

#include <REGX51.H>
#include<intrins.h>
#define uint unsigned int
#define uchar unsigned char
	
void delay(uchar z);    //函数声明

void Timer0Init();     //函数声明
//----------------------------------------------------------------------
sbit RedLED=P1^0;     // 定义绿灯的I/O口

sbit GreenLED=P1^1;   // 定义红灯的I/O口 

sbit Key=P3^4;       // 定义按键的I/O口

typedef enum
{
	Key_Check,
	Key_Press,
	Key_Release,
	Key_Over,
}Key_State;

Key_State keyState = Key_Check;//给按键状态设置初始值

unsigned char keyPressCount = 0; // 定义全局变量记录按键按下次数

unsigned int keyPressTime = 20; // 定义全局变量记录按键按下时间

int KeyStartTime;

void Key_Scan(void);
//----------------------------------------------------------------------

void main()
{
    // 初始状态：红灯亮、绿灯灭
    RedLED=0;                 
  	GreenLED=1;               
    
    Timer0Init();             // 初始化定时器0

    while(1) 	
	{        
        if(keyState == Key_Over)      //只有松手后，即按压时间记录结束，该标志位才会置一，即为松手执行功能，带长按时间检测
	    {
		    keyState = Key_Check;     //保证以下程序只在刚按下时执行一次
            
            keyPressTime = 20;        //按压时间“清零”，方便下次按压时计时
	    }

        if(keyState == Key_Release)
        {
            if(keyPressTime >= 2000)  // 长按超过2秒
            {	
                keyPressCount = 0;
                RedLED = 0;           // 复位初值，红灯亮，绿灯灭
                GreenLED = 1;				
            }
            else
            {
                if(keyPressCount==1)  // 根据按键按下次数控制灯的亮灭				
                {
                    RedLED = 1;
                    GreenLED = 0;
                } 
                else if(keyPressCount==2)
                {
                    RedLED = 0;
                    GreenLED = 0;
                } 
                else if(keyPressCount==3)// 按键第三次按下
                {
                    RedLED = 0;          // 复位初值，红灯亮，绿灯灭
                    GreenLED = 1;														
                }
            }
        }
	}
}

void Timer0_ISR() interrupt 1    // 定时器0中断服务函数
{ 
    // TH0 = (65536-50000)/256;   // 设置定时器0的初始值，定时50ms
    // TL0 = (65536-50000)%256; 

    // 每隔1毫秒中断一次
    TL0 = 0x66;				         
	TH0 = 0xFC;	       

	if(++ KeyStartTime == 10)//每隔10ms满足条件，扫描按键
	{
		KeyStartTime = 0;
		Key_Scan();
	}
}

void Key_Scan(void)
{
	switch(keyState)
	{
		case Key_Check://平常状态
		{
			if(Key == 0)
			{
				keyState = Key_Press;//在检测状态下，检测是否有按键按下，如果有，转换为按下状态
			}
		};
		break;
		case Key_Press://在按下状态下，判断具体是哪个按键按下，给予键值
		{
			keyPressCount ++;
            keyPressCount %= 4;

			keyState = Key_Release;//不管松没松手，直接进入“松手”状态
		};
		break;
		case Key_Release://在“松手”状态下，判断是否真的松手
		{
			if(Key == 0)
			{
				keyPressTime += 10;//过了10ms，发现还没松手，按压时间+10
			}
			else//真的松手了，判断为短按
			{
				keyState = Key_Over;//此时为按下后松手的状态
			}
		};
		break;
		default:break;
	}
}

void Timer0Init()     // 定时器0函数  以主频12M
{
    
    TMOD&=0xF0;                        //TMOD清0
    TMOD|=0x01;                       // 设置定时器0为工作方式1（16位定时器）
    TH0=(65536-50000)/256;           // 设置定时器0的初始值，定时50ms
    TL0=(65536-50000)%256;      
    TR0=1;                          // 开启定时器0    
    ET0=1;                         // 允许定时器0中断   
    EA=1;                         // 开启总中断

}

void delay(uchar z)       //按键延时消抖
{
	uchar x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}






