#include "CatLoveDog_Help.h"
#include "CatLoveDog_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
void initCatLoveDogHelp(CatLoveDog_Help * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=CatLoveDog_Help_Windows_Render;
	myself->windows.UpdateCallBack=CatLoveDog_Help_windows_Update;
	myself->picLib=picLib;
	myself->imghelpBorder = myself->picLib->GetImage(picLib,"border.gif");
	CatLoveDog_Loading_UpdateStep();
#ifdef GAME_240_320
	initTextBox(&myself->textBox,2*1024,20,50,SCREEN_WIDTH-40,200);
	myself->textBox.SetDistance(&myself->textBox,20);
#endif 
#ifdef GAME_176_220
	initTextBox(&myself->textBox,2*1024,30,40,SCREEN_WIDTH-TEXT_SIZE*4,135);
#endif
	myself->textBox.SetText(&myself->textBox,"    进入游戏后玩家可以选择游戏难度,难度\n越难的关卡狗扔骨头就越快和准。\n    玩家控制猫这个角色,按5或者选择键\n启动力度条,再按一次猫投掷鱼刺以打到对方为目的，先使对方生命值减少为0的胜利。\n    玩家玩的时候要注意风的方向和大小\n    会影响到猫扔出的鱼刺的力度，风的方向力度显示在屏幕上方。\n\n  祝您玩的愉快!!\n  本游戏短信支付(2元/10天)或酷宝支付(28酷宝/月)");
	myself->textBox.SetStyle(&myself->textBox,TEXTBOX_ALIGN_LEFT);
}
void CatLoveDog_Help_Windows_Render(void * param)
{
	CatLoveDog_Help * myself=(CatLoveDog_Help *)param;
	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(36,19,121));
	myself->picLib->DrawImageEx(myself->picLib,myself->imghelpBorder,0,0,true,0);
#ifdef GAME_240_320
	extOldGameManager->DrawString("帮助",25,SCREEN_WIDTH/2-20,15,0xffff00);
	myself->textBox.Render(&myself->textBox,0xffff00);
#endif 
#ifdef GAME_176_220 
	extOldGameManager->DrawString("帮助",25,SCREEN_WIDTH/2-20,10,0xffff00);
	myself->textBox.Render(&myself->textBox,0xffff00);
#endif
	extOldGameManager->DrawString("↑↓",12,SCREEN_WIDTH/2-20,TOUCH_Y_LEFT,0xffff00);
	extOldGameManager->DrawString("返回",25,TOUCH_X_RIGHT,TOUCH_Y_RIGHT,0xffff00);
}

void CatLoveDog_Help_windows_Update(void * param)
{
	CatLoveDog_Help * myself=(CatLoveDog_Help *)param;
	gm_s32 px,py;
	if (extOldGameManager->IsKeyDown(MF_KEY_UP|MF_KEY_2))
	{
		if (myself->textBox.curPage>0)
		{
			myself->textBox.curPage--;
		}
		
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&myself->windows.DF_Windows_Rect);
	}
	else if (extOldGameManager->IsKeyDown(MF_KEY_DOWN|MF_KEY_8))
	{
		if (myself->textBox.curPage<myself->textBox.page-1)
		{
			myself->textBox.curPage++;		
		}
		
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&myself->windows.DF_Windows_Rect);
	}
	if (extOldGameManager->IsKeyDown(MF_KEY_RIGHTSOFT))
	{		
		myself->textBox.curPage = 0;
		CatLoveDog_Title_ChangeState(CatLoveDog_TITLE_STATE_MENU);
	}
	if(SCREEN_IsPointerDown())
	{
		px = SCREEN_GetPointerX();
		py = SCREEN_GetPointerY();
#ifdef GAME_240_320
		if(CdRectPoint2(TOUCH_X_RIGHT,TOUCH_Y_RIGHT,TOUCH_X1_RIGHT,TOUCH_Y1_RIGHT,px,py))
#endif
#ifdef GAME_176_220
			if(CdRectPoint2(TOUCH_X_RIGHT,TOUCH_Y_RIGHT,TOUCH_X1_RIGHT,TOUCH_Y1_RIGHT,px,py))
#endif
			{
				myself->textBox.curPage = 0;
				CatLoveDog_Title_ChangeState(CatLoveDog_TITLE_STATE_MENU);
				
			}

	}
}