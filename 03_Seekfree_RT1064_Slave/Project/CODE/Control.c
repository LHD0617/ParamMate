/*---------------------------------------------------------------------
                            ����Ƽ�Э��

��ƽ    ̨��RT1064
����    д���ֺ��
����ϵ��ʽ��QQ��320388825 ΢�ţ�LHD0617_
�������¡�2021.03.08
������ƽ̨��MDK 5.28.0
����    �ܡ�����ģ��
��ע�����������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;��
---------------------------------------------------------------------*/


#include "Control.h"

PID_struct Motor1;//������������������������������������������������������������������������������������������������������������������������PID�ṹ��
PID_struct Motor2;//������������������������������������������������������������������������������������������������������������������������PID�ṹ��
uint8 CK_Dir;//���������������������������������������������������������������������������������������������������������������������������������ⷽ��
uint16 L_mileage;//�������������������������������������������������������������������������������������������������������������������������ֱ�߾���
uint16 C_mileage;//����������������������������������������������������������������������������������������������������������������������������߾���
uint8 Basic_speed;//�������������������������������������������������������������������������������������������������������������������������ٶ�
uint16 Inductance_AD[4];//����������������������������������������������������������������������������������������������������������·���ֵ
int32 mileage=0;//���������������������������������������������������������������������������������������������������������������������������
uint32 mileage_flag1;//���������������������������������������������������������������������������������������������������������������ǲ���̱�־λ1
uint32 mileage_flag2;//���������������������������������������������������������������������������������������������������������������ǲ���̱�־λ2
uint32 mileage_flag3;//���������������������������������������������������������������������������������������������������������������ǲ���̱�־λ3
uint32 mileage_flag4;//���������������������������������������������������������������������������������������������������������������ǲ���̱�־λ4
//�����Ǽ�������ֵ
uint16 Steering_Engine_Left_limit;
uint16 Steering_Engine_Right_limit;
uint16 Steering_Engine_Mid;

/************************************************************
								����Ƽ�Э�� �ֺ��
								
���������ơ�Steering_Engine_Control
����    �ܡ������ǿ���
����    ����data  �Ƕ�ֵ  ��Χ-150~150  ��ֵ���� ��ֵ����  0Ϊ��ǰ
���� �� ֵ����
��ʵ    ����Steering_Engine_Control(0);
��ע�������

************************************************************/
void Steering_Engine_Control(int16 data)
{
	
	int16 duty;
	duty = Steering_Engine_Mid-data;
	if(duty>Steering_Engine_Left_limit) duty=Steering_Engine_Left_limit;
	if(duty<Steering_Engine_Right_limit) duty=Steering_Engine_Right_limit;
	//�鿴���δ�ע��
	//SW_Oscilloscope(duty);
	pwm_duty(PWM4_MODULE3_CHA_C31, duty);
}

/************************************************************
								����Ƽ�Э�� �ֺ��
								
���������ơ�Motor_Parameters_Init(PID_struct* Motor)
����    �ܡ��ٶȿ���PID������ʼ��
����    ������
���� �� ֵ����
��ʵ    ����Motor_Parameters_Init(&Motor);
��ע�������

************************************************************/

void Motor_Parameters_Init(PID_struct *Motor)
{
	Motor->Current_Speed 		= 0;
	Motor->Target_Speed 		= 0;
	Motor->Encoder      		= 0;
  Motor->E       					= 0;
  Motor->E_L     					= 0;
  Motor->E_L_L   					= 0;
  Motor->KP      					= 350;
  Motor->KI      					= 60;
  Motor->KD      					= 60;
  Motor->PIDOUT  					= 0;
}


/************************************************************
								����Ƽ�Э�� �ֺ��
								
���������ơ�Motor_Parameters_Init(PID_struct* Motor)
����    �ܡ�����ʽPID����
����    ����PID�ṹ��
���� �� ֵ�����ռ�ձ�
��ʵ    ����Motro_PID_Control(&Motor)
��ע�������

************************************************************/

short Motro_PID_Control(PID_struct* Motor)
{
  int duty;
  //ռ�ձȼ���
  duty = Motor->KP*(Motor->E-Motor->E_L)+Motor->KI*Motor->E+Motor->KD*(Motor->E+Motor->E_L_L-2*Motor->E_L);
  //����ƫ��
  Motor->E_L_L = Motor->E_L;
  Motor->E_L = Motor->E;
  Motor->PIDOUT+=duty;
  //�޷�
  if(Motor->PIDOUT>10000)
    Motor->PIDOUT=10000;
  else if(Motor->PIDOUT<-10000)
    Motor->PIDOUT=-10000;
  return Motor->PIDOUT;
}

/************************************************************
								����Ƽ�Э�� �ֺ��
								
���������ơ�Motor_Parameters_Init(PID_struct* Motor)
����    �ܡ�����ʽPID����
����    ����PID�ṹ��
���� �� ֵ�����ռ�ձ�
��ʵ    ����Motro_PID_Control(&Motor)
��ע�������

************************************************************/
void PID_Control_Speed()
{
	//������
	Motor1.Encoder=-qtimer_quad_get(QTIMER_1, QTIMER1_TIMER0_C0)/2;
	Motor2.Encoder=qtimer_quad_get(QTIMER_1, QTIMER1_TIMER2_C2)/2;
	//���ó�
//	Motor1.Encoder=qtimer_quad_get(QTIMER_1, QTIMER1_TIMER0_C0);
//	Motor2.Encoder=-qtimer_quad_get(QTIMER_1, QTIMER1_TIMER2_C2);
	mileage+=Motor1.Encoder;
	mileage+=Motor2.Encoder;
	qtimer_quad_clear(QTIMER_1, QTIMER1_TIMER0_C0);
	qtimer_quad_clear(QTIMER_1, QTIMER1_TIMER2_C2);
	Motor1.Current_Speed=Motor1.Encoder;
	Motor2.Current_Speed=Motor2.Encoder;
	Motor1.E = Motor1.Target_Speed-Motor1.Current_Speed;
	Motor2.E = Motor2.Target_Speed-Motor2.Current_Speed;
	Motor_Ctrl(1, Motro_PID_Control(&Motor1)*2);
	Motor_Ctrl(2, Motro_PID_Control(&Motor2)*2);
}



