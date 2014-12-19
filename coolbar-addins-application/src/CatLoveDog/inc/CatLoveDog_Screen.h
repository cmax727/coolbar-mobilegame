/*******************************************************************
* 2010
* 
* 文件名称：CatLoveDog_Screen.h

此功能是设定游戏一些公用常量和公用方法
*******************************************************************/
#ifndef CATLOVEDOG_SCREEN_H
#define CATLOVEDOG_SCREEN_H

#include "coolbar_GameInc.h"
#include "DF_Util.h"
#include "DF_Windows.h"
#include "DF_PictureLibrary.h"
#include "DF_Record.h"
#include "CatLoveDog_Resource_Data.h"
#include "CatLoveDog_InGame.h"



#ifndef __WIN_32
#include "billing_ext.h"
#endif
#define FREE_REALEASE 

#define CatLoveDog_TITLE_STATE_SHOW_TITLE     0
#define CatLoveDog_TITLE_STATE_MENU           1
#define CatLoveDog_TITLE_STATE_HELP           2
#define CatLoveDog_TITLE_STATE_ABOUT          3
#define CatLoveDog_TITLE_STATE_SET			  4
#define CatLoveDog_TITLE_STATE_PAY			  5

#define NETAPP_APP_CatLoveDog    2041  

#define CatLoveDog_RECORD_ID_LIFE      0       
#define CatLoveDog_RECORD_ID_BOMB      1       
#define CatLoveDog_RECORD_ID_MUSI      2  



extern tScreen CatLoveDog_Screen_Title;      
extern tScreen CatLoveDog_Screen_Loading;   
extern tScreen CatLoveDog_Screen_InGame;
extern tScreen * CatLoveDog_Screen_Next;     
extern DF_PictureLibrary catLoveDogPicLib;   
extern Manager * manager_my;
extern MemoryBlock *memoryblock_my;         

extern gm_s8  gameMusic;
extern gm_s8  level;							//游戏难度


extern gm_s16 CatLoveDogTitleState;   
extern gm_s16 CatLoveDogGameMenuShow;  
extern gm_s16 catLoveDogLoadingStep;
extern gm_s16 catLoveDogLoadingStepTotal;
extern gm_s16 CatLoveDogInGameState;

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

extern void CatLoveDog_Loading_UpdateStep(void);
extern void CatLoveDog_Title_ChangeState(gm_s16 state);
#endif

