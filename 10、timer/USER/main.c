#include "STM32F10X.h"
#include "GPIO.h"
#include "USART.h"
#include "Delay.h"
#include "stdio.h"
#include "tim.h"

int fputc(int ch,FILE *P)
{
	USART_SendData(USART1, (u8) ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET);
	return ch;
}

u16 i=10000;
int main()
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断分组
	LED_GPIO_INIT();
	USART_INIT();
	
	GPIO_ResetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);Delay_ms (1);	
	printf(" 开始！ \n");	
	tim3_init(4999,9999);
	
	
	while(1)
	{		
		GPIO_ResetBits(GPIOC,GPIO_Pin_1);  while(i--);
	}	
}


void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update)==SET)
	{
		//GPIO_ResetBits(GPIOC,GPIO_Pin_1); 
		GPIO_SetBits(GPIOC,GPIO_Pin_1);while(i--);
		printf ("溢出成功!\n");		
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);	
	}
	
}

