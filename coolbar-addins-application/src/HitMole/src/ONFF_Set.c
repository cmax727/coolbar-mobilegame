#include "ONFF_Set.h" 
#include "ONFF_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
char * temp0;
void initONFFSet(ONFFSet * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=ONFF_Set_Render;
	myself->windows.UpdateCallBack=ONFF_Set_Update;
	myself->picLib = picLib;
	myself->imgGB = picLib->GetImage(picLib,"guangbiao.gif");
	myself->border = picLib->GetImage(picLib,"border.gif");
	ONFF_Loading_UpdateStep();

	myself->gamest.gameplayerlife = gamePlayerlife;
	myself->gamest.gameplayerbomb = gamePlayerbomb;
	myself->chose = 0;
}

void Set_Render(ONFFSet * myself)
{
	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(36,19,121));
	myself->picLib->DrawImageEx(myself->picLib,myself->border,0,0,true,0);
	extOldGameManager->DrawString("设置",25,SCREEN_WIDTH/2-20,10,0xffff00);
	#ifdef GAME_240_320
		extOldGameManager->DrawString("设置",25,SCREEN_WIDTH/2-20,15,0xffff00);
		extOldGameManager->DrawString("玩家生命:",20,30,70,0xffff00);
		temp0=manager_my->formatString("%d", myself->gamest.gameplayerlife);
		extOldGameManager->DrawString(temp0,20,170,70,0xffff00);
		extOldGameManager->DrawString("玩家雷数:",20,30,120,0xffff00);
		temp0=manager_my->formatString("%d", myself->gamest.gameplayerbomb);
		extOldGameManager->DrawString(temp0,20,170,120,0xffff00);
		switch(myself->chose)
		{
			case 0:
				myself->picLib->DrawRegionEx(myself->picLib,myself->imgGB,140,70,0,0,35,20,true,0);
				myself->picLib->DrawRegionEx(myself->picLib,myself->imgGB,175,70,35,0,35,20,true,0);
				break;
			case 1:
				myself->picLib->DrawRegionEx(myself->picLib,myself->imgGB,140,120,0,0,35,20,true,0);
				myself->picLib->DrawRegionEx(myself->picLib,myself->imgGB,175,120,35,0,35,20,true,0);
				break;
		}
	#endif
	#ifdef GAME_176_220
		extOldGameManager->DrawString("设置",25,SCREEN_WIDTH/2-20,10,0xffff00);
		extOldGameManager->DrawString("玩家生命:",20,15,70,0xffff00);
		temp0=manager_my->formatString("%d",myself->gamest.gameplayerlife);
		extOldGameManager->DrawString(temp0,20,130,70,0xffff00);
		extOldGameManager->DrawString("玩家雷数:",20,15,120,0xffff00);
		temp0=manager_my->formatString("%d", myself->gamest.gameplayerbomb);
		extOldGameManager->DrawString(temp0,20,130,120,0xffff00);
		switch(myself->chose)
		{
			case 0:
				myself->picLib->DrawRegionEx(myself->picLib,myself->imgGB,110,70,0,0,35,20,true,0);
				myself->picLib->DrawRegionEx(myself->picLib,myself->imgGB,125,70,35,0,35,20,true,0);
				break;
			case 1:
				myself->picLib->DrawRegionEx(myself->picLib,myself->imgGB,110,120,0,0,35,20,true,0);
				myself->picLib->DrawRegionEx(myself->picLib,myself->imgGB,125,120,35,0,35,20,true,0);
				break;
		}
	#endif
	extOldGameManager->DrawString("确定",25,TOUCH_X_RIGHT-10,TOUCH_Y_RIGHT,0xffff00);
}
void ONFF_Set_Render(void * param)
{
	ONFFSet *myself = (ONFFSet *)param;
	Set_Render(myself);
}

gm_bool CdRectPoint3(gm_s16 x,gm_s16 y,gm_s16 x1,gm_s16 y1,gm_s16 px,gm_s16 py)
{
	if(px>=x && px<=x1 && py>=y && py<=y1)
	{
		return true;
	}else
		return false;
}
void ONFF_Set_Update(void * param)
{
	gm_s16 px,py;
	ONFFSet *myself = (ONFFSet *)param;
	Set_Render(myself);
	if (extOldGameManager->IsKeyDown(MF_KEY_RIGHTSOFT))
	{
		gamePlayerlife = myself->gamest.gameplayerlife;
		gamePlayerbomb = myself->gamest.gameplayerbomb;
		ONFF_Title_ChangeState(ONFF_TITLE_STATE_MENU);
	}
	if(extOldGameManager->IsKeyDown(MF_KEY_UP | MF_KEY_2))
	{
		if(myself->chose <= 0)
		{
			myself->chose = 1;
		}
		else
		{
			myself->chose--;
		}
	}
	if(extOldGameManager->IsKeyDown(MF_KEY_DOWN | MF_KEY_8))
	{
		if(myself->chose >= 1)
		{
			myself->chose = 0;
		}
		else
		{
			myself->chose++;
		}
	}
	if(extOldGameManager->IsKeyDown(MF_KEY_LEFT | MF_KEY_4))
	{
		 if(myself->chose == 0)
	 	{
	 		if(myself->gamest.gameplayerlife>=4)
	 		{
	 			myself->gamest.gameplayerlife -= 2;
	 		}
	 	}
		 if(myself->chose == 1)
	 	{
	 		if(myself->gamest.gameplayerbomb>=2)
	 		{
	 			myself->gamest.gameplayerbomb--;
	 		}
	 	}
		 
	}
	if(extOldGameManager->IsKeyDown(MF_KEY_RIGHT | MF_KEY_6))
	{
		if(myself->chose == 0)
	 	{
	 		if(myself->gamest.gameplayerlife<=4)
	 		{
	 			myself->gamest.gameplayerlife += 2;
	 		}
	 	}
		 if(myself->chose == 1)
	 	{
	 		if(myself->gamest.gameplayerbomb<=2)
	 		{
	 			myself->gamest.gameplayerbomb++;
	 		}
	 	}
	}
	if(SCREEN_IsPointerDown())
	{
		px = SCREEN_GetPointerX();
		py = SCREEN_GetPointerY();
	#ifdef GAME_240_320
		if(CdRectPoint3(TOUCH_X_RIGHT,TOUCH_Y_RIGHT,TOUCH_X1_RIGHT,TOUCH_Y1_RIGHT,px,py))
	#endif
		{
			gamePlayerlife = myself->gamest.gameplayerlife;
			gamePlayerbomb = myself->gamest.gameplayerbomb;
			ONFF_Title_ChangeState(ONFF_TITLE_STATE_MENU);		
		}
	}
}	