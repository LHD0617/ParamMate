/*
 * Copyright (C), 1988-1999, Xxxxxx Tech. Co., Ltd.
 * FileName: PM_CommProt.c
 * Description: 通信协议栈
 * Change Logs: 
  |Date          |Author       |Notes     			|version
  |2022-08-03    |满心欢喜     |Initial build     	|1.0.0
 */
 
#include "PM_CommProt.h"


/**
	* @name		PM_SendMessage
	* @brief  	发送消息
	* @param  	Type		消息类型
	* @param  	Length		消息长度
	* @param  	DataP		消息数据
	* @return 	void
	* @Sample 
  */
void PM_SendMessage(PM_uint8 Type, PM_uint8 ID, PM_uint16 Length, void* DataP)
{
	PM_CommMsg_t PM_CommMsg;			/* 声明数据包结构体 */
	PM_CommMsg.Head = PM_PACKAGEHEAD;	/* 帧头 */
	PM_CommMsg.Type = Type;				/* 消息类型 */
	PM_CommMsg.ID = ID;					/* 数据ID */
	PM_CommMsg.Length = Length;			/* 数据长度 */
	PM_CommMsg.DataP = DataP;			/* 数据地址 */
	PM_SendPackect(&PM_CommMsg);		/* 发送数据包 */
}

/**
	* @name		PM_SendPackect
	* @brief  	发送数据包
	* @param  	PM_CommMsg		数据包结构体
	* @return 	void
	* @Sample 
  */
void PM_SendPackect(PM_CommMsg_t* PM_CommMsg)
{
	PM_uint32 i;
	PM_uint8 dat;
	PM_SendByte(PM_CommMsg -> Head);
	PM_TranSendByte(PM_CommMsg -> Type);
	PM_TranSendByte(PM_CommMsg -> ID);
	PM_TranSendByte(PM_CommMsg -> Length & 0xFF);
	PM_TranSendByte(PM_CommMsg -> Length >> 8);
	for(i = 0; i < PM_CommMsg -> Length; i++)
	{
		dat = *((PM_uint8*)PM_CommMsg -> DataP + i);
		PM_TranSendByte(dat);
	}
}

/**
	* @name		PM_TranSendByte
	* @brief  	转义发送
	* @param  	dat		待发送的数据
	* @return 	void
	* @Sample 
  */
void PM_TranSendByte(PM_uint8 dat)
{
	if(dat == 0x7A)
	{
		PM_SendByte(0x7B);
		PM_SendByte(0x00);
	}
	else if(dat == 0x7B)
	{
		PM_SendByte(0x7B);
		PM_SendByte(0x01);
	}
	else
	{
		PM_SendByte(dat);
	}
}

/**
	* @name		PM_SendBinImage
	* @brief  	发送二值化图像
	* @param  	PM_CommMsg		数据包结构体
	* @return 	void
	* @Sample 
  */
void PM_SendBinImage(PM_Image_t* PM_Image)
{
	PM_uint8 dat, j;
	PM_uint16 DataSize, i;
	if(PM_Image -> ImageType == 0)
	{
		DataSize = PM_Image -> Height * PM_Image -> Width / 8;
		if(PM_Image -> Height * PM_Image -> Width % 8 != 0)
		{
			DataSize++;
		}
	}
	PM_SendByte(PM_PACKAGEHEAD);
	PM_TranSendByte(PM_SENDIMAGE_COMM);
	PM_TranSendByte(PM_Image -> ID);
	PM_TranSendByte(DataSize & 0xFF);
	PM_TranSendByte(DataSize >> 8);
	for(i = 0; i < DataSize; i++)
	{
		dat = 0;
		for(j = 0; j < 8; j++)
		{
			if(*((PM_uint8*)PM_Image -> DataAddr + i * 8 + j))
				dat |= (0x01 << (7 - j));
		}
		PM_TranSendByte(dat);
	}
	
}

