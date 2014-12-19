/*******************************************************************
* 
* 
* �ļ����ƣ�HitMole_Title.h

�˹�������ʾ��Ϸ��Logo����
*******************************************************************/

#ifndef HITMOLE_TITLE_H
#define HITMOLE_TITLE_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"

typedef struct HITMOLE_TITLE
{
	gm_u16 timer;
	gm_s32 imgTitle;//LogoͼƬ��
	DF_Windows windows;//Logo���ڽ���
	DF_PictureLibrary * picLib;//LogoͼƬ��
}HitMoleTitle;


extern void initHitMoleTitle(HitMoleTitle * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);

void HitMole_Title_Windows_Render(void * param);//Logo�������

void HitMole_Title_Windows_Update(void * param);//Logo����ˢ��
#endif
