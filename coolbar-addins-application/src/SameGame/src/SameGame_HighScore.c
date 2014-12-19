#include "SameGame_HighScore.h"
#include "SameGame_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif

void SameGame_HighScore_Init(SameGameHighScore * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=SameGame_HighScore_Render;
	myself->windows.UpdateCallBack=SameGame_HighScore_Update;
	myself->picLib=picLib;//得到图片库指针
	SameGame_Loading_UpdateStep();
}

void SameGame_HighScore_Render(void * param)
{
	SameGameHighScore * myself = (SameGameHighScore *)param;
	gm_s16 i;
	char * temp;

	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(0,146,0));

	getManagerPtr()->DrawString("★ ハイスコア ★",40,(SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("★ ハイスコア ★"))/2,50,0xFFFFFF);
	getManagerPtr()->DrawString("初級 : ",40,60,100,0xFFFFFF);
	getManagerPtr()->DrawString("中級 : ",40,60,130,0xFFFFFF);
	getManagerPtr()->DrawString("上級 : ",40,60,160,0xFFFFFF);
	getManagerPtr()->DrawString("??????は",40,(SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("??????は"))/2,200,0xFFFFFF);
	getManagerPtr()->DrawString("ホームページをみてね",40,(SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("ホームページをみてね"))/2,230,0xFFFFFF);

	for(i=0;i<3;i++)
	{
		temp = manager_my->formatString("%d",sameGameHighTimeValue[i]);
		getManagerPtr()->DrawString(temp,40,140,100+i*30,0xFFFFFF);
	}

	getManagerPtr()->DrawString("返回",40,SCREEN_WIDTH-extVmLcdManager->VMGetStringWidth("返回"),SCREEN_HEIGHT-20,0xFFFF00);
}

void SameGame_HighScore_Update(void * param)
{
	if(getManagerPtr()->IsKeyDown(MF_KEY_RIGHTSOFT|MF_KEY_MID|MF_KEY_5) || SCREEN_IsPointerDown())
	{
		SameGame_Title_ChangeState(SAMEGAME_STATE_TITLEMENU);
	}
}
