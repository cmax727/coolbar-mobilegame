/*******************************************************************
* 2009 Wingtech, Incoporated. All Rights Reserved.
* 
* 文件名称：RussBlock_Title.h

此功能是显示游戏中Logo界面
*******************************************************************/

#ifndef RUSSBLOCK_TITLE_H
#define RUSSBLOCK_TITLE_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"

typedef struct RUSSBLOCK_TITLE
{
	gm_s16 counter;
	gm_s32 imgTitle[4];//Logo图片名
	DF_Windows windows;//Logo窗口界面
	DF_PictureLibrary * picLib;//Logo图片库
}RussBlockTitle;


extern void initRussBlockTitle(RussBlockTitle * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);

void RussBlock_Title_Windows_Render(void * param);//Logo界面绘制

void RussBlock_Title_Windows_Update(void * param);//Logo界面刷新

#endif 