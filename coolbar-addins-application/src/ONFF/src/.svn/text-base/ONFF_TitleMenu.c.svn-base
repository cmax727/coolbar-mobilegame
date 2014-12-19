#include "ONFF_TitleMenu.h"
#include "ONFF_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif

static Manager manager;
void ONFF_DoSelectMenu(gm_s16 id);

void initONFFTitleMenu(ONFFTitleMenu * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
	initManager(&manager);
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=ONFF_TitleMenu_Render;
	myself->windows.UpdateCallBack=ONFF_TitleMenu_Update;
	ONFF_Loading_UpdateStep();
	myself->picLib=picLib;
	myself->imgTitleMenu[0]=picLib->GetImage(picLib,"Menu_map.gif");
	ONFF_Loading_UpdateStep();
	myself->imgTitleMenu[1]=picLib->GetImage(picLib,"Menu_bar.gif");
	ONFF_Loading_UpdateStep();
	myself->selectMenu=0;
}

void ONFF_DrawMiddleString(gm_u8 * str,gm_s32 x,gm_s32 y,gm_u32 color)
{
	gm_s32 width = (gm_s32)extVmLcdManager->VMGetStringWidth((char*)str);
	gm_s32 height = (gm_s32)extVmLcdManager->VMGetStringHeight((char*)str);
	width = width>>1;
	height = height>>1;
	extVmGameLcdManager->DrawString((char*)str,strlen(str),x-width,y-height,color);
}

void ONFFMonthPayCheck(void)
{
	if(extVmBillingManager->BILLING_GetRemainDay(NETAPP_APP_ONFF,NETAPP_BILLING_METHOD_ONCE_MONTH) == 0)
	{	
		
		ONFF_Title_ChangeState(ONFF_TITLE_STATE_PAY);
		
	}else
	{		
		ONFF_Screen_Next = &ONFF_Screen_InGame;
		oNFFLoadingStep = 0;
		oNFFLoadingStepTotal = 16;
		SCREEN_ChangeScreen(&ONFF_Screen_Loading);
	}
}

void ONFF_TitleMenu_Render(void *param)
{
	ONFFTitleMenu * myself = (ONFFTitleMenu *)param;
	
	manager.DrawFullScreen(myself->picLib->image[myself->imgTitleMenu[0]]);
	
#ifdef GAME_240_320                  
	myself->picLib->DrawRegionEx(myself->picLib,myself->imgTitleMenu[1],105,156+30*(myself->selectMenu),(myself->selectMenu)*92,0,92,30,true,0);
#endif
#ifdef	GAME_176_220
	myself->picLib->DrawRegionEx(myself->picLib,myself->imgTitleMenu[1],78,109+20*(myself->selectMenu),(myself->selectMenu)*67.4,0,67.4,20,true,0);
#endif
}

void ONFF_TitleMenu_Update(void * param)
{
	ONFFTitleMenu * myself = (ONFFTitleMenu *)param;
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
		ONFF_DoSelectMenu(myself->selectMenu);
	}
	#ifdef GAME_240_320
	if(extOldGameManager->SCREEN_IsPointerDown())
	{
		px = SCREEN_GetPointerX();
		py = SCREEN_GetPointerY();
		if(CdRectPoint3(105,156,197,306,px,py))
		{
			if(CdRectPoint3(105,156+30*(myself->selectMenu),197,186+30*(myself->selectMenu),px,py))

			{
				ONFF_DoSelectMenu(myself->selectMenu);
			}			
			else
			{
				myself->selectMenu = (py-156)/30;
			}
		}
	}
	#endif

}

void ONFF_DoSelectMenu(gm_s16 id)
{
	switch(id)
		{
			case 0:
				ONFFMonthPayCheck();
				//ONFF_Screen_Next = &ONFF_Screen_InGame;
				//oNFFLoadingStep = 0;
				//oNFFLoadingStepTotal = 16;
				//SCREEN_ChangeScreen(&ONFF_Screen_Loading);
				break;
			case 1:
				ONFF_Title_ChangeState(ONFF_TITLE_STATE_SET);
				break;
			case 2:
				ONFF_Title_ChangeState(ONFF_TITLE_STATE_HELP);
				break;
			case 3:
				ONFF_Title_ChangeState(ONFF_TITLE_STATE_ABOUT);
				break;
			case 4:
				GAME_ServiceExit();
				break;
		}
}


