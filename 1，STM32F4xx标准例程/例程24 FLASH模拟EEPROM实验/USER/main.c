#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "stmflash.h" 
#include "key.h"  
 
//FLASHģ��EEPROM ʵ�� -�⺯���汾
//STM32F4����ģ��-�⺯���汾
//�Ա����̣�http://mcudev.taobao.com	

//Ҫд�뵽STM32 FLASH���ַ�������
const u8 TEXT_Buffer[]={"STM32 FLASH TEST"};
#define TEXT_LENTH sizeof(TEXT_Buffer)	 		  	//���鳤��	
#define SIZE TEXT_LENTH/4+((TEXT_LENTH%4)?1:0)

#define FLASH_SAVE_ADDR  0X0800C004 	//����FLASH �����ַ(����Ϊż��������������,Ҫ���ڱ�������ռ�õ�������.
										//����,д������ʱ��,���ܻᵼ�²�����������,�Ӷ����𲿷ֳ���ʧ.��������.
int main(void)
{ 
	u8 key=0;
	u16 i=0;
	u8 datatemp[SIZE];	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	
	LED_Init();					//��ʼ��LED 
 	LCD_Init();					//LCD��ʼ��  
 	KEY_Init();					//������ʼ�� 
 	POINT_COLOR=RED;//��������Ϊ��ɫ 
	LCD_ShowString(30,50,200,16,16,"mcudev STM32F4");	
	LCD_ShowString(30,70,200,16,16,"FLASH EEPROM TEST");	
	LCD_ShowString(30,90,200,16,16,"mcudev.taobao.com");
	LCD_ShowString(30,110,200,16,16,"2014/5/9"); 
	LCD_ShowString(30,130,200,16,16,"KEY1:Write  KEY0:Read");
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY1_PRES)	//KEY1����,д��STM32 FLASH
		{
			LCD_Fill(0,170,239,319,WHITE);//�������    
 			LCD_ShowString(30,170,200,16,16,"Start Write FLASH....");
			STMFLASH_Write(FLASH_SAVE_ADDR,(u32*)TEXT_Buffer,SIZE);
			LCD_ShowString(30,170,200,16,16,"FLASH Write Finished!");//��ʾ�������
		}
		if(key==KEY0_PRES)	//KEY0����,��ȡ�ַ�������ʾ
		{
 			LCD_ShowString(30,170,200,16,16,"Start Read FLASH.... ");
			STMFLASH_Read(FLASH_SAVE_ADDR,(u32*)datatemp,SIZE);
			LCD_ShowString(30,170,200,16,16,"The Data Readed Is:  ");//��ʾ�������
			LCD_ShowString(30,190,200,16,16,datatemp);//��ʾ�������ַ���
		}
		i++;
		delay_ms(10);  
		if(i==20)
		{
			LED0=!LED0;//��ʾϵͳ��������	
			i=0;
		}		   
	}    
}

