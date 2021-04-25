//
// Created by ansel on 2020/2/14.
//

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


void my_func(int signal_no)
{
    if(signal_no==SIGINT)
        printf("the signal is SIGINT\n");
    else if(signal_no==SIGQUIT)
        printf("the signal is SIGQUIT\n");
}

int main()
{
    printf("wait for signal \n");

    //注册信号处理函数
    signal(SIGINT, my_func);
    signal(SIGQUIT, my_func);
    printf("pid is %d\n",getpid());
    pause();
    exit(0);
}
