#include "timer.h"

void timer3_delay()
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
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
	//1s
	TIM_TimeBaseInitStruct.TIM_Prescaler=36000;//set the frequency of timer  1K
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;	
	TIM_TimeBaseInitStruct.TIM_Period=1000-1;//ARR:set the value of autoreload register,change the counter
	TIM_TimeBaseInitStruct.TIM_ClockDivision=0;	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);	
	
	//chanle 1
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse=100;//Õ¼¿Õ±È
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_Low;
	TIM_OC1Init(TIM3,&TIM_OCInitStruct);
	//TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);
	//chanle 2
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStruct.TIM_Pulse=700;//CCR:duty cycle = (TIM3_CCR1/ TIM3_ARR)* 100 = 50%
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_Low;
	TIM_OC2Init(TIM3,&TIM_OCInitStruct);
	//TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);	

	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM3,ENABLE);	

	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;//the IT functions is in stm32f10x.h??	
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//qiang zan you xian ji:0~3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;	
	NVIC_Init(&NVIC_InitStructure);	
}
int cunt=0;
void TIM3_IRQHandler()
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)//检查溢出信号  
  {  
    TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//清除溢出标志  
   cunt++; 
  }  	
	switch(cunt)
	{					
		case 1:GPIO_ResetBits(GPIOC,GPIO_Pin_0);printf("cunt:%d\n",cunt);break;
		case 11:GPIO_ResetBits(GPIOC,GPIO_Pin_1);printf("cunt:%d\n",cunt);break;
		case 21:GPIO_ResetBits(GPIOC,GPIO_Pin_2);printf("cunt:%d\n",cunt);break;
		case 31:GPIO_ResetBits(GPIOC,GPIO_Pin_3);printf("cunt:%d\n",cunt);break;
//		case 50:GPIO_ResetBits(GPIOC,GPIO_Pin_4);printf("cunt:%d\n",cunt);break;
//		case 80:GPIO_ResetBits(GPIOC,GPIO_Pin_5);printf("cunt:%d\n",cunt);break;
//		case 100:GPIO_ResetBits(GPIOC,GPIO_Pin_6);printf("cunt:%d\n",cunt);break;
		case 200:GPIO_SetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6);break;
		default :GPIO_ResetBits(GPIOC,GPIO_Pin_7);printf("cunt:%d\n",cunt);break;
	}
}
/*
void timer3_init(void)
{	
	gpio_pwm();
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	

	TIM_DeInit(TIM3);
	TIM_InternalClockConfig(TIM3);		
	
	TIM_TimeBaseInitStruct.TIM_Prescaler=0;//set the frequency of timer
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;	
	TIM_TimeBaseInitStruct.TIM_Period=0xE7d-1;//ARR:set the value of autoreload register,change the counter
	TIM_TimeBaseInitStruct.TIM_ClockDivision=0;	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);	
	//
	
			

	TIM_Cmd(TIM3, ENABLE);
}

*/
