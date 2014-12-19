/*******************************************************************
* 
* 
* 文件名称：SameGame_Title.h

此功能是显示游戏中Logo界面
*******************************************************************/

#ifndef SAMEGAME_TITLE_H
#define SAMEGAME_TITLE_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"

typedef struct SAMEGAME_LOGO
{
	DF_Windows windows;//Logo窗口界面
	DF_PictureLibrary * picLib;//Logo图片库

	gm_u16 timer;
	gm_s32 imgLogo;//Logo图片名
}SameGameLogo;

void SameGame_Logo_Init(SameGameLogo * myself, Rect DF_Windows_Rect, DF_PictureLibrary* picLib);
void SameGame_Logo_Render(void * param);//Logo界面绘制
void SameGame_Logo_Update(void * param);//Logo界面刷新

#endif
