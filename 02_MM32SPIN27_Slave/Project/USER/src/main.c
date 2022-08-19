/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,��ɿƼ�
* All rights reserved.
* ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
*
* �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
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



PM_Param_t* PM_Param;
PM_Waveform_t* PM_Waveform[3];
PM_Image_t* PM_Image[2];
uint16 adc;
int8 test1 = 1;
int16 test2 = 0;
int32 test3 = 0;
uint8 test4 = 0;
uint16 test5 = 0;
uint32 test6 = 0;
float test7 = 0.0;
uint8 testparam[25];
uint8 Image[50][90] = {0};


void Window_init(void);

void UpdateImage(uint16 num)
{
	uint8 i, j, k;
	for(i=5;i>0;i--)
	{
		for(j=0;j<16;j++)
		{
			for(k=0;k<8;k++)
			{
				if(tft_ascii[16 + num % 10][j] & (0x01 << k))
					Image[j][(i-1)*8+k] = 255;
				else
					Image[j][(i-1)*8+k] = 0;
			}
		}
		num /= 10;
	}
}

int main(void)
{
	uint16 count = 0;
	uint8 i,j;
	board_init(true);
	uart_rx_irq(UART_1,1);
	adc_init(ADC_1, ADC1_CH00_A00, ADC_12BIT);
	gpio_init(C0, GPO, 1, GPO_PUSH_PULL);
	mpu6050_init();
	Window_init();
	while(1)
	{
		gpio_toggle(C0);
		
		/* �������� */
		adc = adc_convert(ADC_1, ADC1_CH00_A00);
		get_accdata();
		get_gyro();
		UpdateImage(count++);
		
		
		/* �������� */
		PM_SendParamData(PM_Param);
		PM_SendWaveformData(PM_Waveform[0]);
		PM_SendWaveformData(PM_Waveform[1]);
		PM_SendWaveformData(PM_Waveform[2]);
//		PM_SendImageData(PM_Image[0]);
		PM_SendImageData(PM_Image[1]);
		
		/* ��ʱ */
		systick_delay_ms(10);
	}
} 


void Window_init(void)
{
	/* ��λMainWindow�ؼ� */
	PM_ResetWindow();
	
	/* Test_param �ؼ� */
	PM_Param = PM_CreateParam(0x00, "Test_param");
	PM_CreateParamChannels(PM_Param, "Test_Param1",R_Type, int8_Type, &test1);
	PM_CreateParamChannels(PM_Param, "Test_Param2",W_Type, int16_Type, &test2);
	PM_CreateParamChannels(PM_Param, "Test_Param3",RW_Type, int32_Type, &test3);
	PM_CreateParamChannels(PM_Param, "Test_Param4",RW_Type, uint8_Type, &test4);
	PM_CreateParamChannels(PM_Param, "Test_Param5",RW_Type, uint16_Type, &test5);
	PM_CreateParamChannels(PM_Param, "Test_Param6",RW_Type, uint32_Type, &test6);
	PM_CreateParamChannels(PM_Param, "Test_Param7",RW_Type, float_Type, &test7);
	
	/* ADC0 �ؼ� */
	PM_Waveform[0] = PM_CreateWaveform(0x01, "ADC0", LineSeries_Type, uint16_Type);
	PM_CreateWaveformChannels(PM_Waveform[0], "Test", &adc);
	
	/* MPU6050_Gyro �ؼ� */
	PM_Waveform[1] = PM_CreateWaveform(0x02, "MPU6050_Gyro", SplineSeries_Type, int16_Type);
	PM_CreateWaveformChannels(PM_Waveform[1], "GyroX", &mpu_gyro_x);
	PM_CreateWaveformChannels(PM_Waveform[1], "Gyroy", &mpu_gyro_y);
	PM_CreateWaveformChannels(PM_Waveform[1], "GyroZ", &mpu_gyro_z);
	
	/* MPU6050_Acc �ؼ� */
	PM_Waveform[2] = PM_CreateWaveform(0x03, "MPU6050_Acc", BarSeries_Type, int16_Type);
	PM_CreateWaveformChannels(PM_Waveform[2], "AccX", &mpu_acc_x);
	PM_CreateWaveformChannels(PM_Waveform[2], "AccY", &mpu_acc_y);
	PM_CreateWaveformChannels(PM_Waveform[2], "AccZ", &mpu_acc_z);
	
	/* Test_RGB565 �ؼ� */
//	PM_Image[0] = PM_CreateImage(0x04, "Test_RGB565", RGB565_Type, 50, 90, Image);
	
	/* Test_Grayscale �ؼ� */
	PM_Image[1] = PM_CreateImage(0x05, "Test_Grayscale", Binarization_Type, 50, 90, Image);
	
	/* ��ʼ��MainWindow */
	PM_InitWindow();
}

