/*
 * Copyright (C), 1988-1999, Xxxxxx Tech. Co., Ltd.
 * FileName: PM_Waveform.c
 * Description: ���οؼ��ļ�
 * Change Logs: 
  |Date          |Author       |Notes     			|version
  |2022-08-03    |���Ļ�ϲ     |Initial build     	|1.0.0
 */
 
#include "ParamMate.h"


/**
	* @name		PM_CreateWaveform
	* @brief  	����ʾ���ؼ�
	* @param  	Name		�ؼ�����
	* @param  	SeriesType	�ؼ�����
	* @param  	DataType	��������
	* @return 	PM_Waveform	�ؼ��ṹ��
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
	* @brief  	��������ͨ��
	* @param  	Name		ͨ������
	* @param  	DataAddr	ͨ�����ݵ�ַ
	* @return 	PM_Series	ͨ���ṹ��
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
	* @brief  	ʾ���ؼ����ͨ��
	* @param  	PM_Waveform		ʾ���ؼ��ṹ��ָ��
	* @param  	PM_Series		ͨ���ṹ��ָ��
	* @return 	������
	* @Sample 
  */
PM_err PM_AddSeries(PM_Waveform_t* PM_Waveform, PM_Series_t PM_Series)
{
	if(PM_Waveform -> Channels >= PM_MAX_CHANNELS)	return PM_EFULL;
	PM_Waveform -> PM_SeriesList[PM_Waveform -> Channels++] = PM_Series;
	return PM_EOK;
}





