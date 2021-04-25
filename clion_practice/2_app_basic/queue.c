#define PERM S_IRUSR|S_IWUSR
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/msg.h>

#include <sys/ipc.h>
#include <sys/wait.h>

struct mymsg
{
	long int mytype;
	/* data */
	char mytext[512];
};


int main(int argc, char **argv)
{
	key_t key ;
	int id = 0;
	struct  mymsg queuemsg;
	int ret;

	key = ftok("/tmp/msg1", 66);
	id = msgget(key, IPC_CREAT|0666);
	if(id==-1){
		printf("create message error!\n");
		return 0;
	}else
	{
		printf("key is %x\n", key);
	}

	queuemsg.mytype = getpid();    //类型只需要收发队列保持一致即可
	strcpy(queuemsg.mytext, "queuemsg text~");
	ret = msgsnd(id, &queuemsg, sizeof(queuemsg.mytext), IPC_NOWAIT);
	if(ret==-1){
		printf("sned message error\n");
		return -1;
	}

	memset(&queuemsg, 0, sizeof(queuemsg));
	ret = msgrcv(id, &queuemsg, sizeof(queuemsg.mytext), getpid(), IPC_NOWAIT);
	if(ret==-1){
		printf("recv msg error\n");
		return -1;
	}
	printf("recv msg is %s\n", queuemsg.mytext);
}	
