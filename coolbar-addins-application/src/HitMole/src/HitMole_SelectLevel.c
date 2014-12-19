#include "HitMole_SelectLevel.h"
#include "HitMole_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
static Manager manager;
extern void initSelectLevel(SelectLevel * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
	initManager(&manager);
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=HitMole_SelectLevel_Windows_Render;//绘制区域
	myself->windows.UpdateCallBack=HitMole_SelectLevel_windows_Update;//按键控制
	myself->picLib=picLib;
	myself->imgIcon = picLib->GetImage(picLib,"icon.gif");	
	myself->border = picLib->GetImage(picLib,"border.gif");
	myself->selectnum = 2;
	HitMole_Loading_UpdateStep();
}
void HitMole_SelectLevel_Windows_Render(void * param)//帮助界面绘制区域
{
	gm_u8 i;
	char buff[10];
	SelectLevel * myself=(SelectLevel *)param;
	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(102,51,0));
	myself->picLib->DrawImageEx(myself->picLib,myself->border,0,0,true,0);
	manager.DrawString("过关百分比",40,SCREEN_WIDTH/2-50,15,0xffff00);
	#ifdef GAME_240_320
	for(i=0;i<5;i++)
	{	
		sprintf((char*)buff,"%d",60+i*10);
		manager.DrawString(buff,40,SCREEN_WIDTH/2-10,70+i*50,0xffff00);
	}
	#endif
	#ifdef GAME_176_220
	for(i=0;i<5;i++)
	{	
		sprintf((char*)buff,"%d",60+i*10);
		manager.DrawString(buff,40,SCREEN_WIDTH/2-10,50+i*30,0xffff00);
	}
	#endif
	manager.DrawString("返回",40,TOUCH_X_RIGHT,TOUCH_Y_RIGHT,0xffff00);
}
void HitMole_SelectLevel_windows_Update(void * param)//帮助界面按键控制
{
	SelectLevel * myself=(SelectLevel *)param;
	gm_s32 px,py;
	if(myself->selectnum>=0 && myself->selectnum<=4)
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
			if(myself->selectnum == 5)
			{
				myself->selectnum = 4;
			}
		}
	}
	#ifdef GAME_240_320
		myself->picLib->FillRect(myself->picLib,10,40,50,270,GAME_ToRGB(102,51,0));
		myself->picLib->DrawImageEx(myself->picLib,myself->imgIcon,20,70+myself->selectnum*50,true,0);
		if(extOldGameManager->SCREEN_IsPointerDown())//触摸功能
		{
			px = SCREEN_GetPointerX();
			py = SCREEN_GetPointerY();
			if(MyCdRectPoint(100,70+50*(myself->selectnum),140,120+50*(myself->selectnum),px,py))	
			{
				gamestage = 2;
				percent = 60+myself->selectnum*10;
				level = 1;
				HitMole_Screen_Next = &HitMole_Screen_InGame;
				hitMoleLoadingStep = 0;
				hitMoleLoadingStepTotal = 16;
				SCREEN_ChangeScreen(&HitMole_Screen_Loading);
			}else if(py>70 && py<320 && px>100 && px<140)
			{
				myself->selectnum = (py-70)/50;
			}
			if(MyCdRectPoint(TOUCH_X_RIGHT,TOUCH_Y_RIGHT,TOUCH_X1_RIGHT,TOUCH_Y1_RIGHT,px,py))
				{
					HitMole_Title_ChangeState(HITMOLE_TITLE_STATE_MENU);
				}
		}
	#endif
	#ifdef GAME_176_220
		myself->picLib->FillRect(myself->picLib,6,40,30,160,GAME_ToRGB(102,51,0));
		myself->picLib->DrawImageEx(myself->picLib,myself->imgIcon,10,50+myself->selectnum*30,true,0);
	#endif
	if(getManagerPtr()->IsKeyDown(MF_KEY_MID))
	{
		gamestage = 2;
		percent = 60+myself->selectnum*10;
		level = 1;
		HitMole_Screen_Next = &HitMole_Screen_InGame;
		hitMoleLoadingStep = 0;
		hitMoleLoadingStepTotal = 16;
		SCREEN_ChangeScreen(&HitMole_Screen_Loading);
	}
	if(getManagerPtr()->IsKeyDown(MF_KEY_RIGHTSOFT))
	{
		HitMole_Title_ChangeState(HITMOLE_TITLE_STATE_MENU);
	}
}

