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

  
//EMWIN5.22分段存储设备
//STM32F4工程----库函数版本
//淘宝店铺：http://mcudev.taobao.com	

//START任务
//设置任务的优先级
#define START_TASK_PRIO				0
//任务堆栈大小 
#define START_STK_SIZE			  128
//任务堆栈
OS_STK	START_TASK_STK[START_STK_SIZE];
//start_task任务
void start_task(void *pdata);

//TOUCH任务
//设置任务优先级
#define TOUCH_TASK_PRIO				2
//任务堆栈大小
#define TOUCH_STK_SIZE				128
//任务堆栈
OS_STK TOUCH_TASK_STK[TOUCH_STK_SIZE];
//touch任务
void touch_task(void *pdata);

//LED0任务
//设置任务优先级
#define LED0_TASK_PRIO 				3
//任务堆栈大小
#define LED0_STK_SIZE				64
//任务堆栈
OS_STK LED0_TASK_STK[LED0_STK_SIZE];
//led0任务
void led0_task(void *pdata);


//EMWINDEMO任务
//设置任务优先级
#define EMWINDEMO_TASK_PRIO		4
//任务堆栈大小
#define EMWINDEMO_STK_SIZE		2048
//任务堆栈
OS_STK EMWINDEMO_TASK_STK[EMWINDEMO_STK_SIZE];
//emwindemo_task任务
void emwin_maintask(void *pdata);

int main(void)
{
	delay_init(168);       	//延时初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  	//中断分组配置
	uart_init(115200);    	//串口波特率设置
	TFTLCD_Init();			//初始化LCD
	TP_Init();				//初始化触摸屏
	W25QXX_Init();			//初始化W25Q16
	LED_Init();   			//LED初始化
//	FSMC_SRAM_Init(); 		//SRAM初始化
	
	mem_init(SRAMIN); 		//内部RAM初始化
//	mem_init(SRAMEX); 		//外部RAM初始化
	mem_init(SRAMCCM);		//CCM初始化
		
	exfuns_init();			//为fatfs文件系统分配内存
	f_mount(fs[0],"0:",1);	//挂载SD卡
	f_mount(fs[1],"1:",1);	//挂载FLASH
	OSInit();  //开始UCOS
	OSTaskCreate(start_task,  									//start_task任务
				(void*)0,    									//参数
				(OS_STK*)&START_TASK_STK[START_STK_SIZE-1], 	//任务堆栈栈顶
				START_TASK_PRIO);  								//任务优先级
	OSStart();  //开启UCOS
}

//START任务
void start_task(void *pdata)
{
	OS_CPU_SR cpu_sr;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC,ENABLE);	//开启CRC时钟				//在所有窗口上使用存储设备
	GUI_Init();  										//emwin初始化
	
	OSStatInit(); //初始化统计任务
	OS_ENTER_CRITICAL();  //进入临界区,关闭中断
	
	OSTaskCreate(emwin_maintask,(void*)0,(OS_STK*)&EMWINDEMO_TASK_STK[EMWINDEMO_STK_SIZE-1],EMWINDEMO_TASK_PRIO);  //WMEINDEMO任务优					
	OSTaskCreate(touch_task,(void*)0,(OS_STK*)&TOUCH_TASK_STK[TOUCH_STK_SIZE-1],TOUCH_TASK_PRIO); //触摸屏任务
	OSTaskCreate(led0_task,(void*)0,(OS_STK*)&LED0_TASK_STK[LED0_STK_SIZE-1],LED0_TASK_PRIO); //LED0任务
	
	OSTaskSuspend(OS_PRIO_SELF); //挂起start任务
	OS_EXIT_CRITICAL();  //退出临界区,开中断					
}

//EMWINDEMO任务
void emwin_maintask(void *pdata)
{
	while(1)
	{
		_DemoBandingMemdev();
	}
}

//TOUCH任务
void touch_task(void *pdata)
{
	while(1)
	{
		GUI_TOUCH_Exec();
		OSTimeDlyHMSM(0,0,0,5);//延时5ms
	}
}

//LED0任务
void led0_task(void *pdata)
{
	while(1)
	{
		LED0 = !LED0;
		OSTimeDlyHMSM(0,0,0,500);//延时500ms
	}
}
