#ifndef MEMORYBOX_PLAY_H
#define MEMORYBOX_PLAY_H

#include "DF_Windows.h"
#include "MemoryBox_Screen.h"
#include "DF_PictureLibrary.h"
typedef struct MEMORYBOX_PLAY
{
	DF_PictureLibrary * picLib;
  	DF_Windows windows;
    gm_bool gameexit;//判断游戏是否结束    	//
    gm_s16 jishi;									//
    gm_s16 score;//玩家分数    
    gm_s16 rand;
    gm_s32 imgLog[2];
	gm_s32 imgLaba;
	gm_s32 imgBeijing;
	gm_s32 imgTupian;
	gm_s32 imgDipian;
	gm_s32 imgBei;
	gm_s32 imgGuangbiao;
	gm_s32 imgGameOver;
	gm_s32 imgWin;
	gm_s32 imgPojilu;
	gm_s32 imgQueingfanhui;
	gm_s32 imgJinxingxiayiguan;
    gm_s32 screenwidth;
    gm_s32 screenheight;
    gm_bool pojilu;								//
    gm_s16 zhuangtai; //--进入游戏后的状态 0没有块被翻开，1有一个块被翻开，2两个块被翻开，此时禁止选择，3全部的块都被翻开，过关，4时间到 GAMEOVER
    gm_s16 mendis;//--难度选择上手型图标y方向移动的距离
    gm_s16 guangbiaox;//游戏过程中光标（白框）的位置:x(0-3）,y:(0-4)
    gm_s16 guangbiaoy;
    gm_s16 clipx1 ;//记录下被翻开的第一个块的x,y
    gm_s16 clipy1;
    gm_s16 clipx2 ;//记录下被翻开的第二个块的x,y
    gm_s16 clipy2;
    gm_s16 picw;   //--每个块的宽高
    gm_s16 pich;	//
    gm_s16 x0;  //--最左上块的位置
    gm_s16 y0;//
    gm_s16 opennum;//已经找到的图片对数
    gm_s16 sourcetime;//--剩余时间，练习模式下为使用时间
    gm_s16 temptime;//累加时间，每加10次为1秒
    gm_s16 starttime;
    gm_s16 tempstarttime;//确保两个图片翻开后1秒钟后再翻回去
    gm_bool ingame;//--是否正在游戏，让时间运行
    gm_bool soundopen;//--游戏声音开关
    gm_bool gameoverl;
	gm_s32 time;

}MemoryBoxplay;
extern void initMemoryBoxplay(MemoryBoxplay * myself,Rect windows_Rect,DF_PictureLibrary * picLib,gm_s16 repaintMax);
void MemoryBox_Play_Windows_Render(void *param);
void MemoryBox_Play_Windows_Update(void * param);
#endif

