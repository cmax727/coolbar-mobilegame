/**************************************************************************************************************************************************
*compay:daicom
*name:zhaoliangqi
*filename:ONFF_map.c
*
**************************************************************************************************************************************************/
#include "ONFF_Map.h"
#include "ONFF_Screen.h"
#include "coolbar_GameUtil.h"
#ifdef COOLBAR_DYNAMIC_LOADING
#include "dl_app_Redefine.h"
#endif
gm_s16 candy_speed1[6] = {4, 8, 12, 12, 3, 3}; 
gm_s16 candy[51][13],candy_speed[6],adjunct[5][7];
gm_s16 Enemy_Unit[25][54];
char * temp;
static Manager manager;
static gm_s16 unsign(gm_s16 x) {
    if (x < 0 || x == 44) {
      return (x + 256);
    }
    else {
      return (x);
    }
  }

gm_s16 trig(gm_s16 x, gm_s16 index) { 
    gm_s32 i, j, k;
	gm_s16 sin[10] = {0, 17, 34, 50, 64, 77, 87, 94, 98, 100};
    i = 0;
    if (x > 180) {
      j = 360 - x;
    }
    else {
      j = x;
    }
    if (j > 90) {
      j = 180 - j;
    }
    while (j > 0) {
      i++;
      j = j - 10;
    }
    if (index == 0) {
      if (x > 180) {
        k = 1;
      }
      else {
        k = -1;
      }
      j = sin[i] * k;
    }
    else {
      if (x > 90 && x < 270) {
        k = -1;
      }
      else {
        k = 1;
      }
      j = sin[9 - i] * k;
    }
    return (j);
  }

const gm_s16 adjuctMap(gm_s16 x0, gm_s16 x1, gm_s16 speed) 
{
	if (Abs(x0 - x1) < speed) {
		return (0);
	} else if (x0 - x1 < 0) {
		return speed;
	} else {
		return (-speed);
	}
}

gm_s32 atan(gm_s16 x, gm_s16 y) {
		int i, j;
		gm_s16 atg[9] = {1, 18, 36, 58, 84, 130, 200, 385, 800};
		if (x != 0 && y * 10 / x < 80 && y * 10 / x > -80) {
			j = y * 100 / x;
		} else {
			if (y > 0) {
				return (90);
			} else {
				return (270);
			}
		}
		if (j < 0) {
			j = -j;
		}
		i = 0;
		while (i < 8 && j > atg[i]) {
			i++;
		}
		if (x > 0 && y > 0) {
			return (i * 10);
		}
		if (x < 0 && y > 0) {
			return (180 - i * 10);
		}
		if (x < 0 && y < 0) {
			return (180 + i * 10);
		} else {
			return (360 - i * 10);
		}
	}
void initONFFMap(ONFF_Map * myself,Rect windows_Rect,DF_PictureLibrary * picLib,GameState gamestate,gm_s16 repaintMax)
{
	initManager(&manager);
 	initDFWindows(&myself->windows,windows_Rect,myself,myself,repaintMax);
    myself->windows.RenderCallBack=ONFF_Map_Windows_Render;
    myself->windows.UpdateCallBack=ONFF_Map_Windows_Update;
	myself->picLib=picLib;
	myself->Game_stage = 1;
	myself->score = 0;
	myself->nextscore = 200;
	myself->imgFailed = picLib->GetImage(picLib,"Menu_title.gif");
	myself->imgSuccess = picLib->GetImage(picLib,"Menu_map_0.gif");
	ONFF_Loading_UpdateStep();
	myself->imgpoint = picLib->GetImage(picLib,"Menu_point.gif");
	ONFF_Loading_UpdateStep();
	myself->background.imgbroud = picLib->GetImage(picLib,"Background.gif");
	myself->background.col = (SCREEN_WIDTH%32==0?SCREEN_WIDTH/32+1:SCREEN_WIDTH/32+2);
	myself->background.row = (SCREEN_HEIGHT%32==0?SCREEN_HEIGHT/32+1:SCREEN_HEIGHT/32+2);
	myself->background.t = 0;
	myself->background.y = 0;
	myself->background.counter = 0;
	myself->background.scroll = true;
	ONFF_Loading_UpdateStep();
	myself->enemy[0] = picLib->GetImage(picLib,"Enemy.gif");
	myself->tagenum = 0;
	myself->enemy_index = 25;
	myself->enemy[1] = picLib->GetImage(picLib,"boss1.gif");
	myself->bomb = picLib->GetImage(picLib,"Enemy_bomb.gif");
	ONFF_Loading_UpdateStep();
	myself->player.player_image = picLib->GetImage(picLib,"player_main.gif");
	myself->player.player_image2 = picLib->GetImage(picLib,"player_k.gif");
	myself->test1 = picLib->GetImage(picLib,"test1.gif");
	ONFF_Loading_UpdateStep();
	myself->player.player_show = picLib->GetImage(picLib,"player_show.gif");
	myself->player.player_effect = picLib->GetImage(picLib,"player_effect.gif");
	myself->imgfont = picLib->GetImage(picLib,"font.gif");
	ONFF_Loading_UpdateStep();
	myself->player.playerlifenum = gamestate.gameplayerlife;
	myself->player.playerbombnum = gamestate.gameplayerbomb;
	myself->player.player_Blood_max = 9;
	myself->player.collision_x = 6;
	myself->player.collision_y = 7;
	myself->player.mov_x = 0;
	myself->player.mov_y = 0;
	myself->player.player_Blood_now = myself->player.playerlifenum;
	myself->player.bomb_count_now = myself->player.playerbombnum;	
	myself->player.player_width = 23;
	myself->player.player_height = 19;
	myself->player.collision_width = 11;
	myself->player.collision_height = 5;
	myself->player.const_shot_max = 4;
	myself->player.bomb_count_max = 5;
	myself->player.shot_type = 0;
	myself->player.adjunct_index = 5;
	ONFF_Loading_UpdateStep();
	myself->candy.Bullet = picLib->GetImage(picLib,"Bullet.gif");
	myself->candy.Prize = picLib->GetImage(picLib,"Prize.gif");
	ONFF_Loading_UpdateStep();
	myself->candy.candy_index = 50;	
}

extern gm_s16 CandyCollisionWithItem(ONFF_Map *myself,gm_s16 x, gm_s16 y, gm_s16 width, gm_s16 height, gm_s16 type);
extern void setNewCandy(ONFF_Map *myself,gm_s16 positionx, gm_s16 positiony, gm_s16 angle, gm_s16 type,gm_s16 index);
void Background_Render(ONFF_Map * myself)
{
	gm_u8 col = myself->background.col;
	gm_u8 row = myself->background.row;
	gm_s8 i,j;

			for(i=0;i<col;i++)
			{	
				for(j=-1;j<row;j++)
				{	
					manager.DrawImageEx(myself->picLib->image[myself->background.imgbroud],(myself->tagenum)*32,0,32,32,32*i,32*j+(myself->background.y*2));
				}	
			};
			if(myself->background.scroll == true)
			{
				myself->background.y++;
			}
			myself->background.t = 0;
			myself->background.counter++;
		
}
gm_bool EnemyCollisionWithItem(ONFF_Map * myself,gm_s16 x, gm_s16 y, gm_s16 width, gm_s16 height,
                                   gm_s16 index, gm_s16 type) {
    gm_s16 temp_count = 0;
    gm_s8 result = 0;
    while (temp_count < myself->enemy_index) {
      if (Enemy_Unit[temp_count][3] == 1 && Enemy_Unit[temp_count][1] >= index) {
        if (CdRect2(Enemy_Unit[temp_count][19] + Enemy_Unit[temp_count][36],
                          Enemy_Unit[temp_count][20] + Enemy_Unit[temp_count][37],
						  Enemy_Unit[temp_count][38],Enemy_Unit[temp_count][39], x, y, width, height)) 
        {
          if (type == 0 || (type == 1 && Enemy_Unit[temp_count][40] == 1)) 
		  	{
            if (Enemy_Unit[temp_count][2] == 0 && Enemy_Unit[temp_count][0] > 0) {
              Enemy_Unit[temp_count][0] = Enemy_Unit[temp_count][0] - 1;
              result = result + 1;
            }
            else if (index == -2) {
              Enemy_Unit[temp_count][2] = 0;
            }
          }
        }
      }
      temp_count++;
    }
    if (result > 0) {
      return (true);
    }
    return (false);
  }

void EnemySetAllDeath(ONFF_Map *myself)
{
	int temp_count = 0;
    while (temp_count < myself->enemy_index) {
      if (Enemy_Unit[temp_count][3] == 1) {
        Enemy_Unit[temp_count][0] = 0;
        Enemy_Unit[temp_count][21] = 0;
        Enemy_Unit[temp_count][22] = 0;
      }
      temp_count++;
    }
}

