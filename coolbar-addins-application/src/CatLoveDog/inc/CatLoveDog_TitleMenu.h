#ifndef CATLOVEDOG_TITLEMENU_H
#define CATLOVEDOG_TITLEMENU_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"

typedef struct CatLoveDog_TITLE_MENU
{
	gm_s32 selectMenu;
	gm_s16 imgTitleMenu[2];
	DF_PictureLibrary * picLib;
	DF_Windows windows;
}CatLoveDogTitleMenu;

extern void initCatLoveDogTitleMenu(CatLoveDogTitleMenu * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);

void CatLoveDog_TitleMenu_Render(void * param);

void CatLoveDog_TitleMenu_Update(void * param);
void CatLoveDog_MenuBar_Paint(DF_PictureLibrary * param,gm_s16 id,gm_s16 width,gm_s16 height,gm_s16 y);	

#endif
