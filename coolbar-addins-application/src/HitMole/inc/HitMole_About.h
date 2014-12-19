#ifndef HITMOLE_ABOUT_H
#define HITMOLE_ABOUT_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"
#include "coolbar_TextBox.h"

typedef struct HITMOLE_ABOUT
{
	DF_Windows windows;//游戏帮助界面窗口
	DF_PictureLibrary * picLib;//游戏帮助得到图片库
	TextBox textBox;   //文本编辑框
	gm_s16 border;
}HitMole_About;

extern void initHitMoleAbout(HitMole_About * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
 void HitMole_About_Windows_Render(void * param);//帮助界面绘制区域
 void HitMole_About_windows_Update(void * param);//帮助界面按键控制
#endif

