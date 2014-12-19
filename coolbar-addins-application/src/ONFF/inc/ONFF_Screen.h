/*******************************************************************
* 2010
* 
* 文件名称：ONFF_Screen.h

此功能是设定游戏一些公用常量和公用方法
*******************************************************************/
# ifndef ONFF_SCREEN_H
# define ONFF_SCREEN_H

#include "coolbar_GameInc.h"
#include "DF_Util.h"
#include "DF_Windows.h"
#include "DF_PictureLibrary.h"
#include "DF_Record.h"
#include "ONFF_Resource_Data.h"
#include "ONFF_Map.h"



#ifndef __WIN_32
#include "billing_ext.h"
#endif
#define FREE_REALEASE 

#define ONFF_TITLE_STATE_SHOW_TITLE     0
#define ONFF_TITLE_STATE_MENU           1
#define ONFF_TITLE_STATE_HELP           2
#define ONFF_TITLE_STATE_ABOUT          3
#define ONFF_TITLE_STATE_SET			4
#define ONFF_TITLE_STATE_PAY			5

#define NETAPP_APP_ONFF    130  

#define ONFF_RECORD_ID_LIFE      0       
#define ONFF_RECORD_ID_BOMB      1       
#define ONFF_RECORD_ID_MUSI      2  



extern tScreen ONFF_Screen_Title;      
extern tScreen ONFF_Screen_Loading;   
extern tScreen ONFF_Screen_InGame;
extern tScreen * ONFF_Screen_Next;     
extern DF_PictureLibrary oNFFPicLib;   
extern Manager * manager_my;
extern MemoryBlock *memoryblock_my;         

extern gm_s8  gamePlayerlife;
extern gm_s8  gamePlayerbomb;
extern gm_s8  gameMusic;

extern gm_s16 oNFFTitleState;   
extern gm_s16 oNFFGameMenuShow;  
extern gm_s16 oNFFLoadingStep;
extern gm_s16 oNFFLoadingStepTotal;
extern gm_s16 oNFFInGameState;

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

extern void ONFF_Loading_UpdateStep(void);
extern void ONFF_Title_ChangeState(gm_s16 state);
extern gm_bool CdRectPoint3(gm_s16 x,gm_s16 y,gm_s16 x1,gm_s16 y1,gm_s16 px,gm_s16 py);
#endif

