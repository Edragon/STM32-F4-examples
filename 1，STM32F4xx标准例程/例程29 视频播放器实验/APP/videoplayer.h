#ifndef __VIDEOPLAYER_H
#define __VIDEOPLAYER_H 
#include <stm32f4xx.h> 
#include "avi.h"
#include "ff.h"
//////////////////////////////////////////////////////////////////////////////////	 
 
//��Ƶ������ Ӧ�ô���	   
//STM32F4��������-�⺯���汾
//�Ա����̣�http://mcudev.taobao.com								  
////////////////////////////////////////////////////////////////////////////////// 	
 
 
#define AVI_AUDIO_BUF_SIZE    1024*5		//����avi����ʱ,��Ƶbuf��С.
#define AVI_VIDEO_BUF_SIZE    1024*60		//����avi����ʱ,��Ƶbuf��С.


void video_play(void);
u8 video_play_mjpeg(u8 *pname); 
void video_time_show(FIL *favi,AVI_INFO *aviinfo);
void video_info_show(AVI_INFO *aviinfo);
void video_bmsg_show(u8* name,u16 index,u16 total);
u16 video_get_tnum(u8 *path);
u8 video_seek(FIL *favi,AVI_INFO *aviinfo,u8 *mbuf);

#endif

