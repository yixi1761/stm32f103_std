#include "STM32F10X.h"
#include "GPIO.h"

void Delay(u32 sec)
{
	while(sec--);
}
int main()
{
	led_init();
	while(1)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_0);
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		Delay(100000);
		GPIO_ResetBits(GPIOC,GPIO_Pin_0);
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);
		Delay(100000);
	}
}
