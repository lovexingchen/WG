#include "./Agreement/Agreement.h"
#include "bsp_usart.h"
#include "./check/check.h"
#include "./query/query.h"

//����һ��Э�������
TransportProtocol_Manager_Typedef TransportProtocol_Manager;

extern uint8_t rx_buf[];
extern uint16_t num;
u8 rx_buf2[10];
TYPE_CRC DataCRCS;

//���

static TransportProtocol_Result TransportProtocol_Unpacked()
{	

//	TransportProtocol_Manager.TransportProtocol->Parameter1 = rx_buf[6];  //���յ������ݳ��ȸ��ֽ�
//	TransportProtocol_Manager.TransportProtocol->Parameter2 = rx_buf[7];  //���յ������ݳ��ȵ��ֽ�
	
	TransportProtocol_Manager.TransportProtocol->MODBUS1 = rx_buf[num-2]; //���յ���CRCУ�� ��λ
	TransportProtocol_Manager.TransportProtocol->MODBUS2 = rx_buf[num-1]; //���յ���CRCУ�� ��λ
		
	if(num > MAX_FRAME_LENGTH || num < MIN_FRAME_LENGTH)
	{
		
		return FRAME_FORMAT_ERR;  //�������С����С������
					
	}
	
	DataCRCS = Checksum_CRC16(rx_buf,num-2); //����CRCУ��ֵ
	
	if((DataCRCS.High != TransportProtocol_Manager.TransportProtocol->MODBUS1)||
		 (DataCRCS.Low != TransportProtocol_Manager.TransportProtocol->MODBUS2))
	{
		printf("У��ֵ���󣬼����У��ֵΪ %x , %x  \r\n",DataCRCS.High,DataCRCS.Low);
		printf("У��ֵ���󣬽��յ�У��ֵΪ %x , %x  \r\n",rx_buf[num-2],rx_buf[num-1]);
		return CHECK_ERR;    //У��ֵ����
	}
	
//		//�豸��ַ
//		TransportProtocol_Manager.TransportProtocol->Device_Address1 = rx_buf[1];
//		TransportProtocol_Manager.TransportProtocol->Device_Address2 = rx_buf[2];
//	  //�豸���
//	  TransportProtocol_Manager.TransportProtocol->Equipment_Number = rx_buf[3];
//		//֡����
//		TransportProtocol_Manager.TransportProtocol->Function_Type1 = rx_buf[4];
//		TransportProtocol_Manager.TransportProtocol->Function_Type2 = rx_buf[5];
	
	return UPACKED_SUCCESS;  
}

//���
static void TransportProtocol_Packed()
{
	//����֡ͷ
	TransportProtocol_Manager.Buf[0] = 0X7E;
	//�豸��ַ
	TransportProtocol_Manager.Buf[1] = TransportProtocol_Manager.TransportProtocol->Device_Address1;  
	TransportProtocol_Manager.Buf[2] = TransportProtocol_Manager.TransportProtocol->Device_Address2; 
	//�豸���
	TransportProtocol_Manager.Buf[3] = TransportProtocol_Manager.TransportProtocol->Equipment_Number; 
	//֡����
	TransportProtocol_Manager.Buf[4] = TransportProtocol_Manager.TransportProtocol->Function_Type1;
	TransportProtocol_Manager.Buf[5] = TransportProtocol_Manager.TransportProtocol->Function_Type2;    
	//֡����
	TransportProtocol_Manager.Buf[6] = TransportProtocol_Manager.TransportProtocol->Parameter1;
	TransportProtocol_Manager.Buf[7] = TransportProtocol_Manager.TransportProtocol->Parameter2;
	
	DataCRCS = Checksum_CRC16(TransportProtocol_Manager.Buf,8);
	TransportProtocol_Manager.Buf[8] = DataCRCS.High;
	TransportProtocol_Manager.Buf[9] = DataCRCS.Low;

}

//���
void TransportProtocol2_Packed(void)
{
	//����֡ͷ
	TransportProtocol_Manager.Buf[0] = 0X7E;
	//�豸��ַ
	TransportProtocol_Manager.Buf[1] = TransportProtocol_Manager.TransportProtocol->Device_Address1;  
	TransportProtocol_Manager.Buf[2] = TransportProtocol_Manager.TransportProtocol->Device_Address2; 
	//�豸���
	TransportProtocol_Manager.Buf[3] = TransportProtocol_Manager.TransportProtocol->Equipment_Number; 
	//֡����
	TransportProtocol_Manager.Buf[4] = TransportProtocol_Manager.TransportProtocol->Function_Type1;
	TransportProtocol_Manager.Buf[5] = TransportProtocol_Manager.TransportProtocol->Function_Type2;    
	//֡����
	TransportProtocol_Manager.Buf[6] = TransportProtocol_Manager.TransportProtocol->Parameter1;
	TransportProtocol_Manager.Buf[7] = TransportProtocol_Manager.TransportProtocol->Parameter2;
	
	TransportProtocol_Manager.Buf[8] = 0x00;
	TransportProtocol_Manager.Buf[9] = 0x00;
	TransportProtocol_Manager.Buf[10] = 0x00;
	TransportProtocol_Manager.Buf[11] = 0x00;
	TransportProtocol_Manager.Buf[12] = 0x00;
	TransportProtocol_Manager.Buf[13] = 0x00;
	TransportProtocol_Manager.Buf[14] = 0x00;
	TransportProtocol_Manager.Buf[15] = 0x00;
	
	DataCRCS = Checksum_CRC16(TransportProtocol_Manager.Buf,16);
	TransportProtocol_Manager.Buf[16] = DataCRCS.High;
	TransportProtocol_Manager.Buf[17] = DataCRCS.Low;

}


void  TransportProtocol_Init(TransportProtocol_Typedef *TransportProtocol)
{	
	//Э���
	TransportProtocol_Manager.TransportProtocol = TransportProtocol;
	//����Э�黺�� 
	TransportProtocol_Manager.Buf = rx_buf2;
	//�������
	TransportProtocol_Manager.Packed = TransportProtocol_Packed;
	//�������
	TransportProtocol_Manager.Unpacked = TransportProtocol_Unpacked;	
}










