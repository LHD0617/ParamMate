/*---------------------------------------------------------------------
                            睿龙科技协会

【平    台】RT1064
【编    写】林宏达
【联系方式】QQ：320388825 微信：LHD0617_
【最后更新】2021.03.08
【编译平台】MDK 5.28.0
【功    能】控制模块
【注意事项】本程序只供学习使用，未经作者许可，不得用于其它任何用途。
---------------------------------------------------------------------*/


#include "Control.h"

PID_struct Motor1;//——————————————————————————————————————————————————————————左轮PID结构体
PID_struct Motor2;//——————————————————————————————————————————————————————————右轮PID结构体
uint8 CK_Dir;//———————————————————————————————————————————————————————————————车库方向
uint16 L_mileage;//———————————————————————————————————————————————————————————入库直线距离
uint16 C_mileage;//———————————————————————————————————————————————————————————入库曲线距离
uint8 Basic_speed;//——————————————————————————————————————————————————————————基础速度
uint16 Inductance_AD[4];//————————————————————————————————————————————————————四路电感值
int32 mileage=0;//————————————————————————————————————————————————————————————里程
uint32 mileage_flag1;//———————————————————————————————————————————————————————记步里程标志位1
uint32 mileage_flag2;//———————————————————————————————————————————————————————记步里程标志位2
uint32 mileage_flag3;//———————————————————————————————————————————————————————记步里程标志位3
uint32 mileage_flag4;//———————————————————————————————————————————————————————记步里程标志位4
//舵机打角极限与中值
uint16 Steering_Engine_Left_limit;
uint16 Steering_Engine_Right_limit;
uint16 Steering_Engine_Mid;

/************************************************************
								睿龙科技协会 林宏达
								
【函数名称】Steering_Engine_Control
【功    能】舵机打角控制
【参    数】data  角度值  范围-150~150  负值向左 正值向右  0为向前
【返 回 值】无
【实    例】Steering_Engine_Control(0);
【注意事项】无

************************************************************/
void Steering_Engine_Control(int16 data)
{
	
	int16 duty;
	duty = Steering_Engine_Mid-data;
	if(duty>Steering_Engine_Left_limit) duty=Steering_Engine_Left_limit;
	if(duty<Steering_Engine_Right_limit) duty=Steering_Engine_Right_limit;
	//查看波形打开注释
	//SW_Oscilloscope(duty);
	pwm_duty(PWM4_MODULE3_CHA_C31, duty);
}

/************************************************************
								睿龙科技协会 林宏达
								
【函数名称】Motor_Parameters_Init(PID_struct* Motor)
【功    能】速度控制PID参数初始化
【参    数】无
【返 回 值】无
【实    例】Motor_Parameters_Init(&Motor);
【注意事项】无

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
								睿龙科技协会 林宏达
								
【函数名称】Motor_Parameters_Init(PID_struct* Motor)
【功    能】增量式PID控制
【参    数】PID结构体
【返 回 值】输出占空比
【实    例】Motro_PID_Control(&Motor)
【注意事项】无

************************************************************/

short Motro_PID_Control(PID_struct* Motor)
{
  int duty;
  //占空比计算
  duty = Motor->KP*(Motor->E-Motor->E_L)+Motor->KI*Motor->E+Motor->KD*(Motor->E+Motor->E_L_L-2*Motor->E_L);
  //更新偏差
  Motor->E_L_L = Motor->E_L;
  Motor->E_L = Motor->E;
  Motor->PIDOUT+=duty;
  //限幅
  if(Motor->PIDOUT>10000)
    Motor->PIDOUT=10000;
  else if(Motor->PIDOUT<-10000)
    Motor->PIDOUT=-10000;
  return Motor->PIDOUT;
}

/************************************************************
								睿龙科技协会 林宏达
								
【函数名称】Motor_Parameters_Init(PID_struct* Motor)
【功    能】增量式PID控制
【参    数】PID结构体
【返 回 值】输出占空比
【实    例】Motro_PID_Control(&Motor)
【注意事项】无

************************************************************/
void PID_Control_Speed()
{
	//比赛车
	Motor1.Encoder=-qtimer_quad_get(QTIMER_1, QTIMER1_TIMER0_C0)/2;
	Motor2.Encoder=qtimer_quad_get(QTIMER_1, QTIMER1_TIMER2_C2)/2;
	//备用车
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



