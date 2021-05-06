#ifndef __rtc_h
#define __rtc_h

#include "STM32F10X.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_pwr.h"
#include "stm32f10x_bkp.h"
#include "stm32f10x_rtc.h"
#include "delay.h"
#include "led.h"
#include "misc.h"

u8 rtc_init(void);
u8 rtc_set(u16 year,u8 month,u8 day,u8 h,u8 m,u8 s);
u8 rtc_get(void);
	
typedef struct
{
	u16 year;
	u16 month;
	u16 day;
	u16 hour;
	u16 minute;
	u16 second;	
}calendartypedef;

extern calendartypedef calendarstruct;
#endif
