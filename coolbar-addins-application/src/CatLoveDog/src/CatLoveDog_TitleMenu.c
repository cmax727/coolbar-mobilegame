#include "CatLoveDog_TitleMenu.h"
#include "CatLoveDog_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif

static Manager manager;
void CatLoveDog_DoSelectMenu(gm_s16 id);

void initCatLoveDogTitleMenu(CatLoveDogTitleMenu * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
	initManager(&manager);
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=CatLoveDog_TitleMenu_Render;
	myself->windows.UpdateCallBack=CatLoveDog_TitleMenu_Update;
	CatLoveDog_Loading_UpdateStep();
	myself->picLib=picLib;
	myself->imgTitleMenu[0]=picLib->GetImage(picLib,"menu.gif");
	CatLoveDog_Loading_UpdateStep();
	myself->imgTitleMenu[1]=picLib->GetImage(picLib,"se.gif");
	CatLoveDog_Loading_UpdateStep();
	myself->selectMenu=0;
}

void CatLoveDog_DrawMiddleString(gm_u8 * str,gm_s32 x,gm_s32 y,gm_u32 color)
{
	gm_s32 width = (gm_s32)extVmLcdManager->VMGetStringWidth((char*)str);
	gm_s32 height = (gm_s32)extVmLcdManager->VMGetStringHeight((char*)str);
	width = width>>1;
	height = height>>1;
	extVmGameLcdManager->DrawString((char*)str,strlen(str),x-width,y-height,color);
}

void CatLoveDogMonthPayCheck(void)
{
	if(extVmBillingManager->BILLING_GetRemainDay(NETAPP_APP_CatLoveDog,NETAPP_BILLING_METHOD_ONCE_MONTH) == 0)
	{	
		CatLoveDog_Title_ChangeState(CatLoveDog_TITLE_STATE_PAY);

	}else
	{
		CatLoveDog_Screen_Next = &CatLoveDog_Screen_InGame;
		catLoveDogLoadingStep = 0;
		catLoveDogLoadingStepTotal = 16;
		SCREEN_ChangeScreen(&CatLoveDog_Screen_Loading);
		
	}
}

gm_bool CatLoveDogCdRectPoint(gm_s16 x,gm_s16 y,gm_s16 x1,gm_s16 y1,gm_s16 px,gm_s16 py)
{
	if(px>=x && px<=x1 && py>=y && py<=y1)
	{
		return true;
	}else
		return false;
}

void CatLoveDog_TitleMenu_Render(void *param)
{
	CatLoveDogTitleMenu * myself = (CatLoveDogTitleMenu *)param;
	
	manager.DrawFullScreen(myself->picLib->image[myself->imgTitleMenu[0]]);
	
#ifdef GAME_240_320
	//if(myself->selectMenu == 0 || myself->selectMenu == 2)
	myself->picLib->DrawRegionEx(myself->picLib,myself->imgTitleMenu[1],58-(myself->selectMenu%2)*44,7+62*(myself->selectMenu),0,(myself->selectMenu)*63,175,63,true,0);
#endif
#ifdef	GAME_176_220
	myself->picLib->DrawRegionEx(myself->picLib,myself->imgTitleMenu[1],0,109+20*(myself->selectMenu),(myself->selectMenu)*67.4,0,67.4,20,true,0);
#endif
}

void CatLoveDog_TitleMenu_Update(void * param)
{
	CatLoveDogTitleMenu * myself = (CatLoveDogTitleMenu *)param;
	Rect ur;
	gm_s32 px,py;
	#ifdef GAME_240_320
	ur.x=(SCREEN_WIDTH-30)>>1;
	ur.y=155;
	ur.w=92;
	ur.h=150;
#endif
#ifdef GAME_176_220
	ur.x=78;
	ur.y=190;
	ur.w=67;
	ur.h=100;
#endif
	DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);
