#ifndef __IIC_H
#define __IIC_H

#include "Delay.H"
#include "GPIO.H"

//void IIC_INIT(void);
void IIC_START(void);
void IIC_STOP(void);
u8 IIC_WAIT_ACK(void);
void IIC_ACK(void);
void IIC_NOACK(void);
void IIC_SendByte(u8 dat);
u8 IIC_ReceiveByte(void);



#endif

