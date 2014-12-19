#ifndef ONFF_SET_H
#define ONFF_SET_H
#include "ONFF_Screen.h"
#include "DF_PictureLibrary.h"
#include "DF_Windows.h"

typedef struct ONFF_SET
{
	gm_s32 imgGB;
	gm_s16 chose;
	GameState gamest;
	DF_Windows windows;
	DF_PictureLibrary * picLib;
	gm_s16 border;
}ONFFSet;

extern void initONFFSet(ONFFSet * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);

void ONFF_Set_Render(void *param);
void ONFF_Set_Update(void *param);
#endif