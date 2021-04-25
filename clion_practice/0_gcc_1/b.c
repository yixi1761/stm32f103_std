#include <time.h>
#include <stdio.h>
int main(void){
	time_t t;
	t=time(NULL);
	printf("%d\n",t);
	struct tm *local;
	local=localtime(&t);
	printf("%d\n",local->tm_min);
}
