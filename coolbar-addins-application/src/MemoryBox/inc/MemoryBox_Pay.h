#ifndef MEMORYBOX_PAY_H
#define MEMORYBOX_PAY_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"
#include "coolbar_TextBox.h"

typedef struct MEMORYBOX_PAY
{
	DF_Windows windows;
	DF_PictureLibrary * picLib;
	TextBox textBox;
	gm_s16 border;
}MemoryBox_Pay;

extern void initHitMolePay(MemoryBox_Pay * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
void MemoryBox_Pay_Windows_Render(void * param);
void MemoryBox_Pay_Windows_Update(void * param);
#endif