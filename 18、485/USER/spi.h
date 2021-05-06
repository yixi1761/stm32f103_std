# ifndef __spi_h
# define __spi_h

# include <stm32f10x_spi.h>
# include <stm32f10x_gpio.h>
# include "gpio.h"

/* 定义指令表	8M=65535bit	,SECTOR addr=0~511 */
#define W25X_WriteEnable		0x06 
#define W25X_WriteDisable		0x04 
#define W25X_ReadStatusReg		0x05 
#define W25X_WriteStatusReg		0x01 
#define W25X_ReadData			0x03 
#define W25X_FastReadData		0x0B 
#define W25X_FastReadDual		0x3B 
#define W25X_PageProgram		0x02 
#define W25X_BlockErase			0xD8 
#define W25X_SectorErase		0x20 
#define W25X_ChipErase			0xC7 
#define W25X_PowerDown			0xB9 
#define W25X_ReleasePowerDown	0xAB 
#define W25X_DeviceID			0xAB 
#define W25X_ManufactDeviceID	0x90 
#define W25X_JedecDeviceID		0x9F 

#define spi_cs  GO(13)

/*声明外部函数*/
void spi_cfg(void);
int spi_readID(void);
void spi_flashread(u8 *buf,u32 startaddr,u16 length);
u8 spi_write(u8* buf,u32 startaddr,u16 length);

#endif
