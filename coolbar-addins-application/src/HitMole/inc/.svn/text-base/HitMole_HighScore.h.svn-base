#ifndef HITMOLE_HIGHSCORE_H
#define HITMOLE_HIGHSCORE_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"

typedef struct HITMOLE_HIGHSCORE
{
	DF_Windows windows;//游戏中排行榜窗口
	DF_PictureLibrary * picLib;//游戏中排行榜图片库指针
}HitMole_HighScore;

extern void initHitMoleHighScore(HitMole_HighScore * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
void HitMole_HighScore_Windows_Render(void * param);//游戏中排行榜绘制
void HitMole_HighScore_windows_Update(void * param);//游戏中排行榜刷新
#endif

