#include <stdio.h>

int fun();
float temp_humid[2];


int fun(){
     temp_humid[0]=2.2;
     temp_humid[1]=2.2;
    return temp_humid;
}

int main() {
    printf("Hello, World!\n");
    float aa =fun();

   //printf("%f",);
    return 0;
}
