#include <stdio.h>

int main ()
{
   FILE *fp;
   int len;

   fp = fopen("file.txt", "r");
   if( fp == NULL ) 
   {
      perror ("���ļ�����");
      return(-1);
   }
   fseek(fp, 0, SEEK_END);

   len = ftell(fp);
   fclose(fp);

   printf("file.txt ���ܴ�С = %d �ֽ�\n", len);
   
   return(0);
}
