#include <stdio.h>
#include <stm32f10x.h>
#include "GPIO.H"
#include "Delay.H"
#include "USART.H"
#include "IIC.H"
#include "24c02.H"

int fputc(int ch,FILE *P)
{
	USART_SendData(USART1, (u8) ch);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET);
	return ch;
}


int main()
{	
	u8 i;
	char data1;
	USART_INIT();
	LED_GPIO_INIT();Delay_s(4);
	IIC_GPIO_INIT();
	printf(" start!\n");	
	for(i=0;i<5;i++)
		{			
			GPIO_ResetBits(GPIOC,GPIO_Pin_0);	Delay_ms(200);		
			GPIO_SetBits(GPIOC,GPIO_Pin_0);	  Delay_ms(200);				
		}	
	Write_Byte(0x11,5);
	
	//Write_nByte(0x12,"zmss",'4');
	//get = Read_Byte(0x10);
	printf("写入成功!i=%d",i);
	data1=Read_Byte(0x11);
	printf("读出成功!读出的是=%s",data1);
}

