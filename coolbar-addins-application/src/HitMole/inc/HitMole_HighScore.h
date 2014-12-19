#ifndef HITMOLE_HIGHSCORE_H
#define HITMOLE_HIGHSCORE_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"

typedef struct HITMOLE_HIGHSCORE
{
	DF_Windows windows;//��Ϸ�����а񴰿�
	DF_PictureLibrary * picLib;//��Ϸ�����а�ͼƬ��ָ��
}HitMole_HighScore;

extern void initHitMoleHighScore(HitMole_HighScore * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
void HitMole_HighScore_Windows_Render(void * param);//��Ϸ�����а����
void HitMole_HighScore_windows_Update(void * param);//��Ϸ�����а�ˢ��
#endif

