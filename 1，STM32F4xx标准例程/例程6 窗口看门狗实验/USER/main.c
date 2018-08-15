#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "wwdg.h"



//窗口看门狗实验 -库函数版本
//STM32F4工程模板-库函数版本
//淘宝店铺：http://mcudev.taobao.com			

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
	LED_Init();				//初始化LED端口
	KEY_Init();		  	//初始化按键
	LED0=0;				   //点亮LED0
	delay_ms(300);
	WWDG_Init(0x7F,0X5F,WWDG_Prescaler_8); 	//计数器值为7f,窗口寄存器为5f,分频数为8	   
	
	while(1)
	{
		LED0=1;  //熄灭LED灯
	}
}
