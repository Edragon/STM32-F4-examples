#ifndef _LED_H
#define _LED_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
 
//LED驱动代码	   
//STM32F4工程----库函数版本
//淘宝店铺：http://mcudev.taobao.com							  
////////////////////////////////////////////////////////////////////////////////// 	

//LED端口定义
#define LED0 PAout(6)
#define LED1 PAout(7)

void LED_Init(void);  //初始化
#endif
