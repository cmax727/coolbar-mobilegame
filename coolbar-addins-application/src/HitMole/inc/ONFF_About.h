#ifndef ONFF_ABOUT_H
#define ONFF_ABOUT_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"
#include "coolbar_TextBox.h"

typedef struct ONFF_ABOUT
{
	DF_Windows windows;
	DF_PictureLibrary * picLib;
	TextBox textBox;
	gm_s16 border;
}ONFF_About;

extern void initONFFAbout(ONFF_About * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
 void ONFF_About_Windows_Render(void * param);
 void ONFF_About_windows_Update(void * param);
 void InitAbout(ONFF_About * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
#endif

