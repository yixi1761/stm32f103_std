#ifndef __led_h
#define __led_h

#include "STM32F10X.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "gpio.h"

void led_cfg(void);

#define LED1   CO(0)
#define LED2   CO(1)
#define LED3   CO(2)
#define LED4   CO(3)
#define LED5   CO(4)
#define LED6   CO(5)
#define LED7   CO(6)
#define LED8   CO(7)

#endif
