#ifndef _SPI_H
#define _SPI_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
 
//SPI 驱动代码	   
//STM32F4工程----库函数版本
//淘宝店铺：http://mcudev.taobao.com											  
////////////////////////////////////////////////////////////////////////////////// 	 

// SPI总线速度设置 
#define SPI_SPEED_2   	0
#define SPI_SPEED_4   	1
#define SPI_SPEED_8   	2
#define SPI_SPEED_16  	3	
#define SPI_SPEED_32 		4
#define SPI_SPEED_64 		5
#define SPI_SPEED_128 	6
#define SPI_SPEED_256 	7	

void  SPI1_Init(void);
void SPI1_SetSpeed(u8 SpeedSet);
u8 SPI1_ReadWriteByte(u8 Txdata);
#endif

