#include "RussBlock_UI.h"
#include "RussBlock_Screen.h"
#include "RussBlock_Map.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif

gm_s16 action1;
//初使化和加载UI中得数值
void initRussBlockUi (RussBlockUi * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib,gm_s32 score,gm_s32 clearedlayer)
{
	initDFWindows (&myself->windows,DF_Windows_Rect,myself,myself,10);
	myself->windows.RenderCallBack =RussBlock_UI_Windows_Render;
	myself->windows.UpdateCallBack =RussBlock_UI_Windows_Update;
	myself->picLib=picLib;
	//加载ui中的图片
	myself->imgUI[0]=myself->picLib->GetImage(myself->picLib,"panel.gif");
	myself->imgUI[1]=myself->picLib->GetImage(myself->picLib,"top.gif");
	RussBlock_Loading_UpdateStep();
	myself->imgUI[2]=myself->picLib->GetImage(myself->picLib,"leftframe.gif");
	myself->imgUI[3]=myself->picLib->GetImage(myself->picLib,"bottom.gif");
	myself->imgUI[4]=myself->picLib->GetImage(myself->picLib,"score_num.gif");
	RussBlock_Loading_UpdateStep();
	myself->imgGirl=myself->picLib->GetImage(myself->picLib,"rtx.gif");
	myself->imgHiteffect=picLib->GetImage(picLib,"hiteffect.gif");
/*	initDFActor(&myself->actorGirlFace,0,0);
	myself->actorGirlFace.LoadActor(&myself->actorGirlFace,myself->picLib,"rwbq.actor");
*/
	myself->imgCmd=myself->picLib->GetImage(myself->picLib,"cmd.gif");
	RussBlock_Loading_UpdateStep();
	if (russBlockGameType==GAMETYPE_TIME)
	{
		myself->imgTime=myself->picLib->GetImage(myself->picLib,"time.gif");
	}
	myself->imgPropBar=myself->picLib->GetImage(myself->picLib,"propbar.gif");
	RussBlock_Loading_UpdateStep();
	myself->imgPropNum=myself->picLib->GetImage(myself->picLib,"propnum.gif");
	myself->imgPropKey=myself->picLib->GetImage(myself->picLib,"propkey.gif");
	RussBlock_Loading_UpdateStep();
	myself->imgClear=myself->picLib->GetImage(myself->picLib,"clear.gif");
	myself->score=russBlockGameData[russBlockGameType][1];
	//myself->score=9999;
	myself->lastClearedLayer=0;
	myself->clearedlayer=russBlockGameData[russBlockGameType][2];
	//myself->clearedlayer=9999;
	myself->flag_action=false;
	myself->level=russBlockGameData[russBlockGameType][0];
	myself->action=0;
	myself->flag_hit=false;
	myself->hitCount=0;

	myself->hitNum=0;
	myself->UpdateScore=RussBlock_UI_UpdateScore;
	myself->UpdateClearedLayer=RussBlock_UI_UpdateClearedLayer;
	myself->UpdateLevel=RussBlock_UI_UpdateLevel;
	myself->UpdateRect=RussBlock_UI_UpdateRect;
	myself->UpdateGirlFace=RussBlock_UI_UpdateGirlFace;
}
void RussBlock_UI_Windows_Update(void * param)
{
	RussBlockUi * myself=(RussBlockUi * )param;

	if (myself->flag_action) UpdateGirlFace1(param);    /*MM笑了*/
	if (myself->flag_hit)  
	{
		RussBlock_UI_UpdateRect(myself,150,93,90,30); /*出现连击*/
	
		if(myself->hitCount++>10)
		{
			myself->flag_hit=false;
			myself->hitCount=0;
		}
	}
}
//刷新UI界面中数值
static void UpdateGirlFace1(void * param)
{
	Rect ur ;
	RussBlockUi * myself;
	myself=(RussBlockUi * )param;
	ur.x=173;
	ur.y=39;
	ur.w=49;
	ur.h=53;

	//myself->actorGirlFace.ChangeAction(&myself->actorGirlFace,myself->action);
	
	DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);
	/*一次动画循环播放结束*/
/*	if (myself->actorGirlFace.currentFrameCount>=myself->actorGirlFace.GetFrameNum(&myself->actorGirlFace))
	{
		myself->flag_action=false;

	}
	myself->actorGirlFace.Update(&myself->actorGirlFace);
*/
}

