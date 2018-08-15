#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "iwdg.h"



//独立看门狗实验 -库函数版本
//STM32F4工程模板-库函数版本
//淘宝店铺：http://mcudev.taobao.com		

int main(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
	LED_Init();				//初始化LED端口
	KEY_Init();		  	//初始化按键
  delay_ms(100);    //延时100ms 
	IWDG_Init(4,500); //与分频数为64,重载值为500,溢出时间为1s	
	LED0=0;					  //先点亮红灯
	while(1)
	{
		if(KEY_Scan(0)==WKUP_PRES)//如果WK_UP按下,则喂狗
		{
			IWDG_Feed();//喂狗
		}
		delay_ms(10);
	};

}
