#include "Delay.h"

void Delay_us(u32 n_us)
{	
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	//默认使用内核时钟源FCLK（HCLK 72MHz），每个tick周期1/72000 000，1us是72个周期。
	SysTick_Config(n_us*72);//判断24位load寄存器超出；重载；中断优先级设置；计数器清零；设置时钟源；开启中断；开始计数
	while((SysTick->CTRL&1)&&!(SysTick->CTRL&(1<<16)));	//查询检测control寄存器的最高位flag，数到0会置位。前面&1是判断计数器有没有被意外关闭
			
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;//关闭计数器
	SysTick->VAL	= 0;	//计数寄存器清零
}

void Delay_ms(u16 n_ms)
{	
	u16 i=n_ms;
	while (i--)	{		Delay_us(1000);	}
}

void Delay_s(u16 n_s)
{
	u16 i=n_s;
	while (i--)		{		Delay_ms(1000);	}
}
