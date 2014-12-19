/*******************************************************************
* 2009 Wingtech, Incoporated. All Rights Reserved.
* 
* 文件名称：RussBlock_Screen.h

此功能是设定游戏一些公用常量和公用方法
*******************************************************************/
# ifndef RUSSBLOCK_SCREEN_H
# define RUSSBLOCK_SCREEN_H

#include "coolbar_GameInc.h"
#include "DF_Util.h"
#include "DF_Map.h"
#include "DF_Windows.h"
#include "DF_PictureLibrary.h"
#include "DF_Record.h"
#include "RussBlock_UI.h"
#include "RussBlock_Map.h"
#include "RussBlock_Resource.h"

#ifndef __WIN_32
#include "billing_ext.h"
#endif
#define FREE_REALEASE 

//标题界面状态
#define RUSSBLOCK_TITLE_STATE_SHOW_PRE 8
#define RUSSBLOCK_TITLE_STATE_SHOW_TITLE     0
#define RUSSBLOCK_TITLE_STATE_MENU           1
#define RUSSBLOCK_TITLE_STATE_SELECTLEVEL    3
#define RUSSBLOCK_TITLE_STATE_HELP           4
#define RUSSBLOCK_TITLE_STATE_ABOUT          5
#define RUSSBLOCK_TITLE_STATE_HIGHSCORE      7

#define NETAPP_APP_RUSSBLOCK    1016  //游戏应用号

#define MAX_BOX              19         /*总共有19种各形态的方块*/
#define BEGIN_BOXS_X         5          /*产生第一个方块时应该出现的起始位置 这里指定是在第6格出现*/

#ifdef GAME_240_320
    #define BSIZE                12         /*方块的边长是12个象素*/
    #define SYS_X                10         /*显示方块界面的左上角x座标*/
    #define SYS_Y                38         /*显示方块界面的左上角y座标*/
    #define HORIZONTAL_BOXS      12         /*水平的方向以方块为单位的长度*/
    #define VERTICAL_BOXS        21         /*垂直的方向以方块为单位的长度,也就说长是21个方块*/
    #define BLOCKAREAX           9           /*网格的左上点X,相对于子windows */
    #define BLOCKAREAY           37         /*网格的左上点Y，相对于子windows*/
//  #define LEFTWIN_X            SYS_X+HORIZONTAL_BOXS*BSIZE+50     /*左边状态栏的x座标*/
    #define MENUBARWIDTH         38                  /*Menubar 单位宽*/
    #define MENUBARHEIGHT        36                 /*Menubar 单位高*/
#endif
#ifdef GAME_176_220
#define BSIZE                9          /*方块的边长是12个象素*/
#define SYS_X                7          /*显示方块界面的左上角x座标*/
#define SYS_Y                26         /*显示方块界面的左上角y座标*/
#define HORIZONTAL_BOXS      12         /*水平的方向以方块为单位的长度*/
#define VERTICAL_BOXS        19         /*垂直的方向以方块为单位的长度,也就说长是21个方块*/
#define BLOCKAREAX           6           /*网格的左上点X,相对于子windows */
#define BLOCKAREAY           25         /*网格的左上点Y，相对于子windows*/
#define MENUBARWIDTH         38                  /*Menubar 单位宽*/
#define MENUBARHEIGHT        36                 /*Menubar 单位高*/
#endif
#define RUSSBLOCK_INGAME_MAINSTATE_PLAYING      0       /*玩游戏*/
#define RUSSBLOCK_INGAME_MAINSTATE_GAMEMENU     1       /*弹出菜单*/
#define RUSSBLOCK_INGAME_MAINSTATE_MOVING       2       /*播放美女脱衣状态*/
#define RUSSBLOCK_INGAME_MAINSTATE_SCORE        3       /*积分显示界面*/
#define GAMETYPE_NOMAL 0           /*游戏普通模式*/
#define GAMETYPE_TIME  1           /*游戏时间模式*/

//保存时记录索引号
#define RUSSBLOCK_RECORD_ID_COMMONMODEL             0
#define RUSSBLOCK_RECORD_ID_TIMEMODEL               1
#define RUSSBLOCK_RECORD_ID_PROP                    2
#define RUSSBLOCK_RECORD_ID_GRID_NOMAL              3
#define RUSSBLOCK_RECORD_ID_GRID_TIME               4
#define RUSSBLOCK_RECORD_ID_GAMEDATA_NOMAL          5
#define RUSSBLOCK_RECORD_ID_GAMEDATA_TIME           6   
#define RUSSBLOCK_RECORD_ID_GAMETIME                7   //游戏时间


