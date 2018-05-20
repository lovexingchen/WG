#include "./Agreement/Agreement.h"
#include "bsp_usart.h"
#include "./check/check.h"
#include "./query/query.h"

//定义一个协议管理器
TransportProtocol_Manager_Typedef TransportProtocol_Manager;

extern uint8_t rx_buf[];
extern uint16_t num;
u8 rx_buf2[10];
TYPE_CRC DataCRCS;

//解包

static TransportProtocol_Result TransportProtocol_Unpacked()
{	

//	TransportProtocol_Manager.TransportProtocol->Parameter1 = rx_buf[6];  //接收到的数据长度高字节
//	TransportProtocol_Manager.TransportProtocol->Parameter2 = rx_buf[7];  //接收到的数据长度低字节
	
	TransportProtocol_Manager.TransportProtocol->MODBUS1 = rx_buf[num-2]; //接收到的CRC校验 高位
	TransportProtocol_Manager.TransportProtocol->MODBUS2 = rx_buf[num-1]; //接收到的CRC校验 低位
		
	if(num > MAX_FRAME_LENGTH || num < MIN_FRAME_LENGTH)
	{
		
		return FRAME_FORMAT_ERR;  //大于最大小于最小都不行
					
	}
	
	DataCRCS = Checksum_CRC16(rx_buf,num-2); //计算CRC校验值
	
	if((DataCRCS.High != TransportProtocol_Manager.TransportProtocol->MODBUS1)||
		 (DataCRCS.Low != TransportProtocol_Manager.TransportProtocol->MODBUS2))
	{
		printf("校验值错误，计算的校验值为 %x , %x  \r\n",DataCRCS.High,DataCRCS.Low);
		printf("校验值错误，接收的校验值为 %x , %x  \r\n",rx_buf[num-2],rx_buf[num-1]);
		return CHECK_ERR;    //校验值错误
	}
	
//		//设备地址
//		TransportProtocol_Manager.TransportProtocol->Device_Address1 = rx_buf[1];
//		TransportProtocol_Manager.TransportProtocol->Device_Address2 = rx_buf[2];
//	  //设备编号
//	  TransportProtocol_Manager.TransportProtocol->Equipment_Number = rx_buf[3];
//		//帧功能
//		TransportProtocol_Manager.TransportProtocol->Function_Type1 = rx_buf[4];
//		TransportProtocol_Manager.TransportProtocol->Function_Type2 = rx_buf[5];
	
	return UPACKED_SUCCESS;  
}

//打包
static void TransportProtocol_Packed()
{
	//定义帧头
	TransportProtocol_Manager.Buf[0] = 0X7E;
	//设备地址
	TransportProtocol_Manager.Buf[1] = TransportProtocol_Manager.TransportProtocol->Device_Address1;  
	TransportProtocol_Manager.Buf[2] = TransportProtocol_Manager.TransportProtocol->Device_Address2; 
	//设备编号
	TransportProtocol_Manager.Buf[3] = TransportProtocol_Manager.TransportProtocol->Equipment_Number; 
	//帧功能
	TransportProtocol_Manager.Buf[4] = TransportProtocol_Manager.TransportProtocol->Function_Type1;
	TransportProtocol_Manager.Buf[5] = TransportProtocol_Manager.TransportProtocol->Function_Type2;    
	//帧长度
	TransportProtocol_Manager.Buf[6] = TransportProtocol_Manager.TransportProtocol->Parameter1;
	TransportProtocol_Manager.Buf[7] = TransportProtocol_Manager.TransportProtocol->Parameter2;
	
	DataCRCS = Checksum_CRC16(TransportProtocol_Manager.Buf,8);
	TransportProtocol_Manager.Buf[8] = DataCRCS.High;
	TransportProtocol_Manager.Buf[9] = DataCRCS.Low;

}

//打包
void TransportProtocol2_Packed(void)
{
	//定义帧头
	TransportProtocol_Manager.Buf[0] = 0X7E;
	//设备地址
	TransportProtocol_Manager.Buf[1] = TransportProtocol_Manager.TransportProtocol->Device_Address1;  
	TransportProtocol_Manager.Buf[2] = TransportProtocol_Manager.TransportProtocol->Device_Address2; 
	//设备编号
	TransportProtocol_Manager.Buf[3] = TransportProtocol_Manager.TransportProtocol->Equipment_Number; 
	//帧功能
	TransportProtocol_Manager.Buf[4] = TransportProtocol_Manager.TransportProtocol->Function_Type1;
	TransportProtocol_Manager.Buf[5] = TransportProtocol_Manager.TransportProtocol->Function_Type2;    
	//帧长度
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
	//协议包
	TransportProtocol_Manager.TransportProtocol = TransportProtocol;
	//传输协议缓存 
	TransportProtocol_Manager.Buf = rx_buf2;
	//打包函数
	TransportProtocol_Manager.Packed = TransportProtocol_Packed;
	//解包函数
	TransportProtocol_Manager.Unpacked = TransportProtocol_Unpacked;	
}










