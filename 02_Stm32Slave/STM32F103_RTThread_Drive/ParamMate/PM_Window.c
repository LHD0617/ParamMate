/*
 * Copyright (C), 1988-1999, Xxxxxx Tech. Co., Ltd.
 * FileName: PM_Window.c
 * Description: �����ļ�
 * Change Logs: 
  |Date          |Author       |Notes     			|version
  |2022-08-03    |���Ļ�ϲ     |Initial build     	|1.0.0
 */
 
#include "ParamMate.h"

/**
	* @name		PM_CreateWindow
	* @brief  	��������
	* @param  	Name		��������
	* @return 	PM_Window	���ڽṹ��
	* @Sample 
  */
PM_Window_t PM_CreateWindow(PM_int8* Name)
{
	PM_Window_t PM_Window;
	PM_Strcpy(PM_Window.Name, Name);
	PM_Window.PM_WaveformNum = 0;
	return PM_Window;
}

/**
	* @name		PM_Waveform
	* @brief  	���ʾ���ؼ�
	* @param  	PM_Window		���ڽṹ��ָ��
	* @param  	PM_Waveform		�ؼ��ṹ��ָ��
	* @return 	������
	* @Sample 
  */
PM_err PM_AddWaveform(PM_Window_t* PM_Window, PM_Waveform_t PM_Waveform)
{
	if(PM_Window -> PM_WaveformNum >= PM_MAX_WAVEFORM)	return PM_EFULL;
	PM_Window -> PM_WaveformList[PM_Window -> PM_WaveformNum++] = PM_Waveform;
	return PM_EOK;
}

/**
	* @name		PM_WindowInit
	* @brief  	���ڳ�ʼ��
	* @param  	PM_Window		���ڽṹ��
	* @return 	������
	* @Sample 
  */
PM_err PM_WindowInit(PM_Window_t* PM_Window)
{
	PM_uint8 i;
	PM_uint8 SpaceSize = 0;
	for(i = 0; i < PM_Window -> PM_ParamNum; i++)
		SpaceSize += PM_Window -> PM_ParamList[i].ParamNum;
	for(i = 0; i < PM_Window -> PM_WaveformNum; i++)
		SpaceSize += PM_Window -> PM_WaveformList[i].Channels;
	SpaceSize += PM_Window -> PM_ImageNum;
	void** DataAddressList = malloc(SpaceSize * sizeof(void*));
	
	PM_SendWindowReset();
	PM_SendWindowInit(PM_Window);
	
	return PM_EOK;
}

/**
	* @name		PM_Strcpy
	* @brief  	�ַ�����������
	* @param  	strSrc		ԭ�ַ���
	* @param  	strDest		Ŀ���ַ���
	* @return 				Ŀ���ַ���
	* @Sample 
  */
PM_int8* PM_Strcpy(PM_int8 *strDest, const PM_int8 *strSrc)
{
	PM_uint8 len = 0;
    if(strDest == PM_NULL || strSrc == PM_NULL)
        return PM_NULL;
    if(strDest == strSrc)
        return strDest;
    PM_int8 *tempDest = strDest;
    while((*strDest++ = *strSrc++) != '\0' && len < PM_MAX_NAME_LEN) len++;
    return tempDest;
}




