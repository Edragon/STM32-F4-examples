#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "wwdg.h"



//���ڿ��Ź�ʵ�� -�⺯���汾
//STM32F4����ģ��-�⺯���汾
//�Ա����̣�http://mcudev.taobao.com			

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	LED_Init();				//��ʼ��LED�˿�
	KEY_Init();		  	//��ʼ������
	LED0=0;				   //����LED0
	delay_ms(300);
	WWDG_Init(0x7F,0X5F,WWDG_Prescaler_8); 	//������ֵΪ7f,���ڼĴ���Ϊ5f,��Ƶ��Ϊ8	   
	
	while(1)
	{
		LED0=1;  //Ϩ��LED��
	}
}
