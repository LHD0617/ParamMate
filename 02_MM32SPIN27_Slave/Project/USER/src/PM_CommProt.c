/*
 * Copyright (C), 1988-1999, Xxxxxx Tech. Co., Ltd.
 * FileName: PM_CommProt.c
 * Description: ͨ��Э��ջ
 * Change Logs: 
  |Date          |Author       |Notes     			|version
  |2022-08-03    |���Ļ�ϲ     |Initial build     	|1.0.0
 */
 
#include "PM_CommProt.h"


/**
	* @name		PM_SendMessage
	* @brief  	������Ϣ
	* @param  	Type		��Ϣ����
	* @param  	Length		��Ϣ����
	* @param  	DataP		��Ϣ����
	* @return 	void
	* @Sample 
  */
void PM_SendMessage(PM_uint8 Type, PM_uint8 ID, PM_uint16 Length, void* DataP)
{
	PM_CommMsg_t PM_CommMsg;			/* �������ݰ��ṹ�� */
	PM_CommMsg.Head = PM_PACKAGEHEAD;	/* ֡ͷ */
	PM_CommMsg.Type = Type;				/* ��Ϣ���� */
	PM_CommMsg.ID = ID;					/* ����ID */
	PM_CommMsg.Length = Length;			/* ���ݳ��� */
	PM_CommMsg.DataP = DataP;			/* ���ݵ�ַ */
	PM_SendPackect(&PM_CommMsg);		/* �������ݰ� */
}

/**
	* @name		PM_SendPackect
	* @brief  	�������ݰ�
	* @param  	PM_CommMsg		���ݰ��ṹ��
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
	* @brief  	ת�巢��
	* @param  	dat		�����͵�����
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
	* @brief  	���Ͷ�ֵ��ͼ��
	* @param  	PM_CommMsg		���ݰ��ṹ��
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

