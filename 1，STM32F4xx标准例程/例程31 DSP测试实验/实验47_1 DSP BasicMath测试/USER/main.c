#include "sys.h"
#include "delay.h"  
#include "usart.h"  
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "timer.h" 
#include "math.h" 
#include "arm_math.h"  

 
//DSP BasicMath����ʵ�� -�⺯���汾
//STM32F4����ģ��-�⺯���汾
//�Ա����̣�http://mcudev.taobao.com


#define	DELTA	0.000001f		//���ֵ
 
//sin cos����
//angle:��ʼ�Ƕ�
//times:�������
//mode:0,��ʹ��DSP��;1,ʹ��DSP��
//����ֵ��0,�ɹ�;0XFF,����
u8 sin_cos_test(float angle,u32 times,u8 mode)
{
	float sinx,cosx;
	float result;
	u32 i=0;
	if(mode==0)
	{
		for(i=0;i<times;i++)
		{
			cosx=cosf(angle);			//��ʹ��DSP�Ż���sin��cos����
			sinx=sinf(angle);
			result=sinx*sinx+cosx*cosx; //������Ӧ�õ���1  
			result=fabsf(result-1.0f);	//�Ա���1�Ĳ�ֵ
			if(result>DELTA)return 0XFF;//�ж�ʧ�� 
			angle+=0.001f;				//�Ƕ�����
		}
	}else
	{
		for(i=0;i<times;i++)
		{
			cosx=arm_cos_f32(angle);	//ʹ��DSP�Ż���sin��cos����
			sinx=arm_sin_f32(angle);
			result=sinx*sinx+cosx*cosx; //������Ӧ�õ���1  
			result=fabsf(result-1.0f);	//�Ա���1�Ĳ�ֵ
			if(result>DELTA)return 0XFF;//�ж�ʧ�� 
			angle+=0.001f;				//�Ƕ�����
		}
	}
	return 0;//�������
} 
u8 timeout;//��ʱ���������


int main(void)
{ 
	float time; 
	u8 buf[50];
	u8 res;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	
	LED_Init();					//��ʼ��LED
	KEY_Init();					//��ʼ������
 	LCD_Init();					//��ʼ��LCD
 	TIM3_Int_Init(65535,8400-1);//10Khz����Ƶ��,����ʱ6.5�볬��
	POINT_COLOR=RED; 
	LCD_ShowString(30,50,200,16,16,"mcudev STM32F4");	
	LCD_ShowString(30,70,200,16,16,"DSP BasicMath TEST");	
	LCD_ShowString(30,90,200,16,16,"mcudev.taobao.com");
	LCD_ShowString(30,110,200,16,16,"2015/7/20");	
	LCD_ShowString(30,150,200,16,16," No DSP runtime:");	//��ʾ��ʾ��Ϣ
	LCD_ShowString(30,190,200,16,16,"Use DSP runtime:");	//��ʾ��ʾ��Ϣ	
 	POINT_COLOR=BLUE;	//��������Ϊ��ɫ   
	while(1)
	{
		LCD_Fill(30+16*8,150,lcddev.width-1,60,WHITE);		//���ԭ����ʵ
		//��ʹ��DSP�Ż�
		TIM_SetCounter(TIM3,0);//����TIM3��ʱ���ļ�����ֵ
		timeout=0;
		res=sin_cos_test(PI/6,200000,0);
		time=TIM_GetCounter(TIM3)+(u32)timeout*65536;
		sprintf((char*)buf,"%0.1fms\r\n",time/10);
		if(res==0)LCD_ShowString(30+16*8,150,100,16,16,buf);	//��ʾ����ʱ��		
		else LCD_ShowString(30+16*8,150,100,16,16,"error��");	//��ʾ��ǰ�������	
		//ʹ��DSP�Ż�		
		TIM_SetCounter(TIM3,0);//����TIM3��ʱ���ļ�����ֵ
		timeout=0;
		res=sin_cos_test(PI/6,200000,1);
		time=TIM_GetCounter(TIM3)+(u32)timeout*65536;
		sprintf((char*)buf,"%0.1fms\r\n",time/10);
		if(res==0)LCD_ShowString(30+16*8,190,100,16,16,buf);	//��ʾ����ʱ��	
		else LCD_ShowString(30+16*8,190,100,16,16,"error��");	//��ʾ����	
		LED0=!LED0;
	}
}
 
