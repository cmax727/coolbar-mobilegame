#include "HitMole_TitleMenu.h"
#include "HitMole_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif

static Manager manager;
void HitMole_DoSelectMenu(gm_s16 id);

//加载游戏中主菜单资源
void initHitMoleTitleMenu(HitMoleTitleMenu * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
	initManager(&manager);
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=HitMole_TitleMenu_Render;
	myself->windows.UpdateCallBack=HitMole_TitleMenu_Update;
	HitMole_Loading_UpdateStep();
	myself->picLib=picLib;
	myself->imgTitleMenu[0]=picLib->GetImage(picLib,"beijing0.gif");
	HitMole_Loading_UpdateStep();
	myself->imgTitleMenu[1]=picLib->GetImage(picLib,"biaoti.gif");
	HitMole_Loading_UpdateStep();
	myself->selectMenu=0;
	HitMole_Loading_UpdateStep();
}

gm_bool MyCdRectPoint(gm_s16 x,gm_s16 y,gm_s16 x1,gm_s16 y1,gm_s16 px,gm_s16 py)
{
	if(px>=x && px<=x1 && py>=y && py<=y1)
	{
		return true;
	}else
		return false;
}
//游戏主菜单绘制界面
void HitMole_TitleMenu_Render(void *param)
{
	HitMoleTitleMenu * myself = (HitMoleTitleMenu *)param;
	
	manager.DrawFullScreen(myself->picLib->image[myself->imgTitleMenu[0]]);
	
#ifdef GAME_240_320                  
	myself->picLib->DrawRegionEx(myself->picLib,myself->imgTitleMenu[1],72,60+36*(myself->selectMenu),(myself->selectMenu)*93,0,93,30,true,0);
#endif
#ifdef	GAME_176_220
	myself->picLib->DrawRegionEx(myself->picLib,myself->imgTitleMenu[1],53,41+25*(myself->selectMenu),(myself->selectMenu)*68,0,68,20,true,0);
#endif
}

//游戏主菜单按键控制界面
void HitMole_TitleMenu_Update(void * param)
{
	HitMoleTitleMenu * myself = (HitMoleTitleMenu *)param;
	Rect ur;
	gm_s32 px,py;
	gm_s16 selectMenutemp;
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
		HitMole_DoSelectMenu(myself->selectMenu);
	}
	#ifdef GAME_240_320
	if(extOldGameManager->SCREEN_IsPointerDown())//触摸功能
	{
		px = SCREEN_GetPointerX();
		py = SCREEN_GetPointerY();
				if(MyCdRectPoint(72,60+36*(myself->selectMenu),165,85+36*(myself->selectMenu),px,py))
	
				{
					HitMole_DoSelectMenu(myself->selectMenu);
				}			
				else if(py>50 && py<275 && px>70 && px<165)
				{
					selectMenutemp = (py-60)/36;
					if(!MyCdRectPoint(72,85+36*selectMenutemp,165,95+36*selectMenutemp,px,py))
						myself->selectMenu = selectMenutemp;
				}
	}
	#endif

}

//选定主菜单后功能
void HitMole_DoSelectMenu(gm_s16 id)
{
	switch(id)
		{
			case 0:
				if(extVmBillingManager->BILLING_GetRemainDay(NETAPP_APP_HITMOLE,NETAPP_BILLING_METHOD_ONCE_MONTH) == 0)
				{			
					HitMole_Title_ChangeState(HITMOLE_TITLE_STATE_PAY);
				}
				else
				{		
					HitMole_Title_ChangeState(HITMOLE_TITLE_STATE_SELECT);
				}
				break;
			case 1:
				HitMole_Title_ChangeState(HITMOLE_TITLE_STATE_USERSET);
				break;
			case 2:
				HitMole_Title_ChangeState(HITMOLE_TITLE_STATE_HELP);
				break;
			case 3:
				HitMole_Title_ChangeState(HITMOLE_TITLE_STATE_ABOUT);
				break;
			case 4:
				HitMole_Title_ChangeState(HITMOLE_TITLE_STATE_HIGSCORE);
				break;
			case 5:
				GAME_ServiceExit();
				break;
		}
}

