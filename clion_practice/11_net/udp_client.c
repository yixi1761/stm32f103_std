#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include <netdb.h>

#include<sys/socket.h>
#include<sys/types.h>

#include<netinet/in.h>
#include<arpa/inet.h>

#define port_num 8888
#define max_buf_size 1024

void udp_client_rec(int sockfd, const struct sockaddr_in *server_addr, int len)
{
	char buf[max_buf_size];
	int n, stat;
	while (1)
	{
		printf("please input char:\n");
		fgets(buf, max_buf_size, stdin);
		printf("get OK\n");
		stat  = sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)server_addr, len);
		printf("send over, %d\n", stat);
		if(stat == -1){
			fprintf(stderr, "send error: %s \n\a", strerror(errno));
			exit(1);
		}
		bzero(buf, max_buf_size);
	}
}
int main(int argc, char  **argv)
{
	int sockfd, stat;
	struct sockaddr_in server_addr;

	if(argc != 2){
		fprintf(stderr, "use %s server ip \n\a", argv[0]);
		exit(1);
	}

	//client端创建套接字
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0){
		fprintf(stderr, "socket error: %s  \n\a", strerror(errno));
		exit(1);
	}
	//填充服务器资料
	bzero(&server_addr, sizeof(server_addr));   //清零
	server_addr.sin_family = AF_INET;
	server_addr.sin_port     = htons(port_num);
	stat = inet_aton(argv[1], &server_addr.sin_addr); //字符串型的IP转换为网络格式,存入服务器地质结构中
	if(stat<0){
		fprintf(stderr, "IP error: %s  \n\a", strerror(errno));
		exit(1);
	}
	udp_client_rec( sockfd, &server_addr, sizeof(struct sockaddr_in) );

	close(sockfd);
	exit(0);
}
