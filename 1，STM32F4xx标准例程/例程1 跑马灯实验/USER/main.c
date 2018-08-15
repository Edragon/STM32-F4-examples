#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"


//跑马灯实验 -库函数版本
//STM32F4工程模板-库函数版本
//淘宝店铺：http://mcudev.taobao.com

int main(void)
{ 
 
	delay_init(168);		  //初始化延时函数
	LED_Init();		        //初始化LED端口
	
  /**下面是通过直接操作库函数的方式实现IO控制**/	
	
	while(1)
	{
	GPIO_ResetBits(GPIOA,GPIO_Pin_6);  //LED0对应引脚GPIOA.6拉低，亮  等同LED0=0;
	GPIO_SetBits(GPIOA,GPIO_Pin_7);   //LED1对应引脚GPIOA.7拉高，灭 等同LED1=1;
	delay_ms(500);  		   //延时300ms
	GPIO_SetBits(GPIOA,GPIO_Pin_6);	   //LED0对应引脚GPIOA.6拉高，灭  等同LED0=1;
	GPIO_ResetBits(GPIOA,GPIO_Pin_7); //LED1对应引脚GPIOA.7拉低，亮 等同LED1=0;
	delay_ms(500);                     //延时300ms
	}
}



 



