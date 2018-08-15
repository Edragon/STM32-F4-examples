#include "spi.h"
//////////////////////////////////////////////////////////////////////////////////	 
 
//SPI 驱动代码	   
//STM32F4工程----库函数版本
//淘宝店铺：http://mcudev.taobao.com									  
////////////////////////////////////////////////////////////////////////////////// 	 

//以下是SPI模块的初始化代码,配置为主机模式
//SPI1初始化
void  SPI1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);//使能GPIOB时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE); //使能SPI时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5; //PB 3 4 5设置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; //复用输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 	//推挽输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 		//上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_SPI1); //PB3复用SPI1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_SPI1); //PB4复用SPI1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_SPI1); //PB5复用SPI1
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //全双工模式
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master; //主模式
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; //8位数据格式
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High; //CLK空闲时为1
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge; //数据采样从第二个时间边沿开始
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;  //软件NSS管理
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256; //APB2时钟84M,Fsck=Fpclk1/256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; //高位先发送
	SPI_InitStructure.SPI_CRCPolynomial = 7; //CRC
	SPI_Init(SPI1,&SPI_InitStructure); //SPI1设置
	
	SPI_Cmd(SPI1,ENABLE); //开启SPI1
}
//SPI1速度设置函数
//SpeedSet:0~7
//SPI速度=fAPB2/2^(SpeedSet+1)
//fAPB2时钟一般为84Mhz
void SPI1_SetSpeed(u8 SpeedSet)
{
	SpeedSet&=0X07;			//限制范围
	SPI1->CR1&=0XFFC7; 
	SPI1->CR1|=SpeedSet<<3;	//设置SPI1速度  
	SPI1->CR1|=1<<6; 		//SPI设备使能	 
}

//SPI1 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
u8 SPI1_ReadWriteByte(u8 Txdata)
{
	u8 retry = 0;
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) == RESET) //等待发送缓冲区空
	{
		retry ++;
		if(retry > 200) return 0;
	}
	SPI_I2S_SendData(SPI1,Txdata); //发送
	retry = 0;
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE) == RESET) //等待接收完一个字节
	{
		retry ++;
		if(retry > 200) return 0;
	}
	return SPI_I2S_ReceiveData(SPI1); //发送数据
}
