#include <REGX51.H>
#include "UART.h"
#include "OLED.h"
#include "delay.h"
#include "Servo.h"
#include "AT24C02.h"
#include "XPT2046.h"
#include "MatrixKey.h"
#include "Timer0_Init.h"

#define RainSensor 		  			  	P0_4//雨滴传感引脚
#define Pin_Mode   		  			  	P2_2//语音-工作模式引脚
#define Pin_Action 		  				P2_3//语音-舵机动作引脚
#define Pin_Speech_MatrixAndBlueTooth   P2_4//语音-键盘-蓝牙控制模式转换引脚

#define Withdraw 1 
#define Manual 1
#define Extend 0
#define Auto 0
#define Rain 0
#define Dry  1
#define Speech_Contral 1
#define MatrixAndBlueTooth_Contral 0
#define Enable 1
#define Disable 0

uint8_t LightPower = 0, LightPower_Limit = 0, LightPower_Limit_Temp = 0,Flag_SetLightPower, //光强、光强阈值、中间值、标志位（是否开始设置光强阈值）
MatrixKeyNum = 0, Num_Count = 0, Pressed_Count = 0,  //按键键码、输入数字位数、按键按下次数
Mode = 0, Action = 0, Flag_Speech_MatrixAndBlueTooth,//标志位：手动/自动模式、收回/伸出模式、键盘/语音/蓝牙控制模式
BlueTooth_Value = 0, BlueTooth_Mode = 0;             //蓝牙接收值、蓝牙模式

void Speech_Recognition(void);
void BlueTooth_Contral(void);
void OLED_Show(void);

void main ()        
{
	UART_Init();
	Timer0_Init();
	OLED_Init();
    OLED_Clear();
	
	OLED_ShowString(0, 0, "Lg:", 16);
	OLED_ShowString(63, 0, "Bound:", 16);
	OLED_ShowString(63, 6, "Count:", 16);
	
	while(1)
	{		
		/*******************************************按键控制模式设置****************************************************************/
		
		MatrixKeyNum = MatrixKey();                           //全局扫描矩阵键盘
		OLED_ShowNum(110, 6, Pressed_Count, 2, 16);           //显示总按下次数		
		if(MatrixKeyNum != 0)                            	  
		{ 
			Pressed_Count++;                                  //按键按下次数加一
			
			if(MatrixKeyNum <= 10)                	  	      /***按键1~10输入光强阈值***/
			{
				if(Flag_SetLightPower == Enable)
				{
					if(Num_Count < 2)                         //最大位数为2
					{
						LightPower_Limit_Temp *= 10;          //新输入的数字作个位
						LightPower_Limit_Temp += MatrixKeyNum % 10;//输入10即为0
						Num_Count++;                          //输入一个数，总位数加一
					}	
				}		
			}
			else if(MatrixKeyNum == 11)                       /***按键11开始（或重新）输入光强阈值***/
			{
				Flag_SetLightPower = Enable; 
				Num_Count = 0;
				LightPower_Limit = 0;
			}
			else if(MatrixKeyNum == 12)                       /***按键12确认最终光强阈值***/
			{
				LightPower_Limit = LightPower_Limit_Temp;
				Flag_SetLightPower = Disable;
				Num_Count = 2;
				AT24C02_WriteByte(0, LightPower_Limit);       //存储光强阈值，位置0
			}
			/************以下是功能按键***********/
			else if(MatrixKeyNum == 13)                       /***按键13切换手动/自动工作模式***/
			{
				if(Pin_Speech_MatrixAndBlueTooth == MatrixAndBlueTooth_Contral)Mode = !Mode;//键盘蓝牙控制模式该键有效
			}
			else if(MatrixKeyNum == 14)                       /***按键14收回/伸出晾衣架***/
			{
				if(Mode == Auto)Mode = Manual;                //自动工作模式下，按下按键，转换手动工作模式
				Action = !Action;						      //手动工作模式可收回/伸出，非雨天
			}
//			else if(MatrixKeyNum == 15)                       /***按键15转换键盘/语音蓝牙控制，加入语音转换后该键失效***/
//			{
//				Flag_Speech_MatrixAndBlueTooth = !Flag_Speech_MatrixAndBlueTooth;
//			}
		}	
		
		/***********************************************语音/键盘/蓝牙控制模式转换*************************************************************/
		
		//使用语音控制模式时，其他两种无效，但键盘和蓝牙控制模式可以共存，因为语音电平不变，但蓝牙和键盘进入一次即清零
		if(Pin_Speech_MatrixAndBlueTooth == Speech_Contral)//识别语音转换对应控制模式
			Flag_Speech_MatrixAndBlueTooth = Speech_Contral;  
		else if(Pin_Speech_MatrixAndBlueTooth == MatrixAndBlueTooth_Contral)
			Flag_Speech_MatrixAndBlueTooth = MatrixAndBlueTooth_Contral;
		
		//根据标志位启动对应控制程序
		if(Flag_Speech_MatrixAndBlueTooth == Speech_Contral)Speech_Recognition();
		else if(Flag_Speech_MatrixAndBlueTooth == MatrixAndBlueTooth_Contral)BlueTooth_Contral();
		
		/**********************************************自动/手动工作模式功能设置*********************************************************/
		
		if(Mode == Auto)                                      /***自动工作模式设置***/
		{
			if(LightPower > LightPower_Limit && RainSensor == Dry)Action = Extend;//白天/晴天自动伸出晾晒（非雨天），防止太阳雨 
			else Action = Withdraw;          	              //黑夜/阴天/雨天自动收回防潮/雨
		}
		if(Mode == Manual){}                                  /***手动工作模式设置***/
		
		/******************************独立于模式之外的规则：有雨时强制收回晾衣架，无法进行其他动作***********************************/
		
		if(RainSensor == Rain)Action = Withdraw;     		  
	
		/**********************************************当一切尘埃落地（显示指令及数据）*********************************************/
			
		OLED_Show();	
		
		/***************************************************收尾（最终按指令执行收回/伸出动作）*************************************************/
		
		if(Action == Withdraw)contral_1();                      //收回衣服
		else if(Action == Extend)contral_4();                   //晾晒衣服
	}                    
}


