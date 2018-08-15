#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "ILI93xx.h"
#include "led.h"
#include "sram.h"
#include "malloc.h"
#include "touch.h"
#include "GUI.h"
#include "timer.h"
#include "GUIDemo.h"


//STemWin��ֲʵ��
//STM32F4����----�⺯���汾
//�Ա����̣�http://mcudev.taobao.com		

int main(void)
{	
	delay_init(168);       	//��ʱ��ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  	//�жϷ�������
	uart_init(115200);    	//���ڲ���������
	LED_Init(); 			//LED��ʼ��
	TFTLCD_Init();  		//LCD��ʼ��
	TP_Init();				//��������ʼ��
//	FSMC_SRAM_Init(); 		//SRAM��ʼ��
	TIM3_Int_Init(999,83); 	//1KHZ ��ʱ��3����Ϊ1ms
	
	mem_init(SRAMIN); 		//��ʼ���ڲ��ڴ��
//	mem_init(SRAMEX);  		//��ʼ���ⲿ�ڴ��
	mem_init(SRAMCCM); 		//��ʼ��CCM�ڴ��
	
	TIM4_Int_Init(999,839);  //������ɨ���ٶ�,100HZ.
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC,ENABLE);//����CRCʱ��
	WM_SetCreateFlags(WM_CF_MEMDEV);
	GUI_Init();
	GUIDEMO_Main();
	while(1);
}




