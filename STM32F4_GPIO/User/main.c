#include "stm32f4xx.h"

#define ON  0
#define OFF 1

#define key (GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_4))

#define LED(a) if(a)\
								GPIO_SetBits(GPIOC,0XFFCF );\
								else\
								GPIO_ResetBits(GPIOC,0XFFCF )

void LED_Configuration(void);
void delay(unsigned long int time);


/*
 * 函数名：main
 * 描述  ：主函数体
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
int main(void)
{

    SystemInit();
    LED_Configuration();
    while (1)
    {
        LED(ON);
			
        delay(6000000);
        LED(OFF);
		
        delay(6000000);
			if(!key)
				{
					GPIO_SetBits(GPIOC,0x0020 );
				}
			else
				{	
					GPIO_ResetBits(GPIOC,0x0020 );
				}
				
			
    }
}


/*
 * 函数名：LED_Configuration
 * 描述  ：LED GPIO口配置
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 */
void LED_Configuration(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;  //声明一个 初始化GPIO口时候用的 结构体
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC , ENABLE); //使能PI口的时钟，否则端口是不工作的
    GPIO_InitStructure.GPIO_Pin = 0XFFEF ; //对结构体的GPIO_Pin对象赋值，声明要操作的是11端口
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//对结构体的GPIO_Mode对象赋值，声明IO口的模式是输出
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//对结构体的GPIO_OType对象赋值，声明IO口的结构是推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//对结构体的GPIO_Speed对象赋值，声明速度是100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL; //对结构体的GPIO_PuPd对象赋值，声明内部上拉
    GPIO_Init(GPIOC, &GPIO_InitStructure);//将结构体带入初始化函数中，执行初始化，否则之前设置都是无效的
	
	  GPIO_InitStructure.GPIO_Pin = 0X0010 ; //对结构体的GPIO_Pin对象赋值，声明要操作的是11端口
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//对结构体的GPIO_Mode对象赋值，声明IO口的模式是输出
    //GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//对结构体的GPIO_OType对象赋值，声明IO口的结构是推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//对结构体的GPIO_Speed对象赋值，声明速度是100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //对结构体的GPIO_PuPd对象赋值，声明内部上拉
    GPIO_Init(GPIOC, &GPIO_InitStructure);//将结构体带入初始化函数中，执行初始化，否则之前设置都是无效的
	
	
	
}


void delay(unsigned long int time)
{
    while(time--);
}

/******************* (C) COPYRIGHT 2012 Richards *****END OF FILE***************/
