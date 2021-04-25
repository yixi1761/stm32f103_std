#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/*
void create_file(char *filename)
{
    if(creat(filename, 0755)<0){
        printf("create file failure!\n");
    } else{
        printf("create file success!");
    }
}

int main(int argc, char *argv[])
{
    int i;
    if(argc<2){
        perror("you haven't input the filename!")
        exit(EXIT_FAILURE);
    }

    for(i=1; i<argc; i++){
        create_file(argv[i]);
    }

    exit(EXIT_SUCCESS);
}
 */
/*
int main(int argc, char *argv[])
{
    int fd;
    if(argc<2){
        puts("plase input the open file name!\n");
        exit(1);
    }

    if((fd=open(argv[1], O_CREAT|O_RDWR, 0755))<0){
        perror("打开文件失败！\n");
        exit(1);
    }else{
        printf("open file %d success!\n", fd);
    }

    close(fd);
    exit(0);
}
 */
/*
int main()
{
   FILE *fp;
   char ch;
   if((fp=fopen("text.txt", "rt"))==NULL){
       printf("\nconnot open file any key exit!");
       getch();
       exit(1);
   }
    ch = fgetc(fp);
   while(ch!=EOF){
       putchar(ch);
       ch = fgetc(fp);
   }
    fclose(fp);
}
 */
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid;
    pid = fork();
    if(pid<0)
        printf("error!\n");
    else if(pid==0)
        printf("this is the child process, id is%d\n", getpid());
    else
        printf("this is parent process, id is%d\n", getpid());
}