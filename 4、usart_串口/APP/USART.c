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
	USART_Cmd(USART1,ENABLE);//串口1使能
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//串口1中断配置
	
	
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;//在stm32f10x.h里面
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级，分组为2的话就是0~3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;	
	NVIC_Init(&NVIC_InitStructure);//初始化中断	
}

