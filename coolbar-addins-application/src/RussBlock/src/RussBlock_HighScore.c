#include "RussBlock_HighScore.h"
#include "RussBlock_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
//初使化加载排行界面
void initRussBlockHighScore(RussBlock_HighScore * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=RussBlock_Score_Windows_Render;
	myself->windows.UpdateCallBack=RussBlock_Score_windows_Update;
	myself->picLib=picLib;//得到图片库指针
	myself->imgHelp[0]=myself->picLib->GetImage(myself->picLib,"help.gif");//加载图片
	myself->imgHelp[1]=myself->picLib->GetImage(myself->picLib,"cmd.gif");
	RussBlock_Loading_UpdateStep();
	myself->imgHelp[2]=myself->picLib->GetImage(myself->picLib,"bottom.gif");
	myself->imgMenuBar=myself->picLib->GetImage(myself->picLib,"menubar.gif");
	RussBlock_Loading_UpdateStep();
	myself->model=0;
}
//绘制排行界面
void RussBlock_Score_Windows_Render(void * param)
{
	char * temp;
	char * temp0;
	gm_s16 i=0;
	RussBlock_HighScore * myself=(RussBlock_HighScore *)param;
	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(36,19,121));
#ifdef GAME_240_320
	RussBlock_MenuBar_Paint(myself->picLib,myself->imgMenuBar,MENUBARWIDTH*6,MENUBARHEIGHT*7,9+5);
	myself->picLib->DrawRegionEx(myself->picLib,myself->imgHelp[0],(SCREEN_WIDTH-myself->picLib->GetImageWidth(myself->picLib,myself->imgHelp[0]))>>1,9+7+5,0,20,92,20,true,0);
	myself->picLib->DrawImage(myself->picLib,myself->imgHelp[2],0,SCREEN_HEIGHT-myself->picLib->GetImageHeight(myself->picLib,myself->imgHelp[2]));
	myself->picLib->DrawRegionEx(myself->picLib,myself->imgHelp[1],206,301,0,39,25,13,TRUE,0);
	if (myself->model==0)
	{
		temp0="传统模式";
	}
	else 
	{
		temp0="时间模式";
	}
	getManagerPtr()->DrawString(temp0,10,85,58,0xffffff);
	for (i=0;i<12;i+=2)
	{
		if (myself->model==0)
		{
			temp=manager_my->formatString("第%d名 %d分 %d层",(i>>1)+1,russBlockHighScoreValue_CommonModel[i],russBlockHighScoreValue_CommonModel[i+1]);
		}
		else
			temp=manager_my->formatString("第%d名 %d分 %d层",(i>>1)+1,russBlockHighScoreValue_TimeModel[i],russBlockHighScoreValue_TimeModel[i+1]);

		getManagerPtr()->DrawString(temp,20,25,96+25*(i>>1),0xffffff);
	}
	getManagerPtr()->DrawString("按上下键翻页",20,64,298,0xffffff);
#endif
#ifdef GAME_176_220
	RussBlock_MenuBar_Paint(myself->picLib,myself->imgMenuBar,MENUBARWIDTH*4,MENUBARHEIGHT*5,5);
	myself->picLib->DrawRegionEx(myself->picLib,myself->imgHelp[0],(SCREEN_WIDTH-myself->picLib->GetImageWidth(myself->picLib,myself->imgHelp[0]))>>1,6+5,0,18,83,18,true,0);
	myself->picLib->DrawImage(myself->picLib,myself->imgHelp[2],0,SCREEN_HEIGHT-myself->picLib->GetImageHeight(myself->picLib,myself->imgHelp[2]));
	myself->picLib->DrawRegionEx(myself->picLib,myself->imgHelp[1],148,203,0,39,25,13,TRUE,0);
	if (myself->model==0)
	{
		temp0="传统模式";
	}
	else 
	{
		temp0="时间模式";
	}
	getManagerPtr()->DrawString(temp0,8,55,45,0xffffff);
	for (i=0;i<12;i+=2)
	{
		if (myself->model==0)
		{
			temp=manager_my->formatString("%d名 %d分",(i>>1)+1,russBlockHighScoreValue_CommonModel[i]);
		}
		else
			temp=manager_my->formatString("%d名 %d分",(i>>1)+1,russBlockHighScoreValue_TimeModel[i]);

		getManagerPtr()->DrawString(temp,strlen(temp),30,66+17*(i>>1),0xffffff);
	}
	getManagerPtr()->DrawString("按上下键翻页",12,(SCREEN_WIDTH-6*TEXT_SIZE)>>1,202,0xffffff);
#endif
}
//按键排行界面操作
void RussBlock_Score_windows_Update(void * param)
{
	RussBlock_HighScore * myself=(RussBlock_HighScore *)param;
	gm_s16 px,py;

	if (getManagerPtr()->IsKeyDown(MF_KEY_RIGHTSOFT))//按键回主菜单
	{
		RussBlock_Title_ChangeState(RUSSBLOCK_TITLE_STATE_MENU);
	}
	else if (getManagerPtr()->IsKeyDown(MF_KEY_UP|MF_KEY_2))//按键向上
	{
		myself->model--;
		myself->model+=1;
		myself->model=(myself->model+1)%2;
		//刷新屏幕
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&myself->windows.DF_Windows_Rect);
	}
	else if (getManagerPtr()->IsKeyDown(MF_KEY_DOWN|MF_KEY_8))//按键向下
	{
		myself->model++;
		myself->model+=1;
		myself->model=(myself->model+1)%2;
		//刷新屏幕
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&myself->windows.DF_Windows_Rect);

	}
	if(SCREEN_IsPointerDown())//触摸点
	{
		px = SCREEN_GetPointerX();
		py = SCREEN_GetPointerY();
#ifdef GAME_240_320
		if(CdRectPoint(TOUCH_X_RIGHT,TOUCH_Y_RIGHT,TOUCH_X1_RIGHT,TOUCH_Y1_RIGHT,px,py))
#endif
#ifdef GAME_176_220
			if(CdRectPoint(TOUCH_X_RIGHT,TOUCH_Y_RIGHT,TOUCH_X1_RIGHT,TOUCH_Y1_RIGHT,px,py))
#endif
				RussBlock_Title_ChangeState(RUSSBLOCK_TITLE_STATE_MENU);//点击回主菜单

	}
}