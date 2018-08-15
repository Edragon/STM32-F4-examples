#include "usmart.h"
#include "usmart_str.h"
////////////////////////////�û�������///////////////////////////////////////////////
//������Ҫ�������õ��ĺ�����������ͷ�ļ�(�û��Լ����) 
#include "delay.h"	 
#include "wm8978.h" 

//�������б��ʼ��(�û��Լ����)
//�û�ֱ������������Ҫִ�еĺ�����������Ҵ�
struct _m_usmart_nametab usmart_nametab[]=
{
#if USMART_USE_WRFUNS==1 	//���ʹ���˶�д����
	(void*)read_addr,"u32 read_addr(u32 addr)",
	(void*)write_addr,"void write_addr(u32 addr,u32 val)",	 
#endif		   
	(void*)delay_ms,"void delay_ms(u16 nms)",
 	(void*)delay_us,"void delay_us(u32 nus)",
		

 	(void*)WM8978_Write_Reg,"void WM8978_Write_Reg(u8 reg,u8 val)", 
 	(void*)WM8978_Read_Reg,"u8 WM8978_Read_Reg(u8 reg)", 
 	(void*)WM8978_HPvol_Set,"void WM8978_HPvol_Set(u8 voll,u8 volr)", 
 	(void*)WM8978_SPKvol_Set,"void WM8978_SPKvol_Set(u8 volx)", 
 	(void*)WM8978_3D_Set,"void WM8978_3D_Set(u8 depth)",  
 	(void*)WM8978_EQ_3D_Dir,"void WM8978_EQ_3D_Dir(u8 dir)", 
 	(void*)WM8978_EQ1_Set,"void WM8978_EQ1_Set(u8 cfreq,u8 gain)", 
 	(void*)WM8978_EQ2_Set,"void WM8978_EQ2_Set(u8 cfreq,u8 gain)", 
 	(void*)WM8978_EQ3_Set,"void WM8978_EQ3_Set(u8 cfreq,u8 gain)", 
 	(void*)WM8978_EQ4_Set,"void WM8978_EQ4_Set(u8 cfreq,u8 gain)", 
 	(void*)WM8978_EQ5_Set,"void WM8978_EQ5_Set(u8 cfreq,u8 gain)", 	
};						
					  
///////////////////////////////////END///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//�������ƹ�������ʼ��
//�õ������ܿغ���������
//�õ�����������
struct _m_usmart_dev usmart_dev=
{
	usmart_nametab,
	usmart_init,
	usmart_cmd_rec,
	usmart_exe,
	usmart_scan,
	sizeof(usmart_nametab)/sizeof(struct _m_usmart_nametab),//��������
	0,	  	//��������
	0,	 	//����ID
	1,		//������ʾ����,0,10����;1,16����
	0,		//��������.bitx:,0,����;1,�ַ���	    
	0,	  	//ÿ�������ĳ����ݴ��,��ҪMAX_PARM��0��ʼ��
	0,		//�����Ĳ���,��ҪPARM_LEN��0��ʼ��
};   



















