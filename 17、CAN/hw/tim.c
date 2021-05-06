#include "tim.h"

void tim3_nvic_init()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;	
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;			
	NVIC_Init(&NVIC_InitStructure);	
}


void tim3_init(u16 period,u16 Prescaler)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_TimeBaseInitStructure.TIM_Prescaler=Prescaler;//分频系数
	TIM_TimeBaseInitStructure.TIM_Period=period;  //计数周期
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV2;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
	
	tim3_nvic_init();
	
	TIM_ITConfig(TIM3, TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
	
}