void setNewEnemy(ONFF_Map *myself,gm_s32 imageindex, gm_s32 movindex, gm_s32 shotindex)
{
    gm_s16 temp_count,i;
	
	gm_s16 Type_image0[13][11]  = {
									{2,0,0,0,0,0,0,0,10,10,1},{0,1,0,0,76,50,6,15,64,20,1},{0,2,26,50,25,20,2,8,21,9,1},{0,1,0,70,26,20,2,8,22,9,1},
									{0,2,26,70,25,20,2,8,21,9,1},{0,1,76,0,84,50,0,15,76,30,1},{0,1,104,80,38,30,2,8,34,15,1},{0,1,-95,40,18,70,0,4,18,50,0},{1,1,0,0,23,65,0,0,23,40,1},
									{1,1,23,0,23,65,0,0,23,40,1},{1,1,46,0,23,26,0,0,23,26,1},{1,1,46,26,23,39,0,8,24,15,1},{1,1,69,0,38,65,4,15,30,40,1}
								};
	gm_s16 Type_shot0[11][8] = {
								{0,0,50,0,0,0,0,0},{1,0,25,36,0,0,0,0},{2,0,20,36,30,0,0,0},{6,0,20,0,60,0,0,0},{4,1,30,28,20,5,1,0},{4,0,20,0,90,0,0,0},
								{9,0,60,0,40,0,0,0},{5,1,40,36,20,0,0,0},{9,1,50,0,40,0,0,2},{9,1,50,18,40,0,0,2},{5,0,40,36,30,0,0,0}
							};
	
	#ifdef GAME_240_320 
	gm_s16 Type_mov0[31][26] = {
								{3,0,0,6,3,40,0,0,20,40,0,100,0,40,0,0,20,0,0,0,0,0,2,20,1,3},{3,0,0,6,3,70,0,0,20,70,0,100,0,70,0,0,20,0,0,0,0,0,2,20,1,3},
								{3,0,0,6,3,100,0,0,20,100,0,100,0,100,0,0,20,0,0,0,0,0,2,20,1,3},{3,0,0,6,3,-126,0,0,20,-126,0,100,0,-126,0,0,20,0,0,0,0,0,2,20,1,3},
								{3,0,0,6,3,-96,0,0,20,-96,0,100,0,-96,0,0,20,0,0,0,0,1,2,20,1,3},{3,1,0,1,10,0,76,10,0,20,0,10,0,0,0,10,0,0,0,0,0,0,20,50,0,3},
								{3,1,0,1,10,-56,0,20,0,80,0,20,0,100,0,20,0,0,0,0,0,0,20,50,0,3},{2,0,0,5,3,20,0,0,20,20,0,44,0,0,0,0,0,0,0,0,0,0,2,15,0,3},
								{2,0,0,5,3,50,0,0,20,50,0,44,0,0,0,0,0,0,0,0,0,0,2,15,0,3},{2,0,0,5,3,80,0,0,20,80,0,44,0,0,0,0,0,0,0,0,0,0,2,15,0,3},
								{2,0,0,5,3,110,0,0,20,110,0,44,0,0,0,0,0,0,0,0,0,0,2,15,0,3},{2,0,0,5,3,-116,0,0,20,-116,0,44,0,0,0,0,0,0,0,0,0,0,2,15,0,3},
								{3,1,0,1,10,70,0,0,50,70,0,5,0,40,0,5,0,0,0,0,0,2,40,15,0,4},{2,0,0,2,10,80,0,0,70,80,0,-16,0,0,0,0,0,0,0,0,0,0,14,15,0,3},
								{2,0,0,2,10,-116,0,0,70,-116,0,-16,0,0,0,0,0,0,0,0,0,0,14,15,0,3,},{2,0,0,2,10,30,0,0,70,30,0,-16,0,0,0,0,0,0,0,0,0,0,14,15,0,3},
								{2,0,0,3,10,20,0,0,20,20,0,-16,0,0,0,0,0,0,0,0,0,0,6,15,0,3},{2,0,0,3,10,50,0,0,20,50,0,-16,0,0,0,0,0,0,0,0,0,0,6,15,0,3},
								{2,0,0,3,10,80,0,0,20,80,0,-16,0,0,0,0,0,0,0,0,0,0,6,15,0,3},{2,0,0,3,10,110,0,0,20,110,0,-16,0,0,0,0,0,0,0,0,0,0,6,15,0,3},
								{2,0,0,3,10,-116,0,0,20,-116,0,-16,0,0,0,0,0,0,0,0,0,0,6,15,0,3},{3,1,0,2,10,45,0,0,60,45,0,-126,0,45,0,30,0,0,0,0,0,-1,5,15,0,10},
								{3,1,0,2,10,-86,0,0,60,-86,0,-126,0,-86,0,40,0,0,0,0,0,-1,5,15,0,10},{2,1,120,2,10,106,0,0,16,106,0,75,0,0,0,0,0,0,0,0,0,-1,1,15,0,10},
								{2,1,120,2,1,95,0,0,79,95,0,10,0,0,0,0,0,0,0,0,0,-1,1,15,0,10},{2,1,120,2,1,118,0,0,77,118,0,10,0,0,0,0,0,0,0,0,0,-1,1,15,0,10},
								{2,1,120,2,1,106,0,0,70,106,0,15,0,0,0,0,0,0,0,0,0,3,80,15,0,10},{2,1,120,1,100,99,0,0,0,99,0,10,0,0,0,0,0,0,0,0,0,8,100,15,0,10},
								{2,1,120,1,100,95,0,10,0,76,0,10,7,0,0,0,0,0,0,0,0,4,1,15,0,10},{2,1,120,1,100,118,0,10,0,-119,0,10,7,0,0,0,0,0,0,0,0,4,1,15,0,10},
								{2,1,120,1,100,118,0,15,0,118,0,20,0,0,0,0,0,0,0,0,0,4,1,15,0,10}
							};
	gm_s16 Type_mov1[31][26] = {
								{3,0,0,6,6,40,0,0,20,40,0,100,0,40,0,0,20,0,0,0,0,0,2,20,1,3},
								{3,0,0,6,6,70,0,0,20,70,0,100,0,70,0,0,20,0,0,0,0,0,2,20,1,3},
								{3,0,0,6,6,100,0,0,20,100,0,100,0,100,0,0,20,0,0,0,0,0,2,20,1,3},
								{3,0,0,6,6,-126,0,0,20,-126,0,100,0,-126,0,0,20,0,0,0,0,0,2,20,1,3},
								{3,0,0,6,6,-56,0,0,20,-86,0,100,0,-86,0,0,20,0,0,0,0,1,2,20,1,3},
								{2,0,0,6,6,-56,0,5,0,0,30,5,0,0,0,0,0,0,0,0,0,0,1,20,1,3},
								{2,0,0,6,6,-56,0,25,0,0,30,25,0,0,0,0,0,0,0,0,0,0,1,20,1,3},
								{2,0,0,6,6,-56,0,45,0,0,30,45,0,0,0,0,0,0,0,0,0,0,1,20,1,3},
								{2,0,0,6,6,-56,0,65,0,0,30,65,0,0,0,0,0,0,0,0,0,0,1,20,1,3},
								{3,1,0,1,10,70,0,0,50,70,0,5,0,40,0,5,0,0,0,0,0,2,40,15,0,2},
								{2,0,0,3,6,50,0,0,20,50,0,44,0,0,0,0,0,0,0,0,0,0,4,15,0,3},
								{2,0,0,3,6,80,0,0,20,80,0,44,0,0,0,0,0,0,0,0,0,0,4,15,0,3},
								{2,0,0,3,6,110,0,0,20,110,0,44,0,0,0,0,0,0,0,0,0,0,4,15,0,3},
								{2,0,0,3,6,-116,0,0,20,-116,0,44,0,0,0,0,0,0,0,0,0,0,4,15,0,3},
								{2,0,0,3,6,-86,0,0,20,-86,0,44,0,0,0,0,0,0,0,0,0,0,4,15,0,3},
								{2,0,0,2,10,0,40,20,0,-76,0,20,0,0,0,0,0,0,0,0,0,0,14,15,0,3},
								{2,0,0,2,6,20,0,0,20,20,0,44,0,0,0,0,0,0,0,0,0,0,10,15,0,3},
								{2,0,0,2,6,110,0,0,20,110,0,44,0,0,0,0,0,0,0,0,0,0,10,15,0,3},
								{2,0,0,2,6,-56,0,0,20,-56,0,44,0,0,0,0,0,0,0,0,0,0,10,15,0,3},
								{2,0,0,4,6,50,0,0,20,50,0,44,0,0,0,0,0,0,0,0,0,0,5,15,0,3},
								{2,0,0,4,6,80,0,0,20,80,0,44,0,0,0,0,0,0,0,0,0,0,5,15,0,3},
								{2,0,0,4,6,110,0,0,20,110,0,44,0,0,0,0,0,0,0,0,0,0,5,15,0,3},
								{2,0,0,4,6,-116,0,0,20,-116,0,44,0,0,0,0,0,0,0,0,0,0,5,15,0,3},
								{2,0,0,4,6,-86,0,0,20,-86,0,44,0,0,0,0,0,0,0,0,0,0,5,15,0,3},
								{2,1,120,3,1,124,0,0,72,124,0,5,0,0,0,0,0,0,0,0,0,-1,1,50,0,10},
								{2,1,120,3,1,84,0,0,54,84,0,20,0,0,0,0,0,0,0,0,0,-1,1,50,0,10},
								{2,1,120,3,1,-115,0,0,51,-115,0,20,0,0,0,0,0,0,0,0,0,-1,1,50,0,10},
								{2,1,120,3,1,121,0,0,30,121,0,38,0,0,0,0,0,0,0,0,0,3,80,50,0,10},
								{4,1,2,3,100,94,0,5,0,-116,0,5,0,50,0,5,0,94,0,40,0,8,100,50,0,10},
								{4,1,2,3,100,70,0,27,0,116,0,27,0,26,0,27,0,70,0,62,0,4,1,50,0,10},
								{4,1,2,3,100,111,0,27,0,-99,0,27,0,67,0,27,0,111,0,62,0,4,1,50,0,10}
							};
	gm_s16 Type_mov2[28][26]={
								{3,0,0,6,6,40,0,0,20,40,0,100,0,40,0,0,20,0,0,0,0,0,2,20,1,3},
								{3,0,0,6,6,70,0,0,20,70,0,100,0,70,0,0,20,0,0,0,0,0,2,20,1,3},
								{3,0,0,6,6,100,0,0,20,100,0,100,0,100,0,0,20,0,0,0,0,0,2,20,1,3},
								{3,0,0,6,6,-126,0,0,20,-126,0,100,0,-126,0,0,20,0,0,0,0,0,2,20,1,3},
								{3,0,0,6,6,-96,0,0,20,-96,0,100,0,-96,0,0,20,0,0,0,0,1,2,20,1,3},
								{3,0,1,5,6,0,30,10,0,40,0,70,0,40,0,0,20,0,0,0,0,0,3,1,8,3},
								{3,0,1,5,6,0,30,0,20,80,0,70,0,80,0,0,20,0,0,0,0,0,3,1,10,3},
								{3,0,1,5,6,-36,0,0,20,120,0,70,0,120,0,0,20,0,0,0,0,0,3,1,10,3},
								{3,0,1,5,6,-36,0,10,0,-96,0,70,0,-96,0,0,20,0,0,0,0,0,3,1,8,3},
								{4,0,0,2,6,40,0,0,30,40,0,80,0,40,0,40,0,0,20,40,0,0,8,15,0,3},
								{4,0,0,2,6,-96,0,0,30,-96,0,80,0,-96,0,40,0,-36,0,40,0,0,8,15,0,3},
								{3,1,2,2,10,0,76,10,0,20,0,10,0,0,0,10,0,0,0,0,0,2,16,50,0,3},
								{3,1,2,2,10,-36,0,20,0,100,0,20,0,120,0,20,0,0,0,0,0,0,16,50,0,3},
								{2,0,0,2,6,20,0,0,20,20,0,44,0,0,0,0,0,0,0,0,0,0,16,15,0,3},
								{2,0,0,2,6,80,0,0,20,80,0,44,0,0,0,0,0,0,0,0,0,0,16,15,0,3},
								{2,0,0,2,6,-116,0,0,20,-116,0,44,0,0,0,0,0,0,0,0,0,0,16,15,0,3},
								{2,0,0,1,6,30,0,0,50,30,0,44,0,0,0,0,0,0,0,0,0,0,12,15,0,3},
								{2,0,0,1,6,100,0,0,50,100,0,44,0,0,0,0,0,0,0,0,0,0,12,15,0,3},
								{2,0,0,1,6,-86,0,0,50,-86,0,44,0,0,0,0,0,0,0,0,0,0,12,15,0,3},
								{2,1,120,3,5,101,0,0,82,101,0,0,10,0,0,0,0,0,0,0,0,3,90,50,0,10},
								{2,1,120,3,5,101,0,0,23,101,0,46,0,0,0,0,0,0,0,0,0,-1,1,50,0,10},
								{2,1,120,3,5,111,0,0,79,111,0,0,13,0,0,0,0,0,0,0,0,-1,1,50,0,10},
								{4,1,1,3,100,101,0,38,0,71,0,38,0,35,0,38,0,115,0,38,0,4,1,50,0,10},
								{4,1,1,3,100,101,0,38,0,-125,0,38,0,95,0,38,0,-81,0,38,0,4,1,50,0,10},
								{4,1,1,3,100,106,0,40,0,76,0,70,0,40,0,70,0,120,0,70,0,4,1,50,0,10},
								{4,1,1,3,100,97,0,40,0,127,0,70,0,91,0,70,0,-85,0,70,0,4,1,50,0,10},
								{4,1,1,3,100,101,0,0,10,101,0,20,0,65,0,20,0,-111,0,20,0,8,100,50,0,10},
								{2,1,120,3,5,101,0,0,82,101,0,0,10,0,0,0,0,0,0,0,0,-1,1,50,0,10}
							};
	gm_s16 Type_mov3[34][26]={
								{3,0,0,6,6,40,0,0,20,40,0,100,0,40,0,0,20,0,0,0,0,0,2,20,1,3},
								{3,0,0,6,6,70,0,0,20,70,0,100,0,70,0,0,20,0,0,0,0,0,2,20,1,3},
								{3,0,0,6,6,100,0,0,20,100,0,100,0,100,0,0,20,0,0,0,0,0,2,20,1,3},
								{3,0,0,6,6,-126,0,0,20,-126,0,100,0,-126,0,0,20,0,0,0,0,0,2,20,1,3},
								{3,0,0,6,6,-96,0,0,20,-96,0,100,0,-96,0,0,20,0,0,0,0,1,2,20,1,3},
								{3,0,1,5,6,0,30,10,0,40,0,70,0,40,0,0,20,0,0,0,0,0,3,1,8,3},
								{3,0,1,5,6,0,30,0,20,80,0,70,0,80,0,0,20,0,0,0,0,0,3,1,10,3},
								{3,0,1,5,6,-36,0,0,20,120,0,70,0,120,0,0,20,0,0,0,0,0,3,1,10,3},
								{3,0,1,5,6,-36,0,10,0,-96,0,70,0,-96,0,0,20,0,0,0,0,0,3,1,8,3},
								{2,0,0,6,5,50,0,0,20,50,0,120,0,0,0,0,0,0,0,0,0,0,1,15,0,3},
								{2,0,0,6,5,80,0,0,20,80,0,120,0,0,0,0,0,0,0,0,0,0,1,15,0,3},
								{2,0,0,6,5,110,0,0,0,110,0,-116,0,0,0,0,0,0,0,0,0,0,1,15,0,3},
								{2,0,0,6,5,-116,0,0,0,-116,0,-116,0,0,0,0,0,0,0,0,0,0,1,15,0,3},
								{2,0,0,6,5,-86,0,0,20,-86,0,-116,0,0,0,0,0,0,0,0,0,0,1,15,0,3},
								{3,1,2,2,10,0,76,10,0,20,0,10,0,0,0,10,0,0,0,0,0,0,16,50,0,3},
								{3,1,2,2,10,-56,0,20,0,80,0,20,0,100,0,20,0,0,0,0,0,0,16,50,0,3},
								{2,0,0,2,6,20,0,0,20,20,0,44,0,0,0,0,0,0,0,0,0,0,10,15,0,3},
								{2,0,0,2,6,100,0,0,20,100,0,44,0,0,0,0,0,0,0,0,0,0,10,15,0,3},
								{2,0,0,2,6,-56,0,0,20,-56,0,44,0,0,0,0,0,0,0,0,0,0,10,15,0,3},
								{2,0,0,2,5,5,0,-56,0,5,0,0,50,0,0,0,0,0,0,0,0,0,12,15,0,3},
								{2,0,0,2,5,-76,0,-56,0,-76,0,0,50,0,0,0,0,0,0,0,0,0,12,15,0,3},
								{2,0,0,1,6,30,0,0,50,30,0,44,0,0,0,0,0,0,0,0,0,0,12,15,0,3},
								{2,0,0,1,6,-36,0,0,50,-36,0,-6,0,0,0,0,0,0,0,0,0,0,12,15,0,3},
								{2,1,120,3,5,96,0,0,124,96,0,33,0,0,0,0,0,0,0,0,0,-1,1,50,0,10},
								{2,1,120,3,5,84,0,0,83,84,0,51,0,0,0,0,0,0,0,0,0,-1,1,50,0,10},
								{2,1,120,3,5,-120,0,0,80,-120,0,51,0,0,0,0,0,0,0,0,0,-1,1,50,0,10},
								{2,1,120,3,5,98,0,0,-128,98,0,0,0,0,0,0,0,0,0,0,0,-1,1,50,0,10},
								{2,1,120,3,5,118,0,0,125,118,0,0,0,0,0,0,0,0,0,0,0,-1,1,50,0,10},
								{2,1,120,3,5,99,0,0,68,99,0,54,0,0,0,0,0,0,0,0,0,3,60,50,0,10},
								{4,1,1,3,100,98,0,0,0,65,0,8,0,35,0,8,0,95,0,8,0,4,1,50,0,10},
								{4,1,1,3,100,118,0,0,0,-105,0,8,0,121,0,8,0,-75,0,8,0,4,1,50,0,10},
								{4,1,1,3,100,96,0,33,0,96,0,0,0,66,0,0,0,126,0,0,0,8,80,50,0,10},
								{4,1,1,3,100,84,0,51,0,84,0,18,0,54,0,18,0,114,0,18,0,4,1,50,0,10},
								{4,1,1,3,100,-120,0,51,0,-120,0,18,0,106,0,18,0,-90,0,18,0,4,1,50,0,10}
							};
	#endif
	#ifdef GAME_176_220
	gm_s16 Type_mov0[31][26] = {
								{3,0,0,6,3,20,0,0,20,20,0,100,0,20,0,0,20,0,0,0,0,0,2,20,1,3},
								{3,0,0,6,3,50,0,0,20,50,0,100,0,50,0,0,20,0,0,0,0,0,2,20,1,3},
								{3,0,0,6,3,80,0,0,20,80,0,100,0,80,0,0,20,0,0,0,0,0,2,20,1,3},
								{3,0,0,6,3,110,0,0,20,110,0,100,0,110,0,0,20,0,0,0,0,0,2,20,1,3},
								{3,0,0,6,3,-116,0,0,20,-116,0,100,0,-116,0,0,20,0,0,0,0,1,2,20,1,3},
								{3,1,0,1,10,0,76,10,0,20,0,10,0,0,0,10,0,0,0,0,0,0,20,50,0,3},
								{3,1,0,1,10,-56,0,20,0,80,0,20,0,100,0,20,0,0,0,0,0,0,20,50,0,3},
								{2,0,0,5,3,20,0,0,20,20,0,-36,0,0,0,0,0,0,0,0,0,0,2,15,0,3},
								{2,0,0,5,3,50,0,0,20,50,0,-36,0,0,0,0,0,0,0,0,0,0,2,15,0,3},
								{2,0,0,5,3,80,0,0,20,80,0,-36,0,0,0,0,0,0,0,0,0,0,2,15,0,3},
								{2,0,0,5,3,110,0,0,20,110,0,-36,0,0,0,0,0,0,0,0,0,0,2,15,0,3},
								{2,0,0,5,3,-116,0,0,20,-116,0,-36,0,0,0,0,0,0,0,0,0,0,2,15,0,3},
								{3,1,0,1,10,70,0,0,50,70,0,5,0,40,0,5,0,0,0,0,0,2,40,15,0,4},
								{2,0,0,2,10,80,0,0,70,80,0,-16,0,0,0,0,0,0,0,0,0,0,14,15,0,3},
								{2,0,0,2,10,-116,0,0,70,-116,0,-16,0,0,0,0,0,0,0,0,0,0,14,15,0,3},
								{2,0,0,2,10,30,0,0,70,30,0,-16,0,0,0,0,0,0,0,0,0,0,14,15,0,3},
								{2,0,0,3,10,20,0,0,20,20,0,-16,0,0,0,0,0,0,0,0,0,0,6,15,0,3},
								{2,0,0,3,10,50,0,0,20,50,0,-16,0,0,0,0,0,0,0,0,0,0,6,15,0,3},
								{2,0,0,3,10,80,0,0,20,80,0,-16,0,0,0,0,0,0,0,0,0,0,6,15,0,3},
								{2,0,0,3,10,110,0,0,20,110,0,-16,0,0,0,0,0,0,0,0,0,0,6,15,0,3},
								{2,0,0,3,10,-116,0,0,20,-116,0,-16,0,0,0,0,0,0,0,0,0,0,6,15,0,3},
								{3,1,0,2,10,15,0,0,70,15,0,120,0,15,0,20,0,0,0,0,0,-1,5,15,0,10},
								{3,1,0,2,10,-116,0,0,70,-116,0,120,0,-116,0,30,0,0,0,0,0,-1,5,15,0,10},
								{2,1,120,2,10,76,0,0,26,76,0,65,0,0,0,0,0,0,0,0,0,-1,1,15,0,10},
								{2,1,120,2,1,65,0,0,89,65,0,0,0,0,0,0,0,0,0,0,0,-1,1,15,0,10},
								{2,1,120,2,1,88,0,0,87,88,0,0,0,0,0,0,0,0,0,0,0,-1,1,15,0,10},
								{2,1,120,2,1,76,0,0,80,76,0,5,0,0,0,0,0,0,0,0,0,3,80,15,0,10},
								{2,1,120,1,100,69,0,0,10,69,0,0,0,0,0,0,0,0,0,0,0,8,100,15,0,10},
								{2,1,120,1,100,65,0,0,0,46,0,0,7,0,0,0,0,0,0,0,0,4,1,15,0,10},
								{2,1,120,1,100,88,0,0,0,107,0,0,7,0,0,0,0,0,0,0,0,4,1,15,0,10},
								{2,1,120,1,100,88,0,5,0,88,0,10,0,0,0,0,0,0,0,0,0,4,1,15,0,10}
		};
	gm_s16 Type_mov1[31][26] = {
			{3,0,0,6,6,20,0,0,20,20,0,100,0,20,0,0,20,0,0,0,0,0,2,20,1,3},
			{3,0,0,6,6,50,0,0,20,50,0,100,0,50,0,0,20,0,0,0,0,0,2,20,1,3},
			{3,0,0,6,6,80,0,0,20,80,0,100,0,80,0,0,20,0,0,0,0,0,2,20,1,3},
			{3,0,0,6,6,110,0,0,20,110,0,100,0,110,0,0,20,0,0,0,0,0,2,20,1,3},
			{3,0,0,6,6,-116,0,0,20,-116,0,100,0,-116,0,0,20,0,0,0,0,1,2,20,1,3},
			{2,0,0,6,6,-86,0,5,0,0,30,5,0,0,0,0,0,0,0,0,0,0,1,20,1,3},
			{2,0,0,6,6,-86,0,25,0,0,30,25,0,0,0,0,0,0,0,0,0,0,1,20,1,3},
			{2,0,0,6,6,-86,0,45,0,0,30,45,0,0,0,0,0,0,0,0,0,0,1,20,1,3},
			{2,0,0,6,6,-86,0,65,0,0,30,65,0,0,0,0,0,0,0,0,0,0,1,20,1,3},
			{3,1,0,1,10,70,0,0,50,70,0,5,0,40,0,5,0,0,0,0,0,2,40,15,0,4},
			{2,0,0,3,6,30,0,0,20,30,0,-36,0,0,0,0,0,0,0,0,0,0,4,15,0,3},
			{2,0,0,3,6,50,0,0,20,50,0,-36,0,0,0,0,0,0,0,0,0,0,4,15,0,3},
			{2,0,0,3,6,80,0,0,20,80,0,-36,0,0,0,0,0,0,0,0,0,0,4,15,0,3},
			{2,0,0,3,6,110,0,0,20,110,0,-36,0,0,0,0,0,0,0,0,0,0,4,15,0,3},
			{2,0,0,3,6,-116,0,0,20,-116,0,-36,0,0,0,0,0,0,0,0,0,0,4,15,0,3},
			{2,0,0,2,10,0,40,20,0,-76,0,20,0,0,0,0,0,0,0,0,0,0,14,15,0,3},
			{2,0,0,2,6,20,0,0,20,20,0,-36,0,0,0,0,0,0,0,0,0,0,10,15,0,3},
			{2,0,0,2,6,80,0,0,20,80,0,-36,0,0,0,0,0,0,0,0,0,0,10,15,0,3},
			{2,0,0,2,6,-116,0,0,20,-116,0,-36,0,0,0,0,0,0,0,0,0,0,10,15,0,3},
			{2,0,0,4,6,30,0,0,20,30,0,-36,0,0,0,0,0,0,0,0,0,0,5,15,0,3},
			{2,0,0,4,6,50,0,0,20,50,0,-36,0,0,0,0,0,0,0,0,0,0,5,15,0,3},
			{2,0,0,4,6,80,0,0,20,80,0,-36,0,0,0,0,0,0,0,0,0,0,5,15,0,3},
			{2,0,0,4,6,110,0,0,20,110,0,-36,0,0,0,0,0,0,0,0,0,0,5,15,0,3},
			{2,0,0,4,6,-116,0,0,20,-116,0,-36,0,0,0,0,0,0,0,0,0,0,5,15,0,3},
			{2,1,120,3,1,74,0,0,72,74,0,5,0,0,0,0,0,0,0,0,0,-1,1,50,0,10},
			{2,1,120,3,1,34,0,0,54,34,0,20,0,0,0,0,0,0,0,0,0,-1,1,50,0,10},
			{2,1,120,3,1,91,0,0,51,91,0,20,0,0,0,0,0,0,0,0,0,-1,1,50,0,10},
			{2,1,120,3,1,71,0,0,30,71,0,38,0,0,0,0,0,0,0,0,0,3,80,50,0,10},
			{4,1,2,3,100,74,0,5,0,120,0,5,0,30,0,5,0,74,0,40,0,8,100,50,0,10},
			{4,1,2,3,100,50,0,27,0,96,0,27,0,6,0,27,0,50,0,62,0,4,1,50,0,10},
			{4,1,2,3,100,91,0,27,0,-119,0,27,0,47,0,27,0,91,0,62,0,4,1,50,0,10}
		};
	gm_s16 Type_mov2[28][26] = {
			{3,0,0,6,6,20,0,0,20,20,0,100,0,20,0,0,20,0,0,0,0,0,2,20,1,3},
			{3,0,0,6,6,50,0,0,20,50,0,100,0,50,0,0,20,0,0,0,0,0,2,20,1,3},
			{3,0,0,6,6,80,0,0,20,80,0,100,0,80,0,0,20,0,0,0,0,0,2,20,1,3},
			{3,0,0,6,6,110,0,0,20,110,0,100,0,110,0,0,20,0,0,0,0,0,2,20,1,3},
			{3,0,0,6,6,-116,0,0,20,-116,0,100,0,-116,0,0,20,0,0,0,0,1,2,20,1,3},
			{3,0,1,5,6,0,30,10,0,30,0,70,0,30,0,0,20,0,0,0,0,0,3,1,8,3},
			{3,0,1,5,6,0,30,0,20,60,0,70,0,60,0,0,20,0,0,0,0,0,3,1,10,3},
			{3,0,1,5,6,-76,0,0,20,90,0,70,0,90,0,0,20,0,0,0,0,0,3,1,10,3},
			{3,0,1,5,6,-76,0,10,0,120,0,70,0,120,0,0,20,0,0,0,0,0,3,1,8,3},
			{4,0,0,2,6,40,0,0,30,40,0,80,0,40,0,40,0,0,20,40,0,0,8,15,0,3},
			{4,0,0,2,6,120,0,0,30,120,0,80,0,120,0,40,0,-76,0,40,0,0,8,15,0,3},
			{3,1,2,2,10,0,76,10,0,20,0,10,0,0,0,10,0,0,0,0,0,2,16,50,0,3},
			{3,1,2,2,10,-56,0,20,0,80,0,20,0,100,0,20,0,0,0,0,0,0,16,50,0,3},
			{2,0,0,2,6,20,0,0,20,20,0,-36,0,0,0,0,0,0,0,0,0,0,16,15,0,3},
			{2,0,0,2,6,80,0,0,20,80,0,-36,0,0,0,0,0,0,0,0,0,0,16,15,0,3},
			{2,0,0,2,6,-116,0,0,20,-116,0,-36,0,0,0,0,0,0,0,0,0,0,16,15,0,3},
			{2,0,0,1,6,30,0,0,50,30,0,-36,0,0,0,0,0,0,0,0,0,0,12,15,0,3},
			{2,0,0,1,6,80,0,0,50,80,0,-36,0,0,0,0,0,0,0,0,0,0,12,15,0,3},
			{2,0,0,1,6,-116,0,0,50,-116,0,-36,0,0,0,0,0,0,0,0,0,0,12,15,0,3},
			{2,1,120,3,5,71,0,0,82,71,0,0,10,0,0,0,0,0,0,0,0,3,90,50,0,10},
			{2,1,120,3,5,71,0,0,23,71,0,46,0,0,0,0,0,0,0,0,0,-1,1,50,0,10},
			{2,1,120,3,5,81,0,0,79,81,0,0,13,0,0,0,0,0,0,0,0,-1,1,50,0,10},
			{4,1,1,3,100,71,0,38,0,41,0,38,0,5,0,38,0,85,0,38,0,4,1,50,0,10},
			{4,1,1,3,100,71,0,38,0,101,0,38,0,65,0,38,0,-111,0,38,0,4,1,50,0,10},
			{4,1,1,3,100,76,0,40,0,46,0,70,0,10,0,70,0,90,0,70,0,4,1,50,0,10},
			{4,1,1,3,100,67,0,40,0,97,0,70,0,61,0,70,0,-115,0,70,0,4,1,50,0,10},
			{4,1,1,3,100,71,0,0,10,71,0,20,0,35,0,20,0,115,0,20,0,8,100,50,0,10},
			{2,1,120,3,5,71,0,0,82,71,0,0,10,0,0,0,0,0,0,0,0,-1,1,50,0,10}
		};
	gm_s16 Type_mov3[34][26] = {
			{3,0,0,6,6,20,0,0,20,20,0,100,0,20,0,0,20,0,0,0,0,0,2,20,1,3},
			{3,0,0,6,6,50,0,0,20,50,0,100,0,50,0,0,20,0,0,0,0,0,2,20,1,3},
			{3,0,0,6,6,80,0,0,20,80,0,100,0,80,0,0,20,0,0,0,0,0,2,20,1,3},
			{3,0,0,6,6,110,0,0,20,110,0,100,0,110,0,0,20,0,0,0,0,0,2,20,1,3},
			{3,0,0,6,6,-116,0,0,20,-116,0,100,0,-116,0,0,20,0,0,0,0,1,2,20,1,3},
			{3,0,1,5,6,0,30,10,0,30,0,70,0,30,0,0,20,0,0,0,0,0,3,1,8,3},
			{3,0,1,5,6,0,30,0,20,60,0,70,0,60,0,0,20,0,0,0,0,0,3,1,10,3},
			{3,0,1,5,6,-76,0,0,20,90,0,70,0,90,0,0,20,0,0,0,0,0,3,1,10,3},
			{3,0,1,5,6,-76,0,10,0,120,0,70,0,120,0,0,20,0,0,0,0,0,3,1,8,3},
			{2,0,0,6,5,20,0,0,20,20,0,120,0,0,0,0,0,0,0,0,0,0,1,15,0,3},
			{2,0,0,6,5,50,0,0,20,50,0,120,0,0,0,0,0,0,0,0,0,0,1,15,0,3},
			{2,0,0,6,5,80,0,0,20,80,0,120,0,0,0,0,0,0,0,0,0,0,1,15,0,3},
			{2,0,0,6,5,110,0,0,20,110,0,120,0,0,0,0,0,0,0,0,0,0,1,15,0,3},
			{2,0,0,6,5,-116,0,0,20,-116,0,120,0,0,0,0,0,0,0,0,0,0,1,15,0,3},
			{3,1,2,2,10,0,76,10,0,20,0,10,0,0,0,10,0,0,0,0,0,0,16,50,0,3},
			{3,1,2,2,10,-56,0,20,0,80,0,20,0,100,0,20,0,0,0,0,0,0,16,50,0,3},
			{2,0,0,2,6,20,0,0,20,20,0,-36,0,0,0,0,0,0,0,0,0,0,10,15,0,3},
			{2,0,0,2,6,80,0,0,20,80,0,-36,0,0,0,0,0,0,0,0,0,0,10,15,0,3},
			{2,0,0,2,6,-116,0,0,20,-116,0,-36,0,0,0,0,0,0,0,0,0,0,10,15,0,3},
			{2,0,0,2,5,5,0,-86,0,5,0,0,50,0,0,0,0,0,0,0,0,0,12,15,0,3},
			{2,0,0,2,5,100,0,-86,0,100,0,0,50,0,0,0,0,0,0,0,0,0,12,15,0,3},
			{2,0,0,1,6,30,0,0,50,30,0,-36,0,0,0,0,0,0,0,0,0,0,12,15,0,3},
			{2,0,0,1,6,-116,0,0,50,-116,0,-36,0,0,0,0,0,0,0,0,0,0,12,15,0,3},
			{2,1,120,3,5,66,0,0,104,66,0,33,0,0,0,0,0,0,0,0,0,-1,1,50,0,10},
			{2,1,120,3,5,54,0,0,83,54,0,51,0,0,0,0,0,0,0,0,0,-1,1,50,0,10},
			{2,1,120,3,5,106,0,0,80,106,0,51,0,0,0,0,0,0,0,0,0,-1,1,50,0,10},
			{2,1,120,3,5,68,0,0,-128,68,0,0,0,0,0,0,0,0,0,0,0,-1,1,50,0,10},
			{2,1,120,3,5,88,0,0,125,88,0,0,0,0,0,0,0,0,0,0,0,-1,1,50,0,10},
			{2,1,120,3,5,69,0,0,68,69,0,54,0,0,0,0,0,0,0,0,0,3,60,50,0,10},
			{4,1,1,3,100,68,0,0,0,35,0,8,0,5,0,8,0,65,0,8,0,4,1,50,0,10},
			{4,1,1,3,100,88,0,0,0,121,0,8,0,91,0,8,0,-105,0,8,0,4,1,50,0,10},
			{4,1,1,3,100,66,0,33,0,66,0,0,0,36,0,0,0,96,0,0,0,8,80,50,0,10},
			{4,1,1,3,100,54,0,51,0,54,0,18,0,24,0,18,0,84,0,18,0,4,1,50,0,10},
			{4,1,1,3,100,106,0,51,0,106,0,18,0,76,0,18,0,-120,0,18,0,4,1,50,0,10}
		};
	#endif	
	gm_s16 Type_image1[14][11] = {{2,0,0,0,0,0,0,0,10,10,1},{0,2,26,50,25,20,2,8,21,9,1},{0,2,26,70,25,20,2,8,21,9,1},
						{0,1,0,50,26,20,2,8,22,9,1},
						{0,1,-113,80,18,30,0,0,18,30,0},
						{0,1,76,0,84,50,0,15,76,30,1},
						{0,1,-95,0,40,40,0,0,40,40,1},
						{0,1,76,80,28,30,0,0,28,30,0},
						{0,1,104,80,38,30,2,8,34,15,1},
						{1,1,0,0,28,56,-14,4,58,30,1},
						{1,1,28,0,51,28,0,0,51,28,1},
						{1,1,28,28,51,28,0,0,51,28,1},
						{1,1,79,0,35,39,-24,-9,85,20,1},
						{1,1,79,39,35,17,0,0,35,17,1}
						};
gm_s16 Type_shot1[14][8]={
					{0,0,50,0,0,0,0,0},
					{1,0,20,36,0,0,0,0},
					{2,0,25,36,40,0,0,0},
					{4,1,30,36,30,5,1,0},
					{3,0,20,36,30,0,0,2},
					{4,1,20,0,90,0,0,0},
					{3,0,30,36,30,5,1,0},
					{5,1,50,27,20,0,0,0},
					{8,0,40,20,-19,10,1,1},
					{8,0,40,34,20,10,1,1},
					{3,1,30,36,20,0,0,0},
					{7,0,30,36,30,5,1,0},
					{2,1,40,30,30,2,5,0},
					{2,1,40,26,30,2,5,0}
						};
gm_s16 Type_image2[15][11]={
					{2,0,0,0,34,64,0,33,34,25,0},
					{0,2,26,50,25,20,2,8,21,9,1},
					{0,2,26,70,25,20,2,8,21,9,1},
					{0,2,26,90,25,20,2,8,21,9,1},
					{0,1,76,50,20,30,0,0,20,30,0},
					{0,1,101,50,59,30,10,10,40,12,1},
					{0,1,0,90,26,20,0,0,26,20,0},
					{0,1,-77,63,22,47,0,0,22,40,0},
					{1,1,0,0,34,64,0,33,34,25,0},
					{1,1,47,38,34,26,0,0,34,26,0},
					{1,1,34,0,13,58,0,0,13,58,0},
					{1,1,47,0,33,19,0,0,33,19,0},
					{1,1,47,19,33,19,0,0,33,19,0},
					{1,1,81,0,33,32,0,0,33,32,0},
					{1,1,81,32,33,32,0,0,33,32,0}
};

gm_s16 Type_shot2[17][8]={
					{0,0,50,0,0,0,0,0},
					{1,0,20,36,0,0,0,0},
					{2,0,28,28,50,0,0,0},
					{6,0,25,36,60,0,0,2},
					{2,1,20,28,30,5,2,0},
					{2,0,25,36,30,15,1,0},
					{6,0,25,0,60,0,0,0},
					{3,0,25,36,30,15,1,0},
					{8,0,50,26,30,0,0,2},
					{8,0,50,27,30,0,0,2},
					{8,0,50,28,30,0,0,2},
					{5,1,60,27,40,5,1,0},
					{12,1,60,0,30,0,0,2},
					{3,0,50,30,30,0,0,0},
					{3,0,50,26,30,0,0,0},
					{5,0,40,0,30,0,0,0},
					{5,0,40,18,30,0,0,0}
};
gm_s16 Type_image3[17][11]={
					{2,0,0,0,34,64,0,33,34,25,0},
					{0,2,26,50,25,20,2,8,21,9,1},
					{0,2,26,70,25,20,2,8,21,9,1},
					{0,2,26,90,25,20,2,8,21,9,1},
					{0,1,96,50,5,30,0,0,5,24,1},
					{0,1,101,50,59,30,10,10,40,12,1},
					{0,1,-77,40,22,23,0,0,22,23,0},
					{0,1,0,0,76,50,6,15,64,20,1},
					{0,1,-77,63,22,47,0,0,22,40,0},
					{0,1,76,80,28,30,0,0,28,30,0},
					{0,1,0,90,26,20,0,0,26,20,0},
					{1,1,56,0,45,72,0,20,45,30,0},
					{1,1,40,36,16,36,0,0,16,36,0},
					{1,1,40,0,16,36,0,0,16,36,0},
					{1,1,0,0,20,72,0,0,20,72,0},
					{1,1,20,0,20,72,0,0,20,72,0},
					{1,1,101,0,38,72,0,0,38,20,0}
};

gm_s16 Type_shot3[14][8]={
					{0,0,50,0,0,0,0,0},
					{1,0,30,36,0,0,0,0},
					{3,0,32,28,50,0,0,0},
					{6,0,22,0,60,0,0,0},
					{5,0,20,27,30,0,0,0},
					{1,1,30,36,0,10,1,0},
					{4,0,30,36,30,4,1,0},
					{5,1,30,36,30,0,0,4},
					{2,0,30,36,30,5,2,0},
					{2,0,80,36,30,30,1,0},
					{12,0,50,27,30,0,0,0},
					{8,1,40,22,20,0,0,2},
					{8,1,40,32,-19,0,0,2},
					{3,1,70,27,70,30,1,0}
};
	
	if(myself->tagenum == 0){
		if (Type_image0[imageindex][10] == 0) {
		  temp_count = 0;
		  while (temp_count < myself->enemy_index && Enemy_Unit[temp_count][3] == 1) {
			temp_count++;
		  }
		}
		else {
		  temp_count = myself->enemy_index;
		  i = myself->enemy_index / 2;
		  while (i < myself->enemy_index / 2 * 3) {
			if (Enemy_Unit[i % myself->enemy_index][3] == 0) {
			  temp_count = i % myself->enemy_index;
			  break;
			}
			i++;
		  }
		}
		
		if (temp_count < myself->enemy_index) {
		  Enemy_Unit[temp_count][3] = 1;
		  Enemy_Unit[temp_count][12] = 0;
		  Enemy_Unit[temp_count][11] = Type_image0[imageindex][0];
		  Enemy_Unit[temp_count][6] = Type_image0[imageindex][1];
		  Enemy_Unit[temp_count][9] = unsign(Type_image0[imageindex][2]);
		  Enemy_Unit[temp_count][10] = unsign(Type_image0[imageindex][3]);
		  Enemy_Unit[temp_count][7] = Type_image0[imageindex][4];
		  Enemy_Unit[temp_count][8] = Type_image0[imageindex][5];
		  Enemy_Unit[temp_count][36] = Type_image0[imageindex][6];
		  Enemy_Unit[temp_count][37] = Type_image0[imageindex][7];
		  Enemy_Unit[temp_count][38] = Type_image0[imageindex][8];
		  Enemy_Unit[temp_count][39] = Type_image0[imageindex][9];
		  Enemy_Unit[temp_count][40] = Type_image0[imageindex][10];
		  Enemy_Unit[temp_count][14] = 0;
		  Enemy_Unit[temp_count][16] = 0;
		  Enemy_Unit[temp_count][17] = 0;
		  Enemy_Unit[temp_count][31] = Type_mov0[movindex][0] - 1;
		  Enemy_Unit[temp_count][34] = Type_mov0[movindex][1];
		  Enemy_Unit[temp_count][24] = unsign(Type_mov0[movindex][2]) * 10;
		  Enemy_Unit[temp_count][33] = Type_mov0[movindex][3];
		  Enemy_Unit[temp_count][4] = Type_mov0[movindex][4];
		  Enemy_Unit[temp_count][5] = 0;
		  Enemy_Unit[temp_count][19] = unsign(Type_mov0[movindex][5]) -
			  unsign(Type_mov0[movindex][6]);
		  Enemy_Unit[temp_count][20] = unsign(Type_mov0[movindex][7]) -
			  unsign(Type_mov0[movindex][8]);
		  Enemy_Unit[temp_count][25] = unsign(Type_mov0[movindex][9]) -
			  unsign(Type_mov0[movindex][10]);
		  Enemy_Unit[temp_count][26] = unsign(Type_mov0[movindex][11]) -
			  unsign(Type_mov0[movindex][12]);
		  Enemy_Unit[temp_count][27] = unsign(Type_mov0[movindex][13]) -
			  unsign(Type_mov0[movindex][14]);
		  Enemy_Unit[temp_count][28] = unsign(Type_mov0[movindex][15]) -
			  unsign(Type_mov0[movindex][16]); //??
		  Enemy_Unit[temp_count][29] = unsign(Type_mov0[movindex][17]) -
			  unsign(Type_mov0[movindex][18]);
		  Enemy_Unit[temp_count][30] = unsign(Type_mov0[movindex][19]) -
			  unsign(Type_mov0[movindex][20]);
		  Enemy_Unit[temp_count][23] = 0;
		  Enemy_Unit[temp_count][32] = 0;
		  Enemy_Unit[temp_count][21] = 0;
		  Enemy_Unit[temp_count][22] = 0;
		  Enemy_Unit[temp_count][18] = 3;
		  Enemy_Unit[temp_count][1] = Type_mov0[movindex][21];
		  if (Enemy_Unit[temp_count][1] > 3) {
			Enemy_Unit[temp_count][2] = 1;
			Enemy_Unit[temp_count][1] = Enemy_Unit[temp_count][1] - 5;
		  }
		  else {
			Enemy_Unit[temp_count][2] = 0;
		  }
		  Enemy_Unit[temp_count][0] = Type_mov0[movindex][22];
		  Enemy_Unit[temp_count][13] = Type_mov0[movindex][23];
		  Enemy_Unit[temp_count][15] = Type_mov0[movindex][24];
		  Enemy_Unit[temp_count][35] = Type_mov0[movindex][25] * 100;
		  Enemy_Unit[temp_count][53] = Type_shot0[shotindex][1];
		  Enemy_Unit[temp_count][51] = Type_shot0[shotindex][0];
		  Enemy_Unit[temp_count][52] = 0;
		  Enemy_Unit[temp_count][42] = Type_shot0[shotindex][2];
		  Enemy_Unit[temp_count][41] = Type_shot0[shotindex][2];
		  Enemy_Unit[temp_count][47] = Type_shot0[shotindex][3] * 10;
		  Enemy_Unit[temp_count][48] = Type_shot0[shotindex][4];
		  Enemy_Unit[temp_count][46] = Type_shot0[shotindex][5];
		  Enemy_Unit[temp_count][45] = Type_shot0[shotindex][6];
		  Enemy_Unit[temp_count][44] = Type_shot0[shotindex][6];
		  Enemy_Unit[temp_count][43] = Type_shot0[shotindex][7];
		}
    }
	if(myself->tagenum == 1){
		if (Type_image1[imageindex][10] == 0) {
		  temp_count = 0;
		  while (temp_count < myself->enemy_index && Enemy_Unit[temp_count][3] == 1) {
			temp_count++;
		  }
		}
		else {
		  temp_count = myself->enemy_index;
		  i = myself->enemy_index / 2;
		  while (i < myself->enemy_index / 2 * 3) {
			if (Enemy_Unit[i % myself->enemy_index][3] == 0) {
			  temp_count = i % myself->enemy_index;
			  break;
			}
			i++;
		  }
		}
		if (temp_count < myself->enemy_index) {
		  Enemy_Unit[temp_count][3] = 1;
		  Enemy_Unit[temp_count][12] = 0;
		  Enemy_Unit[temp_count][11] = Type_image1[imageindex][0];
		  Enemy_Unit[temp_count][6] = Type_image1[imageindex][1];
		  Enemy_Unit[temp_count][9] = unsign(Type_image1[imageindex][2]);
		  Enemy_Unit[temp_count][10] = unsign(Type_image1[imageindex][3]);
		  Enemy_Unit[temp_count][7] = Type_image1[imageindex][4];
		  Enemy_Unit[temp_count][8] = Type_image1[imageindex][5];
		  Enemy_Unit[temp_count][36] = Type_image1[imageindex][6];
		  Enemy_Unit[temp_count][37] = Type_image1[imageindex][7];
		  Enemy_Unit[temp_count][38] = Type_image1[imageindex][8];
		  Enemy_Unit[temp_count][39] = Type_image1[imageindex][9];
		  Enemy_Unit[temp_count][40] = Type_image1[imageindex][10];
		  Enemy_Unit[temp_count][14] = 0;
		  Enemy_Unit[temp_count][16] = 0;
		  Enemy_Unit[temp_count][17] = 0;
		  Enemy_Unit[temp_count][31] = Type_mov1[movindex][0] - 1;
		  Enemy_Unit[temp_count][34] = Type_mov1[movindex][1];
		  Enemy_Unit[temp_count][24] = unsign(Type_mov1[movindex][2]) * 10;
		  Enemy_Unit[temp_count][33] = Type_mov1[movindex][3];
		  Enemy_Unit[temp_count][4] = Type_mov1[movindex][4];
		  Enemy_Unit[temp_count][5] = 0;
		  Enemy_Unit[temp_count][19] = unsign(Type_mov1[movindex][5]) -
			  unsign(Type_mov1[movindex][6]);
		  Enemy_Unit[temp_count][20] = unsign(Type_mov1[movindex][7]) -
			  unsign(Type_mov1[movindex][8]);
		  Enemy_Unit[temp_count][25] = unsign(Type_mov1[movindex][9]) -
			  unsign(Type_mov1[movindex][10]);
		  Enemy_Unit[temp_count][26] = unsign(Type_mov1[movindex][11]) -
			  unsign(Type_mov1[movindex][12]);
		  Enemy_Unit[temp_count][27] = unsign(Type_mov1[movindex][13]) -
			  unsign(Type_mov1[movindex][14]);
		  Enemy_Unit[temp_count][28] = unsign(Type_mov1[movindex][15]) -
			  unsign(Type_mov1[movindex][16]); //??
		  Enemy_Unit[temp_count][29] = unsign(Type_mov1[movindex][17]) -
			  unsign(Type_mov1[movindex][18]);
		  Enemy_Unit[temp_count][30] = unsign(Type_mov1[movindex][19]) -
			  unsign(Type_mov1[movindex][20]);
		  Enemy_Unit[temp_count][23] = 0;
		  Enemy_Unit[temp_count][32] = 0;
		  Enemy_Unit[temp_count][21] = 0;
		  Enemy_Unit[temp_count][22] = 0;
		  Enemy_Unit[temp_count][18] = 3;
		  Enemy_Unit[temp_count][1] = Type_mov1[movindex][21];
		  if (Enemy_Unit[temp_count][1] > 3) {
			Enemy_Unit[temp_count][2] = 1;
			Enemy_Unit[temp_count][1] = Enemy_Unit[temp_count][1] - 5;
		  }
		  else {
			Enemy_Unit[temp_count][2] = 0;
		  }
		  Enemy_Unit[temp_count][0] = Type_mov1[movindex][22];
		  Enemy_Unit[temp_count][13] = Type_mov1[movindex][23];
		  Enemy_Unit[temp_count][15] = Type_mov1[movindex][24];
		  Enemy_Unit[temp_count][35] = Type_mov1[movindex][25] * 100;
		  Enemy_Unit[temp_count][53] = Type_shot1[shotindex][1];
		  Enemy_Unit[temp_count][51] = Type_shot1[shotindex][0];
		  Enemy_Unit[temp_count][52] = 0;
		  Enemy_Unit[temp_count][42] = Type_shot1[shotindex][2];
		  Enemy_Unit[temp_count][41] = Type_shot1[shotindex][2];
		  Enemy_Unit[temp_count][47] = Type_shot1[shotindex][3] * 10;
		  Enemy_Unit[temp_count][48] = Type_shot1[shotindex][4];
		  Enemy_Unit[temp_count][46] = Type_shot1[shotindex][5];
		  Enemy_Unit[temp_count][45] = Type_shot1[shotindex][6];
		  Enemy_Unit[temp_count][44] = Type_shot1[shotindex][6];
		  Enemy_Unit[temp_count][43] = Type_shot1[shotindex][7];
		}
    }

	if(myself->tagenum == 2){
		if (Type_image2[imageindex][10] == 0) {
		  temp_count = 0;
		  while (temp_count < myself->enemy_index && Enemy_Unit[temp_count][3] == 1) {
			temp_count++;
		  }
		}
		else {
		  temp_count = myself->enemy_index;
		  i = myself->enemy_index / 2;
		  while (i < myself->enemy_index / 2 * 3) {
			if (Enemy_Unit[i % myself->enemy_index][3] == 0) {
			  temp_count = i % myself->enemy_index;
			  break;
			}
			i++;
		  }
		}
		if (temp_count < myself->enemy_index) {
		  Enemy_Unit[temp_count][3] = 1;
		  Enemy_Unit[temp_count][12] = 0;
		  Enemy_Unit[temp_count][11] = Type_image2[imageindex][0];
		  Enemy_Unit[temp_count][6] = Type_image2[imageindex][1];
		  Enemy_Unit[temp_count][9] = unsign(Type_image2[imageindex][2]);
		  Enemy_Unit[temp_count][10] = unsign(Type_image2[imageindex][3]);
		  Enemy_Unit[temp_count][7] = Type_image2[imageindex][4];
		  Enemy_Unit[temp_count][8] = Type_image2[imageindex][5];
		  Enemy_Unit[temp_count][36] = Type_image2[imageindex][6];
		  Enemy_Unit[temp_count][37] = Type_image2[imageindex][7];
		  Enemy_Unit[temp_count][38] = Type_image2[imageindex][8];
		  Enemy_Unit[temp_count][39] = Type_image2[imageindex][9];
		  Enemy_Unit[temp_count][40] = Type_image2[imageindex][10];
		  Enemy_Unit[temp_count][14] = 0;
		  Enemy_Unit[temp_count][16] = 0;
		  Enemy_Unit[temp_count][17] = 0;
		  Enemy_Unit[temp_count][31] = Type_mov2[movindex][0] - 1;
		  Enemy_Unit[temp_count][34] = Type_mov2[movindex][1];
		  Enemy_Unit[temp_count][24] = unsign(Type_mov2[movindex][2]) * 10;
		  Enemy_Unit[temp_count][33] = Type_mov2[movindex][3];
		  Enemy_Unit[temp_count][4] = Type_mov2[movindex][4];
		  Enemy_Unit[temp_count][5] = 0;
		  Enemy_Unit[temp_count][19] = unsign(Type_mov2[movindex][5]) -
			  unsign(Type_mov2[movindex][6]);
		  Enemy_Unit[temp_count][20] = unsign(Type_mov2[movindex][7]) -
			  unsign(Type_mov2[movindex][8]);
		  Enemy_Unit[temp_count][25] = unsign(Type_mov2[movindex][9]) -
			  unsign(Type_mov2[movindex][10]);
		  Enemy_Unit[temp_count][26] = unsign(Type_mov2[movindex][11]) -
			  unsign(Type_mov2[movindex][12]);
		  Enemy_Unit[temp_count][27] = unsign(Type_mov2[movindex][13]) -
			  unsign(Type_mov2[movindex][14]);
		  Enemy_Unit[temp_count][28] = unsign(Type_mov2[movindex][15]) -
			  unsign(Type_mov2[movindex][16]); //??
		  Enemy_Unit[temp_count][29] = unsign(Type_mov2[movindex][17]) -
			  unsign(Type_mov2[movindex][18]);
		  Enemy_Unit[temp_count][30] = unsign(Type_mov2[movindex][19]) -
			  unsign(Type_mov2[movindex][20]);
		  Enemy_Unit[temp_count][23] = 0;
		  Enemy_Unit[temp_count][32] = 0;
		  Enemy_Unit[temp_count][21] = 0;
		  Enemy_Unit[temp_count][22] = 0;
		  Enemy_Unit[temp_count][18] = 3;
		  Enemy_Unit[temp_count][1] = Type_mov2[movindex][21];
		  if (Enemy_Unit[temp_count][1] > 3) {
			Enemy_Unit[temp_count][2] = 1;
			Enemy_Unit[temp_count][1] = Enemy_Unit[temp_count][1] - 5;
		  }
		  else {
			Enemy_Unit[temp_count][2] = 0;
		  }
		  Enemy_Unit[temp_count][0] = Type_mov2[movindex][22];
		  Enemy_Unit[temp_count][13] = Type_mov2[movindex][23];
		  Enemy_Unit[temp_count][15] = Type_mov2[movindex][24];
		  Enemy_Unit[temp_count][35] = Type_mov2[movindex][25] * 100;
		  Enemy_Unit[temp_count][53] = Type_shot2[shotindex][1];
		  Enemy_Unit[temp_count][51] = Type_shot2[shotindex][0];
		  Enemy_Unit[temp_count][52] = 0;
		  Enemy_Unit[temp_count][42] = Type_shot2[shotindex][2];
		  Enemy_Unit[temp_count][41] = Type_shot2[shotindex][2];
		  Enemy_Unit[temp_count][47] = Type_shot2[shotindex][3] * 10;
		  Enemy_Unit[temp_count][48] = Type_shot2[shotindex][4];
		  Enemy_Unit[temp_count][46] = Type_shot2[shotindex][5];
		  Enemy_Unit[temp_count][45] = Type_shot2[shotindex][6];
		  Enemy_Unit[temp_count][44] = Type_shot2[shotindex][6];
		  Enemy_Unit[temp_count][43] = Type_shot2[shotindex][7];
		}
    }
	if(myself->tagenum == 3){
		if (Type_image2[imageindex][10] == 0) {
		  temp_count = 0;
		  while (temp_count < myself->enemy_index && Enemy_Unit[temp_count][3] == 1) {
			temp_count++;
		  }
		}
		else {
		  temp_count = myself->enemy_index;
		  i = myself->enemy_index / 2;
		  while (i < myself->enemy_index / 2 * 3) {
			if (Enemy_Unit[i % myself->enemy_index][3] == 0) {
			  temp_count = i % myself->enemy_index;
			  break;
			}
			i++;
		  }
		}
		if (temp_count < myself->enemy_index) {
		  Enemy_Unit[temp_count][3] = 1;
		  Enemy_Unit[temp_count][12] = 0;
		  Enemy_Unit[temp_count][11] = Type_image3[imageindex][0];
		  Enemy_Unit[temp_count][6] = Type_image3[imageindex][1];
		  Enemy_Unit[temp_count][9] = unsign(Type_image3[imageindex][2]);
		  Enemy_Unit[temp_count][10] = unsign(Type_image3[imageindex][3]);
		  Enemy_Unit[temp_count][7] = Type_image3[imageindex][4];
		  Enemy_Unit[temp_count][8] = Type_image3[imageindex][5];
		  Enemy_Unit[temp_count][36] = Type_image3[imageindex][6];
		  Enemy_Unit[temp_count][37] = Type_image3[imageindex][7];
		  Enemy_Unit[temp_count][38] = Type_image3[imageindex][8];
		  Enemy_Unit[temp_count][39] = Type_image3[imageindex][9];
		  Enemy_Unit[temp_count][40] = Type_image3[imageindex][10];
		  Enemy_Unit[temp_count][14] = 0;
		  Enemy_Unit[temp_count][16] = 0;
		  Enemy_Unit[temp_count][17] = 0;
		  Enemy_Unit[temp_count][31] = Type_mov3[movindex][0] - 1;
		  Enemy_Unit[temp_count][34] = Type_mov3[movindex][1];
		  Enemy_Unit[temp_count][24] = unsign(Type_mov3[movindex][2]) * 10;
		  Enemy_Unit[temp_count][33] = Type_mov3[movindex][3];
		  Enemy_Unit[temp_count][4] = Type_mov3[movindex][4];
		  Enemy_Unit[temp_count][5] = 0;
		  Enemy_Unit[temp_count][19] = unsign(Type_mov3[movindex][5]) -
			  unsign(Type_mov3[movindex][6]);
		  Enemy_Unit[temp_count][20] = unsign(Type_mov3[movindex][7]) -
			  unsign(Type_mov3[movindex][8]);
		  Enemy_Unit[temp_count][25] = unsign(Type_mov3[movindex][9]) -
			  unsign(Type_mov3[movindex][10]);
		  Enemy_Unit[temp_count][26] = unsign(Type_mov3[movindex][11]) -
			  unsign(Type_mov3[movindex][12]);
		  Enemy_Unit[temp_count][27] = unsign(Type_mov3[movindex][13]) -
			  unsign(Type_mov3[movindex][14]);
		  Enemy_Unit[temp_count][28] = unsign(Type_mov3[movindex][15]) -
			  unsign(Type_mov3[movindex][16]); //??
		  Enemy_Unit[temp_count][29] = unsign(Type_mov3[movindex][17]) -
			  unsign(Type_mov3[movindex][18]);
		  Enemy_Unit[temp_count][30] = unsign(Type_mov3[movindex][19]) -
			  unsign(Type_mov3[movindex][20]);
		  Enemy_Unit[temp_count][23] = 0;
		  Enemy_Unit[temp_count][32] = 0;
		  Enemy_Unit[temp_count][21] = 0;
		  Enemy_Unit[temp_count][22] = 0;
		  Enemy_Unit[temp_count][18] = 3;
		  Enemy_Unit[temp_count][1] = Type_mov3[movindex][21];
		  if (Enemy_Unit[temp_count][1] > 3) {
			Enemy_Unit[temp_count][2] = 1;
			Enemy_Unit[temp_count][1] = Enemy_Unit[temp_count][1] - 5;
		  }
		  else {
			Enemy_Unit[temp_count][2] = 0;
		  }
		  Enemy_Unit[temp_count][0] = Type_mov3[movindex][22];
		  Enemy_Unit[temp_count][13] = Type_mov3[movindex][23];
		  Enemy_Unit[temp_count][15] = Type_mov3[movindex][24];
		  Enemy_Unit[temp_count][35] = Type_mov3[movindex][25] * 100;
		  Enemy_Unit[temp_count][53] = Type_shot3[shotindex][1];
		  Enemy_Unit[temp_count][51] = Type_shot3[shotindex][0];
		  Enemy_Unit[temp_count][52] = 0;
		  Enemy_Unit[temp_count][42] = Type_shot3[shotindex][2];
		  Enemy_Unit[temp_count][41] = Type_shot3[shotindex][2];
		  Enemy_Unit[temp_count][47] = Type_shot3[shotindex][3] * 10;
		  Enemy_Unit[temp_count][48] = Type_shot3[shotindex][4];
		  Enemy_Unit[temp_count][46] = Type_shot3[shotindex][5];
		  Enemy_Unit[temp_count][45] = Type_shot3[shotindex][6];
		  Enemy_Unit[temp_count][44] = Type_shot3[shotindex][6];
		  Enemy_Unit[temp_count][43] = Type_shot3[shotindex][7];
		}
    }
}

