# include "can.h"

/*  declare internal reference Function */

void can_cfg()
{		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);
	//CANX_TX
	GPIO_InitTypeDef GPIO_InitStructure;	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA,&GPIO_InitStructure);	
	//CAN_RX
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA,&GPIO_InitStructure);	
	
	CAN_InitTypeDef CAN_InitStructure;
	CAN_InitStructure.CAN_Prescaler=5;
	CAN_InitStructure.CAN_Mode=CAN_Mode_Normal;
	CAN_InitStructure.CAN_SJW=CAN_SJW_1tq;
	CAN_InitStructure.CAN_BS1=CAN_BS1_8tq;
	CAN_InitStructure.CAN_BS2=CAN_BS1_7tq;
	CAN_InitStructure.CAN_ABOM=DISABLE;
	CAN_InitStructure.CAN_AWUM=	DISABLE;
	CAN_InitStructure.CAN_NART=	ENABLE;
	CAN_InitStructure.CAN_RFLM=	DISABLE;
	CAN_InitStructure.CAN_TTCM=DISABLE;
	CAN_InitStructure.CAN_TXFP=DISABLE;
	CAN_Init(CAN1,&CAN_InitStructure);
	
	CAN_FilterInitTypeDef CAN_FilterInitStruct;	
	CAN_FilterInitStruct.CAN_FilterNumber=0;
	CAN_FilterInitStruct.CAN_FilterFIFOAssignment=CAN_FilterFIFO0;
	CAN_FilterInitStruct.CAN_FilterMode=CAN_FilterMode_IdMask;
	CAN_FilterInitStruct.CAN_FilterScale=CAN_FilterScale_32bit;
	CAN_FilterInitStruct.CAN_FilterIdHigh=0x0000;
	CAN_FilterInitStruct.CAN_FilterIdLow=0x0000;
	CAN_FilterInitStruct.CAN_FilterMaskIdHigh=0x0000;
	CAN_FilterInitStruct.CAN_FilterMaskIdLow=0x0000;
	CAN_FilterInitStruct.CAN_FilterActivation=ENABLE;	
	CAN_FilterInit(&CAN_FilterInitStruct);	
	
	CAN_ITConfig(CAN1,CAN_IT_FMP0,DISABLE);
}
    
u8 can_send_msg(u32 ID,u8* msg,u8 length)
{
	u8 i,transmit_mailbox;
	u16 j;
	CanTxMsg TxMessage;
	TxMessage.RTR=CAN_RTR_Data;
	TxMessage.IDE=CAN_Id_Standard;
	TxMessage.StdId=ID;
	TxMessage.ExtId=ID;	
	TxMessage.DLC=length;
	for(i=0;i<length;i++)
	{		
		TxMessage.Data[i]=msg[i];
		transmit_mailbox=CAN_Transmit(CAN1,&TxMessage);
		j=0;
		while(CAN_TransmitStatus(CAN1,transmit_mailbox)!=CAN_TxStatus_Ok)
			{
				j++;
				if(j>0xfff)
					return 1;
			}
		return 0;
	}
	return 0;
}

//CAN'T return RxMessage.Data£¿£¿£¿£¿£¿
u8 can_receive_msg(u8* buf)
{
	u8 i;
	CanRxMsg RxMessage;	
	if(CAN_MessagePending(CAN1,CAN_FIFO0)==0)
		return 0;
	CAN_Receive(CAN1,CAN_FIFO0,&RxMessage);
	for(i=0;i<8;i++)
		buf[i]=RxMessage.Data[i];
	return RxMessage.DLC;
}
                                        

