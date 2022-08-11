/*
 * Copyright (C), 1988-1999, Xxxxxx Tech. Co., Ltd.
 * FileName: PM_Waveform.c
 * Description: 波形控件文件
 * Change Logs: 
  |Date          |Author       |Notes     			|version
  |2022-08-03    |满心欢喜     |Initial build     	|1.0.0
 */
 
#include "ParamMate.h"


/**
	* @name		PM_CreateWaveform
	* @brief  	创建示波控件
	* @param  	Name		控件名称
	* @param  	SeriesType	控件类型
	* @param  	DataType	数据类型
	* @return 	PM_Waveform	控件结构体
	* @Sample 
  */
PM_Waveform_t PM_CreateWaveform(PM_int8* Name, Series_Type SeriesType, Data_Type DataType)
{
	PM_Waveform_t PM_Waveform;
	PM_Strcpy(PM_Waveform.Name, Name);
	PM_Waveform.SeriesType = SeriesType;
	PM_Waveform.DataType = DataType;
	PM_Waveform.Channels = 0;
	return PM_Waveform;
}


/**
	* @name		PM_CreateSeries
	* @brief  	创建数据通道
	* @param  	Name		通道名称
	* @param  	DataAddr	通道数据地址
	* @return 	PM_Series	通道结构体
	* @Sample 
  */
PM_Series_t PM_CreateSeries(PM_int8* Name, void* DataAddr)
{
	PM_Series_t PM_Series;
	PM_Strcpy(PM_Series.Name, Name);
	PM_Series.DataAddr = DataAddr;
	return PM_Series;
}

/**
	* @name		PM_AddSeries
	* @brief  	示波控件添加通道
	* @param  	PM_Waveform		示波控件结构体指针
	* @param  	PM_Series		通道结构体指针
	* @return 	错误码
	* @Sample 
  */
PM_err PM_AddSeries(PM_Waveform_t* PM_Waveform, PM_Series_t PM_Series)
{
	if(PM_Waveform -> Channels >= PM_MAX_CHANNELS)	return PM_EFULL;
	PM_Waveform -> PM_SeriesList[PM_Waveform -> Channels++] = PM_Series;
	return PM_EOK;
}





