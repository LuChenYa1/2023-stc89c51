#include <REGX51.H>
#include "MatrixLED.h"
#include "MatrixKey.h"
#include "Timer0_Init.h"
#include "Data_MatrixLED.h"
#include "nixie.h"
#include "delay.h"

#define  uint8_t unsigned char 
uint8_t a, Offset, Count;     //滚屏显示变量
uint8_t MatrixKeyNum, Mode, Flag_Number, Length_Number, Flag_Start_Stop, Num_Count;
unsigned long int Number; 
uint8_t Number_Array[8] = {0};//存放输入的数字

void nixie_Show();
void ShowNumber_Act(uint8_t Number);
void Array_GetNumber(void);
long int Pow(char x, char y);

void main ()
{
	Timer0_Init();
	MatrixLED_Init();
	nixie(8,16);//消残影
	

	// while (1)//四、滚屏显示名字
    // {
    // 	
    // }

//五、滚屏显示输入数字
	while(1)
	{
		MatrixKeyNum = MatrixKey();
		if(MatrixKeyNum)                            	  
		{ 
			if(MatrixKeyNum <= 10)                	  	  //确保输入数字时，输入的是
														  //合法的小于等于10的数字键
			{
				if(Num_Count < 8)                         //最大位数为8
				{
					Number *= 10;                         //新输入的数字作个位
					Number += MatrixKeyNum % 10;          //输入10即为0
					Num_Count++;                          //输入一个数，总位数加一
				}			
			}		
			else if(MatrixKeyNum == 11)                   //11‘A’键，确认最终输入的数字
			{
				Length_Number = Num_Count;
				Num_Count = 8; 
				Array_GetNumber();
			}
			else if(MatrixKeyNum == 12)                   //12‘B’键，启停滚动显示输入数字
			{
				Flag_Start_Stop = !Flag_Start_Stop;
			}
			else if(MatrixKeyNum == 13)                   //13‘C’键，暂停滚屏显示输入数字
			{
				Flag_Start_Stop = 0;
			}
			else if(MatrixKeyNum == 14)                   //14‘D’键，重新输入数字，原数字作废
			{
				Num_Count = 0;                            //位数清零
				Number = 0;								  //数字清零
			}
			else if(MatrixKeyNum == 15)                   //15‘E’键
			{
				Mode ++;
				Mode %= 5;
			}
		}
		nixie_Show();//数码管显示当前正在输入的数字
		if(Flag_Start_Stop == 1)//滚屏显示最终输入的数字
		{
			if(Flag_Number == 0)ShowNumber_Act(Number_Array[0]);	
			else if(Flag_Number == 1)ShowNumber_Act(Number_Array[1]);	
			else if(Flag_Number == 2)ShowNumber_Act(Number_Array[2]);
			else if(Flag_Number == 3)ShowNumber_Act(Number_Array[3]);	
			else if(Flag_Number == 4)ShowNumber_Act(Number_Array[4]);
			else if(Flag_Number == 5)ShowNumber_Act(Number_Array[5]);	
			else if(Flag_Number == 6)ShowNumber_Act(Number_Array[6]);
			else if(Flag_Number == 7)ShowNumber_Act(Number_Array[7]);
		}
		if(Mode == 1)MatrixLED_8_ShowColumn(8, 0xff);//一、显示一行
		else if(Mode == 2)
		{
			 //二、显示数字0
			for(a = 1; a < 9; a++)
			{
				MatrixLED_8_ShowColumn(a, Show0[a-1]);
			}
		}
		else if(Mode == 3)
		{
			//三、滚屏显示0~3
			for(a = 1; a < 9; a++)
			{
				MatrixLED_8_ShowColumn(a,Show0_3[a+Offset-1]);
			}
			Count++;
			if(Count == 10)
			{
				Count = 0;
				Offset += 1;
				if(Offset == 32)     //总列数40，所以最左端增加到40-8就要回到0，防止越界
				{
					Offset = 0;
				}
			}
			
		}
		else if(Mode == 4)
		{
			for(a = 1; a < 17; a++)
			{
				MatrixLED_16_ShowColumn(a,ShowName_H[a+Offset-1], ShowName_L[a+Offset-1]);
			}
			Count++;
			if(Count == 10)
			{
				Count = 0;
				Offset ++;
				if(Offset == 48)     //以上，同理
				{
					Offset = 0;
				}
			}
		}
	}
}

