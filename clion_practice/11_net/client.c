#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<errno.h>

#define port_num 3399

int main(int argc, char *argv[])
{
	int sockfd;;
	char buf[1024];
	struct sockaddr_in server_addr;
	struct hostent *host;

	if(argc != 2){
		fprintf(stderr, "use %s hostname \n\a", argv[0]);
		exit(1);
	}

	host=gethostbyname(argv[1]);
	if(host == NULL){
		fprintf(stderr, "gethostname error\n\a");
		exit(1);
	}
	//client端创建套接字
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1){
		fprintf(stderr, "socket error: %s  \n\a", strerror(errno));
		exit(1);
	}
	//填充服务器资料
	bzero(&server_addr, sizeof(server_addr));   //清零
	server_addr.sin_family = AF_INET;
	server_addr.sin_port     = htons(port_num);
	server_addr.sin_addr    = *((struct in_addr *)host->h_addr);

	//发起连接请求
	if(
		connect(sockfd, (struct sockaddr *)(&server_addr), sizeof(server_addr))==-1
	)
	{
		fprintf(stderr, "connect error: %s  \n\a", strerror(errno));
		exit(1);
	}

	printf("input char:\n");
	while(1){
		fgets(buf, 1024, stdin);
		
		write(sockfd, buf, strlen(buf));
	}
	

	close(sockfd);
	exit(0);

}