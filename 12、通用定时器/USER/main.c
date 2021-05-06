# include "led.h"
# include "delay.h"
# include "usart.h"
#include "timer.h"


int main()
{
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	led_init();
	usart_init();
	printf ("\nKAI\n");
	//timer3_init();printf ("KA\n");	
  timer3_delay();
	
	while(1)
		{
//		GPIO_ResetBits(GPIOC,GPIO_Pin_3);	delay_simple(500000);
//		GPIO_SetBits(GPIOC,GPIO_Pin_3);delay_simple(500000);
//		GPIO_ResetBits(GPIOC,GPIO_Pin_2);delay_simple(500000);
//		GPIO_SetBits(GPIOC,GPIO_Pin_2);delay_simple(500000);
//		printf ("%d\n",a++);
		}
	
}
