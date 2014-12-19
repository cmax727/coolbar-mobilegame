/*******************************************************************
* 2009 Wingtech, Incoporated. All Rights Reserved.
* 
* �ļ����ƣ�RussBlock_HighScore.h

�˹�������ʾ��Ϸ�����н���
*******************************************************************/

#ifndef RUSSBLOCK_HIGHSCORE_H
#define RUSSBLOCK_HIGHSCORE_H
#include "DF_PictureLibrary.h"
#include "DF_Windows.h"

typedef struct RUSSBLOCK_HIGHSCORE
{
	gm_s16 imgHelp[4];//��Ϸ�����а�������ͼƬ��
	gm_s16	imgMenuBar;//
	gm_s8 model;
	DF_PictureLibrary * picLib;//��Ϸ�����а�ͼƬ��ָ��
	DF_Windows windows;//��Ϸ�����а񴰿�
}RussBlock_HighScore;

extern void initRussBlockHighScore(RussBlock_HighScore * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
void RussBlock_Score_Windows_Render(void * param);//��Ϸ�����а����
void RussBlock_Score_windows_Update(void * param);//��Ϸ�����а�ˢ��

#endif