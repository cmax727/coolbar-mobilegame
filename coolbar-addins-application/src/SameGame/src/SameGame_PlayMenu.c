#include "SameGame_PlayMenu.h"
#include "SameGame_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif

//初使化帮助界面中信息，加载图片和文字
void SameGame_PlayMenu_Init(SameGamePlayMenu * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=SameGame_PlayMenu_Render;//绘制区域
	myself->windows.UpdateCallBack=SameGame_PlayMenu_Update;//按键控制
	myself->picLib=picLib;
	myself->selectMenu = 0;

	SameGame_Loading_UpdateStep();
}

//绘制帮助中界面
void SameGame_PlayMenu_Render(void * param)
{
	SameGamePlayMenu * myself=(SameGamePlayMenu *)param;
	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(0, 146, 0));

	myself->picLib->DrawLine(myself->picLib,40,50,200,50,0xFFFFFF);
	myself->picLib->DrawLine(myself->picLib,40,90,200,90,0xFFFFFF);
	myself->picLib->DrawLine(myself->picLib,40,280,200,280,0xFFFFFF);
	myself->picLib->DrawLine(myself->picLib,40,50,40,280,0xFFFFFF);
	myself->picLib->DrawLine(myself->picLib,200,50,200,280,0xFFFFFF);

	myself->picLib->FillRect(myself->picLib,68,98+30*myself->selectMenu,110,24,GAME_ToRGB(228, 36, 20));
	
	getManagerPtr()->DrawString("メニュー",40,(SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("メニュー"))/2,60,0xFFFFFF);
	getManagerPtr()->DrawString("新規",40,(SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("新規"))/2,100,myself->selectMenu==0?0x000000:0xFFFFFF);
	getManagerPtr()->DrawString("やり直し",40,(SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("やり直し"))/2,130,myself->selectMenu==1?0x000000:0xFFFFFF);
	getManagerPtr()->DrawString("パターン変更",40,(SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("パターン変更"))/2,160,myself->selectMenu==2?0x000000:0xFFFFFF);
	getManagerPtr()->DrawString("タイトルへ戻る",40,(SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("タイトルへ戻る"))/2,190,myself->selectMenu==3?0x000000:0xFFFFFF);
	getManagerPtr()->DrawString("ゲーム終了",40,(SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("ゲーム終了"))/2,220,myself->selectMenu==4?0x000000:0xFFFFFF);
	getManagerPtr()->DrawString("キャンセル",40,(SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("キャンセル"))/2,250,myself->selectMenu==5?0x000000:0xFFFFFF);
}

//按键操作帮助中界面
void SameGame_PlayMenu_Update(void * param)
{
	SameGamePlayMenu * myself=(SameGamePlayMenu *)param;
	Rect ur;
	gm_s32 px,py,i,tempMenu=-1;
	gm_s16 selectMenutemp;
	ur.x=0;
	ur.y=0;
	ur.w=SCREEN_WIDTH;
	ur.h=SCREEN_HEIGHT;
	
	DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);
	if (extOldGameManager->IsKeyDown(MF_KEY_UP|MF_KEY_2))//主菜单项选择
	{
		myself->selectMenu=(myself->selectMenu+5)%6;
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);
	}
	else if(extOldGameManager->IsKeyDown(MF_KEY_8|MF_KEY_DOWN))//主菜单项选择
	{
		myself->selectMenu=(myself->selectMenu+1)%6;
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);
	}
	else if(extOldGameManager->IsKeyDown(MF_KEY_5|MF_KEY_MID|MF_KEY_LEFTSOFT))
	{
		tempMenu = myself->selectMenu;
	}
	else if (SCREEN_IsPointerDown())
	{
		px = SCREEN_GetPointerX();
		py = SCREEN_GetPointerY();
		for(i=0;i<6;i++)
		{
			if (CdRectPoint(70,100+i*30,180,100+(i+1)*30,px,py))
			{
				if ( myself->selectMenu == i)
				{
					tempMenu = i;
				}
				else
				{
					myself->selectMenu = i;
				}
				break;
			}
		}
	}

	if (tempMenu == myself->selectMenu)
	{
		switch(myself->selectMenu)
		{
		case 0:
			newGame = 1;
			break;
		case 1:
			newGame = 2;
			break;
		case 2:
			SameGame_Title_ChangeState(SAMEGAME_STATE_CHANGECHIP);
			return;
		case 3:
			SameGame_Title_ChangeState(SAMEGAME_STATE_TITLEMENU);
			return;
		case 4:
			GAME_ServiceExit();
			return;
		case 5:
			newGame = 0;
			break;
		}

		sameGame_Screen_Next = &sameGame_Screen_InGame;
		sameGameLoadingStep = 0;
		sameGameLoadingStepTotal = 16;
		SCREEN_ChangeScreen(&sameGame_Screen_Loading);
	}
}