#define GAME_PROP_BOMB          0  /*炸弹道具*/
#define GAME_PROP_SLOWSPEED     1  /*减速道具*/
#define GAME_PROP_EXTANDTIME    2  /*延长时间道具*/

#define SHOWGIRL_LEVEL_ONE      2  /*美女脱衣的等级条件*/
#define SHOWGIRL_LEVEL_TWO      4
#define SHOWGIRL_LEVEL_THREE    7
#define SHOWGIRL_LEVEL_FOUR     10

#define BLOCK_SPEED        17   /*方块最慢下落速度，BLOCK_SPEED 倍于刷屏率*/
#define BLOCK_SPEED_START  4    /*■初始速度 ,一般为4*/
#define BLOCK_TIME         60   /*时间模式下的游戏时间*/
#define BLOCK_ERASE        10  /*可升级的消去行数*/

#ifdef GAME_240_320
    #define TOUCH_X_LEFT 0
    #define TOUCH_Y_LEFT 290
    #define TOUCH_X1_LEFT 43
    #define TOUCH_Y1_LEFT 320

    #define TOUCH_X_RIGHT 196
    #define TOUCH_Y_RIGHT 290
    #define TOUCH_X1_RIGHT 240
    #define TOUCH_Y1_RIGHT 320
#endif
#ifdef GAME_176_220
    #define TOUCH_X_LEFT 0
    #define TOUCH_Y_LEFT 199
    #define TOUCH_X1_LEFT 29
    #define TOUCH_Y1_LEFT 220

    #define TOUCH_X_RIGHT 147
    #define TOUCH_Y_RIGHT 199
    #define TOUCH_X1_RIGHT 176
    #define TOUCH_Y1_RIGHT 220
#endif

extern tScreen RussBlock_Screen_InGame;     //游戏中大界面
extern tScreen RussBlock_Screen_Title;      //游戏中标题界面
extern tScreen RussBlock_Screen_Loading;    //游戏中loading界面
extern tScreen * RussBlock_Screen_Next;     //记录下screen，临时保存作用
extern DF_PictureLibrary russBlockPicLib;   //图片库对象
extern Manager * manager_my;                //游戏中工具指针，可调用底层相关函数
extern MemoryBlock *memoryblock_my;         //内存控制
extern DF_Record russBlockRecord;           //记录集，可保存数据

extern gm_s8 russBlockSpeed;   //方块下落速度 
extern gm_s32 russBlockHitNum; /*玩家连击数*/
extern gm_s8  russBlockGameType; /*游戏模式*/
extern gm_s8  russBlockGameTime; /*游戏时间*/

extern gm_s32 russBlockProp[3]; /*游戏道具表*/
extern gm_s16 russBlockTitleState;   //主菜单状态
extern gm_s16 russBlockGameMenuShow;   //游戏中菜单显示
extern gm_s16 russBlockLoadingStep;
extern gm_s16 russBlockLoadingStepTotal;
extern gm_s16 russBlockInGameState;
extern gm_u8 flag_GirlShow_Notify;
extern gm_u8 flag_GirlShow;
extern gm_u8 flag_GameOver;
extern gm_s8 timerCnt;
extern gm_s32 russBlockHighScoreValue_CommonModel[12];
extern gm_s32 russBlockHighScoreValue_TimeModel[12];
extern gm_s32 russBlockGameData [2][4];  //等级 分数 消的成数 下落速度
extern gm_u8  russBlockGameGrid [2][VERTICAL_BOXS][HORIZONTAL_BOXS];

extern void RussBlock_Loading_UpdateStep();
extern void RussBlock_Title_ChangeState(gm_s16 state);//场景切换状态
/*画游戏菜单背景框*/
extern void RussBlock_MenuBar_Paint(DF_PictureLibrary * param,gm_s16 id,gm_s16 width,gm_s16 height,gm_s16 y);
extern void InGame_SetBuyTextBox(gm_s16 state);
extern void RussBlock_SMS_BuyOneMonth(BOOLEAN isSucess);//包月回调函数
extern void updateHighScore();
extern void updateGameData();//更新游戏数据，写入记录
extern void copyGrid();
#endif