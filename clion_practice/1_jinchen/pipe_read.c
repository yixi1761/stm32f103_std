#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>

int main(void)
{
    int result = -1;
    int fd[2];
    pid_t pid;
    char readbuf[100];

    result = pipe(fd); //创建管道
    pid = fork();   //创建进程
    if(0 == pid){
		char string[] = "ansel pipe管道！";
        printf("父进程写：%s\n",string);
        close(fd[0]);	//读写打时候必须关闭管道打另一端
        write(fd[1], string, 20); 
        return 0;
    }
    else if(pid>0)	{
		 //	sleep(1);
        close(fd[1]);
		 read(fd[0], readbuf, 100);
        printf("读取内容是：%s \n", readbuf);
    }
    return 0;
}



