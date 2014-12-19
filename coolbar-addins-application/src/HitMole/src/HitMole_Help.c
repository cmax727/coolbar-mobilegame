#include "HitMole_Help.h"
#include "HitMole_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif

//初使化帮助界面中信息，加载图片和文字
void initHitMoleHelp(HitMole_Help* myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=HitMole_Help_Windows_Render;//绘制区域
	myself->windows.UpdateCallBack=HitMole_Help_windows_Update;//按键控制
	myself->picLib=picLib;
	myself->border=picLib->GetImage(picLib,"border.gif");
	//使用文本编辑器加载文字
#ifdef GAME_240_320
	initTextBox(&myself->textBox,2*1024,20,45,SCREEN_WIDTH-40,240);
	myself->textBox.SetDistance(&myself->textBox,20);
	myself->textBox.SetText(&myself->textBox,"    操作：1-9键对应9个地洞挥锤(触摸屏可直接点),确定键进行下一关,0键开/关音效,左软键暂停右软键返回开始画面。\n    本游戏共有9个难度，按开始从难度1打起,第一关有20只棕鼠,以后每关加10只难度也会增加,打中数达到相应百分比,才可以过关,注意：不要打白鼠。\n    自定义可选择适当难度,一开始有十条命,每达到一定的分数会增加一条命,漏掉一只棕鼠,或错打一只白鼠,都要减一条命,直到生命为0游戏结束。\n    本游戏(2元/10天)或酷宝(28酷宝/月)。");
	
#endif 
#ifdef GAME_176_220
	initTextBox(&myself->textBox,2*1024,15,40,SCREEN_WIDTH-TEXT_SIZE*2,165);
	myself->textBox.SetText(&myself->textBox,"    操作：1-9键对应9个地洞挥锤(触摸屏可直接点),确定键进行下一关,0键开/关音效,左软键暂停右软键返回开始画面。\n    本游戏共有9个难度，按开始从难度1打起,第一关有20只棕鼠,以后每关加10只难度也会增加,打中数达到相应百分比,才可以过关,注意：不要打白鼠。\n    自定义可选择适当难度,一开始有十条命,每达到一定的分数会增加一条命,漏掉一只棕鼠,或错打一只白鼠,都要减一条命,直到生命为0游戏结束。\n    本游戏(2元/10天)或酷宝(28酷宝/月)。");
	myself->textBox.SetStyle(&myself->textBox,TEXTBOX_ALIGN_LEFT);
#endif
	HitMole_Loading_UpdateStep();
	
}
//绘制帮助中界面
void HitMole_Help_Windows_Render(void * param)
{
	HitMole_Help* myself=(HitMole_Help *)param;
	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(102,51,0));
	myself->picLib->DrawImageEx(myself->picLib,myself->border,0,0,true,0);
	
#ifdef GAME_240_320
	extOldGameManager->DrawString("帮助",25,SCREEN_WIDTH/2-20,15,0xffff00);
	myself->textBox.Render(&myself->textBox,0xffff00);//绘制帮助内容
	extOldGameManager->DrawString("下一页",12,TOUCH_X_LEFT,TOUCH_Y_LEFT,0xffff00);
	extOldGameManager->DrawString("返回",25,TOUCH_X_RIGHT-10,TOUCH_Y_RIGHT,0xffff00);
#endif 
#ifdef GAME_176_220 
	extOldGameManager->DrawString("帮助",25,SCREEN_WIDTH/2-20,10,0xffff00);
	myself->textBox.Render(&myself->textBox,0xffff00);//绘制帮助内容
	if(myself->textBox.curPage == 0)
			extOldGameManager->DrawString(" ↓",12,SCREEN_WIDTH/2-15,SCREEN_HEIGHT-20,0xffff00);
		else if(myself->textBox.curPage == 3)
			extOldGameManager->DrawString(" ↑",12,SCREEN_WIDTH/2-15,SCREEN_HEIGHT-20,0xffff000);
		else
			extOldGameManager->DrawString("↑↓",12,SCREEN_WIDTH/2-15,SCREEN_HEIGHT-20,0xffff00);
	extOldGameManager->DrawString("返回",25,TOUCH_X_RIGHT,TOUCH_Y_RIGHT,0xffff00);
#endif
	
}
//按键操作帮助中界面
void HitMole_Help_windows_Update(void * param)
{
	HitMole_Help * myself=(HitMole_Help *)param;
	gm_s32 px,py;
	#ifdef	GAME_240_320
	myself->picLib->FillRect(myself->picLib,9,288,20,20,GAME_ToRGB(102,51,0));
	if(myself->textBox.curPage == 0)
		extOldGameManager->DrawString("下一页",12,TOUCH_X_LEFT,TOUCH_Y_LEFT,0xffff00);
	else
		extOldGameManager->DrawString("上一页",12,TOUCH_X_LEFT,TOUCH_Y_LEFT,0xffff00);
	if (getManagerPtr()->IsKeyDown(MF_KEY_LEFTSOFT))//按键操作部分
	{
		if (myself->textBox.curPage==1)//文本框翻页
		{
			myself->textBox.curPage=0;
		}else
			myself->textBox.curPage=1;
		//刷新屏幕
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&myself->windows.DF_Windows_Rect);
	}
	#endif
	#ifdef	GAME_176_220
		if(myself->textBox.curPage >= 0 && myself->textBox.curPage <= 3)
		{
			if (getManagerPtr()->IsKeyDown(MF_KEY_UP | MF_KEY_2))//文本框翻页
			{
				myself->textBox.curPage--;
				if(myself->textBox.curPage < 0)
					myself->textBox.curPage = 0;
			}
			else if(getManagerPtr()->IsKeyDown(MF_KEY_DOWN | MF_KEY_8))
			{
				myself->textBox.curPage++;
				if(myself->textBox.curPage > 3)
					myself->textBox.curPage = 3;
			}
			DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&myself->windows.DF_Windows_Rect);
		}
			//刷新屏幕
	#endif
	if (getManagerPtr()->IsKeyDown(MF_KEY_RIGHTSOFT))//回主菜单
	{		
		myself->textBox.curPage = 0;
		HitMole_Title_ChangeState(HITMOLE_TITLE_STATE_MENU);
	}
#ifdef GAME_240_320
	if(SCREEN_IsPointerDown())//触摸点击
	{
		px = SCREEN_GetPointerX();
		py = SCREEN_GetPointerY();//按键获得屏幕点
		if(MyCdRectPoint(185,290,227,308,px,py))
		{
			myself->textBox.curPage = 0;
			HitMole_Title_ChangeState(HITMOLE_TITLE_STATE_MENU);
		}
		if(MyCdRectPoint(8,290,68,308,px,py))
		{
			if (myself->textBox.curPage==1)//文本框翻页
			{
			myself->textBox.curPage=0;
			}else
			myself->textBox.curPage=1;
			DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&myself->windows.DF_Windows_Rect);
		}
	}
#endif

}


