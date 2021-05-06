#include "GPIO.h"

void GPIO_INIT(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	//������һ���ṹ�壬������ں���ǰ�棬gpio.h�Ѿ�����������ṹ�壬�������һ��ʵ��
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//�ж�ָʾ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//�жϰ���
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//�ⲿ�ж���Ҫʹ��AFIOʱ��
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//LED0/1/2/3,�ĸ���˸ָʾ�ƣ�PP���ģʽ
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;	
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);
	
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//�жϰ���bottom left/down/right���������������
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	//GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;	
	GPIO_Init(GPIOE,&GPIO_InitStructure);	
	
}


