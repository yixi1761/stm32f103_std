#ifndef __delay_h
#define __delay_h

#include "STM32F10X.h"
#include "core_cm3.h"

void delay_simple(u32 i);
void delay_us(u32 n_us);
void delay_ms(u16 n_ms);
void delay_s(u16 n_s);

#endif

