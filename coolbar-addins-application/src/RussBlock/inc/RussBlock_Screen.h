/*******************************************************************
* 2009 Wingtech, Incoporated. All Rights Reserved.
* 
* �ļ����ƣ�RussBlock_Screen.h

�˹������趨��ϷһЩ���ó����͹��÷���
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

//�������״̬
#define RUSSBLOCK_TITLE_STATE_SHOW_PRE 8
#define RUSSBLOCK_TITLE_STATE_SHOW_TITLE     0
#define RUSSBLOCK_TITLE_STATE_MENU           1
#define RUSSBLOCK_TITLE_STATE_SELECTLEVEL    3
#define RUSSBLOCK_TITLE_STATE_HELP           4
#define RUSSBLOCK_TITLE_STATE_ABOUT          5
#define RUSSBLOCK_TITLE_STATE_HIGHSCORE      7

#define NETAPP_APP_RUSSBLOCK    1016  //��ϷӦ�ú�

#define MAX_BOX              19         /*�ܹ���19�ָ���̬�ķ���*/
#define BEGIN_BOXS_X         5          /*������һ������ʱӦ�ó��ֵ���ʼλ�� ����ָ�����ڵ�6�����*/

#ifdef GAME_240_320
    #define BSIZE                12         /*����ı߳���12������*/
    #define SYS_X                10         /*��ʾ�����������Ͻ�x����*/
    #define SYS_Y                38         /*��ʾ�����������Ͻ�y����*/
    #define HORIZONTAL_BOXS      12         /*ˮƽ�ķ����Է���Ϊ��λ�ĳ���*/
    #define VERTICAL_BOXS        21         /*��ֱ�ķ����Է���Ϊ��λ�ĳ���,Ҳ��˵����21������*/
    #define BLOCKAREAX           9           /*��������ϵ�X,�������windows */
    #define BLOCKAREAY           37         /*��������ϵ�Y���������windows*/
//  #define LEFTWIN_X            SYS_X+HORIZONTAL_BOXS*BSIZE+50     /*���״̬����x����*/
    #define MENUBARWIDTH         38                  /*Menubar ��λ��*/
    #define MENUBARHEIGHT        36                 /*Menubar ��λ��*/
#endif
#ifdef GAME_176_220
#define BSIZE                9          /*����ı߳���12������*/
#define SYS_X                7          /*��ʾ�����������Ͻ�x����*/
#define SYS_Y                26         /*��ʾ�����������Ͻ�y����*/
#define HORIZONTAL_BOXS      12         /*ˮƽ�ķ����Է���Ϊ��λ�ĳ���*/
#define VERTICAL_BOXS        19         /*��ֱ�ķ����Է���Ϊ��λ�ĳ���,Ҳ��˵����21������*/
#define BLOCKAREAX           6           /*��������ϵ�X,�������windows */
#define BLOCKAREAY           25         /*��������ϵ�Y���������windows*/
#define MENUBARWIDTH         38                  /*Menubar ��λ��*/
#define MENUBARHEIGHT        36                 /*Menubar ��λ��*/
#endif
#define RUSSBLOCK_INGAME_MAINSTATE_PLAYING      0       /*����Ϸ*/
#define RUSSBLOCK_INGAME_MAINSTATE_GAMEMENU     1       /*�����˵�*/
#define RUSSBLOCK_INGAME_MAINSTATE_MOVING       2       /*������Ů����״̬*/
#define RUSSBLOCK_INGAME_MAINSTATE_SCORE        3       /*������ʾ����*/
#define GAMETYPE_NOMAL 0           /*��Ϸ��ͨģʽ*/
#define GAMETYPE_TIME  1           /*��Ϸʱ��ģʽ*/

