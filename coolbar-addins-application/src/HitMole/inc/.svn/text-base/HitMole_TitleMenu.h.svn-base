#ifndef HITMOLE_TITLEMENU_H
#define HITMOLE_TITLEMENU_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"

typedef struct HITMOLE_TITLE_MENU
{
	gm_s32 selectMenu;
	gm_s16 imgTitleMenu[2];//主菜单图片名
	DF_PictureLibrary * picLib;
	DF_Windows windows;
}HitMoleTitleMenu;
extern void initHitMoleTitleMenu(HitMoleTitleMenu * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);

void HitMole_TitleMenu_Render(void * param);//主菜单中绘制

void HitMole_TitleMenu_Update(void * param);//主菜单中刷新
#endif

