
#ifndef ONFF_HELP_H
#define ONFF_HELP_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"
#include "coolbar_TextBox.h"

typedef struct ONFF_HELP
{
	DF_Windows windows;
	DF_PictureLibrary * picLib;
	TextBox textBox;  
	gm_s16 border;
}ONFF_Help;

extern void initONFFHelp(ONFF_Help * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
 void ONFF_Help_Windows_Render(void * param);
 void ONFF_Help_windows_Update(void * param);
#endif