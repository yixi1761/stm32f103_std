#define PERM S_IRUSR|S_IWUSR
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>


int main(int argc, char **argv)
{
	int shmid;
	char *p_addr, *c_addr;

	if(argc!=2){
		fprintf(stderr, "%s\n",argv[0] );
		exit(1);
	}

	//创建共享内存
	if((shmid=shmget(IPC_PRIVATE, 1024, PERM))==-1){
		fprintf(stderr,"create share memory error %s\n\a", strerror(errno));
		exit(1);
	}

	// 父進程 寫
	if(fork()){
		p_addr = shmat(shmid, 0, 0);
		memset(p_addr, '\0', 1024);
		strncpy(p_addr, argv[1], 1024);
		wait(NULL);
		exit(0);
	}else{
		sleep(1);
		c_addr = shmat(shmid, 0, 0);
		printf("get the char: %s\n", c_addr);
		exit(0);
	}
}	
