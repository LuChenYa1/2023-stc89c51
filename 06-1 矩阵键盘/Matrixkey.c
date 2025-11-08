 #include <REGX51.H>
 #include <delay.h>
 #include <LCD1602.h>
 
 /**
  * @brief  矩阵键盘读取按键键码
  * @param  无
  * @retval 键码KeyNum
	按下并松开后重新赋值并显示
  */  
 int Matrixkey()
 {
	 //列扫描
	 unsigned int KeyNum;
	 P1=0xff;     //全部复位
	 P1_0=0;      //确定扫描列数          
	 if(P1_4==0){delay(20);while(P1_4==0);delay(20);KeyNum=16;}
	 if(P1_5==0){delay(20);while(P1_5==0);delay(20);KeyNum=12;}
	 if(P1_6==0){delay(20);while(P1_6==0);delay(20);KeyNum=8;}
	 if(P1_7==0){delay(20);while(P1_7==0);delay(20);KeyNum=4;}
	 
	 
	 P1=0xff;
	 P1_1=0;
	 if(P1_4==0){delay(20);while(P1_4==0);delay(20);KeyNum=15;}
	 if(P1_5==0){delay(20);while(P1_5==0);delay(20);KeyNum=11;}
	 if(P1_6==0){delay(20);while(P1_6==0);delay(20);KeyNum=7;}
	 if(P1_7==0){delay(20);while(P1_7==0);delay(20);KeyNum=3;}
	 
	 P1=0xff;
	 P1_2=0;
	 if(P1_4==0){delay(20);while(P1_4==0);delay(20);KeyNum=14;}
	 if(P1_5==0){delay(20);while(P1_5==0);delay(20);KeyNum=10;}
	 if(P1_6==0){delay(20);while(P1_6==0);delay(20);KeyNum=6;}
	 if(P1_7==0){delay(20);while(P1_7==0);delay(20);KeyNum=2;}
	 
	 P1=0xff;
	 P1_3=0;
	 if(P1_4==0){delay(20);while(P1_4==0);delay(20);KeyNum=13;}
	 if(P1_5==0){delay(20);while(P1_5==0);delay(20);KeyNum=9;}
	 if(P1_6==0){delay(20);while(P1_6==0);delay(20);KeyNum=5;}
	 if(P1_7==0){delay(20);while(P1_7==0);delay(20);KeyNum=1;}
	 
	 
	 return KeyNum;
 }

