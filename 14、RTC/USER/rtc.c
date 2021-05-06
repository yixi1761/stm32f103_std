# include "rtc.h"
#include "led.h"

calendartypedef calendarstruct;
static void rtc_nvic()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=RTC_IRQn;//the IT functions is in stm32f10x.h??
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;//qiang zan you xian ji:0~3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;	
	NVIC_Init(&NVIC_InitStructure);	
}
u8 rtc_init(void)
{	
	if(BKP_ReadBackupRegister(BKP_DR1)!=0x5050)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP,ENABLE);
		PWR_BackupAccessCmd(ENABLE);
		BKP_DeInit();
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		//config the LSE clock
		RCC_LSEConfig(RCC_LSE_ON);delay_simple(10000);	
		u8 temp=0;
		while(RCC_GetFlagStatus(RCC_FLAG_LSERDY)==RESET&&temp<250)
		{			
			temp++;
			delay_simple(1000);			
		}
		if(temp>=250)
		{
			printf("超时!\r\n");
			return 1;
		}
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
		RCC_RTCCLKCmd(ENABLE);
		RTC_WaitForLastTask();
		RTC_WaitForSynchro();
		RTC_ITConfig(RTC_IT_SEC,ENABLE);
		RTC_WaitForLastTask();
		RTC_ExitConfigMode();
		RTC_SetPrescaler(32767);
		RTC_WaitForLastTask();
		RTC_SetCounter(0);
		RTC_ExitConfigMode();		
		printf ("\n4\n");
		BKP_WriteBackupRegister(BKP_DR1,0x5050);		
	}
	else
	{
		RTC_WaitForSynchro();
		RTC_ITConfig(RTC_IT_SEC,ENABLE);
		RTC_WaitForLastTask();
	}	
	rtc_nvic();
	return 0;
}

void RTC_IRQHandler()
{
	if(RTC_GetITStatus(RTC_IT_SEC))
	{
		RTC_ClearITPendingBit(RTC_IT_SEC);
		LED2=~LED2;
		rtc_get();
		printf("TIME:%d / %d / %d  %d:%d:%d\n",calendarstruct.year,calendarstruct.month,calendarstruct.day,
																						calendarstruct.hour,calendarstruct.minute,calendarstruct.second);
	}
}

u8 rtc_set(u16 year,u8 month,u8 day,u8 h,u8 m,u8 s)
{
	//from 1990,1,1,0:0:0 to 2126,1,1,0:0:0
	if((year<1990)|(year>2126))
		return 1;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	//calcute the seconds
	u16 runyear=0;
	u32 seconds=0;
	u16 temp;
	year-=1990;	
	
	const u8 mon[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	//calculate how many leap years
	for (temp=1990;temp<=((month>=2&&day>=29)? year:(year-1));temp++)
		{
			if((year%400==0)|(year%100!=0&&year%4==0))
					runyear++;		
		}
	for(temp=0;temp<month;temp++)
		{
			seconds+=mon[temp]*86400;
		}
		seconds+=year*31536000+(day+runyear)*86400+h*3600+m*60+s;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR|RCC_APB1Periph_BKP,ENABLE);
		PWR_BackupAccessCmd(ENABLE);
		RTC_SetCounter(seconds);
		RTC_WaitForLastTask();
		return 0;
}

u8 rtc_get()
{
	u32 seconds;	
	u16 year,month,day,h,m,s,days;
	year=1990;
	u8 mon[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	seconds=RTC_GetCounter();	

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	days=seconds/86400;
	while(days>=365)
	{		
		if((year%400==0)|(year%100!=0&&year%4==0))
		{
			if(days>=366)
			{				
				day-=366;
			}		
			else
				break;
		}
		else
		{
			days-=365;
		}
		year++;
	}
	if((year%400==0)|(year%100!=0&&year%4==0))
			mon[1]=29;
	for(month=0;days>0;)
	{		
		if(days-mon[month]>0)
		{
			month++;
			days-=mon[month];
		}
		else
		{
			day=days;
			days=0;
		}
	}	
	seconds=seconds%86400;
	h=seconds/3600;
	m=seconds%3600/60;
	s=seconds%60;	
	calendarstruct.year=year;
	calendarstruct.month=month;
	calendarstruct.day=day;
	calendarstruct.hour=h;
	calendarstruct.minute=m;
	calendarstruct.second=s;
	return 0;
}




