#include <stdio.h>
#include"hlw8032.h"

static uint64_t tick = 0;

int main()
{
    printf("hello1!\n");
    voltameter_init();
    while(1){
        if (1 == get_is_timeout(&tick, 500)) {
            powerCheck();
        }
//        voltameter_status_check();
//        if (1 == get_is_timeout(&tick, 1000)){
//            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~状态值:%d\n", voltameter.status);
//            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~电压值:%.2f\n", voltameter.voltage);
//            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~电流值:%.3f\n", voltameter.current);
//            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~功率值:%.4f\n", voltameter.power_factor);
//            printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~电量值:%.4f\n", voltameter.power_consumption);
//        }
    }
}