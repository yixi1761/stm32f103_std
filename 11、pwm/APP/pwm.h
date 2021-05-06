#ifndef __tim_h
#define __tim_h

#include "STM32F10X.h"
#include <misc.h>
#include <stm32f10x_tim.h>

void tim3_init(u16 period,u16 Prescaler);
void tim3_nvic_init(void);

#endif
