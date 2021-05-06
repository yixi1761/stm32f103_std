# include "led.h"
# include "delay.h"
# include "usart.h"
#include "timer.h"
# include "rtc.h"


int main()
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	led_init();
	usart_init();	printf ("\nSTART!\n");
	
	rtc_init();
	rtc_set(2018,2,3,19,24,55);
	while(1)
		{					
			
		}	
}
