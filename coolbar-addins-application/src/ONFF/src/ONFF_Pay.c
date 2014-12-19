/**************************************************************************************************************************************************
*compay:daicom
*name:zhaoliangqi
*filename:ONFF_map.c
**************************************************************************************************************************************************/
#include "ONFF_Pay.h"
#include "ONFF_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
static Manager manager;
void initONFFPay(ONFF_Pay * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{	
	initManager(&manager);
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=ONFF_Pay_Windows_Render;
	myself->windows.UpdateCallBack=ONFF_Pay_Windows_Update;
	myself->picLib = picLib;
	myself->border = picLib->GetImage(picLib,"border.gif");
#ifdef GAME_240_320
	initTextBox(&myself->textBox,2*1024,20,50,SCREEN_WIDTH-40,170);
	myself->textBox.SetDistance(&myself->textBox,20);
#endif 
#ifdef GAME_176_220
	initTextBox(&myself->textBox,2*1024,15,40,SCREEN_WIDTH-TEXT_SIZE*2,150);
#endif
	myself->textBox.SetText(&myself->textBox,"    本作是以二次大战为游戏背景，再加上一些科幻的设定,玩家可以在空中尽情地射击并歼灭敌人，好好体验一下重回第二次世界大战现场的感觉。\n    你可以使用短信(2元)或酷宝(28酷宝)支付，继续点播开始享受服务，返回则不扣费。\n  客服电话400-877-3373");
	myself->textBox.SetStyle(&myself->textBox,TEXTBOX_ALIGN_LEFT);
}


static void billingOnceCB(VMBOOLEAN isSuccess)
{
	if(isSuccess)
	{
		//成功
		//这里暂不处理
		ONFF_Screen_Next = &ONFF_Screen_InGame;
		oNFFLoadingStep = 0;
		oNFFLoadingStepTotal = 16;
		SCREEN_ChangeScreen(&ONFF_Screen_Loading);
		
	}
	else
	{
	       //失败      退出
		ONFF_Title_ChangeState(ONFF_TITLE_STATE_MENU);				
	}		
}

void ONFFPayRender(ONFF_Pay * myself)
{

	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(36,19,121));
	myself->picLib->DrawImageEx(myself->picLib,myself->border,0,0,true,0);
#ifdef GAME_176_220
	extOldGameManager->DrawString("返回",25,130,TOUCH_Y_RIGHT,0xffff00);
	extOldGameManager->DrawString("资费提示",20,SCREEN_WIDTH/2-40,10,0xffff00);
	myself->textBox.Render(&myself->textBox,0xffff00);//绘制帮助内容
#endif
#ifdef GAME_240_320
	extOldGameManager->DrawString("资费提示",20,SCREEN_WIDTH/2-40,15,0xffff00);
	myself->textBox.Render(&myself->textBox,0xffff00);//绘制帮助内容
	extOldGameManager->DrawString("下一页",25,TOUCH_X_RIGHT-30,TOUCH_Y_RIGHT,0xffff00);
#endif 
#ifdef GAME_176_220 
	myself->textBox.Render(&myself->textBox,0xffff00);//绘制帮助内容
	extOldGameManager->DrawString(" ↓",12,SCREEN_WIDTH/2-15,TOUCH_Y_LEFT,0xffff00);
#endif
	if(extVmBillingManager->BILLING_GetRemainDay(NETAPP_APP_ONFF,NETAPP_BILLING_METHOD_ONCE_MONTH) == 0){
		extOldGameManager->DrawString("点播",12,TOUCH_X_LEFT,TOUCH_Y_LEFT,0xffff00);
	}
}
void ONFF_Pay_Windows_Render(void * param)
{
	ONFF_Pay * myself =(ONFF_Pay *)param;
	ONFFPayRender(myself);
}

