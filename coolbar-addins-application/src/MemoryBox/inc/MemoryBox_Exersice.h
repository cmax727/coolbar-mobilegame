#ifndef MEMORYBOX_EXERSICE_H
#define MEMORYBOX_EXERSICE_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"

typedef struct MEMORYBOX_EXERSICE
{
 DF_Windows windows;//游戏帮助界面窗口
 DF_PictureLibrary * picLib;//游戏帮助得到图片库	
 gm_s16 imgIcon;
 gm_s16 imgback;
 gm_s8 selectnum;
}MemoryBoxExersice;

extern void initMemoryBoxExersice(MemoryBoxExersice * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib);
 void MemoryBox_Exersice_Windows_Render(void * param);//帮助界面绘制区域
 void MemoryBox_Exersice_Windows_Update(void * param);//帮助界面按键控制
#endif