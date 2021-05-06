#include "STM32F10X.h"
#include "GPIO.h"
#include "usart.h"
#include "Delay.h"
#include "stm32f10x_usart.h"

int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//ÖÐ¶Ï·Ö×é
	mygpio_init();
	myusart_init();
	GPIO_SetBits(GPIOC,GPIO_Pin_0);
	
	while(1)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_1);Delay_s(1);
		GPIO_ResetBits(GPIOC,GPIO_Pin_1);Delay_s(1);
	}
}

void USART1_IRQHandler()
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE))
	{
		u8 rec_data;u8 i=2;
		rec_data=USART_ReceiveData(USART1);
		USART_SendData(USART1,rec_data);
//		while(i--)
//		{					
//			GPIO_ResetBits(GPIOC,GPIO_Pin_0);Delay_ms(500);
//			GPIO_SetBits(GPIOC,GPIO_Pin_0);Delay_ms(500);
//		}		
	}
}