void drawEnemy(ONFF_Map * myself, gm_s16 temp_count){
	if (Enemy_Unit[temp_count][11] < 2) {
		gm_s16 temp_dis_width = - (Enemy_Unit[temp_count][12] * Enemy_Unit[temp_count][7]);
		myself->picLib->DrawRegionEx(myself->picLib,myself->enemy[Enemy_Unit[temp_count][11]],
		Enemy_Unit[temp_count][19],Enemy_Unit[temp_count][20],
        Enemy_Unit[temp_count][9] - temp_dis_width, Enemy_Unit[temp_count][10],
		Enemy_Unit[temp_count][7], Enemy_Unit[temp_count][8],true,0);

      if (Enemy_Unit[temp_count][0] <= 0 && Enemy_Unit[temp_count][18] < 3) 
	  { 
		myself->picLib->DrawRegionEx(myself->picLib,myself->bomb,
			            Enemy_Unit[temp_count][19] + Enemy_Unit[temp_count][36] + Enemy_Unit[temp_count][16]-15,
						Enemy_Unit[temp_count][20] + Enemy_Unit[temp_count][37] + Enemy_Unit[temp_count][17],
						Enemy_Unit[temp_count][18] * 40,0,40,30,true,0);
      }
	}
}
void Enemy_Render(ONFF_Map * myself)
{
	gm_s16 temp_count = 0;
	while (temp_count < myself->enemy_index) {
		
      if (Enemy_Unit[temp_count][3] == 1 && Enemy_Unit[temp_count][2] == 0) {
        drawEnemy(myself,temp_count);
	  }
      temp_count++;
    }
	temp=manager_my->formatString("%d",myself->score);
	manager.DrawString(temp,20,SCREEN_WIDTH- 40,1,0xffff00);
}

