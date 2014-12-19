/**********************************************************************************************************************
Logo界面
***********************************************************************************************************************/
#include "HitMole_Title.h"
#include "HitMole_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif

//游戏中logo界面初使化和加载
static Manager manager;
void initHitMoleTitle(HitMoleTitle * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
    initManager(&manager);
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=HitMole_Title_Windows_Render;
	myself->windows.UpdateCallBack=HitMole_Title_Windows_Update;
	myself->picLib=picLib;
	myself->timer = 0;
	HitMole_Loading_UpdateStep();
	myself->imgTitle=myself->picLib->GetImage(myself->picLib,"logo_176.gif");
	
	HitMole_Loading_UpdateStep();
}	
//游戏中logo界面绘制
void HitMole_Title_Windows_Render(void * param)
{
	HitMoleTitle * myself=(HitMoleTitle *)param;
	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(102,51,0));
	myself->picLib->DrawImageEx(myself->picLib,myself->imgTitle,(SCREEN_WIDTH-myself->picLib->GetImageWidth(myself->picLib,myself->imgTitle))/2,
								(SCREEN_HEIGHT-myself->picLib->GetImageHeight(myself->picLib,myself->imgTitle))/2,true,0);
}
//游戏中logo界面按键
void HitMole_Title_Windows_Update(void * param)
{
	HitMoleTitle * myself = (HitMoleTitle *)param;
	myself->timer++;
	if (getManagerPtr()->IsKeyDown(MF_KEY_ANY)||SCREEN_IsPointerDown()||myself->timer == 30 )
	{
		HitMole_Title_ChangeState(HITMOLE_TITLE_STATE_MENU);
	#ifdef FREE_REALEASE
		HitMole_Title_ChangeState(HITMOLE_TITLE_STATE_MENU);
	#endif
	
	}
}