if (extOldGameManager->IsKeyDown(MF_KEY_UP|MF_KEY_2))
	{
		myself->selectMenu--;
		myself->selectMenu+=4;
		myself->selectMenu=(myself->selectMenu+1)%5;
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);
	}
	else if(extOldGameManager->IsKeyDown(MF_KEY_8|MF_KEY_DOWN))
	{
		myself->selectMenu++;
		myself->selectMenu+=4;
		myself->selectMenu=(myself->selectMenu+1)%5;
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);
	}
	
	if(extOldGameManager->IsKeyDown(MF_KEY_5|MF_KEY_MID|MF_KEY_LEFTSOFT))
	{
		CatLoveDog_DoSelectMenu(myself->selectMenu);
	}

	#ifdef GAME_240_320
	if(extOldGameManager->SCREEN_IsPointerDown())
	{
		px = SCREEN_GetPointerX();
		py = SCREEN_GetPointerY();

		/*
		if(CdRectPoint3(32,18,210,313,px,py))
		{
			if(CdRectPoint3(77-45*((myself->selectMenu+1)%2),18+64*(myself->selectMenu),210-45*((myself->selectMenu+2)%2),50+36*(myself->selectMenu),px,py))

			{
				CatLoveDog_DoSelectMenu(myself->selectMenu);
			}			
			else
			{
				myself->selectMenu = (py-18)/53;
			}
		}
		*/
		if(CatLoveDogCdRectPoint(58,16,206,68,px,py))
		{
			if(myself->selectMenu != 0) myself->selectMenu=0;
			else if(myself->selectMenu == 0) CatLoveDog_DoSelectMenu(myself->selectMenu);
		}
		if(CatLoveDogCdRectPoint(35,81,167,128,px,py))
		{
			if(myself->selectMenu != 1) myself->selectMenu=1;
			else if(myself->selectMenu == 1) CatLoveDog_DoSelectMenu(myself->selectMenu);
		}
		if(CatLoveDogCdRectPoint(58,144,206,189,px,py))
		{
			if(myself->selectMenu != 2) myself->selectMenu=2;
			else if(myself->selectMenu == 2) CatLoveDog_DoSelectMenu(myself->selectMenu);
		}
		if(CatLoveDogCdRectPoint(35,203,167,250,px,py))
		{
			if(myself->selectMenu != 3) myself->selectMenu=3;
			else if(myself->selectMenu == 3) CatLoveDog_DoSelectMenu(myself->selectMenu);
		}
		if(CatLoveDogCdRectPoint(58,267,206,315,px,py))
		{
			if(myself->selectMenu != 4) myself->selectMenu=4;
			else if(myself->selectMenu == 4) CatLoveDog_DoSelectMenu(myself->selectMenu);
		}
	}
	#endif

}

void CatLoveDog_DoSelectMenu(gm_s16 id)
{
	switch(id)
		{
			case 0:
				level = 1;
				CatLoveDog_Screen_Next = &CatLoveDog_Screen_InGame;
				catLoveDogLoadingStep =0;
				catLoveDogLoadingStepTotal = 16;
				SCREEN_ChangeScreen(&CatLoveDog_Screen_Loading);
				break;
			case 1:
				level = 2;
				/*
				CatLoveDog_Screen_Next = &CatLoveDog_Screen_InGame;
				catLoveDogLoadingStep =0;
				catLoveDogLoadingStepTotal = 16;
				SCREEN_ChangeScreen(&CatLoveDog_Screen_Loading);
				*/
				CatLoveDogMonthPayCheck();
				break;
			case 2:
				/*
				level = 3;
				CatLoveDog_Screen_Next = &CatLoveDog_Screen_InGame;
				catLoveDogLoadingStep =0;
				catLoveDogLoadingStepTotal = 16;
				SCREEN_ChangeScreen(&CatLoveDog_Screen_Loading);
				*/
				CatLoveDogMonthPayCheck();
				break;
			case 3:
				CatLoveDog_Title_ChangeState(CatLoveDog_TITLE_STATE_HELP);
				break;
			case 4:
				GAME_ServiceExit();
				break;
		}
}


