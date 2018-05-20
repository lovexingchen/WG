#include "./query/query.h"
#include "./systick/systick.h"
#include "./check/check.h"
#include "bsp_usart.h"
#include "./Agreement/Agreement.h"

TransportProtocol_Typedef TransportProtocol;

TransportProtocol_Result res;	//传输结果

uint16_t i = 4;
u8 i2 = 0;
u8 i3 = 0;
uint16_t  Num_sum=0; 

extern u8 aa1[];
extern u8 aa2[];
extern u8 aa3[];

extern uint16_t num;
extern uint8_t rx_buf[];
extern uint8_t rx1_buf[];
extern uint16_t num1;

void electricity_agreement(void)
{
	  u8 AS32_TTL_electricity[] = {0x20,0x01,0x17};//劳拉模块定点传输地址
		TransportProtocol.Device_Address1 = 0XFF;   //设备地址  
    TransportProtocol.Device_Address2 = 0X60;   //设备地址  配电柜
	  TransportProtocol.Equipment_Number = 0X01;  //总线电能测量
    TransportProtocol.Function_Type1 = 0XFF;    //帧功能    
	  TransportProtocol.Function_Type2 = 0X01;    //帧功能      
		TransportProtocol.Parameter1 = 0X00;        //帧参数长度
		TransportProtocol.Parameter2 = 0X0A;        //帧参数长度    
		TransportProtocol_Manager.Packed();			    //打包	
	
		Usart_SendArray(USART2,AS32_TTL_electricity,3);
	  Usart_SendArray(USART2,TransportProtocol_Manager.Buf,10);

		while(i)
		{
			delay_ms(500);
			if(i==1)  //第一次超时重发 第二次超时判断故障并退出
			{
				if(i2==1)
				{
					TransportProtocol.Function_Type1 = 0XFF;
					TransportProtocol.Function_Type2 = 0XFF;
					TransportProtocol_Manager.Packed();			    //打包	
//					printf("设备故障：配电柜\r\n");
	        Usart_SendArray(USART1,TransportProtocol_Manager.Buf,10);
					i2 = 0;
					i = 4;
					num = 0;
					break;
				}
				i2++;
				i = 4;
				Usart_SendArray(USART2,AS32_TTL_electricity,3);
	      Usart_SendArray(USART2,TransportProtocol_Manager.Buf,10);
			}
			
			if(num >= 5)
		  {
			  Num_sum = rx_buf[6]+rx_buf[7];
			  if(num == Num_sum)  //数据位校验
			  {
				  res = TransportProtocol_Manager.Unpacked();//解包	
         	if((res == UPACKED_SUCCESS) && (rx_buf[2] ==  0X60))  //解包成功
				  {							
//						printf("配电柜态查询成功，返回一帧数据：");
				    Usart_SendArray(USART1,rx_buf,num);		
//            for(i3=0;i3<num;i3++)
//            {
//							printf(" %X",rx_buf[i3]);
//						}						
//						printf("\r\n");
						num = 0;		
						i2 = 0;
						i = 4;
						break;
				  } 
          else  //解包失败的时候重新进行应答
					{
						i=2; //即将进行重发
					}		

			  }
		  }
				
			i--;
			
		}
}


