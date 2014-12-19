/*******************************************************************
* 2010
* 
* �ļ����ƣ�ONFF_Screen.h

�˹������趨��ϷһЩ���ó����͹��÷���
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

#define NETAPP_APP_MONSTER   2039			//��ϷӦ�ú�

tScreen em_Screen_Title;				//��Ϸ�б������
tScreen em_Screen_Loading;			//��Ϸ��loading����
tScreen em_Screen_InGame;
tScreen * em_Screen_Next;				//��¼��screen����ʱ��������

DF_PictureLibrary allPicLib;				//ͼƬ�����
DF_PictureLibrary SameGameLoadingPicLib;	//��Screen����ͼƬ��
Manager * manager_my;
MemoryBlock *memoryblock_my;
DF_Record emRecord;
static DF_DataPackage dataPackage;

// gm_s16 shape;
// gm_s16 level;
// gm_s16 newGame;
// gm_s16 completeState;
// gm_s16 emTitleState;					//���˵�״̬
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
