#include "STM32F10X.h"
#include "Delay.h"
#include "GPIO.h"
#include "EXTI.h"

int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断分组
	
	GPIO_INIT();	
	EXTI_INIT();	
	while(1)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_0);Delay_ms(500);
		GPIO_ResetBits(GPIOC,GPIO_Pin_0);Delay_ms(500);
	}
}

/*~~~~~~~~~~~~~~~~~~~~~~~以下为中断入口函数~~~~~~~~~~~~~~~~~~~~~~*/
void EXTI2_IRQHandler()
{
	u8 i=3;
	Delay_s(1);
	while(i--)
	{		
		GPIO_ResetBits(GPIOC,GPIO_Pin_1);Delay_ms(500);
		GPIO_SetBits(GPIOC,GPIO_Pin_1);Delay_ms(500);
	}
 
	EXTI_ClearITPendingBit(EXTI_Line2);	
}
void EXTI3_IRQHandler()
{
	u8 i=3;
	Delay_s(1);
	while(i--)
	{		
		GPIO_ResetBits(GPIOC,GPIO_Pin_2);Delay_ms(500);
		GPIO_SetBits(GPIOC,GPIO_Pin_2);Delay_ms(500);
	}
	EXTI_ClearITPendingBit(EXTI_Line3);
}	
               
void EXTI4_IRQHandler()
{
	u8 i=3;
	Delay_s(1);
	while(i--)
	{		
		GPIO_ResetBits(GPIOC,GPIO_Pin_3);Delay_ms(500);
		GPIO_SetBits(GPIOC,GPIO_Pin_3);Delay_ms(500);
	}
	EXTI_ClearITPendingBit(EXTI_Line4);
}
