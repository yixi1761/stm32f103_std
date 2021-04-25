#include "../head/led_display.h"

//#define __DEBUG
#ifdef __DEBUG
#define DEBUG(format, ...) printf(format, ##__VA_ARGS__)
#else
#define DEBUG(format, ...)
#endif

int main(){
    DEBUG("hello!\n");
    char a[]="111111";
    char b[]="888999";
    while(1){
        led_display(a); sleep(1);
        led_display(b); sleep(1);
    }
}

int led_display(char *data)
{
    int fd;
    size_t rel_size;
    fd=open("/dev/led_display", O_WRONLY);
    if(fd<0){
        perror("open file failure!\n");
        return fd;      //失败返回-1
    }
    rel_size = write(fd, data, 7);

    if(rel_size != 7) {                     //写入错误
        rel_size = write(fd, data, 7);
        if(rel_size != 7){
            DEBUG("写入错误! %d\n",rel_size);
            return -2;
        }
    }
    close(fd);
    DEBUG("%d\n",rel_size);
    return 1;
}