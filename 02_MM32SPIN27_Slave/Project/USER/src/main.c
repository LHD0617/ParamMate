/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,��ɿƼ�
* All rights reserved.
* ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
*
* �����������ݰ�Ȩ������ɿƼ����У�δ����������������ҵ��;��
* ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
*
* @file				main
* @company			�ɶ���ɿƼ����޹�˾
* @author			��ɿƼ�(QQ3184284598)
* @version			�鿴doc��version�ļ� �汾˵��
* @Software			IAR 8.3 or MDK 5.24
* @Target core		MM32SPIN2XPs
* @Taobao			https://seekfree.taobao.com/
* @date				2020-11-23
********************************************************************************************************************/

#include "headfile.h"
#include "ParamMate.h"




PM_Waveform_t* PM_Waveform[3];
PM_Param_t* PM_Param;
int8 test1 = 0;
int16 test2 = 0;
int32 test3 = 0;
uint8 test4 = 0;
uint16 test5 = 0;
uint32 test6 = 0;
float test7 = 0.0;


void Window_init(void);

int main(void)
{
	board_init(true);
	adc_init(ADC_1, ADC1_CH00_A00, ADC_12BIT);
	gpio_init(C0, GPO, 1, GPO_PUSH_PULL);
	mpu6050_init();
	Window_init();
	while(1)
	{
		gpio_toggle(C0);
		get_accdata();
		get_gyro();
		uint16 adc = adc_convert(ADC_1, ADC1_CH00_A00);
		test1 = adc;
		test2 = adc - 2048;
		test3 = adc + 2048;
		test4 = adc + 10;
		test5 = adc + 20;
		test6 = adc + 30;
		test7 += 0.0000001;
		PM_SendWaveformData(PM_Waveform[0]);
		PM_SendWaveformData(PM_Waveform[1]);
		PM_SendParamData(PM_Param);
		systick_delay_ms(20);
	}
} 


void Window_init(void)
{
	PM_ResetWindow();
	PM_Waveform[0] = PM_CreateWaveform(35, "MPU6050_Gyro", LineSeries_Type, int16_Type);
	PM_CreateWaveformChannels(PM_Waveform[0], "X_Gyro", &mpu_gyro_x);
	PM_CreateWaveformChannels(PM_Waveform[0], "Y_Gyro", &mpu_gyro_y);
	PM_CreateWaveformChannels(PM_Waveform[0], "Z_Gyro", &mpu_gyro_z);
	PM_Waveform[1] = PM_CreateWaveform(36, "MPU6050_Acc", LineSeries_Type, int16_Type);
	PM_CreateWaveformChannels(PM_Waveform[1], "X_Acc", &mpu_acc_x);
	PM_CreateWaveformChannels(PM_Waveform[1], "Y_Acc", &mpu_acc_y);
	PM_CreateWaveformChannels(PM_Waveform[1], "Z_Acc", &mpu_acc_z);
	PM_Param = PM_CreateParam(37, "Test_param");
	PM_CreateParamChannels(PM_Param, "Test1", RW_Type, int8_Type, &test1);
	PM_CreateParamChannels(PM_Param, "Test2", RW_Type, int16_Type, &test2);
	PM_CreateParamChannels(PM_Param, "Test3", RW_Type, int32_Type, &test3);
	PM_CreateParamChannels(PM_Param, "Test4", RW_Type, uint8_Type, &test4);
	PM_CreateParamChannels(PM_Param, "Test5", RW_Type, uint16_Type, &test5);
	PM_CreateParamChannels(PM_Param, "Test6", RW_Type, uint32_Type, &test6);
	PM_CreateParamChannels(PM_Param, "Test7", RW_Type, float_Type, &test7);
	PM_InitWindow();
}

