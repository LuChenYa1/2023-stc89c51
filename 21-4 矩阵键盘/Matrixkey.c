//#include <REGX51.H>
//#include <delay.h>
// 
// /**
//  * @brief  矩阵键盘读取按键键码
//  * @param  参数无
//  * @retval 返回值为键码
//	按下并松开后重新赋值并显示
//  */  
//unsigned char MatrixKey()
// {
//	 //列扫描
//	 unsigned char KeyNum = 0;
//	 P1=0xff;
//	 P1_0=0;      //确定扫描列数          
//	 if(P1_4==0){delay_ms(20);while(P1_4==0);delay_ms(20);KeyNum=16;}
//	 if(P1_5==0){delay_ms(20);while(P1_5==0);delay_ms(20);KeyNum=12;}
//	 if(P1_6==0){delay_ms(20);while(P1_6==0);delay_ms(20);KeyNum=8;}
//	 if(P1_7==0){delay_ms(20);while(P1_7==0);delay_ms(20);KeyNum=4;}
//	 
//	 
//	 P1=0xff;
//	 P1_1=0;
//	 if(P1_4==0){delay_ms(20);while(P1_4==0);delay_ms(20);KeyNum=15;}
//	 if(P1_5==0){delay_ms(20);while(P1_5==0);delay_ms(20);KeyNum=11;}
//	 if(P1_6==0){delay_ms(20);while(P1_6==0);delay_ms(20);KeyNum=7;}
//	 if(P1_7==0){delay_ms(20);while(P1_7==0);delay_ms(20);KeyNum=3;}
//	 
//	 P1=0xff;
//	 P1_2=0;
//	 if(P1_4==0){delay_ms(20);while(P1_4==0);delay_ms(20);KeyNum=14;}
//	 if(P1_5==0){delay_ms(20);while(P1_5==0);delay_ms(20);KeyNum=10;}
//	 if(P1_6==0){delay_ms(20);while(P1_6==0);delay_ms(20);KeyNum=6;}
//	 if(P1_7==0){delay_ms(20);while(P1_7==0);delay_ms(20);KeyNum=2;}
//	 
//	 P1=0xff;
//	 P1_3=0;
//	 if(P1_4==0){delay_ms(20);while(P1_4==0);delay_ms(20);KeyNum=13;}
//	 if(P1_5==0){delay_ms(20);while(P1_5==0);delay_ms(20);KeyNum=9;}
//	 if(P1_6==0){delay_ms(20);while(P1_6==0);delay_ms(20);KeyNum=5;}
//	 if(P1_7==0){delay_ms(20);while(P1_7==0);delay_ms(20);KeyNum=1;}
//	 
//	 
//	 return KeyNum;
// }


 #include <REGX51.H>
 #include <delay.h>
 
 //定时器扫描矩阵键盘
 unsigned char Scan_MatrixKeyNum;
 /**
  * @brief  矩阵键盘读取按键键码
  * @param  无
  * @retval 键码KeyNum
	按下并松开后重新赋值并显示
  */  
unsigned char MatrixKey_GetState()
 {
	 //列扫描
	 unsigned char MatrixKeyNum = 0;//这一步赋值0很重要，不能省略
	 P1=0xff;     //全部复位
	 P1_0=0;      //确定扫描列数          
	 if(P1_4==0){MatrixKeyNum=16;}
	 if(P1_5==0){MatrixKeyNum=12;}
	 if(P1_6==0){MatrixKeyNum=8;}
	 if(P1_7==0){MatrixKeyNum=4;}
	 
	 
	 P1=0xff;
	 P1_1=0;
	 if(P1_4==0){MatrixKeyNum=15;}
	 if(P1_5==0){MatrixKeyNum=11;}
	 if(P1_6==0){MatrixKeyNum=7;}
	 if(P1_7==0){MatrixKeyNum=3;}
	 
	 P1=0xff;
	 P1_2=0;
	 if(P1_4==0){MatrixKeyNum=14;}
	 if(P1_5==0){MatrixKeyNum=10;}
	 if(P1_6==0){MatrixKeyNum=6;}
	 if(P1_7==0){MatrixKeyNum=2;}
	 
	 P1=0xff;
	 P1_3=0;
	 if(P1_4==0){MatrixKeyNum=13;}
	 if(P1_5==0){MatrixKeyNum=9;}
	 if(P1_6==0){MatrixKeyNum=5;}
	 if(P1_7==0){MatrixKeyNum=1;}
	  
	 return MatrixKeyNum;
 }

