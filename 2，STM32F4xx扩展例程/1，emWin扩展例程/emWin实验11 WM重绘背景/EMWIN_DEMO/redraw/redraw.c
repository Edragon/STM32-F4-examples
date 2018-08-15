#include "redraw.h"
#include "WM.h"

//背景窗口回调函数
static void _cbBkWindow(WM_MESSAGE *pMsg)
{
	switch(pMsg->MsgId) //根据不同的消息类型处理
	{
		case WM_PAINT:   //WM_PAIMNT消息，窗口重绘自身
			GUI_ClearRect(0,50,319,239);
			break;
		default:
			WM_DefaultProc(pMsg); //此函数可处理未处理的消息
	}
}

//窗口回调函数
static void _cbWindow(WM_MESSAGE *pMsg)
{
	GUI_RECT Rect;
	switch(pMsg->MsgId)
	{
		case WM_PAINT:
			WM_GetInsideRect(&Rect); //返回活动窗口减去边界后的尺寸
			GUI_SetBkColor(GUI_RED); //红色背景色
			GUI_SetColor(GUI_YELLOW);//黄色
			GUI_ClearRectEx(&Rect);	 //清除Rect区域,既绘制红色区域
			GUI_DrawRectEx(&Rect);	 //绘制Rect区域,既绘制黄色框框
			GUI_SetColor(GUI_BLACK); //黑色
			GUI_SetFont(&GUI_Font16_ASCII); //设置字体
			GUI_DispStringHCenterAt("Foreground Window",75,40);
			break;
		default:
			WM_DefaultProc(pMsg);
	}
}


//移动窗口
static void _MoveWindow(const char* pText)
{
	WM_HWIN hWnd;
	int i;
	//创建前景窗口
	hWnd = WM_CreateWindow(10,50,150,100,WM_CF_SHOW,_cbWindow,0);
	GUI_Delay(500);
	
	//移动前景窗口
	for(i=0;i<40;i++)
	{
		WM_MoveWindow(hWnd,2,2); //移动窗口
		GUI_Delay(10);
	}
	
	//删除窗口之前显示文本
	if(pText)
	{
		GUI_DispStringAt(pText,5,50);
		GUI_Delay(2500);
	}
	
	//删除前景窗口
	WM_DeleteWindow(hWnd); //删除窗口
	WM_Invalidate(WM_HBKWIN); //背景窗口无效
	GUI_Exec();
}


//窗口演示
void _DemoRedraw(void)
{
	WM_CALLBACK *_cbOldBK;
	GUI_SetBkColor(GUI_BLACK); 	//设置背景颜色
	GUI_Clear();
	GUI_SetColor(GUI_WHITE);	//白色
	GUI_SetFont(&GUI_Font24_ASCII);//设置字体
	GUI_DispStringHCenterAt("WM_Redraw-Sample",160,5);
	GUI_SetFont(&GUI_Font16B_ASCII); //设置字体
	while(1)
	{
		_MoveWindow("Background has not been redraw"); //移动窗口
		
		//清除背景
		GUI_ClearRect(0,50,319,239);
		GUI_Delay(1000);
		
		//为背景窗口设置回调函数
		_cbOldBK = WM_SetCallback(WM_HBKWIN,_cbBkWindow);
		
		//移动窗口
		_MoveWindow("Background has been redraw");
		
		//删除背景窗口的回调函数
		WM_SetCallback(WM_HBKWIN,_cbOldBK);		
	}
}

