#include "SameGame_ChangeChip.h"
#include "SameGame_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif

//初使化帮助界面中信息，加载图片和文字
void SameGame_ChangeChip_Init(SameGameChangeChip* myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=SameGame_ChangeChip_Render;//绘制区域
	myself->windows.UpdateCallBack=SameGame_ChangeChip_Update;//按键控制
	myself->picLib=picLib;

	SameGame_Loading_UpdateStep();
}

//绘制帮助中界面
void SameGame_ChangeChip_Render(void * param)
{
	SameGameChangeChip* myself=(SameGameChangeChip *)param;
	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(0, 146, 0));

	myself->picLib->DrawLine(myself->picLib,40,30,200,30,0xFFFFFF);
	myself->picLib->DrawLine(myself->picLib,40,70,200,70,0xFFFFFF);
	myself->picLib->DrawLine(myself->picLib,40,290,200,290,0xFFFFFF);
	myself->picLib->DrawLine(myself->picLib,40,30,40,290,0xFFFFFF);
	myself->picLib->DrawLine(myself->picLib,200,30,200,290,0xFFFFFF);

	myself->picLib->FillRect(myself->picLib,55,78+30*myself->selectMenu,130,24,GAME_ToRGB(228, 36, 20));

	getManagerPtr()->DrawString("コマメニュー",40,(SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("コマメニュー"))/2,40,0xFFFFFF);
	getManagerPtr()->DrawString("タイル",40,(SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("タイル"))/2,80,myself->selectMenu==0?0x000000:0xFFFFFF);
	getManagerPtr()->DrawString("玉",40,(SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("玉"))/2,110,myself->selectMenu==1?0x000000:0xFFFFFF);
	getManagerPtr()->DrawString("ボンバーマン１",40,(SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("ボンバーマン１"))/2,140,myself->selectMenu==2?0x000000:0xFFFFFF);
	getManagerPtr()->DrawString("ボンバーマン２",40,(SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("ボンバーマン２"))/2,170,myself->selectMenu==3?0x000000:0xFFFFFF);
	getManagerPtr()->DrawString("数字",40,(SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("数字"))/2,200,myself->selectMenu==4?0x000000:0xFFFFFF);
	getManagerPtr()->DrawString("図形",40,(SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("図形"))/2,230,myself->selectMenu==5?0x000000:0xFFFFFF);
	getManagerPtr()->DrawString("ウェッビー",40,(SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("ウェッビー"))/2,260,myself->selectMenu==6?0x000000:0xFFFFFF);
}

//按键操作帮助中界面
void SameGame_ChangeChip_Update(void * param)
{
	SameGameChangeChip * myself=(SameGameChangeChip *)param;
	Rect ur;
	gm_s32 px,py,i,tempMenu=-1;
	ur.x=0;
	ur.y=0;
	ur.w=SCREEN_WIDTH;
	ur.h=SCREEN_HEIGHT;

	DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);
	if (extOldGameManager->IsKeyDown(MF_KEY_UP|MF_KEY_2))//主菜单项选择
	{
		myself->selectMenu=(myself->selectMenu+6)%7;
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);
	}
	else if(extOldGameManager->IsKeyDown(MF_KEY_8|MF_KEY_DOWN))//主菜单项选择
	{
		myself->selectMenu=(myself->selectMenu+1)%7;
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);
	}
	else if (extOldGameManager->IsKeyDown(MF_KEY_5|MF_KEY_MID|MF_KEY_LEFTSOFT))
	{
		tempMenu = myself->selectMenu;
	}
	else if (SCREEN_IsPointerDown())
	{
		px = SCREEN_GetPointerX();
		py = SCREEN_GetPointerY();

		for(i=0;i<7;i++)
		{
			if (CdRectPoint(55,80+i*30,165,80+(i+1)*30,px,py))
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
		shape = myself->selectMenu;
		newGame = 0;
		sameGame_Screen_Next = &sameGame_Screen_InGame;
		sameGameLoadingStep = 0;
		sameGameLoadingStepTotal = 16;
		SCREEN_ChangeScreen(&sameGame_Screen_Loading);
	}
}
