#ifndef __Delay_h
#define __Delay_h

#include "STM32F10X.h"
#include "misc.h"
#include "core_cm3.h"
#include <stm32f10x_conf.h>

#include <stdio.h>

void Delay_us(u32 n_us);
void Delay_ms(u32 n_ms);
void Delay_s(u32 n_s);

#endif
