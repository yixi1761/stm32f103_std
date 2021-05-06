#include "IWDG.h"

void IWDG_Init(u8 fre,u16 Reload)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//取消写保护
  IWDG_SetPrescaler(fre);//预分频系数
  IWDG_SetReload(Reload);//重装载值 
	IWDG_ReloadCounter();//喂狗函数	，先喂一次
  IWDG_Enable();//使能函数	
}
