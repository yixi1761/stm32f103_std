#include "EXTI.h"

void EXTI_INIT(void)
{
	//三个GPIO按键中断
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;		
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line2|EXTI_Line3|EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;		
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);	
		
	//设置中断向量表，公用的部分写一遍，不能用与符号设置成同一优先级，所以分别初始化
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级，分组为2的话就是0~3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;	
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI2_IRQn;//在stm32f10x.h里面，外部中断放到NVIC里面
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;	//响应优先级	
	NVIC_Init(&NVIC_InitStructure);//初始化中断	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);	
	
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;	//响应优先级
	NVIC_Init(&NVIC_InitStructure);	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);	
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;	//响应优先级	
	NVIC_Init(&NVIC_InitStructure);	
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);		
	
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;	
	NVIC_Init(&NVIC_InitStructure);
	
	/*IO与中断线的映射，挂载到中断线上,需要在中断向量初始化后加上,也可以先挂到外部中断线上，
	再挂到NVIC向量表,	但是必须一一对应，用与符号是没法一一对应的*/	
}


/*~~~~~~~~~~~~~~~~~~~~~~~以下为中断入口函数~~~~~~~~~~~~~~~~~~~~~~*/
void EXTI2_IRQHandler()
{
	u8 i=2;	
	while(i--)
	{		
		GPIO_ResetBits(GPIOC,GPIO_Pin_1);Delay_ms(500);
		GPIO_SetBits(GPIOC,GPIO_Pin_1);Delay_ms(500);
	} 
	printf ("this is irq2,\n");
	EXTI_ClearITPendingBit(EXTI_Line2);	
}

void EXTI3_IRQHandler()
{
	u8 i=2;	
	while(i--)
	{		
		GPIO_ResetBits(GPIOC,GPIO_Pin_2);Delay_ms(500);
		GPIO_SetBits(GPIOC,GPIO_Pin_2);Delay_ms(500);
	}
	printf ("这是下键\n");
	EXTI_ClearITPendingBit(EXTI_Line3);
}	
               
void EXTI4_IRQHandler()
{
	u8 i=2;	
	while(i--)
	{		
		GPIO_ResetBits(GPIOC,GPIO_Pin_3);Delay_ms(500);
		GPIO_SetBits(GPIOC,GPIO_Pin_3);Delay_ms(500);
	}
	printf ("这是右键\n");
	EXTI_ClearITPendingBit(EXTI_Line4);
}
/*~~~~~~~~~~~~~~~~~~~~~~~以下为USART1中断入口函数~~~~~~~~~~~~~~~~~~~~~~*/
void USART1_IRQHandler()
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE))
	{
		u8 rec_data;
		rec_data=USART_ReceiveData(USART1);
		USART_SendData(USART1,rec_data);
	}
}