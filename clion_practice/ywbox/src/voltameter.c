#include "../head/voltameter.h"
static int fd;
int main() {
    printf("hello1!\n");
    voltameter_init();
    while(1){
        powerCheck();
//        voltameter_status_check();
    }

}
/*************************************************************************
 * 初始化电量计
 * 返回参数：	   -1:异常 fd:串口句柄
 *************************************************************************/
int voltameter_init()
{
    fd = uart_block_init("/dev/ttyS4", 2400, 0, 8, 1, 'E');   //初始化串口
    if(fd<0){       //串口打开失败
        fd = uart_block_init("/dev/ttyS4", 2400, 0, 8, 1, 'E');
        if(fd<0){
            printf("串口打开失败\n");
            return -1;
        }
    }
    return fd;

}

struct volt powerCheck(void)
{
    static uint64_t tick = 0;
    if ( 1!= get_is_timeout(&tick, 1000))   //计时未超过1s 不更新电量数据
        return voltameter;

    const char cmd_data[] = {0x68,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0x68,0x11,0x04,0x33,0x34,0x42,0x35,0xBF,0x16};
    char recv_data[28];
    char sum = 0,i;
    int status ;
    //第一次运行只发送不接收
    static int step=0;
    if(step<0){
        step++;
        printf("step %d\n",step);
        return voltameter;
    }
    if (step==0){
        status = uart_send(fd, cmd_data, 16);
        if(status!=16){
            printf("uart_send error %d\n",status);
            for (i=0;i<status;i++){
                printf("%x ",cmd_data[i]);
            }
            printf("\n");
            return voltameter;
        }
        step++;
        return voltameter;
    }

    //返回数据长度，未接收到数据返回-1,参数错误返回-2。
    status = uart_block_recv(fd, recv_data, 28, 100);
    if( status!=28 ) {
        printf("!!!!!!!!!接收电量错误! %d\n",status);
        voltameter.status=1;
        for (i=0;i<status;i++){
            printf("%x ",cmd_data[i]);
        }
        printf("\n");
        printf("step=%d\n",step);
        step=-2;
        return voltameter;
    }
    //计算校验和
    for (i=0;i<26;i++){
        sum += recv_data[i];
        printf("%x ",recv_data[i]);
    }
    printf("%x %x\n",recv_data[26],recv_data[27]);
    //数据校验
    if((recv_data[0]==0x68)&&(recv_data[7]==0x68)&&(recv_data[8]==0x91)&&(recv_data[27]==0x16)&&(recv_data[26]==sum)) {
        //计算电压值
        float voltage_data = (
                (float) ((recv_data[15] - 0x33) >> 4) * 100 +
                (float) ((recv_data[15] - 0x33) & 0x0f) * 10 +
                (float) ((recv_data[14] - 0x33) >> 4) +
                (float) ((recv_data[14] - 0x33) & 0x0f) / 10
        );
        voltameter.voltage = voltage_data;
        printf(" 原始电压值:%.1fV\n", voltage_data);
        // 解析电流值
        float current_data = (
                (float) ((recv_data[18] - 0x33) >> 4) * 100 +
                (float) ((recv_data[18] - 0x33) & 0x0f) * 10 +
                (float) ((recv_data[17] - 0x33) >> 4) +
                (float) ((recv_data[17] - 0x33) & 0x0f) / 10 +
                (float) ((recv_data[16] - 0x33) >> 4) / 100 +
                (float) ((recv_data[16] - 0x33) & 0x0f) / 1000
        );
        voltameter.current = current_data;
        printf(" 原始电流:%.3fA\n", current_data);
        // 解析功率
        float factor_data = (
                (float) ((recv_data[21] - 0x33) >> 4) * 10 +
                (float) ((recv_data[21] - 0x33) & 0x0f) +
                (float) ((recv_data[20] - 0x33) >> 4)/10 +
                (float) ((recv_data[20] - 0x33) & 0x0f) / 100 +
                (float) ((recv_data[19] - 0x33) >> 4) / 1000 +
                (float) ((recv_data[19] - 0x33) & 0x0f) / 10000
        );
        voltameter.power_factor = factor_data;
        printf(" 原始功率:%.4f KW\n", factor_data);
        // 解析电量
        float consumption_data = (
                (float) ((recv_data[25] - 0x33) >> 4) * 100000 +
                (float) ((recv_data[25] - 0x33) & 0x0f) * 10000 +
                (float) ((recv_data[24] - 0x33) >> 4) * 1000 +
                (float) ((recv_data[24] - 0x33) & 0x0f) * 100 +
                (float) ((recv_data[23] - 0x33) >> 4) * 10 +
                (float) ((recv_data[23] - 0x33) & 0x0f) +
                (float) ((recv_data[22] - 0x33) >> 4) / 10 +
                (float) ((recv_data[22] - 0x33) & 0x0f) / 100
        );
        voltameter.power_consumption = consumption_data;
        voltameter.status=0;
        printf(" 原始电量:%.2f KWh\n", consumption_data);
    } else{
        printf("数据校验失败!");
        voltameter.status=2;
    }
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~状态值:%d\n",voltameter.status);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~电压值:%.1f\n",voltameter.voltage);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~电流值:%.3f\n",voltameter.current);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~功率值:%.4f\n",voltameter.power_factor);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~电量值:%.2f\n",voltameter.power_consumption);

    status = uart_send(fd, cmd_data, 16);
    if(status!=16){
        printf("uart_send error %d\n",status);
        step=0;
        printf("uart_send: ");
        for (i=0;i<16;i++){
            printf("%x ",cmd_data[i]);
        }
        printf("\n");
        return voltameter;
    }

    //记录进程运行时间
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC , &ts);
    printf("开机时间: %ld 分 %ld 秒\n" ,ts.tv_sec/60,ts.tv_sec%60);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID , &ts);
    printf("运行时间: %ld 分 %ld 秒\n" ,ts.tv_sec/60,ts.tv_sec%60);
    return voltameter;
}

/*************************************************************************
 函数名称：	voltameter_status_check
 功能说明：	获取电量计状态.
 输入参数：	无
 返回参数：	0:正常 1:无法读取 2:接收校验失败
 *************************************************************************/
int voltameter_status_check(void)
{
    static uint64_t tick = 0;
    if ( 1!= get_is_timeout(&tick, 1000))
        return voltameter.status;

    printf("电量计状态 %d\n",voltameter.status);
    return voltameter.status;
}