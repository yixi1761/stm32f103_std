#include "IWDG.h"

void IWDG_Init(u8 fre,u16 Reload)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//ȡ��д����
  IWDG_SetPrescaler(fre);//Ԥ��Ƶϵ��
  IWDG_SetReload(Reload);//��װ��ֵ 
	IWDG_ReloadCounter();//ι������	����ιһ��
  IWDG_Enable();//ʹ�ܺ���	
}
