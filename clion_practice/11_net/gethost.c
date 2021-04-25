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


int main(int argc, char *argv[])
{
	int sockfd;
	char buf[1024];
	struct hostent *host;
	struct sockaddr_in server_addr;
	
	if(argc != 2){
		fprintf(stderr, "use %s hostname \n\a", argv[0]);
		exit(1);
	}

	host=gethostbyname(argv[1]);
	if(host == NULL){
		fprintf(stderr, "gethostname error\n\a");
		exit(1);
	}
	
	//填充服务器资料
	bzero(&server_addr, sizeof(server_addr));   //清零
	server_addr.sin_family = AF_INET;
	server_addr.sin_port     = htons(3399);
	server_addr.sin_addr    = *((struct in_addr *)host->h_addr);
	printf("sin_addr is %s", (char *)server_addr.sin_addr);

	close(sockfd);
	exit(0);

}