#include "STM32F10X.h"
#include "led.h"
#include "Delay.h"

void Delay(u32 i)
{
    while(i--);
}

int main(void)
{
	led_init();
	while(1)
	{
		
		GPIO_SetBits(GPIOC,GPIO_Pin_0);//按照原理图，led上拉。此处熄灭
		GPIO_SetBits(GPIOC,GPIO_Pin_1);
		Delay_s(1);		
		GPIO_ResetBits(GPIOC,GPIO_Pin_0);
		GPIO_ResetBits(GPIOC,GPIO_Pin_1);		
		Delay_s(3);
	
	}
}
