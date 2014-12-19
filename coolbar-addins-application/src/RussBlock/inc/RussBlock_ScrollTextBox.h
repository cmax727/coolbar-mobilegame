#ifndef RUSSBLOCK_SCORLLTEXTBOX_H
#define RUSSBLOCK_SCORLLTEXTBOX_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"
#include "coolbar_TextBox.h"

typedef struct RUSSBLOCK_SCROLLTEXTBOX
{
	gm_s16 offsetY;
	gm_s16 windowsHeight;
	gm_s16 scollHeight;
	gm_s16 imgScollTextBox[2];
	gm_s32 imgTitle[3];
	gm_s16 imgCmd;
	gm_s16 imgBottom;
	gm_s16 inx;
	gm_s16 count;
	DF_Windows windows;
	DF_PictureLibrary * picLib;
	TextBox textBox;
	TextBox textBox1;
}RussBlock_ScrollTextBox;

extern void initRussBlockScrollTextBox(RussBlock_ScrollTextBox * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib,gm_s16 w );
void RussBlock_ScrollTextBox_Windows_Render(void * param);
void RussBlock_ScrollTextBox_Winsows_Update(void * param);


#endif