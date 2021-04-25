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
    fd=open("/dev/dht12",O_RDONLY);//���ļ�
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
    /*����У��� OK��������,���򷵻ؾɵ�����*/
    if (recv_data[0]+recv_data[1]+recv_data[2]+recv_data[3]==recv_data[4] ){
        temp_humid[0] = recv_data[0] + (float)recv_data[1]/10;  //ʪ��
        temp_humid[1] = recv_data[2] + (float)recv_data[3]/10;  //�¶�
    } else{
        printf("У��ʧ��!\n");
//        return temp_humid;
    }
    printf("humidity   :%.1f\n", temp_humid[0]);
    printf("temperature:%.1f\n", temp_humid[1]);
    return temp_humid;
}
/*************************************************************************
BYTE ADDR R/W Desc.
0x00 R ʪ������λ
0x01 R ʪ��С��λ

0x02 R �¶�����λ
0x03 R �¶�С��λ
0x04 R У���
*************************************************************************/

// 0:���� 1:���豸���� 2:��ȡ���� 3:����У�����
int thermograph_status_check(void)
{
    int fd;
    int status;
    char recv_data[5];
    fd=open("/dev/dht12",O_RDONLY);//���ļ�
    if(fd<0){  //���ļ�
        perror("open file failure!\n");
        status=1;
        return status;
    }
    status=read(fd, recv_data, 6);
    if(status!=6){
        printf("��ȡ���ݴ���!\n");
        status=2;
        return status;
    }
    close(fd);
    /*����У���*/
    if (recv_data[0]+recv_data[1]+recv_data[2]+recv_data[3]==recv_data[4] ){
        status=0;
    } else{
        status=3;
        printf("У��ʧ��!\n");
    }
    return status;
}