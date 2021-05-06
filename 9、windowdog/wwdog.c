#include "wwdg.h"

void wwdg_nvic_init()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel=WWDG_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;	
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;		
	NVIC_Init(&NVIC_InitStructure);
}

void wwdg_int()
{
	wwdg_nvic_init();
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);	
	WWDG_SetPrescaler(WWDG_Prescaler_8);
	WWDG_SetWindowValue(0x70);
	WWDG_EnableIT();		
	
	WWDG_Enable(0x70);
}



