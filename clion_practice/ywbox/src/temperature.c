#include "../head/temperature.h"

void main()
{
    printf("hello!\n");
    float *aa;
    while(1){
        temp_humid_get();
        int aa;
        aa = thermograph_status_check();
        printf("%d\n",aa);
        sleep(1);
    }
}

static float temp_humid[2]={0,0};

float* temp_humid_get()
{
    static uint64_t tick = 0;
    if ( 1!= get_is_timeout(&tick, 1000))
        return temp_humid;

    int fd;
    int num;
    char recv_data[5];
    fd=open("/dev/dht12",O_RDONLY);//打开文件
    if(fd<0){
        perror("open file failure!\n");
        return temp_humid;
    }
    num=read(fd, recv_data, 6);
    if(num!=6){
        perror("read file failure!\n");
        return temp_humid;
    }
    close(fd);
    /*计算校验和 OK更新数据,否则返回旧的数据*/
    if (recv_data[0]+recv_data[1]+recv_data[2]+recv_data[3]==recv_data[4] ){
        temp_humid[0] = recv_data[0] + (float)recv_data[1]/10;  //湿度
        temp_humid[1] = recv_data[2] + (float)recv_data[3]/10;  //温度
    } else{
        printf("校验失败!\n");
//        return temp_humid;
    }
    printf("humidity   :%.1f\n", temp_humid[0]);
    printf("temperature:%.1f\n", temp_humid[1]);
    return temp_humid;
}
/*************************************************************************
BYTE ADDR R/W Desc.
0x00 R 湿度整数位
0x01 R 湿度小数位

0x02 R 温度整数位
0x03 R 温度小数位
0x04 R 校验和
*************************************************************************/

// 0:正常 1:打开设备错误 2:读取错误 3:数据校验错误
int thermograph_status_check(void)
{
    int fd;
    int status;
    char recv_data[5];
    fd=open("/dev/dht12",O_RDONLY);//打开文件
    if(fd<0){  //打开文件
        perror("open file failure!\n");
        status=1;
        return status;
    }
    status=read(fd, recv_data, 6);
    if(status!=6){
        printf("读取数据错误!\n");
        status=2;
        return status;
    }
    close(fd);
    /*计算校验和*/
    if (recv_data[0]+recv_data[1]+recv_data[2]+recv_data[3]==recv_data[4] ){
        status=0;
    } else{
        status=3;
        printf("校验失败!\n");
    }
    return status;
}