void EnemySetStage(ONFF_Map * myself) {
    gm_s16 temp_count;
	temp_count = 0;
    while (temp_count < myself->enemy_index) {
      Enemy_Unit[temp_count][3] = 0;
      temp_count++;
    }

}

void EnemyNextImage(ONFF_Map *myself,gm_s16 temp_count)//nextImage(temp_count);
{
		if (Enemy_Unit[temp_count][15] > 0) {
			if (Enemy_Unit[temp_count][1] >= 0
					&& Enemy_Unit[temp_count][14] == Enemy_Unit[temp_count][13]) {
				Enemy_Unit[temp_count][12] = (Enemy_Unit[temp_count][12] + 1)%Enemy_Unit[temp_count][6];
				Enemy_Unit[temp_count][15]--;
				Enemy_Unit[temp_count][14] = 0;
			}
			else {
				Enemy_Unit[temp_count][14]++;
			}
		}
}
void EnemyNextPosition(ONFF_Map * myself,gm_s16 temp_count)//void nextPosition
{	
		if (Enemy_Unit[temp_count][11] < 2) {
			if (Enemy_Unit[temp_count][0] > 0) 
			{
				EnemyNextImage(myself,temp_count);
			} 
			else 
			{
				if (Enemy_Unit[temp_count][18] == 3) 
				{
					if (Random(0,10) > 5|| Enemy_Unit[temp_count][5] == 0)
					{
						Enemy_Unit[temp_count][16] = Random(0,Enemy_Unit[temp_count][38]-1) - 20;
						Enemy_Unit[temp_count][17] = Random(0,Enemy_Unit[temp_count][39]-1) - 15;
						Enemy_Unit[temp_count][18] = 0;
					}
				} 
				else 
				{
					Enemy_Unit[temp_count][18]++;
				}
			}
		}
		if (Enemy_Unit[temp_count][35] > 0) 
		{
			if (Enemy_Unit[temp_count][31] != 0) 
			{
				Enemy_Unit[temp_count][21] = adjuctMap(
				Enemy_Unit[temp_count][19],
				Enemy_Unit[temp_count][Enemy_Unit[temp_count][32] * 2 + 25],
				Enemy_Unit[temp_count][33]);
				Enemy_Unit[temp_count][22] = adjuctMap(Enemy_Unit[temp_count][20],
											 			Enemy_Unit[temp_count][Enemy_Unit[temp_count][32] * 2 + 26],
														Enemy_Unit[temp_count][33]);
				if (Enemy_Unit[temp_count][21] == 0 && Enemy_Unit[temp_count][22] == 0) 
				{
					if (Enemy_Unit[temp_count][23] == Enemy_Unit[temp_count][24]) 
					{
						if (Enemy_Unit[temp_count][34] == 0) 
						{
							Enemy_Unit[temp_count][32] = Enemy_Unit[temp_count][32] + 1;
							if (Enemy_Unit[temp_count][32] == Enemy_Unit[temp_count][31]) 
							{
								Enemy_Unit[temp_count][3] = 0;
							}
						} 
						else 
						{
							Enemy_Unit[temp_count][32] = (Enemy_Unit[temp_count][32] + 1) % Enemy_Unit[temp_count][31];
						}
						Enemy_Unit[temp_count][23] = 0;
					} 
					else
					{
						Enemy_Unit[temp_count][23]++;
					}
				}
			}
			Enemy_Unit[temp_count][35]--;
		} 
		else 
		{
			Enemy_Unit[temp_count][42] = -1;
			if (Enemy_Unit[temp_count][1] == 3) 
			{
				Enemy_Unit[temp_count][0] = 0;
			} 
			else 
			{
				Enemy_Unit[temp_count][21] = 0;
				Enemy_Unit[temp_count][22] = 4;
			}
		}
			Enemy_Unit[temp_count][19] = Enemy_Unit[temp_count][19]
					+ Enemy_Unit[temp_count][21];
			Enemy_Unit[temp_count][20] = Enemy_Unit[temp_count][20]
					+ Enemy_Unit[temp_count][22];
			if (Enemy_Unit[temp_count][20] > SCREEN_HEIGHT) 
			{
				Enemy_Unit[temp_count][3] = 0;
			}
}

