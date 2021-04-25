#include <unistd.h>
#include <stdio.h>

int main(void)
{
    pid_t pid;
    int count=0;
    pid = fork();
    count++;
    printf( "count = %d\n", count );
    return 0;
}

