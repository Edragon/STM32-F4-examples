#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"



//按键输入实验-库函数版本 
//STM32F4工程模板-库函数版本
//淘宝店铺：http://mcudev.taobao.com


int main(void)
{ 
 
  u8 key;           //保存键值
	delay_init(168);  //初始化延时函数
	LED_Init();				//初始化LED端口 
//	BEEP_Init();      //初始化蜂鸣器端口
	KEY_Init();       //初始化与按键连接的硬件接口
	LED0=0;				  	//先点亮红灯
	while(1)
	{
		key=KEY_Scan(0);		//得到键值
	   	if(key)
		{						   
			switch(key)
			{				 
				case WKUP_PRES:	//控制蜂鸣器
 					LED0=!LED0;
 					LED1=!LED1;
					break;
				case KEY0_PRES:	//控制LED0翻转
					LED0=!LED0;
					break;
				case KEY1_PRES:	//控制LED1翻转	 
					LED1=!LED1;
					break;
//				case KEY2_PRES:	//同时控制LED0,LED1翻转 
//					LED0=!LED0;
//					LED1=!LED1;
//					break;
			}
		}else delay_ms(10); 
	}

}
