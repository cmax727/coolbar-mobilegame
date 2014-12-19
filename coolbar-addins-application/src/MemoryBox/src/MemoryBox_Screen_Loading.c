/***********************************************************************************************************************
过度页面
***********************************************************************************************************************/
#include "MemoryBox_Screen.h"   //包含它的目的是为了 把图片等资源包含进来
#include "DF_PictureLibrary.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
	 void MemoryBox_Loading_LoadResource(void);
	 void MemoryBox_Loading_Init(void);
	 void MemoryBox_Loading_Destory(void);
	 void MemoryBox_Loading_Logic(void);
	 void MemoryBox_Loading_Render(tGraphics *g);
	 void MemoryBox_Loading_Pause(void);
	 void MemoryBox_Loading_Resume(void);
#ifdef __WIN_32
	extern BOOL 	GAME_Update();
#endif
	
	tScreen MemoryBox_Screen_Loading;
	
	tScreen * MemoryBox_Screen_Next;
	
	gm_s32 memoryBoxmageLoading[2];
	 gm_s16 memoryBoxLoadingStep;
	 gm_s16 memoryBoxLoadingStepTotal;
	gm_s8 memoryBoxLoadingRepaintAll;
	gm_s8 memoryBoxLoadingRepaintStep;
	
	DF_PictureLibrary MemoryBoxLoadingPicLib;  //本Screen自有图片库
	
	
	//在SCREEN_CHANGE()函数调用的时候 调用
	void MemoryBox_Loading_Init(void)
	{
		//初始化图片库,释放以前用过的所有图片
		allPicLib.Release(&allPicLib);		
		//重置内存
		memoryblock_my->Reset((void *)memoryblock_my);
		initDFPictureLibrary(&MemoryBoxLoadingPicLib,5);
		memoryBoxmageLoading[0] = MemoryBoxLoadingPicLib.GetImage(&MemoryBoxLoadingPicLib,"loading.gif");
		memoryBoxmageLoading[1] = MemoryBoxLoadingPicLib.GetImage(&MemoryBoxLoadingPicLib,"loading1.gif");
		
		memoryBoxLoadingRepaintAll = 1;
	}
	
	void MemoryBox_Loading_Destory()//销毁load中图片
	{
		MemoryBoxLoadingPicLib.Release(&MemoryBoxLoadingPicLib);
	}
	
	//此类方法 被主线程循环调用  
	void MemoryBox_Loading_Logic(void)
	{
		GAME_SetKeyEnable(0);
		MemoryBox_Loading_Render(0);	
		MemoryBox_Screen_Next->NotifyLoadResource();   // 通知下个屏幕加载相关资源 如调用UniversalWal_Screen_Title 里的ONFF_Title_LoadResource（）；
		//又如 进入游戏界面 前有个加载资源的界面
		SCREEN_ChangeScreen(MemoryBox_Screen_Next);
		GAME_SetKeyEnable(1);
	}
	
	void MemoryBox_Loading_Render(tGraphics *g)//绘制loading进度条
	{
		gm_s32 w;
		w=memoryBoxLoadingStep/memoryBoxLoadingStepTotal;	
		if(memoryBoxLoadingRepaintAll)
		{
			MemoryBoxLoadingPicLib.FillRect(&MemoryBoxLoadingPicLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,DF_RGB565(102,51,0));
#ifdef GAME_240_320
			MemoryBoxLoadingPicLib.DrawImageEx(&MemoryBoxLoadingPicLib,memoryBoxmageLoading[0],(SCREEN_WIDTH-106)>>1,180,1,0);
			MemoryBoxLoadingPicLib.DrawRegion(&MemoryBoxLoadingPicLib,memoryBoxmageLoading[1],(SCREEN_WIDTH-96)>>1,184,0,0,96*memoryBoxLoadingStep/memoryBoxLoadingStepTotal,7);
#endif
#ifdef GAME_176_220
			MemoryBoxLoadingPicLib.DrawImageEx(&MemoryBoxLoadingPicLib,memoryBoxmageLoading[0],(SCREEN_WIDTH-106)>>1,120,1,0);
			MemoryBoxLoadingPicLib.DrawRegion(&MemoryBoxLoadingPicLib,memoryBoxmageLoading[1],(SCREEN_WIDTH-96)>>1,124,0,0,96*memoryBoxLoadingStep/memoryBoxLoadingStepTotal,7);
#endif
			memoryBoxLoadingRepaintAll = 0;
		}
		if(memoryBoxLoadingRepaintStep)
		{
			if(memoryBoxLoadingStep<=memoryBoxLoadingStepTotal)
#ifdef GAME_240_320
				MemoryBoxLoadingPicLib.DrawRegion(&MemoryBoxLoadingPicLib,memoryBoxmageLoading[1],(SCREEN_WIDTH-96)>>1,184,0,0,96*memoryBoxLoadingStep/memoryBoxLoadingStepTotal,7);
#endif
#ifdef GAME_176_220
			MemoryBoxLoadingPicLib.DrawRegion(&MemoryBoxLoadingPicLib,memoryBoxmageLoading[1],(SCREEN_WIDTH-96)>>1,124,0,0,96*memoryBoxLoadingStep/memoryBoxLoadingStepTotal,7);
#endif
			memoryBoxLoadingRepaintStep = 0;
		}
	}
	
	void MemoryBox_Loading_Pause(void)
	{
	}
	
	void MemoryBox_Loading_Resume(void)
	{
	}
	
	void MemoryBox_Loading_LoadResource(void)
	{
	}
	
	//更新屏幕显示
	void MemoryBox_Loading_UpdateStep(void)
	{
		memoryBoxLoadingStep++;
		if(memoryBoxLoadingStep>memoryBoxLoadingStepTotal)
			memoryBoxLoadingStep = memoryBoxLoadingStepTotal;
		memoryBoxLoadingRepaintStep = 1;
		MemoryBox_Loading_Render(0);
#ifdef __WIN_32
		GAME_Update();
		SDL_Delay(50);
#else
		GAME_RefresScreen();
#endif
	}
	
	

