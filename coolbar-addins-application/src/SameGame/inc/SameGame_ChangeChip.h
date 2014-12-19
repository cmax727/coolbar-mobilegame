#ifndef SAMEGAME_HELP_H
#define SAMEGAME_HELP_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"
#include "coolbar_TextBox.h"

typedef struct SAMEGAME_CHANGE_CHIP
{
	DF_Windows windows;//��Ϸ�������洰��
	DF_PictureLibrary * picLib;//��Ϸ�����õ�ͼƬ��

	gm_s16 selectMenu;
}SameGameChangeChip;

void SameGame_ChangeChip_Init(SameGameChangeChip * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
void SameGame_ChangeChip_Render(void * param);//���������������
void SameGame_ChangeChip_Update(void * param);//�������水������

#endif

