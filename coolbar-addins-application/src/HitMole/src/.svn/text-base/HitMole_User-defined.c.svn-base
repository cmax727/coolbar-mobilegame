#include "HitMole_User-defined.h"
#include "HitMole_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
static Manager manager;
extern void initUserDefine(UserDefine * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
	initManager(&manager);
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=HitMole_UserDefine_Windows_Render;//绘制区域
	myself->windows.UpdateCallBack=HitMole_UserDefine_windows_Update;//按键控制
	myself->picLib=picLib;
	myself->imgIcon = picLib->GetImage(picLib,"icon.gif");
	myself->border = picLib->GetImage(picLib,"border.gif");
	myself->selectnum = 4;
	HitMole_Loading_UpdateStep();
}
void HitMole_UserDefine_Windows_Render(void * param)//帮助界面绘制区域
{
	gm_u8 i;
	char buff[10];
	UserDefine * myself=(UserDefine *)param;
	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(102,51,0));
	myself->picLib->DrawImageEx(myself->picLib,myself->border,0,0,true,0);
	manager.DrawString("请选择难度",40,SCREEN_WIDTH/2-50,15,0xffff00);
	
#ifdef GAME_240_320
		for(i=0;i<9;i++)
		{	
			sprintf((char*)buff,"%d",1+i);
			manager.DrawString(buff,40,SCREEN_WIDTH/2-10,40+i*30,0xffff00);
		}
	#endif
	#ifdef GAME_176_220
		for(i=0;i<9;i++)
		{	
			sprintf((char*)buff,"%d",1+i);
			manager.DrawString(buff,40,SCREEN_WIDTH/2-10,30+i*20,0xffff00);
		}
	#endif
	manager.DrawString("返回",40,TOUCH_X_RIGHT,TOUCH_Y_RIGHT,0xffff00);
}
void HitMole_UserDefine_windows_Update(void * param)//帮助界面按键控制
{
	UserDefine * myself=(UserDefine *)param;
	gm_s32 px,py;
	if(myself->selectnum>=0 && myself->selectnum<=8)
	{
		if(getManagerPtr()->IsKeyDown(MF_KEY_UP | MF_KEY_2))
		{
			myself->selectnum--;
			if(myself->selectnum == -1)
			{
				myself->selectnum = 0;
			}
		}
		if(getManagerPtr()->IsKeyDown(MF_KEY_DOWN | MF_KEY_8))
		{
			myself->selectnum++;
			if(myself->selectnum == 9)
			{
				myself->selectnum = 8;
			}
		}
	}
	#ifdef GAME_240_320
		myself->picLib->FillRect(myself->picLib,10,40,50,270,GAME_ToRGB(102,51,0));
		myself->picLib->DrawImageEx(myself->picLib,myself->imgIcon,20,40+myself->selectnum*30,true,0);
		if(extOldGameManager->SCREEN_IsPointerDown())//触摸功能
		{
			px = SCREEN_GetPointerX();
			py = SCREEN_GetPointerY();
				if(MyCdRectPoint(100,40+30*(myself->selectnum),130,70+30*(myself->selectnum),px,py))	
				{
					gamestage = 4;
					level = 1+myself->selectnum;
					
					if(extVmBillingManager->BILLING_GetRemainDay(NETAPP_APP_HITMOLE,NETAPP_BILLING_METHOD_ONCE_MONTH) == 0 && level > 1)
					{
						HitMole_Title_ChangeState(HITMOLE_TITLE_STATE_PAY);
					}
					else
					{
						HitMole_Screen_Next = &HitMole_Screen_InGame;
						hitMoleLoadingStep = 0;
						hitMoleLoadingStepTotal = 16;
						SCREEN_ChangeScreen(&HitMole_Screen_Loading);
					}
				}			
				else if(py>40 && py<320 && px>100 && px<130)
				{
					myself->selectnum = (py-40)/30;
				}
				if(MyCdRectPoint(TOUCH_X_RIGHT,TOUCH_Y_RIGHT,TOUCH_X1_RIGHT,TOUCH_Y1_RIGHT,px,py))
				{
					HitMole_Title_ChangeState(HITMOLE_TITLE_STATE_MENU);
				}
	}
	#endif
	#ifdef GAME_176_220
		myself->picLib->FillRect(myself->picLib,6,20,30,200,GAME_ToRGB(102,51,0));
		myself->picLib->DrawImageEx(myself->picLib,myself->imgIcon,10,30+myself->selectnum*20,true,0);
	#endif
/*
	if(getManagerPtr()->IsKeyDown(MF_KEY_0))
	{
		myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(102,51,0));
		sprintf((char*)time,"%d-%d-%d",getManagerPtr()->MF_GetBlackYear(),getManagerPtr()->MF_GetBlackMonth(),getManagerPtr()->MF_GetBlackDay());
		manager.DrawString(time,40,0,0,0xffff00);
	}
*/
	if(getManagerPtr()->IsKeyDown(MF_KEY_MID))
	{
		gamestage = 4;
		level = 1+myself->selectnum;
		
		if(extVmBillingManager->BILLING_GetRemainDay(NETAPP_APP_HITMOLE,NETAPP_BILLING_METHOD_ONCE_MONTH) == 0 && level > 1)
		{
			HitMole_Title_ChangeState(HITMOLE_TITLE_STATE_PAY);
		}
		else
		{
			HitMole_Screen_Next = &HitMole_Screen_InGame;
			hitMoleLoadingStep = 0;
			hitMoleLoadingStepTotal = 16;
			SCREEN_ChangeScreen(&HitMole_Screen_Loading);
		}
	}
	if(getManagerPtr()->IsKeyDown(MF_KEY_RIGHTSOFT))
	{
		HitMole_Title_ChangeState(HITMOLE_TITLE_STATE_MENU);
	}
}


