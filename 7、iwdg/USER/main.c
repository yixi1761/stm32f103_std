#include "STM32F10X.h"
#include "GPIO.h"
#include "EXTI.h"
#include "USART.h"
#include "Delay.h"
#include "stdio.h"
#include "misc.h"
#include "IWDG.h"

int fputc(int ch,FILE *P)
{
	USART_SendData(USART1, (u8) ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET);
	return ch;
}


int main()
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断分组
	
	GPIO_INIT();	
	EXTI_INIT();	
	USART_INIT();	
	IWDG_Init(IWDG_Prescaler_64,625);
		GPIO_SetBits(GPIOC,GPIO_Pin_0);  Delay_ms (100);
		GPIO_ResetBits(GPIOC,GPIO_Pin_0);
	
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
