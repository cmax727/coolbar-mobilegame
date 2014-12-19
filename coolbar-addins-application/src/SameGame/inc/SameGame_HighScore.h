#ifndef SAMEGAME_HIGHSCORE_H
#define SAMEGAME_HIGHSCORE_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"

typedef struct SAMEGAME_HIGHSCORE
{
	DF_Windows windows;//��Ϸ�����а񴰿�
	DF_PictureLibrary * picLib;//��Ϸ�����а�ͼƬ��ָ��
}SameGameHighScore;

void SameGame_HighScore_Init(SameGameHighScore * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
void SameGame_HighScore_Render(void * param);//��Ϸ�����а����
void SameGame_HighScore_Update(void * param);//��Ϸ�����а�ˢ��

#endif

