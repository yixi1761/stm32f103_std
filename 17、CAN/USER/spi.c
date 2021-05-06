# include "spi.h"

/*  declare internal reference Function */
u8 spi_sendreaddata(u8 senddata);
static u8 spi_busywaitting(void);
static void spi_pagewrite(u8 *buf,u32 startaddr,u16 length);
static void spi_erase_currentsector(u32 startaddr);
static void spi_directwrite(u8 *buf,u32 startaddr,u16 length);

void spi_cfg()
{		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOG,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOB,&GPIO_InitStructure);	
	//MISO
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	
	GPIO_Init(GPIOB,&GPIO_InitStructure);	
	//CS
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13;
	GPIO_Init(GPIOG,&GPIO_InitStructure);	
	GPIO_ResetBits(GPIOG,GPIO_Pin_13);
	
	SPI_InitTypeDef SPI_structure;
	SPI_structure.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
	SPI_structure.SPI_Mode=SPI_Mode_Master;
	SPI_structure.SPI_DataSize=SPI_DataSize_8b;
	SPI_structure.SPI_CPOL=SPI_CPOL_Low;
	SPI_structure.SPI_CPHA=SPI_CPHA_1Edge;
	SPI_structure.SPI_NSS=SPI_NSS_Soft;
	SPI_structure.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_256;
	SPI_structure.SPI_FirstBit=SPI_FirstBit_MSB;
	SPI_structure.SPI_CRCPolynomial=7;
	SPI_Init(SPI2,&SPI_structure);	
	SPI_Cmd(SPI2,ENABLE);
}

u8 spi_sendreaddata(u8 senddata)
{
	u8 retry=0; 
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE)==RESET)
	{
		retry++;
		if(retry>200)	
			return 1;
	}
	SPI_I2S_SendData(SPI2,senddata); 
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE)==RESET)
		{
		retry--;
		if(retry<1)	
			return 1;
		}
	return (SPI_I2S_ReceiveData(SPI2));
}

u8 spi_busywaitting()
{
	u8 time=0;
	spi_cs=0;
	do
	{
		if(time++>200)
			return 1;
	}
	while((spi_sendreaddata(W25X_ReadStatusReg)&0x01)==0x01);	
	spi_cs=1;
	return 0;
}

int spi_readID(void)
{	
	int id;
	spi_cs=0;
	spi_sendreaddata(W25X_ManufactDeviceID);	
	spi_sendreaddata(0xff);	
	spi_sendreaddata(0xff);
	spi_sendreaddata(0x00);
	
	id|=spi_sendreaddata(0xff)<<8;//(M7~m0)
	id|=spi_sendreaddata(0xff)<<8;//(ID7~ID0)		
	spi_cs=1;	
	return id;
}

 void spi_flashread(u8 *readbuf,u32 startaddr,u16 length)
 {
	 u16 i;
	 spi_cs=0;
 	 spi_sendreaddata(W25X_ReadData);	
	 spi_sendreaddata(startaddr>>16);
	 spi_sendreaddata(startaddr>>8);
	 spi_sendreaddata(startaddr);
	 while(length--)
	 {
		 readbuf[i++]=spi_sendreaddata(0xff);
	 }	 
	 spi_cs=1;	
 }
/****************************************************************************
* Function Name  : spi_pagewrite
* Description    : page write,less then one page(256Byte) every time
* Input          : none
* Output         : None
****************************************************************************/
 void spi_pagewrite(u8 *buf,u32 startaddr,u16 length)//less then one page(256Byte)
 {
	 u16 i;
	 spi_cs=0;
	 spi_sendreaddata(W25X_WriteEnable);
	 spi_sendreaddata(W25X_PageProgram);
	 spi_sendreaddata(startaddr>>16);
	 spi_sendreaddata(startaddr>>8);
	 spi_sendreaddata(startaddr);
	  for (i=0;i<length;i++)
	 {
		 spi_sendreaddata(buf[i]);
	 }	 
	 spi_busywaitting();
	 spi_cs=1;	
 }
   
 void spi_erase_currentsector(u32 startaddr)
 {
		spi_cs=0;
		spi_sendreaddata(W25X_SectorErase);
	  startaddr=startaddr-startaddr%4096;
		spi_sendreaddata(startaddr>>16);
		spi_sendreaddata(startaddr>>8);
		spi_sendreaddata(startaddr);
	  spi_busywaitting();
	  spi_cs=1;
 }
 
 void spi_directwrite(u8 *buf,u32 startaddr,u16 length)
 {
	 while(1)
		 {		
			 static int j=0;			 
			 if(length>256)
			 {				
				 spi_pagewrite(buf+j,startaddr,256);
				 length-=256;startaddr+=256;j+=256;
			 }			 
				else
					 spi_pagewrite(buf+j,startaddr,length);break;
			}	 
 }
  
 u8 spi_write(u8* buf,u32 startaddr,u16 length)
 {		 
	 //判断溢出
	 if(length+startaddr>8*1024*1024)
				return 1;
	 //计算需要擦除扇区个数
	 u16 sectornum;
	 if((length+startaddr)%4096!=0)
		 sectornum=(length+startaddr)/4096-startaddr/4096+1;
	 else
		 sectornum=(length+startaddr)/4096-startaddr/4096;
	 
	  u16 i;	
		u8 remain=startaddr%4096;
	  u8 tempbuf[remain];;	  
		//保护起始地址所在扇区之前的数据
	 spi_flashread(tempbuf,(startaddr-remain),remain);
	 //擦除所需扇区
	 for(i=0;i<sectornum;i++)
		 {
			 spi_erase_currentsector(startaddr+4096*i);
		 }
		 
	 spi_directwrite(tempbuf,(startaddr-remain),remain);
	 spi_directwrite(buf,startaddr,length);	 	
		return 0;
 }
 