void ONFF_Pay_Windows_Update(void * param)
{
	ONFF_Pay * myself =(ONFF_Pay *)param;
	char enterStr[60] = {0};
	gm_s16 px,py;
	
	if(extVmBillingManager->BILLING_GetRemainDay(NETAPP_APP_ONFF,NETAPP_BILLING_METHOD_ONCE_MONTH) == 0){
		ONFFPayRender(myself);
		if(myself->textBox.curPage == 1)
		{
			manager.DrawString(enterStr,40,TOUCH_X_LEFT,SCREEN_HEIGHT-90,0xff0000);
//			sprintf((char*)enterStr,"点播后可享用%d天",extVmBillingManager->BILLING_GetValidDayByAppId(NETAPP_APP_ONFF,NETAPP_BILLING_METHOD_ONCE_MONTH));
			manager.DrawString(enterStr,40,TOUCH_X_LEFT,SCREEN_HEIGHT-60,0xff0000);
			#ifdef GAME_240_320
			myself->picLib->FillRect(myself->picLib,TOUCH_X_RIGHT-30,288,65,22,GAME_ToRGB(36,16,121));
				extOldGameManager->DrawString("返回",25,TOUCH_X_RIGHT-10,TOUCH_Y_RIGHT,0xffff00);
			#endif
		}
		if(extOldGameManager->IsKeyDown(MF_KEY_LEFTSOFT) && extVmBillingManager->BILLING_GetRemainDay(NETAPP_APP_ONFF,NETAPP_BILLING_METHOD_ONCE_MONTH) == 0)
		{
//			extVmBillingManager->BILLING_Pay3(NETAPP_APP_ONFF,NETAPP_BILLING_METHOD_ONCE_MONTH,billingOnceCB,1,FALSE);
		}
		#ifdef GAME_176_220
		myself->picLib->FillRect(myself->picLib,SCREEN_WIDTH/2-10,195,25,20,GAME_ToRGB(36,19,121));
		if(myself->textBox.curPage == 0)
		extOldGameManager->DrawString(" ↓",12,SCREEN_WIDTH/2-15,TOUCH_Y_LEFT,0xffff00);
		else if(myself->textBox.curPage == 1)
		extOldGameManager->DrawString(" ↓↑",12,SCREEN_WIDTH/2-20,TOUCH_Y_LEFT,0xffff00);
		else if(myself->textBox.curPage ==2)
		extOldGameManager->DrawString(" ↑",12,SCREEN_WIDTH/2-15,TOUCH_Y_LEFT,0xffff00);
	if (getManagerPtr()->IsKeyDown(MF_KEY_UP | MF_KEY_2))//按键操作部分
	{
		if (myself->textBox.curPage==2)//文本框翻页
			myself->textBox.curPage=1;
		else if (myself->textBox.curPage==1)
			myself->textBox.curPage = 0;
		//刷新屏幕
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&myself->windows.DF_Windows_Rect);
	}
	if (getManagerPtr()->IsKeyDown(MF_KEY_DOWN| MF_KEY_8))//按键操作部分
	{
		if (myself->textBox.curPage==0)//文本框翻页
			myself->textBox.curPage=1;
		else if (myself->textBox.curPage==1)
			myself->textBox.curPage = 2;
		//刷新屏幕
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&myself->windows.DF_Windows_Rect);
	}
	if (extOldGameManager->IsKeyDown(MF_KEY_RIGHTSOFT))
	{		
		myself->textBox.curPage = 0;
		ONFF_Title_ChangeState(ONFF_TITLE_STATE_MENU);
	}
	#endif
		#ifdef GAME_240_320
		if(extOldGameManager->IsKeyDown(MF_KEY_RIGHTSOFT) && myself->textBox.curPage==1)
		{	
			myself->textBox.curPage = 0;
			ONFF_Title_ChangeState(ONFF_TITLE_STATE_MENU);
		}
		else if(extOldGameManager->IsKeyDown(MF_KEY_RIGHTSOFT) && myself->textBox.curPage==0)
		{
			myself->textBox.curPage = 1;
		}
		
		if(SCREEN_IsPointerDown())
		{
			px = SCREEN_GetPointerX();
			py = SCREEN_GetPointerY();

			if(CdRectPoint3(TOUCH_X_RIGHT,TOUCH_Y_RIGHT,TOUCH_X1_RIGHT,TOUCH_Y1_RIGHT,px,py))
			{
				if(myself->textBox.curPage == 1)
				{
					myself->textBox.curPage = 0;
					ONFF_Title_ChangeState(ONFF_TITLE_STATE_MENU);
				}
				else
				{
					myself->textBox.curPage = 1;
				}
				
			}

//			if(CdRectPoint3(TOUCH_X_LEFT,TOUCH_Y_LEFT,TOUCH_X1_LEFT,TOUCH_Y1_LEFT,px,py) && extVmBillingManager->BILLING_GetRemainDay(NETAPP_APP_ONFF,NETAPP_BILLING_METHOD_ONCE_MONTH) == 0)
//				extVmBillingManager->BILLING_Pay3(NETAPP_APP_ONFF,NETAPP_BILLING_METHOD_ONCE_MONTH,billingOnceCB,1,FALSE);
		}
		#endif
	}
	else
	{
		ONFF_Title_ChangeState(ONFF_TITLE_STATE_MENU);
	}
	
}
