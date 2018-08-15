#include "numdisplay.h"

//emwin 数值显示例程
void numdisplay_demo(u16 x,u16 y)
{
	char* emwinversion;						//emwin版本号
	GUI_SetBkColor(GUI_BLUE);
	GUI_Clear();
	GUI_SetTextMode(GUI_TM_TRANS);			//透明显示模式
	
	GUI_SetFont(&GUI_Font24_ASCII);
	GUI_SetColor(GUI_YELLOW);
	GUI_DispStringHCenterAt("Mcudev NUM DISPLAY ",120,10);
	
	GUI_SetColor(GUI_RED);
	GUI_SetFont(&GUI_Font20_ASCII);
	
	GUI_DispStringAt("GUI_DispDecAt():",x,y);
	GUI_DispDecAt(200,x+150,y,3);			//显示数值200
	
	
	GUI_DispStringAt("GUI_DispFloat():",x,y+20);
	GUI_GotoXY(x+150,y+20);					//移动光标
	GUI_DispFloat(49.35,5);					//显示浮点数49.35
	GUI_DispString("   ");
	GUI_DispFloat(-0.345,6);				//显示浮点数-0.345
	
	GUI_DispStringAt("GUI_DispBinAt():",x,y+40);
	GUI_DispBinAt(8,x+150,y+40,4);				//显示十进制数8的二进制值	
	
	
	GUI_DispStringAt("GUI_DispHex():",x,y+60); 
	GUI_GotoXY(x+150,y+60);					//移动光标
	GUI_DispHex(100,3);						//显示十进制数100的16进制值
	
	GUI_DispStringAt("GUI_DispHexAt():",x,y+80);
	GUI_DispHexAt(100,x+150,y+80,3);		//在指定位置显示十进制数100的16进制值
	
	GUI_DispStringAt("GUI_GetVersionString():",x,y+100);
	emwinversion = (char*)GUI_GetVersionString(); 	//获取当前emwin版本号
	GUI_DispStringAt(emwinversion,x+200,y+100);		//显示emwin版本号
	
}

