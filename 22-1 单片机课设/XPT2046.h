#ifndef _XPT2046__H__
#define _XPT2046__H__

//不同的测量类型有不同的通道A2、A1、A0，对应不同的命令字Command
#define XPT2046_XP_8 0x9C             //0x8C 电位器
#define XPT2046_YP_8 0xDC             //热敏电阻（小小的水滴状）
#define XPT2046_VBAT_8 0xAC           //光敏电阻（有波浪线）
#define XPT2046_AUX_8 0xEC            //MODE=1,8位分辨率

#define XPT2046_XP_12 0x94            //0x84
#define XPT2046_YP_12 0xD4
#define XPT2046_VBAT_12 0xA4          //MODE=0，12位分辨率
#define XPT2046_AUX_12 0xE4

unsigned int XPT2046_ReadAD (unsigned char Command);

#endif