#ifndef IO_CHECK_CTL_H_INCLUDED
#define IO_CHECK_CTL_H_INCLUDED

#include "util.h"
/*************************************************************************
 函数名称：	power_off_check
 功能说明：	输入电源断电检测.
 输入参数：	无
 返回参数：	0:电源正常 1:连续检测3s断电  -1:设备异常 -2:检测异常
 *************************************************************************/
int power_off_check(void);

/*************************************************************************
 函数名称：	door_check
 功能说明：	门磁开关检测.
 输入参数：	无
 返回参数：	0:关闭状态 1:连续检测3s打开状态; -1:设备异常 -2:两门磁状态不同
 *************************************************************************/
int door_check(void);



/*************************************************************************
 函数名称：	power_ctl
 功能说明：	220V市电开关.
 输入参数：	0:关闭 1:打开 -1:查询当前状态
 返回参数：	继电器状态 0:关闭  1:打开 -1:操作失败
 *************************************************************************/
int power_ctl(int cmd);

/*************************************************************************
 函数名称：	fan_ctl
 功能说明：	风扇开关.
 输入参数：	0:关闭 1:打开 -1:查询当前状态
 返回参数：	继电器状态 0:关闭  1:打开 -1:操作失败
 *************************************************************************/
int fan_ctl(int cmd);

/*************************************************************************
 函数名称：	alarm_ctl
 功能说明：	报警开关.
 输入参数：	0:关闭 1:打开 -1:查询当前状态
 返回参数：	继电器状态 0:关闭  1:打开 -1:操作失败
 *************************************************************************/
int alarm_ctl(int cmd);


#endif // IO_CHECK_CTL_H_INCLUDED



