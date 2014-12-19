/***********************************************************************************************************************
过度页面
***********************************************************************************************************************/
#include "CatLoveDog_Screen.h"   //包含它的目的是为了 把图片等资源包含进来
#include "DF_PictureLibrary.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
	 void CatLoveDog_Loading_LoadResource(void);
	 void CatLoveDog_Loading_Init(void);
	 void CatLoveDog_Loading_Destory(void);
	 void CatLoveDog_Loading_Logic(void);
	 void CatLoveDog_Loading_Render(tGraphics *g);
	 void CatLoveDog_Loading_Pause(void);
	 void CatLoveDog_Loading_Resume(void);
#ifdef __WIN_32
	extern BOOL 	GAME_Update();
#endif
	
	tScreen CatLoveDog_Screen_Loading;
	
	tScreen * CatLoveDog_Screen_Next;
	
	gm_s32 CatLoveDogImageLoading[2];
	 gm_s16 catLoveDogLoadingStep;
	 gm_s16 catLoveDogLoadingStepTotal;
	gm_s8 catLoveDogLoadingRepaintAll;
	gm_s8 catLoveDogLoadingRepaintStep;
	gm_s32 CatLoveDogImageHintWidth;
	gm_s32 CatLoveDogImageHintHeight;
	
	DF_PictureLibrary catLoveDogLoadingPicLib;  //本Screen自有图片库
	
	
	//在SCREEN_CHANGE()函数调用的时候 调用
	void CatLoveDog_Loading_Init(void)
	{
		//初始化图片库,释放以前用过的所有图片
		catLoveDogPicLib.Release(&catLoveDogPicLib);		
		//重置内存
		memoryblock_my->Reset((void *)memoryblock_my);
		initDFPictureLibrary(&catLoveDogLoadingPicLib,5);
		CatLoveDogImageLoading[0] = catLoveDogLoadingPicLib.GetImage(&catLoveDogLoadingPicLib,"loading.gif");
		CatLoveDogImageLoading[1] = catLoveDogLoadingPicLib.GetImage(&catLoveDogLoadingPicLib,"loading1.gif");
		
		catLoveDogLoadingRepaintAll = 1;
	}
	
	void CatLoveDog_Loading_Destory()//销毁load中图片
	{
		catLoveDogLoadingPicLib.Release(&catLoveDogLoadingPicLib);
	}
	
	//此类方法 被主线程循环调用  
	void CatLoveDog_Loading_Logic(void)
	{
		GAME_SetKeyEnable(0);
		CatLoveDog_Loading_Render(0);	
		CatLoveDog_Screen_Next->NotifyLoadResource();   // 通知下个屏幕加载相关资源 如调用UniversalWal_Screen_Title 里的CatLoveDog_Title_LoadResource（）；
		//又如 进入游戏界面 前有个加载资源的界面
		SCREEN_ChangeScreen(CatLoveDog_Screen_Next);
		GAME_SetKeyEnable(1);
	}
	
	void CatLoveDog_Loading_Render(tGraphics *g)//绘制loading进度条
	{
		gm_s32 w;
		w=catLoveDogLoadingStep/catLoveDogLoadingStepTotal;	
		if(catLoveDogLoadingRepaintAll)
		{
			catLoveDogLoadingPicLib.FillRect(&catLoveDogLoadingPicLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,DF_RGB565(36,19,121));
#ifdef GAME_240_320
			catLoveDogLoadingPicLib.DrawImageEx(&catLoveDogLoadingPicLib,CatLoveDogImageLoading[0],(SCREEN_WIDTH-106)>>1,180,1,0);
			catLoveDogLoadingPicLib.DrawRegion(&catLoveDogLoadingPicLib,CatLoveDogImageLoading[1],(SCREEN_WIDTH-96)>>1,184,0,0,96*catLoveDogLoadingStep/catLoveDogLoadingStepTotal,7);
#endif
#ifdef GAME_176_220
			catLoveDogLoadingPicLib.DrawImageEx(&catLoveDogLoadingPicLib,CatLoveDogImageLoading[0],(SCREEN_WIDTH-106)>>1,120,1,0);
			catLoveDogLoadingPicLib.DrawRegion(&catLoveDogLoadingPicLib,CatLoveDogImageLoading[1],(SCREEN_WIDTH-96)>>1,124,0,0,96*catLoveDogLoadingStep/catLoveDogLoadingStepTotal,7);
#endif
			catLoveDogLoadingRepaintAll = 0;
		}
		if(catLoveDogLoadingRepaintStep)
		{
			if(catLoveDogLoadingStep<=catLoveDogLoadingStepTotal)
#ifdef GAME_240_320
				catLoveDogLoadingPicLib.DrawRegion(&catLoveDogLoadingPicLib,CatLoveDogImageLoading[1],(SCREEN_WIDTH-96)>>1,184,0,0,96*catLoveDogLoadingStep/catLoveDogLoadingStepTotal,7);
#endif
#ifdef GAME_176_220
			catLoveDogLoadingPicLib.DrawRegion(&catLoveDogLoadingPicLib,CatLoveDogImageLoading[1],(SCREEN_WIDTH-96)>>1,124,0,0,96*catLoveDogLoadingStep/catLoveDogLoadingStepTotal,7);
#endif
			catLoveDogLoadingRepaintStep = 0;
		}
	}
	
	void CatLoveDog_Loading_Pause(void)
	{
	}
	
	void CatLoveDog_Loading_Resume(void)
	{
	}
	
	void CatLoveDog_Loading_LoadResource(void)
	{
	}
	
	//更新屏幕显示
	void CatLoveDog_Loading_UpdateStep(void)
	{
		catLoveDogLoadingStep++;
		if(catLoveDogLoadingStep>catLoveDogLoadingStepTotal)
			catLoveDogLoadingStep = catLoveDogLoadingStepTotal;
		catLoveDogLoadingRepaintStep = 1;
		CatLoveDog_Loading_Render(0);
#ifdef __WIN_32
		GAME_Update();
		SDL_Delay(50);
#else
		GAME_RefresScreen();
#endif
	}
	
	


