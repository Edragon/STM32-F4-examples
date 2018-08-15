#include "bitmapdisplay.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "arm_math.h"

extern GUI_BITMAP bm2_128X128;  // 图标

//显示位图
void draw_bitmap(void)
{
	GUI_SetBkColor(GUI_BLUE);
	GUI_SetColor(GUI_YELLOW);
	GUI_Clear();
	
	GUI_SetFont(&GUI_Font24_ASCII);
	GUI_SetTextMode(GUI_TM_TRANS);	//透明显示
	GUI_DispStringHCenterAt("Mcudev BITMAP DISPLAY",50,0 );
	
	GUI_DrawBitmap(&bm2_128X128,100,100);  //绘制图标	
}

//在显示器中缩放位图
void zoom_bitmap(int Xmag,int Ymag)
{
	GUI_SetBkColor(GUI_BLUE);
	GUI_Clear();
	GUI_DrawBitmapEx(&bm2_128X128,220,90,105,46,Xmag,Ymag); //按照比例绘制位图
}
