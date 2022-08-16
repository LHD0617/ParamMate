/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2019,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		IAR 8.3 or MDK 5.28
 * @Target core		NXP RT1064DVL6A
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2019-04-30
 ********************************************************************************************************************/
#include "headfile.h"
#include "ParamMate.h"
#include "PM_CommProt.h"
#include "Motor.h"
#include "Control.h"

extern PID_struct Motor1;
extern PID_struct Motor2;

uint8 					UART1_rx_buffer;
lpuart_handle_t     	UART1_lpuartHandle;

PM_Param_t* PM_Param;

void UART1_callback(LPUART_Type *base, lpuart_handle_t *handle, status_t status, void *userData)
{
	handle->rxDataSize = 1;//����������������������������������������������������������������������������������������������ԭ����������
	handle->rxData = &UART1_rx_buffer;//������������������������������������������������������������������������ԭ��������ַ
	PM_RevHandle(PM_Param, UART1_rx_buffer);
//	rt_mb_send(Openart_mailbox, UART3_rx_buffer);
}

int main(void)
{
	DisableGlobalIRQ();
    board_init();
	uart_rx_irq(USART_1,1);
	uart_set_handle(USART_1, &UART1_lpuartHandle, UART1_callback, NULL, 0, &UART1_rx_buffer, 1);
	gpio_init(B9, GPO, 1, GPIO_PIN_CONFIG);
	gpio_init(B1, GPI, 1, GPIO_PIN_CONFIG);
	mt9v03x_csi_init();
	Motor_Init();
	pit_init();
	pit_interrupt_ms(PIT_CH0, 5);
	qtimer_quad_init(QTIMER_1, QTIMER1_TIMER2_C2,QTIMER1_TIMER3_C24);
	qtimer_quad_init(QTIMER_1, QTIMER1_TIMER0_C0,QTIMER1_TIMER1_C1);
    EnableGlobalIRQ(0);
	
	while(gpio_get(B1) == 1);
	
	/* ParamMate ���� */
	PM_ResetWindow();
	//PM_Image_t* PM_Image = PM_CreateImage(0x00, "MT9V032_Image", Binarization_Type, 60, 90, mt9v03x_csi_image);
	PM_Waveform_t* PM_Waveform1 = PM_CreateWaveform(0x01,"Speed_PID", SplineSeries_Type, int16_Type);
	PM_CreateWaveformChannels(PM_Waveform1, "Motor1 TarSpeed", &Motor1.Target_Speed);
	PM_CreateWaveformChannels(PM_Waveform1, "Motor2 TarSpeed", &Motor2.Target_Speed);
	PM_CreateWaveformChannels(PM_Waveform1, "Motor1 CurSpeed", &Motor1.Current_Speed);
	PM_CreateWaveformChannels(PM_Waveform1, "Motor2 CurSpeed", &Motor2.Current_Speed);
	PM_Waveform_t* PM_Waveform2 = PM_CreateWaveform(0x02,"Speed_PID", BarSeries_Type, int16_Type);
	PM_CreateWaveformChannels(PM_Waveform2, "Motor1 Duty", &Motor1.PIDOUT);
	PM_CreateWaveformChannels(PM_Waveform2, "Motor2 Duty", &Motor2.PIDOUT);
	PM_Param = PM_CreateParam(0x03, "PID_Param");
	PM_CreateParamChannels(PM_Param, "Motor1_TarSpeed", W_Type, int16_Type, &Motor1.Target_Speed);
	PM_CreateParamChannels(PM_Param, "Motor1_KP", W_Type, int16_Type, &Motor1.KP);
	PM_CreateParamChannels(PM_Param, "Motor1_KI", W_Type, int16_Type, &Motor1.KI);
	PM_CreateParamChannels(PM_Param, "Motor1_KD", W_Type, int16_Type, &Motor1.KD);
	PM_CreateParamChannels(PM_Param, "Motor2_TarSpeed", W_Type, int16_Type, &Motor2.Target_Speed);
	PM_CreateParamChannels(PM_Param, "Motor2_KP", W_Type, int16_Type, &Motor2.KP);
	PM_CreateParamChannels(PM_Param, "Motor2_KI", W_Type, int16_Type, &Motor2.KI);
	PM_CreateParamChannels(PM_Param, "Motor2_KD", W_Type, int16_Type, &Motor2.KD);
	PM_InitWindow();
	
    while(1)
    {
		if(mt9v03x_csi_finish_flag)
		{
			mt9v03x_csi_finish_flag = 0;
			gpio_toggle(B9);
			//PM_SendImageData(PM_Image);
			PM_SendWaveformData(PM_Waveform1);
			PM_SendWaveformData(PM_Waveform2);
		}
    }
}