void RussBlock_UI_UpdateRect(RussBlockUi * myself ,gm_s16 x,gm_s16 y,gm_s16 w,gm_s16 h)
{
	Rect ur;
	ur.x=x;
	ur.y=y;
	ur.w=w;
	ur.h=h;
   DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);
}
void RussBlock_UI_UpdateScore(RussBlockUi * myself)
{
#ifdef GAME_240_320
	Rect ur;
	ur.x=189;
	ur.y=155;
	ur.w=51;
	ur.h=11;
	DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);
#endif // GAME_240_320

}
void RussBlock_UI_UpdateClearedLayer(RussBlockUi * myself)
{
#ifdef GAME_240_320
	Rect ur;
	ur.x=212;
	ur.y=123;
	ur.w=28;
	ur.h=16;
	DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);
#endif // GAME_240_320
}
void RussBlock_UI_UpdateLevel(RussBlockUi * myself)
{
#ifdef GAME_240_320
	Rect ur;
	ur.x=217;
	ur.y=84;
	ur.w=19;
	ur.h=11;
	DF_SendMessage(&myself->windows,DF_WINDOWS_MSG_INVALITE,&ur);
#endif // GAME_240_320
}

void RussBlock_UI_UpdateGirlFace(RussBlockUi * myself,gm_s16 action)
{
	myself->flag_action=true;
	myself->action=action;
}

