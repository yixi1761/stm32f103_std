#include "GPIO.h"

void GPIO_INIT(void)
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	//先声明一个结构体，必须放在函数前面，gpio.h已经定义了这个结构体，这里提出一个实例
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);//中断指示灯
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//中断按键
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断需要使能AFIO时钟
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;//LED0/1/2/3,四个闪烁指示灯，PP输出模式
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;	
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOC,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3);
	
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;//中断按键bottom left/down/right，三个上拉输入脚
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	//GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;	
	GPIO_Init(GPIOE,&GPIO_InitStructure);	
	
}


