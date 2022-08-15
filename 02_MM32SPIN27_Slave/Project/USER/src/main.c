/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,逐飞科技
* All rights reserved.
* 技术讨论QQ群：一群：179029047(已满)  二群：244861897
*
* 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
* 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
*
* @file				main
* @company			成都逐飞科技有限公司
* @author			逐飞科技(QQ3184284598)
* @version			查看doc内version文件 版本说明
* @Software			IAR 8.3 or MDK 5.24
* @Target core		MM32SPIN2XPs
* @Taobao			https://seekfree.taobao.com/
* @date				2020-11-23
********************************************************************************************************************/

#include "headfile.h"
#include "ParamMate.h"




PM_Waveform_t* PM_Waveform[1];
PM_Param_t* PM_Param;
//PM_Image_t* PM_Image;
int16 ad;
int8 test1 = 1;
int16 test2 = 0;
int32 test3 = 0;
uint8 test4 = 0;
uint16 test5 = 0;
uint32 test6 = 0;
float test7 = 0.0;
uint8 image[60][90] = {0};


void Window_init(void);

int main(void)
{
	uint8 i,j;
	board_init(true);
	uart_rx_irq(UART_1,1);
	adc_init(ADC_1, ADC1_CH00_A00, ADC_12BIT);
	gpio_init(C0, GPO, 1, GPO_PUSH_PULL);
	mpu6050_init();
	Window_init();
	while(1)
	{
		for(i=0;i<60;i++)
		{
			for(j=0;j<90;j++)
			{
				gpio_toggle(C0);
				ad = adc_convert(ADC_1, ADC1_CH00_A00) * test1;
//				image[i][j] = adc & 0x01;
//				test1 = adc;
//				test2 = adc - 2048;
//				test3 = adc + 2048;
//				test4 = adc + 10;
//				test5 = adc + 20;
//				test6 = adc + 30;
//				test7 += 0.0000001;
				PM_SendWaveformData(PM_Waveform[0]);
////				PM_SendWaveformData(PM_Waveform[1]);
				PM_SendParamData(PM_Param);
				//PM_SendImageData(PM_Image);
				systick_delay_ms(20);
			}
		}
	}
} 


void Window_init(void)
{
	PM_ResetWindow();
	PM_Waveform[0] = PM_CreateWaveform(35, "ADC", LineSeries_Type, int16_Type);
	PM_CreateWaveformChannels(PM_Waveform[0], "ad0", &ad);
////	PM_CreateWaveformChannels(PM_Waveform[0], "Y_Gyro", &mpu_gyro_y);
////	PM_CreateWaveformChannels(PM_Waveform[0], "Z_Gyro", &mpu_gyro_z);
////	PM_Waveform[1] = PM_CreateWaveform(36, "MPU6050_Acc", LineSeries_Type, int16_Type);
////	PM_CreateWaveformChannels(PM_Waveform[1], "X_Acc", &mpu_acc_x);
////	PM_CreateWaveformChannels(PM_Waveform[1], "Y_Acc", &mpu_acc_y);
////	PM_CreateWaveformChannels(PM_Waveform[1], "Z_Acc", &mpu_acc_z);
	PM_Param = PM_CreateParam(37, "Test_param");
	PM_CreateParamChannels(PM_Param, "Test1", RW_Type, int8_Type, &test1);
	PM_CreateParamChannels(PM_Param, "Test2", R_Type, int16_Type, &test2);
	PM_CreateParamChannels(PM_Param, "Test3", RW_Type, int32_Type, &test3);
	PM_CreateParamChannels(PM_Param, "Test4", RW_Type, uint8_Type, &test4);
	PM_CreateParamChannels(PM_Param, "Test5", RW_Type, uint16_Type, &test5);
	PM_CreateParamChannels(PM_Param, "Test6", RW_Type, uint32_Type, &test6);
	PM_CreateParamChannels(PM_Param, "Test7", RW_Type, float_Type, &test7);
////	PM_Image = PM_CreateImage(38, "TestImage1", Binarization_Type, 60, 90, image);
	PM_InitWindow();
}


