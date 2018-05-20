/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   �����жϽ��ղ���
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� F103-ָ���� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "./AS32/AS32.h"
#include "./led/bsp_led.h"  
#include "./Agreement/Agreement.h"
#include "./systick/systick.h"
#include "./check/check.h"
#include "./query/query.h"
#include "./iwdg/bsp_iwdg.h"
#include "stm32f10x_iwdg.h"


//����һ֡Э��
extern TransportProtocol_Typedef TransportProtocol;
u8 ch=0;
extern u8 bh;

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
	
  /*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
  USART_Config();
	USART2_Config();
	
	/* ��ʼ��AS32 GPIO���� */
	AS32_Config();
	
	/*AS32  MD0 MD1 ģʽ���� */
	To_configure_AS32();
	
	LED_GPIO_Config();
	
	Key_GPIO_Config();
	
  //��ʼ������Э��  ָ�򴮿ڽ��ջ�����  
	TransportProtocol_Init(&TransportProtocol);
	
	// IWDG  ��ʱ���
	IWDG_Config(IWDG_Prescaler_256 ,8000);
	
	printf("�����ʼ�����\r\n");
	
  while(1)
	{	
		LED1_TOGGLE;
		if(1)
		{
			switch(ch)
			{
				case 1:electricity_agreement(); break;  //����
				case 2:window_agreement();break;        //����		
				case 3:curtain_agreement();break;       //����
				case 4:experiment_agreement();break;    //ʵ��̨
				case 5:window2_agreement();break;       //���Ŵ���
			}
			ch++;
			if(ch>5) ch=0;		
		}
		
		if(bh==1)
		{
			response_OK();
			bh=0;
		}			
    
		//ι��
		IWDG_Feed();
	}
}
/*********************************************END OF FILE**********************/
