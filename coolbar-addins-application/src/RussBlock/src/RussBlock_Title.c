#include "RussBlock_Title.h"
#include "RussBlock_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
//游戏中logo界面初使化和加载
static Manager manager;
void initRussBlockTitle(RussBlockTitle * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
       initManager(&manager);
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=RussBlock_Title_Windows_Render;
	myself->windows.UpdateCallBack=RussBlock_Title_Windows_Update;
	myself->picLib=picLib;
	 RussBlock_Loading_UpdateStep();
	myself->imgTitle[0]=myself->picLib->GetImage(myself->picLib,"logoitem1.gif");
	RussBlock_Loading_UpdateStep();
	myself->imgTitle[1]=myself->picLib->GetImage(myself->picLib,"logoitem2.gif");
	myself->imgTitle[2]=myself->picLib->GetImage(myself->picLib,"entergame.gif");
	myself->imgTitle[3]=myself->picLib->GetImage(myself->picLib,"bg.gif");
		
	RussBlock_Loading_UpdateStep();
	myself->counter=0;
}
//游戏中logo界面绘制
void RussBlock_Title_Windows_Render(void * param)
{
	RussBlockTitle * myself=(RussBlockTitle *)param;
	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(36,19,121));
//	manager.DrawUI(myself->picLib->image[myself->imgTitle[3]],0,SCREEN_HEIGHT/6,SCREEN_WIDTH,SCREEN_HEIGHT*4/6,3);	
#ifdef GAME_240_320
	
	myself->picLib->DrawImageEx(myself->picLib,myself->imgTitle[0],(SCREEN_WIDTH-myself->picLib->GetImageWidth(myself->picLib,myself->imgTitle[0]))>>1,73,true,0);
	myself->picLib->DrawImageEx(myself->picLib,myself->imgTitle[1],(SCREEN_WIDTH-myself->picLib->GetImageWidth(myself->picLib,myself->imgTitle[1]))>>1,150,true,0);
	if(myself->counter%8<4)
	myself->picLib->DrawImageEx(myself->picLib,myself->imgTitle[2],(SCREEN_WIDTH-myself->picLib->GetImageWidth(myself->picLib,myself->imgTitle[2]))>>1,293,true,0);
#endif 
#ifdef GAME_176_220

	myself->picLib->DrawImageEx(myself->picLib,myself->imgTitle[0],(SCREEN_WIDTH-myself->picLib->GetImageWidth(myself->picLib,myself->imgTitle[0]))>>1,50,true,0);
	myself->picLib->DrawImageEx(myself->picLib,myself->imgTitle[1],(SCREEN_WIDTH-myself->picLib->GetImageWidth(myself->picLib,myself->imgTitle[1]))>>1,115,true,0);
	if(myself->counter%8<4)
		myself->picLib->DrawImageEx(myself->picLib,myself->imgTitle[2],(SCREEN_WIDTH-myself->picLib->GetImageWidth(myself->picLib,myself->imgTitle[2]))>>1,200,true,0);
#endif 
}
//游戏中logo界面按键
void RussBlock_Title_Windows_Update(void * param)
{
	
//按任意键继续闪烁程序
/*	RussBlockTitle * myself=(RussBlockTitle *)param;
	Rect ur;
	myself->counter++;
	if(myself->counter%8 == 4||myself->counter%8 == 0)
	{
		ur.x=(SCREEN_WIDTH-myself->picLib->GetImageWidth(myself->picLib,myself->imgTitle[1]))>>1;
#ifdef GAME_240_320
		ur.y=293;
#endif
#ifdef GAME_176_220
		ur.y=200;
#endif 
		ur.w=myself->picLib->GetImageWidth(myself->picLib,myself->imgTitle[1]);
		ur.h=myself->picLib->GetImageHeight(myself->picLib,myself->imgTitle[1]);
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);
	}
	*/
	if (getManagerPtr()->IsKeyDown(MF_KEY_ANY)||SCREEN_IsPointerDown())
	{

		gm_u32 u=BILLING_GetRemainDay(NETAPP_APP_RUSSBLOCK,NETAPP_BILLING_METHOD_ONCE_MONTH);
		RussBlock_Title_ChangeState(RUSSBLOCK_TITLE_STATE_MENU);
	#ifdef FREE_REALEASE
		RussBlock_Title_ChangeState(RUSSBLOCK_TITLE_STATE_MENU);
#endif
	
	}
}
