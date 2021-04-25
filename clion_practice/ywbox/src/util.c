
#include "../head/util.h"
  
static int uart_block_open(char* port)  
{     
	int fd;
    fd = open( port, O_RDWR|O_NOCTTY);  
    if (fd < 0)  
    {  
        printf("can't open serial port:%s\n",port);  
        return (FALSE);  
    }  
        
    if(isatty(STDIN_FILENO) == TRUE) {    
        printf("standard input is not a terminal device\n");  
        return (FALSE);  
    } 
	
    return fd;  
}   

static int uart_nonblock_open(char* port)  
{     
	int fd;
    fd = open( port, O_RDWR|O_NOCTTY|O_NONBLOCK);  //非阻塞
    if (fd < 0)  
    {  
        printf("can't open serial port:%s\n",port);  
        return (FALSE);  
    }  
    
	if(isatty(STDIN_FILENO) == TRUE) {    
        printf("standard input is not a terminal device\n");  
        return (FALSE);  
    } 
	
    return fd;  
}

void uart_close(int fd)
{  
    if (fd >= 0)
		close(fd);  
}  

static int uart_set(int fd,int speed,int flow_ctrl,int databits,int stopbits,int parity)  
{       
    int   i;  
    int   status;  
    int   speed_arr[] = { B115200, B19200, B9600, B4800, B2400, B1200, B300};  
    int   name_arr[] = {115200,  19200,  9600,  4800,  2400,  1200,  300};  
           
    struct termios options;  
     
    /*tcgetattr(fd,&options)得到与fd指向对象的相关参数，并将它们保存于options,该函数还可以测试配置是否正确，该串口是否可用等。若调用成功，函数返回值为0，若调用失败，函数返回值为-1. 
    */  
    if ( tcgetattr( fd,&options)  !=  0) {     
        perror("setupSerial 1");      
        return FALSE;   
    }      
 
    for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++)  {
        if  (speed == name_arr[i]) {                       
            cfsetispeed(&options, speed_arr[i]);   
            cfsetospeed(&options, speed_arr[i]);    
        }  
    }    
     
    options.c_cflag |= CLOCAL;  //修改控制模式，保证程序不会占用串口   
    options.c_cflag |= CREAD;   //修改控制模式，使得能够从串口中读取输入数据  
       
    switch(flow_ctrl) {   //设置数据流控制
        
       case 0 :
            options.c_cflag &= ~CRTSCTS;  //不使用流控制  
            break;     
        
       case 1 : 
            options.c_cflag |= CRTSCTS; //使用硬件流控制  
            break;  
       case 2 :
            options.c_cflag |= IXON | IXOFF | IXANY;//使用软件流控制    
            break;  
    }  
    
   
    options.c_cflag &= ~CSIZE;//设置数据位   //屏蔽其他标志位  
	
    switch (databits) {   
       case 5:  
            options.c_cflag |= CS5;  
            break;  
       case 6:  
            options.c_cflag |= CS6;  
            break;  
       case 7:      
            options.c_cflag |= CS7;  
            break;  
       case 8:      
            options.c_cflag |= CS8;  
            break;    
       default:     
            fprintf(stderr,"Unsupported data size\n");  
            return FALSE;   
    }  
    
    switch (parity) { //设置校验位 
       case 'n':  
       case 'N': //无奇偶校验位。  
            options.c_cflag &= ~PARENB;   
            options.c_iflag &= ~INPCK;      
            break;   
       case 'o':    
       case 'O'://设置为奇校验      
            options.c_cflag |= (PARODD | PARENB);   
            options.c_iflag |= INPCK;               
            break;   
       case 'e':   
       case 'E'://设置为偶校验    
            options.c_cflag |= PARENB;         
            options.c_cflag &= ~PARODD;         
            options.c_iflag |= INPCK;        
            break;  
       case 's':  
       case 'S': //设置为空格   
            options.c_cflag &= ~PARENB;  
            options.c_cflag &= ~CSTOPB;  
            break;   
        default:    
            fprintf(stderr,"Unsupported parity\n");      
            return FALSE;   
    }   
    
    switch (stopbits) { // 设置停止位  
       case 1:     
            options.c_cflag &= ~CSTOPB; break;   
       case 2:     
            options.c_cflag |= CSTOPB; break;  
       default:     
            fprintf(stderr,"Unsupported stop bits\n");   
            return FALSE;  
    }  
     
    //修改输出模式，原始数据输出  
    options.c_oflag &= ~OPOST;  
    
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);//我加的  
    //options.c_lflag &= ~(ISIG | ICANON);  
     
    //设置等待时间和最小接收字符  
    options.c_cc[VTIME] = 1; /* 读取一个字符等待1*(1/10)s */    
    options.c_cc[VMIN] = 1; /* 读取字符的最少个数为1 */  
     
    //如果发生数据溢出，接收数据，但是不再读取 刷新收到的数据但是不读  
    tcflush(fd,TCIFLUSH);  
     
    //激活配置 (将修改后的termios数据设置到串口中）  
    if (tcsetattr(fd,TCSANOW,&options) != 0)  { 
        perror("com set error!\n");    
        return FALSE;   
    }  
    return TRUE;   
}

int uart_nonblock_init(char *tty,int speed,int flow_ctrl,int databits,int stopbits,int parity)  
{  
    int err;  
	int fd;   
	
    fd = uart_nonblock_open(tty); 
     
    if (fd < 0) {
		printf("open %s fail!",tty);
		return fd;
	}
	    	
    if (uart_set(fd,speed,flow_ctrl,databits,stopbits,parity) == FALSE) {
       close(fd);		
       return -1;  
    }
	
    return fd;      
} 
 
int uart_block_init(char *tty,int speed,int flow_ctrl,int databits,int stopbits,int parity)  
{  
    int err;  
	int fd;   
	
    fd = uart_block_open(tty); 
  
    if (fd < 0) {
		printf("open %s fail!",tty);
		return fd;
	}
	    	
    if (uart_set(fd,speed,flow_ctrl,databits,stopbits,parity) == FALSE) {
       close(fd);		
       return -1;  
    }
	
    return fd;      
}  
 
int uart_block_recv(int fd, char *buf,int dlen,int ms)  
{  
    int len,fs_sel;  
    fd_set fs_read;  
     
    struct timeval time;  
     
    FD_ZERO(&fs_read);  
    FD_SET(fd,&fs_read);
	     
    time.tv_sec = ms/1000;  
    time.tv_usec = (ms%1000)*1000; 
    
    if (fd >= 0 && buf != NULL) {
		fs_sel = select(fd+1,&fs_read,NULL,NULL,&time);  
		if(fs_sel)  {    
			len = read(fd,buf,dlen);
			return len;  
		}   else  {
			return FALSE;  
	    }
	} else {
		return -2;
	}
}

int uart_nonblock_recv(int fd, char *buf,int dlen)  
{  
    if (fd >= 0 && buf != NULL)
		return read(fd,buf,dlen);  
    else
		return -2;
}

int uart_send(int fd, char *buf,int dlen)  
{  
    if (fd >= 0 && buf != NULL)    
		return write(fd,buf,dlen);  
    else
		return -2;	
}

int get_is_timeout(uint64_t *tick,uint32_t ms)
{
    uint64_t diff;
	uint64_t temp;

	if (tick != NULL) {
		struct timespec ts;
		clock_gettime(CLOCK_MONOTONIC, &ts);
		temp = (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);

		diff = temp - *tick;

		if (diff > ms) {
			*tick=temp;
			return 1;
		}
		return 0;
	}

	return -2;
}
