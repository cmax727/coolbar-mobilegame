/*******************************************************************
* 2009 Wingtech, Incoporated. All Rights Reserved.
* 
* 文件名称：RussBlock_Map.h

此功能是游戏地图类，主要实现InGame时候的主逻辑、画图、核心算法、方块初使定位
*******************************************************************/


#ifndef RUSSBLOCK_SHAPE_H
#define RUSSBLOCK_SHAPE_H

#include "coolbar_Sprite.h"
#include "DF_Windows.h"
#include "RussBlock_Screen.h"
//#include "DF_Actor.h"
//方块颜色
#define RED    0
#define ORANGE 1
#define YELLOW 2
#define GREEN  3
#define GRAY   4
#define BLUE   5
#define	PINK   6
/*移动的方向*/
#define MOVELEFT   1
#define MOVERIGHT  2
#define MOVEDOWN   3
#define MOVEROLL   4
#define MOVETOBASE 5
#define MOVEDOWNHOLD 6
extern RussBlockUi russBlockUi;
typedef struct BOARD			/*游戏底板结构,表示每个点所具有的属性*/
{
	gm_u8 var;			/*当前状态 只有0和1*/
	gm_u8 color;				/*颜色*/
	//gm_u8  isDraw;            /*是否在屏幕显示*/
}Board;
/*方块结构*/
struct SHAPE
{
	gm_s8 box[2];			/*一个字节等于8位,每4位来表示一个方块的一行*/
	gm_u8 color;				/*颜色*/
	gm_u8 next;				/*下个方块的编号*/
	gm_u8 prev;				/*上个方块的编号*/
};
typedef struct RUSSBLOCK_MAP
{
	gm_s16 imgBlock[7];
	gm_s16 imgTop;
	gm_s16 imgTime;
	gm_s16 imgBack;    //缓冲
	
//	DF_Actor blockFallSlow;    //慢速下落
//	DF_Actor blockFallFast;    //快速下落
//	DF_Actor blockErase;   //消去方块效果
	DF_PictureLibrary * picLib;
	DF_Windows windows;	

}RussBlock_Map;

extern void initRussBlockMap(RussBlock_Map * myself,Rect windows_Rect,DF_PictureLibrary *picLib,gm_s32 repaintMax);
void RussBlock_Map_Windows_Render(void *param);
void RussBlock_Map_Windows_Update(void * param);
void RussBlock_Map_drawGrid(void * param);
static void RussBlock_Map_SetSpecifiedGrid(void * param,gm_s8 beginrow,gm_s8 row,gm_u8 var);/*填充指定行,消行动画同步用*/
void RussBlock_Map_init(gm_s32 x,gm_s32 y,gm_s32 m,gm_s32 n);
gm_s32  MkNextBox(gm_s32 box_numb);/*产生下个方块*/
gm_s32  DelFullRow(gm_s32 y);  /**/
void setFullRow(gm_s32 t_boardy);
void show_box(void * param,gm_s32 x,gm_s32 y,gm_s32 box_numb,gm_u8 color);/*显示特定方块*/
void setTimerCnt();
gm_u8 MoveAble(gm_s32 x,gm_s32 y,gm_s32 box_numb,gm_s32 direction);
void show_AllBlock(void * param);/*显示表里的所有方块*/
/*魔法消除最底下4行*/
gm_u8 setFullRow_Magic();
/*方块下落到底通知播放动画*/
void BlockDowned();
extern void RussBlock_Flush_NextBloc(void * param);/*刷新显示下个方块的区域*/
void RussBlock_EraseBlock_Run(void * param,gm_s8 arr[]);
void RussBlock_EraseBlock_Paint(void * param,gm_s8 arr[]);
#endif