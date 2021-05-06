#ifndef __GPIO_H
#define __GPIO_H

void IIC_GPIO_INIT(void);
void USART_GPIO_INIT(void);
void LED_GPIO_INIT(void);
void SDAOUT(void);
void SDAIN(void);

#define IIC2_SCL GPIO_Pin_10
#define IIC2_SDA GPIO_Pin_11

#endif

