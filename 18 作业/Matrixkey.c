 #include <REGX51.H>
 #include <delay.h>
 
 unsigned char Scan_KeyNum;
 /**
  * @brief  矩阵键盘读取按键键码
  * @param  参数无
  * @retval 返回值为键码
	按下并松开后重新赋值并显示
  */  
 int Matrixkey_GetState()
 {
	 //列扫描
	 unsigned int KeyNum=0;
	 P1=0xff;     //全部复位
	 P1_0=0;      //确定扫描列数          
	 if(P1_4==0){ KeyNum=16;}
	 if(P1_5==0){ KeyNum=12;}
	 if(P1_6==0){ KeyNum=8;}
	 if(P1_7==0){ KeyNum=4;}
	 
	 
	 P1=0xff;
	 P1_1=0;
	 if(P1_4==0){ KeyNum=15;}
	 if(P1_5==0){ KeyNum=11;}
	 if(P1_6==0){ KeyNum=7;}
	 if(P1_7==0){ KeyNum=3;}
	 
	 P1=0xff;
	 P1_2=0;
	 if(P1_4==0){ KeyNum=14;}
	 if(P1_5==0){ KeyNum=10;}
	 if(P1_6==0){ KeyNum=6;}
	 if(P1_7==0){ KeyNum=2;}
	 
	 P1=0xff;
	 P1_3=0;
	 if(P1_4==0){ KeyNum=13;}
	 if(P1_5==0){ KeyNum=9;}
	 if(P1_6==0){ KeyNum=5;}
	 if(P1_7==0){ KeyNum=1;}
	 
	 
	 return KeyNum;
 }
 void Matrixkey_Loop(void)
{
	static unsigned char laststate,nowstate;
	laststate=nowstate;
	nowstate=Matrixkey_GetState();
	
	if(laststate==0&&nowstate==1)//更换10位置可以按下即变，不需松手
	{
		Scan_KeyNum=1;	
	}
	if(laststate==0&&nowstate==2)
	{
		Scan_KeyNum=2;	
	}
	if(laststate==0&&nowstate==3)
	{
		Scan_KeyNum=3;	
	}
	if(laststate==0&&nowstate==4)
	{
		Scan_KeyNum=4;	
	}
	
	if(laststate==0&&nowstate==5)//更换10位置可以按下即变，不需松手
	{
		Scan_KeyNum=5;	
	}
	if(laststate==0&&nowstate==6)
	{
		Scan_KeyNum=6;	
	}
	if(laststate==0&&nowstate==7)
	{
		Scan_KeyNum=7;	
	}
	if(laststate==0&&nowstate==8)
	{
		Scan_KeyNum=8;	
	}
	
	if(laststate==0&&nowstate==9)//更换10位置可以按下即变，不需松手
	{
		Scan_KeyNum=9;	
	}
	if(laststate==0&&nowstate==10)
	{
		Scan_KeyNum=10;	
	}
	if(laststate==0&&nowstate==11)
	{
		Scan_KeyNum=11;	
	}
	if(laststate==0&&nowstate==12)
	{
		Scan_KeyNum=12;	
	}
	
	if(laststate==0&&nowstate==13)//更换10位置可以按下即变，不需松手
	{
		Scan_KeyNum=13;	
	}
	if(laststate==0&&nowstate==14)
	{
		Scan_KeyNum=14;	
	}
	if(laststate==0&&nowstate==15)
	{
		Scan_KeyNum=15;	
	}
	if(laststate==0&&nowstate==16)
	{
		Scan_KeyNum=16;	
	}
}


unsigned char Matrixkey(void)
{
	unsigned char temp;
	temp = Scan_KeyNum;     //返回按键值前对Scan_KeyNum清零,防止不按下时返回原值
	Scan_KeyNum = 0;
	return temp;
}
 