//unsigned char MatrixKey_GetState()
// {
//	 //线翻转法扫描(失败品)
//	 unsigned char MatrixKeyNum = 0, line = 0, column = 0;
//	 
//	 P1=0xF0;
//	 if(P1 != 0xF0)
//	 {
////		delay_ms(1);
//		if(P1 != 0xF0)
//		{
//			if(P1 == 0xE0)
//			{line = 4;P2_1 = ~P2_1;}
//			else if(P1 == 0xD0)line = 3;
//			else if(P1 == 0xB0)line = 2;
//			else if(P1 == 0x70)line = 1;
//		}
//	 }
//	 P1 = 0x0F;
//	 if(P1 != 0x0F)
//	 {
////		delay_ms(1);
//		if(P1 != 0x0F)
//		{
//			if(P1 == 0x0E){P2_0 = ~P2_0;column = 4;}
//			else if(P1 == 0x0D)column = 3;
//			else if(P1 == 0x0B)column = 2;
//			else if(P1 == 0x07)column = 1;
//		}
//	  }
//	 if(MatrixKeyNum == 16)P2_5 = ~P2_5;
//	 MatrixKeyNum = (line -1) * 4 + column;
//	 return MatrixKeyNum;
// }


/**
  * @brief  中断时执行的函数，功能是检测按键落下并返回相应的值，去除了原来的delay和死循环
  * @param  无
  * @retval 无
  */
void MatrixKey_Loop(void)
{
	static unsigned char laststate,nowstate;
	laststate = nowstate;
	nowstate = MatrixKey_GetState();
	//更换10位置可以按下即变，不需松手
	if(laststate==1&&nowstate==0)Scan_MatrixKeyNum = 1;	
	else if(laststate==2 && nowstate == 0)Scan_MatrixKeyNum = 2;	
	else if(laststate==3 && nowstate == 0)Scan_MatrixKeyNum = 3;	
	else if(laststate==4 && nowstate == 0)Scan_MatrixKeyNum = 4;	
	else if(laststate==5 && nowstate == 0)Scan_MatrixKeyNum = 5;	
	else if(laststate==6 && nowstate == 0)Scan_MatrixKeyNum = 6;	
	else if(laststate==7 && nowstate == 0)Scan_MatrixKeyNum = 7;	
	else if(laststate==8 && nowstate == 0)Scan_MatrixKeyNum = 8;	
	else if(laststate==9 && nowstate == 0)Scan_MatrixKeyNum = 9;	
	else if(laststate==10&& nowstate == 0)Scan_MatrixKeyNum = 10;	
	else if(laststate==11&& nowstate == 0)Scan_MatrixKeyNum = 11;	
	else if(laststate==12&& nowstate == 0)Scan_MatrixKeyNum = 12;	
	else if(laststate==13&& nowstate == 0)Scan_MatrixKeyNum = 13;	
	else if(laststate==14&& nowstate == 0)Scan_MatrixKeyNum = 14;	
	else if(laststate==15&& nowstate == 0)Scan_MatrixKeyNum = 15;	
	else if(laststate==16&& nowstate == 0)Scan_MatrixKeyNum = 16;	
}
/**
  * @brief  返回按键键码
  * @param  无
  * @retval 键码
  */
unsigned char MatrixKey(void)
{
	unsigned char temp;
	temp = Scan_MatrixKeyNum;     //返回按键值前对Scan_KeyNum清零,防止不按下时返回原值
	Scan_MatrixKeyNum = 0;
	return temp;
}
