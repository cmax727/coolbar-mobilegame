#include "MemoryBox_Exersice.h"
#include "MemoryBox_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
static Manager manager;
extern void initMemoryBoxExersice(MemoryBoxExersice * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
	initManager(&manager);
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=MemoryBox_Exersice_Windows_Render;//绘制区域
	myself->windows.UpdateCallBack=MemoryBox_Exersice_Windows_Update;//按键控制
	myself->picLib=picLib;
	myself->imgIcon = picLib->GetImage(picLib,"icon.gif");
	myself->selectnum = 4;
	myself->imgback = picLib->GetImage(picLib,"bei.gif");
	MemoryBox_Loading_UpdateStep();
}
void MemoryBox_Exersice_Windows_Render(void * param)//帮助界面绘制区域
{
	gm_u8 i;
	char buff[10];
	MemoryBoxExersice * myself=(MemoryBoxExersice *)param;
	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(102,51,0));
	myself->picLib->DrawImageEx(myself->picLib,myself->imgback,0,0,true,0);
	manager.DrawString("请选择难度",40,SCREEN_WIDTH/2-50,10,0xffff00);
	
#ifdef GAME_240_320
		for(i=0;i<9;i++)
		{	
			sprintf((char*)buff,"%d",1+i);
			manager.DrawString(buff,40,SCREEN_WIDTH/2-10,50+i*24,0xffff00);
		}
	#endif
	#ifdef GAME_176_220
		for(i=0;i<9;i++)
		{	
			sprintf((char*)buff,"%d",1+i);
			manager.DrawString(buff,40,SCREEN_WIDTH/2-10,30+i*20,0xffff00);
		}
	#endif
	manager.DrawString("确定",40,TOUCH_X_LEFT,TOUCH_Y_LEFT,0xffff00);
	manager.DrawString("返回",40,TOUCH_X_RIGHT-10,TOUCH_Y_RIGHT,0xffff00);
}
void MemoryBox_Exersice_Windows_Update(void * param)//帮助界面按键控制
{
	gm_s32 px,py;
	MemoryBoxExersice * myself=(MemoryBoxExersice *)param;
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
		myself->picLib->FillRect(myself->picLib,20,50,50,230,GAME_ToRGB(102,51,0));
		myself->picLib->DrawImageEx(myself->picLib,myself->imgIcon,20,25+(myself->selectnum+1)*25,true,0);
		if(extOldGameManager->SCREEN_IsPointerDown())//触摸功能
		{
			px = SCREEN_GetPointerX();
			py = SCREEN_GetPointerY();
			if(MBCdRectPoint(20, 50+24*(myself->selectnum),210,74+24*(myself->selectnum),px,py))	
			{
				gamestage = 5;
				level = 1+myself->selectnum;
				if(level > 1)
				{
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
				}
				else
				{
					MemoryBox_Screen_Next = &MemoryBox_Screen_InGame;
					memoryBoxLoadingStep = 0;
					memoryBoxLoadingStepTotal = 16;
					SCREEN_ChangeScreen(&MemoryBox_Screen_Loading);
				}
			}else if(py>50 && py<270 && px>20 && px<210)
			{
				myself->selectnum = (py-50)/24;
			}
			if(MBCdRectPoint(TOUCH_X_RIGHT,TOUCH_Y_RIGHT,TOUCH_X1_RIGHT,TOUCH_Y1_RIGHT,px,py))
				{
					MemoryBox_Title_ChangeState(MEMORYBOX_TITLE_STATE_MENU);
				}
		}
	#endif
	#ifdef GAME_176_220
		myself->picLib->FillRect(myself->picLib,6,20,30,200,GAME_ToRGB(102,51,0));
		myself->picLib->DrawImageEx(myself->picLib,myself->imgIcon,10,30+myself->selectnum*20,true,0);
	#endif
	
	if(getManagerPtr()->IsKeyDown(MF_KEY_MID | MF_KEY_LEFTSOFT))
	{
		gamestage = 5;
		level = 1+myself->selectnum;
		if(level > 1)
		{
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
		}
		else
		{
			MemoryBox_Screen_Next = &MemoryBox_Screen_InGame;
			memoryBoxLoadingStep = 0;
			memoryBoxLoadingStepTotal = 16;
			SCREEN_ChangeScreen(&MemoryBox_Screen_Loading);
		}
	}
	if(getManagerPtr()->IsKeyDown(MF_KEY_RIGHTSOFT))
	{
		MemoryBox_Title_ChangeState(MEMORYBOX_TITLE_STATE_MENU);
	}
	/*
#ifdef GAME_240_320
	if(SCREEN_IsPointerDown())//触摸点击
	{
		px = SCREEN_GetPointerX();
		py = SCREEN_GetPointerY();//按键获得屏幕点

		if(MBCdRectPoint(TOUCH_X_RIGHT,TOUCH_Y_RIGHT,TOUCH_X1_RIGHT,TOUCH_Y1_RIGHT,px,py))
		{
			MemoryBox_Title_ChangeState(MEMORYBOX_TITLE_STATE_MENU);
				
		}
		if(MBCdRectPoint(TOUCH_X_LEFT,TOUCH_Y_LEFT,TOUCH_X1_LEFT,TOUCH_Y1_LEFT,px,py))
		{
			gamestage = 5;
			level = 1+myself->selectnum;
			if(level > 1)
			{
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
			}
			else
			{

				MemoryBox_Screen_Next = &MemoryBox_Screen_InGame;
				memoryBoxLoadingStep = 0;
				memoryBoxLoadingStepTotal = 16;
				SCREEN_ChangeScreen(&MemoryBox_Screen_Loading);
			}
		}
		
		if(MBCdRectPoint(20, 50+24*(myself->selectnum),210,74+24*(myself->selectnum),px,py))
		{
			gamestage = 5;
			level = 1+myself->selectnum;
			if(level > 1)
			{
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
			}
			else
			{

				MemoryBox_Screen_Next = &MemoryBox_Screen_InGame;
				memoryBoxLoadingStep = 0;
				memoryBoxLoadingStepTotal = 16;
				SCREEN_ChangeScreen(&MemoryBox_Screen_Loading);
			}
		}
		else if(py>50 && py<270 && px>20 && px<210)
		{
			myself->selectnum = (py-50)/24;
		}
	}
#endif
*/
}

