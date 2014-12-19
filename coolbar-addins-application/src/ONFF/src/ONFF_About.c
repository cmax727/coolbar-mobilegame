#include "ONFF_About.h"
#include "ONFF_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif

void initONFFAbout(ONFF_About * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=ONFF_About_Windows_Render;
	myself->windows.UpdateCallBack=ONFF_About_windows_Update;
	myself->picLib=picLib;
	myself->border = picLib->GetImage(picLib,"border.gif");
	ONFF_Loading_UpdateStep();
#ifdef GAME_240_320
	initTextBox(&myself->textBox,2*1024,20,50,SCREEN_WIDTH-40,200);
	myself->textBox.SetDistance(&myself->textBox,20);
	myself->textBox.SetText(&myself->textBox,"游戏名称:1945 \n容量:204k \n版本号:V1.0 \n开发商:\n大连泰康科技 \n电话:\n0411-39750535 \n网址：\nhttp://www.daicom.ca");
#endif 
#ifdef GAME_176_220
	initTextBox(&myself->textBox,2*1024,15,40,SCREEN_WIDTH-TEXT_SIZE*2,165);
	myself->textBox.SetText(&myself->textBox,"游戏名称:1945 \n容量:201k \n版本号:V1.0 \n开发商:\n大连泰康科技 \n电话:\n0411-39750535 \n网址：\nhttp://www.daicom.ca");
	myself->textBox.SetStyle(&myself->textBox,TEXTBOX_ALIGN_LEFT);
#endif
	
}
void ONFF_About_Windows_Render(void * param)
{
	ONFF_About * myself=(ONFF_About *)param;
	
	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(36,19,121));
	myself->picLib->DrawImageEx(myself->picLib,myself->border,0,0,true,0);
	extOldGameManager->DrawString("关于",25,SCREEN_WIDTH/2-20,10,0xffff00);
#ifdef GAME_240_320
	myself->textBox.Render(&myself->textBox,0xffff00);
#endif 
#ifdef GAME_176_220 
	myself->textBox.Render(&myself->textBox,0xffff00);
	//extOldGameManager->DrawString("按上下键翻页",12,10 ,202,0xffff00);
	extOldGameManager->DrawString(" ↓",12,SCREEN_WIDTH/2-10,TOUCH_Y_LEFT,0xffff00);
	extOldGameManager->DrawString("返回",25,TOUCH_X_RIGHT,TOUCH_Y_RIGHT,0xffff00);
#endif
}
void ONFF_About_windows_Update(void * param)
{
	ONFF_About * myself=(ONFF_About *)param;
	gm_s32 px,py;
	#ifdef GAME_176_220
		myself->picLib->FillRect(myself->picLib,SCREEN_WIDTH/2-10,195,25,20,GAME_ToRGB(36,19,121));
		if(myself->textBox.curPage == 0)
		extOldGameManager->DrawString(" ↓",12,SCREEN_WIDTH/2-10,TOUCH_Y_LEFT,0xffff00);
		else
		extOldGameManager->DrawString(" ↑",12,SCREEN_WIDTH/2-10,TOUCH_Y_LEFT,0xffff00);
	if (getManagerPtr()->IsKeyDown(MF_KEY_UP | MF_KEY_2))//按键操作部分
	{
		 if (myself->textBox.curPage==1)
			myself->textBox.curPage = 0;
		//刷新屏幕
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&myself->windows.DF_Windows_Rect);
	}
	if (getManagerPtr()->IsKeyDown(MF_KEY_DOWN| MF_KEY_8))//按键操作部分
	{
		if (myself->textBox.curPage==0)//文本框翻页
			myself->textBox.curPage=1;
		//刷新屏幕
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&myself->windows.DF_Windows_Rect);
	}
	if (extOldGameManager->IsKeyDown(MF_KEY_RIGHTSOFT))
	{		
		myself->textBox.curPage = 0;
		ONFF_Title_ChangeState(ONFF_TITLE_STATE_MENU);
	}
	#endif
	if(SCREEN_IsPointerDown())
	{
		px = SCREEN_GetPointerX();
		py = SCREEN_GetPointerY();
#ifdef GAME_240_320
		if(CdRectPoint3(TOUCH_X_RIGHT,TOUCH_Y_RIGHT,TOUCH_X1_RIGHT,TOUCH_Y1_RIGHT,px,py))
			{
				myself->textBox.curPage = 0;
				ONFF_Title_ChangeState(ONFF_TITLE_STATE_MENU);
				
			}
#endif

	}
}