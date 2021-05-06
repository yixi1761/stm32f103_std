# include "led.h"
# include "delay.h"
# include "usart.h"

int main()
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	led_init();
	usart_init();
	printf ("\nKAI\n");
	
	while(1)
		{
			LED7=~LED7;
			delay_simple(500000); 
		}	
}
