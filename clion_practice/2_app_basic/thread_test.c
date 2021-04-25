#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *mythread1(void)
{
	int i;
	for(i=0; i<5; i++){
		printf("this is thread1\n");
		sleep(1);
	}
}

void *mythread2(void)
{
	int i;
	for(i=0; i<5; i++){
		printf("this is thread2~\n");
		sleep(1);
	}
}

int main()
{
	int i=0, ret=0;
	pthread_t id1, id2;
	ret = pthread_create(&id1, NULL, (void *)mythread1, NULL);
	if(ret){
		printf("create pthread1 error!\n");
		return 1;
	}

	ret = pthread_create(&id2, NULL, (void *)mythread2, NULL);
	if(ret){
		printf("create pthread2 error!\n");
		return 1;
	}
	 
	 pthread_join(id1, NULL);
	 pthread_join(id2, NULL);
	return 0;
}