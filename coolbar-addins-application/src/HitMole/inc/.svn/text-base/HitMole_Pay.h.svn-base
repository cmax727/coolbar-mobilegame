#ifndef HITMOLE_PAY_H
#define HITMOLE_PAY_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"
#include "coolbar_TextBox.h"

typedef struct HITMOLE_PAY
{
	DF_Windows windows;
	DF_PictureLibrary * picLib;
	TextBox textBox;
	gm_s16 border;
}HitMole_Pay;

extern void initHitMolePay(HitMole_Pay * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
void HitMole_Pay_Windows_Render(void * param);
void HitMole_Pay_Windows_Update(void * param);
#endif