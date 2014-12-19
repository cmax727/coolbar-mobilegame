#include "SameGame_CompleteMenu.h"
#include "SameGame_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif

void SameGame_CompleteMenu_Init(SameGameCompleteMenu * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=SameGame_CompleteMenu_Render;//��������
	myself->windows.UpdateCallBack=SameGame_CompleteMenu_Update;//��������
	myself->picLib=picLib;
	myself->selectnum = 0;

	SameGame_Loading_UpdateStep();
}

void SameGame_CompleteMenu_Render(void * param)//���������������
{
	SameGameCompleteMenu * myself=(SameGameCompleteMenu *)param;
	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(0, 146, 0));

	myself->picLib->DrawLine(myself->picLib,40,70,200,70,0xFFFFFF);
	myself->picLib->DrawLine(myself->picLib,40,110,200,110,0xFFFFFF);
	myself->picLib->DrawLine(myself->picLib,40,240,200,240,0xFFFFFF);
	myself->picLib->DrawLine(myself->picLib,40,70,40,240,0xFFFFFF);
	myself->picLib->DrawLine(myself->picLib,200,70,200,240,0xFFFFFF);

	myself->picLib->FillRect(myself->picLib,60,118+30*myself->selectnum,120,24,GAME_ToRGB(228, 36, 20));

	if (completeState == 2)
	{
		getManagerPtr()->DrawString("�ѩ`�ե�����",40,(SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("�ѩ`�ե�����"))/2,80,0xFFFFFF);
	}
	else
	{
		getManagerPtr()->DrawString("��ԑ�ޤ�",40,(SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("��ԑ�ޤ�"))/2,80,0xFFFFFF);
	}
	getManagerPtr()->DrawString("��Ҏ",40,(SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("��Ҏ"))/2,120,myself->selectnum==0?0x000000:0xFFFFFF);
	getManagerPtr()->DrawString("���ֱ��",40,(SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("���ֱ��"))/2,150,myself->selectnum==1?0x000000:0xFFFFFF);
	getManagerPtr()->DrawString("�ϥ�������",40,(SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("�ϥ�������"))/2,180,myself->selectnum==2?0x000000:0xFFFFFF);
	getManagerPtr()->DrawString("�����ȥ�ؑ���",40,(SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("�����ȥ�ؑ���"))/2,210,myself->selectnum==3?0x000000:0xFFFFFF);
}

void SameGame_CompleteMenu_Update(void * param)//�������水������
{
	SameGameCompleteMenu * myself=(SameGameCompleteMenu *)param;
	Rect ur;
	gm_s32 px,py,i,tempMenu=-1;
	gm_s16 selectMenutemp;
	ur.x=0;
	ur.y=0;
	ur.w=SCREEN_WIDTH;
	ur.h=SCREEN_HEIGHT;

	DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);
	if (extOldGameManager->IsKeyDown(MF_KEY_UP|MF_KEY_2))//���˵���ѡ��
	{
		myself->selectnum=(myself->selectnum+3)%4;
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);
	}
	else if(extOldGameManager->IsKeyDown(MF_KEY_8|MF_KEY_DOWN))//���˵���ѡ��
	{
		myself->selectnum=(myself->selectnum+1)%4;
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);
	}
	else if(extOldGameManager->IsKeyDown(MF_KEY_5|MF_KEY_MID|MF_KEY_LEFTSOFT))
	{
		tempMenu = myself->selectnum;
	}
	else if (SCREEN_IsPointerDown())
	{
		px = SCREEN_GetPointerX();
		py = SCREEN_GetPointerY();
		for(i=0;i<4;i++)
		{
			if (CdRectPoint(60,120+i*30,180,120+(i+1)*30,px,py))
			{
				if ( myself->selectnum == i)
				{
					tempMenu = i;
				}
				else
				{
					myself->selectnum = i;
				}
				break;
			}
		}
	}

	if (tempMenu == myself->selectnum)
	{
		if (myself->selectnum < 2)
		{
			newGame = myself->selectnum + 1;
			sameGame_Screen_Next = &sameGame_Screen_InGame;
			sameGameLoadingStep = 0;
			sameGameLoadingStepTotal = 16;
			completeState = 0;
			SCREEN_ChangeScreen(&sameGame_Screen_Loading);
		}
		else if (myself->selectnum == 2)
		{
			SameGame_Title_ChangeState(SAMEGAME_STATE_HIGSCORE);
		}
		else
		{
			SameGame_Title_ChangeState(SAMEGAME_STATE_TITLEMENU);
		}
	}
}

