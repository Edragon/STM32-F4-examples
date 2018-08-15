#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "key.h"  
#include "malloc.h" 
#include "sdio_sdcard.h"
#include "spi.h"
#include "w25qxx.h"
 
//SD�� ʵ�� -�⺯���汾
//STM32F4����ģ��-�⺯���汾
//�Ա����̣�http://mcudev.taobao.com


//ͨ�����ڴ�ӡSD�������Ϣ
void show_sdcard_info(void)
{
	switch(SDCardInfo.CardType)
	{
		case SDIO_STD_CAPACITY_SD_CARD_V1_1:printf("Card Type:SDSC V1.1\r\n");break;
		case SDIO_STD_CAPACITY_SD_CARD_V2_0:printf("Card Type:SDSC V2.0\r\n");break;
		case SDIO_HIGH_CAPACITY_SD_CARD:printf("Card Type:SDHC V2.0\r\n");break;
		case SDIO_MULTIMEDIA_CARD:printf("Card Type:MMC Card\r\n");break;
	}	
  	printf("Card ManufacturerID:%d\r\n",SDCardInfo.SD_cid.ManufacturerID);	//������ID
 	printf("Card RCA:%d\r\n",SDCardInfo.RCA);								//����Ե�ַ
	printf("Card Capacity:%d MB\r\n",(u32)(SDCardInfo.CardCapacity>>20));	//��ʾ����
 	printf("Card BlockSize:%d\r\n\r\n",SDCardInfo.CardBlockSize);			//��ʾ���С
}



u32 FLASH_SIZE;


int main(void)
{        
	u8 key;		 
	u32 sd_size;
	u8 t=0;	
	u8 *buf;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	LED_Init();					//��ʼ��LED  
 	LCD_Init();					//LCD��ʼ��  
 	KEY_Init();					//������ʼ��  
	
	W25QXX_Init();			//W25QXX��ʼ��
	
	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ�� 
	my_mem_init(SRAMCCM);		//��ʼ��CCM�ڴ��
	
 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(30,50,200,16,16,"mcudev STM32F4");	
	LCD_ShowString(30,70,200,16,16,"STM32F407VET6 system TEST");	
	LCD_ShowString(30,90,200,16,16,"mcudev.taobao.com");
	LCD_ShowString(30,110,200,16,16,"2015/8/15");   
	LCD_ShowString(30,130,200,16,16,"KEY0:Read Sector 0");	   
 	while(SD_Init())//��ⲻ��SD��
	{
		LCD_ShowString(30,150,200,16,16,"SD Card Error!");
		delay_ms(500);					
		LCD_ShowString(30,150,200,16,16,"Please Check! ");
		delay_ms(500);
		LED0=!LED0;//DS0��˸
	}
	show_sdcard_info();	//��ӡSD�������Ϣ
 	POINT_COLOR=BLUE;	//��������Ϊ��ɫ 
	//���SD���ɹ� 											    
	LCD_ShowString(30,150,200,16,16,"SD Card OK......OK    ");
	LCD_ShowString(30,170,200,16,16,"SD Card Size:     MB");
	LCD_ShowNum(30+13*8,170,SDCardInfo.CardCapacity>>20,5,16);//��ʾSD������
	
  while(W25QXX_ReadID()!=W25Q16)								//��ⲻ��W25Q16
	{
		LCD_ShowString(30,190,200,16,16,"W25Q16 Check Failed!");
		delay_ms(500);
		LCD_ShowString(30,210,200,16,16,"Please Check!      ");
		delay_ms(500);
		LED1=!LED1;		//DS0��˸
	}
	LCD_ShowString(30,190,200,16,16,"W25Q16 OK.......OK!"); 
	FLASH_SIZE=16*1024*1024;	//FLASH ��СΪ2M�ֽ�
  POINT_COLOR=BLUE;			//��������Ϊ��ɫ	
	
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY0_PRES)//KEY0������
		{
			buf=mymalloc(0,512);		//�����ڴ�
			if(SD_ReadDisk(buf,0,1)==0)	//��ȡ0����������
			{	
				LCD_ShowString(30,190,200,16,16,"USART1 Sending Data...");
				printf("SECTOR 0 DATA:\r\n");
				for(sd_size=0;sd_size<512;sd_size++)printf("%x ",buf[sd_size]);//��ӡ0��������    	   
				printf("\r\nDATA ENDED\r\n");
				LCD_ShowString(30,190,200,16,16,"USART1 Send Data Over!");
			}
			myfree(0,buf);//�ͷ��ڴ�	   
		}   
		t++;
		delay_ms(10);
		if(t==20)
		{
			LED0=!LED0;
			LED1=!LED1;
			printf("SD Card: OK.......\r\n");
			printf("W25QXX Flash: OK.......\r\n");
			t=0;
		}
	} }





