#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "usmart.h"



//USMART����ʵ�� -�⺯���汾
//STM32F4����ģ��-�⺯���汾
//�Ա����̣�http://mcudev.taobao.com		


//LED״̬���ú���
void led_set(u8 sta)
{
	LED1=sta;
} 
//�����������ò��Ժ���
void test_fun(void(*ledset)(u8),u8 sta)
{
	ledset(sta);
}  


int main(void)
{ 
 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);      //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	usmart_dev.init(84); 	//��ʼ��USMART			
	LED_Init();					  //��ʼ��LED
 	LCD_Init();           //��ʼ��LCD
	POINT_COLOR=RED;
	LCD_ShowString(30,50,200,16,16,"Mcudev STM32F4XX");	
	LCD_ShowString(30,70,200,16,16,"USMART TEST");	
	LCD_ShowString(30,90,200,16,16,"mcudev.taobao");
	LCD_ShowString(30,110,200,16,16,"2015/5/5");	   
  	while(1) 
	{		 	  
		LED0=!LED0;					 
		delay_ms(500);	
	}
}
