/*******************************************************************
* 
* 
* �ļ����ƣ�CatLoveDog_Title.h

�˹�������ʾ��Ϸ��Logo����
*******************************************************************/

#ifndef CATLOVEDOG_TITLE_H
#define CATLOVEDOG_TITLE_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"

typedef struct CatLoveDog_TITLE
{
	gm_u16 timer;
	gm_s32 imgTitle;
	DF_Windows windows;
	DF_PictureLibrary * picLib;
}CatLoveDogTitle;


extern void initCatLoveDogTitle(CatLoveDogTitle * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);

void CatLoveDog_Title_Windows_Render(void * param);
void CatLoveDog_Title_Windows_Update(void * param);
#endif
