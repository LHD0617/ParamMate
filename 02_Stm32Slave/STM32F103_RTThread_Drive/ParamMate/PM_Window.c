/*
 * Copyright (C), 1988-1999, Xxxxxx Tech. Co., Ltd.
 * FileName: PM_Window.c
 * Description: 窗口文件
 * Change Logs: 
  |Date          |Author       |Notes     			|version
  |2022-08-03    |满心欢喜     |Initial build     	|1.0.0
 */
 
#include "ParamMate.h"

/**
	* @name		PM_CreateWindow
	* @brief  	创建窗口
	* @param  	Name		窗口名称
	* @return 	PM_Window	窗口结构体
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
	* @brief  	添加示波控件
	* @param  	PM_Window		窗口结构体指针
	* @param  	PM_Waveform		控件结构体指针
	* @return 	错误码
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
	* @brief  	窗口初始化
	* @param  	PM_Window		窗口结构体
	* @return 	错误码
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
	* @brief  	字符串拷贝函数
	* @param  	strSrc		原字符串
	* @param  	strDest		目的字符串
	* @return 				目的字符串
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




