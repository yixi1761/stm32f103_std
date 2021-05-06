#ifndef __usart_h
#define __usart_h

#include "STM32F10X.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "misc.h"
#include "led.h"

void usart_init(void);
void USART1_IRQHandler(void);


#endif