void EnemyChackShot(ONFF_Map * myself, gm_s16 x, gm_s16 y, gm_s16 temp_count) {

		if (Enemy_Unit[temp_count][0] > 0) {
			if (Enemy_Unit[temp_count][42] == 0) {
				if (Enemy_Unit[temp_count][52] == 0) {
					if (Enemy_Unit[temp_count][47] != 360) {
						Enemy_Unit[temp_count][49] = Enemy_Unit[temp_count][47];
					} else {
						Enemy_Unit[temp_count][49] = atan(x - Enemy_Unit[temp_count][19] - Enemy_Unit[temp_count][7] / 2,
								Enemy_Unit[temp_count][20] + Enemy_Unit[temp_count][8] / 4 * 3 - y);
					}
					Enemy_Unit[temp_count][49] = Enemy_Unit[temp_count][49] - Enemy_Unit[temp_count][51] / 2
							* Enemy_Unit[temp_count][48];
					if (Enemy_Unit[temp_count][49] < 0) {
						Enemy_Unit[temp_count][49] = Enemy_Unit[temp_count][49] + 360;
					}
				}
				while (Enemy_Unit[temp_count][42] == 0
						&& Enemy_Unit[temp_count][52] < Enemy_Unit[temp_count][51]) {
					Enemy_Unit[temp_count][50] = Enemy_Unit[temp_count][49]
							+ Enemy_Unit[temp_count][52]
							* Enemy_Unit[temp_count][48];
					if (Enemy_Unit[temp_count][50] >= 360) {
						Enemy_Unit[temp_count][50] = Enemy_Unit[temp_count][50] - 360;
					}
					setNewCandy(myself,Enemy_Unit[temp_count][19] + Enemy_Unit[temp_count][7] / 2,
							Enemy_Unit[temp_count][20] + Enemy_Unit[temp_count][8] / 4 * 3,
							Enemy_Unit[temp_count][50], 0,Enemy_Unit[temp_count][53]);
							Enemy_Unit[temp_count][52]++;
							Enemy_Unit[temp_count][42] = Enemy_Unit[temp_count][43];
				}
				if (Enemy_Unit[temp_count][52] == Enemy_Unit[temp_count][51]) {
					Enemy_Unit[temp_count][52] = 0;
					if (Enemy_Unit[temp_count][45] == 0) {
						Enemy_Unit[temp_count][42] = Enemy_Unit[temp_count][41];
						Enemy_Unit[temp_count][45] = Enemy_Unit[temp_count][44];
					}
					else {
						Enemy_Unit[temp_count][45]--;
						Enemy_Unit[temp_count][42] = Enemy_Unit[temp_count][46];
					}
				}
			}
			else {
				Enemy_Unit[temp_count][42]--;
			}
		}
	}


void EnemyChackDeathFade(ONFF_Map * myself,gm_s16 temp_count) {//private void chackDeathFade(int temp_count, Candy c)
		if (Enemy_Unit[temp_count][5] == 0) {
			myself->score = myself->score + (Enemy_Unit[temp_count][51] + 1) * 2;
			Enemy_Unit[temp_count][31] = 0;
			if (Enemy_Unit[temp_count][1] >= 0) {
				EnemyCollisionWithItem(myself,Enemy_Unit[temp_count][19],Enemy_Unit[temp_count][20], 
					Enemy_Unit[temp_count][7],Enemy_Unit[temp_count][8], -1, 0);
			}
			if (Enemy_Unit[temp_count][1] == 3) {
				EnemyCollisionWithItem(myself,0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, -2, 0);
			}
			Enemy_Unit[temp_count][31] = 0;
			Enemy_Unit[temp_count][21] = 0;
			Enemy_Unit[temp_count][22] = 0;
			if (Enemy_Unit[temp_count][1] > 0 && Enemy_Unit[temp_count][1] < 3) {
				setNewCandy(myself,Enemy_Unit[temp_count][19]
						+ Enemy_Unit[temp_count][7] / 2,
						Enemy_Unit[temp_count][20] +Enemy_Unit[temp_count][8]
								/ 2, 80 + Random(0,59), 2,
						Enemy_Unit[temp_count][1] + 3);
			}
		}
		if (Enemy_Unit[temp_count][5] == Enemy_Unit[temp_count][4]) {
			Enemy_Unit[temp_count][3] = 0;
		} else {
			Enemy_Unit[temp_count][5]++;
		}
}

gm_bool EnemyRun(ONFF_Map * myself, gm_s16 x, gm_s16 y) {
	gm_s16 temp_count = 0;
	gm_s16 result = 1;
	while (temp_count < myself->enemy_index) {
		if (Enemy_Unit[temp_count][3] == 1) {
			if (Enemy_Unit[temp_count][2] == 0) {
				EnemyNextPosition(myself,temp_count);
				if (Enemy_Unit[temp_count][0] > 0) {
					EnemyChackShot(myself, x, y, temp_count);
					if (Enemy_Unit[temp_count][1] >=0) {
						Enemy_Unit[temp_count][0] = Enemy_Unit[temp_count][0]
								- CandyCollisionWithItem(myself,
												Enemy_Unit[temp_count][19]
														+ Enemy_Unit[temp_count][36],
												Enemy_Unit[temp_count][20]
														+ Enemy_Unit[temp_count][37],
												Enemy_Unit[temp_count][38],
												Enemy_Unit[temp_count][39],1);
					}
				}
				else {
					EnemyChackDeathFade(myself,temp_count);
				}
			}
			if (Enemy_Unit[temp_count][1] == 3) {
				if (Enemy_Unit[temp_count][0] > 0) {
					result = 0;
				} else {
					result = result * 2;
				}
			}
		}
		temp_count++;
	}
	if (result > 1) {
		return (true);
	} else {
		return (false);
	}
}
const void setFade(ONFF_Map * myself,gm_s16  control)
{
	if(control == 1)
	{
		myself->player.mov_y = 0;
      	myself->player.mov_x = 0;
      	myself->player.controlable = true;
	
	}
	else
	{
	  myself->player.mov_y = control;
      myself->player.mov_x = 0;
      myself->player.controlable = false;
      myself->player.player_cur = 0;
	}
}

const void setMoive(ONFF_Map * myself,gm_s16 index) {
    adjunct[index][0] = 1;
    adjunct[index][2] = 0;
    adjunct[index][4] = 0;
    adjunct[index][5] = myself->player.position_x;
    adjunct[index][6] = myself->player.position_y;
  }

void keyPressed(ONFF_Map * myself) 
{
    if(myself->player.controlable)
		{
        if(extOldGameManager->IsKeyDown(MF_KEY_0)&&myself->player.bomb_count_now>0) 
		{
            myself->player.bombshot=10;
            setMoive(myself,0);
            myself->player.bomb_count_now--;
        }
        if(extOldGameManager->IsKeyDown(MF_KEY_DOWN|MF_KEY_8)||extOldGameManager->IsKeyHold(MF_KEY_DOWN|MF_KEY_8))
		{
            if(myself->player.mov_x==0) myself->player.player_cur=0;
             myself->player.mov_y = 4;
        }
        if(extOldGameManager->IsKeyDown(MF_KEY_LEFT|MF_KEY_7) ||extOldGameManager->IsKeyHold(MF_KEY_LEFT|MF_KEY_7))
		{
             myself->player.player_cur=2;
             myself->player.mov_x = -4;
        }
        if(extOldGameManager->IsKeyDown(MF_KEY_UP|MF_KEY_5) || extOldGameManager->IsKeyHold(MF_KEY_UP|MF_KEY_5))
		{
             if(myself->player.mov_x==0) myself->player.player_cur=0;
             myself->player.mov_y = -4;
        }
        if(extOldGameManager->IsKeyDown(MF_KEY_RIGHT|MF_KEY_9) || extOldGameManager->IsKeyHold(MF_KEY_RIGHT|MF_KEY_9))
		{
             myself->player.player_cur=1;
             myself->player.mov_x = 4;
        }
    }
}

