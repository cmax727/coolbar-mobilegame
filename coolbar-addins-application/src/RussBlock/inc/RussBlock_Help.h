/*******************************************************************
* 2009 Wingtech, Incoporated. All Rights Reserved.
* 
* 文件名称：RussBlock_Help.h

此功能是显示游戏中帮助界面绘制,它主要采用底层封装TextBox函数
注:TextBox函数可设显示文字区域大小，TextBox.curPage代表当前显示页
*******************************************************************/

#ifndef RUSSBLOCK_HELP_H
#define RUSSBLOCK_HELP_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"
#include "coolbar_TextBox.h"

typedef struct RUSSBLOCK_HELP
{
	DF_Windows windows;//游戏帮助界面窗口
	DF_PictureLibrary * picLib;//游戏帮助得到图片库
	TextBox textBox;   //文本编辑框
//	gm_s16 imgHelp[4]; //游戏帮助中加载图片名
//	gm_s16	imgMenuBar; //游戏帮助中加载图片名
}RussBlock_Help;

extern void initRussBlockHelp(RussBlock_Help * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
 void RussBlock_Help_Windows_Render(void * param);//帮助界面绘制区域
 void RussBlock_Help_windows_Update(void * param);//帮助界面按键控制
 void initHelp(RussBlock_Help * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
 void Help_Windows_Render(void * param);
#endif