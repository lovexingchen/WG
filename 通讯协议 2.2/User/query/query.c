#include "./query/query.h"
#include "./systick/systick.h"
#include "./check/check.h"
#include "bsp_usart.h"
#include "./Agreement/Agreement.h"

TransportProtocol_Typedef TransportProtocol;

TransportProtocol_Result res;	//������

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
	  u8 AS32_TTL_electricity[] = {0x20,0x01,0x17};//����ģ�鶨�㴫���ַ
		TransportProtocol.Device_Address1 = 0XFF;   //�豸��ַ  
    TransportProtocol.Device_Address2 = 0X60;   //�豸��ַ  ����
	  TransportProtocol.Equipment_Number = 0X01;  //���ߵ��ܲ���
    TransportProtocol.Function_Type1 = 0XFF;    //֡����    
	  TransportProtocol.Function_Type2 = 0X01;    //֡����      
		TransportProtocol.Parameter1 = 0X00;        //֡��������
		TransportProtocol.Parameter2 = 0X0A;        //֡��������    
		TransportProtocol_Manager.Packed();			    //���	
	
		Usart_SendArray(USART2,AS32_TTL_electricity,3);
	  Usart_SendArray(USART2,TransportProtocol_Manager.Buf,10);

		while(i)
		{
			delay_ms(500);
			if(i==1)  //��һ�γ�ʱ�ط� �ڶ��γ�ʱ�жϹ��ϲ��˳�
			{
				if(i2==1)
				{
					TransportProtocol.Function_Type1 = 0XFF;
					TransportProtocol.Function_Type2 = 0XFF;
					TransportProtocol_Manager.Packed();			    //���	
//					printf("�豸���ϣ�����\r\n");
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
			  if(num == Num_sum)  //����λУ��
			  {
				  res = TransportProtocol_Manager.Unpacked();//���	
         	if((res == UPACKED_SUCCESS) && (rx_buf[2] ==  0X60))  //����ɹ�
				  {							
//						printf("����̬��ѯ�ɹ�������һ֡���ݣ�");
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
          else  //���ʧ�ܵ�ʱ�����½���Ӧ��
					{
						i=2; //���������ط�
					}		

			  }
		  }
				
			i--;
			
		}
}


void curtain_agreement(void)
{
    u8 AS32_TTL_curtain[] = {0x30,0x01,0x17};   //����ģ�鶨�㴫���ַ
		TransportProtocol.Device_Address1 = 0XFF;   //�豸��ַ  
    TransportProtocol.Device_Address2 = 0X10;   //�豸��ַ  �������
	  TransportProtocol.Equipment_Number = 0X01;  //һ�Ŵ���
    TransportProtocol.Function_Type1 = 0XFF;    //֡����    
	  TransportProtocol.Function_Type2 = 0X00;    //֡����    ��ѯ����״̬
		TransportProtocol.Parameter1 = 0X00;        //֡��������
		TransportProtocol.Parameter2 = 0X0A;        //֡��������    
		TransportProtocol_Manager.Packed();			    //���	
	  Usart_SendArray(USART2,AS32_TTL_curtain,3);
	  Usart_SendArray(USART2,TransportProtocol_Manager.Buf,10);
	  while(i)
		{
			delay_ms(500);
			if(i==1)  //��һ�γ�ʱ�ط� �ڶ��γ�ʱ�жϹ��ϲ��˳�
			{
				if(i2==1)
				{
					TransportProtocol.Function_Type1 = 0XFF;
					TransportProtocol.Function_Type2 = 0XFF;
					TransportProtocol_Manager.Packed();			    //���	
	        Usart_SendArray(USART1,TransportProtocol_Manager.Buf,10);
//					printf("�豸���ϣ�����\r\n");
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
			  if(num == Num_sum)  //����λУ��
			  {
				  res = TransportProtocol_Manager.Unpacked();//���	
         	if((res == UPACKED_SUCCESS) && (rx_buf[2] ==  0X10))  //����ɹ�
				  {	
//						printf("һ�Ŵ���״̬��ѯ�ɹ�������һ֡���ݣ�");
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
          else  //���ʧ�ܵ�ʱ�����½���Ӧ��
					{
						i=2; //���������ط�
					}		
					
			  }
				num = 0;
		  }
				
			i--;
			
		}
}

void window_agreement(void)
{
    u8 AS32_TTL_window[] = {0x30,0x01,0x17};   //����ģ�鶨�㴫���ַ
		TransportProtocol.Device_Address1 = 0XFF;   //�豸��ַ  
    TransportProtocol.Device_Address2 = 0X20;   //�豸��ַ  �������
	  TransportProtocol.Equipment_Number = 0X01;  //һ�Ŵ���
    TransportProtocol.Function_Type1 = 0XFF;    //֡����    
	  TransportProtocol.Function_Type2 = 0X00;    //֡����    ��ѯ����״̬
		TransportProtocol.Parameter1 = 0X00;        //֡��������
		TransportProtocol.Parameter2 = 0X0A;        //֡��������    
		TransportProtocol_Manager.Packed();			    //���	
	
	  Usart_SendArray(USART2,AS32_TTL_window,3);
	  Usart_SendArray(USART2,TransportProtocol_Manager.Buf,10);
	
	  while(i)
		{
			delay_ms(500);
			if(i==1)  //��һ�γ�ʱ�ط� �ڶ��γ�ʱ�жϹ��ϲ��˳�
			{
				if(i2==1)
				{
					TransportProtocol.Function_Type1 = 0XFF;
					TransportProtocol.Function_Type2 = 0XFF;
					TransportProtocol_Manager.Packed();			    //���	
	        Usart_SendArray(USART1,TransportProtocol_Manager.Buf,10);
//					printf("�豸���ϣ�����\r\n");
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
			  if(num == Num_sum)  //����λУ��
			  {
				  res = TransportProtocol_Manager.Unpacked();//���	
         	if((res == UPACKED_SUCCESS) && (rx_buf[2] ==  0X20))  //����ɹ�
				  {	
//						printf("һ�Ŵ���״̬��ѯ�ɹ�������һ֡���ݣ�");
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
          else  //���ʧ�ܵ�ʱ�����½���Ӧ��
					{
						i=2; //���������ط�
					}		
					
			  }
				num = 0;
		  }
				
			i--;
			
		}
}


void window2_agreement(void)
{
    u8 AS32_TTL_window[] = {0x30,0x01,0x17};   //����ģ�鶨�㴫���ַ
		TransportProtocol.Device_Address1 = 0XFF;   //�豸��ַ  
    TransportProtocol.Device_Address2 = 0X20;   //�豸��ַ  �������
	  TransportProtocol.Equipment_Number = 0X02;  //һ�Ŵ���
    TransportProtocol.Function_Type1 = 0XFF;    //֡����    
	  TransportProtocol.Function_Type2 = 0X00;    //֡����    ��ѯ����״̬
		TransportProtocol.Parameter1 = 0X00;        //֡��������
		TransportProtocol.Parameter2 = 0X0A;        //֡��������    
		TransportProtocol_Manager.Packed();			    //���	
	
	  Usart_SendArray(USART2,AS32_TTL_window,3);
	  Usart_SendArray(USART2,TransportProtocol_Manager.Buf,10);
	
	  while(i)
		{
			delay_ms(500);
			if(i==1)  //��һ�γ�ʱ�ط� �ڶ��γ�ʱ�жϹ��ϲ��˳�
			{
				if(i2==1)
				{
					TransportProtocol.Function_Type1 = 0XFF;
					TransportProtocol.Function_Type2 = 0XFF;
					TransportProtocol_Manager.Packed();			    //���	
	        Usart_SendArray(USART1,TransportProtocol_Manager.Buf,10);
//					printf("�豸���ϣ����Ŵ���\r\n");
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
			  if(num == Num_sum)  //����λУ��
			  {
				  res = TransportProtocol_Manager.Unpacked();//���	
         	if((res == UPACKED_SUCCESS) && (rx_buf[2] ==  0X20))  //����ɹ�
				  {	
//						printf("���Ŵ���״̬��ѯ�ɹ�������һ֡���ݣ�");
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
          else  //���ʧ�ܵ�ʱ�����½���Ӧ��
					{
						i=2; //���������ط�
					}		
					
			  }
				num = 0;
		  }
				
			i--;
			
		}
}

void experiment_agreement(void)
{
	  u8 AS32_TTL_experiment[] = {0x10,0x01,0x17};   //����ģ�鶨�㴫���ַ
		TransportProtocol.Device_Address1 = 0XFF;   //�豸��ַ  
    TransportProtocol.Device_Address2 = 0X70;   //�豸��ַ  ʵ��̨
	  TransportProtocol.Equipment_Number = 0X01;  //һ��
    TransportProtocol.Function_Type1 = 0XFF;    //֡����    
	  TransportProtocol.Function_Type2 = 0X00;    //֡����    
		TransportProtocol.Parameter1 = 0X00;        //֡��������
		TransportProtocol.Parameter2 = 0X0A;        //֡��������    
		TransportProtocol_Manager.Packed();			    //���	
	
		Usart_SendArray(USART2,AS32_TTL_experiment,3);
	  Usart_SendArray(USART2,TransportProtocol_Manager.Buf,10);
		
	  while(i)
		{
			delay_ms(500);
			if(i==1)  //��һ�γ�ʱ�ط� �ڶ��γ�ʱ�жϹ��ϲ��˳�
			{
				if(i2==1)
				{
					TransportProtocol.Function_Type1 = 0XFF;
					TransportProtocol.Function_Type2 = 0XFF;	
					TransportProtocol_Manager.Packed();			    //���	
	        Usart_SendArray(USART1,TransportProtocol_Manager.Buf,10);					
//					printf("�豸���ϣ�ʵ��̨\r\n");
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
			  if(num == Num_sum)  //����λУ��
			  {
				  res = TransportProtocol_Manager.Unpacked();//���	
         	if((res == UPACKED_SUCCESS) && (rx_buf[2] ==  0X70))  //����ɹ�
				  {	
//						printf("ʵ��̨״̬��ѯ�ɹ�������һ֡���ݣ�");
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
          else  //���ʧ�ܵ�ʱ�����½���Ӧ��
					{
						i=2; //���������ط�
					}		
					
			  }
				num = 0;
		  }
				
			i--;
			
		}
}

void door_agreement(void)
{
		TransportProtocol.Device_Address1 = 0XFF;   //�豸��ַ  
    TransportProtocol.Device_Address2 = 0X40;   //�豸��ַ  ����
	  TransportProtocol.Equipment_Number = 0X00;  //һ��
    TransportProtocol.Function_Type1 = 0XFF;    //֡����    
	  TransportProtocol.Function_Type2 = 0X00;    //֡����  
		TransportProtocol.Parameter1 = 0X00;        //֡��������
		TransportProtocol.Parameter2 = 0X12;        //֡��������   
		TransportProtocol2_Packed();			    //���	
}


void response_OK(void)
{
	while(i)
	{
	    delay_ms(500);
			if(i==1)  //��һ�γ�ʱ�ط� �ڶ��γ�ʱ�жϹ��ϲ��˳�
			{
				if(i2==1)
				{
					//�˴�δ���յ�"OK"  ����λ������Ӧ��
					
//					TransportProtocol.Function_Type1 = 0XFF;
//					TransportProtocol.Function_Type2 = 0XFF;
//					TransportProtocol_Manager.Packed();			    //���	
////					printf("�豸���ϣ�����\r\n");
//	        Usart_SendArray(USART1,TransportProtocol_Manager.Buf,10);
					
					i2 = 0;
					i = 4;
					num = 0;
					num1=0;
					break;
				}
				i2++;
				i = 4;
				
				if(rx1_buf[2]==0X10)//����
				{
					Usart_SendArray(USART2,aa1,3);					
				}
				if(rx1_buf[2]==0X20)//����
				{
					Usart_SendArray(USART2,aa1,3);
				}
				if(rx1_buf[2]==0X40)//����
				{
					Usart_SendArray(USART2,aa3,3);
				}
				if(rx1_buf[2]==0X60)//����
				{
					Usart_SendArray(USART2,aa2,3);
				}				
				Usart_SendArray(USART2,rx1_buf,num1);
			}
			
			if(num >= 5)
		  {
			  Num_sum = rx_buf[6]+rx_buf[7];
			  if(num == Num_sum)  //����λУ��
			  {
				  res = TransportProtocol_Manager.Unpacked();//���	
         	if((res == UPACKED_SUCCESS) && (rx_buf[2] ==  0X60))  //����ɹ�
				  {							
//						printf("����̬��ѯ�ɹ�������һ֡���ݣ�");
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
          else  //���ʧ�ܵ�ʱ�����½���Ӧ��
					{
					   i=2; //���������ط�
					}		

			  }
		  }
				
			i--;
	}
}
/**
  * @brief  ���ð����õ���I/O��
  * @param  ��
  * @retval ��
  */
void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*���������˿ڵ�ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	//ѡ�񰴼�������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; 
	// ���ð���������Ϊ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//ʹ�ýṹ���ʼ������
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//ѡ�񰴼�������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; 
	//���ð���������Ϊ��������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//ʹ�ýṹ���ʼ������
	GPIO_Init(GPIOC, &GPIO_InitStructure);	
}

 /*
 * ��������Key_Scan
 * ����  ������Ƿ��а�������
 * ����  ��GPIOx��x ������ A��B��C��D���� E
 *		     GPIO_Pin������ȡ�Ķ˿�λ 	
 * ���  ��KEY_OFF(û���°���)��KEY_ON�����°�����
 */
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{			
	/*����Ƿ��а������� */
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == 1 )  
	{	 
		/*�ȴ������ͷ� */
		while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == 1);   
		return 	1;	 
	}
	else
		return 0;
}









