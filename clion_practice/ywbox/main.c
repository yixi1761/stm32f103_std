#include <stdio.h>
#include "head/io_check_ctl.h"
#include "head/led_display.h"
#include "head/util.h"
#include "head/voltameter.h"
#include "head/temperature.h"


int main()
{
    printf("hello!\n");
    voltameter_init();
    while(1) {
//        power_ctl(0);
//        sleep(1);
//        printf("status: %d\n", power_ctl(-1));
//        power_ctl(1);
//        sleep(1);
//        printf("status: %d\n", power_ctl(-1));
//        fan_ctl(0);
//        sleep(1);
//        printf("status: %d\n", fan_ctl(-1));
//        fan_ctl(1);
//        sleep(1);
//        printf("status: %d\n", fan_ctl(-1));
//        alarm_ctl(0);
//        sleep(1);
//        printf("status: %d\n", alarm_ctl(-1));
//        alarm_ctl(1);
//        sleep(1);
//        printf("status: %d\n", alarm_ctl(-1));
        int status;
        status = power_off_check();
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~PowerOff status:%d\n", status);
        status = door_check();
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~door status:%d\n", status);
        sleep(1);

        char a[]="111111";
        char b[]="888999";
        led_display(a); sleep(1);
        led_display(b); sleep(1);

        temp_humid_get();
        status = thermograph_status_check();
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~thermograph status:%d\n", status);


        printf("Hello, World!\n");
        voltameter_init();
        while (1) {
            powerCheck();
        }
    }
}
