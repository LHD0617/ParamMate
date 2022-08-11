/*
 * Copyright (C), 1988-1999, Xxxxxx Tech. Co., Ltd.
 * FileName: PM_Param.h
 * Description: 参数控件
 * Change Logs: 
  |Date          |Author       |Notes     		|version
  |2022-08-05    |满心欢喜     |Initial build   |1.0.0
 */

#ifndef __PM_PARAM_H_
#define __PM_PARAM_H_

#include "ParamMate.h"

/* @define PM_MAX_PARAMNUM */
#define PM_MAX_PARAMNUM		32						/* 最大参数数量 */

/* @enum RWMode_Type */
typedef enum{
	R_Type,											/* 只读 */
	W_Type,											/* 只写 */
	RW_Type,										/* 读写 */
}RWMode_Type;

/* @struct PM_Parameter_t */
typedef struct
{
	PM_int8 Name[PM_MAX_NAME_LEN];					/* 数据名称 */
	Data_Type DataType;								/* 数据类型 */
	RWMode_Type RWMode;								/* 读写类型 */
	void* DataAddr;									/* 数据地址 */
}PM_Parameter_t;

/* @struct PM_Param_t */
typedef struct
{
	PM_int8 Name[PM_MAX_NAME_LEN];					/* 控件名称 */
	PM_uint8 ParamNum;								/* 通道数 */
	PM_Series_t PM_ParameterList[PM_MAX_PARAMNUM];	/* 通道列表 */
}PM_Param_t;


#endif


