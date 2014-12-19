/*********************************************************************************************************************
*	游戏中的界面
*********************************************************************************************************************/
#include "MemoryBox_Screen.h"
#include "MemoryBoxPlay.h"
#include "DF_Util.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
void MemoryBox_InGame_Init(void);
void MemoryBox_InGame_Destory(void);
void MemoryBox_InGame_Logic(void);
void MemoryBox_InGame_Render(tGraphics *g);
void MemoryBox_InGame_Pause(void);
void MemoryBox_InGame_Resume(void);
void MemoryBox_InGame_LoadResource(void);
DF_PictureLibrary allPicLib;
gm_s8 gamestage;
gm_s8 level;
MemoryBoxplay memoryBoxplay;

tScreen MemoryBox_Screen_InGame;

void MemoryBox_InGame_Init(void)
{

}

void MemoryBox_InGame_Destory(void)
{
	allPicLib.Release(&allPicLib);
}

void MemoryBox_InGame_Logic(void)
{
	memoryBoxplay.windows.DF_Update(&memoryBoxplay.windows);
}

void MemoryBox_InGame_Render(tGraphics * g)
{
	memoryBoxplay.windows.DF_Render(&memoryBoxplay.windows);	
}

void MemoryBox_InGame_Pause(void)
{
//	memoryBoxplay.gamepause = true;
}

void MemoryBox_InGame_Resume(void)
{
	MemoryBox_Play_Windows_Update(&memoryBoxplay);
}
void MemoryBox_InGame_LoadResource(void)
{	
	Rect ur;	//初始化屏幕矩形
	ur.x=0;
	ur.y=0;
	ur.w=SCREEN_WIDTH;
	ur.h=SCREEN_HEIGHT;

#ifdef GAME_176_220
	ur.w = SCREEN_WIDTH;
	ur.y = 0;
	ur.h = SCREEN_HEIGHT;
#endif
	initDFPictureLibrary(&allPicLib,60);//初使化图片库
	MemoryBox_Loading_UpdateStep();
	initMemoryBoxplay(&memoryBoxplay,ur,&allPicLib,30);
	MemoryBox_Loading_UpdateStep();
}
