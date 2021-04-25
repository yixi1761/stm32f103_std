#ifndef __THERM_H
#define __THERM_H

#include "util.h"

/*************************************************************************
 函数名称：	temp_humid_get
 功能说明：	读取DHT12温湿度数据.
 输入参数：	无
 返回参数：	温湿度数据数组,temp_humid[0]:湿度  temp_humid[1]:温度.
 *************************************************************************/
float* temp_humid_get(void);

/*************************************************************************
 函数名称：	thermograph_status_check
 功能说明：	检查DHT12温湿度计状态.
 输入参数：	无
 返回参数：	0:正常 1:打开设备错误 2:读取错误 3:数据校验错误
 *************************************************************************/
int thermograph_status_check(void);

#endif
