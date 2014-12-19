/*******************************************************************
* 2009 Wingtech, Incoporated. All Rights Reserved.
* 
* 文件名称：RussBlock_UI.h

此功能是游戏中UI界面，它可减少游戏中需要刷屏区域，增加游戏速度,按块去刷新屏幕
*******************************************************************/

#ifndef RUSSBLOCK_UI_H
#define RUSSBLOCK_UI_H

#include "DF_PictureLibrary.h"
#include "DF_Windows.h"
//#include "DF_Actor.h"




typedef struct RUSSBLOCK_UI 
{
	gm_s32 score;  //玩家得分
	gm_s32 clearedlayer; //已消层数
	gm_s32 level;   //玩家等级

	gm_s32 lastClearedLayer;   //上次消的层数
	gm_s32 hitNum;  //连击数
	gm_bool flag_hit;     /*连击动画标志*/
	gm_s16 hitCount;	/*连击动画显示计数*/
	gm_bool flag_action;   /*女孩面部动画是否激活*/
	gm_s16 action;      /*女孩动画类型标志 0为正常 1为消1层 2为消2层 3为消3成 4为消4层 5为失败*/
	//DF_Actor actorGirlFace;
//#ifdef GAME_240_320
	gm_s16 imgUI[5];//UI界面中得图片名
	gm_s16 imgGirl;
	gm_s16 imgHiteffect;   //连击效果图
	gm_s16 imgTime;
	gm_s16 imgPropBar;
	gm_s16 imgPropNum;
	gm_s16 imgPropKey;
	gm_s16 imgCmd;
	gm_s16 imgClear;
//#endif
	DF_Windows windows;//UI中窗口
	DF_PictureLibrary *picLib;//UI中图片库
	//UI中刷新区域
	void (*UpdateScore)(struct RUSSBLOCK_UI *myself);
	void (*UpdateClearedLayer)(struct RUSSBLOCK_UI * myself);
	void (*UpdateLevel)(struct RUSSBLOCK_UI * myself);
	void (*UpdateRect)(struct RUSSBLOCK_UI * myself,gm_s16 x,gm_s16 y,gm_s16 w,gm_s16 h);
	void (*UpdateGirlFace)(struct RUSSBLOCK_UI * myself,gm_s16 action);
	void (*UpdateNextBlockArea)(struct RUSSBLOCK_MAP * myself);
}RussBlockUi;
//UI中刷新函数
extern void initRussBlockUi(RussBlockUi * myself,Rect DF_Windows_Rect,DF_PictureLibrary * picLib,gm_s32 score,gm_s32 clearedlayer);
void RussBlock_UI_Windows_Render(void * param);
void RussBlock_UI_Windows_Update(void * param);
void RussBlock_UI_UpdateScore(RussBlockUi * myself);
void RussBlock_UI_UpdateClearedLayer(RussBlockUi * myself);
void RussBlock_UI_UpdateLevel(RussBlockUi * myself);
void RussBlock_UI_UpdateRect(RussBlockUi * myself,gm_s16 x,gm_s16 y,gm_s16 w,gm_s16 h);
void RussBlock_UI_UpdateGirlFace(RussBlockUi * myself,gm_s16 action);/*外部调用，女孩表情变化*/
static void UpdateGirlFace1(void * param);

#endif