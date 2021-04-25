//
// Created by Ansel on 2018/12/7.
//

#ifndef __VOLTAMETER_H
#define __VOLTAMETER_H

struct volt {
    int status;     //0:正常 1:无法读取 2:接收校验失败
    float current;
    float voltage;
    float power_factor;
    float power_consumption;
};


/*************************************************************************
 函数名称：	powerCheck
 功能说明：	读取解析4个电量参数,保存结构体voltameter里面.
 输入参数：	无
 返回参数：	&voltameter
 *************************************************************************/
struct volt powerCheck(void);

/*************************************************************************
 函数名称：	voltameter_init
 功能说明：	初始化电量计串口.
 输入参数：	无
 返回参数：	0:异常 fd:串口句柄
 *************************************************************************/
int voltameter_init(void);

/*************************************************************************
 函数名称：	voltameter_status_check
 功能说明：	获取电量计状态.
 输入参数：	无
 返回参数：	0:正常 1:无法读取 2:接收校验失败
 *************************************************************************/
int voltameter_status_check(void);
#endif  //__VOLTAMETER_H
