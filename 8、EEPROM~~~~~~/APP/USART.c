#include "USART.H"


void USART_INIT()
{
	USART_InitTypeDef USART_InitStructure;
	USART_GPIO_INIT();
	
	
	USART_InitStructure.USART_BaudRate=115200;
	USART_InitStructure.USART_Mode= USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_Parity= USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl= USART_HardwareFlowControl_None;  
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_Init(USART1,&USART_InitStructure);
	
	USART_Cmd(USART1, ENABLE);
	USART_ITConfig(USART1, USART_IT_RXNE,  ENABLE);

}

