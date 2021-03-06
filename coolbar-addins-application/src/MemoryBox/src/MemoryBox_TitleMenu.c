#include "MemoryBox_TitleMenu.h"
#include "MemoryBox_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif

static Manager manager;
void MemoryBox_DoSelectMenu(gm_s16 id);

//加载游戏中主菜单资源
void initMemoryBoxTitleMenu(MemoryBoxTitleMenu * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
	initManager(&manager);
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=MemoryBox_TitleMenu_Render;
	myself->windows.UpdateCallBack=MemoryBox_TitleMenu_Update;
	MemoryBox_Loading_UpdateStep();
	myself->picLib=picLib;
	myself->imgTitleMenu[0]=picLib->GetImage(picLib,"beijing.gif");
	MemoryBox_Loading_UpdateStep();
	myself->imgTitleMenu[1]=picLib->GetImage(picLib,"icon.gif");
	MemoryBox_Loading_UpdateStep();
	myself->selectMenu=0;
	MemoryBox_Loading_UpdateStep();
}

gm_bool MBCdRectPoint(gm_s16 x,gm_s16 y,gm_s16 x1,gm_s16 y1,gm_s16 px,gm_s16 py)
{
	if(px>=x && px<=x1 && py>=y && py<=y1)
	{
		return true;
	}else
		return false;
}
//游戏主菜单绘制界面
void MemoryBox_TitleMenu_Render(void *param)
{
	MemoryBoxTitleMenu * myself = (MemoryBoxTitleMenu *)param;
	
	manager.DrawFullScreen(myself->picLib->image[myself->imgTitleMenu[0]]);
	
#ifdef GAME_240_320                  
	myself->picLib->DrawImageEx(myself->picLib,myself->imgTitleMenu[1],35,108+30*(myself->selectMenu),true,0);
#endif
#ifdef	GAME_176_220
	myself->picLib->DrawImageEx(myself->picLib,myself->imgTitleMenu[1],53,41+25*(myself->selectMenu),(myself->selectMenu)*68,0,68,20,true,0);
#endif
}

//游戏主菜单按键控制界面
void MemoryBox_TitleMenu_Update(void * param)
{

	MemoryBoxTitleMenu * myself = (MemoryBoxTitleMenu *)param;
	Rect ur;
	gm_s32 px,py;
	gm_s16 selectMenutemp;
	#ifdef GAME_240_320
	ur.x=30;
	ur.y=95;
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
if (extOldGameManager->IsKeyDown(MF_KEY_UP|MF_KEY_2))//主菜单项选择
	{
		myself->selectMenu--;
		myself->selectMenu+=5;
		myself->selectMenu=(myself->selectMenu+1)%6;
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);
	}
	else if(extOldGameManager->IsKeyDown(MF_KEY_8|MF_KEY_DOWN))//主菜单项选择
	{
		myself->selectMenu++;
		myself->selectMenu+=5;
		myself->selectMenu=(myself->selectMenu+1)%6;
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);
	}
	
	if(extOldGameManager->IsKeyDown(MF_KEY_5|MF_KEY_MID|MF_KEY_LEFTSOFT))
	{
		MemoryBox_DoSelectMenu(myself->selectMenu);
	}
	
	#ifdef GAME_240_320
	if(extOldGameManager->SCREEN_IsPointerDown())
	{
		px = SCREEN_GetPointerX();
		py = SCREEN_GetPointerY();
		if(MBCdRectPoint(90,108,150,283,px,py) && MBCdRectPoint(90,108+29*(myself->selectMenu),150,134+29*(myself->selectMenu),px,py))
		{	
				MemoryBox_DoSelectMenu(myself->selectMenu);			
		}else if(MBCdRectPoint(90,108,150,283,px,py) && !MBCdRectPoint(90,108+29*(myself->selectMenu),150,134+29*(myself->selectMenu),px,py))
		{
			myself->selectMenu = (py-108)/29;
		}
	}
	#endif
	
}

//选定主菜单后功能
void MemoryBox_DoSelectMenu(gm_s16 id)
{
	switch(id)
		{
			case 0:
				gamestage = 1;
				level = 1;
				if(extVmBillingManager->BILLING_GetRemainDay(NETAPP_APP_MEMORYBOX,NETAPP_BILLING_METHOD_ONCE_MONTH) == 0)
				{			
					MemoryBox_Title_ChangeState(MEMORYBOX_TITLE_STATE_PAY);	
				}
				else
				{		
					MemoryBox_Screen_Next = &MemoryBox_Screen_InGame;
					memoryBoxLoadingStep = 0;
					memoryBoxLoadingStepTotal = 16;
					SCREEN_ChangeScreen(&MemoryBox_Screen_Loading);
				}
				break;
			case 1:
				MemoryBox_Title_ChangeState(MEMORYBOX_TITLE_STATE_EXERSICE);
				break;
			case 2:
				MemoryBox_Title_ChangeState(MEMORYBOX_TITLE_STATE_HELP);
				break;
			case 3:
				MemoryBox_Title_ChangeState(MEMORYBOX_TITLE_STATE_ABOUT);
				break;
			case 4:
				MemoryBox_Title_ChangeState(MEMORYBOX_TITLE_STATE_HIGSCORE);
				break;
			case 5:
				GAME_ServiceExit();
				break;
		}
}

