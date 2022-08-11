/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : 主函数
	* @author					: 满心欢喜
	* @contact				: QQ:320388825 VX:LHD0617_
	* @Created				: 2021/12/30
  ******************************************************************************
  * @attention
  *
  * 本程序只供学习使用，未经作者许可，不得用于其它任何用途。
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "ParamMate.h"

uint16 ad[3][8];


/**
	* @name		main
	* @brief  	The application entry point.
	* @param  	void
	* @return 	void
	* @Sample 
  */
int main(void)
{
	PM_Waveform_t* PM_Waveform[3];
	uart_init(UART1, 115200, UART1_TX_PA9, UART1_RX_PA10, WordLength_8b, StopBits_1, Parity_No);
	PM_ResetWindow();
	PM_Waveform[0] = PM_CreateWaveform(0x45, "TestWaveform1", LineSeries_Type, uint8_Type);
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
	PM_CreateImage(0x35, "TestImage1", Grayscale_Type, 120, 188, ad);
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
	while(1)
	{
		
	}
}


