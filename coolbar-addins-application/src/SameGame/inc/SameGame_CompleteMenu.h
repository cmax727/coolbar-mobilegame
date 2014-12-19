#ifndef SAMEGAME_EXERSICE_H
#define SAMEGAME_EXERSICE_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"

typedef struct SAMEGAME_CMPLETE_MENU
{
	DF_Windows windows;//游戏帮助界面窗口
	DF_PictureLibrary * picLib;//游戏帮助得到图片库	

	gm_s16 selectnum;
}SameGameCompleteMenu;

void SameGame_CompleteMenu_Init(SameGameCompleteMenu * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
void SameGame_CompleteMenu_Render(void * param);//帮助界面绘制区域
void SameGame_CompleteMenu_Update(void * param);//帮助界面按键控制

#endif