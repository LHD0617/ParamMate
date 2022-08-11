/*
 * Copyright (C), 1988-1999, Xxxxxx Tech. Co., Ltd.
 * FileName: PM_Waveform.h
 * Description: 波形控件文件
 * Change Logs: 
  |Date          |Author       |Notes     			|version
  |2022-08-03    |满心欢喜     |Initial build     	|1.0.0
 */
 
#ifndef __PM_WAVEFORM_H_
#define __PM_WAVEFORM_H_

#include "ParamMate.h"

/* @define PM_MAX_CHANNELS */
#define PM_MAX_CHANNELS		8					/* 最大通道数 */


/* @enum SeriesType */
typedef enum{
	LineSeries_Type,							/* 折线图 */
	SplineSeries_Type,							/* 样条线图 */
	BarSeries_Type,								/* 直条形图 */
	PieSeries_Type,								/* 饼图 */
}Series_Type;


/* @struct PM_Series_t */
typedef struct
{
	PM_int8 Name[PM_MAX_NAME_LEN];				/* 数据名称 */
	void* DataAddr;								/* 数据地址 */
}PM_Series_t;

/* @struct PM_Waveform_t */
typedef struct
{
	PM_int8 Name[PM_MAX_NAME_LEN];				/* 控件名称 */
	PM_uint8 SeriesType;						/* 控件类型 */
	PM_uint8 DataType;							/* 数据类型 */
	PM_uint8 Channels;							/* 通道数 */
	PM_Series_t PM_SeriesList[PM_MAX_CHANNELS];	/* 通道列表 */
}PM_Waveform_t;

/* @Function declarations */
PM_Series_t PM_CreateSeries(PM_int8* Name, void* DataAddr);
PM_Waveform_t PM_CreateWaveform(PM_int8* Name, Series_Type SeriesType, Data_Type DataType);
PM_err PM_AddSeries(PM_Waveform_t* PM_Waveform, PM_Series_t PM_Series);


#endif


