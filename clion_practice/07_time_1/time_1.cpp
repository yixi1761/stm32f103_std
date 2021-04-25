#include<stdio.h>
#include<time.h>
#include<sys/types.h>
#include<unistd.h>

int main ()
{
    #define BST (+1)
    #define CCT (+8)
   time_t time1;
   struct tm *localti;
   //time1 = time(NULL);
   time(&time1);
   localti = gmtime(&time1);
   printf("time is %ld\n",time1);
   printf("日期：、\n%02d",localti->tm_mon);
   printf("伦敦：%2d:%02d\n", (localti->tm_hour+BST)%24, localti->tm_min);
   printf("中国：%2d:%02d\n", (localti->tm_hour+CCT)%24, localti->tm_min);
   printf(asctime(localti));
   printf("%d\n",getpid());
   //printf("%d\n",getppid());
   return(0);
}

