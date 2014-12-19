#include "HitMole_HighScore.h"
#include "HitMole_Screen.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
void initHitMoleHighScore(HitMole_HighScore * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib)
{
	initDFWindows(&myself->windows,DF_Windows_Rect,myself,myself,5);
	myself->windows.RenderCallBack=HitMole_HighScore_Windows_Render;
	myself->windows.UpdateCallBack=HitMole_HighScore_windows_Update;
	myself->picLib=picLib;//得到图片库指针
	HitMole_Loading_UpdateStep();
}
void HitMole_HighScore_Windows_Render(void * param)
{
	gm_s8 i;
	char * temp;
	char buff[10];
	HitMole_HighScore * myself = (HitMole_HighScore *)param;
	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(102,51,0));
	#ifdef GAME_240_320
		getManagerPtr()->DrawString("级别  最高分   日期",40,10,10,0xffff00);
		for(i=0;i<5;i++)
		{	
			sprintf((char*)buff,"%d％",60+i*10);
			getManagerPtr()->DrawString(buff,40,10,40+i*25,0xffff00);
			sprintf((char*)buff,"%d级",5+i);
			getManagerPtr()->DrawString(buff,40,15,165+i*25,0xffff00);
		}
		for(i=0;i<10;i++)
		{	temp = manager_my->formatString("%d",hitMoleHighScoreValue[i]);
			getManagerPtr()->DrawString(temp,40,75,40+i*25,0xffff00);
			//getManagerPtr()->DrawString("0000-00-00",40,130,40+i*25,0xffff00);
			if(hitMoleHighScoreYear[i]>0)
			{
				temp = manager_my->formatString("%d-%d-%d",hitMoleHighScoreYear[i],hitMoleHighScoreMonth[i],hitMoleHighScoreDate[i]);
				getManagerPtr()->DrawString(temp,40,130,40+i*25,0xffff00);
			}
			
		}
	#endif
	#ifdef GAME_176_220
		getManagerPtr()->DrawString("级别 最高分 年月日",40,10,10,0xffff00);
		for(i=0;i<5;i++)
		{	
			sprintf((char*)buff,"%d％",60+i*10);
			getManagerPtr()->DrawString(buff,40,10,25+i*17,0xffff00);
			sprintf((char*)buff,"%d级",5+i);
			getManagerPtr()->DrawString(buff,40,15,110+i*17,0xffff00);
		}
		for(i=0;i<10;i++)
		{	temp = manager_my->formatString("%d",hitMoleHighScoreValue[i]);
			getManagerPtr()->DrawString(temp,40,55,25+i*17,0xffff00);
			//getManagerPtr()->DrawString("0000-00-00",40,130,40+i*25,0xffff00);
			if(hitMoleHighScoreYear[i]>0)
			{
				temp = manager_my->formatString("%d-%d-%d",hitMoleHighScoreYear[i]-2000,hitMoleHighScoreMonth[i],hitMoleHighScoreDate[i]);
				getManagerPtr()->DrawString(temp,40,110,25+i*17,0xffff00);
			}
			
		}
	#endif
	getManagerPtr()->DrawString("按确定键返回",40,SCREEN_WIDTH/2-70,SCREEN_HEIGHT-20,0xffff00);
}
void HitMole_HighScore_windows_Update(void * param)
{
	if(getManagerPtr()->IsKeyDown(MF_KEY_MID))
		{
			HitMole_Title_ChangeState(HITMOLE_TITLE_STATE_MENU);
		}
}

