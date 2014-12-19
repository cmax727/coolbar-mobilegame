#ifndef SAMEGAME_HIGHSCORE_H
#define SAMEGAME_HIGHSCORE_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"

typedef struct SAMEGAME_HIGHSCORE
{
	DF_Windows windows;//游戏中排行榜窗口
	DF_PictureLibrary * picLib;//游戏中排行榜图片库指针
}SameGameHighScore;

void SameGame_HighScore_Init(SameGameHighScore * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
void SameGame_HighScore_Render(void * param);//游戏中排行榜绘制
void SameGame_HighScore_Update(void * param);//游戏中排行榜刷新

#endif

