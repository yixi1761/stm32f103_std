#include<stdio.h>
#include<unistd.h>
int main ()
{
   FILE *fp;
   int c;
   int n = 0;

   fp = fopen("file.txt","r");
   if(fp == NULL)
   {
      perror("���ļ�ʱ��������");
      return(-1);
   }
   do
   {
      c = fgetc(fp);
      if( feof(fp) )
      {
          break ;
      }
      printf("%c", c);
   }while(1);

   fclose(fp);
   char buf[90];
   getcwd(buf,sizeof(buf));
   printf(buf);
   return(0);
}

