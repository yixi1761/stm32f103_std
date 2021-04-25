1.串口初始化-阻塞模式函数
	int uart_block_init(char *tty,int speed,int flow_ctrl,int databits,int stopbits,int parity)
	参数说明：
		tty:串口名，例如：/dev/ttyS0
		speed:波特率,例如：115200
		flow_ctrl:1：流控 0：无流控。一般无流控
		databits:数据位数：8
		stopbits:停止位：1
		parity:校验位：'N' :无校验，'O':寄校验，'E':偶校验, 'S':空格校验
        返回值：串口文件句柄，应用需要记录此参数，在需要发送和接收时使用此参数
    例：
       int fd = uart_block_init("/dev/ttyS2",9600,0,8,1,'N');	

2.串口初始化-非阻塞模式函数，
	int uart_nonblock_init(char *tty,int speed,int flow_ctrl,int databits,int stopbits,int parity)
	参数说明：
		tty:串口名，例如：/dev/ttyS0
		speed:波特率,例如：115200
		flow_ctrl:1：流控 0：无流控。一般无流控
		databits:数据位数：8
		stopbits:停止位：1
		parity:校验位：'N' :无校验，'O':寄校验，'E':偶校验, 'S':空格校验
        返回值：串口文件句柄，应用需要记录此参数，在需要发送和接收时使用此参数	
	例：
       int fd = uart_nonblock_init("/dev/ttyS2",9600,0,8,1,'N');
	   
3.串口接收-阻塞模式函数
	说明：如果串口未有数据，则阻塞50ms，返回-1
	int uart_block_recv(int fd, char *buf,int dlen,int ms)
	参数说明:
	    fd:串口句柄
		buf:串口数据保存，申请buf内存时，可根据可能接收到的最大数据包为数据长度，这样可以保存一次全部读取完
		dlen:期望接收的长度，此长度与buf可接收的实际长度相同
		ms: 阻塞时间，单位毫秒
        返回值：返回数据长度，未接收到数据返回-1,参数错误返回-2。如果实际读取到的数据小于则期望的长度，则返回实际读取到的长度，最大读取长度为期望读取到的长度。
		
4.串口接收-非阻塞模式函数
	int uart_nonblock_recv(int fd, char *buf,int dlen) 
	说明：读取系统缓存的串口数据，未收到串口数据则返回-1
	参数说明:
	    fd:串口句柄
		buf:串口数据保存，申请buf内存时，可根据可能接收到的最大数据包为数据长度，这样可以保存一次全部读取完
		dlen:期望接收的长度，此长度与buf可接收的实际长度相同
        返回值：返回数据长度，未接收到数据返回-1,参数错误返回-2。如果实际读取到的数据小于则期望的长度，则返回实际读取到的长度，最大读取长度为期望读取到的长度。

5.串口发送
    int uart_send(int fd, char *buf,int dlen)
	参数说明：
        fd:串口句柄
		buf:串口数据
		dlen:需要发送的长度
		返回值：返回实际发送的长度,参数错误返回-2
		
6.关闭串口
	void uart_close(int fd)
	参数说明：
		fd:串口句柄

7.检测是否超时
	int get_is_timeout(uint64_t *tick,uint32_t ms)
	参数说明：
		tick:记录时间参数，传入的需要是static类型
		ms:超时时间，就是上次运行到本次运行时，是否超过这个时间
		返回值：超时返回1，否则为0，当参数错误时返回-2;