void curtain_agreement(void)
{
    u8 AS32_TTL_curtain[] = {0x30,0x01,0x17};   //劳拉模块定点传输地址
		TransportProtocol.Device_Address1 = 0XFF;   //设备地址  
    TransportProtocol.Device_Address2 = 0X10;   //设备地址  窗帘电机
	  TransportProtocol.Equipment_Number = 0X01;  //一号窗帘
    TransportProtocol.Function_Type1 = 0XFF;    //帧功能    
	  TransportProtocol.Function_Type2 = 0X00;    //帧功能    查询窗帘状态
		TransportProtocol.Parameter1 = 0X00;        //帧参数长度
		TransportProtocol.Parameter2 = 0X0A;        //帧参数长度    
		TransportProtocol_Manager.Packed();			    //打包	
	  Usart_SendArray(USART2,AS32_TTL_curtain,3);
	  Usart_SendArray(USART2,TransportProtocol_Manager.Buf,10);
	  while(i)
		{
			delay_ms(500);
			if(i==1)  //第一次超时重发 第二次超时判断故障并退出
			{
				if(i2==1)
				{
					TransportProtocol.Function_Type1 = 0XFF;
					TransportProtocol.Function_Type2 = 0XFF;
					TransportProtocol_Manager.Packed();			    //打包	
	        Usart_SendArray(USART1,TransportProtocol_Manager.Buf,10);
//					printf("设备故障：窗帘\r\n");
					i2 = 0;
					i = 4;
					num = 0;
					break;
				}
				i2++;
				i = 4;
				Usart_SendArray(USART2,AS32_TTL_curtain,3);
	      Usart_SendArray(USART2,TransportProtocol_Manager.Buf,10);
			}
			if(num >= 5)
		  {
			  Num_sum = rx_buf[6]+rx_buf[7];
			  if(num == Num_sum)  //数据位校验
			  {
				  res = TransportProtocol_Manager.Unpacked();//解包	
         	if((res == UPACKED_SUCCESS) && (rx_buf[2] ==  0X10))  //解包成功
				  {	
//						printf("一号窗帘状态查询成功，返回一帧数据：");
				    Usart_SendArray(USART1,rx_buf,num);
//            for(i3=0;i3<num;i3++)
//            {
//							printf(" %X",rx_buf[i3]);
//						}	
//						printf(" \r\n");
						i2 = 0;
						num = 0;
						i = 4;
						break;
				  } 
          else  //解包失败的时候重新进行应答
					{
						i=2; //即将进行重发
					}		
					
			  }
				num = 0;
		  }
				
			i--;
			
		}
}

void window_agreement(void)
{
    u8 AS32_TTL_window[] = {0x30,0x01,0x17};   //劳拉模块定点传输地址
		TransportProtocol.Device_Address1 = 0XFF;   //设备地址  
    TransportProtocol.Device_Address2 = 0X20;   //设备地址  窗户电机
	  TransportProtocol.Equipment_Number = 0X01;  //一号窗帘
    TransportProtocol.Function_Type1 = 0XFF;    //帧功能    
	  TransportProtocol.Function_Type2 = 0X00;    //帧功能    查询窗帘状态
		TransportProtocol.Parameter1 = 0X00;        //帧参数长度
		TransportProtocol.Parameter2 = 0X0A;        //帧参数长度    
		TransportProtocol_Manager.Packed();			    //打包	
	
	  Usart_SendArray(USART2,AS32_TTL_window,3);
	  Usart_SendArray(USART2,TransportProtocol_Manager.Buf,10);
	
	  while(i)
		{
			delay_ms(500);
			if(i==1)  //第一次超时重发 第二次超时判断故障并退出
			{
				if(i2==1)
				{
					TransportProtocol.Function_Type1 = 0XFF;
					TransportProtocol.Function_Type2 = 0XFF;
					TransportProtocol_Manager.Packed();			    //打包	
	        Usart_SendArray(USART1,TransportProtocol_Manager.Buf,10);
//					printf("设备故障：窗户\r\n");
					i2 = 0;
					i = 4;
					num = 0;
					break;
				}
				i2++;
				i = 4;
				Usart_SendArray(USART2,AS32_TTL_window,3);
	      Usart_SendArray(USART2,TransportProtocol_Manager.Buf,10);
			}
			
			if(num >= 5)
		  {
			  Num_sum = rx_buf[6]+rx_buf[7];
			  if(num == Num_sum)  //数据位校验
			  {
				  res = TransportProtocol_Manager.Unpacked();//解包	
         	if((res == UPACKED_SUCCESS) && (rx_buf[2] ==  0X20))  //解包成功
				  {	
//						printf("一号窗户状态查询成功，返回一帧数据：");
				    Usart_SendArray(USART1,rx_buf,num);
//						for(i3=0;i3<num;i3++)
//            {
//							printf(" %X",rx_buf[i3]);
//						}	
//						printf(" \r\n");
						i2 = 0;
						num = 0;
						i = 4;
						break;
				  } 
          else  //解包失败的时候重新进行应答
					{
						i=2; //即将进行重发
					}		
					
			  }
				num = 0;
		  }
				
			i--;
			
		}
}


