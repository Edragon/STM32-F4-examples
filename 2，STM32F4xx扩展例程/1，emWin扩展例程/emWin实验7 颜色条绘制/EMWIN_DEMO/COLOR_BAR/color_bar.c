#include "color_bar.h"

#define X_START 60  //��ɫ����ʼX����
#define Y_START 40	//��ɫ����ʼY���� 

typedef struct {
	int NumBars;
	GUI_COLOR Color;
	const char * s;
} BAR_DATA;  


static const BAR_DATA _aBarData[] = {
	{ 2, GUI_RED    , "Red" },
	{ 2, GUI_GREEN  , "Green" },
	{ 2, GUI_BLUE   , "Blue" },
	{ 1, GUI_WHITE  , "Grey" },
	{ 2, GUI_YELLOW , "Yellow" },
	{ 2, GUI_CYAN   , "Cyan" },
	{ 2, GUI_MAGENTA, "Magenta" },
};

static const GUI_COLOR _aColorStart[] = { GUI_BLACK, GUI_WHITE };

//��ʾ��ɫ��
static void _DemoShowColorBar(void) 
{
	GUI_RECT Rect;
	int      yStep;
	int      i;
	int      j;
	int      xSize;
	int      ySize;
	int      NumBars;    //Ҫ��ʾ����ɫ������2+2+2+1+2+2+2=13
	int      NumColors;  //Ҫ��ʾ����ɫ������������7��

	//��ȡ��ʾ�ߴ�
	xSize = LCD_GetXSize();
	ySize = LCD_GetYSize();

	//��ȡ��ɫ��������
	NumColors = GUI_COUNTOF(_aBarData);  
	for (i = NumBars = 0, NumBars = 0; i < NumColors; i++) {
		NumBars += _aBarData[i].NumBars;
	}
	yStep = (ySize - Y_START) / NumBars;
 
	//��ʾ�ı�
	Rect.x0 = 0;
	Rect.x1 = X_START - 1;
	Rect.y0 = Y_START;
	GUI_SetFont(&GUI_Font8x16);
	for (i = 0; i < NumColors; i++) {
		Rect.y1 = Rect.y0 + yStep * _aBarData[i].NumBars - 1;
		GUI_DispStringInRect(_aBarData[i].s, &Rect, GUI_TA_LEFT | GUI_TA_VCENTER);  //��ʾ�ı�
		Rect.y0 = Rect.y1 + 1;
  }
	
	//��ʾ��ɫ
	Rect.x0 = X_START;
	Rect.x1 = xSize - 1;
	Rect.y0 = Y_START;
	for (i = 0; i < NumColors; i++) {
		for (j = 0; j < _aBarData[i].NumBars; j++) {
		Rect.y1 = Rect.y0 + yStep - 1;
		GUI_DrawGradientH(Rect.x0, Rect.y0, Rect.x1, Rect.y1, _aColorStart[j], _aBarData[i].Color); //��ʾ��ɫ
		Rect.y0 = Rect.y1 + 1;
		}
	}
}
//��ɫ������ʵ��
void color_bar_test(void)
{
	GUI_SetBkColor(GUI_BLUE);
	GUI_SetColor(GUI_YELLOW);
	GUI_Clear();
	
	GUI_SetFont(&GUI_Font24_ASCII);
	GUI_SetTextMode(GUI_TM_TRANS);	//͸����ʾ
	GUI_DispStringHCenterAt("COLOR_BAR TEST!",100,0);
	
	_DemoShowColorBar();   //��ʾ��ɫ��
}

