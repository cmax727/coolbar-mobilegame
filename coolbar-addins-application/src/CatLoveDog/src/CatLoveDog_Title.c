/**********************************************************************************************************************
Logo½çÃæ
***********************************************************************************************************************/
#include "CatLoveDog_Title.h"
#include "CatLoveDog_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif

static Manager manager;
void initCatLoveDogTitle(CatLoveDogTitle * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
       initManager(&manager);
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=CatLoveDog_Title_Windows_Render;
	myself->windows.UpdateCallBack=CatLoveDog_Title_Windows_Update;
	myself->picLib=picLib;
	myself->timer = 0;
	CatLoveDog_Loading_UpdateStep();
	myself->imgTitle=myself->picLib->GetImage(myself->picLib,"logo_176.gif");
	
	CatLoveDog_Loading_UpdateStep();
}	
void CatLoveDog_Title_Windows_Render(void * param)
{
	CatLoveDogTitle * myself=(CatLoveDogTitle *)param;
	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(36,19,121));
	myself->picLib->DrawImageEx(myself->picLib,myself->imgTitle,(SCREEN_WIDTH-myself->picLib->GetImageWidth(myself->picLib,myself->imgTitle))/2,
								(SCREEN_HEIGHT-myself->picLib->GetImageHeight(myself->picLib,myself->imgTitle))/2,true,0);
}
void CatLoveDog_Title_Windows_Update(void * param)
{
	CatLoveDogTitle * myself = (CatLoveDogTitle *)param;
	myself->timer++;
	if (getManagerPtr()->IsKeyDown(MF_KEY_ANY)||SCREEN_IsPointerDown()||myself->timer == 30 )
	{
		CatLoveDog_Title_ChangeState(CatLoveDog_TITLE_STATE_MENU);
	#ifdef FREE_REALEASE
		CatLoveDog_Title_ChangeState(CatLoveDog_TITLE_STATE_MENU);
	#endif
	
	}
}

