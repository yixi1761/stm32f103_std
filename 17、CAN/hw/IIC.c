#include <stm32f10x_i2c.h>
#include "IIC.H"

#define SDA1 GPIO_SetBits(GPIOB,IIC2_SDA)
#define SDA0 GPIO_ResetBits(GPIOB,IIC2_SDA)
#define SCL1 GPIO_SetBits(GPIOB,IIC2_SCL)
#define SCL0 GPIO_ResetBits(GPIOB,IIC2_SCL)
u8 p=100;
/*void IIC_INIT()
{
	I2C_InitTypeDef I2C_InitStructure;
	
	I2C_InitStructure.I2C_ClockSpeed=400000;
	I2C_InitStructure.I2C_Mode=I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle=I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1=0x300;
	I2C_InitStructure.I2C_Ack=I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit;
	I2C_Cmd(I2C2,ENABLE);
	I2C_Init(I2C2,&I2C_InitStructure);
}
*/

void IIC_START()
{
	SDAOUT();
	SDA1;
	SCL1;	
	SDA0;	
	SCL0;	
}

void IIC_STOP()
{
	SDAOUT();
	SDA0;
	SCL1;while(p--);//时钟保持，数据跳变
	SDA1;while(p--);	
}

u8 IIC_WAIT_ACK()
{
	u16 waittime=0;
	SDAIN();
	SDA1;while(p--);
	SCL1;while(p--);
	while(GPIO_ReadInputDataBit(GPIOB,IIC2_SDA))
	{
		waittime++;
		if(waittime>300)
		{
			IIC_STOP();
			return 1;				
		}		
	}
	SCL0;
	return 0;
}

void IIC_ACK()//第9个时钟接收端应答0或1
{
	SCL0;
	SDAOUT();
	SDA0;while(p--);
	SCL1;while(p--);
	SCL0;while(p--);
}

void IIC_NOACK()
{
	SCL0;
	SDAOUT();
	SDA1;Delay_us(4);
	SCL1;Delay_us(4);
	SCL0;Delay_us(4);
}

void IIC_SendByte(u8 dat)
{
	u8 i=0;
	SCL0;
	//Delay_us(1);
	SDAOUT();
	for(i=0;i<8;i++)
	{
		if((dat&0x80)>0)
		{
			SDA1;while(p--);
		}
		else
		{
			SDA0;while(p--);
		}
		dat<<=1;
		SCL1;while(p--);
		SCL0;while(p--);
	}
}

u8 IIC_ReceiveByte()
{
	u8 i=0,dat=0;
	SCL0;while(p--);
	SDAIN();
	for(;i<8;i++)
	{
		dat<<=1;
		dat|=GPIO_ReadInputDataBit(GPIOB,IIC2_SDA);while(p--);
	}
//	if(ack)
//		IIC_ACK();
//	else
		IIC_NOACK();	
	return dat;		
}

