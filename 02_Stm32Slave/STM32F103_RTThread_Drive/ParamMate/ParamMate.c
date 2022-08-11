/*
 * Copyright (C), 1988-1999, Xxxxxx Tech. Co., Ltd.
 * FileName: ParamMate.c
 * Description: ParamMate驱动文件
 * Change Logs: 
  |Date          |Author       |Notes     			|version
  |2022-08-03    |满心欢喜     |Initial build     	|1.0.0
 */
 
#include "ParamMate.h"
#include "PM_CommProt.h"


/**
	* @name		PM_ResetWindow
	* @brief  	复位窗口
	* @param  	void
	* @return 	void
	* @Sample 
  */
void PM_ResetWindow(void)
{
	PM_uint8 dat = 0x01;
	PM_SendMessage(PM_RESETWINDOW_COMM, PM_MAIN_WINDOW_ID, 0x01, &dat);
}

/**
	* @name		PM_InitWindow
	* @brief  	初始化窗口
	* @param  	void
	* @return 	void
	* @Sample 
  */
void PM_InitWindow(void)
{
	PM_uint8 dat = 0x01;
	PM_SendMessage(PM_INITWINDOW_COMM, PM_MAIN_WINDOW_ID, 0x01, &dat);
}

/**
	* @name		PM_CreateParam
	* @brief  	创建参数控件
	* @param  	ID			控件ID（保证全局唯一性）
	* @param  	Name		控件名称（标题）
	* @return 	参数控件结构体指针
	* @Sample 	
  */
PM_Param_t* PM_CreateParam(PM_uint8 ID, const PM_int8* Name)
{
	PM_uint8 datbuf[PM_MAX_NAME_LEN] = {0};
	PM_Param_t* PM_Param = (PM_Param_t*)malloc(sizeof(PM_Param_t));
	if(PM_Param == PM_NULL)
	{
		return PM_NULL;
	}
	PM_Param -> ID = ID;
	PM_Strcpy(datbuf, Name);
	PM_SendMessage(PM_CREATEPARAM_COMM, ID, sizeof(datbuf), datbuf);
	return PM_Param;
}

/**
	* @name		PM_CreateParamChannels
	* @brief  	创建参数通道
	* @param  	PM_Param			参数控件指针
	* @param  	Name				数据名称
	* @param  	ModeType			读写类型
	* @param  	DataAddr			数据地址
	* @return 	错误码
	* @Sample 
  */
PM_err PM_CreateParamChannels(PM_Param_t* PM_Param, const PM_int8* Name, RWMode_Type ModeType, void* DataAddr)
{
	PM_uint8 datbuf[PM_MAX_NAME_LEN + 1] = {0};
	PM_uint8* Dp = datbuf;
	if(PM_Param -> Channels >= PM_MAX_PARAMCANNELS)	return PM_EFULL;
	PM_Param -> DataAddrList[PM_Param -> Channels++] = DataAddr;
	*Dp++ = ModeType & 0xff;
	Dp = PM_Strcpy(Dp, Name);
	PM_SendMessage(PM_CREATEPARAMCHANNELS_COMM, PM_Param -> ID, sizeof(datbuf), datbuf);
	return PM_EOK;
}

/**
	* @name		PM_CreateWaveform
	* @brief  	创建示波控件
	* @param  	ID			控件ID（保证全局唯一性）
	* @param  	Name		控件名称（标题）
	* @param  	SeriesType	控件类型：详见ParamMate.h文件枚举类型
	* @param  	DataType	数据类型
	* @return 	示波控件结构体指针
	* @Sample 	PM_CreateWaveform(0x00, "TEST123456", SplineSeries_Type, uint16_Type);
  */
PM_Waveform_t* PM_CreateWaveform(PM_uint8 ID, const PM_int8* Name, Series_Type SeriesType, Data_Type DataType)
{
	PM_uint8 datbuf[PM_MAX_NAME_LEN + 2] = {0};
	PM_uint8* Dp = datbuf;
	PM_Waveform_t* PM_Waveform = (PM_Waveform_t*)malloc(sizeof(PM_Waveform_t));
	if(PM_Waveform == PM_NULL)
	{
		return PM_NULL;
	}
	PM_Waveform -> ID = ID;
	PM_Waveform -> DataType = DataType;
	*Dp++ = SeriesType & 0xff;
	*Dp++ = DataType & 0xff;
	Dp = PM_Strcpy(Dp, Name);
	PM_SendMessage(PM_CREATEWAVEFORM_COMM, ID, sizeof(datbuf), datbuf);
	return PM_Waveform;
}

/**
	* @name		PM_CreateWaveformChannels
	* @brief  	创建示波通道
	* @param  	PM_Waveform			示波控件指针
	* @param  	Name				数据名称
	* @param  	DataAddr			数据地址
	* @return 	错误码
	* @Sample 
  */
