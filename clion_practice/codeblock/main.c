#include <stdio.h>
#include "util.h"
#include "time.h"
//#include <string.h>

//#define path1 "/home/ansel/test.txt"

//int main() {
//    FILE *fp;
//    char msg[]="testtttt!";
//    char buf[20];
//    size_t size;
//    fp = fopen(path1, "w+");
//    size = fwrite(msg, 1, strlen(msg)+1, fp);
//    printf("%d\n", (int)size);
//    //指针回到文件的开头
//    fseek(fp,0,SEEK_SET);
//
//    fread(buf, strlen(msg)+1, 1, fp);
//    printf("%s\n", buf);
//    fclose(fp);
//    printf("ok");
//    return 0;
//}
//int main(){
//    FILE *fp = NULL;
//    char data[]="888999";
//    fp = fopen("/dev/led_display", "r+");
//    fwrite(data, 1, 7, fp);
//    fclose(fp);
//    return 0;
//}
int main(){
    printf("Hello, World!\n");
//    powerCheck();
    char cmd_data[]={0X68, 0XAA, 0XAA, 0XAA, 0XAA, 0XAA, 0XAA, 0X68, 0X11, 0X04, 0X33, 0X34, 0X34, 0X35, 0XB1, 0X16};//读电压命令
    char recv_data[50];

    int fp = uart_nonblock_init("/dev/ttyS4", 2400, 0, 8, 1, 'E');
    uart_send(fp, cmd_data, 16);
    //send_cmd(fp, cmd_data, 16, recv_data);
    uart_block_recv(fp, recv_data, 50, 100);

    FILE* rd=NULL;
    rd = fopen("/root/1115.txt", "w+");
    fwrite(recv_data, 1, 50, rd);
    fclose(rd);
    return 0;
}