//����ʱ��¼������
#define RUSSBLOCK_RECORD_ID_COMMONMODEL             0
#define RUSSBLOCK_RECORD_ID_TIMEMODEL               1
#define RUSSBLOCK_RECORD_ID_PROP                    2
#define RUSSBLOCK_RECORD_ID_GRID_NOMAL              3
#define RUSSBLOCK_RECORD_ID_GRID_TIME               4
#define RUSSBLOCK_RECORD_ID_GAMEDATA_NOMAL          5
#define RUSSBLOCK_RECORD_ID_GAMEDATA_TIME           6   
#define RUSSBLOCK_RECORD_ID_GAMETIME                7   //��Ϸʱ��


#define GAME_PROP_BOMB          0  /*ը������*/
#define GAME_PROP_SLOWSPEED     1  /*���ٵ���*/
#define GAME_PROP_EXTANDTIME    2  /*�ӳ�ʱ�����*/

#define SHOWGIRL_LEVEL_ONE      2  /*��Ů���µĵȼ�����*/
#define SHOWGIRL_LEVEL_TWO      4
#define SHOWGIRL_LEVEL_THREE    7
#define SHOWGIRL_LEVEL_FOUR     10

#define BLOCK_SPEED        17   /*�������������ٶȣ�BLOCK_SPEED ����ˢ����*/
#define BLOCK_SPEED_START  4    /*����ʼ�ٶ� ,һ��Ϊ4*/
#define BLOCK_TIME         60   /*ʱ��ģʽ�µ���Ϸʱ��*/
#define BLOCK_ERASE        10  /*����������ȥ����*/

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

extern tScreen RussBlock_Screen_InGame;     //��Ϸ�д����
extern tScreen RussBlock_Screen_Title;      //��Ϸ�б������
extern tScreen RussBlock_Screen_Loading;    //��Ϸ��loading����
extern tScreen * RussBlock_Screen_Next;     //��¼��screen����ʱ��������
extern DF_PictureLibrary russBlockPicLib;   //ͼƬ�����
extern Manager * manager_my;                //��Ϸ�й���ָ�룬�ɵ��õײ���غ���
extern MemoryBlock *memoryblock_my;         //�ڴ����
extern DF_Record russBlockRecord;           //��¼�����ɱ�������

extern gm_s8 russBlockSpeed;   //���������ٶ� 
extern gm_s32 russBlockHitNum; /*���������*/
extern gm_s8  russBlockGameType; /*��Ϸģʽ*/
extern gm_s8  russBlockGameTime; /*��Ϸʱ��*/

extern gm_s32 russBlockProp[3]; /*��Ϸ���߱�*/
extern gm_s16 russBlockTitleState;   //���˵�״̬
extern gm_s16 russBlockGameMenuShow;   //��Ϸ�в˵���ʾ
extern gm_s16 russBlockLoadingStep;
extern gm_s16 russBlockLoadingStepTotal;
extern gm_s16 russBlockInGameState;
extern gm_u8 flag_GirlShow_Notify;
extern gm_u8 flag_GirlShow;
extern gm_u8 flag_GameOver;
extern gm_s8 timerCnt;
extern gm_s32 russBlockHighScoreValue_CommonModel[12];
extern gm_s32 russBlockHighScoreValue_TimeModel[12];
extern gm_s32 russBlockGameData [2][4];  //�ȼ� ���� ���ĳ��� �����ٶ�
extern gm_u8  russBlockGameGrid [2][VERTICAL_BOXS][HORIZONTAL_BOXS];

extern void RussBlock_Loading_UpdateStep();
extern void RussBlock_Title_ChangeState(gm_s16 state);//�����л�״̬
/*����Ϸ�˵�������*/
extern void RussBlock_MenuBar_Paint(DF_PictureLibrary * param,gm_s16 id,gm_s16 width,gm_s16 height,gm_s16 y);
extern void InGame_SetBuyTextBox(gm_s16 state);
extern void RussBlock_SMS_BuyOneMonth(BOOLEAN isSucess);//���»ص�����
extern void updateHighScore();
extern void updateGameData();//������Ϸ���ݣ�д���¼
extern void copyGrid();
#endif