#include "GUI.h"
#include "includes.h" //因为使用UCOS所以此处应该包含UCOS的代码


/*
*********************************************************************************************************
*                                         GLOBAL VARIABLES
*********************************************************************************************************
*/

static OS_EVENT *DispSem;  	//显示的信号量
static OS_EVENT *EventMbox; //消息邮箱

static OS_EVENT	*KeySem;  	//按键信号量
static int			KeyPressed;
static char			KeyIsInited;

/*
*********************************************************************************************************
*                                        TIMING FUNCTIONS
*
* Notes: Some timing dependent routines of uC/GUI require a GetTime and delay funtion. 
*        Default time unit (tick), normally is 1 ms.
*********************************************************************************************************
*/
int GUI_X_GetTime(void) { 
	
  return ((int)OSTimeGet());   //获取系统时间,此处时间单元为1ms

}

//GUI延时函数
void GUI_X_Delay(int period) { 
	
	INT32U ticks;
	
	ticks = (period * 1000) / OS_TICKS_PER_SEC; 
	OSTimeDly(ticks);
}

/*
*********************************************************************************************************
*                                          GUI_X_ExecIdle()
*********************************************************************************************************
*/
void GUI_X_ExecIdle(void)
{
	
	GUI_X_Delay(1);
	
}

/*
*********************************************************************************************************
*                                    MULTITASKING INTERFACE FUNCTIONS
*
* Note(1): 1) The following routines are required only if uC/GUI is used in a true multi task environment, 
*             which means you have more than one thread using the uC/GUI API.  In this case the #define 
*             GUI_OS 1   needs to be in GUIConf.h
*********************************************************************************************************
*/
void GUI_X_InitOS(void)
{
	
	DispSem = OSSemCreate(1);  //创建初始值为1的信号量
	EventMbox = OSMboxCreate((void*)0); //创建消息邮箱
}

void GUI_X_Lock(void)
{
	INT8U err;
	OSSemPend(DispSem,0,&err); //请求信号量
}

void GUI_X_Unlock(void)
{
	OSSemPost(DispSem); 		//发送信号量
}

U32 GUI_X_GetTaskId(void)
{
	return ((U32)(OSTCBCur->OSTCBPrio)); //获取任务优先级,也就是任务ID
}

/*
*********************************************************************************************************
*                                        GUI_X_WaitEvent()
*                                        GUI_X_SignalEvent()
*********************************************************************************************************
*/
void GUI_X_WaitEvent(void)
{
	INT8U err;
	(void)OSMboxPend(EventMbox,0,&err); //请求消息邮箱
}

void GUI_X_SignalEvent(void)
{
	(void)OSMboxPost(EventMbox,(void*)1); //发送消息邮箱
}
/*
*********************************************************************************************************
*                                      KEYBOARD INTERFACE FUNCTIONS
*
* Purpose: The keyboard routines are required only by some widgets.
*          If widgets are not used, they may be eliminated.
*
* Note(s): If uC/OS-II is used, characters typed into the log window will be placed	in the keyboard buffer. 
*          This is a neat feature which allows you to operate your target system without having to use or 
*          even to have a keyboard connected to it. (useful for demos !)
*********************************************************************************************************
*/

static void CheckInit(void)
{
	if(KeyIsInited == OS_FALSE){
		KeyIsInited = OS_TRUE;
		GUI_X_Init();
	}
}

void GUI_X_Init(void)
{

	KeySem = OSSemCreate(0); //创建初始值为0的信号量
	
}

int GUI_X_GetKey(void) 
{
	int r;
	
	r = KeyPressed;
	CheckInit();
	KeyPressed = 0;
	return (r);
}

int GUI_X_WaitKey(void)
{
	int r;
	INT8U err;
	
	CheckInit();
	if(KeyPressed == 0)
	{
		OSSemPend(KeySem,0,&err); //请求信号量
	}
	r = KeyPressed;
	KeyPressed = 0;
	return (r);
}

void GUI_X_StoreKey(int k)
{
	KeyPressed = k;
	OSSemPost(KeySem);
}

/*********************************************************************
*
*      Logging: OS dependent

Note:
  Logging is used in higher debug levels only. The typical target
  build does not use logging and does therefor not require any of
  the logging routines below. For a release build without logging
  the routines below may be eliminated to save some space.
  (If the linker is not function aware and eliminates unreferenced
  functions automatically)

*/

void GUI_X_Log     (const char *s) { GUI_USE_PARA(s); }
void GUI_X_Warn    (const char *s) { GUI_USE_PARA(s); }
void GUI_X_ErrorOut(const char *s) { GUI_USE_PARA(s); }

