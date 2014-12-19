#ifndef SAMEGAME_EXERSICE_H
#define SAMEGAME_EXERSICE_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"

typedef struct SAMEGAME_CMPLETE_MENU
{
	DF_Windows windows;//��Ϸ�������洰��
	DF_PictureLibrary * picLib;//��Ϸ�����õ�ͼƬ��	

	gm_s16 selectnum;
}SameGameCompleteMenu;

void SameGame_CompleteMenu_Init(SameGameCompleteMenu * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
void SameGame_CompleteMenu_Render(void * param);//���������������
void SameGame_CompleteMenu_Update(void * param);//�������水������

#endif