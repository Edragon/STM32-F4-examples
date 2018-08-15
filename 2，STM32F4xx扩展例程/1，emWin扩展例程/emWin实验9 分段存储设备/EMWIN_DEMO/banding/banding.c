#include "banding.h"
#include "GUI.h"

#define USE_BANDING_MEMDEV (1) //定义使用分段存储
#define SIZE_OF_ARRAY(Array) (sizeof(Array) / sizeof(Array[0]))

//多边形点坐标
static const GUI_POINT aPoints[] = {   
  {-50,  0},
  {-10, 10},
  {  0, 50},
  { 10, 10},
  { 50,  0},
  { 10,-10},
  {  0,-50},
  {-10,-10}
};

typedef struct 
{
	int XPos_Poly;
	int YPos_Poly;
	int XPos_Text;
	int YPos_Text;
	GUI_POINT aPointsDest[8];
} tDrawItContext;


static void _DrawIt(void * pData) 
{
	tDrawItContext * pDrawItContext = (tDrawItContext *)pData;
	GUI_Clear();
	GUI_SetFont(&GUI_Font8x8);
	GUI_SetTextMode(GUI_TM_TRANS);
 
	//绘制背景
	GUI_SetColor(GUI_GREEN);
	GUI_FillRect(pDrawItContext->XPos_Text, 
               pDrawItContext->YPos_Text - 25,
               pDrawItContext->XPos_Text + 100,
               pDrawItContext->YPos_Text - 5);
	//绘制多边形
	GUI_SetColor(GUI_BLUE);
	GUI_FillPolygon(pDrawItContext->aPointsDest, SIZE_OF_ARRAY(aPoints), 160, 120);
 
	//绘制前景
	GUI_SetColor(GUI_RED);
	GUI_FillRect(220 - pDrawItContext->XPos_Text, 
               pDrawItContext->YPos_Text + 5,
               220 - pDrawItContext->XPos_Text + 100,
               pDrawItContext->YPos_Text + 25);
}

//分段存储演示程序
void _DemoBandingMemdev(void) 
{
	tDrawItContext DrawItContext;
	int i, swap=0;
	GUI_SetBkColor(GUI_BLACK);
	GUI_Clear();
	GUI_SetColor(GUI_YELLOW);
	GUI_SetFont(&GUI_Font24_ASCII);
	GUI_DispStringHCenterAt("MEMDEV_Banding - Sample", 160, 5);
	GUI_SetFont(&GUI_Font16_ASCII);
	GUI_DispStringHCenterAt("Banding memory device\nwithout flickering", 160, 40);
	DrawItContext.XPos_Poly = 160;
	DrawItContext.YPos_Poly = 120;
	DrawItContext.YPos_Text = 116;
	while (1) 
	{
		swap = ~swap;
		for (i = 0; i < 220; i++) 
		{
			float angle = i * 3.1415926 / 55;
			DrawItContext.XPos_Text = (swap) ? i : 220 - i;
			//旋转多边形
			GUI_RotatePolygon(DrawItContext.aPointsDest, aPoints, 
							SIZE_OF_ARRAY(aPoints), angle);
			#if USE_BANDING_MEMDEV
			{
				GUI_RECT Rect = {0, 70, 320,170};
				GUI_MEMDEV_Draw(&Rect,&_DrawIt,&DrawItContext,0,0);//使用分段存储绘制
			}
			#else
				//如果没有开启分段存储的话就使用普通绘制方式
				_DrawIt((void *)&DrawItContext);
			#endif
		}
	}
}

