#include "hlw8032.h"

//static struct volt voltameter;
static int fd;
static uint64_t updata_count = 0;
static uint64_t tick = 0;

/*************************************************************************
 * 初始化电量计
 * 返回参数：	   -1:异常 fd:串口句柄
 *************************************************************************/
int voltameter_init()
{
    fd = uart_block_init("/dev/ttyS4", 4800, 0, 8, 1, 'E');   //初始化串口
    if(fd<0){       //串口打开失败
        fd = uart_block_init("/dev/ttyS4", 4800, 0, 8, 1, 'E');
        if(fd<0){
            printf("串口打开失败\n");
            return -1;
        }
    }
    return fd;
}

/*************************************************************************
 * 解析电量
 * 传入参数: 数据帧
 * 返回参数：	   无
 *************************************************************************/
void calculate_pwr(char* recv_data)
{
    static int power_flag = 0; //电量溢出翻转标志位
    //计算电压值
    float voltage_data = (
            1.88 * 188200 / (
                    ((int) (recv_data[5] >> 4)) * 1048576 +
                    ((int) (recv_data[5] & 0x0f)) * 65536 +
                    ((int) (recv_data[6] >> 4)) * 4096 +
                    ((int) (recv_data[6] & 0x0f)) * 256 +
                    ((int) (recv_data[7] >> 4)) * 16 +
                    ((int) (recv_data[7] & 0x0f)) * 1
            )
    );
    voltameter.voltage = voltage_data;
//    printf(" 原始电压值:%.2fV\n", voltage_data);

// 解析电流值
    float current_data = (
            15955.0 / (
                    ((int) (recv_data[11] >> 4)) * 1048576 +
                    ((int) (recv_data[11] & 0x0f)) * 65536 +
                    ((int) (recv_data[12] >> 4)) * 4096 +
                    ((int) (recv_data[12] & 0x0f)) * 256 +
                    ((int) (recv_data[13] >> 4)) * 16 +
                    ((int) (recv_data[13] & 0x0f)) * 1
            )
    );
    voltameter.current = current_data;
//    printf(" 原始电流:%.3fA\n", current_data);
// 解析功率
    float factor_data = (
            1.88 * 5174000 / (
                    ((int) (recv_data[17] >> 4)) * 1048576 +
                    ((int) (recv_data[17] & 0x0f)) * 65536 +
                    ((int) (recv_data[18] >> 4)) * 4096 +
                    ((int) (recv_data[18] & 0x0f)) * 256 +
                    ((int) (recv_data[19] >> 4)) * 16 +
                    ((int) (recv_data[19] & 0x0f)) * 1
            )
    );
    voltameter.power_factor = factor_data;
//    printf(" 原始功率:%.4f W\n", factor_data);
// 解析电量
// PF寄存器溢出,计数加1, 更新标志位
    if (recv_data[20] >> 7 != power_flag) {
        power_flag = recv_data[20] >> 7;
        updata_count += 1;
    }
    float consumption_data = (
            (updata_count * 65536 +
             ((int) (recv_data[21] >> 4)) * 4096 +
             ((int) (recv_data[21] & 0x0f)) * 256 +
             ((int) (recv_data[22] >> 4)) * 16 +
             ((int) (recv_data[22] & 0x0f)) * 1
            ) * 972712 / 36e10
    );
    voltameter.power_consumption = consumption_data;
    voltameter.status = 0;
//    printf(" 原始电量:%.4f KWh\n", consumption_data);
}

struct volt powerCheck(void)
{
    char buf[24];
    static char recv_data[130];
    static int data_len=0;
    char sum = 0;
    int len, i, j;
    int flag=0;
    //接收,返回数据长度，未接收到数据返回-1,参数错误返回-2。
    len = uart_block_recv(fd, buf, 24, 50);//阻塞50ms
    printf("len : %d   ", len);
    if (len <= 0) {
        return voltameter;
    } else {
        for(i=0;i<len;i++){
            printf("%x ",buf[i]);
        }
        printf("\n");

        memcpy(recv_data + data_len,buf,len);
        data_len += len;
        printf("memcopy -- data_len %d\n", data_len);
    }

    if(data_len > 47){
    // 遍历数据,找出帧头,丢掉前面不匹配的数据
        for (i = 0; i < 24; i++) {
            if (recv_data[i + 1] == 0x5A && recv_data[i + 2] == 0x02 && recv_data[i + 3] == 0xDF && recv_data[i + 4] == 0x28) {
                // recv_data 左移i位
                for (j = 0; j < (data_len - i); j++) {
                    recv_data[j] = recv_data[j+i];
                    printf(" %x",recv_data[j]);
                }
                printf("\n");

                data_len -= i;
                flag = 1;
                break;
            }
        }

        /****************************************************************************/
        if(flag == 1 ){
            // 计算校验和
            printf("数据帧: %x %x",recv_data[0],recv_data[1]);
            for (i = 2; i < 23; i++) {
                sum += recv_data[i];
                printf(" %x",recv_data[i]);
            }
            printf(" %x",recv_data[23]);
            printf("   sum= %x \n", sum);

            if(recv_data[23] == sum){
//                calculate_pwr(recv_data);
                // recv_data 左移24位
                for(i=0;i<data_len-24;i++) {
                    recv_data[i] = recv_data[i+24];
                }
                data_len -= 24;
                printf("data_len %d\n", data_len);

            } else {
                printf("数据校验失败!\n");
                voltameter.status = 2;
            }

        } else{
            printf("未找到帧头 !\n");

        }

        /****************************************************************************/
    }

    if(data_len>96){
        data_len = 0;
    }
    return voltameter;
}
        /*
        if(flag == 1 && data_len >24){
            // 计算校验和
            printf("数据帧: %x %x",recv_data[0],recv_data[1]);
            for (i = 2; i < 23; i++) {
                sum += recv_data[i];
                printf(" %x",recv_data[i]);
            }
            printf(" %x",recv_data[23]);
            printf("\n");
            printf("sum = %x \n", sum);

            if(recv_data[23] == sum){
                calculate_pwr(recv_data);
                // recv_data 左移24位
                for(i=0;i<data_len-24;i++) {
                    recv_data[i] = recv_data[i+24];
//            printf("recv_data %x ", recv_data[i]);
                }
                data_len -= 24;
            } else {
                printf("数据校验失败!\n");
                voltameter.status = 2;
            }

        } else{
            printf("data_length %x\n", data_len);
            // recv_data 左移24位
            for(i=0;i<data_len-24;i++) {
                recv_data[i] = recv_data[i+24];
                printf("recv_data %x ", recv_data[i]);
            }
            data_len -= 24;
        }
*/


/*************************************************************************
 函数名称：	voltameter_status_check
 功能说明：	获取电量计状态.
 输入参数：	无
 返回参数：	0:正常 1:无法读取 2:接收校验失败
 *************************************************************************/
int voltameter_status_check(void)
{
    printf("电量计状态 %d\n",voltameter.status);
    return voltameter.status;
}
