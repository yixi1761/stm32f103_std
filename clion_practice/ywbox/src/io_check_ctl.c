#include"../head/io_check_ctl.h"
#include <unistd.h>
#include <string.h>
#include "../util/util.h"

int main()
{
    printf("hello!\n");
    while(1){
        power_ctl(0); sleep(1);    printf("status: %d\n",power_ctl(-1))  ;
        power_ctl(1); sleep(1);    printf("status: %d\n",power_ctl(-1));
        fan_ctl(0); sleep(1);   printf("status: %d\n",fan_ctl(-1));
        fan_ctl(1); sleep(1);   printf("status: %d\n",fan_ctl(-1));
        alarm_ctl(0); sleep(1); printf("status: %d\n",alarm_ctl(-1));
        alarm_ctl(1); sleep(1); printf("status: %d\n",alarm_ctl(-1));
        int status;
        status = power_off_check();
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~PowerOff status:%d\n",status);
        status = door_check();
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~door status:%d\n",status);sleep(1);
    }
}

/*************************************************************************
 功能说明：	继电器写入操作.
 输入参数：	path:操作的继电器 cmd:打开/关闭
 返回参数：	-1:设备异常 -2:写入错误 1:操作成功
 *************************************************************************/
int relay_write(char* path,int cmd)
{
    char open_cmd[]="ON";
    char close_cmd[]="OFF";
    int fd;
    size_t rel_size=-1;

    fd=open(path, O_WRONLY);
    if(fd<0){
        printf("error!无法打开设备\n");
        return -1;
    }
    if (cmd == 0){
        rel_size = write(fd, open_cmd, 3);
        if(rel_size != 3)
            rel_size = write(fd, open_cmd, 3);
    } else if(cmd == 1){
        rel_size = write(fd, close_cmd, 4);
        if (rel_size != 4) {
            rel_size = write(fd, close_cmd, 4);
        }
    }
    if(rel_size < 0){
        printf("写入错误! %d\n",rel_size);
        return -2;
    }
    close(fd);
    return 1;
}

/*************************************************************************
 功能说明：	记录异常状态持续时间
 输入参数：	flag==0记录开始  flag!=0记录
 返回参数：	记录时间,单位ms
 *************************************************************************/
int anomaly_time_count(int flag)
{
    struct timespec ts;
    static uint64_t start_time=0;
    uint64_t open_time;
    printf("flag:%d\n",flag);

    if(flag==0){
        printf("开始计时\n");
        clock_gettime(CLOCK_MONOTONIC, &ts);
        start_time=(ts.tv_sec* 1000 + ts.tv_nsec / 1000000);
        open_time=0;
    } else{
        clock_gettime(CLOCK_MONOTONIC, &ts);
        open_time=(ts.tv_sec* 1000 + ts.tv_nsec/1000000)-start_time;
    }
//    printf("opentime :%ld\n",open_time);
    return open_time;
}

#define POWER_OFF_CHECK_NAME "/dev/pwr_off"
// 返回参数：	0:电源正常 1:连续检测3s断电  -1:设备异常 -2:检测异常 -3:读取数据错误
int power_off_check(void)
{
    int fd ;
    char status;
    static int flag = 0;

    fd = open("/dev/pwr_off", O_RDONLY);
    if((fd<0)||(1!=read(fd, &status, 1))){
        //无法打开设备 或 无法读取
        return -1;
    }
    close(fd);
    if(status == 49){
        flag = 0;
//        printf("power_off实时状态:正常\n");
    }else if(status == 48){
        uint64_t open_time = anomaly_time_count(flag);
        flag=1;
        printf("power_off实时状态:断电 %ld ms\n",open_time);
        if (open_time>3000)  //断电3s
            return 1;
    }else{
        printf("power_off实时检测:异常 %d\n",status);
        return -2;
    }
    return 0;   //正常
}

/*************************************************************************
 函数名称：	door_check
 功能说明：	门磁开关检测.
 输入参数：	无
 返回参数：	0:关闭状态 1:连续检测3s打开状态; -1:设备异常 -2:两门磁状态不同
 *************************************************************************/
int door_check(void)
{
    int fd ;
    char status[2];
    static int flag = 0;

    //门磁1
    fd = open("/dev/door1", O_RDONLY);
    if((fd<0)||(2!=read(fd, &status, 2))){
        //无法打开设备 或 无法读取
        return -1;
    }
    close(fd);
    printf("门磁1: %c\n",status[0]);
    //门磁2
    fd = open("/dev/door2", O_RDONLY);
    if((fd<0)||(2!=read(fd, &status, 2))){
        //无法打开设备 或 无法读取
        return -1;
    }
    close(fd);
    printf("门磁2: %c\n",status[1]);

    if(status[0]==48&&status[1]==48){
        printf("DOOR实时状态:关闭\n");
        flag = 0;
    }else if(status[0]==49&&status[1]==49){
        uint64_t open_time = anomaly_time_count(flag);
        flag=1;
        printf("DOOR实时状态:打开 %ld ms\n",open_time);
        if (open_time>3000)  //断电3s,返回断电
            return 1;
    }else{
        printf("门磁异常\n");
        return -2;
    }
    return 0;
}

/*************************************************************************
 函数名称：	power_ctl
 功能说明：	220V市电开关.
 输入参数：	0:关闭 1:打开 -1:查询当前状态
 返回参数：	继电器状态 0:关闭 1:打开 -1:操作失败
 *************************************************************************/
int power_ctl(int cmd)
{
    static int status=0;
    if(cmd==-1)
        return status;
    char path[]="/dev/relay1";
    printf("AC:");
    if( relay_write(path,cmd)<0 ){
        if( relay_write(path,cmd)<0)
            return -1;
    }
    if(cmd==0){
        status=0;
    } else if(cmd==1){
        status=1;
    }
    printf("%d\n",status);
    return status;
}

int fan_ctl(int cmd)
{
    static int status=0;
    if(cmd==-1)
        return status;
    char path[]="/dev/relay2";
    printf("FAN:");
    if( relay_write(path,cmd)<0 ){
        if( relay_write(path,cmd)<0)
            return -1;
    }
    if(cmd==0){
        status=0;
    } else if(cmd==1){
        status=1;
    }
    printf("%d\n",status);
    return status;
}

int alarm_ctl(int cmd)
{
    static int status=0;
    if(cmd==-1)
        return status;
    char path[]="/dev/relay3";
    printf("ALR:");
    if( relay_write(path,cmd)<0 ){
        if( relay_write(path,cmd)<0)
            return -1;
    }
    if(cmd==0){
        status=0;
    } else if(cmd==1){
        status=1;
    }
    printf("%d\n",status);
    return status;
}


