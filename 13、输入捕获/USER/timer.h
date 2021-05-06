#ifndef __timer_h
#define __timer_h

#include "STM32F10X.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void timer3_init(void);
void gpio_pwm(void);

void timer3_delay(void);
void TIM3_IRQHandler(void);

#endif

