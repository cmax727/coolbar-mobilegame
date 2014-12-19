/*******************************************************************
* 
* 
* �ļ����ƣ�SameGame_Title.h

�˹�������ʾ��Ϸ��Logo����
*******************************************************************/

#ifndef SAMEGAME_TITLE_H
#define SAMEGAME_TITLE_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"

typedef struct SAMEGAME_LOGO
{
	DF_Windows windows;//Logo���ڽ���
	DF_PictureLibrary * picLib;//LogoͼƬ��

	gm_u16 timer;
	gm_s32 imgLogo;//LogoͼƬ��
}SameGameLogo;

void SameGame_Logo_Init(SameGameLogo * myself, Rect DF_Windows_Rect, DF_PictureLibrary* picLib);
void SameGame_Logo_Render(void * param);//Logo�������
void SameGame_Logo_Update(void * param);//Logo����ˢ��

#endif