void window2_agreement(void)
{
    u8 AS32_TTL_window[] = {0x30,0x01,0x17};   //劳拉模块定点传输地址
		TransportProtocol.Device_Address1 = 0XFF;   //设备地址  
    TransportProtocol.Device_Address2 = 0X20;   //设备地址  窗户电机
	  TransportProtocol.Equipment_Number = 0X02;  //一号窗户
    TransportProtocol.Function_Type1 = 0XFF;    //帧功能    
	  TransportProtocol.Function_Type2 = 0X00;    //帧功能    查询窗帘状态
		TransportProtocol.Parameter1 = 0X00;        //帧参数长度
		TransportProtocol.Parameter2 = 0X0A;        //帧参数长度    
		TransportProtocol_Manager.Packed();			    //打包	
	
	  Usart_SendArray(USART2,AS32_TTL_window,3);
	  Usart_SendArray(USART2,TransportProtocol_Manager.Buf,10);
	
	  while(i)
		{
			delay_ms(500);
			if(i==1)  //第一次超时重发 第二次超时判断故障并退出
			{
				if(i2==1)
				{
					TransportProtocol.Function_Type1 = 0XFF;
					TransportProtocol.Function_Type2 = 0XFF;
					TransportProtocol_Manager.Packed();			    //打包	
	        Usart_SendArray(USART1,TransportProtocol_Manager.Buf,10);
//					printf("设备故障：二号窗户\r\n");
					i2 = 0;
					i = 4;
					num = 0;
					break;
				}
				i2++;
				i = 4;
				Usart_SendArray(USART2,AS32_TTL_window,3);
	      Usart_SendArray(USART2,TransportProtocol_Manager.Buf,10);
			}
			
			if(num >= 5)
		  {
			  Num_sum = rx_buf[6]+rx_buf[7];
			  if(num == Num_sum)  //数据位校验
			  {
				  res = TransportProtocol_Manager.Unpacked();//解包	
         	if((res == UPACKED_SUCCESS) && (rx_buf[2] ==  0X20))  //解包成功
				  {	
//						printf("二号窗户状态查询成功，返回一帧数据：");
				    Usart_SendArray(USART1,rx_buf,num);
//						for(i3=0;i3<num;i3++)
//            {
//							printf(" %X",rx_buf[i3]);
//						}	
//						printf(" \r\n");
						i2 = 0;
						num = 0;
						i = 4;
						break;
				  } 
          else  //解包失败的时候重新进行应答
					{
						i=2; //即将进行重发
					}		
					
			  }
				num = 0;
		  }
				
			i--;
			
		}
}

void experiment_agreement(void)
{
	  u8 AS32_TTL_experiment[] = {0x10,0x01,0x17};   //劳拉模块定点传输地址
		TransportProtocol.Device_Address1 = 0XFF;   //设备地址  
    TransportProtocol.Device_Address2 = 0X70;   //设备地址  实验台
	  TransportProtocol.Equipment_Number = 0X01;  //一号
    TransportProtocol.Function_Type1 = 0XFF;    //帧功能    
	  TransportProtocol.Function_Type2 = 0X00;    //帧功能    
		TransportProtocol.Parameter1 = 0X00;        //帧参数长度
		TransportProtocol.Parameter2 = 0X0A;        //帧参数长度    
		TransportProtocol_Manager.Packed();			    //打包	
	
		Usart_SendArray(USART2,AS32_TTL_experiment,3);
	  Usart_SendArray(USART2,TransportProtocol_Manager.Buf,10);
		
	  while(i)
		{
			delay_ms(500);
			if(i==1)  //第一次超时重发 第二次超时判断故障并退出
			{
				if(i2==1)
				{
					TransportProtocol.Function_Type1 = 0XFF;
					TransportProtocol.Function_Type2 = 0XFF;	
					TransportProtocol_Manager.Packed();			    //打包	
	        Usart_SendArray(USART1,TransportProtocol_Manager.Buf,10);					
//					printf("设备故障：实验台\r\n");
					i2 = 0;
					i = 4;
					num = 0;
					break;
				}
				i2++;
				i = 4;
				Usart_SendArray(USART2,AS32_TTL_experiment,3);
	      Usart_SendArray(USART2,TransportProtocol_Manager.Buf,10);
			}
			
			if(num >= 5)
		  {
			  Num_sum = rx_buf[6]+rx_buf[7];
			  if(num == Num_sum)  //数据位校验
			  {
				  res = TransportProtocol_Manager.Unpacked();//解包	
         	if((res == UPACKED_SUCCESS) && (rx_buf[2] ==  0X70))  //解包成功
				  {	
//						printf("实验台状态查询成功，返回一帧数据：");
				    Usart_SendArray(USART1,rx_buf,num);
//						for(i3=0;i3<num;i3++)
//            {
//							printf(" %X",rx_buf[i3]);
//						}	
//						printf(" \r\n");
						i2 = 0;
						num = 0;
						i = 4;
						break;
				  } 
          else  //解包失败的时候重新进行应答
					{
						i=2; //即将进行重发
					}		
					
			  }
				num = 0;
		  }
				
			i--;
			
		}
}

