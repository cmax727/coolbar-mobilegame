#ifndef MEMORYBOX_HIGHSCORE_H
#define MEMORYBOX_HIGHSCORE_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"

typedef struct MEMORYBOX_HIGHSCORE
{
	DF_Windows windows;//��Ϸ�����а񴰿�
	DF_PictureLibrary * picLib;//��Ϸ�����а�ͼƬ��ָ��
}MemoryBox_HighScore;

extern void initMemoryBoxHighScore(MemoryBox_HighScore * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
void MemoryBox_HighScore_Windows_Render(void * param);//��Ϸ�����а����
void MemoryBox_HighScore_windows_Update(void * param);//��Ϸ�����а�ˢ��
#endif

