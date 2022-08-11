/*
 * Copyright (C), 1988-1999, Xxxxxx Tech. Co., Ltd.
 * FileName: PM_Image.h
 * Description: ͼ�����
 * Change Logs: 
  |Date          |Author       |Notes     		|version
  |2022-08-05    |���Ļ�ϲ     |Initial build   |1.0.0
 */

#ifndef __PM_IMAGE_H_
#define __PM_IMAGE_H_

#include "ParamMate.h"

/* @define PM_MAX_WIDTH */
#define PM_MAX_WIDTH		 188			   /* ͼ������� */

/* @define PM_MAX_HEIGHT */
#define PM_MAX_HEIGHT		 120			   /* ͼ�����߶� */


/* @enum Image_Type */
typedef enum{
	Binarization_Type,							/* ��ֵ��ͼ */
	Grayscale_Type,								/* �Ҷ�ͼ */
	RGB565_Type,								/* RGB565��ͼ */
	RGB888_Type,								/* RGB888��ͼ */
}Image_Type;

/* @struct PM_Image_t */
typedef struct
{
	PM_int8 Name[PM_MAX_NAME_LEN];				/* �ؼ����� */
	PM_uint8 ImageType;							/* ͼ������ */
	PM_uint16 ImageWidth;						/* ͼ���� */
	PM_uint16 ImageHeight;						/* ͼ��߶� */
	void* ImageAddr;							/* ͼ���ַ */
}PM_Image_t;


#endif


