#ifndef __led_h
#define __led_h

#include "STM32F10X.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void led_init(void);

#define BITBAND(addr, bitnum) (0x42000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 

#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 

#define AO(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define AI(n)   BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define BO(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define BI(n)   BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define CO(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define CI(n)   BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define DO(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define DI(n)   BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define EO(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define EI(n)   BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define FO(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define FI(n)   BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define GO(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define GI(n)   BIT_ADDR(GPIOG_IDR_Addr,n)  //输入

#define LED1   CO(0)
#define LED2   CO(1)
#define LED3   CO(2)
#define LED4   CO(3)
#define LED5   CO(4)
#define LED6   CO(5)
#define LED7   CO(6)
#define LED8   CO(7)

#endif
