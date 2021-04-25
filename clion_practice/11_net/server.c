#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<errno.h>
#include<arpa/inet.h>

#define port_num 3399
int main()
{
	int sockfd, new_fd;
	struct sockaddr_in server_addr, client_addr;
	int sin_size;
	int nbytes;
	char buf[1024];

	//服务器端建立sockefd描述符
	if((sockfd=socket(AF_INET, SOCK_STREAM, 0))==-1){
		fprintf(stderr, "socket error:%s\n\a", strerror(errno));
		exit(1);
	}
	//服务器端填充sockaddr结构
	bzero(&server_addr, sizeof(server_addr));  //清零
	server_addr.sin_family 		   = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //0.0.0.0  多网卡情况下任意一个IP都行
	server_addr.sin_port		     =htons(port_num);

	//将套接字与IP地址绑定
	if(bind(sockfd, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr)) == -1){
		fprintf(stderr, "bind error:%s\n\a", strerror(errno));
		exit(1);
	}
	//监听套接字
	if(listen(sockfd, 5)==-1){
		fprintf(stderr, "listen error:%s\n\a", strerror(errno));
		exit(1);
	}

	while (1)
	{
		sin_size = sizeof(server_addr);
		new_fd = accept(sockfd, (struct sockaddr *)(&client_addr), &sin_size);
		if( new_fd == -1 ){
			fprintf(stderr, "accept error:%s\n\a", strerror(errno));
			exit(1);
		}
		fprintf(stderr, "server get connection from %s\n", inet_ntoa(client_addr.sin_addr));
		nbytes=read(new_fd, buf, 1024)
		if(nbytes ==-1){
			fprintf(stderr, "read error:%s\n\a", strerror(errno));
			exit(1);
		}
		buf[nbytes] = '\0';
		printf("server receive %s\n", buf);
		close(new_fd);
	}
	
}
