/*******************************************************************
* 2009 Wingtech, Incoporated. All Rights Reserved.
* 
* �ļ����ƣ�RussBlock_Title.h

�˹�������ʾ��Ϸ��Logo����
*******************************************************************/

#ifndef RUSSBLOCK_TITLE_H
#define RUSSBLOCK_TITLE_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"

typedef struct RUSSBLOCK_TITLE
{
	gm_s16 counter;
	gm_s32 imgTitle[4];//LogoͼƬ��
	DF_Windows windows;//Logo���ڽ���
	DF_PictureLibrary * picLib;//LogoͼƬ��
}RussBlockTitle;


extern void initRussBlockTitle(RussBlockTitle * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);

void RussBlock_Title_Windows_Render(void * param);//Logo�������

void RussBlock_Title_Windows_Update(void * param);//Logo����ˢ��

#endif 