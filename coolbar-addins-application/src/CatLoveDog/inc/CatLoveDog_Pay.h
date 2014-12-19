#ifndef CATLOVEDOG_PAY_H
#define  CATLOVEDOG_PAY_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"
#include "coolbar_TextBox.h"

typedef struct CATLOVEDOG_PAY
{
	DF_Windows windows;
	DF_PictureLibrary * picLib;
	TextBox textBox;
	gm_s16 border;
}CatLoveDog_Pay;

extern void initCatLoveDogPay(CatLoveDog_Pay * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
void CatLoveDog_Pay_Windows_Render(void * param);
void CatLoveDog_Pay_Windows_Update(void * param);
#endif
