#include "lateclipping.h"

#include "GUI.h"
#include "WM.h"
#include "FRAMEWIN.h"
#include "BUTTON.h"

static WM_HWIN _hWin1;
static WM_HWIN _hWin2;
static WM_HWIN _hBut1;
static WM_HWIN _hBut2;
static int     _PaintCount1;
static int     _PaintCount2;

static GUI_COLOR _aColors[] = {
  0x0000FF, 0x00FF00, 0xFF0000, 0x00FFFF, 0xA000A0, 0xFFFF00
};


//�������ڻص�����
static void _cbBkWin(WM_MESSAGE *pMsg)
{
	switch(pMsg->MsgId)
	{
		case WM_PAINT:
			GUI_SetBkColor(GUI_BLACK);
			GUI_Clear();
			GUI_SetColor(0x0060FF);
			GUI_DispStringAt("PaintCount (Early):",0,0);
			GUI_DispDecAt(_PaintCount1,120,0,5);
			GUI_SetColor(0x00FFC0);
			GUI_DispStringAt("PaintCount (Late):",0,12);
			GUI_DispDecAt(_PaintCount2,120,12,5);
			break;
		case WM_NOTIFY_PARENT:
			if(pMsg->Data.v == WM_NOTIFICATION_RELEASED)  //��ť���ͷ�ʱ
			{
				if(pMsg->hWinSrc == _hBut1)	//button1���ͷ�
				{
					WM_InvalidateWindow(_hWin1); 	//����1ʧЧ
					WM_InvalidateWindow(_hWin2);	//����2ʧЧ		
				}else if(pMsg->hWinSrc == _hBut2)	//button2���ͷ�
				{
					_PaintCount1 = 0;
					_PaintCount2 = 0;
					WM_InvalidateWindow(pMsg->hWin); //������ʧЧ
				}
			}
			break;
			default:
				WM_DefaultProc(pMsg);	
	}
}


//���㴰�ڻص�����
static void _cbTop(WM_MESSAGE *pMsg)
{
	switch(pMsg->MsgId)
	{
		case WM_PAINT:
			GUI_SetBkColor(GUI_MAGENTA);
			GUI_Clear();
			break;
		default:
			WM_DefaultProc(pMsg);
	}
}

//��ܴ���1�ص�����
static void _cbFrameWin1(WM_MESSAGE *pMsg)
{
	switch(pMsg->MsgId)
	{
		case WM_PAINT:
			GUI_SetBkColor(_aColors[_PaintCount1 % 6]); //���ñ�����ɫ
			GUI_Clear();
			GUI_SetColor(0x0060FF);
			GUI_FillCircle(25,25,15);
			GUI_SetColor(GUI_BLACK);
			GUI_DrawCircle(25,25,15);
			_PaintCount1++;
			WM_InvalidateWindow(WM_HBKWIN); //��������ʧЧ
			break;
		default:
			WM_DefaultProc(pMsg);
	}
}

//��ܴ���2�ص�����
static void _cbFrameWin2(WM_MESSAGE *pMsg)
{
	switch(pMsg->MsgId)
	{
		case WM_PAINT:
			GUI_SetBkColor(_aColors[_PaintCount2 % 6]);
			GUI_Clear();
			GUI_SetColor(0x00FFC0);
			GUI_FillCircle(25,25,15);
			GUI_SetColor(GUI_BLACK);
			GUI_DrawCircle(25,25,15);
			_PaintCount2++;
			WM_InvalidateWindow(WM_HBKWIN);
			break;
		default:
			WM_DefaultProc(pMsg);
	}		
}


//���Ժ���
void _ShowDemo(void)
{
	WM_HWIN hWin0;
	WM_HWIN	hWin1;
	WM_HWIN hWin2;
	WM_HWIN	hFrame1;
	WM_HWIN hFrame2;
	WM_HWIN	hClient1;
	WM_HWIN hClient2;
	
	WM_SetCallback(WM_HBKWIN,_cbBkWin);
	hFrame1 = FRAMEWIN_CreateEx(10,30,140,140,0,WM_CF_SHOW,FRAMEWIN_CF_MOVEABLE,0,"Early Clipping",_cbFrameWin1); //������ܴ���1,���ƶ�
	hFrame2 = FRAMEWIN_CreateEx(170,30,140,140,0,WM_CF_SHOW,FRAMEWIN_CF_MOVEABLE,0,"Late Clipping",_cbFrameWin2); //������ܴ���2,���ƶ�
	hClient1= WM_GetClientWindow(hFrame1); 	//���ؿ��1�Ŀͻ��˴��ھ��
	hClient2= WM_GetClientWindow(hFrame2);	//���ؿ��2�Ŀͻ��˴��ھ��
	_hWin1 = WM_CreateWindowAsChild(0,0,WM_GetWindowSizeX(hClient1),WM_GetWindowSizeY(hClient2),hClient1,WM_CF_SHOW,_cbFrameWin1,0);
	_hWin2 = WM_CreateWindowAsChild(0,0,WM_GetWindowSizeX(hClient2),WM_GetWindowSizeY(hClient2),hClient2,WM_CF_SHOW|WM_CF_LATE_CLIP,_cbFrameWin2,0);
	_hBut1 = BUTTON_CreateEx(10,210,140,20,0,WM_CF_SHOW,0,1);	//������ť1
	_hBut2 = BUTTON_CreateEx(170,210,140,20,0,WM_CF_SHOW,0,2);	//������ť2
	hWin0 = FRAMEWIN_CreateEx(60,80,40,40,	0, 	WM_CF_SHOW|WM_CF_STAYONTOP,FRAMEWIN_CF_MOVEABLE,0,"Top 0",_cbTop);
	hWin1 = FRAMEWIN_CreateEx(220,80,40,40,	0,	WM_CF_SHOW|WM_CF_STAYONTOP,FRAMEWIN_CF_MOVEABLE,0,"Top 1",_cbTop);
	hWin2 = FRAMEWIN_CreateEx(140,170,40,40,0, 	WM_CF_SHOW|WM_CF_STAYONTOP,FRAMEWIN_CF_MOVEABLE,0,"Top 2",_cbTop);
	
	FRAMEWIN_SetResizeable(hWin0,1);  	//��������Ϊ������
	FRAMEWIN_SetResizeable(hWin1,1);	//��������Ϊ������
	FRAMEWIN_SetResizeable(hWin2,1);    //��������Ϊ������
	
	BUTTON_SetText(_hBut1,"Invalidate");	//���ð�ť������
	BUTTON_SetText(_hBut2,"Reset counts");	
	while(1)
	{
		GUI_Delay(50);
	}
}