//将最终输入的数字依次赋值给数组，方便后期从大到小滚屏显示
void Array_GetNumber()
{
	long int i = 10000000, temp;//用于确定输入数字的总位数
	char j = 0, m;//数字的总位数
	while(1)
	{
		if(Number / i != 0)
		{	
			Number_Array[0] = Number / i % 10;//将数字最高位赋值给数组首位
			temp = i;//保存此时间接代表总位数的i值
			while(1)
			{
				temp /= 10;
				if(temp != 0)j++;//用j得到数字的直接位数
				else break;
			}
			break;
		}
		i /= 10;
	}
	for(m = 1; m < j+1; m++)//数字从大到小依次赋值给数组
	{
		Number_Array[m] = Number / (i / Pow(10, m)) % 10;
	}
}

//x的y次方
long int Pow(char x, char y)
{
	long int sum = 1, i;
	for(i = 0; i < y; i++)
	{
		sum = sum * x;
	}
	return sum;
}

//数码管显示输入的数字
void nixie_Show()
{
	nixie(1, Number / 10000000 % 10);
	nixie(2, Number / 1000000 % 10);
	nixie(3, Number / 100000 % 10);
	nixie(4, Number / 10000 % 10);
	nixie(5, Number / 1000 % 10);
	nixie(6, Number / 100 % 10);
	nixie(7, Number / 10 % 10);
	nixie(8, Number % 10);
}

//定时器中断函数
void Timer0_Routine () interrupt 1
{
	static unsigned int T0count1, T0count2;//静态局部变量

	TL0 = 0x66;				               //重新赋初值
	TH0 = 0xFC;	
	
	T0count1 ++;
	if(T0count1 == 20)
	{
		T0count1 = 0;
		MatrixKey_Loop();                  //定时器扫描矩阵键盘
	}
	
	T0count2++;
	if(T0count2 == 2)                      //定时器扫描数码管
	{
		T0count2 = 0;
		nixie_Loop();
	}
}

//滚屏显示单个数字
void ShowNumber_Act(uint8_t Number)
{
	for(a = 1; a < 17; a++)
	{
		switch (Number)
		{
			case 0:MatrixLED_16_ShowColumn(a,Show0_H[a+Offset-1], Show0_L[a+Offset-1]);break;
			case 1:MatrixLED_16_ShowColumn(a,Show1_H[a+Offset-1], Show1_L[a+Offset-1]);break;
			case 2:MatrixLED_16_ShowColumn(a,Show2_H[a+Offset-1], Show2_L[a+Offset-1]);break;
			case 3:MatrixLED_16_ShowColumn(a,Show3_H[a+Offset-1], Show3_L[a+Offset-1]);break;
			case 4:MatrixLED_16_ShowColumn(a,Show4_H[a+Offset-1], Show4_L[a+Offset-1]);break;
			case 5:MatrixLED_16_ShowColumn(a,Show5_H[a+Offset-1], Show5_L[a+Offset-1]);break;
			case 6:MatrixLED_16_ShowColumn(a,Show6_H[a+Offset-1], Show6_L[a+Offset-1]);break;
			case 7:MatrixLED_16_ShowColumn(a,Show7_H[a+Offset-1], Show7_L[a+Offset-1]);break;
			case 8:MatrixLED_16_ShowColumn(a,Show8_H[a+Offset-1], Show8_L[a+Offset-1]);break;
			case 9:MatrixLED_16_ShowColumn(a,Show9_H[a+Offset-1], Show9_L[a+Offset-1]);break;
		}
	}
	Count++;
	if(Count == 3)
	{
		Count = 0;
		Offset ++;
		if(Offset == 32)     //显示完一个数字后，Flag_Number自增，显示下一个数字
		{
			Offset = 0;
			Flag_Number++;
			Flag_Number %= Length_Number;
		}
	}
}
