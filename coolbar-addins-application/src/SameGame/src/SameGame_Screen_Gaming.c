/*********************************************************************************************************************
*	游戏中的界面
*********************************************************************************************************************/
#include "SameGame_Screen.h"
#include "SameGame_Playing.h"
#include "DF_Util.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif

void SameGame_InGame_Init(void)
{
}

void SameGame_InGame_Destory(void)
{
	allPicLib.Release(&allPicLib);
}

void SameGame_InGame_Logic(void)
{
	sameGamePlaying.windows.DF_Update(&sameGamePlaying.windows);
}

void SameGame_InGame_Render(tGraphics * g)
{
	sameGamePlaying.windows.DF_Render(&sameGamePlaying.windows);	
}

void SameGame_InGame_Pause(void)
{
}

void SameGame_InGame_Resume(void)
{
	SameGame_Playing_Update(&sameGamePlaying);
}
void SameGame_InGame_LoadResource(void)
{	
	Rect ur;	//初始化屏幕矩形
	ur.x=0;
	ur.y=0;
	ur.w=SCREEN_WIDTH;
	ur.h=SCREEN_HEIGHT;

	initDFPictureLibrary(&allPicLib,60);//初使化图片库
	SameGame_Loading_UpdateStep();
	SameGame_Playing_Init(&sameGamePlaying,ur,&allPicLib,30);
	SameGame_Loading_UpdateStep();
}
