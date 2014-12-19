/*******************************************************************
* 2009 Wingtech, Incoporated. All Rights Reserved.
* 
* �ļ����ƣ�RussBlock_Map.h

�˹�������Ϸ��ͼ�࣬��Ҫʵ��InGameʱ������߼�����ͼ�������㷨�������ʹ��λ
*******************************************************************/


#ifndef RUSSBLOCK_SHAPE_H
#define RUSSBLOCK_SHAPE_H

#include "coolbar_Sprite.h"
#include "DF_Windows.h"
#include "RussBlock_Screen.h"
//#include "DF_Actor.h"
//������ɫ
#define RED    0
#define ORANGE 1
#define YELLOW 2
#define GREEN  3
#define GRAY   4
#define BLUE   5
#define	PINK   6
/*�ƶ��ķ���*/
#define MOVELEFT   1
#define MOVERIGHT  2
#define MOVEDOWN   3
#define MOVEROLL   4
#define MOVETOBASE 5
#define MOVEDOWNHOLD 6
extern RussBlockUi russBlockUi;
typedef struct BOARD			/*��Ϸ�װ�ṹ,��ʾÿ���������е�����*/
{
	gm_u8 var;			/*��ǰ״̬ ֻ��0��1*/
	gm_u8 color;				/*��ɫ*/
	//gm_u8  isDraw;            /*�Ƿ�����Ļ��ʾ*/
}Board;
/*����ṹ*/
struct SHAPE
{
	gm_s8 box[2];			/*һ���ֽڵ���8λ,ÿ4λ����ʾһ�������һ��*/
	gm_u8 color;				/*��ɫ*/
	gm_u8 next;				/*�¸�����ı��*/
	gm_u8 prev;				/*�ϸ�����ı��*/
};
typedef struct RUSSBLOCK_MAP
{
	gm_s16 imgBlock[7];
	gm_s16 imgTop;
	gm_s16 imgTime;
	gm_s16 imgBack;    //����
	
//	DF_Actor blockFallSlow;    //��������
//	DF_Actor blockFallFast;    //��������
//	DF_Actor blockErase;   //��ȥ����Ч��
	DF_PictureLibrary * picLib;
	DF_Windows windows;	

}RussBlock_Map;

extern void initRussBlockMap(RussBlock_Map * myself,Rect windows_Rect,DF_PictureLibrary *picLib,gm_s32 repaintMax);
void RussBlock_Map_Windows_Render(void *param);
void RussBlock_Map_Windows_Update(void * param);
void RussBlock_Map_drawGrid(void * param);
static void RussBlock_Map_SetSpecifiedGrid(void * param,gm_s8 beginrow,gm_s8 row,gm_u8 var);/*���ָ����,���ж���ͬ����*/
void RussBlock_Map_init(gm_s32 x,gm_s32 y,gm_s32 m,gm_s32 n);
gm_s32  MkNextBox(gm_s32 box_numb);/*�����¸�����*/
gm_s32  DelFullRow(gm_s32 y);  /**/
void setFullRow(gm_s32 t_boardy);
void show_box(void * param,gm_s32 x,gm_s32 y,gm_s32 box_numb,gm_u8 color);/*��ʾ�ض�����*/
void setTimerCnt();
gm_u8 MoveAble(gm_s32 x,gm_s32 y,gm_s32 box_numb,gm_s32 direction);
void show_AllBlock(void * param);/*��ʾ��������з���*/
/*ħ�����������4��*/
gm_u8 setFullRow_Magic();
/*�������䵽��֪ͨ���Ŷ���*/
void BlockDowned();
extern void RussBlock_Flush_NextBloc(void * param);/*ˢ����ʾ�¸����������*/
void RussBlock_EraseBlock_Run(void * param,gm_s8 arr[]);
void RussBlock_EraseBlock_Paint(void * param,gm_s8 arr[]);
#endif