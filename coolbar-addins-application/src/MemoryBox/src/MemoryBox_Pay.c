/**************************************************************************************************************************************************
*compay:daicom
*name:zhaoliangqi
*
**************************************************************************************************************************************************/
#include "MemoryBox_Pay.h"
#include "MemoryBox_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
static Manager manager;
void initMemoryBoxPay(MemoryBox_Pay * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{	
	initManager(&manager);
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=MemoryBox_Pay_Windows_Render;
	myself->windows.UpdateCallBack=MemoryBox_Pay_Windows_Update;
	myself->picLib = picLib;
	myself->border = picLib->GetImage(picLib,"bei.gif");
#ifdef GAME_240_320
	initTextBox(&myself->textBox,2*1024,20,50,SCREEN_WIDTH-40,230);
	myself->textBox.SetDistance(&myself->textBox,20);
	
#endif 
#ifdef GAME_176_220
	initTextBox(&myself->textBox,2*1024,30,40,SCREEN_WIDTH-TEXT_SIZE*4,105);
	
#endif
	myself->textBox.SetText(&myself->textBox,"记忆盒是一款集趣味娱乐益智于一身的益智休闲游戏,本游戏可以锻炼您的记忆能力并使您的记忆力得到提高，是一款很不错的游戏，你可以使用短信(2元)或酷宝(28酷宝)支付，继续点播开始享受服务，返回则不扣费。客服电话400-877-3373");
	myself->textBox.SetStyle(&myself->textBox,TEXTBOX_ALIGN_LEFT);
}

static void MemoryBoxbillingOnceCB(VMBOOLEAN isSuccess)
{
	if(isSuccess)
	{
		//成功
		//这里暂不处理
		MemoryBox_Title_ChangeState(MEMORYBOX_TITLE_STATE_MENU);
		
	}
	else
	{
	       //失败      退出
		extVmSysManager->VmEnterWinClose();					
	}		
}

void MemoryBoxPayRender(MemoryBox_Pay * myself)
{	
	char enterStr[60] = {0};
	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(102,51,0));
	myself->picLib->DrawImageEx(myself->picLib,myself->border,0,0,true,0);
	extOldGameManager->DrawString("资费提示",20,SCREEN_WIDTH/2-40,5,0xffff00);
#ifdef GAME_240_320
	myself->textBox.Render(&myself->textBox,0xffff00);//绘制帮助内容
#endif 
#ifdef GAME_176_220 
	myself->textBox.Render(&myself->textBox,0xffff00);//绘制帮助内容
	extOldGameManager->DrawString("↑↓",25,SCREEN_WIDTH/2-15,TOUCH_Y_RIGHT,0xffff00);
#endif
	extOldGameManager->DrawString("返回",25,TOUCH_X_RIGHT,TOUCH_Y_RIGHT,0xffff00);
	extOldGameManager->DrawString("点播",25,TOUCH_X_LEFT,TOUCH_Y_LEFT,0xffff00);
//	sprintf((char*)enterStr,"点播后可享用%d天",extVmBillingManager->BILLING_GetValidDayByAppId(NETAPP_APP_MEMORYBOX,NETAPP_BILLING_METHOD_ONCE_MONTH));
	manager.DrawString(enterStr,40,30,SCREEN_HEIGHT-50,0xff0000);
}
void MemoryBox_Pay_Windows_Render(void * param)
{
	MemoryBox_Pay * myself =(MemoryBox_Pay *)param;
	 MemoryBoxPayRender(myself);
}

void MemoryBox_Pay_Windows_Update(void * param)
{
	gm_s32 px,py;
	MemoryBox_Pay * myself =(MemoryBox_Pay *)param;
	MemoryBoxPayRender(myself);
	if (extOldGameManager->IsKeyDown(MF_KEY_UP|MF_KEY_2))//按键操作部分
	{
		if (myself->textBox.curPage>0)//文本框翻页
		{
			myself->textBox.curPage--;
		}
		//刷新屏幕
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&myself->windows.DF_Windows_Rect);
	}
	else if (extOldGameManager->IsKeyDown(MF_KEY_DOWN|MF_KEY_8))
	{
		if (myself->textBox.curPage<myself->textBox.page-1)//文本框翻页
		{
			myself->textBox.curPage++;		
		}
		//刷新屏幕
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&myself->windows.DF_Windows_Rect);
	}
	if(extOldGameManager->IsKeyDown(MF_KEY_LEFTSOFT))
	{
//		extVmBillingManager->BILLING_Pay3(NETAPP_APP_MEMORYBOX,NETAPP_BILLING_METHOD_ONCE_MONTH,MemoryBoxbillingOnceCB,1,FALSE);
	}
	if(extOldGameManager->IsKeyDown(MF_KEY_RIGHTSOFT))
	{
		myself->textBox.curPage = 0;
		MemoryBox_Title_ChangeState(MEMORYBOX_TITLE_STATE_MENU);
	}
	#ifdef GAME_240_320
	if(SCREEN_IsPointerDown())//触摸点击
	{
		px = SCREEN_GetPointerX();
		py = SCREEN_GetPointerY();//按键获得屏幕点

		if(MBCdRectPoint(TOUCH_X_RIGHT,TOUCH_Y_RIGHT,TOUCH_X1_RIGHT,TOUCH_Y1_RIGHT,px,py))
		{
			myself->textBox.curPage = 0;
			MemoryBox_Title_ChangeState(MEMORYBOX_TITLE_STATE_MENU);
		}
		if(MBCdRectPoint(TOUCH_X_LEFT,TOUCH_Y_LEFT,TOUCH_X1_LEFT,TOUCH_Y1_LEFT,px,py))
		{
//			extVmBillingManager->BILLING_Pay3(NETAPP_APP_MEMORYBOX,NETAPP_BILLING_METHOD_ONCE_MONTH,MemoryBoxbillingOnceCB,1,FALSE);
		}
	}
#endif
}
