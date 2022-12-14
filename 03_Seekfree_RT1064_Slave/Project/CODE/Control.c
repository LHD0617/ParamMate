/*---------------------------------------------------------------------
                            遑霜親室亅氏

‐峠    岬／RT1064
‐園    亟／爽崎器
‐選狼圭塀／QQ??320388825 裏佚??LHD0617_
‐恷朔厚仟／2021.03.08
‐園咎峠岬／MDK 5.28.0
‐孔    嬬／陣崙庁翠
‐廣吭並?遏娠廠茂鰆珊?僥楼聞喘??隆将恬宀俯辛??音誼喘噐凪万販採喘余。
---------------------------------------------------------------------*/


#include "Control.h"

PID_struct Motor1;//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！恣態PID潤更悶
PID_struct Motor2;//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！嘔態PID潤更悶
uint8 CK_Dir;//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！概垂圭??
uint16 L_mileage;//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！秘垂岷?濔狎?
uint16 C_mileage;//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！秘垂爆?濔狎?
uint8 Basic_speed;//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！児粥堀業
uint16 Inductance_AD[4];//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！膨揃窮湖峙
int32 mileage=0;//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！戦殻
uint32 mileage_flag1;//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！芝化戦殻炎崗了1
uint32 mileage_flag2;//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！芝化戦殻炎崗了2
uint32 mileage_flag3;//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！芝化戦殻炎崗了3
uint32 mileage_flag4;//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！芝化戦殻炎崗了4
//倶字嬉叔自?湲誦儘?
uint16 Steering_Engine_Left_limit;
uint16 Steering_Engine_Right_limit;
uint16 Steering_Engine_Mid;

/************************************************************
								遑霜親室亅氏 爽崎器
								
‐痕方兆各／Steering_Engine_Control
‐孔    嬬／倶字嬉叔陣崙
‐歌    方／data  叔業峙  袈律-150~150  減峙?鰈? 屎峙?鰉?  0葎?鯒?
‐卦 指 峙／涙
‐糞    箭／Steering_Engine_Control(0);
‐廣吭並?遏仁?

************************************************************/
void Steering_Engine_Control(int16 data)
{
	
	int16 duty;
	duty = Steering_Engine_Mid-data;
	if(duty>Steering_Engine_Left_limit) duty=Steering_Engine_Left_limit;
	if(duty<Steering_Engine_Right_limit) duty=Steering_Engine_Right_limit;
	//臥心襖侘嬉蝕廣瞥
	//SW_Oscilloscope(duty);
	pwm_duty(PWM4_MODULE3_CHA_C31, duty);
}

/************************************************************
								遑霜親室亅氏 爽崎器
								
‐痕方兆各／Motor_Parameters_Init(PID_struct* Motor)
‐孔    嬬／堀業陣崙PID歌方兜兵晒
‐歌    方／涙
‐卦 指 峙／涙
‐糞    箭／Motor_Parameters_Init(&Motor);
‐廣吭並?遏仁?

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
								遑霜親室亅氏 爽崎器
								
‐痕方兆各／Motor_Parameters_Init(PID_struct* Motor)
‐孔    嬬／奐楚塀PID陣崙
‐歌    方／PID潤更悶
‐卦 指 峙／補竃媼腎曳
‐糞    箭／Motro_PID_Control(&Motor)
‐廣吭並?遏仁?

************************************************************/

short Motro_PID_Control(PID_struct* Motor)
{
  int duty;
  //媼腎曳柴麻
  duty = Motor->KP*(Motor->E-Motor->E_L)+Motor->KI*Motor->E+Motor->KD*(Motor->E+Motor->E_L_L-2*Motor->E_L);
  //厚仟陶餓
  Motor->E_L_L = Motor->E_L;
  Motor->E_L = Motor->E;
  Motor->PIDOUT+=duty;
  //?涎?
  if(Motor->PIDOUT>10000)
    Motor->PIDOUT=10000;
  else if(Motor->PIDOUT<-10000)
    Motor->PIDOUT=-10000;
  return Motor->PIDOUT;
}

/************************************************************
								遑霜親室亅氏 爽崎器
								
‐痕方兆各／Motor_Parameters_Init(PID_struct* Motor)
‐孔    嬬／奐楚塀PID陣崙
‐歌    方／PID潤更悶
‐卦 指 峙／補竃媼腎曳
‐糞    箭／Motro_PID_Control(&Motor)
‐廣吭並?遏仁?

************************************************************/
void PID_Control_Speed()
{
	//曳琵概
	Motor1.Encoder=-qtimer_quad_get(QTIMER_1, QTIMER1_TIMER0_C0)/2;
	Motor2.Encoder=qtimer_quad_get(QTIMER_1, QTIMER1_TIMER2_C2)/2;
	//姥喘概
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



