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



uint16 ad[3][8];
PM_Image_t* PM_Image11;
PM_Waveform_t* PM_Waveform[3];
uint8 image[60][90];



void Window_init(void);

int main(void)
{
	uint8 i,j;
	board_init(true);
	adc_init(ADC_1, ADC1_CH00_A00, ADC_12BIT);
	gpio_init(C0, GPO, 1, GPO_PUSH_PULL);
	for(i=0;i<60;i++)
	{
		for(j=0;j<90;j++)
		{
			image[i][j] = 0xff;
		}
	}
	Window_init();
	while(1)
	{
		gpio_toggle(C0);
		ad[0][0] = adc_convert(ADC_1, ADC1_CH00_A00);
		ad[0][1] = rand();
		ad[0][2] = rand();
		ad[0][3] = rand();
		ad[0][4] = rand();
		ad[0][5] = rand();
		ad[0][6] = rand();
		ad[0][7] = rand();
		PM_SendWaveformData(PM_Waveform[0]);
		PM_SendImageData(PM_Image11);
		systick_delay_ms(20);
	}
} 


void Window_init(void)
{
	PM_ResetWindow();
	PM_Waveform[0] = PM_CreateWaveform(0x45, "TestWaveform1", LineSeries_Type, uint16_Type);
	PM_CreateWaveformChannels(PM_Waveform[0], "Channels1", &ad[0][0]);
	PM_CreateWaveformChannels(PM_Waveform[0], "Channels2", &ad[0][1]);
	PM_CreateWaveformChannels(PM_Waveform[0], "Channels3", &ad[0][2]);
	PM_CreateWaveformChannels(PM_Waveform[0], "Channels4", &ad[0][3]);
	PM_CreateWaveformChannels(PM_Waveform[0], "Channels5", &ad[0][4]);
	PM_CreateWaveformChannels(PM_Waveform[0], "Channels6", &ad[0][5]);
	PM_CreateWaveformChannels(PM_Waveform[0], "Channels7", &ad[0][6]);
	PM_CreateWaveformChannels(PM_Waveform[0], "Channels8", &ad[0][7]);
	PM_Waveform[1] = PM_CreateWaveform(0x46, "TestWaveform2", SplineSeries_Type, uint16_Type);
	PM_CreateWaveformChannels(PM_Waveform[1], "Channels1", &ad[1][0]);
	PM_CreateWaveformChannels(PM_Waveform[1], "Channels2", &ad[1][1]);
	PM_CreateWaveformChannels(PM_Waveform[1], "Channels3", &ad[1][2]);
	PM_CreateWaveformChannels(PM_Waveform[1], "Channels4", &ad[1][3]);
	PM_CreateWaveformChannels(PM_Waveform[1], "Channels5", &ad[1][4]);
	PM_CreateWaveformChannels(PM_Waveform[1], "Channels6", &ad[1][5]);
	PM_CreateWaveformChannels(PM_Waveform[1], "Channels7", &ad[1][6]);
	PM_CreateWaveformChannels(PM_Waveform[1], "Channels8", &ad[1][7]);
	PM_Waveform[2] = PM_CreateWaveform(0x47, "TestWaveform3", SplineSeries_Type, uint32_Type);
	PM_CreateWaveformChannels(PM_Waveform[2], "Channels1", &ad[2][0]);
	PM_CreateWaveformChannels(PM_Waveform[2], "Channels2", &ad[2][1]);
	PM_CreateWaveformChannels(PM_Waveform[2], "Channels3", &ad[2][2]);
	PM_CreateWaveformChannels(PM_Waveform[2], "Channels4", &ad[2][3]);
	PM_CreateWaveformChannels(PM_Waveform[2], "Channels5", &ad[2][4]);
	PM_CreateWaveformChannels(PM_Waveform[2], "Channels6", &ad[2][5]);
	PM_CreateWaveformChannels(PM_Waveform[2], "Channels7", &ad[2][6]);
	PM_CreateWaveformChannels(PM_Waveform[2], "Channels8", &ad[2][7]);
	PM_Image11 = PM_CreateImage(0x35, "TestImage1", Grayscale_Type, 60, 90, image);
	PM_CreateImage(0x36, "TestImage2", Binarization_Type, 120, 188, ad);
	PM_Param_t* PM_Param = PM_CreateParam(0x21, "TestParam");
	PM_CreateParamChannels(PM_Param, "TestParam1", R_Type, ad);
	PM_CreateParamChannels(PM_Param, "TestParam2", RW_Type, ad);
	PM_CreateParamChannels(PM_Param, "TestParam3", RW_Type, ad);
	PM_CreateParamChannels(PM_Param, "TestParam4", RW_Type, ad);
	PM_CreateParamChannels(PM_Param, "TestParam5", RW_Type, ad);
	PM_CreateParamChannels(PM_Param, "TestParam7", RW_Type, ad);
	PM_CreateParamChannels(PM_Param, "TestParam8", RW_Type, ad);
	PM_CreateParamChannels(PM_Param, "TestParam9", RW_Type, ad);
	PM_CreateParamChannels(PM_Param, "TestParam10", RW_Type, ad);
	PM_CreateParamChannels(PM_Param, "TestParam11", RW_Type, ad);
	PM_CreateParamChannels(PM_Param, "TestParam12", RW_Type, ad);
	PM_CreateParamChannels(PM_Param, "TestParam13", RW_Type, ad);
	PM_CreateParamChannels(PM_Param, "TestParam14", RW_Type, ad);
	PM_CreateParamChannels(PM_Param, "TestParam15", RW_Type, ad);
	PM_CreateParamChannels(PM_Param, "TestParam16", RW_Type, ad);
	PM_CreateParamChannels(PM_Param, "TestParam17", RW_Type, ad);
	PM_CreateParamChannels(PM_Param, "TestParam18", RW_Type, ad);
	PM_CreateParamChannels(PM_Param, "TestParam19", RW_Type, ad);
	PM_CreateParamChannels(PM_Param, "TestParam20", RW_Type, ad);
	PM_InitWindow();
}


