#include "stm32f10x.h"
#include "stm32f10x_usart.h"
#include "usart.h"

void myusart_init(void)
{
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	USART_InitStructure.USART_BaudRate=115200;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;		
	USART_Init(USART1,&USART_InitStructure);	
	USART_Cmd(USART1,ENABLE);//����1ʹ��
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//����1�ж�����
	
	
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;//��stm32f10x.h����
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�������Ϊ2�Ļ�����0~3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;	
	NVIC_Init(&NVIC_InitStructure);//��ʼ���ж�	
}

