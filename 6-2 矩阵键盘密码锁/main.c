#include "Matrixkey.h"
#include <LCD1602.h>
#include <delay.h>
unsigned char KeyNum;
unsigned int Password,count;         			  //ȫ�ֱ���Ĭ��0����ȫ�ֲ�Ĭ��

void main ()
{
	LCD_Init();                        			  //LCDʹ��ǰ��
	LCD_ShowString(1,1,"Password:");
	
	while(1)
	{
		KeyNum=Matrixkey();
		if(KeyNum)                            	  //ѭ���ܿ죬Ҫ��ȥ0���������ֵĸ��ţ�������û���ü�ִ�У�KeyNum�ͻᱻ��ֵ0
		{ 
			if(KeyNum<=10)                	  	  //��֤�����λ��������ʮ��������
			{
				if(count<4)                       //��֤����4λ���룬������λû��
				{
					Password*=10;                 //��ʮ��һ
					Password+=KeyNum%10;          //��ʮ����0
					count++;                      //������һ����֤λ��
					LCD_ShowNum(2,1,Password,4);      //������ʾ,������������ν
				}
				
			}
				
			if(KeyNum==11)                        //����11	ȷ������
			{
				if(Password==2345)                //���������ȷ
				{
					LCD_ShowString(1,14,"ok ");   //��ʾOK
					count=0;                      //��������
					Password=0;                   //��������
					delay(200);                   //�ӳ���ʾ
					LCD_ShowString(1,14,"   ");   //������ʾ
					LCD_ShowNum(2,1,Password,4);  //������ʾ
				}
				else                              //����������
				{
					LCD_ShowString(1,14,"err");   //��ʾerr
					delay(200);                   //�ӳ���ʾ
					count=0;                      //��������
					Password=0;                   //��������
					LCD_ShowString(1,14,"   ");   //������ʾ
					LCD_ShowNum(2,1,Password,4);  //������ʾ
				}
			}
				if(KeyNum==12)                    //��12  ȫ�����㣬������ʾ
				{
					Password=0;
					count=0;
					LCD_ShowNum(2,1,Password,4);
				}
		}	
	}
}

