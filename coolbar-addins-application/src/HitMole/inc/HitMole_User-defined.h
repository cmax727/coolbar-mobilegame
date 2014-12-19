#ifndef HITMOLE_USERDEFINED_H
#define HITMOLE_USERDEFINED_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"

typedef struct USER_DEFINE
{
 DF_Windows windows;//游戏帮助界面窗口
 DF_PictureLibrary * picLib;//游戏帮助得到图片库	
 gm_s16 imgIcon;
 gm_s8 selectnum;
 gm_s16 border;
}UserDefine;

extern void initUserDefine(UserDefine * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
 void HitMole_UserDefine_Windows_Render(void * param);//帮助界面绘制区域
 void HitMole_UserDefine_windows_Update(void * param);//帮助界面按键控制
#endif