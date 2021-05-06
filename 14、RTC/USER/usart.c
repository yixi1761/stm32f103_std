#include "usart.h"
#include "stdio.h"

//need to choose Target->Use MicroLIB
int fputc(int ch,FILE *P)
{
	USART_SendData(USART1, (u8) ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET);
	return ch;
}

void usart_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;	
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//TX
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//RX
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;	
	GPIO_Init(GPIOA,&GPIO_InitStructure);	
	
	USART_InitStructure.USART_BaudRate=115200;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_Mode=USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;		
	USART_Init(USART1,&USART_InitStructure);	
	USART_Cmd(USART1,ENABLE);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//IT for receive
		
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;//the IT functions is in stm32f10x.h??
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//qiang zan you xian ji:0~3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;	
	NVIC_Init(&NVIC_InitStructure);	
}
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void USART1_IRQHandler()
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE))
	{
		u8 rec_data;
		rec_data=USART_ReceiveData(USART1);
		delay_simple(500000);
		USART_SendData(USART1,rec_data);
			switch(rec_data)
		{
			//case 1:GPIO_ResetBits(GPIOC,GPIO_Pin_1);
			//case 2:GPIO_ResetBits(GPIOC,GPIO_Pin_2);
			//case 3:GPIO_ResetBits(GPIOC,GPIO_Pin_3);
			//case 4:GPIO_ResetBits(GPIOC,GPIO_Pin_4);
			//case 5:GPIO_ResetBits(GPIOC,GPIO_Pin_5);
			//case 6:GPIO_ResetBits(GPIOC,GPIO_Pin_6);
			case 50:GPIO_ResetBits(GPIOC,GPIO_Pin_7);
			default:{GPIO_ResetBits(GPIOC,GPIO_Pin_0);delay_simple(500000);
							GPIO_SetBits(GPIOC,GPIO_Pin_0);delay_simple(500000);}
	}
	}
	
}


