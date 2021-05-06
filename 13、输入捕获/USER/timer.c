#include "timer.h"
#include "led.h"
#include "STM32F10X.h"

void timer3_delay()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);		
	
	TIM_DeInit(TIM3);
	TIM_InternalClockConfig(TIM3);		
	TIM_TimeBaseInitStruct.TIM_Prescaler=36000;//set the frequency of timer  1M
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;	
	TIM_TimeBaseInitStruct.TIM_Period=10000-1;//ARR:set the value of autoreload register,change the counter
	TIM_TimeBaseInitStruct.TIM_ClockDivision=0;	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);	
	
	//chanle 1
	TIM_ICInitStruct.TIM_Channel=TIM_Channel_1;
	TIM_ICInitStruct.TIM_ICFilter=0x0f;
	TIM_ICInitStruct.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInitStruct.TIM_ICPrescaler=TIM_ICPSC_DIV1;
	TIM_ICInitStruct.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM3,&TIM_ICInitStruct);	

	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC1,ENABLE);
	TIM_Cmd(TIM3,ENABLE);	

	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;//the IT functions is in stm32f10x.h??	
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//qiang zan you xian ji:0~3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;	
	NVIC_Init(&NVIC_InitStructure);	
}

int times=0;
u32 ch1value1,ch1value2,total;
void TIM3_IRQHandler()
{
	static int sta=0;
	
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)//溢出中断 
  { 
		LED1=~LED1;
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//清除溢出标志  
		if (sta==1)	
			{
				times++;						
				LED2=~LED2;
			}
  }  	
	if(TIM_GetITStatus(TIM3,TIM_IT_CC1)!=RESET)//检查捕获  
  {  
		TIM_ClearITPendingBit(TIM3,TIM_IT_CC1);//清除溢出标志  
		if (sta==0)
		{	//rising
			sta=1;
			LED3=1;
			ch1value1=TIM_GetCapture1(TIM3);
			printf ("rising:%d\n",ch1value1);	printf("\r\n");		
			TIM_OC1PolarityConfig(TIM3,TIM_OCPolarity_Low);//bugggggg,but right.			
		} 
		else
		{	//falling
			sta=0;
			LED3=0;
			ch1value2=TIM_GetCapture1(TIM3);
			printf ("falling:%d\n",ch1value2);	printf("\r\n");			
			TIM_OC1PolarityConfig(TIM3,TIM_OCPolarity_High);			
			total=1000*times+ch1value2-ch1value1;
			printf ("high level time is:%dus\n",total);printf("\r\n");
		}
	} 		
}
	
