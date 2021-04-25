#ifndef LED_DISPLAY_INCLUDED
#define LED_DISPLAY_INCLUDED

#include <stdio.h>
#include <string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

/*************************************************************************
 函数名称：	led_display
 功能说明：	显示输入的数字.
 输入参数：	6位数字
 返回参数：	-1:设备异常 -2:写入失败 1:操作成功
 *************************************************************************/
int led_display(char *data);

#endif // DIG_DISPLAY_INCLUDED
