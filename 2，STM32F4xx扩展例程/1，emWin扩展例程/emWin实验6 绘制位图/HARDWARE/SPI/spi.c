#include "spi.h"
//////////////////////////////////////////////////////////////////////////////////	 
 
//SPI ��������	   
//STM32F4����----�⺯���汾
//�Ա����̣�http://mcudev.taobao.com									  
////////////////////////////////////////////////////////////////////////////////// 	 

//������SPIģ��ĳ�ʼ������,����Ϊ����ģʽ
//SPI1��ʼ��
void  SPI1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef SPI_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);//ʹ��GPIOBʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE); //ʹ��SPIʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5; //PB 3 4 5����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 	//�������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 		//����
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_SPI1); //PB3����SPI1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_SPI1); //PB4����SPI1
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_SPI1); //PB5����SPI1
	
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //ȫ˫��ģʽ
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master; //��ģʽ
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; //8λ���ݸ�ʽ
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High; //CLK����ʱΪ1
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge; //���ݲ����ӵڶ���ʱ����ؿ�ʼ
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;  //���NSS����
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256; //APB2ʱ��84M,Fsck=Fpclk1/256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; //��λ�ȷ���
	SPI_InitStructure.SPI_CRCPolynomial = 7; //CRC
	SPI_Init(SPI1,&SPI_InitStructure); //SPI1����
	
	SPI_Cmd(SPI1,ENABLE); //����SPI1
}
//SPI1�ٶ����ú���
//SpeedSet:0~7
//SPI�ٶ�=fAPB2/2^(SpeedSet+1)
//fAPB2ʱ��һ��Ϊ84Mhz
void SPI1_SetSpeed(u8 SpeedSet)
{
	SpeedSet&=0X07;			//���Ʒ�Χ
	SPI1->CR1&=0XFFC7; 
	SPI1->CR1|=SpeedSet<<3;	//����SPI1�ٶ�  
	SPI1->CR1|=1<<6; 		//SPI�豸ʹ��	 
}

//SPI1 ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
u8 SPI1_ReadWriteByte(u8 Txdata)
{
	u8 retry = 0;
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) == RESET) //�ȴ����ͻ�������
	{
		retry ++;
		if(retry > 200) return 0;
	}
	SPI_I2S_SendData(SPI1,Txdata); //����
	retry = 0;
	while(SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE) == RESET) //�ȴ�������һ���ֽ�
	{
		retry ++;
		if(retry > 200) return 0;
	}
	return SPI_I2S_ReceiveData(SPI1); //��������
}
