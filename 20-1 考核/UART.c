#include <REGX51.H>

void UART_Init()
{
	SCON=0x50;
	PCON |= 0x80;
	TMOD &= 0x0F;	
	TMOD |= 0x20;	
	TL1 = 0xE8;		 
	TH1 = 0xFF;		
	ET1 = 0;		
	TR1 = 1;		
}
 
void UART_SendByte(unsigned char Byte)
{
	SBUF=Byte;
	while(TI==0);
	TI=0;
}