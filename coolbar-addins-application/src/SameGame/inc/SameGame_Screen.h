/*******************************************************************
* 2010
* 
* �ļ����ƣ�ONFF_Screen.h

�˹������趨��ϷһЩ���ó����͹��÷���
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

//�������״̬
#define SAMEGAME_STATE_LOGO     				0
#define SAMEGAME_STATE_TITLEMENU           		1
#define SAMEGAME_STATE_CHANGECHIP          		2
#define SAMEGAME_STATE_COMPLETEMENU          	3
#define SAMEGAME_STATE_PLAYMENU					4
#define SAMEGAME_STATE_HIGSCORE					5

#define NETAPP_APP_SAMEGAME   2039			//��ϷӦ�ú�

tScreen sameGame_Screen_Title;				//��Ϸ�б������
tScreen sameGame_Screen_Loading;			//��Ϸ��loading����
tScreen sameGame_Screen_InGame;
tScreen * sameGame_Screen_Next;				//��¼��screen����ʱ��������

DF_PictureLibrary allPicLib;				//ͼƬ�����
DF_PictureLibrary SameGameLoadingPicLib;	//��Screen����ͼƬ��
Manager * manager_my;
MemoryBlock *memoryblock_my;
DF_Record sameGameRecord;
static DF_DataPackage dataPackage;

gm_s16 shape;
gm_s16 level;
gm_s16 newGame;
gm_s16 completeState;
gm_s16 sameGameTitleState;					//���˵�״̬
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
void SameGame_Title_ChangeState(gm_s16 state);//�����л�״̬

#endif
