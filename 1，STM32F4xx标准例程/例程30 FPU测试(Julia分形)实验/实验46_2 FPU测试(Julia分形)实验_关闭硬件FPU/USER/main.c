#include "sys.h"
#include "delay.h"  
#include "usart.h"  
#include "led.h"
#include "key.h"
#include "lcd.h"
#include "timer.h" 

 
////FPU����(Julia����) ʵ��  -�⺯���汾
//STM32F4����ģ��-�⺯���汾
//�Ա����̣�http://mcudev.taobao.com	

//46_2,���汾Ϊ�ر�Ӳ��FPU�汾.

//FPUģʽ��ʾ
#if __FPU_USED==1
#define SCORE_FPU_MODE                  "FPU On" 
#else
#define SCORE_FPU_MODE                  "FPU Off" 
#endif

#define 	ITERATION			128			//��������
#define	 	REAL_CONSTANT		0.285f		//ʵ������
#define	 	IMG_CONSTANT		0.01f		//�鲿����
//��ɫ��
u16 color_map[ITERATION];
//���������б�
const u16 zoom_ratio[] =
{
	120, 110, 100, 150, 200, 275, 350, 450,
	600, 800, 1000, 1200, 1500, 2000, 1500,
	1200, 1000, 800, 600, 450, 350, 275, 200,
	150, 100, 110,
}; 

//��ʼ����ɫ��
//clut:��ɫ��ָ��
void InitCLUT(u16 * clut)
{
 	u32 i=0x00;
	u16  red=0,green=0,blue=0;  
	for(i=0;i<ITERATION;i++)//������ɫ��
	{
		//����RGB��ɫֵ
		red=(i*8*256/ITERATION)%256;
		green=(i*6*256/ITERATION)%256;
		blue=(i*4*256 /ITERATION)%256; 
 		//��RGB888,ת��ΪRGB565
		red=red>>3;
		red=red<<11;
		green=green>>2;
		green=green<<5;
		blue=blue>>3; 
		clut[i]=red+green+blue;
	}
} 

//����Julia����ͼ��
//size_x,size_y:��Ļx,y����ĳߴ�
//offset_x,offset_y:��Ļx,y�����ƫ��
//zoom:��������
void GenerateJulia_fpu(u16 size_x,u16 size_y,u16 offset_x,u16 offset_y,u16 zoom)
{
	u8 i;
	u16 x,y;  
	float tmp1,tmp2;
	float num_real,num_img;
	float radius; 
	for(y=0;y<size_y;y++)
	{
       	for(x=0;x<size_x;x++)
   		{
       		num_real=y-offset_y;
         	num_real=num_real/zoom;
           	num_img=x-offset_x;
          	num_img=num_img/zoom;
           	i=0;
          	radius=0;
           	while((i<ITERATION-1)&&(radius<4))
           	{
           		tmp1=num_real*num_real;
               	tmp2=num_img*num_img;
              	num_img=2*num_real*num_img+IMG_CONSTANT;
             	num_real=tmp1-tmp2+REAL_CONSTANT;
               	radius=tmp1+tmp2;
              	i++;
           	}
			LCD->LCD_RAM=color_map[i];//���Ƶ���Ļ 
       	}
	}
}
u8 timeout;

int main(void)
{ 
	u8 key;
	u8 i=0;
	u8 autorun=0;
	float time; 
	u8 buf[50];
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	
	LED_Init();					//��ʼ��LED
	KEY_Init();
 	LCD_Init();
	TIM3_Int_Init(65535,8400-1);//10Khz����Ƶ��,����ʱ6.5�볬��
	POINT_COLOR=RED; 
	LCD_ShowString(30,50,200,16,16,"Mcudev STM32F4");	
	LCD_ShowString(30,70,200,16,16,"FPU TEST");	
	LCD_ShowString(30,90,200,16,16,"mcudev.taobao.com");
	LCD_ShowString(30,110,200,16,16,"2014/7/2");	
	LCD_ShowString(30,130,200,16,16,"KEY0:+    KEY1:-");	//��ʾ��ʾ��Ϣ
	LCD_ShowString(30,150,200,16,16,"KEY_UP:AUTO/MANUL");	//��ʾ��ʾ��Ϣ	
	delay_ms(1200);
	POINT_COLOR=BLUE;	//��������Ϊ��ɫ 
	InitCLUT(color_map);//��ʼ����ɫ��
	while(1)
	{
		key=KEY_Scan(0);
		switch(key)
		{
			case KEY0_PRES:
				i++;
				if(i>sizeof(zoom_ratio)/2-1)i=0;//���Ʒ�Χ
				break;
			case KEY1_PRES:
				if(i)i--;
				else i=sizeof(zoom_ratio)/2-1;
				break;
			case WKUP_PRES:
				autorun=!autorun;	//�Զ�/�ֶ�
				break;
		} 
		if(autorun==1)//�Զ�ʱ,�Զ�������������
		{
			i++;
			if(i>sizeof(zoom_ratio)/2-1)i=0;//���Ʒ�Χ
		}
		LCD_Set_Window(0,0,lcddev.width,lcddev.height);//���ô���
		LCD_WriteRAM_Prepare();
		TIM3->CNT=0;//����TIM3��ʱ���ļ�����ֵ
		timeout=0;
		GenerateJulia_fpu(lcddev.width,lcddev.height,lcddev.width/2,lcddev.height/2,zoom_ratio[i]);
		time=TIM3->CNT+(u32)timeout*65536;
		sprintf((char*)buf,"%s: zoom:%d  runtime:%0.1fms\r\n",SCORE_FPU_MODE,zoom_ratio[i],time/10);
		LCD_ShowString(5,lcddev.height-5-12,lcddev.width-5,12,12,buf);//��ʾ��ǰ�������	 
		printf("%s",buf);//���������
		LED0=!LED0;
	}
}
 
