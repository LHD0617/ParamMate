/*---------------------------------------------------------------------
                            ����Ƽ�Э��

��ƽ    ̨��RT1064
����    д���ֺ��
����ϵ��ʽ��QQ��320388825 ΢�ţ�LHD0617_
�������¡�2021.02.24
������ƽ̨��MDK 5.28.0
����    �ܡ�����ģ��
��ע�����������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
---------------------------------------------------------------------*/
#ifndef _MOTOR_H_
#define _MOTOR_H_

#include "common.h"

//PWM���Ŷ���
#define Motor1_A PWM1_MODULE3_CHA_D0
#define Motor1_B PWM1_MODULE3_CHB_D1

#define Motor2_A PWM2_MODULE3_CHA_D2
#define Motor2_B PWM2_MODULE3_CHB_D3

void Motor_Init(void);
void Motor_Ctrl(uint8 num, int16 duty);



#endif

