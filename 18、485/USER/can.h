# ifndef __can_h
# define __can_h

# include <stm32f10x_can.h>
# include <stm32f10x_gpio.h>
# include "gpio.h"

/* 定义指令表	8M=65535bit	,SECTOR addr=0~511 */
#define W25X_WriteEnable		0x06 

/*声明外部函数*/
void can_cfg(void);
u8 can_send_msg(u32 ID,u8* msg,u8 length);
u8 can_receive_msg(u8* buf);

#endif
