/**************************************************************************************************************************************************
*compay:daicom
*name:zhaoliangqi
*filename:CatLoveDog_InGame.h
*绘制游戏主体画面
**************************************************************************************************************************************************/

#ifndef CATLOVEDOG_INGAME_H
#define CATLOVEDOG_INGAME_H
#include "DF_Windows.h"
#include "DF_PictureLibrary.h"

typedef struct CATLOVEDOG_INGAME
{
	DF_PictureLibrary * picLib;
	DF_Windows windows;											 
	/*******************************************showgame中的变量*********************************************************************/
    gm_s8 SleepTimer; 												/////////////////初始刷新时间
    gm_s8 changelifeD; 												/////////////////减血量
    gm_s8 changelifeC;
    gm_s8 setColor;
    gm_bool bombRun;
    gm_s16 angle;
    gm_bool alive; 													////设置条件判断线程是否进行
    gm_bool isPause;
	gm_bool gameWin;
	gm_bool gameOver;
    
    //图片
    gm_s16 catImg; 													///////////////////玩家图片
    gm_s16 dogImg;
    gm_s16 fishImg;
    gm_s16 boneImg;
    gm_s16 winImg;
    gm_s16 loseImg;
    gm_s16 bombImg;
    gm_s16 windImg;
    gm_s16 buttonImg;
    gm_s16 button;
    gm_s16 beijing;													//游戏背景图片
	gm_s16 lifeImageD;												//表示狗血的图标
	gm_s16 lifeImageC;												//表示猫血的图标
	gm_s16 catPX;													//猫的位置X坐标
	gm_s8 cattu;													//猫显示的图像
	gm_s8 dogtu;													//狗显示的图像
	gm_s16 isFire;

	/***************************************************Fish类************************************************************/
	gm_s16 fishPX;													//鱼刺的X坐标
	gm_s16 fishPY;													//鱼刺的X坐标
	gm_bool fishShow;												//是否显示鱼刺
	gm_s8 fishFrame;												//鱼刺第几帧
	gm_s16 fish_v0;
	gm_s16 fish_i;
	gm_bool fishGo;
	gm_s16 fish_tTemp;
	gm_s16 fish_t1;
	gm_s16 fish_vx1;
	gm_s16 fish_vy1;
	gm_s16 fish_add1;
	
	/***************************************************Bone类************************************************************/
	gm_s16 bonePX;													//骨头的X坐标
	gm_s16 bonePY;													//骨头的X坐标
	gm_bool boneShow;												//是否显示骨头
	gm_s8 boneFrame;												//骨头第几帧
	gm_s16 bone_v02; //初始速度
  	gm_s16 bone_add2;//加速度
	gm_bool boneGo;	//是否运动
	gm_s16 bone_tTemp2;
	gm_s16 bone_vx2; 
	gm_s16 bone_vy2; //骨头速度
    gm_s16 bone_t2; //骨头抛出时间
  	gm_s16 bone_r;
	gm_s8 bone_i;
	gm_s16 bombFrame;
	gm_bool bombShow;

	
	/***************************************************Wind类************************************************************/
	gm_s16 windn;
	gm_s16 Wind_left;
  	gm_s16 Wind_right;
  	gm_s16 Wind_change;
  	gm_s16 Wind_v;

	/*************************************************LifeC .Class***********************************************************/
	gm_s16 LifeC_lifewc;
	gm_s16 catBlood;												//猫的血量
	
	/*************************************************LifeD.Class***********************************************************/
	gm_s16 dogBlood;												//狗的血量
	gm_s16 LifeD_lifew;
    gm_s16 liliangImg;

	gm_s8 bombPX;													//爆炸X坐标
	gm_s8 bombPY;													//爆炸Y坐标

	gm_bool teshu;
	//public Sprite cat;		
    //public Sprite dog;
    //public Sprite bomb;
    //public Wind wind;
    //LifeD lifeD;
    //LifeC lifeC;
}CatLoveDog_InGame;

extern void initCatLoveDog_InGame(CatLoveDog_InGame * myself,Rect windows_Rect,DF_PictureLibrary * picLib,gm_s16 repaintMax);
void CatLoveDog_InGame_Windows_Render(void *param);
void CatLoveDog_InGame_Windows_Update(void * param);

#endif

