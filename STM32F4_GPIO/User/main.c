#include "stm32f4xx.h"

#define ON  0
#define OFF 1

#define key (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4))

#define LED(a) if(a)\
								GPIO_SetBits(GPIOC,0XFFCF );\
								else\
								GPIO_ResetBits(GPIOC,0XFFCF )

void LED_Configuration(void);
void delay(unsigned long int time);


/*
 * ��������main
 * ����  ����������
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
int main(void)
{

    SystemInit();
    LED_Configuration();
    while (1)
    {
        LED(ON);
			
        delay(6000000);
        LED(OFF);
		
        delay(6000000);
			if(!key)
				{
					GPIO_SetBits(GPIOC,0x0020 );
				}
			else
				{	
					GPIO_ResetBits(GPIOC,0x0020 );
				}
				
			
    }
}


/*
 * ��������LED_Configuration
 * ����  ��LED GPIO������
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
void LED_Configuration(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;  //����һ�� ��ʼ��GPIO��ʱ���õ� �ṹ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC , ENABLE); //ʹ��PI�ڵ�ʱ�ӣ�����˿��ǲ�������
    GPIO_InitStructure.GPIO_Pin = 0XFFEF ; //�Խṹ���GPIO_Pin����ֵ������Ҫ��������11�˿�
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//�Խṹ���GPIO_Mode����ֵ������IO�ڵ�ģʽ�����
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�Խṹ���GPIO_OType����ֵ������IO�ڵĽṹ���������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//�Խṹ���GPIO_Speed����ֵ�������ٶ���100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //�Խṹ���GPIO_PuPd����ֵ�������ڲ�����
    GPIO_Init(GPIOC, &GPIO_InitStructure);//���ṹ������ʼ�������У�ִ�г�ʼ��������֮ǰ���ö�����Ч��
	
	  GPIO_InitStructure.GPIO_Pin = 0X0010 ; //�Խṹ���GPIO_Pin����ֵ������Ҫ��������11�˿�
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//�Խṹ���GPIO_Mode����ֵ������IO�ڵ�ģʽ�����
    //GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�Խṹ���GPIO_OType����ֵ������IO�ڵĽṹ���������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//�Խṹ���GPIO_Speed����ֵ�������ٶ���100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //�Խṹ���GPIO_PuPd����ֵ�������ڲ�����
    GPIO_Init(GPIOC, &GPIO_InitStructure);//���ṹ������ʼ�������У�ִ�г�ʼ��������֮ǰ���ö�����Ч��
	
	
	
}


void delay(unsigned long int time)
{
    while(time--);
}

/******************* (C) COPYRIGHT 2012 Richards *****END OF FILE***************/
