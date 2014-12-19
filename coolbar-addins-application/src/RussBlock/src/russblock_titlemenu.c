#include "RussBlock_TitleMenu.h"
#include "RussBlock_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif

static Manager manager;
 gm_s8  russBlockGameType; /*游戏模式*/
void RussBlock_DoSelectMenu(gm_s16 id);
//加载游戏中主菜单资源
void initRussBlockTitleMenu(RussBlockTitleMenu * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
	initManager(&manager);
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=RussBlock_TitleMenu_Render;
	myself->windows.UpdateCallBack=RussBlock_TitleMenu_Update;
	RussBlock_Loading_UpdateStep();
	myself->picLib=picLib;
	myself->imgTitleMenu[0]=picLib->GetImage(picLib,"logoitem2.gif");
	RussBlock_Loading_UpdateStep();
	myself->imgTitleMenu[2]=picLib->GetImage(picLib,"bottom.gif");
	myself->imgTitleMenu[3]=picLib->GetImage(picLib,"menuword.gif");
	myself->imgTitleMenu[5]=picLib->GetImage(picLib,"bg.gif");
	myself->imgCmd=picLib->GetImage(picLib,"cmd.gif");
	RussBlock_Loading_UpdateStep();
	/*
	initDFActor(&myself->hx,0,0);
	myself->hx.LoadActor(&myself->hx,picLib,"hx.actor");
	*/
	myself->selectMenu=0;
	russBlockGameType=GAMETYPE_NOMAL;
}

void RussBlock_DrawMiddleString(gm_u8 * str,gm_s32 x,gm_s32 y,gm_u32 color)
{
	gm_s32 width = (gm_s32)extVmLcdManager->VMGetStringWidth((char*)str);
	gm_s32 height = (gm_s32)extVmLcdManager->VMGetStringHeight((char*)str);
	width = width>>1;
	height = height>>1;
	extVmGameLcdManager->DrawString((char*)str,strlen(str),x-width,y-height,color);
}

//游戏主菜单绘制界面
void RussBlock_TitleMenu_Render(void *param)
{
	RussBlockTitleMenu * myself=(RussBlockTitleMenu *)param;
	gm_s8 i,j;
	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(36,19,121));
	manager.DrawUI(myself->picLib->image[myself->imgTitleMenu[5]],0,SCREEN_HEIGHT/6,SCREEN_WIDTH,SCREEN_HEIGHT*4/6,3);	
#ifdef GAME_240_320
	myself->picLib->DrawImageEx(myself->picLib,myself->imgTitleMenu[0],(SCREEN_WIDTH-myself->picLib->GetImageWidth(myself->picLib,myself->imgTitleMenu[0]))>>1,53,true,0);
	for (i=0;i<5;i++)
	{
		if(i<2)
		myself->picLib->DrawRegionEx(myself->picLib,myself->imgTitleMenu[3],92,177+18*i,(myself->selectMenu==i?0:57),15*i,57,15,true,0);
		else if(i>=2)
		myself->picLib->DrawRegionEx(myself->picLib,myself->imgTitleMenu[3],92,177+18*i,(myself->selectMenu==i?0:57),15*i+15,57,15,true,0);	
	}


	myself->picLib->DrawImage(myself->picLib,myself->imgTitleMenu[2],0,SCREEN_HEIGHT-myself->picLib->GetImageHeight(myself->picLib,myself->imgTitleMenu[2]));

	/*
	myself->hx.RenderEx(&myself->hx,-73,-182-myself->selectMenu*18);
	myself->hx.RenderEx(&myself->hx,-73-93,-182-myself->selectMenu*18);
	myself->hx.Update(&myself->hx);
	*/
	myself->picLib->DrawRegionEx(&russBlockPicLib,myself->imgCmd,9,301,0,0,25,13,true,0);//确定
	RussBlock_DrawMiddleString((gm_u8*)"本游戏免费",SCREEN_WIDTH>>1,305,0xffffff);
