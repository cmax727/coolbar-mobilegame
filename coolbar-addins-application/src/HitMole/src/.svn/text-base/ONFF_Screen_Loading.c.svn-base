/***********************************************************************************************************************
过度页面
***********************************************************************************************************************/
#include "ONFF_Screen.h"   //包含它的目的是为了 把图片等资源包含进来
#include "DF_PictureLibrary.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
	 void ONFF_Loading_LoadResource(void);
	 void ONFF_Loading_Init(void);
	 void ONFF_Loading_Destory(void);
	 void ONFF_Loading_Logic(void);
	 void ONFF_Loading_Render(tGraphics *g);
	 void ONFF_Loading_Pause(void);
	 void ONFF_Loading_Resume(void);
#ifdef __WIN_32
	extern BOOL 	GAME_Update();
#endif
	
	tScreen ONFF_Screen_Loading;
	
	tScreen * ONFF_Screen_Next;
	
	gm_s32 oNFFImageLoading[2];
	 gm_s16 oNFFLoadingStep;
	 gm_s16 oNFFLoadingStepTotal;
	gm_s8 oNFFLoadingRepaintAll;
	gm_s8 oNFFLoadingRepaintStep;
	gm_s32 oNFFImageHintWidth;
	gm_s32 oNFFImageHintHeight;
	
	DF_PictureLibrary ONFFLoadingPicLib;  //本Screen自有图片库
	
	
	//在SCREEN_CHANGE()函数调用的时候 调用
	void ONFF_Loading_Init(void)
	{
		//初始化图片库,释放以前用过的所有图片
		oNFFPicLib.Release(&oNFFPicLib);		
		//重置内存
		memoryblock_my->Reset((void *)memoryblock_my);
		initDFPictureLibrary(&ONFFLoadingPicLib,5);
		oNFFImageLoading[0] = ONFFLoadingPicLib.GetImage(&ONFFLoadingPicLib,"loading.gif");
		oNFFImageLoading[1] = ONFFLoadingPicLib.GetImage(&ONFFLoadingPicLib,"loading1.gif");
		
		oNFFLoadingRepaintAll = 1;
	}
	
	void ONFF_Loading_Destory()//销毁load中图片
	{
		ONFFLoadingPicLib.Release(&ONFFLoadingPicLib);
	}
	
	//此类方法 被主线程循环调用  
	void ONFF_Loading_Logic(void)
	{
		GAME_SetKeyEnable(0);
		ONFF_Loading_Render(0);	
		ONFF_Screen_Next->NotifyLoadResource();   // 通知下个屏幕加载相关资源 如调用UniversalWal_Screen_Title 里的ONFF_Title_LoadResource（）；
		//又如 进入游戏界面 前有个加载资源的界面
		SCREEN_ChangeScreen(ONFF_Screen_Next);
		GAME_SetKeyEnable(1);
	}
	
	void ONFF_Loading_Render(tGraphics *g)//绘制loading进度条
	{
		gm_s32 w;
		w=oNFFLoadingStep/oNFFLoadingStepTotal;	
		if(oNFFLoadingRepaintAll)
		{
			ONFFLoadingPicLib.FillRect(&ONFFLoadingPicLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,DF_RGB565(36,19,121));
#ifdef GAME_240_320
			ONFFLoadingPicLib.DrawImageEx(&ONFFLoadingPicLib,oNFFImageLoading[0],(SCREEN_WIDTH-106)>>1,180,1,0);
			ONFFLoadingPicLib.DrawRegion(&ONFFLoadingPicLib,oNFFImageLoading[1],(SCREEN_WIDTH-96)>>1,184,0,0,96*oNFFLoadingStep/oNFFLoadingStepTotal,7);
#endif
#ifdef GAME_176_220
			ONFFLoadingPicLib.DrawImageEx(&ONFFLoadingPicLib,oNFFImageLoading[0],(SCREEN_WIDTH-106)>>1,120,1,0);
			ONFFLoadingPicLib.DrawRegion(&ONFFLoadingPicLib,oNFFImageLoading[1],(SCREEN_WIDTH-96)>>1,124,0,0,96*oNFFLoadingStep/oNFFLoadingStepTotal,7);
#endif
			oNFFLoadingRepaintAll = 0;
		}
		if(oNFFLoadingRepaintStep)
		{
			if(oNFFLoadingStep<=oNFFLoadingStepTotal)
#ifdef GAME_240_320
				ONFFLoadingPicLib.DrawRegion(&ONFFLoadingPicLib,oNFFImageLoading[1],(SCREEN_WIDTH-96)>>1,184,0,0,96*oNFFLoadingStep/oNFFLoadingStepTotal,7);
#endif
#ifdef GAME_176_220
			ONFFLoadingPicLib.DrawRegion(&ONFFLoadingPicLib,oNFFImageLoading[1],(SCREEN_WIDTH-96)>>1,124,0,0,96*oNFFLoadingStep/oNFFLoadingStepTotal,7);
#endif
			oNFFLoadingRepaintStep = 0;
		}
	}
	
	void ONFF_Loading_Pause(void)
	{
	}
	
	void ONFF_Loading_Resume(void)
	{
	}
	
	void ONFF_Loading_LoadResource(void)
	{
	}
	
	//更新屏幕显示
	void ONFF_Loading_UpdateStep(void)
	{
		oNFFLoadingStep++;
		if(oNFFLoadingStep>oNFFLoadingStepTotal)
			oNFFLoadingStep = oNFFLoadingStepTotal;
		oNFFLoadingRepaintStep = 1;
		ONFF_Loading_Render(0);
#ifdef __WIN_32
		GAME_Update();
		SDL_Delay(50);
#else
		GAME_RefresScreen();
#endif
	}
	
	


