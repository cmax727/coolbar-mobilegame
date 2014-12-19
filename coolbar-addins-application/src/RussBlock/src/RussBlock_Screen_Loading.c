	/*******************************************************************
* 2009 Wingtech, Incoporated. All Rights Reserved.
* 
* �ļ����ƣ�RussBlock_Screen_Loading.h

  �˹���Ϊ���ɽ��棬��ͼƬ���ڴ�����
*******************************************************************/

#include "RussBlock_Screen.h"   //��������Ŀ����Ϊ�� ��ͼƬ����Դ��������
#include "DF_PictureLibrary.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
extern void RussBlock_Loading_LoadResource();
extern void RussBlock_Loading_Init();
extern void RussBlock_Loading_Destory();
extern void RussBlock_Loading_Logic();
extern void RussBlock_Loading_Render(tGraphics *g);
extern void RussBlock_Loading_Pause();
extern void RussBlock_Loading_Resume();
#ifdef __WIN_32
extern BOOL		GAME_Update();
#endif

tScreen RussBlock_Screen_Loading =
{
	RussBlock_Loading_Init,
	RussBlock_Loading_Destory,
	RussBlock_Loading_Logic,
	RussBlock_Loading_Render,
	RussBlock_Loading_Pause,
	RussBlock_Loading_Resume,
	RussBlock_Loading_LoadResource,
};

tScreen * RussBlock_Screen_Next;

gm_s32 russBlockImageLoading[2];
gm_s32 russBlockImageHint;
 gm_s16 russBlockLoadingStep;
 gm_s16 russBlockLoadingStepTotal;
gm_s8 russBlockLoadingRepaintAll;
gm_s8 russBlockLoadingRepaintStep;
gm_s32 russBlockImageHintWidth;
gm_s32 russBlockImageHintHeight;

DF_PictureLibrary RussBlockLoadingPicLib;  //��Screen����ͼƬ��

//��SCREEN_CHANGE()�������õ�ʱ�� ����
void RussBlock_Loading_Init()
{
	//��ʼ��ͼƬ��,�ͷ���ǰ�ù�������ͼƬ
	russBlockPicLib.Release(&russBlockPicLib);      
	//�����ڴ�
	memoryblock_my->Reset((void *)memoryblock_my);
	initDFPictureLibrary(&RussBlockLoadingPicLib,5);
	russBlockImageLoading[0] = RussBlockLoadingPicLib.GetImage(&RussBlockLoadingPicLib,"loading.gif");
	russBlockImageLoading[1] = RussBlockLoadingPicLib.GetImage(&RussBlockLoadingPicLib,"loading1.gif");
	switch(Random(0,2))
	{
	case 0:
		russBlockImageHint = RussBlockLoadingPicLib.GetImage(&RussBlockLoadingPicLib,"wenzi6.gif");
		russBlockImageHintWidth = 153;
		russBlockImageHintHeight = 18;
		break;
	case 1:
		russBlockImageHint = RussBlockLoadingPicLib.GetImage(&RussBlockLoadingPicLib,"wenzi7.gif");
		russBlockImageHintWidth = 153;
		russBlockImageHintHeight = 18;
		break;
	case 2:
		russBlockImageHint = RussBlockLoadingPicLib.GetImage(&RussBlockLoadingPicLib,"wenzi8.gif");
		russBlockImageHintWidth = 153;
		russBlockImageHintHeight = 18;
		break;
	}
	russBlockLoadingRepaintAll = 1;
}

void RussBlock_Loading_Destory()//����load��ͼƬ
{
	RussBlockLoadingPicLib.Release(&RussBlockLoadingPicLib);
}

//���෽�� �����߳�ѭ������  
void RussBlock_Loading_Logic()
{
	GAME_SetKeyEnable(0);
	RussBlock_Loading_Render(0);	
	RussBlock_Screen_Next->NotifyLoadResource();   // ֪ͨ�¸���Ļ���������Դ �����UniversalWal_Screen_Title ���RussBlock_Title_LoadResource������
	//���� ������Ϸ���� ǰ�и�������Դ�Ľ���
	SCREEN_ChangeScreen(RussBlock_Screen_Next);
	GAME_SetKeyEnable(1);
}

void RussBlock_Loading_Render(tGraphics *g)//����loading������
{
	gm_s32 i,w;
	w=russBlockLoadingStep/russBlockLoadingStepTotal;	
	if(russBlockLoadingRepaintAll)
	{
		RussBlockLoadingPicLib.FillRect(&RussBlockLoadingPicLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,DF_RGB565(0,0,0));
#ifdef GAME_240_320
		RussBlockLoadingPicLib.DrawImageEx(&RussBlockLoadingPicLib,russBlockImageLoading[0],(SCREEN_WIDTH-106)>>1,180,1,0);
		RussBlockLoadingPicLib.DrawRegion(&RussBlockLoadingPicLib,russBlockImageLoading[1],(SCREEN_WIDTH-96)>>1,184,0,0,96*russBlockLoadingStep/russBlockLoadingStepTotal,7);
#endif
#ifdef GAME_176_220
		RussBlockLoadingPicLib.DrawImageEx(&RussBlockLoadingPicLib,russBlockImageLoading[0],(SCREEN_WIDTH-106)>>1,120,1,0);
		RussBlockLoadingPicLib.DrawRegion(&RussBlockLoadingPicLib,russBlockImageLoading[1],(SCREEN_WIDTH-96)>>1,124,0,0,96*russBlockLoadingStep/russBlockLoadingStepTotal,7);
#endif
		russBlockLoadingRepaintAll = 0;
	}
	if(russBlockLoadingRepaintStep)
	{
		if(russBlockLoadingStep<=russBlockLoadingStepTotal)
#ifdef GAME_240_320
			RussBlockLoadingPicLib.DrawRegion(&RussBlockLoadingPicLib,russBlockImageLoading[1],(SCREEN_WIDTH-96)>>1,184,0,0,96*russBlockLoadingStep/russBlockLoadingStepTotal,7);
#endif
#ifdef GAME_176_220
		RussBlockLoadingPicLib.DrawRegion(&RussBlockLoadingPicLib,russBlockImageLoading[1],(SCREEN_WIDTH-96)>>1,124,0,0,96*russBlockLoadingStep/russBlockLoadingStepTotal,7);
#endif
		russBlockLoadingRepaintStep = 0;
	}
}

void RussBlock_Loading_Pause()
{
}

void RussBlock_Loading_Resume()
{
}

void RussBlock_Loading_LoadResource()
{
}

//������Ļ��ʾ
void RussBlock_Loading_UpdateStep()
{
	russBlockLoadingStep++;
	if(russBlockLoadingStep>russBlockLoadingStepTotal)
		russBlockLoadingStep = russBlockLoadingStepTotal;
	russBlockLoadingRepaintStep = 1;
	RussBlock_Loading_Render(0);
#ifdef __WIN_32
	GAME_Update();
	SDL_Delay(50);
#else
	GAME_RefresScreen();
#endif
}



