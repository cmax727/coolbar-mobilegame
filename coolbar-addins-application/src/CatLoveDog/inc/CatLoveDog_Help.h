#ifndef CATLOVEDOG_HELP_H
#define CATLOVEDOG_HELP_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"
#include "coolbar_TextBox.h"

typedef struct CatLoveDog_HELP
{
	DF_Windows windows;
	DF_PictureLibrary * picLib;
	TextBox textBox;  
	gm_s16 imghelpBorder;
}CatLoveDog_Help;

extern void initCatLoveDogHelp(CatLoveDog_Help * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
 void CatLoveDog_Help_Windows_Render(void * param);
 void CatLoveDog_Help_windows_Update(void * param);
#endif