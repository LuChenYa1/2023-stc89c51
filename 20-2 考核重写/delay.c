#include <INTRINS.H>
void delay(unsigned int xms)
{
	while(xms--)
	{
		unsigned char i, j;

		_nop_();
		_nop_();
		_nop_();
		i = 11;
		j = 190;
		do
		{
			while (--j);
		} while (--i);
	}
}
void delay100us(unsigned char x100us)		//@11.0592MHz
{
	while(x100us--)
	{
		unsigned char i, j;

		_nop_();
		_nop_();
		i = 2;
		j = 15;
		do
		{
			while (--j);
		} while (--i);
	}
}
