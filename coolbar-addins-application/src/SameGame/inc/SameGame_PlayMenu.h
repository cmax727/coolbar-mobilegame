#ifndef SAMEGAME_ABOUT_H
#define SAMEGAME_ABOUT_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"
#include "coolbar_TextBox.h"

typedef struct SAMEGAME_PLAY_MENU
{
	DF_Windows windows;//��Ϸ�������洰��
	DF_PictureLibrary * picLib;//��Ϸ�����õ�ͼƬ��

	gm_s16 selectMenu;
}SameGamePlayMenu;

void SameGame_PlayMenu_Init(SameGamePlayMenu * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
void SameGame_PlayMenu_Render(void * param);//���������������
void SameGame_PlayMenu_Update(void * param);//�������水������

#endif

