#ifndef SAMEGAME_TITLEMENU_H
#define SAMEGAME_TITLEMENU_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"

typedef struct SAMEGAME_TITLE_MENU
{
	DF_PictureLibrary * picLib;
	DF_Windows windows;

	gm_s32 selectMenu;
}SameGameTitleMenu;

void SameGame_TitleMenu_Init(SameGameTitleMenu * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
void SameGame_TitleMenu_Render(void * param);//主菜单中绘制
void SameGame_TitleMenu_Update(void * param);//主菜单中刷新

#endif
