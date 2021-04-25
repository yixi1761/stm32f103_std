
#ifndef __UTIL_H
#define __UTIL_H

#ifdef __cplusplus
 extern "C" {
#endif

#include<stdint.h>     
#include<stdio.h>     
#include<stdlib.h>    
#include<unistd.h>     
#include<sys/types.h>   
#include<sys/stat.h>     
#include<fcntl.h>     
#include<termios.h>  
#include<errno.h>    
#include<string.h>  
#include <time.h>

#define FALSE  -1  
#define TRUE   0  

int uart_nonblock_init(char *tty,int speed,int flow_ctrl,int databits,int stopbits,int parity);
int uart_block_init(char *tty,int speed,int flow_ctrl,int databits,int stopbits,int parity);
int uart_nonblock_recv(int fd, char *buf,int dlen);
int uart_block_recv(int fd, char *buf,int dlen,int ms);
int uart_send(int fd, char *buf,int dlen);
void uart_close(int fd);
int get_is_timeout(uint64_t *tick,uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif /* __UTIL_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

