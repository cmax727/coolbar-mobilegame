/**************************************************************************************************************************************************
*compay:daicom
*name:zhaoliangqi
*filename:ONFF_map.h
*ªÊ÷∆µÿÕº
**************************************************************************************************************************************************/
#ifndef ONFF_MAP_H
#define ONFF_MAP_H

#include "DF_Windows.h"
#include "ONFF_Screen.h"
#include "DF_PictureLibrary.h"
#include "ONFF_Player.h"
#include "ONFF_Candy.h"

typedef struct GAMESTATE
{
	gm_s16 gameplayerlife;
	gm_s16 gameplayerbomb;
}GameState;

typedef struct BACKGROUND
{
	gm_s16 imgbroud;
	gm_u8 col;		
	gm_u8 row;		
	gm_u16 counter;	
	gm_u16 t;	
	gm_s16 y;       
	gm_bool scroll;
}Background;

typedef struct ONFF_MAP
{
	gm_s8 music;
	gm_s16 Game_stage;
	gm_s16 Game_count_max;
	gm_s16 Game_count_now;
	gm_s16 enemy[2];
	gm_s16 imgpoint;
	gm_s16 imgFailed;
	gm_s16 imgSuccess;
	gm_s16 bomb;
	gm_s16 tagenum;
	gm_s16 enemy_index;
	gm_s16 score;
	gm_s16 nextscore;
	gm_s16 imgfont;
	gm_s16 test1;
	Background background;
	DF_PictureLibrary * picLib;
	DF_Windows windows;
	Player player;
	Candy candy;
}ONFF_Map;

extern void initONFFMap(ONFF_Map * myself,Rect windows_Rect,DF_PictureLibrary * picLib,GameState gamestate,gm_s16 repaintMax);
void ONFF_Map_Windows_Render(void *param);
void ONFF_Map_Windows_Update(void * param);
#endif