void keyReleased(ONFF_Map *myself) {
        if(myself->player.controlable){
          if(!extOldGameManager->IsKeyDown(MF_KEY_DOWN|MF_KEY_8)){
             if(myself->player.mov_y==4){
             myself->player.mov_y=0;
             }
        }
        if(!extOldGameManager->IsKeyDown(MF_KEY_LEFT|MF_KEY_7)){
            if(myself->player.mov_x==-4){
             myself->player.player_cur=0;
             myself->player.mov_x=0;
            }
        }
        if(!extOldGameManager->IsKeyDown(MF_KEY_UP|MF_KEY_5)){
             if(myself->player.mov_y==-4){
             myself->player.mov_y=0;
             }
        }
        if(!extOldGameManager->IsKeyDown(MF_KEY_RIGHT|MF_KEY_9)){
            if(myself->player.mov_x==4){
             myself->player.player_cur=0;
             myself->player.mov_x=0;
            }
        }
      }
    }

void setNewPlayer(ONFF_Map * myself)
{
	myself->player.mov_x = 0;
	myself->player.mov_y = 0;
	myself->player.position_x = SCREEN_WIDTH/ 2 - myself->player.player_width / 2;
	myself->player.position_y = SCREEN_HEIGHT + myself->player.player_height;
	myself->player.player_cur = 0;
	myself->player.player_cur_count = 0;
	myself->player.const_shot_now = 0;
	myself->player.bossdown = false;
	myself->player.interlude = true;
	setFade( myself,-6);
    myself->player.player_control = 10;
    myself->player.bombshot = 0;
    myself->player.shot_type = 0;
    myself->player.const_unbeatable = 30;
    setMoive(myself,4);
}

const void PlayerNextPosition(ONFF_Map * myself)
{
	if (myself->player.player_Blood_now > 0) {
      if (myself->player.controlable == true) {
        if (myself->player.position_x + myself->player.mov_x < SCREEN_WIDTH- 23 &&
            myself->player.position_x + myself->player.mov_x > 0) {
          myself->player.position_x += myself->player.mov_x;
        }
        if (myself->player.position_y + myself->player.mov_y < SCREEN_HEIGHT- 19 &&
            myself->player.position_y + myself->player.mov_y > 0) {
          myself->player.position_y += myself->player.mov_y;
        }
      }
      else {
        myself->player.position_x += myself->player.mov_x;
        myself->player.position_y += myself->player.mov_y;
      }
      myself->player.player_cur_count = (myself->player.player_cur_count + 1) % 2;
	  
    }
}


const void nextEffect(ONFF_Map * myself)
{
	gm_s16 temp_count=0;
    while (temp_count < myself->player.adjunct_index) {
      if (adjunct[temp_count][0] == 1) {
        adjunct[temp_count][4] = adjunct[temp_count][4] + 1;
        adjunct[temp_count][2] = adjunct[temp_count][2] +
            adjunct[temp_count][4] / adjunct[temp_count][3];
        adjunct[temp_count][4] = adjunct[temp_count][4] % adjunct[temp_count][3];
        if (adjunct[temp_count][2] == adjunct[temp_count][1]) {
          adjunct[temp_count][0] = 0;
        }
      }
      temp_count++;
    }
}

const void setTitle(ONFF_Map * myself,gm_s16 type){
	myself->player.showtitle = true;
    myself->player.title_type = type;
    myself->player.title_stay = (type + 1) * 15;
    myself->player.title_x = -10;
    myself->player.title_y = -6;
}
const void nextTitle(ONFF_Map * myself)
{
	myself->player.roll_count++;
		if (myself->player.roll_count == 2) {
		  setTitle(myself,0);
		}
		if (myself->player.roll_count == 1100) {
		  setTitle(myself,1);
		}
		if (myself->player.showtitle) {
		  if (myself->player.title_type == 0) {
			if (myself->player.title_x > SCREEN_WIDTH) {
			  myself->player.showtitle = false;
			}
			else if (myself->player.title_x >= SCREEN_WIDTH / 2 && myself->player.title_stay != 0) {
			  myself->player.title_stay = myself->player.title_stay - 1;
			}
			else {
			  myself->player.title_x = myself->player.title_x + 11;
			}
		  }
		  else {
			if (myself->player.title_y < SCREEN_WIDTH / 2) {
			  myself->player.title_y = myself->player.title_y + 11;
			}
			else if (myself->player.title_stay != 0) {
			  myself->player.title_stay = myself->player.title_stay - 1;
			}
			else {
			  myself->player.showtitle = false;
			}
		  }
		}

}

const void chackFade(ONFF_Map * myself)
{
	if (myself->player.const_unbeatable > 0) {
      myself->player.const_unbeatable--;
    }
    else {
      adjunct[4][0] = 0;
      adjunct[2][0] = 0;
    }
    if (myself->player.interlude) {
      if (myself->player.player_control > 0) {
        myself->player.player_control--;
      }
      else {
        setFade(myself,1);
        myself->player.interlude = false;
      }
    }
}

const gm_bool chackDamage(ONFF_Map * myself)
{
	gm_s16 temp_count;
	if(myself->player.player_Blood_now <= 0) {
             if(myself->player.player_Blood_now != -10) {
                 myself->player.interlude=true;
                 myself->player.const_unbeatable=50;
                 myself->player.player_control=30;
                 myself->player.player_Blood_now=-10;
                 adjunct[2][0]=0;
             }
             return(myself->player.player_control==0);
         }
         else if(myself->player.bombshot!=0) {
             EnemyCollisionWithItem(myself,0, 0,SCREEN_WIDTH,SCREEN_WIDTH, 0,0);
             CandyCollisionWithItem(myself,0, 0,SCREEN_WIDTH, SCREEN_HEIGHT, 0);
             myself->player.bombshot--;
             return(false);
         }
         else {
             if(myself->player.const_unbeatable==0){
                temp_count=CandyCollisionWithItem(myself,myself->player.position_x+myself->player.collision_x,myself->player.position_y+myself->player.collision_y, myself->player.collision_width, myself->player.collision_height,0);
                if(temp_count>0) {
                    setMoive(myself,3);
					if(myself->player.player_Blood_now > 1)
                    	myself->player.bomb_count_now=myself->player.playerbombnum;
                    if(myself->player.shot_type>1) {
                        setNewCandy(myself,myself->player.position_x+myself->player.player_width/2,myself->player.position_y+myself->player.player_height/2, 90,2,4);//candy.setNewCandy
                    }
                    setNewPlayer(myself);
                    myself->player.player_Blood_now=myself->player.player_Blood_now-1;
                }
                if(EnemyCollisionWithItem(myself,myself->player.position_x+myself->player.collision_x, myself->player.position_y+myself->player.collision_y, myself->player.collision_width, myself->player.collision_height,0,1)){
                    myself->player.const_unbeatable=10;
                    setMoive(myself,2);
                    if(myself->player.shot_type>0) myself->player.shot_type--;
                    else if(myself->player.bomb_count_now>0) myself->player.bomb_count_now--;
                }
             }
             else if(myself->player.bossdown) EnemySetAllDeath(myself);
             temp_count=CandyCollisionWithItem(myself,myself->player.position_x+myself->player.collision_x,myself->player.position_y+myself->player.collision_y, myself->player.collision_width, myself->player.collision_height,2);
             switch(temp_count){
                 case 4:{
                     if(myself->player.shot_type<3) myself->player.shot_type++;
                     setMoive(myself,1);
                     break;
                 }
                 case 5:{
                     if(myself->player.bomb_count_now<myself->player.bomb_count_max) myself->player.bomb_count_now++;
                     setMoive(myself,1);
                     break;
                 }
             }
             return(false);
         }
}


gm_bool startNextStage(ONFF_Map * myself,gm_bool down)
{
	if (down && myself->player.player_Blood_now > 0 && (!myself->player.bossdown)) {
      myself->player.bossdown = true;
      myself->player.const_unbeatable = 60;
      setMoive(myself,4);
    }
    if (myself->player.bossdown && myself->player.const_unbeatable == 30) {
      myself->player.interlude = true;
      myself->player.player_control = 30;
      setFade(myself, -10);
    }
    return (myself->player.bossdown && myself->player.const_unbeatable == 0);
}


void PlayerchackShot(ONFF_Map * myself)
{
    if (myself->player.const_unbeatable == 0) {
      myself->player.const_shot_now = (myself->player.const_shot_now + 1) % myself->player.const_shot_max;
      if (myself->player.const_shot_now == 0) {
        if (myself->player.shot_type == 0 || myself->player.shot_type == 2) {
          setNewCandy(myself,myself->player.position_x + myself->player.player_width / 2, myself->player.position_y, 90, 1, 2);
        }
        if (myself->player.shot_type == 1 || myself->player.shot_type == 3) {
          setNewCandy(myself,myself->player.position_x + myself->player.player_width / 2 - 3, myself->player.position_y, 90,
                            1, 2);
          setNewCandy(myself,myself->player.position_x + myself->player.player_width / 2 + 3, myself->player.position_y, 90,
                            1, 2);
        }
        if (myself->player.shot_type > 1) {
          setNewCandy(myself,myself->player.position_x, myself->player.position_y + myself->player.player_height / 2, 105, 1,
                            2);
          setNewCandy(myself,myself->player.position_x + myself->player.player_width,
                            myself->player.position_y + myself->player.player_height / 2, 75, 1, 2);
        }
      }
      if (myself->player.const_shot_now == myself->player.const_shot_max / 2 && myself->player.shot_type > 0 &&
          myself->player.shot_type == 3) {
        setNewCandy(myself,myself->player.position_x + myself->player.player_width / 2 - 3, myself->player.position_y, 90, 1,
                          2);
        setNewCandy(myself,myself->player.position_x + myself->player.player_width / 2 + 3, myself->player.position_y, 90, 1,
                          2);
      }
    }
}

void Player_Render(ONFF_Map * myself)
{
	gm_s32 i,temp_count;
 	if(myself->player.player_Blood_now > 0){
			myself->picLib->DrawRegionEx(myself->picLib,myself->player.player_image,
				myself->player.position_x,myself->player.position_y,myself->player.player_cur * 23,0,23,19,true,0);
      if (myself->player.player_cur_count == 1) {
       	   myself->picLib->DrawRegionEx(myself->picLib,myself->player.player_image2,
		   	myself->player.position_x + 8,myself->player.position_y,0,0,7,1,true,0);
      	}
	}

    temp_count = 0;
    while (temp_count < myself->player.adjunct_index) {
      if (adjunct[temp_count][0] == 1) {
        switch (temp_count) {
          case 0: {
            for ( i = 1; i < 5; i++) {
              adjunct[temp_count][5] = SCREEN_WIDTH/ 5 * i;
              adjunct[temp_count][6] = SCREEN_HEIGHT - adjunct[temp_count][2] * SCREEN_HEIGHT / 10;
			  myself->picLib->DrawRegionEx(myself->picLib,myself->player.player_effect,
			  adjunct[temp_count][5], adjunct[temp_count][6],
			  0,0,15,54,true,0);
            }
            break;
          }
          case 1: {
			myself->picLib->DrawRegionEx(myself->picLib,myself->player.player_effect,
				adjunct[temp_count][5],adjunct[temp_count][6] - adjunct[temp_count][2] * 3, 
				15+adjunct[temp_count][4] * 30,42,24,12,true,0);
            break;
          }
          case 2: {
			myself->picLib->DrawRegionEx(myself->picLib,myself->player.player_effect,
						adjunct[temp_count][5],adjunct[temp_count][6] - adjunct[temp_count][2] * 3,
						15+adjunct[temp_count][4] * 30,30,24,12,true,0);
            break;
          }
          case 3: {
            myself->picLib->DrawRegionEx(myself->picLib,myself->player.player_effect,
						adjunct[temp_count][5],adjunct[temp_count][6]-5,
						15+adjunct[temp_count][4] * 40,0,40,30,true,0);
            break;
          }
          case 4: {
            adjunct[temp_count][5] = myself->player.position_x;
            adjunct[temp_count][6] = myself->player.position_y;
			myself->picLib->DrawRegionEx(myself->picLib,myself->player.player_effect,
 					myself->player.position_x, myself->player.position_y,
 					76+adjunct[temp_count][4] * 20,30, 20, 24,true,0);
            break;
          }
        }
      }
      temp_count++;
    }
	
    
 	myself->picLib->DrawRegionEx(myself->picLib,myself->player.player_show,SCREEN_WIDTH-57,27,0,0,11,8,true,0);
	myself->picLib->DrawRegionEx(myself->picLib,myself->player.player_show,SCREEN_WIDTH-30,27,0,8,11,9,true,0);//-2?

    if (myself->player.player_Blood_now <= 0) {
	  manager.DrawString("0",5, SCREEN_WIDTH- 45, 20,0xffff00);	
    }
    else {
 		
		temp=manager_my->formatString("%d",myself->player.player_Blood_now); 
		manager.DrawString(temp,5, SCREEN_WIDTH- 45, 20,0xffff00);
    }
		temp=manager_my->formatString("%d",myself->player.bomb_count_now); 
	    manager.DrawString(temp,5, SCREEN_WIDTH- 19, 20,0xffff00);	
    if (myself->player.showtitle) 
	{
      if (myself->player.title_type == 0 && myself->Game_stage == 1) 
	  {
		//manager.DrawString("开始",20,SCREEN_WIDTH/2-18,SCREEN_HEIGHT/2,0xffff00);
		#ifdef GAME_240_320
			myself->picLib->DrawRegionEx(myself->picLib,myself->imgfont,SCREEN_WIDTH/2-40,SCREEN_HEIGHT/2,0,0,80,26,true,0);
		#endif
		#ifdef GAME_176_220
			myself->picLib->DrawRegionEx(myself->picLib,myself->imgfont,SCREEN_WIDTH/2-26,SCREEN_HEIGHT/2,0,0,52,17,true,0);
		#endif
      }
      else if(myself->player.title_type != 0 && myself->Game_stage == 1)
	  {
 		//manager.DrawString("小心",20,SCREEN_WIDTH/2-18,SCREEN_HEIGHT/2,0xff0000);
 		#ifdef GAME_240_320
		myself->picLib->DrawImageEx(myself->picLib,myself->test1,SCREEN_WIDTH/2-40,SCREEN_HEIGHT/2,true,0);
		#endif
		#ifdef GAME_240_320
		myself->picLib->DrawImageEx(myself->picLib,myself->test1,SCREEN_WIDTH/2-26,SCREEN_HEIGHT/2,true,0);
		#endif
      }
    }
}

gm_s16 PlayerRun(ONFF_Map * myself, gm_bool bossdown) { 
    PlayerNextPosition(myself);
    nextEffect(myself);
    nextTitle(myself);
    chackFade(myself);
    if (chackDamage(myself)) {
      return ( -1);
    }
    if (startNextStage(myself,bossdown)) {
      return (1);
    }
    PlayerchackShot(myself);
    return (0);
  }
void CandySetStage(ONFF_Map *myself) {
	gm_s16 temp_count_i = 0;
    myself->candy.candy_cur = 0;
    myself->candy.candy_cur_dely = 0;
    while (temp_count_i < myself->candy.candy_index) {
      myself->candy.temp_count_j = 0;
      while (myself->candy.temp_count_j < 13) {
        candy[temp_count_i][myself->candy.temp_count_j] = 0;
        myself->candy.temp_count_j++;
      }
      temp_count_i++;
    }
  }

