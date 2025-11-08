#include <REGX52.H>
#include "Delay.h"
#include "MatrixKey.h"
#include "Nixie.h"

unsigned char Number;
unsigned char flag;
unsigned char test_1=2;
unsigned char test_2=3;
unsigned char location=1;
void main()
{
	
	unsigned char i = 6;
	
	while(1)
	{
		if(P3_1==0)			
		{
			Delay(20);		
			while(P3_1==0);	
			Delay(20);		
			
			P2_0=~P2_0;		
		}
		
		
		
		flag=MatrixKey();
		if(flag)
		{	
			if(location==1)
			{
				test_1=flag;
				location++;
			}
			else if(location==2)
			{
				test_2=flag;
				location=1;
			}
			
		}
		Nixie(1,test_1);
		Nixie(2,test_2);
		Nixie(3,10);
		Nixie(4,2);
		Nixie(5,9);
		Nixie(6,10);
		Nixie(7,5);
		Nixie(8,i);
		if(P3_0==0)
		{   
			  Delay(20);
				while(P3_0==0);
				Delay(20);
		    i--;
			if(i==-1)
			{
				i=9;
			}
		
		}
		if(P3_2==0)
		{
			  Delay(20);
		 	  while(P3_2==0);
				Delay(20);
				i++;
			if(i==10)
			{
				i=0;
			}
		}
	}
}
	

