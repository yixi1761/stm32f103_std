//
// Created by ansel on 2020/2/12.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

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
        if(write(pipe_fd[1], "hello ", 5)!=-1){
            printf("write hello ");
        }if(write(pipe_fd[1], "ni hao", 6)!=-1){
            printf("write ni hao\n ");
        }
        close(pipe_fd[1]);
        waitpid(pid, NULL, 0); //等待子进程结束才能退出
        exit(0);
    }
}