void setNewCandy(ONFF_Map *myself,gm_s16 positionx, gm_s16 positiony, gm_s16 angle, gm_s16 type,gm_s16 index)
{
	
	gm_s16 temp_count_i = 0;
    while (temp_count_i < myself->candy.candy_index && candy[temp_count_i][0] == 1) {
      temp_count_i++;
    }
    if (temp_count_i < myself->candy.candy_index) {
      candy[temp_count_i][0] = 1;
      candy[temp_count_i][1] = positionx;
      candy[temp_count_i][2] = positiony;
      candy[temp_count_i][3] = trig(angle, 1) * candy_speed[index] / 100;
      candy[temp_count_i][4] = trig(angle, 0) * candy_speed[index] / 100;
      switch (index) {
        case 0: {
          candy[temp_count_i][5] = 5;
          candy[temp_count_i][6] = 5;
          break;
        }
        case 1: {
          candy[temp_count_i][5] = 7;
          candy[temp_count_i][6] = 7;
          break;
        }
        case 2: {
          candy[temp_count_i][5] = 1;
          candy[temp_count_i][6] = 12;
          break;
        }
        default: {
          candy[temp_count_i][5] = 23;
          candy[temp_count_i][6] = 13;
          break;
        }
      }
      candy[temp_count_i][7] = index;
      candy[temp_count_i][8] = type;
      candy[temp_count_i][9] = trig(angle, 1) * candy_speed[index] % 100;
      candy[temp_count_i][10] = trig(angle, 0) * candy_speed[index] % 100;
      candy[temp_count_i][11] = 0;
      candy[temp_count_i][12] = 0;
    }
    
    
}

gm_s16 CandyCollisionWithItem(ONFF_Map *myself,gm_s16 x, gm_s16 y, gm_s16 width, gm_s16 height, gm_s16 type)
{
	gm_s16 index = 0;
    gm_s16 result = 0;
    while (index < myself->candy.candy_index) {
      if (candy[index][0] == 1 && candy[index][8] == type &&
          CdRect2(candy[index][1], candy[index][2], candy[index][5],
                        candy[index][6], x, y, width, height)) {
        candy[index][0] = 0;
        if (candy[index][8] == 2) {
          return (candy[index][7]);
        }
        else {
          result++;
        }
      }
      index++;
    }
    return (result);
}

void Candy_Render(ONFF_Map * myself)
{
	gm_s16 temp_count_i = 0;
    while (temp_count_i < myself->candy.candy_index) {
      if (candy[temp_count_i][0] == 1) {
        switch (candy[temp_count_i][7]) {
          case 0: {
			myself->picLib->DrawRegionEx(myself->picLib,myself->candy.Bullet,candy[temp_count_i][1], candy[temp_count_i][2],0,0, 7, 5,true,0);
            break;
          }
          case 1: {
			myself->picLib->DrawRegionEx(myself->picLib,myself->candy.Bullet,candy[temp_count_i][1], candy[temp_count_i][2],0,5, 7, 7,true,0);
			break;
          }
          case 2: {
 			myself->picLib->DrawRegionEx(myself->picLib,myself->candy.Bullet,candy[temp_count_i][1], candy[temp_count_i][2],7,0, 1, 12,true,0);
            break;
          }
          default: {
			myself->picLib->DrawRegionEx(myself->picLib,myself->candy.Prize,candy[temp_count_i][1], candy[temp_count_i][2],23 * myself->candy.candy_cur,(candy[temp_count_i][7] - 4) * 13, 23, 13,true,0);
            break;
          }
        }
      }
      temp_count_i++;
    }
}

void CandyNextPosition(ONFF_Map * myself)
{
	gm_s16 temp_count_i = 0;
    while (temp_count_i < myself->candy.candy_index) {
      if (candy[temp_count_i][0] == 1) {
        candy[temp_count_i][1] = candy[temp_count_i][1] + candy[temp_count_i][3];
        candy[temp_count_i][11] = candy[temp_count_i][11] +
            candy[temp_count_i][9];
        if (Abs(candy[temp_count_i][11]) >= 100) {
          candy[temp_count_i][1] = candy[temp_count_i][1] +
              candy[temp_count_i][11] / 100;
          candy[temp_count_i][11] = candy[temp_count_i][11] % 100;
        }
        candy[temp_count_i][2] = candy[temp_count_i][2] + candy[temp_count_i][4];
        candy[temp_count_i][12] = candy[temp_count_i][12] +
            candy[temp_count_i][10];
        if (Abs(candy[temp_count_i][12]) >= 100) {
          candy[temp_count_i][2] = candy[temp_count_i][2] +
              candy[temp_count_i][12] / 100;
          candy[temp_count_i][12] = candy[temp_count_i][12] % 100;
        }
      }
      temp_count_i++;
    }
}
void CandyCallBack(ONFF_Map * myself)
{
	gm_s16 temp_count_i = 0;
    while (temp_count_i < myself->candy.candy_index) {
      if (candy[temp_count_i][0] == 1) {
        if (candy[temp_count_i][8] < 2) {
          if (candy[temp_count_i][1] < -candy[temp_count_i][5] ||
              candy[temp_count_i][1] > SCREEN_WIDTH ||
              candy[temp_count_i][2] < -candy[temp_count_i][6] ||
              candy[temp_count_i][2] > SCREEN_HEIGHT) {
            candy[temp_count_i][0] = 0;
          }
        }
        else {
          if (candy[temp_count_i][2] > SCREEN_HEIGHT) {
            candy[temp_count_i][0] = 0;
          }
          else if (candy[temp_count_i][2] < 0 && candy[temp_count_i][10] <= 0) {
            candy[temp_count_i][4] = -candy[temp_count_i][4];
            candy[temp_count_i][10] = -candy[temp_count_i][10];
            candy[temp_count_i][12] = -candy[temp_count_i][12];

          }
          else if ( (candy[temp_count_i][1] < 0 && candy[temp_count_i][9] <= 0) ||
                   (candy[temp_count_i][1] > SCREEN_WIDTH- 23 &&
                    candy[temp_count_i][9] >= 0)) {
            candy[temp_count_i][3] = -candy[temp_count_i][3];
            candy[temp_count_i][9] = -candy[temp_count_i][9];
            candy[temp_count_i][11] = -candy[temp_count_i][11];
          }
        }
      }
      temp_count_i++;
    }
}

void CandyRun(ONFF_Map * myself) 
{
    CandyNextPosition(myself);
    CandyCallBack(myself);
    if (myself->candy.candy_cur_dely == 1) {
      myself->candy.candy_cur = (myself->candy.candy_cur + 1) % 3;
      myself->candy.candy_cur_dely = 0;
    }
    else {
      myself->candy.candy_cur_dely++;
    }
}

void ONFF_Pause_Render(ONFF_Map * myself)
{	
	if(myself->music == 0 && extVmAudioManager->vMAduioGetState() != 0  ){
			extVmAudioManager->vMAudioStop();
		}
	#ifdef GAME_240_320
	//manager.DrawString("暂停",20,SCREEN_WIDTH/2-18,SCREEN_HEIGHT/2,0xffff00);
	myself->picLib->DrawRegionEx(myself->picLib,myself->imgfont,SCREEN_WIDTH/2-40,SCREEN_HEIGHT/2,640,0,80,26,true,0);
	//getManagerPtr()->DrawString("继续",25,TOUCH_X_LEFT,TOUCH_Y_LEFT,0xffff00);
	myself->picLib->DrawRegionEx(myself->picLib,myself->imgfont,TOUCH_X_LEFT-10,TOUCH_Y_LEFT,560,0,80,26,true,0);
	//getManagerPtr()->DrawString("退出",25,TOUCH_X_RIGHT,TOUCH_Y_RIGHT,0xffff00); 
	myself->picLib->DrawRegionEx(myself->picLib,myself->imgfont,160,TOUCH_Y_RIGHT,320,0,80,26,true,0);
	#endif
	#ifdef GAME_176_220
	//manager.DrawString("暂停",20,SCREEN_WIDTH/2-18,SCREEN_HEIGHT/2,0xffff00);
	myself->picLib->DrawRegionEx(myself->picLib,myself->imgfont,SCREEN_WIDTH/2-26,SCREEN_HEIGHT/2,416,0,52,17,true,0);
	//getManagerPtr()->DrawString("继续",25,TOUCH_X_LEFT,TOUCH_Y_LEFT,0xffff00);
	myself->picLib->DrawRegionEx(myself->picLib,myself->imgfont,TOUCH_X_LEFT-10,TOUCH_Y_LEFT,364,0,52,17,true,0);
	//getManagerPtr()->DrawString("退出",25,TOUCH_X_RIGHT,TOUCH_Y_RIGHT,0xffff00); 
	myself->picLib->DrawRegionEx(myself->picLib,myself->imgfont,TOUCH_X_RIGHT-8,TOUCH_Y_RIGHT,208,0,52,17,true,0);
	#endif
	if(extOldGameManager->IsKeyDown(MF_KEY_RIGHTSOFT))
	{
		if(myself->music == 0 && extVmAudioManager->vMAduioGetState() != 0){
			extVmAudioManager->vMAudioStop();
		}
		gameMusic = myself->music;	
		gamePlayerlife = myself->player.playerlifenum;
		gamePlayerbomb  = myself->player.playerbombnum;
		ONFF_Screen_Next = &ONFF_Screen_Title;
		oNFFLoadingStep = 0;
		oNFFLoadingStepTotal = 7;
		SCREEN_ChangeScreen(&ONFF_Screen_Loading);
	}
	else if(extOldGameManager->IsKeyDown(MF_KEY_LEFTSOFT))
	{	
		myself->background.scroll = true;
		if(myself->music == 0 && extVmAudioManager->vMAduioGetState() == 0  ){
//			extVmAudioManager->vMAudioPlayForGame(ONFF_MUSIC_MID,0);
		}
		myself->Game_stage = 1;
	}
}

void ONFF_GameFail_Render(ONFF_Map * myself)
{	
	gm_s16 y0;
	#ifdef GAME_240_320
		y0 = 80;
	#endif
	#ifdef GAME_176_220
		y0 = 40;
	#endif
	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(36,19,121));
	myself->picLib->DrawImageEx(myself->picLib,myself->imgFailed,0,y0,true,0);
	//manager.DrawString("按任意键返回!!!",40,SCREEN_WIDTH/2-70,SCREEN_HEIGHT-40,0xffff00);
	#ifdef GAME_240_320
		myself->picLib->DrawRegionEx(myself->picLib,myself->imgfont,0,SCREEN_HEIGHT-40,400,0,240,26,true,0);
	#endif
	#ifdef GAME_176_220
		myself->picLib->DrawRegionEx(myself->picLib,myself->imgfont,0,SCREEN_HEIGHT-26,260,0,156,17,true,0);
	#endif
	if (getManagerPtr()->IsKeyDown(MF_KEY_ANY)||SCREEN_IsPointerDown())
	{
		if(myself->music == 0 && extVmAudioManager->vMAduioGetState() != 0){
			extVmAudioManager->vMAudioStop();
		}
		gameMusic = myself->music;	
		gamePlayerlife = myself->player.playerlifenum;
		gamePlayerbomb  = myself->player.playerbombnum;
		ONFF_Screen_Next = &ONFF_Screen_Title;
		oNFFLoadingStep = 0;
		oNFFLoadingStepTotal = 6;
		SCREEN_ChangeScreen(&ONFF_Screen_Loading);	
	}
}

