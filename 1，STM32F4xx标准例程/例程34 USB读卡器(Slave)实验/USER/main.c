#include "sys.h"
#include "delay.h"  
#include "usart.h"   
#include "led.h"
#include "lcd.h"
#include "key.h"   
#include "malloc.h" 
#include "w25qxx.h"    
#include "sdio_sdcard.h"    
#include "usbd_msc_core.h"
#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usb_conf.h" 

 
//USB������ ʵ�� -�⺯���汾
//STM32F4����ģ��-�⺯���汾
//�Ա����̣�http://mcudev.taobao.com	
 

USB_OTG_CORE_HANDLE USB_OTG_dev;
extern vu8 USB_STATUS_REG;		//USB״̬
extern vu8 bDeviceState;		//USB���� ���
 
int main(void)
{        
	u8 offline_cnt=0;
	u8 tct=0;
	u8 USB_STA;
	u8 Divece_STA;


	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	LED_Init();					//��ʼ��LED  
 	LCD_Init();					//LCD��ʼ��  
 	KEY_Init();					//������ʼ��  
	W25QXX_Init();				//��ʼ��W25Q16  
  
 	POINT_COLOR=RED;//��������Ϊ��ɫ	   
	LCD_ShowString(30,50,200,16,16,"Mcudev STM32F4");	
	LCD_ShowString(30,70,200,16,16,"USB Card Reader TEST");	
	LCD_ShowString(30,90,200,16,16,"mcudev.taobao.com");
	LCD_ShowString(30,110,200,16,16,"2015/9/5");	
	if(SD_Init())LCD_ShowString(30,130,200,16,16,"SD Card Error!");	//���SD������
	else //SD ������
	{   															  
		LCD_ShowString(30,130,200,16,16,"SD Card Size:     MB"); 
 		LCD_ShowNum(134,130,SDCardInfo.CardCapacity>>20,5,16);	//��ʾSD������
 	}
	if(W25QXX_ReadID()!=W25Q16)LCD_ShowString(30,130,200,16,16,"W25Q16 Error!");	//���W25Q128����
	else //SPI FLASH ����
	{   														 
		LCD_ShowString(30,150,200,16,16,"SPI FLASH Size:2MB");	 
	}  
 	LCD_ShowString(30,170,200,16,16,"USB Connecting...");//��ʾ���ڽ������� 	    
	USBD_Init(&USB_OTG_dev,USB_OTG_FS_CORE_ID,&USR_desc,&USBD_MSC_cb,&USR_cb);
	delay_ms(1800);	
	while(1)
	{	
		delay_ms(1);				  
		if(USB_STA!=USB_STATUS_REG)//״̬�ı��� 
		{	 						   
			LCD_Fill(30,190,240,190+16,WHITE);//�����ʾ			  	   
			if(USB_STATUS_REG&0x01)//����д		  
			{
				LED1=0;
				LCD_ShowString(30,190,200,16,16,"USB Writing...");//��ʾUSB����д������	 
			}
			if(USB_STATUS_REG&0x02)//���ڶ�
			{
				LED1=0;
				LCD_ShowString(30,190,200,16,16,"USB Reading...");//��ʾUSB���ڶ�������  		 
			}	 										  
			if(USB_STATUS_REG&0x04)LCD_ShowString(30,210,200,16,16,"USB Write Err ");//��ʾд�����
			else LCD_Fill(30,210,240,210+16,WHITE);//�����ʾ	  
			if(USB_STATUS_REG&0x08)LCD_ShowString(30,230,200,16,16,"USB Read  Err ");//��ʾ��������
			else LCD_Fill(30,230,240,230+16,WHITE);//�����ʾ    
			USB_STA=USB_STATUS_REG;//��¼����״̬
		}
		if(Divece_STA!=bDeviceState) 
		{
			if(bDeviceState==1)LCD_ShowString(30,170,200,16,16,"USB Connected    ");//��ʾUSB�����Ѿ�����
			else LCD_ShowString(30,170,200,16,16,"USB DisConnected ");//��ʾUSB���γ���
			Divece_STA=bDeviceState;
		}
		tct++;
		if(tct==200)
		{
			tct=0;
			LED1=1;
			LED0=!LED0;//��ʾϵͳ������
			if(USB_STATUS_REG&0x10)
			{
				offline_cnt=0;//USB������,�����offline������
				bDeviceState=1;
			}else//û�еõ���ѯ 
			{
				offline_cnt++;  
				if(offline_cnt>10)bDeviceState=0;//2s��û�յ����߱��,����USB���γ���
			}
			USB_STATUS_REG=0;
		}
	};  
}




