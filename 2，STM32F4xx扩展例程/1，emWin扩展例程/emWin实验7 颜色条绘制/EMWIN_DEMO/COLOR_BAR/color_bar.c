#include "color_bar.h"

#define X_START 60  //颜色条开始X坐标
#define Y_START 40	//颜色条开始Y坐标 

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

//显示颜色条
static void _DemoShowColorBar(void) 
{
	GUI_RECT Rect;
	int      yStep;
	int      i;
	int      j;
	int      xSize;
	int      ySize;
	int      NumBars;    //要显示的颜色条数量2+2+2+1+2+2+2=13
	int      NumColors;  //要显示的颜色数量，这里有7个

	//获取显示尺寸
	xSize = LCD_GetXSize();
	ySize = LCD_GetYSize();

	//获取颜色条的数量
	NumColors = GUI_COUNTOF(_aBarData);  
	for (i = NumBars = 0, NumBars = 0; i < NumColors; i++) {
		NumBars += _aBarData[i].NumBars;
	}
	yStep = (ySize - Y_START) / NumBars;
 
	//显示文本
	Rect.x0 = 0;
	Rect.x1 = X_START - 1;
	Rect.y0 = Y_START;
	GUI_SetFont(&GUI_Font8x16);
	for (i = 0; i < NumColors; i++) {
		Rect.y1 = Rect.y0 + yStep * _aBarData[i].NumBars - 1;
		GUI_DispStringInRect(_aBarData[i].s, &Rect, GUI_TA_LEFT | GUI_TA_VCENTER);  //显示文本
		Rect.y0 = Rect.y1 + 1;
  }
	
	//显示颜色
	Rect.x0 = X_START;
	Rect.x1 = xSize - 1;
	Rect.y0 = Y_START;
	for (i = 0; i < NumColors; i++) {
		for (j = 0; j < _aBarData[i].NumBars; j++) {
		Rect.y1 = Rect.y0 + yStep - 1;
		GUI_DrawGradientH(Rect.x0, Rect.y0, Rect.x1, Rect.y1, _aColorStart[j], _aBarData[i].Color); //显示颜色
		Rect.y0 = Rect.y1 + 1;
		}
	}
}
//颜色条测试实验
void color_bar_test(void)
{
	GUI_SetBkColor(GUI_BLUE);
	GUI_SetColor(GUI_YELLOW);
	GUI_Clear();
	
	GUI_SetFont(&GUI_Font24_ASCII);
	GUI_SetTextMode(GUI_TM_TRANS);	//透明显示
	GUI_DispStringHCenterAt("COLOR_BAR TEST!",100,0);
	
	_DemoShowColorBar();   //显示颜色条
}

