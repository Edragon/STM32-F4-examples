#include "sys.h"
#include "delay.h"  
#include "usart.h"   
#include "led.h"
#include "lcd.h"
#include "key.h"  
#include "usmart.h"  
#include "malloc.h" 
#include "w25qxx.h"    
#include "sdio_sdcard.h"
#include "ff.h"  
#include "exfuns.h"    
#include "fontupd.h"
#include "text.h"	 
#include "wm8978.h"	 
#include "videoplayer.h" 
#include "timer.h" 
 
//��Ƶ������ʵ�� -�⺯���汾
//STM32F4��������-�⺯���汾
//�Ա����̣�http://mcudev.taobao.com	

 
int main(void)
{ 
  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	
	LED_Init();					//��ʼ��LED 
	usmart_dev.init(84);		//��ʼ��USMART
 	LCD_Init();					//LCD��ʼ��  
 	KEY_Init();					//������ʼ��   
	W25QXX_Init();				//��ʼ��W25Q128
	WM8978_Init();				//��ʼ��WM8978	
	
	WM8978_ADDA_Cfg(1,0);		//����DAC
	WM8978_Input_Cfg(0,0,0);	//�ر�����ͨ��
	WM8978_Output_Cfg(1,0);		//����DAC���  
	WM8978_HPvol_Set(40,40);
	WM8978_SPKvol_Set(60);
	TIM3_Int_Init(10000-1,8400-1);//10Khz����,1�����ж�һ��
	
	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ�� 
	my_mem_init(SRAMCCM);		//��ʼ��CCM�ڴ�� 
	exfuns_init();				//Ϊfatfs��ر��������ڴ�  
  	f_mount(fs[0],"0:",1); 		//����SD��  
	POINT_COLOR=RED;      
	while(font_init()) 			//����ֿ�
	{	    
		LCD_ShowString(30,50,200,16,16,"Font Error!");
		delay_ms(200);				  
		LCD_Fill(30,50,240,66,WHITE);//�����ʾ	     
		delay_ms(200);	
		LED0=!LED0;
	}  	 
	POINT_COLOR=RED;      
 	Show_Str(60,50,200,16,"mcudev STM32������",16,0);				    	 
	Show_Str(60,70,200,16,"��Ƶ������ʵ��",16,0);				    	 
	Show_Str(60,90,200,16,"mcudev.taobao.com",16,0);				    	 
	Show_Str(60,110,200,16,"2015��7��10��",16,0);
	Show_Str(60,130,200,16,"KEY0:NEXT   KEY1:PREV",16,0); 
	Show_Str(60,150,200,16,"KEY_UP:FF   KEY1��REW",16,0);
	delay_ms(1500);
	while(1)
	{ 
		video_play();
	} 
}


