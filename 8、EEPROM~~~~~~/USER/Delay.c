#include "Delay.h"

void Delay_us(u32 n_us)
{		
	//默认使用内核时钟源FCLK（HCLK 72MHz）,手工修改为外部时钟9M，每个tick周期1/900 000，1us是9个周期。
	SysTick_Config(n_us*9);	
	/*判断24位load寄存器超出；重载；中断优先级设置；计数器清零；设置时钟源；开启中断；开始计数*/
	while((SysTick->CTRL&1)&&!(SysTick->CTRL&(1<<16)));	
	//查询检测control寄存器的最高位flag，数到0会置位。前面&1是判断计数器有没有被意外关闭			
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;//关闭计数器
}

void Delay_ms(u32 n_ms)	
{			
	SysTick_Config(n_ms*9000);//最大load值16x1024x1024			
	while (!((SysTick->CTRL>>16)&1));		
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;//关闭计数器
}

void Delay_s(u32 n_s)
{
	while(n_s--)
	{
		Delay_ms(1000);
	}
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;//关闭计数器
}
