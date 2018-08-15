#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "sram.h"
#include "malloc.h"
#include "ILI93xx.h"
#include "led.h"
#include "timer.h"
#include "touch.h"
#include "GUI.h"
#include "ff.h"
#include "exfuns.h"
#include "w25qxx.h"
#include "includes.h"
#include "banding.h"

  
//EMWIN5.22�ֶδ洢�豸
//STM32F4����----�⺯���汾
//�Ա����̣�http://mcudev.taobao.com	

//START����
//������������ȼ�
#define START_TASK_PRIO				0
//�����ջ��С 
#define START_STK_SIZE			  128
//�����ջ
OS_STK	START_TASK_STK[START_STK_SIZE];
//start_task����
void start_task(void *pdata);

//TOUCH����
//�����������ȼ�
#define TOUCH_TASK_PRIO				2
//�����ջ��С
#define TOUCH_STK_SIZE				128
//�����ջ
OS_STK TOUCH_TASK_STK[TOUCH_STK_SIZE];
//touch����
void touch_task(void *pdata);

//LED0����
//�����������ȼ�
#define LED0_TASK_PRIO 				3
//�����ջ��С
#define LED0_STK_SIZE				64
//�����ջ
OS_STK LED0_TASK_STK[LED0_STK_SIZE];
//led0����
void led0_task(void *pdata);


//EMWINDEMO����
//�����������ȼ�
#define EMWINDEMO_TASK_PRIO		4
//�����ջ��С
#define EMWINDEMO_STK_SIZE		2048
//�����ջ
OS_STK EMWINDEMO_TASK_STK[EMWINDEMO_STK_SIZE];
//emwindemo_task����
void emwin_maintask(void *pdata);

int main(void)
{
	delay_init(168);       	//��ʱ��ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  	//�жϷ�������
	uart_init(115200);    	//���ڲ���������
	TFTLCD_Init();			//��ʼ��LCD
	TP_Init();				//��ʼ��������
	W25QXX_Init();			//��ʼ��W25Q16
	LED_Init();   			//LED��ʼ��
//	FSMC_SRAM_Init(); 		//SRAM��ʼ��
	
	mem_init(SRAMIN); 		//�ڲ�RAM��ʼ��
//	mem_init(SRAMEX); 		//�ⲿRAM��ʼ��
	mem_init(SRAMCCM);		//CCM��ʼ��
		
	exfuns_init();			//Ϊfatfs�ļ�ϵͳ�����ڴ�
	f_mount(fs[0],"0:",1);	//����SD��
	f_mount(fs[1],"1:",1);	//����FLASH
	OSInit();  //��ʼUCOS
	OSTaskCreate(start_task,  									//start_task����
				(void*)0,    									//����
				(OS_STK*)&START_TASK_STK[START_STK_SIZE-1], 	//�����ջջ��
				START_TASK_PRIO);  								//�������ȼ�
	OSStart();  //����UCOS
}

//START����
void start_task(void *pdata)
{
	OS_CPU_SR cpu_sr;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC,ENABLE);	//����CRCʱ��				//�����д�����ʹ�ô洢�豸
	GUI_Init();  										//emwin��ʼ��
	
	OSStatInit(); //��ʼ��ͳ������
	OS_ENTER_CRITICAL();  //�����ٽ���,�ر��ж�
	
	OSTaskCreate(emwin_maintask,(void*)0,(OS_STK*)&EMWINDEMO_TASK_STK[EMWINDEMO_STK_SIZE-1],EMWINDEMO_TASK_PRIO);  //WMEINDEMO������					
	OSTaskCreate(touch_task,(void*)0,(OS_STK*)&TOUCH_TASK_STK[TOUCH_STK_SIZE-1],TOUCH_TASK_PRIO); //����������
	OSTaskCreate(led0_task,(void*)0,(OS_STK*)&LED0_TASK_STK[LED0_STK_SIZE-1],LED0_TASK_PRIO); //LED0����
	
	OSTaskSuspend(OS_PRIO_SELF); //����start����
	OS_EXIT_CRITICAL();  //�˳��ٽ���,���ж�					
}

//EMWINDEMO����
void emwin_maintask(void *pdata)
{
	while(1)
	{
		_DemoBandingMemdev();
	}
}

//TOUCH����
void touch_task(void *pdata)
{
	while(1)
	{
		GUI_TOUCH_Exec();
		OSTimeDlyHMSM(0,0,0,5);//��ʱ5ms
	}
}

//LED0����
void led0_task(void *pdata)
{
	while(1)
	{
		LED0 = !LED0;
		OSTimeDlyHMSM(0,0,0,500);//��ʱ500ms
	}
}
