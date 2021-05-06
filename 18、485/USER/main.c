# include <stdio.h>
# include "spi.h"
# include "usart.h"
# include "led.h"

int main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	led_cfg();
	usart_cfg();
	spi_cfg();
	printf("start!");
	int data=0;
	data=spi_readID();
	printf("%x\n",data);		
	printf("x\n");
}
