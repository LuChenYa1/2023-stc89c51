#include <INTRINS.H>
 
void delay (unsigned int xms)		//@11.0592MHz
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


/***100us函数模板，适用nixie（）函数***/
//void delay100us()		//@11.0592MHz
//{
//	unsigned char i, j;

//	_nop_();
//	_nop_();
//	i = 2;
//	j = 15;
//	do
//	{
//		while (--j);
//	} while (--i);
//}
