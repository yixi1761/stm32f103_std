
#include "24c02.H"
#include "IIC.h"

void Write_Byte(u8 addr,u8 data)
{	
	IIC_START();	
	IIC_SendByte(0xa0);
	IIC_WAIT_ACK();	
	IIC_SendByte(addr);IIC_WAIT_ACK();	
	IIC_SendByte(data);IIC_WAIT_ACK();
	IIC_STOP();	
}

u8 Read_Byte(u8 addr)
{
	char data;
	IIC_START();
	IIC_SendByte(0xA0);printf(" 2!\n");
	IIC_WAIT_ACK();	printf(" 3!\n");
	IIC_SendByte(addr);printf(" 4!\n");
	IIC_WAIT_ACK();printf(" 5!\n");
	IIC_START();printf(" 6!\n");
	IIC_SendByte(0xA1);printf(" 7!\n");
	IIC_WAIT_ACK();printf(" 8!\n");
  data = IIC_ReceiveByte();printf(" 9!\n");
	IIC_ACK();printf(" 10!\n");
	IIC_STOP();	printf(" 11!\n");
	return data;
	
}

//void Write_nByte(u8 addr,u32 data,u8 n)
//{
//	for(;n>-1;n--)
//	{
//		Write_Byte(addr,data>>8*(n-1));
//	}
//}

//u32 Read_nByte(u8 addr,u8 n)
//{
//	data=0;
//	for(;n--;n>-1)
//	{
//		data<<=8;
//		data|=Read_Byte(u8 addr);
//	}
//	return data;
//}