#endif
#ifdef	GAME_176_220
	myself->picLib->DrawImageEx(myself->picLib,myself->imgTitleMenu[0],(SCREEN_WIDTH-myself->picLib->GetImageWidth(myself->picLib,myself->imgTitleMenu[0]))>>1,25,true,0);
	
	for (i=0;i<5;i++)
	{
		if(i<2)
			myself->picLib->DrawRegionEx(myself->picLib,myself->imgTitleMenu[3],60,100+16*i,(myself->selectMenu==i?0:57),15*i,57,15,true,0);
		else if(i>=2)
			myself->picLib->DrawRegionEx(myself->picLib,myself->imgTitleMenu[3],60,100+16*i,(myself->selectMenu==i?0:57),15*i+15,57,15,true,0);
	}
	myself->picLib->DrawImage(myself->picLib,myself->imgTitleMenu[2],0,SCREEN_HEIGHT-myself->picLib->GetImageHeight(myself->picLib,myself->imgTitleMenu[2]));

/*	myself->hx.RenderEx(&myself->hx,-45,-105-myself->selectMenu*16);
	myself->hx.RenderEx(&myself->hx,-42-90,-105-myself->selectMenu*16);
	myself->hx.Update(&myself->hx);
*/
	myself->picLib->DrawRegionEx(&russBlockPicLib,myself->imgCmd,3,203,0,0,25,13,true,0);//确定
	RussBlock_DrawMiddleString((gm_u8*)"本游戏免费",SCREEN_WIDTH>>1,209,0xffffff);
#endif
}
//游戏主菜单按键控制界面
void RussBlock_TitleMenu_Update(void * param)
{
	RussBlockTitleMenu * myself=(RussBlockTitleMenu*)param;
	Rect ur;
	gm_s32 px,py,i;
#ifdef GAME_240_320
	ur.x=(SCREEN_WIDTH-140)>>1;
	ur.y=160;
	ur.w=140;
	ur.h=140;
#endif
#ifdef GAME_176_220
	ur.x=(SCREEN_WIDTH-107)>>1-10;
	ur.y=90;
	ur.w=140+15;
	ur.h=150;
#endif
	DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);
	if (getManagerPtr()->IsKeyDown(MF_KEY_UP|MF_KEY_2))//主菜单项选择
	{
		myself->selectMenu--;
		myself->selectMenu+=4;
		myself->selectMenu=(myself->selectMenu+1)%5;
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);
	}
	else if(getManagerPtr()->IsKeyDown(MF_KEY_8|MF_KEY_DOWN))//主菜单项选择
	{
		myself->selectMenu++;
		myself->selectMenu+=4;
		myself->selectMenu=(myself->selectMenu+1)%5;
		DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);
	}
	
	if(getManagerPtr()->IsKeyDown(MF_KEY_5|MF_KEY_MID|MF_KEY_LEFTSOFT))
	{
		RussBlock_DoSelectMenu(myself->selectMenu);
	}

	if(SCREEN_IsPointerDown())//触摸功能
	{
		px = SCREEN_GetPointerX();
		py = SCREEN_GetPointerY();
		for(i=0;i<5;i++)
		{
#ifdef GAME_240_320
			if(CdRectPoint((SCREEN_WIDTH-60)>>1,177+18*i,163,177+18*i+18,px,py))
#endif
#ifdef GAME_176_220
				if(CdRectPoint((SCREEN_WIDTH-60)>>1,100+16*i,((SCREEN_WIDTH-60)>>1)+57,100+16*i+16,px,py))
#endif
				{
					if(myself->selectMenu==i)
					{
						RussBlock_DoSelectMenu(myself->selectMenu);
					}
					else
					{
						myself->selectMenu = i;		
					}
					break;
				}
		}
#ifdef GAME_240_320
		if(CdRectPoint(9,299,36,314,px,py))
#endif
#ifdef GAME_176_220
		if(CdRectPoint(TOUCH_X_LEFT,TOUCH_Y_LEFT,TOUCH_X1_LEFT,TOUCH_Y1_LEFT,px,py))
#endif
			{
				RussBlock_DoSelectMenu(myself->selectMenu);
			}
	}
}

