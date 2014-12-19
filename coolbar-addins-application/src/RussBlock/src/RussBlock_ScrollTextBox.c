#include "RussBlock_ScrollTextBox.h"
#include "RussBlock_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif

//#ifndef __WIN_32
//#include "billing.h"
//#endif

char * ppp,* ppp1;


void initRussBlockScrollTextBox(RussBlock_ScrollTextBox * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib,gm_s16 w )
{
	char *str1;
	char *str=  manager_my->formatString("美女们带着俄罗斯方块来了，爽快的道具，赶快加入游戏哦。");
	DF_Malloc((void **)&ppp,(strlen(str)+1)*sizeof(gm_u8));
	memcpy(ppp,str,strlen(str)*sizeof(gm_u8));
	ppp[strlen(str)] = 0;

	str1=manager_my->formatString("快来挑战吧！游戏包月费%d元",BILLING_GetPayNumByAppId(NETAPP_APP_RUSSBLOCK,NETAPP_BILLING_METHOD_ONCE_MONTH));
	DF_Malloc((void **)&ppp1,(strlen(str1)+1)*sizeof(gm_u8));
	memcpy(ppp1,str1,strlen(str1)*sizeof(gm_u8));

	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,1);
	myself->windows.RenderCallBack =RussBlock_ScrollTextBox_Windows_Render;
	myself->windows.UpdateCallBack = RussBlock_ScrollTextBox_Winsows_Update;	
	myself->picLib = picLib;
	myself->inx=0;
	myself->count=0;
	myself->imgCmd=picLib->GetImage(picLib,"cmd.gif");
	myself->imgBottom=picLib->GetImage(picLib,"bottom.gif");
		RussBlock_Loading_UpdateStep();
	myself->imgScollTextBox[0] = picLib->GetImage(picLib,"menubar.gif");	
	myself->imgTitle[1]=myself->picLib->GetImage(myself->picLib,"entergame.gif");
#ifdef GAME_240_320
	initTextBox(&myself->textBox,5024,TEXT_SIZE+5,140+75,SCREEN_WIDTH-TEXT_SIZE*2,100);
	initTextBox(&myself->textBox1,500,TEXT_SIZE+5,140+75,SCREEN_WIDTH-TEXT_SIZE*2,100);
#endif
	RussBlock_Loading_UpdateStep();
#ifdef GAME_176_220
	initTextBox(&myself->textBox,5024,TEXT_SIZE+15,120,SCREEN_WIDTH-TEXT_SIZE*4,220-70);
	initTextBox(&myself->textBox1,500,TEXT_SIZE+15,120,SCREEN_WIDTH-TEXT_SIZE*4,100);
#endif
	myself->textBox.SetText(&myself->textBox,ppp);
	myself->textBox.SetStyle(&myself->textBox,TEXTBOX_ALIGN_LEFT);

	myself->textBox1.SetText(&myself->textBox1,ppp1);
	myself->textBox1.SetStyle(&myself->textBox1,TEXTBOX_ALIGN_LEFT);
	RussBlock_Loading_UpdateStep();
}

void RussBlock_ScrollTextBox_Windows_Render (void * param)
{
	RussBlock_ScrollTextBox * myself = (RussBlock_ScrollTextBox *)param;

	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(36,19,121));

#ifdef GAME_240_320
	RussBlock_MenuBar_Paint(myself->picLib,myself->imgScollTextBox[0],6*MENUBARWIDTH,MENUBARHEIGHT*3,180);
	if(myself->inx==0)
	myself->textBox.Render(&myself->textBox,0xffffff);
	else
	myself->textBox1.Render(&myself->textBox1,0xffffff);
	myself->picLib->DrawImage(myself->picLib,myself->imgBottom,0,SCREEN_HEIGHT-myself->picLib->GetImageHeight(myself->picLib,myself->imgBottom));
	russBlockPicLib.DrawRegionEx(&russBlockPicLib,myself->imgCmd,9,301,0,0,25,13,true,0);//确定
	russBlockPicLib.DrawRegionEx(&russBlockPicLib,myself->imgCmd,206,301,0,13,25,13,true,0);//退出
	getManagerPtr()->DrawString("按上下键翻页",25,64,298,0xffffff);

#endif
#ifdef GAME_176_220
	RussBlock_MenuBar_Paint(myself->picLib,myself->imgScollTextBox[0],4*MENUBARWIDTH,MENUBARHEIGHT*3,90);
	if(myself->inx==0)
	myself->textBox.Render(&myself->textBox,0xffffff);
	else
	myself->textBox1.Render(&myself->textBox1,0xffffff);

	myself->picLib->DrawImage(myself->picLib,myself->imgBottom,0,SCREEN_HEIGHT-myself->picLib->GetImageHeight(myself->picLib,myself->imgBottom));
	russBlockPicLib.DrawRegionEx(&russBlockPicLib,myself->imgCmd,3,203,0,0,25,13,true,0);//确定
	russBlockPicLib.DrawRegionEx(&russBlockPicLib,myself->imgCmd,148,203,0,13,25,13,true,0);//退出
	getManagerPtr()->DrawString("按上下键翻页",12,45 ,202,0xffffff);

#endif 
}

void RussBlock_ScrollTextBox_Winsows_Update(void * param)
{
	gm_s32 px,py;
	RussBlock_ScrollTextBox * myself = (RussBlock_ScrollTextBox *)param;	

	DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&myself->windows.DF_Windows_Rect);
	
	if (myself->count++>100)
	{
		myself->count=0;
		myself->inx=(myself->inx+1)%2;
	}

	if(getManagerPtr()->IsKeyDown(MF_KEY_5|MF_KEY_MID|MF_KEY_LEFTSOFT))
	{
		BILLING_Pay(NETAPP_APP_RUSSBLOCK,NETAPP_BILLING_METHOD_ONCE_MONTH,RussBlock_SMS_BuyOneMonth);
	}
	else if (getManagerPtr()->IsKeyDown(MF_KEY_UP|MF_KEY_2))
	{
		myself->inx=0;
	}
	else if (getManagerPtr()->IsKeyDown(MF_KEY_DOWN|MF_KEY_8))
	{
		myself->inx=1;
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&myself->windows.DF_Windows_Rect);
	}
	else if(getManagerPtr()->IsKeyDown(MF_KEY_RIGHTSOFT))
	{
#ifdef __WIN_32
		russBlockRecord.Close(&russBlockRecord);
#endif
		GAME_ServiceExit();
	}

	if(SCREEN_IsPointerDown())
	{
		px = SCREEN_GetPointerX();
		py = SCREEN_GetPointerY();
#ifdef GAME_240_320
		if(CdRectPoint(9,299,36,314,px,py))
#endif
#ifdef GAME_176_220
		if(CdRectPoint(TOUCH_X_LEFT,TOUCH_Y_LEFT,TOUCH_X1_LEFT,TOUCH_Y1_LEFT,px,py))
#endif
		{
			BILLING_Pay(NETAPP_APP_RUSSBLOCK,NETAPP_BILLING_METHOD_ONCE_MONTH,RussBlock_SMS_BuyOneMonth);
		}
#ifdef GAME_240_320
		else if(CdRectPoint(205,299,231,314,px,py))
#endif
#ifdef GAME_176_220
		else
		if(CdRectPoint(TOUCH_X_RIGHT,TOUCH_Y_RIGHT,TOUCH_X1_RIGHT,TOUCH_Y1_RIGHT,px,py))
#endif
		{
#ifdef __WIN_32
			russBlockRecord.Close(&russBlockRecord);
#endif			
			GAME_ServiceExit();
		}
	}

}