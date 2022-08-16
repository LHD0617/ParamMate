/*---------------------------------------------------------------------
                            睿龙科技协会

【平    台】RT1064
【编    写】林宏达
【联系方式】QQ：320388825 微信：LHD0617_
【最后更新】2021.02.24
【编译平台】MDK 5.28.0
【功    能】动力模块
【注意事项】本程序只供学习使用，未经作者许可，不得用于其它任何用途。
---------------------------------------------------------------------*/
#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "common.h"

//PWM引脚定义
#define Motor1_A PWM1_MODULE3_CHA_D0
#define Motor1_B PWM1_MODULE3_CHB_D1

#define Motor2_A PWM2_MODULE3_CHA_D2
#define Motor2_B PWM2_MODULE3_CHB_D3

void Motor_Init(void);
void Motor_Ctrl(uint8 num, int16 duty);



#endif

