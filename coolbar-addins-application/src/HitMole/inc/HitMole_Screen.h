/*******************************************************************
* 2010
* 
* �ļ����ƣ�ONFF_Screen.h

�˹������趨��ϷһЩ���ó����͹��÷���
*******************************************************************/
#ifndef HITMOLE_SCREEN_H
#define HITMOLE_SCREEN_H

#include "coolbar_GameInc.h"
#include "DF_Util.h"
#include "DF_Windows.h"
#include "DF_PictureLibrary.h"
#include "DF_Record.h"
#include "HitMole_Resource_Data.h"
#include "HitMolePlay.h"

#ifndef __WIN_32
#include "billing_ext.h"
#endif
#define FREE_REALEASE 

//�������״̬
#define HITMOLE_TITLE_STATE_SHOW_TITLE     	   0
#define HITMOLE_TITLE_STATE_MENU           	   1
#define HITMOLE_TITLE_STATE_HELP               2
#define HITMOLE_TITLE_STATE_ABOUT          	   3
#define HITMOLE_TITLE_STATE_USERSET		       4
#define HITMOLE_TITLE_STATE_SELECT             5
#define HITMOLE_TITLE_STATE_HIGSCORE           6
#define HITMOLE_TITLE_STATE_PAY				   7



#define NETAPP_APP_HITMOLE   133  //��ϷӦ�ú�

extern tScreen HitMole_Screen_Title;      //��Ϸ�б������
extern tScreen HitMole_Screen_Loading;    //��Ϸ��loading����
extern tScreen HitMole_Screen_InGame;
extern tScreen * HitMole_Screen_Next;     //��¼��screen����ʱ��������
extern DF_PictureLibrary allPicLib;   //ͼƬ�����
extern Manager * manager_my;//��Ϸ�й���ָ�룬�ɵ��õײ���غ���
extern MemoryBlock *memoryblock_my;         //�ڴ����

extern gm_s8 gamestage;
extern gm_s8 level;
extern gm_s8 percent;
extern gm_s16 hitMoleTitleState;   //���˵�״̬
extern gm_s16 hitMoleLoadingStep;
extern gm_s16 hitMoleLoadingStepTotal;
extern gm_s32 hitMoleHighScoreValue[10];
extern gm_s32 hitMoleHighScoreYear[10];
extern gm_s32 hitMoleHighScoreMonth[10];
extern gm_s32 hitMoleHighScoreDate[10];



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

extern void HitMole_Loading_UpdateStep(void);
extern void HitMole_Title_ChangeState(gm_s16 state);//�����л�״̬
extern gm_bool MyCdRectPoint(gm_s16 x,gm_s16 y,gm_s16 x1,gm_s16 y1,gm_s16 px,gm_s16 py);
#endif

