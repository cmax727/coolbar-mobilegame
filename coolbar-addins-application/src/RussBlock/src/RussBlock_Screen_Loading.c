	/*******************************************************************
* 2009 Wingtech, Incoporated. All Rights Reserved.
* 
* 文件名称：RussBlock_Screen_Loading.h

  此功能为过渡界面，把图片和内存重置
*******************************************************************/

#include "RussBlock_Screen.h"   //包含它的目的是为了 把图片等资源包含进来
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

DF_PictureLibrary RussBlockLoadingPicLib;  //本Screen自有图片库

//在SCREEN_CHANGE()函数调用的时候 调用
void RussBlock_Loading_Init()
{
	//初始化图片库,释放以前用过的所有图片
	russBlockPicLib.Release(&russBlockPicLib);      
	//重置内存
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

void RussBlock_Loading_Destory()//销毁load中图片
{
	RussBlockLoadingPicLib.Release(&RussBlockLoadingPicLib);
}

//此类方法 被主线程循环调用  
void RussBlock_Loading_Logic()
{
	GAME_SetKeyEnable(0);
	RussBlock_Loading_Render(0);	
	RussBlock_Screen_Next->NotifyLoadResource();   // 通知下个屏幕加载相关资源 如调用UniversalWal_Screen_Title 里的RussBlock_Title_LoadResource（）；
	//又如 进入游戏界面 前有个加载资源的界面
	SCREEN_ChangeScreen(RussBlock_Screen_Next);
	GAME_SetKeyEnable(1);
}

void RussBlock_Loading_Render(tGraphics *g)//绘制loading进度条
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

//更新屏幕显示
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