void SetNewStage(ONFF_Map * myself)
{
	gm_s16 stage[4][384] = {
							{30,2,0,1,5,2,1,0,5,2,2,1,5,2,3,0,5,4,4,1,10,1,5,2,0,1,6,2,50,3,9,0,12,3,8,0,12,3,7,0,12,3,11,0,12,3,10,0,12,3,8,0,12,3,11,0,12,3,9,0,12,3,10,0,12,3,7,0,30,2,0,1,5,2,1,1,5,2,2,1,5,2,3,1,5,4,4,1,50,3,9,0,12,3,8,0,0,7,13,3,12,3,7,0,12,3,11,0,12,3,10,0,12,3,8,0,12,3,11,0,0,7,15,3,12,3,9,0,12,3,10,0,12,3,7,0,12,3,11,0,12,3,8,0,0,7,14,3,12,3,7,0,12,3,11,0,12,3,10,0,12,3,8,0,12,3,11,0,5,5,12,4,12,3,9,0,0,7,15,3,12,3,7,0,12,3,11,0,12,3,10,0,12,3,9,0,12,3,8,0,0,7,13,3,10,2,0,1,5,2,1,0,5,2,2,1,5,2,3,0,5,4,4,1,5,5,12,4,25,6,18,5,25,6,16,5,25,6,20,5,25,6,19,5,25,6,18,5,0,7,14,3,20,2,0,1,5,2,1,0,5,2,2,1,5,2,3,0,5,4,4,1,10,1,5,2,0,1,6,2,30,7,13,3,50,7,15,3,12,3,8,0,12,3,7,0,12,3,11,0,12,3,10,0,30,7,15,3,0,7,13,3,0,7,14,3,40,2,0,1,5,2,1,0,5,2,2,1,5,2,3,0,5,4,4,1,60,7,21,6,70,7,22,6,0,12,27,10,0,8,28,0,0,9,29,0,0,0,30,8,0,0,30,9,0,10,23,0,0,8,24,0,0,9,25,0,0,11,26,7,-1,0,0,0},
							{30,1,0,0,5,1,1,0,5,1,2,0,5,1,3,0,5,2,4,1,20,3,5,1,5,3,6,1,5,3,7,1,5,3,8,1,5,3,5,1,5,3,6,1,5,3,7,1,5,3,8,1,10,5,9,3,15,4,12,2,30,4,14,2,30,4,13,2,30,4,11,2,30,4,10,2,30,4,12,2,30,4,10,2,15,6,15,4,30,4,14,2,30,4,13,2,0,6,15,4,30,4,10,2,30,4,12,2,35,6,15,4,30,4,14,2,5,1,0,0,5,1,1,0,5,1,2,0,5,1,3,0,5,2,4,1,30,4,13,2,30,4,11,2,30,4,10,2,5,1,0,0,5,1,1,0,5,1,2,0,5,1,3,0,5,2,4,1,30,4,12,2,30,4,10,2,10,8,21,5,10,7,16,6,20,8,22,5,20,8,20,5,20,8,21,5,15,7,17,6,20,8,23,5,20,8,19,5,20,8,21,5,15,7,18,6,10,5,9,3,45,7,16,6,15,7,17,6,50,1,0,0,5,1,1,0,5,1,2,0,5,1,3,0,5,2,4,1,60,9,24,7,0,10,25,8,0,11,26,9,0,12,27,10,0,13,29,13,0,13,30,12,0,9,28,11,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{30,1,0,0,5,1,1,0,5,1,2,0,5,1,3,0,5,2,4,1,20,3,5,2,0,3,6,2,0,3,7,2,0,3,8,2,20,3,5,2,0,3,6,2,0,3,7,2,0,3,8,2,20,4,9,3,40,3,5,2,0,3,6,2,0,3,7,2,0,3,8,2,10,4,10,3,40,3,5,2,0,3,6,2,0,3,7,2,0,3,8,2,40,1,0,0,5,1,1,0,5,1,2,0,5,1,3,0,5,2,4,1,10,5,11,4,0,5,12,4,30,6,13,5,80,6,15,5,80,6,14,5,40,4,9,3,30,4,10,3,30,1,0,0,5,1,1,0,5,1,2,0,5,1,3,0,5,2,4,1,0,7,16,7,30,6,15,5,50,7,17,7,60,6,13,5,60,3,5,2,0,3,6,2,0,3,7,2,0,3,8,2,30,7,18,7,20,4,9,6,40,1,0,0,5,1,1,0,5,1,2,0,5,1,3,0,5,2,4,1,10,4,10,6,20,6,13,5,40,6,15,5,30,1,0,0,5,1,1,0,5,1,2,0,5,1,3,0,50,0,27,10,0,0,27,9,0,8,19,8,0,9,20,11,0,10,21,0,0,12,22,16,0,11,23,15,0,13,24,13,0,14,25,14,0,8,26,12,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{20,4,9,3,10,4,12,3,10,4,11,3,10,4,10,3,10,4,13,3,10,4,10,3,10,4,9,3,10,4,12,3,10,4,13,3,10,4,11,3,20,3,5,2,0,3,6,2,0,3,7,2,0,3,8,2,20,3,5,2,0,3,6,2,0,3,7,2,0,3,8,2,20,1,0,1,5,1,1,1,5,1,2,1,5,1,3,1,5,2,4,1,0,5,14,4,0,5,15,4,5,6,16,5,80,6,17,5,30,4,9,3,50,6,18,5,30,4,11,3,60,6,16,5,20,7,19,6,60,6,18,5,50,6,17,5,30,7,20,6,40,6,16,5,20,1,0,1,5,1,1,1,5,1,2,1,5,1,3,1,5,2,4,1,15,8,21,7,0,5,14,4,0,5,15,4,70,9,18,8,110,4,9,3,20,4,12,3,20,4,11,3,20,4,10,3,20,4,13,3,120,11,23,9,0,12,24,10,0,13,25,10,0,14,26,11,0,15,27,12,0,16,28,13,0,14,29,12,0,15,30,11,0,11,31,0,0,12,32,10,0,13,33,10,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
							};
	gm_s16 adjunct1[5][7] = {{0, 14, 0, 1, 0, 0, 0}, {0, 4, 0, 2, 0, 0, 0}, {0, 4, 0, 2, 0, 0, 0}, {0, 1, 0, 1, 0, 0, 0}, {0, -1, 0, 3, 0, 0, 0}};
	gm_s16 i,j;
	for(i=0;i<6;i++)
	{
		candy_speed[i] = candy_speed1[i];
	}
	for(i=0;i<5;i++)
	{
		for(j=0;j<7;j++)
		{
			adjunct[i][j] = adjunct1[i][j]; 
		}
	}
	EnemySetStage(myself);
	CandySetStage(myself);
	setNewPlayer(myself);
	myself->player.roll_count = 0;
	myself->Game_count_max = 0;
	myself->Game_count_now = stage[myself->tagenum][myself->Game_count_max];
}

void ONFF_GameCenter_Render(ONFF_Map * myself)
{
	gm_s16 x,y,dx,dy,y0,w,h;
	
	if(myself->music == 0 && extVmAudioManager->vMAduioGetState() != 0  ){
			extVmAudioManager->vMAudioStop();
		}
	myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(36,19,121));
	#ifdef GAME_240_320
		x = 130;
		y = 155;
		dx = 25;
		dy = 15;
		y0 = 80;
		w = 40;
		h = 26;
	#endif
	#ifdef GAME_176_220
		x = 130;
		y = 115;
		dx = 30;
		dy = 10;
		y0 = 60;
		w = 26;
		h = 17;
	#endif
	myself->picLib->DrawImage(myself->picLib,myself->imgSuccess,0,y0);
	switch(myself->tagenum){
		case 0:
			myself->enemy[1] = myself->picLib->GetImage(myself->picLib,"boss2.gif");
			myself->picLib->DrawImageEx(myself->picLib,myself->imgpoint,x,y,true,0);
			myself->picLib->DrawLine(myself->picLib,0,y+8,SCREEN_WIDTH,y+8,GAME_ToRGB(255,0,0));
			myself->picLib->DrawLine(myself->picLib,x+8,y0,x+8,y0+myself->picLib->GetImageHeight(myself->picLib,myself->imgSuccess),GAME_ToRGB(255,0,0));
			//manager.DrawString("按任意键继续",40,SCREEN_WIDTH/2-60,SCREEN_HEIGHT-40,0xffff00);	
			myself->picLib->DrawRegionEx(myself->picLib,myself->imgfont,0,SCREEN_HEIGHT-w,10*w,0,6*w,h,true,0);
			
			break;
		case 1:
			myself->enemy[1] = myself->picLib->GetImage(myself->picLib,"boss3.gif");		
			myself->picLib->DrawImageEx(myself->picLib,myself->imgpoint,x-dx,y-dy,true,0);
			myself->picLib->DrawLine(myself->picLib,0,y+8-dy,SCREEN_WIDTH,y+8-dy,GAME_ToRGB(255,0,0));
			myself->picLib->DrawLine(myself->picLib,x+8-dx,y0,x+8-dx,y0+myself->picLib->GetImageHeight(myself->picLib,myself->imgSuccess),GAME_ToRGB(255,0,0));
		    //manager.DrawString("按任意键继续",40,SCREEN_WIDTH/2-60,SCREEN_HEIGHT-40,0xffff00);	
		   myself->picLib->DrawRegionEx(myself->picLib,myself->imgfont,0,SCREEN_HEIGHT-w,10*w,0,6*w,h,true,0);
			break;
		case 2:
			myself->enemy[1] = myself->picLib->GetImage(myself->picLib,"boss4.gif");
			myself->picLib->DrawImageEx(myself->picLib,myself->imgpoint,x-2*dx,y-2*dy,true,0);
			myself->picLib->DrawLine(myself->picLib,0,y+8-2*dy,SCREEN_WIDTH,y+8-2*dy,GAME_ToRGB(255,0,0));
			myself->picLib->DrawLine(myself->picLib,x+8-2*dx,y0,x+8-2*dx,y0+myself->picLib->GetImageHeight(myself->picLib,myself->imgSuccess),GAME_ToRGB(255,0,0));			
			//manager.DrawString("按任意键继续",40,SCREEN_WIDTH/2-60,SCREEN_HEIGHT-40,0xffff00);	
			myself->picLib->DrawRegionEx(myself->picLib,myself->imgfont,0,SCREEN_HEIGHT-w,10*w,0,6*w,h,true,0);
			break;
		}
			
			myself->picLib->DrawRegionEx(myself->picLib,myself->imgfont,0,7,18*w,0,w,h,true,0);
			myself->picLib->DrawRegionEx(myself->picLib,myself->imgfont,w,7,21*w+myself->tagenum*40,0,w,h,true,0);
			myself->picLib->DrawRegionEx(myself->picLib,myself->imgfont,2*w,7,19*w,0,w,h,true,0);
	if (getManagerPtr()->IsKeyDown(MF_KEY_ANY)||SCREEN_IsPointerDown())
	{
		if(myself->music == 0 && extVmAudioManager->vMAduioGetState() == 0  ){
//			extVmAudioManager->vMAudioPlayForGame(ONFF_MUSIC_MID,0);
		}
		switch(myself->tagenum){
			case 0:
			case 1:
			case 2:
				myself->tagenum++;
				SetNewStage(myself);
				myself->Game_stage = 1;
				break;
		}
	}
}

void ONFF_GameSuccess_Render(ONFF_Map * myself)
{		gm_s8 y0;
		myself->picLib->FillRect(myself->picLib,0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GAME_ToRGB(36,19,121));
	#ifdef GAME_240_320
		y0 = 80;
	#endif
	#ifdef GAME_176_220
		y0 = 60;
	#endif
		myself->picLib->DrawImage(myself->picLib,myself->imgSuccess,0,y0);
		//manager.DrawString("恭喜您过关啦!!!",40,SCREEN_WIDTH/2-70,SCREEN_HEIGHT-70,0xffff00);
		//manager.DrawString("按任意键返回!!!",40,SCREEN_WIDTH/2-70,SCREEN_HEIGHT-40,0xffff00);
	#ifdef GAME_240_320
		myself->picLib->DrawRegionEx(myself->picLib,myself->imgfont,0,SCREEN_HEIGHT-40,400,0,240,26,true,0);
	#endif
	#ifdef GAME_176_220
		myself->picLib->DrawRegionEx(myself->picLib,myself->imgfont,0,SCREEN_HEIGHT-26,260,0,156,26,true,0);
	#endif
	myself->tagenum =0;
	myself->player.bossdown = false;
	if(myself->music == 0 && extVmAudioManager->vMAduioGetState() != 0  ){
			extVmAudioManager->vMAudioStop();
		}
	if (getManagerPtr()->IsKeyDown(MF_KEY_ANY)||SCREEN_IsPointerDown())
	{
		if(myself->music == 0 && extVmAudioManager->vMAduioGetState() != 0){
			extVmAudioManager->vMAudioStop();
		}
		gameMusic = myself->music;	
		gamePlayerlife = myself->player.playerlifenum;
		gamePlayerbomb  = myself->player.playerbombnum;
		ONFF_Screen_Next = &ONFF_Screen_Title;
		oNFFLoadingStep = 0;
		oNFFLoadingStepTotal = 6;
		SCREEN_ChangeScreen(&ONFF_Screen_Loading);
	}
}
void ONFF_Map_Windows_Render(void * param)
{	
	ONFF_Map * myself = (ONFF_Map *)param;
	SetNewStage(myself);
	Background_Render(myself);
	Enemy_Render(myself);
	Player_Render(myself);
	Candy_Render(myself);
	if(myself->music == 0 && extVmAudioManager->vMAduioGetState() == 0){
//			extVmAudioManager->vMAudioPlayForGame(ONFF_MUSIC_MID,0);
		}
}

void ONFF_Map_Windows_Update(void * param)
{	
		gm_s16 t;
		gm_bool b;
		ONFF_Map * myself = (ONFF_Map *)param;
if(myself->Game_stage == 0)
{	
	myself->background.scroll = false;
	Background_Render(myself);
	Enemy_Render(myself);
	Player_Render(myself);
	Candy_Render(myself);
	ONFF_Pause_Render(myself);
}


if(myself->Game_stage == 1){
		if(extOldGameManager->IsKeyDown(MF_KEY_RIGHTSOFT))
		{
			myself->Game_stage = 0;
		}
		myself->background.t++;
		t = myself->background.t;
		if(t/18 == 0)
		{
				CandyRun(myself);
				Background_Render(myself);
				Enemy_Render(myself);
				Player_Render(myself);
				Candy_Render(myself);
				keyReleased(myself);
				keyPressed(myself);
			if (myself->Game_count_now != -1) 
			{
			  if (myself->Game_count_now == 0) 
			  {
			  gm_s16 stage[4][384] = {
							{30,2,0,1,5,2,1,0,5,2,2,1,5,2,3,0,5,4,4,1,10,1,5,2,0,1,6,2,50,3,9,0,12,3,8,0,12,3,7,0,12,3,11,0,12,3,10,0,12,3,8,0,12,3,11,0,12,3,9,0,12,3,10,0,12,3,7,0,30,2,0,1,5,2,1,1,5,2,2,1,5,2,3,1,5,4,4,1,50,3,9,0,12,3,8,0,0,7,13,3,12,3,7,0,12,3,11,0,12,3,10,0,12,3,8,0,12,3,11,0,0,7,15,3,12,3,9,0,12,3,10,0,12,3,7,0,12,3,11,0,12,3,8,0,0,7,14,3,12,3,7,0,12,3,11,0,12,3,10,0,12,3,8,0,12,3,11,0,5,5,12,4,12,3,9,0,0,7,15,3,12,3,7,0,12,3,11,0,12,3,10,0,12,3,9,0,12,3,8,0,0,7,13,3,10,2,0,1,5,2,1,0,5,2,2,1,5,2,3,0,5,4,4,1,5,5,12,4,25,6,18,5,25,6,16,5,25,6,20,5,25,6,19,5,25,6,18,5,0,7,14,3,20,2,0,1,5,2,1,0,5,2,2,1,5,2,3,0,5,4,4,1,10,1,5,2,0,1,6,2,30,7,13,3,50,7,15,3,12,3,8,0,12,3,7,0,12,3,11,0,12,3,10,0,30,7,15,3,0,7,13,3,0,7,14,3,40,2,0,1,5,2,1,0,5,2,2,1,5,2,3,0,5,4,4,1,60,7,21,6,70,7,22,6,0,12,27,10,0,8,28,0,0,9,29,0,0,0,30,8,0,0,30,9,0,10,23,0,0,8,24,0,0,9,25,0,0,11,26,7,-1,0,0,0},
							{30,1,0,0,5,1,1,0,5,1,2,0,5,1,3,0,5,2,4,1,20,3,5,1,5,3,6,1,5,3,7,1,5,3,8,1,5,3,5,1,5,3,6,1,5,3,7,1,5,3,8,1,10,5,9,3,15,4,12,2,30,4,14,2,30,4,13,2,30,4,11,2,30,4,10,2,30,4,12,2,30,4,10,2,15,6,15,4,30,4,14,2,30,4,13,2,0,6,15,4,30,4,10,2,30,4,12,2,35,6,15,4,30,4,14,2,5,1,0,0,5,1,1,0,5,1,2,0,5,1,3,0,5,2,4,1,30,4,13,2,30,4,11,2,30,4,10,2,5,1,0,0,5,1,1,0,5,1,2,0,5,1,3,0,5,2,4,1,30,4,12,2,30,4,10,2,10,8,21,5,10,7,16,6,20,8,22,5,20,8,20,5,20,8,21,5,15,7,17,6,20,8,23,5,20,8,19,5,20,8,21,5,15,7,18,6,10,5,9,3,45,7,16,6,15,7,17,6,50,1,0,0,5,1,1,0,5,1,2,0,5,1,3,0,5,2,4,1,60,9,24,7,0,10,25,8,0,11,26,9,0,12,27,10,0,13,29,13,0,13,30,12,0,9,28,11,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{30,1,0,0,5,1,1,0,5,1,2,0,5,1,3,0,5,2,4,1,20,3,5,2,0,3,6,2,0,3,7,2,0,3,8,2,20,3,5,2,0,3,6,2,0,3,7,2,0,3,8,2,20,4,9,3,40,3,5,2,0,3,6,2,0,3,7,2,0,3,8,2,10,4,10,3,40,3,5,2,0,3,6,2,0,3,7,2,0,3,8,2,40,1,0,0,5,1,1,0,5,1,2,0,5,1,3,0,5,2,4,1,10,5,11,4,0,5,12,4,30,6,13,5,80,6,15,5,80,6,14,5,40,4,9,3,30,4,10,3,30,1,0,0,5,1,1,0,5,1,2,0,5,1,3,0,5,2,4,1,0,7,16,7,30,6,15,5,50,7,17,7,60,6,13,5,60,3,5,2,0,3,6,2,0,3,7,2,0,3,8,2,30,7,18,7,20,4,9,6,40,1,0,0,5,1,1,0,5,1,2,0,5,1,3,0,5,2,4,1,10,4,10,6,20,6,13,5,40,6,15,5,30,1,0,0,5,1,1,0,5,1,2,0,5,1,3,0,50,0,27,10,0,0,27,9,0,8,19,8,0,9,20,11,0,10,21,0,0,12,22,16,0,11,23,15,0,13,24,13,0,14,25,14,0,8,26,12,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
							{20,4,9,3,10,4,12,3,10,4,11,3,10,4,10,3,10,4,13,3,10,4,10,3,10,4,9,3,10,4,12,3,10,4,13,3,10,4,11,3,20,3,5,2,0,3,6,2,0,3,7,2,0,3,8,2,20,3,5,2,0,3,6,2,0,3,7,2,0,3,8,2,20,1,0,1,5,1,1,1,5,1,2,1,5,1,3,1,5,2,4,1,0,5,14,4,0,5,15,4,5,6,16,5,80,6,17,5,30,4,9,3,50,6,18,5,30,4,11,3,60,6,16,5,20,7,19,6,60,6,18,5,50,6,17,5,30,7,20,6,40,6,16,5,20,1,0,1,5,1,1,1,5,1,2,1,5,1,3,1,5,2,4,1,15,8,21,7,0,5,14,4,0,5,15,4,70,9,18,8,110,4,9,3,20,4,12,3,20,4,11,3,20,4,10,3,20,4,13,3,120,11,23,9,0,12,24,10,0,13,25,10,0,14,26,11,0,15,27,12,0,16,28,13,0,14,29,12,0,15,30,11,0,11,31,0,0,12,32,10,0,13,33,10,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
							};
				setNewEnemy(myself,stage[myself->tagenum][myself->Game_count_max + 1],
								  stage[myself->tagenum][myself->Game_count_max + 2],
								  stage[myself->tagenum][myself->Game_count_max + 3]);
				myself->Game_count_max = myself->Game_count_max + 4;
				myself->Game_count_now = stage[myself->tagenum][myself->Game_count_max];
			  }
			  else 
			  {
				myself->Game_count_now--;
			  }
			}
			if (myself->score > myself->nextscore &&
	          myself->player.player_Blood_now < myself->player.player_Blood_max) {
	          myself->player.player_Blood_now++;
	          myself->nextscore = myself->nextscore + 200;
        	}
				b = EnemyRun(myself,myself->player.position_x + myself->player.player_width / 2,myself->player.position_y + myself->player.player_height / 2);
			switch (PlayerRun(myself,b)) 
				{
				  case -1: {
					myself->Game_stage = 3;
					break;
				  }
				  case 1: {
					if (myself->tagenum == 3) {
					  myself->Game_stage = 5;
					}
					else {
					  myself->Game_stage = 4;
					}
					break;
				  }
				}				
			//temp=manager_my->formatString("%s%d%s", "第",myself->tagenum+1,"关");
	    	//manager.DrawString(temp,10, 7, 2,0xffff00);
	    	#ifdef GAME_240_320
	    		myself->picLib->DrawRegionEx(myself->picLib,myself->imgfont,0,7,720,0,40,26,true,0);
				myself->picLib->DrawRegionEx(myself->picLib,myself->imgfont,30,7,840+myself->tagenum*40,0,40,26,true,0);
				myself->picLib->DrawRegionEx(myself->picLib,myself->imgfont,60,7,760,0,40,26,true,0);
			#endif
			#ifdef GAME_176_220
				myself->picLib->DrawRegionEx(myself->picLib,myself->imgfont,0,7,468,0,26,17,true,0);
				myself->picLib->DrawRegionEx(myself->picLib,myself->imgfont,20,7,546+myself->tagenum*26,0,26,17,true,0);
				myself->picLib->DrawRegionEx(myself->picLib,myself->imgfont,40,7,494,0,26,17,true,0);
			#endif
		}
		if(myself->background.y%16 == 0)
				myself->background.y = 0;
	}
	if(myself->Game_stage == 3)
	{
		ONFF_GameFail_Render(myself);
	}
	if(myself->Game_stage == 4)
	{
		ONFF_GameCenter_Render( myself);
	}
	if(myself->Game_stage == 5)
	{
		ONFF_GameSuccess_Render( myself);
	}
}

