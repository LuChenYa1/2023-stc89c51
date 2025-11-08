 #include <REGX51.H>
 #include <delay.h>
 
 //定时器扫描矩阵键盘
 unsigned char Scan_MatrixKeyNum;
 /**
  * @brief  矩阵键盘读取按键键码
  * @param  无
  * @retval 键码KeyNum
  */  
unsigned char MatrixKey_GetState(void)
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
	else if(laststate==0 && nowstate == 2 )Scan_MatrixKeyNum = 2;	
	else if(laststate==0 && nowstate == 3 )Scan_MatrixKeyNum = 3;	
	else if(laststate==0 && nowstate == 4 )Scan_MatrixKeyNum = 4;	
	else if(laststate==0 && nowstate == 5 )Scan_MatrixKeyNum = 5;	
	else if(laststate==0 && nowstate == 6 )Scan_MatrixKeyNum = 6;	
	else if(laststate==0 && nowstate == 7 )Scan_MatrixKeyNum = 7;	
	else if(laststate==0 && nowstate == 8 )Scan_MatrixKeyNum = 8;	
	else if(laststate==0 && nowstate == 9 )Scan_MatrixKeyNum = 9;	
	else if(laststate==0 && nowstate == 10)Scan_MatrixKeyNum = 10;	
	else if(laststate==0 && nowstate == 11)Scan_MatrixKeyNum = 11;	
	else if(laststate==0 && nowstate == 12)Scan_MatrixKeyNum = 12;	
	else if(laststate==0 && nowstate == 13)Scan_MatrixKeyNum = 13;	
	else if(laststate==0 && nowstate == 14)Scan_MatrixKeyNum = 14;	
	else if(laststate==0 && nowstate == 15)Scan_MatrixKeyNum = 15;	
	else if(laststate==0 && nowstate == 16)Scan_MatrixKeyNum = 16;	
}
/**
  * @brief  返回按键键码
  * @param  无
  * @retval 键码
  */
unsigned char MatrixKey(void)
{
	unsigned char temp;
	temp = Scan_MatrixKeyNum;     //返回按键值前对Scan_KeyNum清零，防止不按下时返回原值
	Scan_MatrixKeyNum = 0;
	return temp;
}

