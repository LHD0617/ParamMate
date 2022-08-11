/*
 * Copyright (C), 1988-1999, Xxxxxx Tech. Co., Ltd.
 * FileName: PM_Image.h
 * Description: 图传组件
 * Change Logs: 
  |Date          |Author       |Notes     		|version
  |2022-08-05    |满心欢喜     |Initial build   |1.0.0
 */

#ifndef __PM_IMAGE_H_
#define __PM_IMAGE_H_

#include "ParamMate.h"

/* @define PM_MAX_WIDTH */
#define PM_MAX_WIDTH		 188			   /* 图像最大宽度 */

/* @define PM_MAX_HEIGHT */
#define PM_MAX_HEIGHT		 120			   /* 图像最大高度 */


/* @enum Image_Type */
typedef enum{
	Binarization_Type,							/* 二值化图 */
	Grayscale_Type,								/* 灰度图 */
	RGB565_Type,								/* RGB565彩图 */
	RGB888_Type,								/* RGB888彩图 */
}Image_Type;

/* @struct PM_Image_t */
typedef struct
{
	PM_int8 Name[PM_MAX_NAME_LEN];				/* 控件名称 */
	PM_uint8 ImageType;							/* 图像类型 */
	PM_uint16 ImageWidth;						/* 图像宽度 */
	PM_uint16 ImageHeight;						/* 图像高度 */
	void* ImageAddr;							/* 图像地址 */
}PM_Image_t;


#endif


