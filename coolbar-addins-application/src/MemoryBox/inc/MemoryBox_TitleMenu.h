#ifndef MEMORYBOX_TITLEMENU_H
#define MEMORYBOX_TITLEMENU_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"

typedef struct MEMORYBOX_TITLE_MENU
{
	gm_s32 selectMenu;
	gm_s16 imgTitleMenu[2];//主菜单图片名
	DF_PictureLibrary * picLib;
	DF_Windows windows;
}MemoryBoxTitleMenu;
extern void initMemoryBoxTitleMenu(MemoryBoxTitleMenu * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);

void MemoryBox_TitleMenu_Render(void * param);//主菜单中绘制

void MemoryBox_TitleMenu_Update(void * param);//主菜单中刷新
#endif

