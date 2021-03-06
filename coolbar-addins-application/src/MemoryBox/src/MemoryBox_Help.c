#include "MemoryBox_Help.h"
#include "MemoryBox_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif

//初使化帮助界面中信息，加载图片和文字
void initMemoryBoxHelp(MemoryBox_Help* myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=MemoryBox_Help_Windows_Render;//绘制区域
	myself->windows.UpdateCallBack=MemoryBox_Help_windows_Update;//按键控制
	myself->picLib=picLib;
	//使用文本编辑器加载文字
#ifdef GAME_240_320
	initTextBox(&myself->textBox,2*1024,20,50,SCREEN_WIDTH-40,200);
	myself->textBox.SetDistance(&myself->textBox,20);
	myself->textBox.SetText(&myself->textBox,"    本游戏共分9关,每关累加55秒的时限,规定时间内找出所有,相同的图案算做过关,方向键控制方向，或者数字键2、8、4、6分别控制上、下、左、右移动,确定键或5键点开选择的块.\n本游戏短信支付(2元/10天)或酷宝支付(28酷宝/月)");
	
#endif 
#ifdef GAME_176_220
	initTextBox(&myself->textBox,2*1024,16,18,SCREEN_WIDTH-TEXT_SIZE*2,185);
	myself->textBox.SetText(&myself->textBox,"    本游戏共分9关,每关累加55秒的时限,规定时间内找出所有,相同的图案算做过关,方向键控制方向，或者数字键2、8、4、6分别控制上、下、左、右移动,确定键或5键点开选择的块.\n本游戏短信支付(2元/10天)或酷宝支付(28酷宝/月)");
	myself->textBox.SetStyle(&myself->textBox,TEXTBOX_ALIGN_LEFT);
#endif
	myself->imgback = picLib->GetImage(picLib,"bei.gif");
	MemoryBox_Loading_UpdateStep();
	
}
//绘制帮助中界面
void MemoryBox_Help_Windows_Render(void * param)
{
	MemoryBox_Help* myself=(MemoryBox_Help *)param;
	myself->picLib->DrawFullScreen(myself->picLib,myself->imgback);
#ifdef GAME_240_320
	myself->picLib->FillRect(myself->picLib,20,50,200,250,GAME_ToRGB(102,51,0));
	myself->textBox.Render(&myself->textBox,0xffff00);//绘制帮助内容
#endif 
#ifdef GAME_176_220 
	myself->textBox.Render(&myself->textBox,0xffff00);//绘制帮助内容
	extOldGameManager->DrawString("按上下键翻页",12,TOUCH_X_LEFT,TOUCH_Y_LEFT,0xffff00);
#endif
	extOldGameManager->DrawString("返回",25,TOUCH_X_RIGHT-10,TOUCH_Y_RIGHT+10,0xffff00);
}
//按键操作帮助中界面
void MemoryBox_Help_windows_Update(void * param)
{
	MemoryBox_Help * myself=(MemoryBox_Help *)param;
	gm_s32 px,py;
	if (getManagerPtr()->IsKeyDown(MF_KEY_UP|MF_KEY_2))//按键操作部分
	{
		if (myself->textBox.curPage>0)//文本框翻页
		{
			myself->textBox.curPage--;
		}
		//刷新屏幕
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&myself->windows.DF_Windows_Rect);
	}
	else if (getManagerPtr()->IsKeyDown(MF_KEY_DOWN|MF_KEY_8))
	{
		if (myself->textBox.curPage<myself->textBox.page-1)//文本框翻页
		{
			myself->textBox.curPage++;		
		}
		//刷新屏幕
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&myself->windows.DF_Windows_Rect);
	}
	if (getManagerPtr()->IsKeyDown(MF_KEY_RIGHTSOFT))//回主菜单
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
	}
#endif
}

