#ifndef ONFF_TITLEMENU_H
#define ONFF_TITLEMENU_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"

typedef struct ONFF_TITLE_MENU
{
	gm_s32 selectMenu;
	gm_s16 imgTitleMenu[2];
	DF_PictureLibrary * picLib;
	DF_Windows windows;
}ONFFTitleMenu;

extern void initONFFTitleMenu(ONFFTitleMenu * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);

void ONFF_TitleMenu_Render(void * param);

void ONFF_TitleMenu_Update(void * param);
void ONFF_MenuBar_Paint(DF_PictureLibrary * param,gm_s16 id,gm_s16 width,gm_s16 height,gm_s16 y);	

#endif
