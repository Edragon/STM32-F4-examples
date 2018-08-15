#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "iwdg.h"



//�������Ź�ʵ�� -�⺯���汾
//STM32F4����ģ��-�⺯���汾
//�Ա����̣�http://mcudev.taobao.com		

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	LED_Init();				//��ʼ��LED�˿�
	KEY_Init();		  	//��ʼ������
  delay_ms(100);    //��ʱ100ms 
	IWDG_Init(4,500); //���Ƶ��Ϊ64,����ֵΪ500,���ʱ��Ϊ1s	
	LED0=0;					  //�ȵ������
	while(1)
	{
		if(KEY_Scan(0)==WKUP_PRES)//���WK_UP����,��ι��
		{
			IWDG_Feed();//ι��
		}
		delay_ms(10);
	};

}