void RussBlock_UI_TimeRender(RussBlockUi * myself,gm_s16 time,gm_s16 x, gm_s16 y)
{
	gm_s16 min=0,sec=0;

	min=time/60;
	sec=time-min*60;

	if (time<0)
	{
		return;
	}
#ifdef GAME_240_320

	myself->picLib->DrawNumber(myself->picLib,myself->imgTime,min/10,11,14,x,y,0);

	myself->picLib->DrawNumber(myself->picLib,myself->imgTime,min%10,11,14,x+11,y,0);
	myself->picLib->DrawRegionEx(myself->picLib,myself->imgTime,x+11*2-3,y,110,0,11,14,true,0);  //:

	myself->picLib->DrawNumber(myself->picLib,myself->imgTime,sec/10,11,14,x+28,y,0);
	myself->picLib->DrawNumber(myself->picLib,myself->imgTime,sec%10,11,14,x+28+11,y,0);
#endif 
#ifdef GAME_176_220
	myself->picLib->DrawNumber(myself->picLib,myself->imgTime,min/10,8,11,x,y,0);

	myself->picLib->DrawNumber(myself->picLib,myself->imgTime,min%10,8,11,x+10,y,0);
	myself->picLib->DrawRegionEx(myself->picLib,myself->imgTime,x+20,y,80,0,4,11,true,0);  //:

	myself->picLib->DrawNumber(myself->picLib,myself->imgTime,sec/10,8,11,x+26,y,0);
	myself->picLib->DrawNumber(myself->picLib,myself->imgTime,sec%10,8,11,x+37,y,0);
#endif
}
gm_s16 countShan=0;
//绘制UI界面
void RussBlock_UI_Windows_Render(void * param)
{
	RussBlockUi * myself=(RussBlockUi * )param;
	int temp_0,temp_1,temp_2;
#ifdef GAME_240_320
	myself->picLib->DrawImage(myself->picLib,myself->imgUI[2],0,37);
	myself->picLib->DrawImage(myself->picLib,myself->imgUI[0],SCREEN_WIDTH-myself->picLib->GetImageWidth(myself->picLib,myself->imgUI[0]),37);
	if(russBlockInGameState==RUSSBLOCK_INGAME_MAINSTATE_PLAYING ||russBlockInGameState==RUSSBLOCK_INGAME_MAINSTATE_MOVING)/*画底下横幅*/
	{
		myself->picLib->DrawImage(myself->picLib,myself->imgUI[3],0,SCREEN_HEIGHT-30);
		russBlockPicLib.DrawRegionEx(&russBlockPicLib,myself->imgCmd,9,301,0,52,25,13,true,0);
	}

	myself->picLib->DrawNumber(myself->picLib,myself->imgUI[4],myself->score,7,10,200-14,155,GM_ALIGN_LEFT);
	myself->picLib->DrawImageEx(myself->picLib,myself->imgClear,187,124,TRUE,0);
	myself->picLib->DrawNumber(myself->picLib,myself->imgUI[4],myself->clearedlayer,7,10,224,127,GM_ALIGN_CENTER);
	myself->picLib->DrawNumber(myself->picLib,myself->imgUI[4],myself->level,7,10,228,83,GM_ALIGN_CENTER);

	if (russBlockGameType==GAMETYPE_TIME)
	{	
		RussBlock_UI_TimeRender(myself,russBlockGameTime,182,6);
		if (russBlockGameTime<10)
		{
			countShan=(countShan+1)%10;
			if ( countShan>5)
				getManagerPtr()->DrawString("时间快到！",48,((SCREEN_WIDTH-5*TEXT_SIZE)>>1),295,0xffffff);
		}

	}
	//if (myself->flag_action) myself->actorGirlFace.RenderEx(&myself->actorGirlFace,-173-23,-39-27);
	//else
	myself->picLib->DrawImageEx(myself->picLib,myself->imgGirl,173,39,true,GM_ALIGN_LEFT);
	if (myself->flag_hit)  /*出现连击*/
	{
		switch (russBlockHitNum)
		{
		case 2:
		case 3:
		case 4:
			myself->picLib->DrawRegionEx(myself->picLib,myself->imgHiteffect,150,93,0,33*(russBlockHitNum-2),74,33,true,0);
			break;
		case 5:
		default:
			myself->picLib->DrawRegionEx(myself->picLib,myself->imgHiteffect,150,93,0,33*3,74,33,true,0);
			break;
		}
	}
#endif
#ifdef GAME_176_220
	myself->picLib->DrawImage(myself->picLib,myself->imgUI[2],0,25); 
	myself->picLib->DrawImage(myself->picLib,myself->imgUI[0],SCREEN_WIDTH-myself->picLib->GetImageWidth(myself->picLib,myself->imgUI[0]),25);
	if(russBlockInGameState==RUSSBLOCK_INGAME_MAINSTATE_PLAYING ||russBlockInGameState==RUSSBLOCK_INGAME_MAINSTATE_MOVING)/*画底下横幅*/
	{
		myself->picLib->DrawImage(myself->picLib,myself->imgUI[3],0,SCREEN_HEIGHT-22);
		russBlockPicLib.DrawRegionEx(&russBlockPicLib,myself->imgCmd,3,203,0,52,25,13,true,0);
	}

	myself->picLib->DrawNumber(myself->picLib,myself->imgUI[4],myself->score,7,9,139,99,GM_ALIGN_LEFT);

	myself->picLib->DrawImageEx(myself->picLib,myself->imgClear,132,77,TRUE,0);

	myself->picLib->DrawNumber(myself->picLib,myself->imgUI[4],myself->clearedlayer,7,9,148,78,GM_ALIGN_LEFT);

	if (myself->level<10)
	{
		myself->picLib->DrawNumber(myself->picLib,myself->imgUI[4],myself->level,7,9,160,45,GM_ALIGN_LEFT);
	}
	else if (myself->level>9 && myself->level<100)
	{
		myself->picLib->DrawNumber(myself->picLib,myself->imgUI[4],myself->level,7,9,160,45,GM_ALIGN_LEFT);
	}
	else
		myself->picLib->DrawNumber(myself->picLib,myself->imgUI[4],myself->level,7,9,155,45,GM_ALIGN_LEFT);

	if (russBlockGameType==GAMETYPE_TIME)
	{
		RussBlock_UI_TimeRender(myself,russBlockGameTime,130,4);
		if (russBlockGameTime<10)
		{ 
			if ( timerCnt%10>5)
				getManagerPtr()->DrawString("时间快到！",strlen("时间快到！"),((SCREEN_WIDTH-5*TEXT_SIZE)>>1),202,0xffffff);
		}

	}
//	if (myself->flag_action) myself->actorGirlFace.RenderEx(&myself->actorGirlFace,-126-15,-26-16);
	//else 
	myself->picLib->DrawImageEx(myself->picLib,myself->imgGirl,126,26,true,GM_ALIGN_LEFT);
	if (myself->flag_hit)  /*出现连击*/
	{
		switch (russBlockHitNum)
		{
		case 2:
		case 3:
		case 4:
			myself->picLib->DrawRegionEx(myself->picLib,myself->imgHiteffect,113,48,0,23*(russBlockHitNum-2),53,23,true,0);
			break;
		case 5:
		default:
			myself->picLib->DrawRegionEx(myself->picLib,myself->imgHiteffect,113,48,0,23*3,53,23,true,0);
			break;
		}
	}

#endif
}