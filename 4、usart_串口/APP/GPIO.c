#include "GPIO.h"
#include "STM32F10X.h"

void mygpio_init(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;//������һ���ṹ�壬������ں���ǰ�棬gpio.h�Ѿ�����������ṹ�壬�������һ��ʵ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORT A��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//���ж�ָʾ�ư�
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//����1��ʱ��ʹ��
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//TX
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;//RX
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//LED
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;	
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//LED
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;	
	GPIO_Init(GPIOC,&GPIO_InitStructure);	
}


