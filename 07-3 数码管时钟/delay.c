#include <INTRINS.H>
 
 /************注意这里是100us**********/
void delay (unsigned int x100us)		//@11.0592MHz
{
	unsigned char i, j;
	while(x100us--)
	{
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
