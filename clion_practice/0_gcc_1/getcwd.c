#include <unistd.h>
#include <stdio.h>
#include <time.h>
/*
int main()
{
    char buf[80];
    getcwd(buf, sizeof(buf));
    printf("current work is %s\n", buf);

    time_t t;
	struct tm *local;
    t = time(NULL);
	local = localtime(&t);
	printf("%ld~~\n", t);
	printf("%d~~\n", local->tm_year+1900);
	printf("%d~%d~\n", local->tm_mon+1, local->tm_mday);

	printf("%s\n", asctime(local));
	printf("%s\n", ctime(&t));

	printf("pid is %d\n",getpid());

    return 1;
}
*/

/*
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid;
    pid = fork();
    if(pid<0)
        printf("error!\n");
    else if(pid==0)
        printf("this is the child process, id is %d\n", getpid());
    else
        printf("this is parent process, id is %d,it's child process id is %d\n", getpid(), pid);
}
*/

/*
int main()
{
	int pipe_fd[2];
	printf("pipe  is %d\n", pipe(pipe_fd));
	printf("pipe 1 is %d\n", pipe_fd[0]);
}
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int pipe_fd[2];
    pid_t pid;
    char r_buf[100];
    int r_num;

    memset(r_buf, 0, sizeof(r_buf));

    if (pipe(pipe_fd) < 0) {
        printf("create pipe error!\n");
        return -1;
    }
  //子进程执行
    if ((pid=fork())==0) {
        printf("child process :\n");
        close(pipe_fd[1]);
        sleep(2);
        r_num=read(pipe_fd[0], r_buf, 100);
        printf("%d\n", r_num);
        if(r_num>0){
            printf("%d char is read: %s\n", r_num, r_buf);
        }
        close(pipe_fd[0]);
        exit(0);
    }
    //父进程执行
    else if(pid>0){
        printf("father process:\n");
        //close(pipe_fd[0]);
        if(write(pipe_fd[1], "hello", 5)!=-1){
            printf("write hello ");
        }if(write(pipe_fd[1], "ni hao", 6)!=-1){
            printf("write ni hao\n ");
        }
        close(pipe_fd[1]);
        waitpid(pid, NULL, 0); //等待子进程结束才能退出
        exit(0);
    }
}
