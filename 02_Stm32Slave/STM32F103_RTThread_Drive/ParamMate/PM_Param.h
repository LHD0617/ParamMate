/*
 * Copyright (C), 1988-1999, Xxxxxx Tech. Co., Ltd.
 * FileName: PM_Param.h
 * Description: �����ؼ�
 * Change Logs: 
  |Date          |Author       |Notes     		|version
  |2022-08-05    |���Ļ�ϲ     |Initial build   |1.0.0
 */

#ifndef __PM_PARAM_H_
#define __PM_PARAM_H_

#include "ParamMate.h"

/* @define PM_MAX_PARAMNUM */
#define PM_MAX_PARAMNUM		32						/* ���������� */

/* @enum RWMode_Type */
typedef enum{
	R_Type,											/* ֻ�� */
	W_Type,											/* ֻд */
	RW_Type,										/* ��д */
}RWMode_Type;

/* @struct PM_Parameter_t */
typedef struct
{
	PM_int8 Name[PM_MAX_NAME_LEN];					/* �������� */
	Data_Type DataType;								/* �������� */
	RWMode_Type RWMode;								/* ��д���� */
	void* DataAddr;									/* ���ݵ�ַ */
}PM_Parameter_t;

/* @struct PM_Param_t */
typedef struct
{
	PM_int8 Name[PM_MAX_NAME_LEN];					/* �ؼ����� */
	PM_uint8 ParamNum;								/* ͨ���� */
	PM_Series_t PM_ParameterList[PM_MAX_PARAMNUM];	/* ͨ���б� */
}PM_Param_t;


#endif


