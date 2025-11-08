//// 全局变量默认0；非全局不默认0；

//#include "LCD1602.h"
//#include "Matrixkey.h"

//unsigned char KeyNum;
//unsigned int PassWord,Count, a;

//void main()
//{
//	LCD_Init();
//	LCD_ShowString(1,1,"PassWord:");
//	while(1)
//	{
//		a++;
//		KeyNum=Matrixkey();
//		if(KeyNum)
//		{
//			LCD_ShowNum(2,1,KeyNum,4);
//			if(KeyNum<=10)
//			{
//				if(Count<4)
//				{
//					PassWord*=10;     
//					PassWord+=KeyNum%10;
//					Count++; 
//				}
//				LCD_ShowNum(2,1,PassWord,4);
//			}
//		
//			if(KeyNum==11)
//			{
//				if(PassWord==2345)
//				{
//					LCD_ShowString(1,14,"ok ");
//					PassWord=0;
//					Count=0;
//					LCD_ShowNum(2,1,PassWord,4);
//				}
//				else
//				{
//					LCD_ShowString(1,14,"ERR");
//					PassWord=0;
//					Count=0;
//					LCD_ShowNum(2,1,PassWord,4);
//				}
//			}
//			if(KeyNum==12)
//			{
//				PassWord=0;
//				Count=0;
//				LCD_ShowNum(2,1,PassWord,4);
//			}
//		}
//	}
//}
