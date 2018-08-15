#include "numdisplay.h"

//emwin ��ֵ��ʾ����
void numdisplay_demo(u16 x,u16 y)
{
	char* emwinversion;						//emwin�汾��
	GUI_SetBkColor(GUI_BLUE);
	GUI_Clear();
	GUI_SetTextMode(GUI_TM_TRANS);			//͸����ʾģʽ
	
	GUI_SetFont(&GUI_Font24_ASCII);
	GUI_SetColor(GUI_YELLOW);
	GUI_DispStringHCenterAt("Mcudev NUM DISPLAY ",120,10);
	
	GUI_SetColor(GUI_RED);
	GUI_SetFont(&GUI_Font20_ASCII);
	
	GUI_DispStringAt("GUI_DispDecAt():",x,y);
	GUI_DispDecAt(200,x+150,y,3);			//��ʾ��ֵ200
	
	
	GUI_DispStringAt("GUI_DispFloat():",x,y+20);
	GUI_GotoXY(x+150,y+20);					//�ƶ����
	GUI_DispFloat(49.35,5);					//��ʾ������49.35
	GUI_DispString("   ");
	GUI_DispFloat(-0.345,6);				//��ʾ������-0.345
	
	GUI_DispStringAt("GUI_DispBinAt():",x,y+40);
	GUI_DispBinAt(8,x+150,y+40,4);				//��ʾʮ������8�Ķ�����ֵ	
	
	
	GUI_DispStringAt("GUI_DispHex():",x,y+60); 
	GUI_GotoXY(x+150,y+60);					//�ƶ����
	GUI_DispHex(100,3);						//��ʾʮ������100��16����ֵ
	
	GUI_DispStringAt("GUI_DispHexAt():",x,y+80);
	GUI_DispHexAt(100,x+150,y+80,3);		//��ָ��λ����ʾʮ������100��16����ֵ
	
	GUI_DispStringAt("GUI_GetVersionString():",x,y+100);
	emwinversion = (char*)GUI_GetVersionString(); 	//��ȡ��ǰemwin�汾��
	GUI_DispStringAt(emwinversion,x+200,y+100);		//��ʾemwin�汾��
	
}

