#ifndef __24c02_H
#define __24c02_H

#include "STM32F10X.h"


void Write_Byte(u8 addr,u8 data);
u8 Read_Byte(u8 addr);
//void Write_nByte(u8 addr,u32 data,u8 n);
//u8 Read_nByte(u8 addr,u8 n);


#endif
