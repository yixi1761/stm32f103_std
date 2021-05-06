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
			LED8=~LED8;
			delay_simple(9000000);
			//printf ("\nJUMP!\n");
		}
	
}
