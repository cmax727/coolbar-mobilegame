#ifndef SAMEGAME_ABOUT_H
#define SAMEGAME_ABOUT_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"
#include "coolbar_TextBox.h"

typedef struct SAMEGAME_PLAY_MENU
{
	DF_Windows windows;//游戏帮助界面窗口
	DF_PictureLibrary * picLib;//游戏帮助得到图片库

	gm_s16 selectMenu;
}SameGamePlayMenu;

void SameGame_PlayMenu_Init(SameGamePlayMenu * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
void SameGame_PlayMenu_Render(void * param);//帮助界面绘制区域
void SameGame_PlayMenu_Update(void * param);//帮助界面按键控制

#endif

