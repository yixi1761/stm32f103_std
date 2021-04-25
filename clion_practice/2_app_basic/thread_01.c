#include<pthread.h>
#include<stdio.h>

int main(int argc, char const *argv[])
{
    pthread_t aa;
    aa = pthread_self();
    printf("%lu\n",aa);
    return 0;
}


