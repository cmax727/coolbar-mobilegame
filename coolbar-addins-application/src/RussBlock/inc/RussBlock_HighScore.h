/*******************************************************************
* 2009 Wingtech, Incoporated. All Rights Reserved.
* 
* 文件名称：RussBlock_HighScore.h

此功能是显示游戏中排行界面
*******************************************************************/

#ifndef RUSSBLOCK_HIGHSCORE_H
#define RUSSBLOCK_HIGHSCORE_H
#include "DF_PictureLibrary.h"
#include "DF_Windows.h"

typedef struct RUSSBLOCK_HIGHSCORE
{
	gm_s16 imgHelp[4];//游戏中排行榜界面加载图片名
	gm_s16	imgMenuBar;//
	gm_s8 model;
	DF_PictureLibrary * picLib;//游戏中排行榜图片库指针
	DF_Windows windows;//游戏中排行榜窗口
}RussBlock_HighScore;

extern void initRussBlockHighScore(RussBlock_HighScore * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
void RussBlock_Score_Windows_Render(void * param);//游戏中排行榜绘制
void RussBlock_Score_windows_Update(void * param);//游戏中排行榜刷新

#endif