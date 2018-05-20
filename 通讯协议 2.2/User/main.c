/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   串口中断接收测试
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火 F103-指南者 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
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


//定义一帧协议
extern TransportProtocol_Typedef TransportProtocol;
u8 ch=0;
extern u8 bh;

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{	
	
  /*初始化USART 配置模式为 115200 8-N-1，中断接收*/
  USART_Config();
	USART2_Config();
	
	/* 初始化AS32 GPIO引脚 */
	AS32_Config();
	
	/*AS32  MD0 MD1 模式配置 */
	To_configure_AS32();
	
	LED_GPIO_Config();
	
	Key_GPIO_Config();
	
  //初始化传输协议  指向串口接收缓冲区  
	TransportProtocol_Init(&TransportProtocol);
	
	// IWDG  超时溢出
	IWDG_Config(IWDG_Prescaler_256 ,8000);
	
	printf("程序初始化完成\r\n");
	
  while(1)
	{	
		LED1_TOGGLE;
		if(1)
		{
			switch(ch)
			{
				case 1:electricity_agreement(); break;  //配电柜
				case 2:window_agreement();break;        //窗户		
				case 3:curtain_agreement();break;       //窗帘
				case 4:experiment_agreement();break;    //实验台
				case 5:window2_agreement();break;       //二号窗户
			}
			ch++;
			if(ch>5) ch=0;		
		}
		
		if(bh==1)
		{
			response_OK();
			bh=0;
		}			
    
		//喂狗
		IWDG_Feed();
	}
}
/*********************************************END OF FILE**********************/
