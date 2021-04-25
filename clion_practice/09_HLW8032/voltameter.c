#include "voltameter.h"
#include "util.h"

static struct volt voltameter;
static const char cmd_data[] = {0x68,0xAA,0xAA,0xAA,0xAA,0xAA,0xAA,0x68,0x11,0x04,0x33,0x34,0x42,0x35,0xBF,0x16};
static int fd;
static uint64_t tick = 0;
#define DATA_MAX_LEN 28
  
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
int voltameter_init(void)
{
    fd = uart_block_init("/dev/ttyS4", 2400, 0, 8, 1, 'E');   //初始化串口
    if(fd < 0){       //串口打开失败
        fd = uart_block_init("/dev/ttyS4", 2400, 0, 8, 1, 'E');
        if(fd<0){
            printf("串口打开失败\n");
            return -1;
        }
    }
	
	uart_send(fd, cmd_data, sizeof(cmd_data));
   
	get_is_timeout(&tick, 1);
	
    return fd;
}

struct volt powerCheck(void)
{   
    static char recv_data[128];
	static int status,data_len;
	
	char buf[DATA_MAX_LEN];
    char sum = 0;
    int len,i;
	   
    if (get_is_timeout(&tick, 1000)) {   	
		uart_send(fd, cmd_data, sizeof(cmd_data));		
	}
 
    len = uart_block_recv(fd, buf, DATA_MAX_LEN, 50);//阻塞50ms
     
	if (len > 0) {
		memcpy(recv_data + data_len,buf,len);
		data_len += len;
		
		//printf("len:%d,data_len:%d\n",len,data_len);
		
		if (status == 0 && data_len > 2 && recv_data[0] == 0x68 && recv_data[1] == 0x01) {			
			status = 1;
		}
		
		if (status == 1 && data_len >= DATA_MAX_LEN) {
			for (i=0;i<26;i++){//计算校验和
				sum += recv_data[i];
				printf("%x ",recv_data[i]);
			}
			
			printf("checksum:%x %x\n",recv_data[26],recv_data[27]);
									
			if((recv_data[0]==0x68)&&(recv_data[7]==0x68)&&(recv_data[8]==0x91)&&(recv_data[27]==0x16)&&(recv_data[26]==sum)) {//数据校验
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
			} else {
				printf("数据校验失败!");
				voltameter.status=2;
			}
			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~状态值:%d\n",voltameter.status);
			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~电压值:%.1f\n",voltameter.voltage);
			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~电流值:%.3f\n",voltameter.current);
			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~功率值:%.4f\n",voltameter.power_factor);
			printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~电量值:%.2f\n",voltameter.power_consumption);
					
			for(i=0;i<data_len-28;i++) {
				recv_data[i] = recv_data[i+28];				
			}
			
			data_len -= 28;		
		}
		
		if (data_len >= 100) {
			data_len= 0;
		}
		status = 0;
	}
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


