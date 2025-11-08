#include <INTRINS.H>
void Delay_ms(unsigned int xms)
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