#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "includes.h"
#include "key.h"
#include "beep.h"
 
//UCOSIIʵ��1-2 ���񴴽���ɾ�������𣬻ָ�  -�⺯���汾
//STM32F4����ģ��-�⺯���汾
//�Ա����̣�http://mcudev.taobao.com	


/////////////////////////UCOSII�����ջ����///////////////////////////////////
//START ����
//�����������ȼ�
#define START_TASK_PRIO      			10 //��ʼ��������ȼ�����Ϊ���
//���������ջ��С
#define START_STK_SIZE  				64
//���������ջ�ռ�	
OS_STK START_TASK_STK[START_STK_SIZE];
//�������ӿ�
void start_task(void *pdata);	
 			   
//LED����
//�����������ȼ�
#define LED_TASK_PRIO       			7 
//���������ջ��С
#define LED_STK_SIZE  		    		64
//���������ջ�ռ�	
OS_STK LED_TASK_STK[LED_STK_SIZE];
//�������ӿ�
void led_task(void *pdata);


//����������
//�����������ȼ�
#define BEEP_TASK_PRIO       			5 
//���������ջ��С
#define BEEP_STK_SIZE  					64
//���������ջ�ռ�	
OS_STK BEEP_TASK_STK[BEEP_STK_SIZE];
//�������ӿ�
void beep_task(void *pdata);


//����ɨ������
//�����������ȼ�
#define KEY_TASK_PRIO       			3 
//���������ջ��С
#define KEY_STK_SIZE  					64
//���������ջ�ռ�	
OS_STK KEY_TASK_STK[KEY_STK_SIZE];
//�������ӿ�
void key_task(void *pdata);

int main(void)
{ 
 
	delay_init(168);		  //��ʼ����ʱ����
	uart_init(115200);
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
// 	BEEP_Init();			//��������ʼ��---������ʹ��LED���棬��ʱ����ʼ��	
	KEY_Init();				//������ʼ��
	OSInit();  	 			//��ʼ��UCOSII		 			  
 	OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );//������ʼ����
	OSStart();	
}

//��ʼ����
void start_task(void *pdata)
{
    OS_CPU_SR cpu_sr=0;
	pdata = pdata; 		  		 			  
	OSStatInit();					//��ʼ��ͳ������.�������ʱ1��������	
 	OS_ENTER_CRITICAL();			//�����ٽ���(�޷����жϴ��)    
 	OSTaskCreate(led_task,(void *)0,(OS_STK*)&LED_TASK_STK[LED_STK_SIZE-1],LED_TASK_PRIO);						    				   
 	OSTaskCreate(beep_task,(void *)0,(OS_STK*)&BEEP_TASK_STK[BEEP_STK_SIZE-1],BEEP_TASK_PRIO);	 				   				   
 	OSTaskCreate(key_task,(void *)0,(OS_STK*)&KEY_TASK_STK[KEY_STK_SIZE-1],KEY_TASK_PRIO);	 				   
 	OSTaskSuspend(START_TASK_PRIO);	//������ʼ����.
	OS_EXIT_CRITICAL();				//�˳��ٽ���(���Ա��жϴ��)
}	  
//LED����
void led_task(void *pdata)
{   
	while(1)
	{  
	     LED0=!LED0;
		 
	   	delay_ms(500);
	}									 
}	   

//����������
void beep_task(void *pdata)
{
	while(1)
	{  	
	   if(OSTaskDelReq(OS_PRIO_SELF)==OS_ERR_TASK_DEL_REQ) //�ж��Ƿ���ɾ������
		 {
		 OSTaskDel(OS_PRIO_SELF);						   //ɾ��������TaskLed
		 }
		 LED1=!LED1;                            //�˴�ʹ��LED1���������������IO�Ĺ��ܷ�ʽ��һ����
	   delay_ms(60);
     LED1=!LED1;
		 delay_ms(940);
	}									 
}

//����ɨ������
void key_task(void *pdata)
{	
	u8 key;		    						 
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY0_PRES)
		{
		  OSTaskSuspend(LED_TASK_PRIO);//����LED����LEDֹͣ��˸
		}
		else if (key==KEY1_PRES)
		{
		  OSTaskResume(LED_TASK_PRIO);	//�ָ�LED����LED�ָ���˸
		}
//		else if (key==WKUP_PRES)
//		{
//		  OSTaskDelReq(BEEP_TASK_PRIO);	//����ɾ��BEEP������������˯�ߣ��޷��ָ�
//		}
		else if(key==WKUP_PRES)
		{
		 OSTaskCreate(beep_task,(void *)0,(OS_STK*)&BEEP_TASK_STK[BEEP_STK_SIZE-1],BEEP_TASK_PRIO);//���´�������beep	 				   				   
		}   
 		delay_ms(10);
	}
}



