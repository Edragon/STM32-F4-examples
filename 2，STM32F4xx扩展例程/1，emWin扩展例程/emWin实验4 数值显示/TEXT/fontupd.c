#include "fontupd.h"
#include "ff.h"
#include "w25qxx.h"
#include "ILI93xx.h"
#include "malloc.h"
//////////////////////////////////////////////////////////////////////////////////	 
 
//字库更新 驱动代码	   
//STM32F4工程----库函数版本
//淘宝店铺：http://mcudev.taobao.com								  
////////////////////////////////////////////////////////////////////////////////// 	 

//字库存放起始地址 
#define FONTINFOADDR 	1024*1024*10 					//Explorer STM32F4是从10M地址以后开始存放字库

//用于保存字库基本信息,地址,大小等
_font_info ftinfo;

//字库存放在sd卡中的路径
const u8 *GBK24_PATH="0:/SYSTEM/FONT/GBK24.FON";		//GBK24的存放位置
const u8 *GBK16_PATH="0:/SYSTEM/FONT/GBK16.FON";		//GBK16的存放位置
const u8 *GBK12_PATH="0:/SYSTEM/FONT/GBK12.FON";		//GBK12的存放位置
const u8 *UNIGBK_PATH="0:/SYSTEM/FONT/UNIGBK.BIN";		//UNIGBK.BIN的存放位置


//显示当前字体更新进度
//x,y:坐标
//size:字体大小
//fsize:整个文件大小
//pos:当前文件指针位置
u32 fupd_prog(u16 x,u16 y,u8 size,u32 fsize,u32 pos)
{
	float prog;
	u8 t = 0XFF;
	prog = (float)pos/fsize;
	prog *= 100;
	if(t!=prog)
	{
		LCD_ShowString(x+3*size/2,y,240,320,size,"%");
		t = prog;
		if(t>100) t = 100;
		LCD_ShowNum(x,y,t,3,size);//显示数值
	}
	return 0; 
}

//更新某一个
//x,y:坐标
//size:字体大小
//fxpath:路径
//fx:更新的内容 0,ungbk;1,gbk12;2,gbk16;3,gbk24;
//返回值:0,成功;其他,失败.
u8 updata_fontx(u16 x,u16 y,u8 size,u8 *fxpath,u8 fx)
{
	u32 flashaddr = 0;
	FIL *fftemp;
	u8 *tempbuf;
	u8 res;
	u16 bread;
	u32 offx = 0;
	u8 rval = 0;
	fftemp = (FIL*)mymalloc(SRAMIN,sizeof(FIL)); //分配内存
	if(fftemp == NULL) rval = 1;
	tempbuf = mymalloc(SRAMIN,4096);	//分配4096个字节
	if(tempbuf == NULL) rval =1;
	res = f_open(fftemp,(const TCHAR*)fxpath,FA_READ);
	if(res)rval = 2; //文件打开失败
	if(rval == 0)
	{
		switch(fx)
		{
			case 0:
				ftinfo.ugbkaddr = FONTINFOADDR + sizeof(ftinfo);
				ftinfo.ugbksize = fftemp->fsize;
				flashaddr = ftinfo.ugbkaddr;
				break;
			case 1:
				ftinfo.f12addr = ftinfo.ugbkaddr + ftinfo.ugbksize;
				ftinfo.gbk12size = fftemp->fsize;
				flashaddr = ftinfo.f12addr;
				break;
			case 2:
				ftinfo.f16addr = ftinfo.f12addr + ftinfo.gbk12size;
				ftinfo.gbk16size = fftemp->fsize;
				flashaddr = ftinfo.f16addr;
				break;
			case 3:
				ftinfo.f24addr = ftinfo.f16addr + ftinfo.gbk16size;
				ftinfo.gkb24size = fftemp->fsize;
				flashaddr = ftinfo.f24addr;
				break;
		}
		while(res == FR_OK)  //循环执行
		{
			res = f_read(fftemp,tempbuf,4096,(UINT*)&bread);
			if(res!=FR_OK)break;
			W25QXX_Write(tempbuf,offx+flashaddr,4096);
			offx += bread;
			fupd_prog(x,y,size,fftemp->fsize,offx);
			if(bread!=4096)break;
		}
		f_close(fftemp);
	}
	myfree(SRAMIN,fftemp); //释放内存
	myfree(SRAMIN,tempbuf);//释放内存
	return res;
}

//更新字体文件,UNIGBK,GBK12,GBK16,GBK24一起更新
//x,y:提示信息的显示地址
//size:字体大小
//提示信息字体大小										  
//返回值:0,更新成功;
//		 其他,错误代码.
u8 update_font(u16 x,u16 y,u8 size)
{
	u8 *gbk12_path=(u8*)GBK12_PATH;
	u8 *gbk16_path=(u8*)GBK16_PATH;
	u8 *gbk24_path=(u8*)GBK24_PATH;
	u8 *unigbk_path=(u8*)UNIGBK_PATH;
	u8 res;	
	res = 0XFF;
	ftinfo.fontok  = 0XFF;
	W25QXX_Write((u8*)&ftinfo,FONTINFOADDR,sizeof(ftinfo));	//清除之前字库成功的标志.防止更新到一半重启,导致的字库部分数据丢失.
	W25QXX_Read((u8*)&ftinfo,FONTINFOADDR,sizeof(ftinfo));	//重新读出ftinfo结构体数据
	LCD_ShowString(x,y,240,320,size,"Updating UNIGBK.BIN");	//更新UNIGBK.BIN
	res = updata_fontx(x+20*size/2,y,size,unigbk_path,0);
	if(res)return 1;
	
	LCD_ShowString(x,y,240,320,size,"Updating GBK12.BIN");	//更新GBK12.BIN
	res = updata_fontx(x+20*size/2,y,size,gbk12_path,1);
	if(res)return 2;
	
	LCD_ShowString(x,y,240,320,size,"Updating GBK16.BIN");	//更新GBK16.BIN
	res = updata_fontx(x+20*size/2,y,size,gbk16_path,2);
	if(res)return 3;
	
	LCD_ShowString(x,y,240,320,size,"Updating GBK24.BIN");	//更新GBK14.BIN
	res = updata_fontx(x+20*size/2,y,size,gbk24_path,3);
	if(res)return 4;
	
	//全部更新好
	ftinfo.fontok = 0XAA;
	W25QXX_Write((u8*)&ftinfo,FONTINFOADDR,sizeof(ftinfo));//保存字库信息
	return 0;  //无错误	
}


//初始化字体
//返回值:0,字库完好.
//		 其他,字库丢失
u8 font_init(void)
{
	W25QXX_Init();
	W25QXX_Read((u8*)&ftinfo,FONTINFOADDR,sizeof(ftinfo)); //读出ftinfo机构体数据
	if(ftinfo.fontok != 0XAA)return 1;  //字库错误
	return 0;
}