PM_err PM_CreateWaveformChannels(PM_Waveform_t* PM_Waveform, const PM_int8* Name, void* DataAddr)
{
	PM_uint8 datbuf[PM_MAX_NAME_LEN] = {0};
	if(PM_Waveform -> Channels >= PM_MAX_WAVEFORMCANNELS)	return PM_EFULL;
	PM_Waveform -> DataAddrList[PM_Waveform -> Channels++] = DataAddr;
	PM_Strcpy(datbuf, Name);
	PM_SendMessage(PM_CREATEWAVEFORMCHANNELS_COMM, PM_Waveform -> ID, sizeof(datbuf), datbuf);
	return PM_EOK;
}

/**
	* @name		PM_CreateImage
	* @brief  	创建图传控件
	* @param  	ID			控件ID（保证全局唯一性）
	* @param  	Name		控件名称（标题）
	* @param  	ImageType	图像类型：详见ParamMate.h文件枚举类型
	* @param  	DataAddr	图像地址
	* @return 	图传控件结构体指针
	* @Sample 	
  */
PM_Image_t* PM_CreateImage(PM_uint8 ID, const PM_int8* Name, Image_Type ImageType, PM_uint8 Height, PM_uint8 Width, void* DataAddr)
{
	PM_uint8 datbuf[PM_MAX_NAME_LEN + 3] = {0};
	PM_uint8* Dp = datbuf;
	PM_Image_t* PM_Image = (PM_Image_t*)malloc(sizeof(PM_Image_t));
	if(PM_Image == PM_NULL)
	{
		return PM_NULL;
	}
	PM_Image -> ID = ID;
	PM_Image -> ImageType = ImageType;
	PM_Image -> DataAddr = DataAddr;
	*Dp++ = ImageType & 0xff;
	*Dp++ = Height;
	*Dp++ = Width;
	Dp = PM_Strcpy(Dp, Name);
	PM_SendMessage(PM_CREATEIMAGE_COMM, ID, sizeof(datbuf), datbuf);
	return PM_Image;
}

/**
	* @name		PM_SendParamData
	* @brief  	发送参数控件数据
	* @param  	PM_Param	参数控件结构体
	* @return 	void
	* @Sample 
  */
void PM_SendParamData(PM_Param_t* PM_Param)
{
	
}

/**
	* @name		PM_SendWaveformData
	* @brief  	发送示波控件数据
	* @param  	PM_Param	示波控件结构体
	* @return 	void
	* @Sample 
  */
void PM_SendWaveformData(PM_Waveform_t* PM_Waveform)
{
	PM_uint8 UnitChannelSize;
	PM_uint8* pdatbuf;
	if(PM_Waveform -> DataType & 0x08)
		UnitChannelSize = 4 + (PM_Waveform -> DataType & 0x01) * 4;
	else
		UnitChannelSize = 0x01 << (PM_Waveform -> DataType & 0x03);
	PM_uint8 datbuf[UnitChannelSize * PM_Waveform -> Channels];
	pdatbuf = datbuf;
	for(PM_uint8 i = 0; i < PM_Waveform -> Channels; i++)
	{
		for(PM_uint8 j = 0; j < UnitChannelSize; j++)
		{
			*pdatbuf++ = *((PM_uint8*)PM_Waveform -> DataAddrList[i] + j);
		}
	}
	PM_SendMessage(PM_SENDWAVEFORM_COMM, PM_Waveform -> ID, sizeof(datbuf), datbuf);
}

/**
	* @name		PM_SendImageData
	* @brief  	发送图传控件数据
	* @param  	PM_Image	图传控件结构体
	* @return 	void
	* @Sample 
  */
void PM_SendImageData(PM_Image_t* PM_Image)
{
	PM_uint16 DataSize;
	if(PM_Image -> ImageType == 0)
	{
		DataSize = PM_Image -> Height * PM_Image -> Width / 8;
		if(PM_Image -> Height * PM_Image -> Width % 8 != 0)
		{
			DataSize++;
		}
	}
	else
	{
		DataSize = PM_Image -> Height * PM_Image -> Width * PM_Image -> ImageType;
	}
	PM_SendMessage(PM_SENDIMAGE_COMM, PM_Image -> ID, DataSize, PM_Image -> DataAddr);
}

/**
	* @name		PM_Strcpy
	* @brief  	字符串拷贝函数
	* @param  	startaddr	首地址
	* @param  	strDest		字符串
	* @return 	结束地址
	* @Sample 
  */
PM_uint8* PM_Strcpy(PM_uint8 *startaddr, const PM_int8 *strSrc)
{
	PM_uint8 i;
	for(i = 0; i < PM_MAX_NAME_LEN && *strSrc != '\0'; i++)
	{
		*startaddr++ = *strSrc++;
	}
	return startaddr + PM_MAX_NAME_LEN;
}


