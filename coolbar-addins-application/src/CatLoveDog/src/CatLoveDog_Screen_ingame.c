/*********************************************************************************************************************
*	游戏中的界面
*********************************************************************************************************************/
#include "CatLoveDog_Screen.h"
#include "CatLoveDog_InGame.h"
#include "DF_Util.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif



void CatLoveDog_InGame_Init(void);
void CatLoveDog_InGame_Destory(void);
void CatLoveDog_InGame_Logic(void);
void CatLoveDog_InGame_Render(tGraphics *g);
void CatLoveDog_InGame_Pause(void);
void CatLoveDog_InGame_Resume(void);
void CatLoveDog_InGame_LoadResource(void);
DF_PictureLibrary catLoveDogPicLib;
tScreen CatLoveDog_Screen_InGame;
CatLoveDog_InGame catLoveDog_InGame;
gm_s8 level;

void CatLoveDog_InGame_Init(void)
{

}

void CatLoveDog_InGame_Destory(void)
{
	extVmSysManager->VmSetFPS(100);
	catLoveDogPicLib.Release(&catLoveDogPicLib);
}

void CatLoveDog_InGame_Logic(void)
{
	catLoveDog_InGame.windows.DF_Update(&catLoveDog_InGame.windows);
}

void CatLoveDog_InGame_Render(tGraphics * g)
{
	catLoveDog_InGame.windows.DF_Render(&catLoveDog_InGame.windows);	
}

void CatLoveDog_InGame_Pause(void)
{
//	CatLoveDogMap.Game_stage = 0;
}

void CatLoveDog_InGame_Resume(void)
{
//	CatLoveDog_Pause_Render(&CatLoveDogMap);
}


void CatLoveDog_InGame_LoadResource(void)
{	
	Rect ur;	
	ur.x=0;
	ur.y=0;
	ur.w=SCREEN_WIDTH;
	ur.h=SCREEN_HEIGHT;

#ifdef GAME_176_220
	ur.w = SCREEN_WIDTH;
	ur.y = 0;
	ur.h = SCREEN_HEIGHT;
#endif
	initDFPictureLibrary(&catLoveDogPicLib,60);
	
	CatLoveDog_Loading_UpdateStep();
	initCatLoveDog_InGame(&catLoveDog_InGame,ur,&catLoveDogPicLib,20);
	CatLoveDog_Loading_UpdateStep();
}
