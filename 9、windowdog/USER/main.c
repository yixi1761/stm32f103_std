#include "STM32F10X.h"
#include "GPIO.h"
#include "USART.h"
#include "Delay.h"
#include "stdio.h"
#include "wwdg.h"



int fputc(int ch,FILE *P)
{
	USART_SendData(USART1, (u8) ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET);
	return ch;
}


int main()
{	
	GPIOA->CRL=0X01;
	/*NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断分组
	LED_GPIO_INIT();
	USART_INIT();
	
	GPIO_ResetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);Delay_ms (1);	
	printf(" start~准备喂狗! \n");	

	wwdg_int();
	
	while(1)
	{		
		GPIO_SetBits(GPIOC,GPIO_Pin_0);  Delay_ms (10);	
		GPIO_ResetBits(GPIOC,GPIO_Pin_0);  Delay_ms (10);	
	}	*/
}


void WWDG_IRQHandler()
{
	WWDG_SetCounter(0x70);
	WWDG_ClearFlag();
	GPIO_ResetBits(GPIOC,GPIO_Pin_2|GPIO_Pin_3);	Delay_ms (1);	
	GPIO_SetBits(GPIOC,GPIO_Pin_2|GPIO_Pin_3);	
	printf ("喂狗成功！\n");
}
