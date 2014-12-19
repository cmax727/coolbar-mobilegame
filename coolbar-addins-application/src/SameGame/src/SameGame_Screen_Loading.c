/***********************************************************************************************************************
过度页面
***********************************************************************************************************************/
#include "SameGame_Screen.h"   //包含它的目的是为了 把图片等资源包含进来
#include "DF_PictureLibrary.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif

#ifdef __WIN_32
	extern BOOL 	GAME_Update();
#endif
	
//在SCREEN_CHANGE()函数调用的时候 调用
void SameGame_Loading_Init(void)
{
	//初始化图片库,释放以前用过的所有图片
	allPicLib.Release(&allPicLib);		
	//重置内存
	memoryblock_my->Reset((void *)memoryblock_my);
	initDFPictureLibrary(&SameGameLoadingPicLib,5);
	
	sameGameLoadingRepaintAll = 1;
}

void SameGame_Loading_Destory()//销毁load中图片
{
	SameGameLoadingPicLib.Release(&SameGameLoadingPicLib);
}

//此类方法 被主线程循环调用  
void SameGame_Loading_Logic(void)
{
	gm_s32 w;
	GAME_SetKeyEnable(0);
	SameGame_Loading_Render(0);	
	sameGame_Screen_Next->NotifyLoadResource();   // 通知下个屏幕加载相关资源 如调用UniversalWal_Screen_Title 里的ONFF_Title_LoadResource（）；
	//又如 进入游戏界面 前有个加载资源的界面
	SCREEN_ChangeScreen(sameGame_Screen_Next);
	GAME_SetKeyEnable(1);
	
	w=sameGameLoadingStep/sameGameLoadingStepTotal;	
	if(sameGameLoadingRepaintAll)
	{
		SameGameLoadingPicLib.FillRect(&SameGameLoadingPicLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,DF_RGB565(102,51,0));
		sameGameLoadingRepaintAll = 0;
	}
	if(sameGameLoadingRepaintStep)
	{
		sameGameLoadingRepaintStep = 0;
	}
}

void SameGame_Loading_Render(tGraphics *g)//绘制loading进度条
{

}

void SameGame_Loading_Pause(void)
{
}

void SameGame_Loading_Resume(void)
{
}

void SameGame_Loading_LoadResource(void)
{
}

//更新屏幕显示
void SameGame_Loading_UpdateStep(void)
{
	sameGameLoadingStep++;
	if(sameGameLoadingStep>sameGameLoadingStepTotal)
		sameGameLoadingStep = sameGameLoadingStepTotal;
	sameGameLoadingRepaintStep = 1;
	SameGame_Loading_Render(0);
	#ifdef __WIN_32
		GAME_Update();
		SDL_Delay(50);
	#else
		GAME_RefresScreen();
	#endif
}
	
	

