#ifndef ONFF_PAY_H
#define ONFF_PAY_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"
#include "coolbar_TextBox.h"

typedef struct ONFF_PAY
{
	DF_Windows windows;
	DF_PictureLibrary * picLib;
	TextBox textBox;
	gm_s16 border;
}ONFF_Pay;

extern void initONFFPay(ONFF_Pay * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
void ONFF_Pay_Windows_Render(void * param);
void ONFF_Pay_Windows_Update(void * param);
#endif