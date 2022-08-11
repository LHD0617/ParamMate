/*
 * Copyright (C), 1988-1999, Xxxxxx Tech. Co., Ltd.
 * FileName: PM_Waveform.h
 * Description: ���οؼ��ļ�
 * Change Logs: 
  |Date          |Author       |Notes     			|version
  |2022-08-03    |���Ļ�ϲ     |Initial build     	|1.0.0
 */
 
#ifndef __PM_WAVEFORM_H_
#define __PM_WAVEFORM_H_

#include "ParamMate.h"

/* @define PM_MAX_CHANNELS */
#define PM_MAX_CHANNELS		8					/* ���ͨ���� */


/* @enum SeriesType */
typedef enum{
	LineSeries_Type,							/* ����ͼ */
	SplineSeries_Type,							/* ������ͼ */
	BarSeries_Type,								/* ֱ����ͼ */
	PieSeries_Type,								/* ��ͼ */
}Series_Type;


/* @struct PM_Series_t */
typedef struct
{
	PM_int8 Name[PM_MAX_NAME_LEN];				/* �������� */
	void* DataAddr;								/* ���ݵ�ַ */
}PM_Series_t;

/* @struct PM_Waveform_t */
typedef struct
{
	PM_int8 Name[PM_MAX_NAME_LEN];				/* �ؼ����� */
	PM_uint8 SeriesType;						/* �ؼ����� */
	PM_uint8 DataType;							/* �������� */
	PM_uint8 Channels;							/* ͨ���� */
	PM_Series_t PM_SeriesList[PM_MAX_CHANNELS];	/* ͨ���б� */
}PM_Waveform_t;

/* @Function declarations */
PM_Series_t PM_CreateSeries(PM_int8* Name, void* DataAddr);
PM_Waveform_t PM_CreateWaveform(PM_int8* Name, Series_Type SeriesType, Data_Type DataType);
PM_err PM_AddSeries(PM_Waveform_t* PM_Waveform, PM_Series_t PM_Series);


#endif


