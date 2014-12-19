/*******************************************************************
* 2010
* 
* 文件名称：ONFF_Screen.h

此功能是设定游戏一些公用常量和公用方法
*******************************************************************/
#ifndef MONSTER_SCREEN_H
#define MONSTER_SCREEN_H

#include "coolbar_GameInc.h"
#include "DF_Util.h"
#include "DF_Windows.h"
#include "DF_PictureLibrary.h"
#include "DF_Record.h"

#include "EM_Resource_Data.h"

#ifndef __WIN_32
#include "billing_ext.h"
#endif
#define FREE_REALEASE 

//Game status
#define MONSTER_STATE_LOGO     				0
#define MONSTER_STATE_TITLEMENU           		1
#define MONSTER_STATE_CHANGECHIP          		2
#define MONSTER_STATE_COMPLETEMENU          	3
#define MONSTER_STATE_PLAYMENU					4
#define MONSTER_STATE_HIGSCORE					5

#define NETAPP_APP_MONSTER   2039			//游戏应用号

tScreen em_Screen_Title;				//游戏中标题界面
tScreen em_Screen_Loading;			//游戏中loading界面
tScreen em_Screen_InGame;
tScreen * em_Screen_Next;				//记录下screen，临时保存作用

DF_PictureLibrary allPicLib;				//图片库对象
DF_PictureLibrary SameGameLoadingPicLib;	//本Screen自有图片库
Manager * manager_my;
MemoryBlock *memoryblock_my;
DF_Record emRecord;
static DF_DataPackage dataPackage;

// gm_s16 shape;
// gm_s16 level;
// gm_s16 newGame;
// gm_s16 completeState;
// gm_s16 emTitleState;					//主菜单状态
// gm_s16 emLoadingStep;
// gm_s16 emLoadingStepTotal;
// gm_s32 emHighTimeValue[3];
// gm_s32 emmageLoading[2];
// gm_s32 emLoadingRepaintAll;
// gm_s32 emLoadingRepaintStep;

void em_InGame_Init(void);
void em_InGame_Destory(void);
void em_InGame_Logic(void);
void em_InGame_Render(tGraphics *g);
void em_InGame_Pause(void);
void em_InGame_Resume(void);
void em_InGame_LoadResource(void);

#endif
