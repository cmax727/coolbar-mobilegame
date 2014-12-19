/**********************************************************************************************************************
Logo½çÃæ
***********************************************************************************************************************/
#include "ONFF_Title.h"
#include "ONFF_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif

static Manager manager;
void initONFFTitle(ONFFTitle * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
       initManager(&manager);
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=ONFF_Title_Windows_Render;
	myself->windows.UpdateCallBack=ONFF_Title_Windows_Update;
	myself->picLib=picLib;
	myself->timer = 0;
	ONFF_Loading_UpdateStep();
	myself->imgTitle=myself->picLib->GetImage(myself->picLib,"logo_176.gif");
	
	ONFF_Loading_UpdateStep();
}	
void ONFF_Title_Windows_Render(void * param)
{
	ONFFTitle * myself=(ONFFTitle *)param;
	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(36,19,121));
	myself->picLib->DrawImageEx(myself->picLib,myself->imgTitle,(SCREEN_WIDTH-myself->picLib->GetImageWidth(myself->picLib,myself->imgTitle))/2,
								(SCREEN_HEIGHT-myself->picLib->GetImageHeight(myself->picLib,myself->imgTitle))/2,true,0);
}
void ONFF_Title_Windows_Update(void * param)
{
	ONFFTitle * myself = (ONFFTitle *)param;
	myself->timer++;
	if (getManagerPtr()->IsKeyDown(MF_KEY_ANY)||SCREEN_IsPointerDown()||myself->timer == 30 )
	{
		ONFF_Title_ChangeState(ONFF_TITLE_STATE_MENU);
	#ifdef FREE_REALEASE
		ONFF_Title_ChangeState(ONFF_TITLE_STATE_MENU);
	#endif
	
	}
}

