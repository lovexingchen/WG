#ifndef  __AGREEMENT_H
#define  __AGREEMENT_H
#include "stm32f10x.h"


//����֡����
typedef struct
{
	//���֡����
	#define MAX_FRAME_LENGTH (300)
	//��С֡����
	#define MIN_FRAME_LENGTH  10	
	//�豸��ַ
	u8 Device_Address1; //���ֽ�
	u8 Device_Address2; //���ֽ�
	//�豸���
	u8 Equipment_Number;
	//֡����
	u8 Function_Type1;  //���ֽ�
	u8 Function_Type2;  //���ֽ�
	//֡��������
	u8 Parameter1;     //���ֽ�
	u8 Parameter2;     //���ֽ�
	//����
	u8 *Data;
  //CRCУ��
	u8 MODBUS1;
	u8 MODBUS2;

}TransportProtocol_Typedef;

//������
typedef enum   //ö������
{
	//֡��ʽ����
	FRAME_FORMAT_ERR = 1,		
	//У��ֵ��ʽ����
	CHECK_FORMAR_ERR = 2,
	//У��ֵ����
	CHECK_ERR = 3,
	//����ɹ�
	UPACKED_SUCCESS = 4

}TransportProtocol_Result;


//Э�������
typedef struct
{	
	//����֡
	TransportProtocol_Typedef * TransportProtocol;
	//����֡����
	u8 * Buf;
	//�������
	TransportProtocol_Result (*Unpacked)(void);
	//�������
	void (*Packed)(void);

}TransportProtocol_Manager_Typedef;



//�ⲿ����Э�������
extern TransportProtocol_Manager_Typedef TransportProtocol_Manager;
//��ʼ������Э��
void  TransportProtocol_Init(TransportProtocol_Typedef *TransportProtocol);

void TransportProtocol2_Packed(void);


#endif


