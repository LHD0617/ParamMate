#ifndef _CONTROL_H_
#define _CONTROL_H_

#include "common.h"
#include "zf_pwm.h"
#include "zf_adc.h"
#include "zf_usb_cdc.h"
#include "zf_uart.h"
#include "zf_qtimer.h"
#include "SEEKFREE_OLED.h"
#include "Motor.h"

//倶字嬉叔自�湲誦儘�
extern uint16 Steering_Engine_Left_limit;
extern uint16 Steering_Engine_Right_limit;
extern uint16 Steering_Engine_Mid;
extern uint16 L_mileage;
extern uint16 C_mileage;
extern int32 mileage;
extern uint32 mileage_flag1;
extern uint32 mileage_flag2;
extern uint32 mileage_flag3;
extern uint32 mileage_flag4;
//PID潤更悶
typedef struct{
	int16 Current_Speed;//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！輝念堀業
	int16 Target_Speed;//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！朕炎堀業
	int16 Encoder;//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！園鷹匂峙
  int16 E;//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！云肝議陶餓
  int16 E_L;//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！貧匯肝議陶餓
  int16 E_L_L;//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！貧貧肝議陶餓
  int16 KP;//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！曳箭狼方
  int16 KI;//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！持蛍狼方
  int16 KD;//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！裏蛍狼方
  int16 PIDOUT;//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！PID補竃
}PID_struct;


extern PID_struct Motor1;//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！恣態PID潤更悶
extern PID_struct Motor2;//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！嘔態PID潤更悶
extern uint8 Basic_speed;//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！児粥堀業
extern uint16 Inductance_AD[4];//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！膨揃窮湖峙
extern double DJ_K,DJ_D;//！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！倶字PID歌方


void PID_Control_Speed();
void Motor_Parameters_Init(PID_struct *Motor);
short Motro_PID_Control(PID_struct* Motor);
void Steering_Engine_Control(int16 data);
void SW_Oscilloscope(int16 duty);
void Record_mileage_entry(void *parameter);
void display_mileage(void);
void Fuzzy(float E,float EC);

#endif

