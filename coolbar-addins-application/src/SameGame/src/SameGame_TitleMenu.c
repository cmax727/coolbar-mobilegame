#include "SameGame_TitleMenu.h"
#include "SameGame_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif

static Manager manager;
void SameGame_DoSelectMenu(gm_s16 id);

//������Ϸ�����˵���Դ
void SameGame_TitleMenu_Init(SameGameTitleMenu * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
	initManager(&manager);
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=SameGame_TitleMenu_Render;
	myself->windows.UpdateCallBack=SameGame_TitleMenu_Update;
 	myself->picLib=picLib;
	SameGame_Loading_UpdateStep();
	//


	
}

//��Ϸ���˵����ƽ���
void SameGame_TitleMenu_Render(void *param)
{
	SameGameTitleMenu * myself = (SameGameTitleMenu *)param;
	
	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(0, 146, 0));

	myself->picLib->DrawLine(myself->picLib,40,50,200,50,0xFFFFFF);
	myself->picLib->DrawLine(myself->picLib,40,90,200,90,0xFFFFFF);
	myself->picLib->DrawLine(myself->picLib,40,220,200,220,0xFFFFFF);
	myself->picLib->DrawLine(myself->picLib,40,50,40,220,0xFFFFFF);
	myself->picLib->DrawLine(myself->picLib,200,50,200,220,0xFFFFFF);

	myself->picLib->FillRect(myself->picLib,70,98+30*myself->selectMenu,95,24,GAME_ToRGB(228, 36, 20));

	getManagerPtr()->DrawString("�� ���᤬�� ��",40,(SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("�� ���᤬�� ��"))/2,60,0xFFFFFF);
	getManagerPtr()->DrawString("����",40,(SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("����"))/2,100,myself->selectMenu==0?0x000000:0xFFFFFF);
	getManagerPtr()->DrawString("�м�",40,(SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("�м�"))/2,130,myself->selectMenu==1?0x000000:0xFFFFFF);
	getManagerPtr()->DrawString("�ϼ�",40,(SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("�ϼ�"))/2,160,myself->selectMenu==2?0x000000:0xFFFFFF);
	getManagerPtr()->DrawString("�ϥ�������",40,(SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("�ϥ�������"))/2,190,myself->selectMenu==3?0x000000:0xFFFFFF);
	getManagerPtr()->DrawString("(C)HUDSON SOFT",80,(SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("(C)HUDSON SOFT"))/2,250,0xFFFFFF);

	getManagerPtr()->DrawString("�K��",40,SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("�K��"), SCREEN_HEIGHT-extVmLcdManager->VMGetStringHeight("�K��"),0xFFFF00);
}

//��Ϸ���˵��������ƽ���
int pxx = 0; 
void SameGame_TitleMenu_Update(void * param)
{
	
	SameGameTitleMenu * myself = (SameGameTitleMenu *)param;
	Rect ur;
	gm_s32 px,py,i,tempMenu=-1;
	char s[100];
	ur.x=0;
	ur.y=0;
	ur.w=SCREEN_WIDTH;
	ur.h=SCREEN_HEIGHT;
	
	
	
	DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);

// 	while(true){
// 		if(extOldGameManager->IsKeyDown(MF_KEY_UP|MF_KEY_2)){
// 			break;
// 			myself->selectMenu=(myself->selectMenu+3)%4;
// 			DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);
// 		}else
// 			extOldGameManager->(300);
// 	}

	if (extOldGameManager->IsKeyDown(MF_KEY_UP|MF_KEY_2))//���˵���ѡ��
	{
		myself->selectMenu=(myself->selectMenu+3)%4;
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);
	}
	else if (extOldGameManager->IsKeyDown(MF_KEY_8|MF_KEY_DOWN))//���˵���ѡ��
	{
		myself->selectMenu=(myself->selectMenu+1)%4;
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);
	}
	else if (extOldGameManager->IsKeyDown(MF_KEY_RIGHTSOFT))
	{
		GAME_ServiceExit();
	}
	else if (extOldGameManager->IsKeyDown(MF_KEY_5|MF_KEY_MID|MF_KEY_LEFTSOFT))
	{
		tempMenu = myself->selectMenu;
	}
	else if (SCREEN_IsPointerDown())
	{
		px = SCREEN_GetPointerX();
		py = SCREEN_GetPointerY();
		for(i=0;i<4;i++)
		{
			if (CdRectPoint(70,100+i*30,165,100+(i+1)*30,px,py))
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
		if (myself->selectMenu < 3)
		{
			level = myself->selectMenu;
			sameGame_Screen_Next = &sameGame_Screen_InGame;
			sameGameLoadingStep = 0;
			sameGameLoadingStepTotal = 16;
			newGame = 1;
			completeState = 0;
			SCREEN_ChangeScreen(&sameGame_Screen_Loading);
		}
		else
		{
			SameGame_Title_ChangeState(SAMEGAME_STATE_HIGSCORE);
		}
	}
}
