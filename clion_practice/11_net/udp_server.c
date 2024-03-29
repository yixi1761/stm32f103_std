#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#include<sys/socket.h>
#include<sys/types.h>

#include<netinet/in.h>
#include<arpa/inet.h>

#define port_num 8888
#define max_msg_len 1024

void udps_respon(int sockfd) 
{ 
	struct sockaddr_in addr; 
	int addrlen,n; 
	char msg[max_msg_len]; 

	while(1) 
	{	/* 从网络上读,并写到网络上 */ 
		bzero(msg,sizeof(msg)); // 初始化,清零
		addrlen = sizeof(struct sockaddr); 
		n=recvfrom(sockfd,msg,max_msg_len,0,(struct sockaddr*)&addr,&addrlen); // 从客户端接收消息
		msg[n]=0; 
		/* 显示服务端已经收到了信息 */ 
		fprintf(stdout,"Server have received %s",msg); // 显示消息
	} 
} 

int main(void) 
{ 
	int sockfd; 
	struct sockaddr_in addr; 

	/* 服务器端开始建立socket描述符 */ 
	sockfd=socket(AF_INET,SOCK_DGRAM,0); 
	if(sockfd<0) 
	{ 
		fprintf(stderr,"Socket Error:%s\n",strerror(errno)); 
		exit(1); 
	} 

	/* 服务器端填充 sockaddr结构 */ 
	bzero(&addr,sizeof(struct sockaddr_in)); 
	addr.sin_family=AF_INET; 
	addr.sin_addr.s_addr=htonl(INADDR_ANY); 
	addr.sin_port=htons(port_num); 

	/* 捆绑sockfd描述符 */ 
	if(bind(sockfd,(struct sockaddr *)&addr,sizeof(struct sockaddr_in))<0) 
	{ 
		fprintf(stderr,"Bind Error:%s\n",strerror(errno)); 
		exit(1); 
	} 

	udps_respon(sockfd); // 进行读写操作
	close(sockfd); 
} 


