 #include <REGX51.H>
 #include <Delay.h>
 
 unsigned char Matrixkey(void)
 {
	 //列扫描
	 unsigned char MatrixKeyNum = 0;
	 P1=0xff;
	 P1_0=0;      //确定扫描列数          
	 if(P1_4==0){Delay_ms(20);while(P1_4==0);Delay_ms(20);MatrixKeyNum=16;}
	 if(P1_5==0){Delay_ms(20);while(P1_5==0);Delay_ms(20);MatrixKeyNum=12;}
	 if(P1_6==0){Delay_ms(20);while(P1_6==0);Delay_ms(20);MatrixKeyNum=8;}
	 if(P1_7==0){Delay_ms(20);while(P1_7==0);Delay_ms(20);MatrixKeyNum=4;}
	 
	 
	 P1=0xff;
	 P1_1=0;
	 if(P1_4==0){Delay_ms(20);while(P1_4==0);Delay_ms(20);MatrixKeyNum=15;}
	 if(P1_5==0){Delay_ms(20);while(P1_5==0);Delay_ms(20);MatrixKeyNum=11;}
	 if(P1_6==0){Delay_ms(20);while(P1_6==0);Delay_ms(20);MatrixKeyNum=7;}
	 if(P1_7==0){Delay_ms(20);while(P1_7==0);Delay_ms(20);MatrixKeyNum=3;}
	 
	 P1=0xff;
	 P1_2=0;
	 if(P1_4==0){Delay_ms(20);while(P1_4==0);Delay_ms(20);MatrixKeyNum=14;}
	 if(P1_5==0){Delay_ms(20);while(P1_5==0);Delay_ms(20);MatrixKeyNum=10;}
	 if(P1_6==0){Delay_ms(20);while(P1_6==0);Delay_ms(20);MatrixKeyNum=6;}
	 if(P1_7==0){Delay_ms(20);while(P1_7==0);Delay_ms(20);MatrixKeyNum=2;}
	 
	 P1=0xff;
	 P1_3=0;
	 if(P1_4==0){Delay_ms(20);while(P1_4==0);Delay_ms(20);MatrixKeyNum=13;}
	 if(P1_5==0){Delay_ms(20);while(P1_5==0);Delay_ms(20);MatrixKeyNum=9;}
	 if(P1_6==0){Delay_ms(20);while(P1_6==0);Delay_ms(20);MatrixKeyNum=5;}
	 if(P1_7==0){Delay_ms(20);while(P1_7==0);Delay_ms(20);MatrixKeyNum=1;}
	 
	 
	 return MatrixKeyNum;
 }

