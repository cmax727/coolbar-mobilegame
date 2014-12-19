#ifndef MEMORYBOX_HELP_H
#define MEMORYBOX_HELP_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"
#include "coolbar_TextBox.h"

typedef struct MEMORYBOX_HELP
{
	DF_Windows windows;//游戏帮助界面窗口
	DF_PictureLibrary * picLib;//游戏帮助得到图片库
	TextBox textBox;   //文本编辑框
	gm_s16 imgback;
}MemoryBox_Help;

extern void initMemoryBoxHelp(MemoryBox_Help * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
 void MemoryBox_Help_Windows_Render(void * param);//帮助界面绘制区域
 void MemoryBox_Help_windows_Update(void * param);//帮助界面按键控制
#endif

