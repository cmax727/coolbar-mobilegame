/*******************************************************************
* 2010
* 
* 文件名称：ONFF_Screen.h

此功能是设定游戏一些公用常量和公用方法
*******************************************************************/
#ifndef MEMORYBOX_SCREEN_H
#define MEMORYBOX_SCREEN_H

#include "coolbar_GameInc.h"
#include "DF_Util.h"
#include "DF_Windows.h"
#include "DF_PictureLibrary.h"
#include "DF_Record.h"
#include "MemoryBox_Resource_Data.h"
#include "MemoryBoxPlay.h"

#ifndef __WIN_32
#include "billing_ext.h"
#endif
#define FREE_REALEASE 

//标题界面状态
#define MEMORYBOX_TITLE_STATE_SHOW_TITLE     	   0
#define MEMORYBOX_TITLE_STATE_MENU           	   1
#define MEMORYBOX_TITLE_STATE_HELP          	   2
#define MEMORYBOX_TITLE_STATE_ABOUT          	   3
#define MEMORYBOX_TITLE_STATE_EXERSICE		       4
#define MEMORYBOX_TITLE_STATE_HIGSCORE             5
#define MEMORYBOX_TITLE_STATE_PAY                  6


#define NETAPP_APP_MEMORYBOX   2039  //游戏应用号

extern tScreen MemoryBox_Screen_Title;      //游戏中标题界面
extern tScreen MemoryBox_Screen_Loading;    //游戏中loading界面
extern tScreen MemoryBox_Screen_InGame;
extern tScreen * MemoryBox_Screen_Next;     //记录下screen，临时保存作用
extern DF_PictureLibrary allPicLib;   //图片库对象
extern Manager * manager_my;//游戏中工具指针，可调用底层相关函数
extern MemoryBlock *memoryblock_my;         //内存控制

extern gm_s8 gamestage;
extern gm_s8 level;
extern gm_s8 percent;
extern gm_s16 memoryBoxTitleState;   //主菜单状态
extern gm_s16 memoryBoxLoadingStep;
extern gm_s16 memoryBoxLoadingStepTotal;
extern gm_s32 memoryBoxHighTimeValue[10];
extern gm_s32 memoryBoxHighScoreYear[10];
extern gm_s32 memoryBoxHighScoreMonth[10];
extern gm_s32 memoryBoxHighScoreDate[10];



#ifdef GAME_240_320
    #define TOUCH_X_LEFT 10
    #define TOUCH_Y_LEFT 290
    #define TOUCH_X1_LEFT 43
    #define TOUCH_Y1_LEFT 320

    #define TOUCH_X_RIGHT 196
    #define TOUCH_Y_RIGHT 290
    #define TOUCH_X1_RIGHT 240
    #define TOUCH_Y1_RIGHT 320
#endif
#ifdef GAME_176_220
    #define TOUCH_X_LEFT 10
    #define TOUCH_Y_LEFT 199
    #define TOUCH_X1_LEFT 29
    #define TOUCH_Y1_LEFT 220

    #define TOUCH_X_RIGHT 130
    #define TOUCH_Y_RIGHT 199
    #define TOUCH_X1_RIGHT 176
    #define TOUCH_Y1_RIGHT 220
#endif

extern void MemoryBox_Loading_UpdateStep(void);
extern void MemoryBox_Title_ChangeState(gm_s16 state);//场景切换状态
extern void All_SMS_BuyOneMonth(BOOLEAN isSucess);
extern gm_bool MyCdRectPoint(gm_s16 x,gm_s16 y,gm_s16 x1,gm_s16 y1,gm_s16 px,gm_s16 py);
#endif