void door_agreement(void)
{
		TransportProtocol.Device_Address1 = 0XFF;   //设备地址  
    TransportProtocol.Device_Address2 = 0X40;   //设备地址  门锁
	  TransportProtocol.Equipment_Number = 0X00;  //一号
    TransportProtocol.Function_Type1 = 0XFF;    //帧功能    
	  TransportProtocol.Function_Type2 = 0X00;    //帧功能  
		TransportProtocol.Parameter1 = 0X00;        //帧参数长度
		TransportProtocol.Parameter2 = 0X12;        //帧参数长度   
		TransportProtocol2_Packed();			    //打包	
}


void response_OK(void)
{
	while(i)
	{
	    delay_ms(500);
			if(i==1)  //第一次超时重发 第二次超时判断故障并退出
			{
				if(i2==1)
				{
					//此处未接收到"OK"  对上位机不做应答
					
//					TransportProtocol.Function_Type1 = 0XFF;
//					TransportProtocol.Function_Type2 = 0XFF;
//					TransportProtocol_Manager.Packed();			    //打包	
////					printf("设备故障：配电柜\r\n");
//	        Usart_SendArray(USART1,TransportProtocol_Manager.Buf,10);
					
					i2 = 0;
					i = 4;
					num = 0;
					num1=0;
					break;
				}
				i2++;
				i = 4;
				
				if(rx1_buf[2]==0X10)//窗帘
				{
					Usart_SendArray(USART2,aa1,3);					
				}
				if(rx1_buf[2]==0X20)//窗户
				{
					Usart_SendArray(USART2,aa1,3);
				}
				if(rx1_buf[2]==0X40)//门锁
				{
					Usart_SendArray(USART2,aa3,3);
				}
				if(rx1_buf[2]==0X60)//配电柜
				{
					Usart_SendArray(USART2,aa2,3);
				}				
				Usart_SendArray(USART2,rx1_buf,num1);
			}
			
			if(num >= 5)
		  {
			  Num_sum = rx_buf[6]+rx_buf[7];
			  if(num == Num_sum)  //数据位校验
			  {
				  res = TransportProtocol_Manager.Unpacked();//解包	
         	if((res == UPACKED_SUCCESS) && (rx_buf[2] ==  0X60))  //解包成功
				  {							
//						printf("配电柜态查询成功，返回一帧数据：");
				    Usart_SendArray(USART1,rx_buf,num);		
//            for(i3=0;i3<num;i3++)
//            {
//							printf(" %X",rx_buf[i3]);
//						}						
//						printf("\r\n");
						num = 0;	
			      num1=0;						
						i2 = 0;
						i = 4;
						break;
				  } 
          else  //解包失败的时候重新进行应答
					{
					   i=2; //即将进行重发
					}		

			  }
		  }
				
			i--;
	}
}
/**
  * @brief  配置按键用到的I/O口
  * @param  无
  * @retval 无
  */
void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*开启按键端口的时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	//选择按键的引脚
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; 
	// 设置按键的引脚为浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//使用结构体初始化按键
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//选择按键的引脚
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; 
	//设置按键的引脚为浮空输入
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//使用结构体初始化按键
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
}

 /*
 * 函数名：Key_Scan
 * 描述  ：检测是否有按键按下
 * 输入  ：GPIOx：x 可以是 A，B，C，D或者 E
 *		     GPIO_Pin：待读取的端口位 	
 * 输出  ：KEY_OFF(没按下按键)、KEY_ON（按下按键）
 */
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{			
	/*检测是否有按键按下 */
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == 1 )  
	{	 
		/*等待按键释放 */
		while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == 1);   
		return 	1;	 
	}
	else
		return 0;
}









