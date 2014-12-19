/*******************************************************************
* 
* 
* 文件名称：ONFF_Title.h

此功能是显示游戏中Logo界面
*******************************************************************/

#ifndef ONFF_TITLE_H
#define ONFF_TITLE_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"

typedef struct ONFF_TITLE
{
	gm_u16 timer;
	gm_s32 imgTitle;
	DF_Windows windows;
	DF_PictureLibrary * picLib;
}ONFFTitle;


extern void initONFFTitle(ONFFTitle * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);

void ONFF_Title_Windows_Render(void * param);
void ONFF_Title_Windows_Update(void * param);
#endif
