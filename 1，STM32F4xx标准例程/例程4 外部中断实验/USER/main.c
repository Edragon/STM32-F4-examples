#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "exti.h"


//外部中断实验-库函数版本
//STM32F4工程模板-库函数版本
//淘宝店铺：http://mcudev.taobao.com	

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);    //初始化延时函数
	uart_init(115200); 	//串口初始化 
	LED_Init();				  //初始化LED端口  
//	BEEP_Init();        //初始化蜂鸣器端口
	EXTIX_Init();       //初始化外部中断输入 
	LED0=0;					    //先点亮红灯
	while(1)
	{
  	printf("OK\r\n");	//打印OK提示程序运行
		delay_ms(1000);	  //每隔1s打印一次
	}

}