void RussBlock_DoSelectMenu(gm_s16 id)//选定主菜单后功能
{
	switch (id)
	{
	case 0:
		russBlockGameType=GAMETYPE_NOMAL;
		RussBlock_Screen_Next = &RussBlock_Screen_InGame;
		russBlockLoadingStep = 0;
		russBlockLoadingStepTotal = 16;
		SCREEN_ChangeScreen(&RussBlock_Screen_Loading);
		break;
	case 1:
		russBlockGameType=GAMETYPE_TIME;
		if(flag_GameOver) //游戏中失败了
		russBlockGameTime=BLOCK_TIME;
		RussBlock_Screen_Next = &RussBlock_Screen_InGame;
		russBlockLoadingStep = 0;
		russBlockLoadingStepTotal = 16;
		SCREEN_ChangeScreen(&RussBlock_Screen_Loading);
	    break;
	case 2:  
		RussBlock_Title_ChangeState(RUSSBLOCK_TITLE_STATE_HELP);
		break;
	case 3:
		RussBlock_Title_ChangeState(RUSSBLOCK_TITLE_STATE_HIGHSCORE);
		break;
	case 4:
		GAME_ServiceExit();
		break;
	
	}
}
void RussBlock_MenuBar_Paint(DF_PictureLibrary * param,gm_s16 id,gm_s16 width,gm_s16 height,gm_s16 y)
{
	gm_s32 i,j,x,wcount ,hcount;
	x=(SCREEN_WIDTH-width)>>1;
	param->DrawRegionEx(param,id,x,y,0,0,MENUBARWIDTH,MENUBARHEIGHT,true,0);	/*左上角*/
	param->DrawRegionEx(param,id,x+width-MENUBARWIDTH,y,2*MENUBARWIDTH,0,MENUBARWIDTH,MENUBARHEIGHT,true,0);	/*右上角*/
	
	param->DrawRegionEx(param,id,x,y+height-MENUBARHEIGHT,0,2*MENUBARHEIGHT,MENUBARWIDTH,MENUBARHEIGHT,true,0);	/*左下角*/
	param->DrawRegionEx(param,id,x+width-MENUBARWIDTH,y+height-MENUBARHEIGHT,2*MENUBARWIDTH,2*MENUBARHEIGHT,MENUBARWIDTH,MENUBARHEIGHT,true,0);	/*右下角*/

	for (i=0;i<(width-MENUBARWIDTH*2)/MENUBARWIDTH;i++)		/*上下横幅*/
	{
		param->DrawRegionEx(param,id,x+MENUBARWIDTH+i*MENUBARWIDTH,y,MENUBARWIDTH,0,MENUBARWIDTH,MENUBARHEIGHT,true,0);
		param->DrawRegionEx(param,id,x+MENUBARWIDTH+i*MENUBARWIDTH,y+height-MENUBARHEIGHT,MENUBARWIDTH,2*MENUBARHEIGHT,MENUBARWIDTH,MENUBARHEIGHT,true,0);
	}
	for (j=0;j<(height-MENUBARHEIGHT*2)/MENUBARHEIGHT;j++)		/*左右横幅*/
	{
		param->DrawRegionEx(param,id,x,y+MENUBARHEIGHT+j*MENUBARHEIGHT,0,MENUBARHEIGHT,MENUBARWIDTH,MENUBARHEIGHT,true,0);
		param->DrawRegionEx(param,id,x+width-MENUBARWIDTH,y+MENUBARHEIGHT+j*MENUBARHEIGHT,2*MENUBARWIDTH,MENUBARHEIGHT,MENUBARWIDTH,MENUBARHEIGHT,true,0);
	}
	param->FillRect(param,x+MENUBARWIDTH,y+MENUBARHEIGHT,width-2*MENUBARWIDTH,height-2*MENUBARHEIGHT,GAME_ToRGB(36,19,121));

}