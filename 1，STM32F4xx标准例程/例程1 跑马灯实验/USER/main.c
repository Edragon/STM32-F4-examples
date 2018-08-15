#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"


//�����ʵ�� -�⺯���汾
//STM32F4����ģ��-�⺯���汾
//�Ա����̣�http://mcudev.taobao.com

int main(void)
{ 
 
	delay_init(168);		  //��ʼ����ʱ����
	LED_Init();		        //��ʼ��LED�˿�
	
  /**������ͨ��ֱ�Ӳ����⺯���ķ�ʽʵ��IO����**/	
	
	while(1)
	{
	GPIO_ResetBits(GPIOA,GPIO_Pin_6);  //LED0��Ӧ����GPIOA.6���ͣ���  ��ͬLED0=0;
	GPIO_SetBits(GPIOA,GPIO_Pin_7);   //LED1��Ӧ����GPIOA.7���ߣ��� ��ͬLED1=1;
	delay_ms(500);  		   //��ʱ300ms
	GPIO_SetBits(GPIOA,GPIO_Pin_6);	   //LED0��Ӧ����GPIOA.6���ߣ���  ��ͬLED0=1;
	GPIO_ResetBits(GPIOA,GPIO_Pin_7); //LED1��Ӧ����GPIOA.7���ͣ��� ��ͬLED1=0;
	delay_ms(500);                     //��ʱ300ms
	}
}



 



