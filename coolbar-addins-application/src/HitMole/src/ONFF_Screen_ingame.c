/*********************************************************************************************************************
*	游戏中的界面
*********************************************************************************************************************/
#include "ONFF_Screen.h"
#include "DF_Util.h"
#include "ONFF_Set.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
void ONFF_InGame_Init(void);
void ONFF_InGame_Destory(void);
void ONFF_InGame_Logic(void);
void ONFF_InGame_Render(tGraphics *g);
void ONFF_InGame_Pause(void);
void ONFF_InGame_Resume(void);
void ONFF_InGame_LoadResource(void);
DF_PictureLibrary oNFFPicLib;
ONFF_Map oNFFMap;
GameState gamestate;
tScreen ONFF_Screen_InGame;

void ONFF_InGame_Init(void)
{

}

void ONFF_InGame_Destory(void)
{
	oNFFPicLib.Release(&oNFFPicLib);
}

void ONFF_InGame_Logic(void)
{
	oNFFMap.windows.DF_Update(&oNFFMap.windows);
}

void ONFF_InGame_Render(tGraphics * g)
{
	oNFFMap.windows.DF_Render(&oNFFMap.windows);	
}

void ONFF_InGame_Pause(void)
{
	oNFFMap.Game_stage = 0;
}

void ONFF_InGame_Resume(void)
{
	ONFF_Pause_Render(&oNFFMap);
}


void ONFF_InGame_LoadResource(void)
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
	gamestate.gameplayerlife = gamePlayerlife;
	gamestate.gameplayerbomb = gamePlayerbomb;
	initDFPictureLibrary(&oNFFPicLib,48);
	ONFF_Loading_UpdateStep();
	initONFFMap(&oNFFMap,ur,&oNFFPicLib,gamestate,20);
	ONFF_Loading_UpdateStep();
}