/*********************************************************************************** 
函数名称:Speech_Recognition
函数功能:语音控制（电平检测），缺陷：语音控制模式下，按键模式失效
***********************************************************************************/
void Speech_Recognition(void)
{
	if(Pin_Mode == Manual)Mode = Manual;		//语音控制工作模式
	else if(Pin_Mode == Auto)Mode = Auto;
	if(Pin_Action == Withdraw)Action = Withdraw;//语音控制收伸
	else if(Pin_Action == Extend)Action = Extend;
}


/*********************************************************************************** 
函数名称:BlueTooth_Contral
函数功能:蓝牙控制模式(类似键盘)
***********************************************************************************/
void BlueTooth_Contral(void)
{
	if(BlueTooth_Mode == 1)					   //收回伸出晾衣架
	{
		if(Mode == Auto)Mode = Manual;         //自动工作模式下，按下按键，转换手动模式
		Action = !Action;
		BlueTooth_Mode = 0;
	}
	else if(BlueTooth_Mode == 2)               //转换手动/自动工作模式
	{
		if(Pin_Speech_MatrixAndBlueTooth == MatrixAndBlueTooth_Contral)Mode = !Mode;
		BlueTooth_Mode = 0;
	}
	else if(BlueTooth_Mode == 3)               //开始（或重新）输入光强阈值
	{
		Flag_SetLightPower = Enable; 
		Num_Count = 0;
		LightPower_Limit = 0;
		BlueTooth_Mode = 0;
	}
	else if(BlueTooth_Mode == 4)               //确认最终光强阈值
	{
		LightPower_Limit = LightPower_Limit_Temp;
		Flag_SetLightPower = Enable;
		Num_Count = 2;
		AT24C02_WriteByte(0, LightPower_Limit);//存储光强阈值，位置1
		BlueTooth_Mode = 0;
	}
}


//蓝牙串口中断函数
void UART_Routine()   interrupt 4  
{
	if(RI == 1)                      
	{
		RI = 0;                     //手动复位 
		BlueTooth_Value = SBUF;	
		switch(BlueTooth_Value)
		{
 			case 0x01:BlueTooth_Mode = 1;break;
			case 0x02:BlueTooth_Mode = 2;break;
			case 0x03:BlueTooth_Mode = 3;break; 
			case 0x04:BlueTooth_Mode = 4;break; 
		} 
		UART_SendByte(BlueTooth_Value);
	}
}


/*********************************************************************************** 
函数名称:OLED_Show
函数功能:OLED显示各项命令及检测数据
***********************************************************************************/
void OLED_Show(void)
{
	LightPower_Limit = AT24C02_ReadByte(0);                		   	   //将存储的光强阈值取出来
	OLED_ShowNum(110,0,LightPower_Limit,2, 16);                	   	   //显示光强阈值
	LightPower = XPT2046_ReadAD(XPT2046_VBAT_8) * 4;               	   //读取光强（0 ~ 100）
	OLED_ShowNum(23, 0,LightPower, 2, 16);                         	   //显示光强
//	LightPower = XPT2046_ReadAD(XPT2046_YP_8) * 4;               	   //读取温度（0 ~ 100）
//	OLED_ShowNum(47, 2,LightPower, 2, 16);                         	   //显示温度
	
	if(LightPower < LightPower_Limit)OLED_ShowString(0, 2,"Night", 16);//显示白天
	else OLED_ShowString(0, 2, "Day  ", 16); 			         	   //显示黑夜
	
	if(RainSensor == Rain)OLED_ShowString(94, 2, "Rain", 16);     	   //显示有雨
	else if(RainSensor == Dry)OLED_ShowString(94, 2, "Dry ", 16);	   //显示无雨
	
	if(Mode == Manual)OLED_ShowString(0, 4, "Manual", 16);             //显示手动模式
	else if(Mode == Auto)OLED_ShowString(0, 4, "Auto  ", 16);          //显示自动模式

	if(Action == Withdraw)OLED_ShowString(63, 4, "Withdraw", 16);	   //显示收回晾衣架
	else if(Action == Extend)OLED_ShowString(63, 4, "Extend  ", 16);   //显示伸出晾衣架
	
	if(Flag_Speech_MatrixAndBlueTooth == Speech_Contral)OLED_ShowString(0, 6, "Speak ", 16);//显示语音控制模式
	else if(Flag_Speech_MatrixAndBlueTooth == MatrixAndBlueTooth_Contral)OLED_ShowString(0, 6, "Matrix", 16);//显示非语音控制
}
