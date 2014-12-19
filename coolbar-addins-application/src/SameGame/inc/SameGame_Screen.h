/*******************************************************************
* 2010
* 
* 文件名称：ONFF_Screen.h

此功能是设定游戏一些公用常量和公用方法
*******************************************************************/
#ifndef SAMEGAME_SCREEN_H
#define SAMEGAME_SCREEN_H

#include "coolbar_GameInc.h"
#include "DF_Util.h"
#include "DF_Windows.h"
#include "DF_PictureLibrary.h"
#include "DF_Record.h"

#include "SameGame_Resource_Data.h"
#include "SameGame_Playing.h"
#include "SameGame_Logo.h"
#include "SameGame_PlayMenu.h"
#include "SameGame_ChangeChip.h"
#include "SameGame_TitleMenu.h"
#include "SameGame_CompleteMenu.h"
#include "SameGame_HighScore.h"

#ifndef __WIN_32
#include "billing_ext.h"
#endif
#define FREE_REALEASE 

//标题界面状态
#define SAMEGAME_STATE_LOGO     				0
#define SAMEGAME_STATE_TITLEMENU           		1
#define SAMEGAME_STATE_CHANGECHIP          		2
#define SAMEGAME_STATE_COMPLETEMENU          	3
#define SAMEGAME_STATE_PLAYMENU					4
#define SAMEGAME_STATE_HIGSCORE					5

#define NETAPP_APP_SAMEGAME   2039			//游戏应用号

tScreen sameGame_Screen_Title;				//游戏中标题界面
tScreen sameGame_Screen_Loading;			//游戏中loading界面
tScreen sameGame_Screen_InGame;
tScreen * sameGame_Screen_Next;				//记录下screen，临时保存作用

DF_PictureLibrary allPicLib;				//图片库对象
DF_PictureLibrary SameGameLoadingPicLib;	//本Screen自有图片库
Manager * manager_my;
MemoryBlock *memoryblock_my;
DF_Record sameGameRecord;
static DF_DataPackage dataPackage;

gm_s16 shape;
gm_s16 level;
gm_s16 newGame;
gm_s16 completeState;
gm_s16 sameGameTitleState;					//主菜单状态
gm_s16 sameGameLoadingStep;
gm_s16 sameGameLoadingStepTotal;
gm_s32 sameGameHighTimeValue[3];
gm_s32 sameGamemageLoading[2];
gm_s32 sameGameLoadingRepaintAll;
gm_s32 sameGameLoadingRepaintStep;

SameGameLogo sameGameLogo;
SameGameTitleMenu sameGameTitleMenu;
SameGameChangeChip sameGameChangeChip;
SameGamePlayMenu sameGamePlayMenu;
SameGameCompleteMenu sameGameCompleteMenu;
SameGameHighScore sameGameHighScore;
SameGamePlaying sameGamePlaying;

void SameGame_Title_Init(void);
void SameGame_Title_Destroy(void);
void SameGame_Title_Logic(void);
void SameGame_Title_Render(tGraphics * g);
void SameGame_Title_Pause(void);
void SameGame_Title_Resume(void);
void SameGame_Title_LoadResource(void);
void SameGame_Title_ChangeState(gm_s16 state);

void SameGame_Loading_Init(void);
void SameGame_Loading_Destory(void);
void SameGame_Loading_Logic(void);
void SameGame_Loading_Render(tGraphics *g);
void SameGame_Loading_Pause(void);
void SameGame_Loading_Resume(void);
void SameGame_Loading_LoadResource(void);

void SameGame_InGame_Init(void);
void SameGame_InGame_Destory(void);
void SameGame_InGame_Logic(void);
void SameGame_InGame_Render(tGraphics *g);
void SameGame_InGame_Pause(void);
void SameGame_InGame_Resume(void);
void SameGame_InGame_LoadResource(void);

void SameGame_Loading_UpdateStep(void);
void SameGame_Title_ChangeState(gm_s16 state);//场景切换状态

#endif
