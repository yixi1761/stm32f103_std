#include "EXTI.h"

void EXTI_INIT(void)
{
	//����GPIO�����ж�
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;		
	
	EXTI_InitStructure.EXTI_Line=EXTI_Line2|EXTI_Line3|EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Falling;		
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTI_InitStructure);	
		
	//�����ж����������õĲ���дһ�飬��������������ó�ͬһ���ȼ������Էֱ��ʼ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�������Ϊ2�Ļ�����0~3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;	
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI2_IRQn;//��stm32f10x.h���棬�ⲿ�жϷŵ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;	//��Ӧ���ȼ�	
	NVIC_Init(&NVIC_InitStructure);//��ʼ���ж�	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);	
	
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;	//��Ӧ���ȼ�
	NVIC_Init(&NVIC_InitStructure);	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);	
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=2;	//��Ӧ���ȼ�	
	NVIC_Init(&NVIC_InitStructure);	
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);		
	
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;	
	NVIC_Init(&NVIC_InitStructure);
	
	/*IO���ж��ߵ�ӳ�䣬���ص��ж�����,��Ҫ���ж�������ʼ�������,Ҳ�����ȹҵ��ⲿ�ж����ϣ�
	�ٹҵ�NVIC������,	���Ǳ���һһ��Ӧ�����������û��һһ��Ӧ��*/	
}
