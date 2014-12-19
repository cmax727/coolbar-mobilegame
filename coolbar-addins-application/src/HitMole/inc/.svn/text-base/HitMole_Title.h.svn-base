/*******************************************************************
* 
* 
* 文件名称：HitMole_Title.h

此功能是显示游戏中Logo界面
*******************************************************************/

#ifndef HITMOLE_TITLE_H
#define HITMOLE_TITLE_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"

typedef struct HITMOLE_TITLE
{
	gm_u16 timer;
	gm_s32 imgTitle;//Logo图片名
	DF_Windows windows;//Logo窗口界面
	DF_PictureLibrary * picLib;//Logo图片库
}HitMoleTitle;


extern void initHitMoleTitle(HitMoleTitle * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);

void HitMole_Title_Windows_Render(void * param);//Logo界面绘制

void HitMole_Title_Windows_Update(void * param);//Logo界面刷新
#endif
