#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "adc.h"
#include "key.h"
#include "pwmdac.h"
 
 

//PWM DAC ʵ��  -�⺯���汾
//STM32F4����ģ��-�⺯���汾
//�Ա����̣�http://mcudev.taobao.com			
 

  
int main(void)
{ 
	u16 adcx;
	float temp;
 	u8 t=0;	 
	u16 pwmval=0;
	u8 key; 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);    //��ʼ����ʱ����
	uart_init(115200);	//��ʼ�����ڲ�����Ϊ115200
	
	LED_Init();					//��ʼ��LED 
 	LCD_Init();					//LCD��ʼ��
	Adc_Init(); 				//adc��ʼ��
	KEY_Init(); 				//������ʼ��
	TIM9_CH2_PWM_Init(255,0);	//TIM4 PWM��ʼ��, Fpwm=168M/256=656.25Khz.
	POINT_COLOR=RED; 
	LCD_ShowString(30,50,200,16,16,"Mcudev STM32F4");	
	LCD_ShowString(30,70,200,16,16,"PWM DAC TEST");	
	LCD_ShowString(30,90,200,16,16,"mcudev.taobao.com");
	LCD_ShowString(30,110,200,16,16,"2014/5/6");	 
	LCD_ShowString(30,130,200,16,16,"WK_UP:+  KEY1:-");	 
	POINT_COLOR=BLUE;//��������Ϊ��ɫ      	 
	LCD_ShowString(30,150,200,16,16,"DAC VAL:");	      
	LCD_ShowString(30,170,200,16,16,"DAC VOL:0.000V");	      
	LCD_ShowString(30,190,200,16,16,"ADC VOL:0.000V");
  TIM_SetCompare2(TIM9,pwmval);	//��ʼֵ     	      
	while(1)
	{
		t++;
		key=KEY_Scan(0);			  
		if(key==4)
		{		 
			if(pwmval<250)pwmval+=10;
			TIM_SetCompare2(TIM9,pwmval);	//���	
		}else if(key==2)	
		{
			if(pwmval>10)pwmval-=10;
			else pwmval=0;
			TIM_SetCompare2(TIM9,pwmval);	//���
		}	 
		if(t==10||key==2||key==4) 		//WKUP/KEY1������,���߶�ʱʱ�䵽��
		{	  
 			adcx=TIM_GetCapture2(TIM9);;
			LCD_ShowxNum(94,150,adcx,3,16,0);     	//��ʾDAC�Ĵ���ֵ
			temp=(float)adcx*(3.3/256);;			      //�õ�DAC��ѹֵ
			adcx=temp;
 			LCD_ShowxNum(94,170,temp,1,16,0);     	//��ʾ��ѹֵ��������
 			temp-=adcx;
			temp*=1000;
			LCD_ShowxNum(110,170,temp,3,16,0x80); 	//��ʾ��ѹֵ��С������
 			adcx=Get_Adc_Average(ADC_Channel_5,20); //�õ�ADCת��ֵ	  
			temp=(float)adcx*(3.3/4096);			      //�õ�ADC��ѹֵ
			adcx=temp;
 			LCD_ShowxNum(94,190,temp,1,16,0);     	//��ʾ��ѹֵ��������
 			temp-=adcx;
			temp*=1000;
			LCD_ShowxNum(110,190,temp,3,16,0x80); 	//��ʾ��ѹֵ��С������
			t=0;
			LED0=!LED0;	   
		}	    
		delay_ms(10); 
	}
}




