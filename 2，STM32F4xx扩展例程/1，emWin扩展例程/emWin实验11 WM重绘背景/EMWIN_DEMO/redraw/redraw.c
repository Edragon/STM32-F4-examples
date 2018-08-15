#include "redraw.h"
#include "WM.h"

//�������ڻص�����
static void _cbBkWindow(WM_MESSAGE *pMsg)
{
	switch(pMsg->MsgId) //���ݲ�ͬ����Ϣ���ʹ���
	{
		case WM_PAINT:   //WM_PAIMNT��Ϣ�������ػ�����
			GUI_ClearRect(0,50,319,239);
			break;
		default:
			WM_DefaultProc(pMsg); //�˺����ɴ���δ�������Ϣ
	}
}

//���ڻص�����
static void _cbWindow(WM_MESSAGE *pMsg)
{
	GUI_RECT Rect;
	switch(pMsg->MsgId)
	{
		case WM_PAINT:
			WM_GetInsideRect(&Rect); //���ػ���ڼ�ȥ�߽��ĳߴ�
			GUI_SetBkColor(GUI_RED); //��ɫ����ɫ
			GUI_SetColor(GUI_YELLOW);//��ɫ
			GUI_ClearRectEx(&Rect);	 //���Rect����,�Ȼ��ƺ�ɫ����
			GUI_DrawRectEx(&Rect);	 //����Rect����,�Ȼ��ƻ�ɫ���
			GUI_SetColor(GUI_BLACK); //��ɫ
			GUI_SetFont(&GUI_Font16_ASCII); //��������
			GUI_DispStringHCenterAt("Foreground Window",75,40);
			break;
		default:
			WM_DefaultProc(pMsg);
	}
}


//�ƶ�����
static void _MoveWindow(const char* pText)
{
	WM_HWIN hWnd;
	int i;
	//����ǰ������
	hWnd = WM_CreateWindow(10,50,150,100,WM_CF_SHOW,_cbWindow,0);
	GUI_Delay(500);
	
	//�ƶ�ǰ������
	for(i=0;i<40;i++)
	{
		WM_MoveWindow(hWnd,2,2); //�ƶ�����
		GUI_Delay(10);
	}
	
	//ɾ������֮ǰ��ʾ�ı�
	if(pText)
	{
		GUI_DispStringAt(pText,5,50);
		GUI_Delay(2500);
	}
	
	//ɾ��ǰ������
	WM_DeleteWindow(hWnd); //ɾ������
	WM_Invalidate(WM_HBKWIN); //����������Ч
	GUI_Exec();
}


//������ʾ
void _DemoRedraw(void)
{
	WM_CALLBACK *_cbOldBK;
	GUI_SetBkColor(GUI_BLACK); 	//���ñ�����ɫ
	GUI_Clear();
	GUI_SetColor(GUI_WHITE);	//��ɫ
	GUI_SetFont(&GUI_Font24_ASCII);//��������
	GUI_DispStringHCenterAt("WM_Redraw-Sample",160,5);
	GUI_SetFont(&GUI_Font16B_ASCII); //��������
	while(1)
	{
		_MoveWindow("Background has not been redraw"); //�ƶ�����
		
		//�������
		GUI_ClearRect(0,50,319,239);
		GUI_Delay(1000);
		
		//Ϊ�����������ûص�����
		_cbOldBK = WM_SetCallback(WM_HBKWIN,_cbBkWindow);
		
		//�ƶ�����
		_MoveWindow("Background has been redraw");
		
		//ɾ���������ڵĻص�����
		WM_SetCallback(WM_HBKWIN,_cbOldBK);		
	}
}

