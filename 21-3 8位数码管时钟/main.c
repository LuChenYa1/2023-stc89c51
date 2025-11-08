#include <REGF51RC.H>
#include <Timer0_Init.h>
#include <nixie.h>
#include <INT0_Init.h>
#include <Key.h>

#define Start 1
#define Stop  0
#define uint8_t  unsigned char
uint8_t h = 23, m = 59, s = 56, State, KeyNum, Mode, Flag_INC_DEC, ht, mt, st, Flag_Mode;
void Get_Mode(void);
void nixie_Show(void);

void main()
{
	Timer0_Init();
	INT0_Init();
	
	while(1)
	{
		 Get_Mode();
		 nixie_Show();
		 if(Flag_INC_DEC == 1)//进入暂停自加自减模式
		 {
			 if(KeyNum == 1)  //按下1，自加一次
			 {
				 s ++;
				 if(s == 60)
				 {
					 s = 0;
					 m ++;
					 if(m == 60)
					 {
						 m = 0;
						 h ++;
						 if(h == 24) h = 0;
					 }
				 }
			 }	
			 else if(KeyNum == 2)//按下2，自减一次
			 {
				 s --;
				 if(s == 0)
				 {
					 s = 59;
					 if(m != 0)m --;
					 if(m == 0)
					 {
						 m = 59;
						 if(h != 0)h--;
						 if(h == 0) h = 23;
					 }
				  }
			  }
			 else if(KeyNum == 3)//按下3，解除暂停自加自减模式
			 {
				 ht = h; mt = m; st = s; 
				 Flag_INC_DEC = 0; 
			 }
		 }
	}
}

//由按键得到模式
void Get_Mode(void)
{
	KeyNum = Key();
	if(KeyNum == 1)Mode = 1;
	else if(KeyNum == 2)Mode = 2;
	else if(KeyNum == 3)Mode = 3;
	else if(KeyNum == 4)Mode = 4;
}

//刷新显示
void nixie_Show(void)
{
	nixie(3, 17);//显示分隔号
	nixie(6, 17);
	
	nixie(1, h / 10);
	nixie(2, h % 10);
	
	nixie(4, m / 10);
	nixie(5, m % 10);
	
	nixie(7, s / 10);
	nixie(8, s % 10);
}

//定时中断函数
void Timer0_Routine () interrupt 1
{
	static unsigned int T0count;     //静态局部变量，保证不会被重新赋值

	TL0 = 0x66;				         //确保中断时间不变
	TH0 = 0xFC;	
	T0count++;
	Key_Loop();                      //定时器扫描按键
	if(T0count == 1000)              //每隔1秒进入if，灯亮灭变化
	{
		T0count=0;
		if(State == Start)
		{
			if(Mode == 1)            //一号键顺计时
			{
				if(Flag_INC_DEC == 0)
				{
					if(Flag_Mode == 1)
					{
						Flag_Mode = 0;
						h = ht; m = mt; s = st;
					}
					s ++;
					if(s == 60)
					{
						s = 0;
						m ++;
						if(m == 60)
						{
							m = 0;
							h ++;
							if(h == 24) h = 0;
						}
					}
				}
			}
			else if(Mode == 2)       //二号键倒计时
			{
				if(Flag_INC_DEC == 0)
				{
					if(Flag_Mode == 1)
					{
						Flag_Mode = 0;
						h = ht; m = mt; s = st;
					}
					if(s != 0)s --;
					if(s == 0)
					{
						s = 59;
						if(m != 0)m --;
						if(m == 0)
						{
							m = 59;
							if(h != 0)h--;
							if(h == 0) h = 23;
						}
					}
				}
			}
			else if(Mode == 3)      //三号键归零
			{
				if(Flag_INC_DEC == 0)
				{
					h = 0; m = 0; s = 0;
				}
			}
			else if(Mode == 4)      //四号键暂停
			{
				Flag_INC_DEC = 1;   //进入暂停自加自减模式
				Flag_Mode = 1;
			}
		}
	}
}

//外部中断函数
void int0_Routine() interrupt 0
{
	State = !State;//状态转换，控制启停
}
