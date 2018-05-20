#ifndef  __AGREEMENT_H
#define  __AGREEMENT_H
#include "stm32f10x.h"


//传输帧对象
typedef struct
{
	//最大帧长度
	#define MAX_FRAME_LENGTH (300)
	//最小帧长度
	#define MIN_FRAME_LENGTH  10	
	//设备地址
	u8 Device_Address1; //高字节
	u8 Device_Address2; //低字节
	//设备编号
	u8 Equipment_Number;
	//帧功能
	u8 Function_Type1;  //高字节
	u8 Function_Type2;  //低字节
	//帧参数长度
	u8 Parameter1;     //高字节
	u8 Parameter2;     //低字节
	//数据
	u8 *Data;
  //CRC校验
	u8 MODBUS1;
	u8 MODBUS2;

}TransportProtocol_Typedef;

//传输结果
typedef enum   //枚举类型
{
	//帧格式错误
	FRAME_FORMAT_ERR = 1,		
	//校验值格式错误
	CHECK_FORMAR_ERR = 2,
	//校验值错误
	CHECK_ERR = 3,
	//解包成功
	UPACKED_SUCCESS = 4

}TransportProtocol_Result;


//协议管理器
typedef struct
{	
	//传输帧
	TransportProtocol_Typedef * TransportProtocol;
	//传输帧缓存
	u8 * Buf;
	//解包函数
	TransportProtocol_Result (*Unpacked)(void);
	//打包函数
	void (*Packed)(void);

}TransportProtocol_Manager_Typedef;



//外部声明协议管理器
extern TransportProtocol_Manager_Typedef TransportProtocol_Manager;
//初始化传输协议
void  TransportProtocol_Init(TransportProtocol_Typedef *TransportProtocol);

void TransportProtocol2_Packed(void);


#endif


