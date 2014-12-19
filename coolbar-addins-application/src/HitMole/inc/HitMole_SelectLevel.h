#ifndef HITMOLE_SELECTLEVEL_H
#define HITMOLE_SELECTLEVEL_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"

typedef struct SELECTLEVEL
{
 DF_Windows windows;//游戏帮助界面窗口
 DF_PictureLibrary * picLib;//游戏帮助得到图片库	
 gm_s16 imgIcon;
 gm_s8 selectnum;
 gm_s16 border;
}SelectLevel;

extern void initSelectLevel(SelectLevel * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
 void HitMole_SelectLevel_Windows_Render(void * param);//帮助界面绘制区域
 void HitMole_SelectLevel_windows_Update(void * param);//帮助界面按键控制
#endif

