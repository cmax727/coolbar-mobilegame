/*******************************************************************
* 2009 Wingtech, Incoporated. All Rights Reserved.
* 
* 文件名称：RussBlock_TitleMenu.h

此功能是显示游戏中主菜单界面
*******************************************************************/

#ifndef RUSSBLOCK_TITLEMENU_H
#define RUSSBLOCK_TITLEMENU_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"

typedef struct RUSSBLOCK_TITLE_MENU
{
	gm_s32 selectMenu;
	gm_s16 imgTitleMenu[6];//主菜单图片名
	gm_s16 imgMenuBar;
	gm_s16 imgCmd;
	DF_PictureLibrary * picLib;
	DF_Windows windows;
}RussBlockTitleMenu;
//初使化主菜单界面
extern void initRussBlockTitleMenu(RussBlockTitleMenu * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);

void RussBlock_TitleMenu_Render(void * param);//主菜单中绘制

void RussBlock_TitleMenu_Update(void * param);//主菜单中刷新
/*画菜单后背景 参数 width，height须为 MENUBARWIDTH,MENUBARHEIGHT 的整数倍 ,y 为y坐标*/
void RussBlock_MenuBar_Paint(DF_PictureLibrary * param,gm_s16 id,gm_s16 width,gm_s16 height,gm_s16 y);	





#endif
