#ifndef RUSSBLOCKPROPSHOP_H
#define RUSSBLOCKPROPSHOP_H


#include "DF_PictureLibrary.h"
#include "DF_Windows.h"
#include "coolbar_TextBox.h"

typedef struct RUSSBLOCKPROPSHOP
{
	gm_s16 imgPropBar;
	gm_s16 imgCmd;
	gm_s16 imgPropChoose;
    gm_s16 imgUI[3];
	gm_s16 imgMenuBar;
	TextBox textBox0;
	TextBox textBox1;
	TextBox textBox2;
	DF_Windows windows;
	DF_PictureLibrary * picLib;
}RussBlock_PropShop;

extern void initRussBlockPropShop(RussBlock_PropShop * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);


void RussBlock_PropShop_Windows_Render(void * param);
void RussBlock_PropShop_Windows_Update(void * param);


#endif