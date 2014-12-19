/*********************************************************************************************************************
*	游戏中的界面
*********************************************************************************************************************/
#include "HitMole_Screen.h"
#include "HitMolePlay.h"
#include "DF_Util.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
void HitMole_InGame_Init(void);
void HitMole_InGame_Destory(void);
void HitMole_InGame_Logic(void);
void HitMole_InGame_Render(tGraphics *g);
void HitMole_InGame_Pause(void);
void HitMole_InGame_Resume(void);
void HitMole_InGame_LoadResource(void);
DF_PictureLibrary allPicLib;
gm_s8 gamestage;
gm_s8 level;
gm_s8 percent;
HitMoleplay hitMoleplay;

tScreen HitMole_Screen_InGame;

void HitMole_InGame_Init(void)
{

}

void HitMole_InGame_Destory(void)
{
	allPicLib.Release(&allPicLib);
}

void HitMole_InGame_Logic(void)
{
	hitMoleplay.windows.DF_Update(&hitMoleplay.windows);
}

void HitMole_InGame_Render(tGraphics * g)
{
	hitMoleplay.windows.DF_Render(&hitMoleplay.windows);	
}

void HitMole_InGame_Pause(void)
{
	HitMole_Play_Windows_Update(&hitMoleplay);
}

void HitMole_InGame_Resume(void)
{
	HitMole_Play_Windows_Update(&hitMoleplay);
}
void HitMole_InGame_LoadResource(void)
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
	initDFPictureLibrary(&allPicLib,50);//初使化图片库
	HitMole_Loading_UpdateStep();
	initHitMoleplay(&hitMoleplay,ur,&allPicLib,20);
	HitMole_Loading_UpdateStep();
}
